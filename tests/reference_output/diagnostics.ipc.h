
#ifndef __TESTS_REFERENCE_OUTPUT_DIAGNOSTICS_IPC_H__
#define __TESTS_REFERENCE_OUTPUT_DIAGNOSTICS_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "tests/headers/diagnostics.h"

#ifndef __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_DECLARATIONS__

namespace com::example::diagnostics::v1 {

    // Registers an implementation of the ::com::example::diagnostics::v1::Diagnostics interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
    registerDiagnosticsImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::diagnostics::v1::Diagnostics> theImplementation
    );

    // Looks up a remote implementation of ::com::example::diagnostics::v1::Diagnostics using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
    lookupDiagnosticsImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

}


#endif

//==============================================================================
// Below here is only implementation code which may be perused at leisure
// by an interested reader.

#ifndef __BABEL_HELPERS_FIRST__
#define __BABEL_HELPERS_FIRST__

namespace babel {

    template < class T > struct is_supported_ptr_helper                     : std::false_type {};
    template < class T > struct is_supported_ptr_helper<std::shared_ptr<T>> : std::true_type {};
    template < class T > struct is_supported_ptr_helper<std::unique_ptr<T>> : std::true_type {};
    template < class T > struct is_supported_ptr                            : is_supported_ptr_helper< std::remove_cv_t<T> > {};

    template < class T > struct is_supported_container_helper               : std::false_type {};
    template < class T > struct is_map_container_helper                     : std::false_type {};
    template < class T > struct is_fixed_container_helper                   : std::false_type {};

}


#endif
#ifndef __BABEL_HELPERS_LAST__
#define __BABEL_HELPERS_LAST__

namespace babel {

    template < class T >  struct is_supported_container : is_supported_container_helper< std::remove_cv_t<T>> {};
    template < class T >  struct is_fixed_container     : is_fixed_container_helper< std::remove_cv_t<T>> {};
    template < class T >  struct is_map_container       : is_map_container_helper< std::remove_cv_t<T>> {};

    using std::is_arithmetic;

    template < class T >
    using is_supported = std::conditional<
            ( is_arithmetic<T>::value | is_supported_ptr<T>::value | is_supported_container<T>::value),
              std::true_type, std::false_type
        >;

}


#endif
#ifndef __HAVE_BABEL__IPC_HELPERS__
#define __HAVE_BABEL__IPC_HELPERS__

namespace babel::ipc {

    //======================================================================
    // Templates for providing a value view of an array
    //
    template<std::size_t N, typename Enum, std::size_t... Indices> 
    inline auto ArrayValue( const std::array<std::enable_if_t<std::is_enum<Enum>::value,Enum>,N>& theArray, std::index_sequence< Indices...>&& ) {
        static_assert( sizeof(theArray)   == sizeof(std::array<std::underlying_type_t<Enum>,N>), "Woops, something wrong with enum array size" );
        static_assert( sizeof(theArray[0]) == sizeof(std::underlying_type_t<Enum>), "Woops, something wrong with enum size" );

        return reinterpret_cast<const std::array<std::underlying_type_t<Enum>,N>&>(theArray);
    }

    template<std::size_t N, typename, std::size_t... Indices> 
    auto ArrayValue( const std::array<std::string,N>& theArray, std::index_sequence< Indices...>&& ) {
        return std::array<const char *, N>{ theArray[Indices].c_str()... };
    }

    template<std::size_t N, typename Boolean, std::size_t... Indices> 
    auto ArrayValue( const std::array<bool,N>& theArray, std::index_sequence< Indices...>&& ) {
        return std::array<Boolean, N>{ static_cast<Boolean>(theArray[Indices])... };
    }

    template <typename E, std::size_t N, typename B = int> 
    inline auto ArrayValue( const std::array<E,N>& theArray, B = B{}) {
        return ArrayValue<N,B>( theArray, std::make_index_sequence<N>() );
    }

    //======================================================================
    // Templates for references of some types
    //
    template <typename Boolean>
    struct BooleanReference {
        bool    &itsValue;
        Boolean  itsValueView;
        BooleanReference( bool &theValue ) : itsValue{theValue},itsValueView{static_cast<Boolean>(theValue)} {}
        ~BooleanReference() { itsValue = (itsValueView != Boolean{}); }
        auto operator&() { return &itsValueView; }
    };

    template <typename Enum, void (*validate) ( Enum &, Enum, std::string& ) > 
    struct EnumReference {
        using ViewType = std::underlying_type_t<Enum>;
        Enum        &itsValue;
        std::string &itsErrorString;
        ViewType     itsValueView;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        EnumReference( Enum &theValue, std::string &theErrorString ) : itsValue{theValue}, itsErrorString(theErrorString), itsValueView{static_cast<ViewType>(theValue)} {}
    #pragma GCC diagnostic pop
        ~EnumReference() { validate(itsValue, static_cast<Enum>(itsValueView), itsErrorString ); }
        auto operator&() { return &itsValueView; }
    };

    struct StringReference {
        std::string &itsValue;
        const char  *itsValueView;
        StringReference(std::string &theValue) : itsValue{theValue}, itsValueView{theValue.c_str()} {}
        ~StringReference() { if (itsValue.c_str() != itsValueView) itsValue = itsValueView; }
        auto operator&() { return &itsValueView; }
    };


    //======================================================================
    // Templates for references to array values
    //
    template <typename ValueType, typename ReferenceType, std::size_t N, std::size_t... Indices>
    struct ArrayReference {
        std::array<ReferenceType,  N> itsArrayView;

        ArrayReference( std::array<ValueType,N>& theArray ) 
          : itsArrayView{theArray[Indices]...} {
        }

        auto operator&() { return std::array<decltype(&itsArrayView[0]),N>{&itsArrayView[Indices]...}; }
    };

    template <typename Enum, void (*validate) ( Enum &, Enum, std::string& ), std::size_t N >
    struct EnumArrayReference {
        using UnderlyingArrayType = std::array<std::underlying_type_t<Enum>,N>;
        UnderlyingArrayType &itsUnderlyingArray;
        std::string         &itsErrorString;

        EnumArrayReference(std::array<Enum, N> &theArray, std::string &theErrorString )
            : itsUnderlyingArray(reinterpret_cast<UnderlyingArrayType&>(theArray)),itsErrorString(theErrorString) {
        }
        auto operator &() { return &itsUnderlyingArray; }
        ~EnumArrayReference() {
        Enum notUsed; for (auto v : itsUnderlyingArray ) { validate( notUsed, static_cast<Enum>(v), itsErrorString ); }
        }
    };

    template< typename ValueType, typename ReferenceType, std::size_t N, std::size_t... Indices > 
    inline auto MakeArrayReferenceImpl( std::array<ValueType,N>& theArray, std::index_sequence<Indices...> ) {
        return ArrayReference< ValueType, ReferenceType, N, Indices... >( theArray );
    }

    template <typename Boolean, std::size_t N, typename Indices = std::make_index_sequence<N> > 
    inline auto MakeBooleanArrayReference( std::array<Boolean,N>& theArray ) {
        return MakeArrayReferenceImpl< bool, BooleanReference< Boolean >>( theArray, Indices() );
    }

    template <typename Enum, void (*validate)( Enum &, Enum, std::string& ), std::size_t N >
    inline auto MakeEnumArrayReference( std::array<Enum,N>& theArray, std::string &theErrorString ) {
        return EnumArrayReference<Enum,validate,N>( theArray, theErrorString );
    }

    template< std::size_t N, typename Indices = std::make_index_sequence<N> > 
    inline auto MakeStringArrayReference( std::array<std::string,N>& theArray ) {
        return MakeArrayReferenceImpl<std::string, StringReference>( theArray, Indices() );
    }


}


#endif
#ifndef __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_STUBS__
#define __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_STUBS__

namespace com::example::diagnostics::v1 {

    template <typename IpcPolicy>
    struct DiagnosticsImplementationProxy final :
        public ::com::example::diagnostics::v1::Diagnostics,
        public IpcPolicy::Implementor {

        ~DiagnosticsImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.diagnostics.v1.Diagnostics", this);
        }

        DiagnosticsImplementationProxy( const DiagnosticsImplementationProxy &)             = delete;
        DiagnosticsImplementationProxy( DiagnosticsImplementationProxy &&)                  = delete;
        DiagnosticsImplementationProxy &operator=( const DiagnosticsImplementationProxy & ) = delete;
        DiagnosticsImplementationProxy &operator=( DiagnosticsImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
        registerDiagnosticsImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        DiagnosticsImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        std::string getStatus(  ) override {
            return itsImplementation->getStatus();
        }

        static void getStatus( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<DiagnosticsImplementationProxy&>(*theThis);

            IpcPolicy::appendMessageArguments(
                theReturnValue,
                theProxy.getStatus().c_str()
            );

        }

        std::string getVersion(  ) override {
            return itsImplementation->getVersion();
        }

        static void getVersion( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<DiagnosticsImplementationProxy&>(*theThis);

            IpcPolicy::appendMessageArguments(
                theReturnValue,
                theProxy.getVersion().c_str()
            );

        }

    };

    template <typename IpcPolicy>
    struct DiagnosticsClientProxy final : public ::com::example::diagnostics::v1::Diagnostics {

        DiagnosticsClientProxy( const DiagnosticsClientProxy &)             = delete;
        DiagnosticsClientProxy( DiagnosticsClientProxy &&)                  = delete;
        DiagnosticsClientProxy &operator=( const DiagnosticsClientProxy & ) = delete;
        DiagnosticsClientProxy &operator=( DiagnosticsClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
        lookupDiagnosticsImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        DiagnosticsClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        std::string getStatus(  ) override {
            std::string theIpcReturnValue;
            Message     theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getStatus"
                );

            auto theMessageReturnValue = itsIpcPolicy->sendMessage( theIpcMessage );

            IpcPolicy::getMessageArguments(
                theMessageReturnValue,
                &babel::ipc::StringReference(theIpcReturnValue)
            );

            return theIpcReturnValue;
        }

        std::string getVersion(  ) override {
            std::string theIpcReturnValue;
            Message     theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getVersion"
                );

            auto theMessageReturnValue = itsIpcPolicy->sendMessage( theIpcMessage );

            IpcPolicy::getMessageArguments(
                theMessageReturnValue,
                &babel::ipc::StringReference(theIpcReturnValue)
            );

            return theIpcReturnValue;
        }

    };

    template <typename IpcPolicy>
    const char DiagnosticsClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.diagnostics.v1.Diagnostics";


    template <typename IpcPolicy>
    struct DiagnosticsClientProxyWrapper final :
        public ::com::example::diagnostics::v1::Diagnostics,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::diagnostics::v1::Diagnostics> itsTransmitter;
        std::weak_ptr<::com::example::diagnostics::v1::Diagnostics>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
        lookupDiagnosticsImplementation( std::shared_ptr<Policy>, const char * );

        explicit DiagnosticsClientProxyWrapper( const std::shared_ptr<::com::example::diagnostics::v1::Diagnostics> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        std::string getStatus(  ) override {
            return getItsTransmitter()->getStatus(  );
        }

        std::string getVersion(  ) override {
            return getItsTransmitter()->getVersion(  );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::diagnostics::v1::Diagnostics>(theImplementor);
        }

    };

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__DIAGNOSTICS__V1__DIAGNOSTICS_IMPLEMENTATIONS__

namespace com::example::diagnostics::v1 {

    // Registers an implementation of the ::com::example::diagnostics::v1::Diagnostics interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
    registerDiagnosticsImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::diagnostics::v1::Diagnostics> theImplementation
    ) 
    {
        using ImplementationProxy = DiagnosticsImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.diagnostics.v1.Diagnostics", theProxy )
            .template addMethod< const char *, void >( "getStatus", ImplementationProxy::getStatus )
            .template addMethod< const char *, void >( "getVersion", ImplementationProxy::getVersion )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::diagnostics::v1::Diagnostics using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::diagnostics::v1::Diagnostics>
    lookupDiagnosticsImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<DiagnosticsClientProxyWrapper<IpcPolicy>>(
            new DiagnosticsClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<DiagnosticsClientProxy<IpcPolicy>>(
                    new DiagnosticsClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::diagnostics::v1::Diagnostics>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, DiagnosticsClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }

}


#endif

#endif
