
#ifndef ___HOME_CALLE_TMP_RELEASE_REPOS_APP_SERVICE_PLATFORM_FRAMEWORK_GEN_FILES_TRIPLOG_IPC_H__
#define ___HOME_CALLE_TMP_RELEASE_REPOS_APP_SERVICE_PLATFORM_FRAMEWORK_GEN_FILES_TRIPLOG_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "/home/calle/tmp/release/repos/app-service-platform-framework/dep/app-core-data-engine/include/ocp/ipc/cde/triplog.h"


#ifndef __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace cde { namespace v1 { 
#else
namespace com::volvo::ocp::cde::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::cde::v1::Triplog interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    registerTriplogImplementation(
        std::shared_ptr<IpcPolicy>                           theIpcPolicy,
        const char*                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::cde::v1::Triplog using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    lookupTriplogImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::volvo::ocp::cde::v1::Triplog interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    registerTriplogBroadcastListener(
        std::shared_ptr<IpcPolicy>                           theIpcPolicy,
        const char*                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> theImplementation
    );

    // Creates a proxy implementing the ::com::volvo::ocp::cde::v1::Triplog interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    getTriplogBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__CDE__V1__LOG_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__CDE__V1__LOG_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace cde { namespace v1 { 
#else
namespace com::volvo::ocp::cde::v1 {
#endif

    void IpcEnumValidate( Log &theTarget, Log theValue, std::string &theErrorString ) __attribute__((weak));


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__CDE__V1__LOG_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__CDE__V1__LOG_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace cde { namespace v1 { 
#else
namespace com::volvo::ocp::cde::v1 {
#endif

    void IpcEnumValidate( Log &theTarget, Log theValue, std::string &theErrorString )  {
        switch (theValue) {
        case Log::log1:
        case Log::log2:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::volvo::ocp::cde::v1::Log");
    }


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_STUBS__
#define __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace cde { namespace v1 { 
#else
namespace com::volvo::ocp::cde::v1 {
#endif

    template <typename IpcPolicy>
    struct TriplogImplementationProxy final :
        public ::com::volvo::ocp::cde::v1::Triplog,
        public IpcPolicy::Implementor {

        ~TriplogImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.cde.v1.Triplog", this);
        }

        TriplogImplementationProxy( const TriplogImplementationProxy &)             = delete;
        TriplogImplementationProxy( TriplogImplementationProxy &&)                  = delete;
        TriplogImplementationProxy &operator=( const TriplogImplementationProxy & ) = delete;
        TriplogImplementationProxy &operator=( TriplogImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
        registerTriplogImplementation(
            std::shared_ptr<Policy>                               theIpcPolicy,
            const char *                                          theObjectPath,
            std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TriplogImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void reset( ::com::volvo::ocp::cde::v1::Log log ) override {
            itsImplementation->reset(log);
        }

        static void reset( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TriplogImplementationProxy&>(*theThis);

            ::com::volvo::ocp::cde::v1::Log log;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::cde::v1::Log,
                    ::com::volvo::ocp::cde::v1::IpcEnumValidate
                >(log, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.reset(
                log
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct TriplogClientProxy final : public ::com::volvo::ocp::cde::v1::Triplog {

        TriplogClientProxy( const TriplogClientProxy &)             = delete;
        TriplogClientProxy( TriplogClientProxy &&)                  = delete;
        TriplogClientProxy &operator=( const TriplogClientProxy & ) = delete;
        TriplogClientProxy &operator=( TriplogClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
        lookupTriplogImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TriplogClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void reset( ::com::volvo::ocp::cde::v1::Log log ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "reset"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(log)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TriplogClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.cde.v1.Triplog";


    template <typename IpcPolicy>
    struct TriplogClientProxyWrapper final :
        public ::com::volvo::ocp::cde::v1::Triplog,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::cde::v1::Triplog>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
        lookupTriplogImplementation( std::shared_ptr<Policy>, const char * );

        explicit TriplogClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void reset( ::com::volvo::ocp::cde::v1::Log log ) override {
            getItsTransmitter()->reset( log );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::cde::v1::Triplog>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct TriplogBroadcastListener final :
        public ::com::volvo::ocp::cde::v1::Triplog,
        public IpcPolicy::Implementor {

        ~TriplogBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.cde.v1.Triplog", this);
        }

        TriplogBroadcastListener( const TriplogBroadcastListener &)             = delete;
        TriplogBroadcastListener( TriplogBroadcastListener &&)                  = delete;
        TriplogBroadcastListener &operator=( const TriplogBroadcastListener & ) = delete;
        TriplogBroadcastListener &operator=( TriplogBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
        registerTriplogBroadcastListener(
            std::shared_ptr<Policy>                               theIpcPolicy,
            const char *                                          theObjectPath,
            std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TriplogBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void reset( ::com::volvo::ocp::cde::v1::Log log ) override {
            itsImplementation->reset(log);
        }

        static void reset( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TriplogBroadcastListener&>(*theThis);

            ::com::volvo::ocp::cde::v1::Log log;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::cde::v1::Log,
                    ::com::volvo::ocp::cde::v1::IpcEnumValidate
                >(log, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.reset(
                log
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct TriplogBroadcastProxy final : public ::com::volvo::ocp::cde::v1::Triplog {

        TriplogBroadcastProxy( const TriplogBroadcastProxy &)             = delete;
        TriplogBroadcastProxy( TriplogBroadcastProxy &&)                  = delete;
        TriplogBroadcastProxy &operator=( const TriplogBroadcastProxy & ) = delete;
        TriplogBroadcastProxy &operator=( TriplogBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
        getTriplogBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TriplogBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void reset( ::com::volvo::ocp::cde::v1::Log log ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "reset"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(log)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TriplogBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.cde.v1.Triplog";

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__CDE__V1__TRIPLOG_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace cde { namespace v1 { 
#else
namespace com::volvo::ocp::cde::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::cde::v1::Triplog interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    registerTriplogImplementation(
        std::shared_ptr<IpcPolicy>                           theIpcPolicy,
        const char*                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> theImplementation
    ) 
    {
        using ImplementationProxy = TriplogImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.cde.v1.Triplog", theProxy )
            .template addMethod< void, std::uint8_t >( "reset", ImplementationProxy::reset )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::cde::v1::Triplog using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    lookupTriplogImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<TriplogClientProxyWrapper<IpcPolicy>>(
            new TriplogClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<TriplogClientProxy<IpcPolicy>>(
                    new TriplogClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::cde::v1::Triplog>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, TriplogClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::volvo::ocp::cde::v1::Triplog interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    registerTriplogBroadcastListener(
        std::shared_ptr<IpcPolicy>                           theIpcPolicy,
        const char*                                          theObjectPath,
        std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog> theImplementation
    ) 
    {
        using ImplementationProxy = TriplogBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.volvo.ocp.cde.v1.Triplog", theProxy )
            .template addSignal< std::uint8_t >( "reset", ImplementationProxy::reset )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::volvo::ocp::cde::v1::Triplog interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::cde::v1::Triplog can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::cde::v1::Triplog>
    getTriplogBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<Triplog>(new TriplogBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#endif
