
#ifndef ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_COMMINFO_CLI_IPC_H__
#define ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_COMMINFO_CLI_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "/home/calle/tmp/release/repos/app-message-handler/src/include/internal_ipc/comminfo_cli.h"


#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::CommInfoCli interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
    registerCommInfoCliImplementation(
        std::shared_ptr<IpcPolicy>                                           theIpcPolicy,
        const char*                                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::CommInfoCli using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
    lookupCommInfoCliImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

//==============================================================================
// Below here is only implementation code which may be perused at leisure
// by an interested reader.

#ifndef __BABEL_HELPERS_FIRST__
#define __BABEL_HELPERS_FIRST__

#if __cplusplus < 201700L
namespace babel { 
#else
namespace babel {
#endif

    template < class T > struct is_supported_ptr_helper                     : std::false_type {};
    template < class T > struct is_supported_ptr_helper<std::shared_ptr<T>> : std::true_type {};
    template < class T > struct is_supported_ptr_helper<std::unique_ptr<T>> : std::true_type {};
    template < class T > struct is_supported_ptr                            : is_supported_ptr_helper< std::remove_cv_t<T> > {};

    template < class T > struct is_supported_container_helper               : std::false_type {};
    template < class T > struct is_map_container_helper                     : std::false_type {};
    template < class T > struct is_fixed_container_helper                   : std::false_type {};

#if __cplusplus < 201700L
}
#else
}
#endif


#endif

#ifndef __BABEL_HELPERS_LAST__
#define __BABEL_HELPERS_LAST__

#if __cplusplus < 201700L
namespace babel { 
#else
namespace babel {
#endif

    template < class T >  struct is_supported_container : is_supported_container_helper< std::remove_cv_t<T>> {};
    template < class T >  struct is_fixed_container     : is_fixed_container_helper< std::remove_cv_t<T>> {};
    template < class T >  struct is_map_container       : is_map_container_helper< std::remove_cv_t<T>> {};

    using std::is_arithmetic;

    template < class T >
    using is_supported = std::conditional<
            ( is_arithmetic<T>::value | is_supported_ptr<T>::value | is_supported_container<T>::value),
              std::true_type, std::false_type
        >;

#if __cplusplus < 201700L
}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC_HELPERS__
#define __HAVE_BABEL__IPC_HELPERS__

#if __cplusplus < 201700L
namespace babel { namespace ipc { 
#else
namespace babel::ipc {
#endif

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


#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_STUBS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    template <typename IpcPolicy>
    struct CommInfoCliImplementationProxy final :
        public ::com::volvo::ocp::message_handler::v1::CommInfoCli,
        public IpcPolicy::Implementor {

        ~CommInfoCliImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.message_handler.v1.CommInfoCli", this);
        }

        CommInfoCliImplementationProxy( const CommInfoCliImplementationProxy &)             = delete;
        CommInfoCliImplementationProxy( CommInfoCliImplementationProxy &&)                  = delete;
        CommInfoCliImplementationProxy &operator=( const CommInfoCliImplementationProxy & ) = delete;
        CommInfoCliImplementationProxy &operator=( CommInfoCliImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
        registerCommInfoCliImplementation(
            std::shared_ptr<Policy>                                               theIpcPolicy,
            const char *                                                          theObjectPath,
            std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        CommInfoCliImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        std::string getCommInfo() override {
            return itsImplementation->getCommInfo();
        }

        static void getCommInfo( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<CommInfoCliImplementationProxy&>(*theThis);




            IpcPolicy::appendMessageArguments(
                theReturnValue,
                theProxy.getCommInfo().c_str()
            );

        }

        std::string getServicesInfo() override {
            return itsImplementation->getServicesInfo();
        }

        static void getServicesInfo( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<CommInfoCliImplementationProxy&>(*theThis);




            IpcPolicy::appendMessageArguments(
                theReturnValue,
                theProxy.getServicesInfo().c_str()
            );

        }

    };

    template <typename IpcPolicy>
    struct CommInfoCliClientProxy final : public ::com::volvo::ocp::message_handler::v1::CommInfoCli {

        CommInfoCliClientProxy( const CommInfoCliClientProxy &)             = delete;
        CommInfoCliClientProxy( CommInfoCliClientProxy &&)                  = delete;
        CommInfoCliClientProxy &operator=( const CommInfoCliClientProxy & ) = delete;
        CommInfoCliClientProxy &operator=( CommInfoCliClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
        lookupCommInfoCliImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        CommInfoCliClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        std::string getCommInfo() override {
            std::string theIpcReturnValue;
            Message     theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getCommInfo"
                );



            auto theMessageReturnValue = itsIpcPolicy->sendMessage( theIpcMessage );

            IpcPolicy::getMessageArguments(
                theMessageReturnValue,
                &babel::ipc::StringReference(theIpcReturnValue)
            );


            return theIpcReturnValue;
        }

        std::string getServicesInfo() override {
            std::string theIpcReturnValue;
            Message     theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getServicesInfo"
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
    const char CommInfoCliClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.message_handler.v1.CommInfoCli";


    template <typename IpcPolicy>
    struct CommInfoCliClientProxyWrapper final :
        public ::com::volvo::ocp::message_handler::v1::CommInfoCli,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
        lookupCommInfoCliImplementation( std::shared_ptr<Policy>, const char * );

        explicit CommInfoCliClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        std::string getCommInfo() override {
            return getItsTransmitter()->getCommInfo();
        }

        std::string getServicesInfo() override {
            return getItsTransmitter()->getServicesInfo();
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::CommInfoCli>(theImplementor);
        }

    };


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__COMMINFOCLI_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::CommInfoCli interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
    registerCommInfoCliImplementation(
        std::shared_ptr<IpcPolicy>                                           theIpcPolicy,
        const char*                                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli> theImplementation
    ) 
    {
        using ImplementationProxy = CommInfoCliImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.message_handler.v1.CommInfoCli", theProxy )
            .template addMethod< const char *, void >( "getCommInfo",     ImplementationProxy::getCommInfo )
            .template addMethod< const char *, void >( "getServicesInfo", ImplementationProxy::getServicesInfo )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::CommInfoCli using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::CommInfoCli>
    lookupCommInfoCliImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<CommInfoCliClientProxyWrapper<IpcPolicy>>(
            new CommInfoCliClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<CommInfoCliClientProxy<IpcPolicy>>(
                    new CommInfoCliClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::CommInfoCli>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, CommInfoCliClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#endif
