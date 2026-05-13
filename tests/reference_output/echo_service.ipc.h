
#ifndef __TESTS_REFERENCE_OUTPUT_ECHO_SERVICE_IPC_H__
#define __TESTS_REFERENCE_OUTPUT_ECHO_SERVICE_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "tests/headers/echo_service.h"

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_DECLARATIONS__

namespace com::example::echo::v1 {

    // Registers an implementation of the ::com::example::echo::v1::EchoRequest interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    registerEchoRequestImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoRequest> theImplementation
    );

    // Looks up a remote implementation of ::com::example::echo::v1::EchoRequest using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    lookupEchoRequestImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::example::echo::v1::EchoRequest interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    registerEchoRequestBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoRequest> theImplementation
    );

    // Creates a proxy implementing the ::com::example::echo::v1::EchoRequest interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    getEchoRequestBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


}


#endif

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_DECLARATIONS__

namespace com::example::echo::v1 {

    // Registers an implementation of the ::com::example::echo::v1::EchoResponse interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    registerEchoResponseImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoResponse> theImplementation
    );

    // Looks up a remote implementation of ::com::example::echo::v1::EchoResponse using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    lookupEchoResponseImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::example::echo::v1::EchoResponse interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    registerEchoResponseBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoResponse> theImplementation
    );

    // Creates a proxy implementing the ::com::example::echo::v1::EchoResponse interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    getEchoResponseBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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
#ifndef __BABEL_HELPERS_STD__VECTOR__
#define __BABEL_HELPERS_STD__VECTOR__

#include <vector>

namespace babel {

    template < class T> struct is_supported_container_helper<std::vector<T>> : std::true_type {};

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
#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__PAYLOAD_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__PAYLOAD_IPC_DECLARATIONS__

namespace com::example::echo::v1 {

    template <typename Boolean,typename IpcPolicy>
    using Payload_ArrayView = std::array<std::uint8_t,1>;

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::com::example::echo::v1::Payload &theVaryingLengthContainer );

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::com::example::echo::v1::Payload &theVaryingLengthContainer );

}


#endif

#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__ECHOSTATUS_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__ECHOSTATUS_IPC_DECLARATIONS__

namespace com::example::echo::v1 {

    void IpcEnumValidate( EchoStatus &theTarget, EchoStatus theValue, std::string &theErrorString ) __attribute__((weak));

}


#endif

#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__PAYLOAD_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__PAYLOAD_IPC_IMPLEMENTATIONS__

namespace com::example::echo::v1 {

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::com::example::echo::v1::Payload &theVaryingLengthContainer ) {
        const ::com::example::echo::v1::Payload::value_type *theValues     = nullptr;
        ::com::example::echo::v1::Payload::size_type         theNoOfValues = 0;

        IpcPolicy::getMessageArray( theMessage, theValues, theNoOfValues );

        theVaryingLengthContainer.assign( theValues, (theValues+theNoOfValues) );
    }
    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::com::example::echo::v1::Payload &theVaryingLengthContainer ) {
        IpcPolicy::appendMessageArray(
            theMessage,
            &theVaryingLengthContainer.front(),
            theVaryingLengthContainer.size()
        );
    }

}


#endif

#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__ECHOSTATUS_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__ECHO__V1__ECHOSTATUS_IPC_IMPLEMENTATIONS__

namespace com::example::echo::v1 {

    void IpcEnumValidate( EchoStatus &theTarget, EchoStatus theValue, std::string &theErrorString )  {
        switch (theValue) {
        case EchoStatus::OK:
        case EchoStatus::Error:
        case EchoStatus::Timeout:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::example::echo::v1::EchoStatus");
    }

}


#endif

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_STUBS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_STUBS__

namespace com::example::echo::v1 {

    template <typename IpcPolicy>
    struct EchoRequestImplementationProxy final :
        public ::com::example::echo::v1::EchoRequest,
        public IpcPolicy::Implementor {

        ~EchoRequestImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.echo.v1.EchoRequest", this);
        }

        EchoRequestImplementationProxy( const EchoRequestImplementationProxy &)             = delete;
        EchoRequestImplementationProxy( EchoRequestImplementationProxy &&)                  = delete;
        EchoRequestImplementationProxy &operator=( const EchoRequestImplementationProxy & ) = delete;
        EchoRequestImplementationProxy &operator=( EchoRequestImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::echo::v1::EchoRequest>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoRequest>
        registerEchoRequestImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::echo::v1::EchoRequest>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        EchoRequestImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void ping( const std::string &destination, std::uint64_t timeoutMs ) override {
            itsImplementation->ping(destination, timeoutMs);
        }

        static void ping( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoRequestImplementationProxy&>(*theThis);

            std::string destination;

            std::uint64_t timeoutMs;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(destination),
                &timeoutMs
            );

            theProxy.ping(
                destination, timeoutMs
            );
        }

        void sendPayload( const std::string &destination, std::uint64_t timeoutMs, const ::com::example::echo::v1::Payload &data, bool compressed ) override {
            itsImplementation->sendPayload(destination, timeoutMs, data, compressed);
        }

        static void sendPayload( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoRequestImplementationProxy&>(*theThis);

            std::string destination;

            std::uint64_t timeoutMs;

            ::com::example::echo::v1::Payload data;

            bool compressed;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(destination),
                &timeoutMs
            );
            ::com::example::echo::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                data
            );
            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::BooleanReference<typename IpcPolicy::Boolean>(compressed)
            );

            theProxy.sendPayload(
                destination, timeoutMs, data, compressed
            );
        }

    };

    template <typename IpcPolicy>
    struct EchoRequestClientProxy final : public ::com::example::echo::v1::EchoRequest {

        EchoRequestClientProxy( const EchoRequestClientProxy &)             = delete;
        EchoRequestClientProxy( EchoRequestClientProxy &&)                  = delete;
        EchoRequestClientProxy &operator=( const EchoRequestClientProxy & ) = delete;
        EchoRequestClientProxy &operator=( EchoRequestClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoRequest>
        lookupEchoRequestImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        EchoRequestClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void ping( const std::string &destination, std::uint64_t timeoutMs ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "ping"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                destination.c_str(),
                timeoutMs
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

        void sendPayload( const std::string &destination, std::uint64_t timeoutMs, const ::com::example::echo::v1::Payload &data, bool compressed ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "sendPayload"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                destination.c_str(),
                timeoutMs
            );
            ::com::example::echo::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                data
            );
            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<Boolean>(compressed)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char EchoRequestClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.echo.v1.EchoRequest";


    template <typename IpcPolicy>
    struct EchoRequestClientProxyWrapper final :
        public ::com::example::echo::v1::EchoRequest,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::echo::v1::EchoRequest> itsTransmitter;
        std::weak_ptr<::com::example::echo::v1::EchoRequest>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoRequest>
        lookupEchoRequestImplementation( std::shared_ptr<Policy>, const char * );

        explicit EchoRequestClientProxyWrapper( const std::shared_ptr<::com::example::echo::v1::EchoRequest> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void ping( const std::string &destination, std::uint64_t timeoutMs ) override {
            getItsTransmitter()->ping( destination, timeoutMs );
        }

        void sendPayload( const std::string &destination, std::uint64_t timeoutMs, const ::com::example::echo::v1::Payload &data, bool compressed ) override {
            getItsTransmitter()->sendPayload( destination, timeoutMs, data, compressed );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::echo::v1::EchoRequest>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct EchoRequestBroadcastListener final :
        public ::com::example::echo::v1::EchoRequest,
        public IpcPolicy::Implementor {

        ~EchoRequestBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.echo.v1.EchoRequest", this);
        }

        EchoRequestBroadcastListener( const EchoRequestBroadcastListener &)             = delete;
        EchoRequestBroadcastListener( EchoRequestBroadcastListener &&)                  = delete;
        EchoRequestBroadcastListener &operator=( const EchoRequestBroadcastListener & ) = delete;
        EchoRequestBroadcastListener &operator=( EchoRequestBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::echo::v1::EchoRequest>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoRequest>
        registerEchoRequestBroadcastListener(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::echo::v1::EchoRequest>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        EchoRequestBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void ping( const std::string &destination, std::uint64_t timeoutMs ) override {
            itsImplementation->ping(destination, timeoutMs);
        }

        static void ping( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoRequestBroadcastListener&>(*theThis);

            std::string destination;

            std::uint64_t timeoutMs;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(destination),
                &timeoutMs
            );

            theProxy.ping(
                destination, timeoutMs
            );
        }

        void sendPayload( const std::string &destination, std::uint64_t timeoutMs, const ::com::example::echo::v1::Payload &data, bool compressed ) override {
            itsImplementation->sendPayload(destination, timeoutMs, data, compressed);
        }

        static void sendPayload( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoRequestBroadcastListener&>(*theThis);

            std::string destination;

            std::uint64_t timeoutMs;

            ::com::example::echo::v1::Payload data;

            bool compressed;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(destination),
                &timeoutMs
            );
            ::com::example::echo::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                data
            );
            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::BooleanReference<typename IpcPolicy::Boolean>(compressed)
            );

            theProxy.sendPayload(
                destination, timeoutMs, data, compressed
            );
        }

    };

    template <typename IpcPolicy>
    struct EchoRequestBroadcastProxy final : public ::com::example::echo::v1::EchoRequest {

        EchoRequestBroadcastProxy( const EchoRequestBroadcastProxy &)             = delete;
        EchoRequestBroadcastProxy( EchoRequestBroadcastProxy &&)                  = delete;
        EchoRequestBroadcastProxy &operator=( const EchoRequestBroadcastProxy & ) = delete;
        EchoRequestBroadcastProxy &operator=( EchoRequestBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoRequest>
        getEchoRequestBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        EchoRequestBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void ping( const std::string &destination, std::uint64_t timeoutMs ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "ping"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                destination.c_str(),
                timeoutMs
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

        void sendPayload( const std::string &destination, std::uint64_t timeoutMs, const ::com::example::echo::v1::Payload &data, bool compressed ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "sendPayload"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                destination.c_str(),
                timeoutMs
            );
            ::com::example::echo::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                data
            );
            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<Boolean>(compressed)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char EchoRequestBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.example.echo.v1.EchoRequest";

}


#endif

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_STUBS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_STUBS__

namespace com::example::echo::v1 {

    template <typename IpcPolicy>
    struct EchoResponseImplementationProxy final :
        public ::com::example::echo::v1::EchoResponse,
        public IpcPolicy::Implementor {

        ~EchoResponseImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.echo.v1.EchoResponse", this);
        }

        EchoResponseImplementationProxy( const EchoResponseImplementationProxy &)             = delete;
        EchoResponseImplementationProxy( EchoResponseImplementationProxy &&)                  = delete;
        EchoResponseImplementationProxy &operator=( const EchoResponseImplementationProxy & ) = delete;
        EchoResponseImplementationProxy &operator=( EchoResponseImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::echo::v1::EchoResponse>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoResponse>
        registerEchoResponseImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::echo::v1::EchoResponse>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        EchoResponseImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void pong( ::com::example::echo::v1::EchoStatus status ) override {
            itsImplementation->pong(status);
        }

        static void pong( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoResponseImplementationProxy&>(*theThis);

            ::com::example::echo::v1::EchoStatus status;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::echo::v1::EchoStatus,
                    ::com::example::echo::v1::IpcEnumValidate
                >(status, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.pong(
                status
            );
            #pragma GCC diagnostic pop
        }

        void payloadReceived( ::com::example::echo::v1::EchoStatus status, const ::com::example::echo::v1::Payload &data ) override {
            itsImplementation->payloadReceived(status, data);
        }

        static void payloadReceived( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoResponseImplementationProxy&>(*theThis);

            ::com::example::echo::v1::EchoStatus status;

            ::com::example::echo::v1::Payload data;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::echo::v1::EchoStatus,
                    ::com::example::echo::v1::IpcEnumValidate
                >(status, theErrorString )
            );
            ::com::example::echo::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                data
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.payloadReceived(
                status, data
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct EchoResponseClientProxy final : public ::com::example::echo::v1::EchoResponse {

        EchoResponseClientProxy( const EchoResponseClientProxy &)             = delete;
        EchoResponseClientProxy( EchoResponseClientProxy &&)                  = delete;
        EchoResponseClientProxy &operator=( const EchoResponseClientProxy & ) = delete;
        EchoResponseClientProxy &operator=( EchoResponseClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoResponse>
        lookupEchoResponseImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        EchoResponseClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void pong( ::com::example::echo::v1::EchoStatus status ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "pong"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

        void payloadReceived( ::com::example::echo::v1::EchoStatus status, const ::com::example::echo::v1::Payload &data ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "payloadReceived"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );
            ::com::example::echo::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                data
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char EchoResponseClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.echo.v1.EchoResponse";


    template <typename IpcPolicy>
    struct EchoResponseClientProxyWrapper final :
        public ::com::example::echo::v1::EchoResponse,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::echo::v1::EchoResponse> itsTransmitter;
        std::weak_ptr<::com::example::echo::v1::EchoResponse>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoResponse>
        lookupEchoResponseImplementation( std::shared_ptr<Policy>, const char * );

        explicit EchoResponseClientProxyWrapper( const std::shared_ptr<::com::example::echo::v1::EchoResponse> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void pong( ::com::example::echo::v1::EchoStatus status ) override {
            getItsTransmitter()->pong( status );
        }

        void payloadReceived( ::com::example::echo::v1::EchoStatus status, const ::com::example::echo::v1::Payload &data ) override {
            getItsTransmitter()->payloadReceived( status, data );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::echo::v1::EchoResponse>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct EchoResponseBroadcastListener final :
        public ::com::example::echo::v1::EchoResponse,
        public IpcPolicy::Implementor {

        ~EchoResponseBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.echo.v1.EchoResponse", this);
        }

        EchoResponseBroadcastListener( const EchoResponseBroadcastListener &)             = delete;
        EchoResponseBroadcastListener( EchoResponseBroadcastListener &&)                  = delete;
        EchoResponseBroadcastListener &operator=( const EchoResponseBroadcastListener & ) = delete;
        EchoResponseBroadcastListener &operator=( EchoResponseBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::echo::v1::EchoResponse>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoResponse>
        registerEchoResponseBroadcastListener(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::echo::v1::EchoResponse>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        EchoResponseBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void pong( ::com::example::echo::v1::EchoStatus status ) override {
            itsImplementation->pong(status);
        }

        static void pong( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoResponseBroadcastListener&>(*theThis);

            ::com::example::echo::v1::EchoStatus status;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::echo::v1::EchoStatus,
                    ::com::example::echo::v1::IpcEnumValidate
                >(status, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.pong(
                status
            );
            #pragma GCC diagnostic pop
        }

        void payloadReceived( ::com::example::echo::v1::EchoStatus status, const ::com::example::echo::v1::Payload &data ) override {
            itsImplementation->payloadReceived(status, data);
        }

        static void payloadReceived( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<EchoResponseBroadcastListener&>(*theThis);

            ::com::example::echo::v1::EchoStatus status;

            ::com::example::echo::v1::Payload data;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::echo::v1::EchoStatus,
                    ::com::example::echo::v1::IpcEnumValidate
                >(status, theErrorString )
            );
            ::com::example::echo::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                data
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.payloadReceived(
                status, data
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct EchoResponseBroadcastProxy final : public ::com::example::echo::v1::EchoResponse {

        EchoResponseBroadcastProxy( const EchoResponseBroadcastProxy &)             = delete;
        EchoResponseBroadcastProxy( EchoResponseBroadcastProxy &&)                  = delete;
        EchoResponseBroadcastProxy &operator=( const EchoResponseBroadcastProxy & ) = delete;
        EchoResponseBroadcastProxy &operator=( EchoResponseBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::echo::v1::EchoResponse>
        getEchoResponseBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        EchoResponseBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void pong( ::com::example::echo::v1::EchoStatus status ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "pong"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

        void payloadReceived( ::com::example::echo::v1::EchoStatus status, const ::com::example::echo::v1::Payload &data ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "payloadReceived"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );
            ::com::example::echo::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                data
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char EchoResponseBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.example.echo.v1.EchoResponse";

}


#endif

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHOREQUEST_IMPLEMENTATIONS__

namespace com::example::echo::v1 {

    // Registers an implementation of the ::com::example::echo::v1::EchoRequest interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    registerEchoRequestImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoRequest> theImplementation
    ) 
    {
        using ImplementationProxy = EchoRequestImplementationProxy<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.echo.v1.EchoRequest", theProxy )
            .template addMethod< void, const char *, std::uint64_t >( "ping", ImplementationProxy::ping )
            .template addMethod< void, const char *, std::uint64_t, ::com::example::echo::v1::Payload, Boolean >( "sendPayload", ImplementationProxy::sendPayload )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::echo::v1::EchoRequest using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    lookupEchoRequestImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<EchoRequestClientProxyWrapper<IpcPolicy>>(
            new EchoRequestClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<EchoRequestClientProxy<IpcPolicy>>(
                    new EchoRequestClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::echo::v1::EchoRequest>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, EchoRequestClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::example::echo::v1::EchoRequest interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    registerEchoRequestBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoRequest> theImplementation
    ) 
    {
        using ImplementationProxy = EchoRequestBroadcastListener<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.example.echo.v1.EchoRequest", theProxy )
            .template addSignal< const char *, std::uint64_t >( "ping", ImplementationProxy::ping )
            .template addSignal< const char *, std::uint64_t, ::com::example::echo::v1::Payload, Boolean >( "sendPayload", ImplementationProxy::sendPayload )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::example::echo::v1::EchoRequest interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoRequest>
    getEchoRequestBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<EchoRequest>(new EchoRequestBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

}


#endif

#ifndef __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__ECHO__V1__ECHORESPONSE_IMPLEMENTATIONS__

namespace com::example::echo::v1 {

    // Registers an implementation of the ::com::example::echo::v1::EchoResponse interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    registerEchoResponseImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoResponse> theImplementation
    ) 
    {
        using ImplementationProxy = EchoResponseImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.echo.v1.EchoResponse", theProxy )
            .template addMethod< void, std::uint8_t >( "pong", ImplementationProxy::pong )
            .template addMethod< void, std::uint8_t, ::com::example::echo::v1::Payload >( "payloadReceived", ImplementationProxy::payloadReceived )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::echo::v1::EchoResponse using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    lookupEchoResponseImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<EchoResponseClientProxyWrapper<IpcPolicy>>(
            new EchoResponseClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<EchoResponseClientProxy<IpcPolicy>>(
                    new EchoResponseClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::echo::v1::EchoResponse>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, EchoResponseClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::example::echo::v1::EchoResponse interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    registerEchoResponseBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::echo::v1::EchoResponse> theImplementation
    ) 
    {
        using ImplementationProxy = EchoResponseBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.example.echo.v1.EchoResponse", theProxy )
            .template addSignal< std::uint8_t >( "pong", ImplementationProxy::pong )
            .template addSignal< std::uint8_t, ::com::example::echo::v1::Payload >( "payloadReceived", ImplementationProxy::payloadReceived )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::example::echo::v1::EchoResponse interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::echo::v1::EchoResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::echo::v1::EchoResponse>
    getEchoResponseBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<EchoResponse>(new EchoResponseBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

}


#endif

#endif
