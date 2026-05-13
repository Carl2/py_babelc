
#ifndef ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_TEST_SERVICE_INTERFACE_IPC_H__
#define ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_TEST_SERVICE_INTERFACE_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "/home/calle/tmp/release/repos/app-message-handler/dep/app-test-service/include/ocp/ipc/test_service/test_service_interface.h"


#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    registerTestServiceRequestImplementation(
        std::shared_ptr<IpcPolicy>                                               theIpcPolicy,
        const char*                                                              theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::test_service::v1::TestServiceRequest using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    lookupTestServiceRequestImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    registerTestServiceRequestBroadcastListener(
        std::shared_ptr<IpcPolicy>                                               theIpcPolicy,
        const char*                                                              theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> theImplementation
    );

    // Creates a proxy implementing the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    getTestServiceRequestBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    registerTestServiceResponseImplementation(
        std::shared_ptr<IpcPolicy>                                                theIpcPolicy,
        const char*                                                               theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::test_service::v1::TestServiceResponse using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    lookupTestServiceResponseImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    registerTestServiceResponseBroadcastListener(
        std::shared_ptr<IpcPolicy>                                                theIpcPolicy,
        const char*                                                               theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> theImplementation
    );

    // Creates a proxy implementing the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    getTestServiceResponseBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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

#ifndef __BABEL_HELPERS_STD__VECTOR__
#define __BABEL_HELPERS_STD__VECTOR__

#include <vector>

#if __cplusplus < 201700L
namespace babel { 
#else
namespace babel {
#endif

    template < class T> struct is_supported_container_helper<std::vector<T>> : std::true_type {};

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

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PAYLOAD_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PAYLOAD_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    template <typename Boolean,typename IpcPolicy>
    using Payload_ArrayView = std::array<std::uint8_t,1>;

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::com::volvo::ocp::test_service::v1::Payload &theVaryingLengthContainer );

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::com::volvo::ocp::test_service::v1::Payload &theVaryingLengthContainer );


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PINGSTATUS_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PINGSTATUS_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    void IpcEnumValidate( PingStatus &theTarget, PingStatus theValue, std::string &theErrorString ) __attribute__((weak));


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PAYLOAD_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PAYLOAD_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::com::volvo::ocp::test_service::v1::Payload &theVaryingLengthContainer ) {
        const ::com::volvo::ocp::test_service::v1::Payload::value_type *theValues     = nullptr;
        ::com::volvo::ocp::test_service::v1::Payload::size_type         theNoOfValues = 0;

        IpcPolicy::getMessageArray( theMessage, theValues, theNoOfValues );

        theVaryingLengthContainer.assign( theValues, (theValues+theNoOfValues) );
    }
    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::com::volvo::ocp::test_service::v1::Payload &theVaryingLengthContainer ) {
        IpcPolicy::appendMessageArray(
            theMessage,
            &theVaryingLengthContainer.front(),
            theVaryingLengthContainer.size()
        );
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PINGSTATUS_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__TEST_SERVICE__V1__PINGSTATUS_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    void IpcEnumValidate( PingStatus &theTarget, PingStatus theValue, std::string &theErrorString )  {
        switch (theValue) {
        case PingStatus::OK:
        case PingStatus::ERROR:
        case PingStatus::Timeout:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::volvo::ocp::test_service::v1::PingStatus");
    }


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_STUBS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    template <typename IpcPolicy>
    struct TestServiceRequestImplementationProxy final :
        public ::com::volvo::ocp::test_service::v1::TestServiceRequest,
        public IpcPolicy::Implementor {

        ~TestServiceRequestImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.test_service.v1.TestServiceRequest", this);
        }

        TestServiceRequestImplementationProxy( const TestServiceRequestImplementationProxy &)             = delete;
        TestServiceRequestImplementationProxy( TestServiceRequestImplementationProxy &&)                  = delete;
        TestServiceRequestImplementationProxy &operator=( const TestServiceRequestImplementationProxy & ) = delete;
        TestServiceRequestImplementationProxy &operator=( TestServiceRequestImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
        registerTestServiceRequestImplementation(
            std::shared_ptr<Policy>                                                   theIpcPolicy,
            const char *                                                              theObjectPath,
            std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TestServiceRequestImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void ping(
            const std::string   &dbuspath,
                  std::uint64_t  timeOut
        ) override {
            itsImplementation->ping(dbuspath, timeOut);
        }

        static void ping( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceRequestImplementationProxy&>(*theThis);

            std::string   dbuspath;
            std::uint64_t timeOut;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(dbuspath),
                &timeOut
            );

            theProxy.ping(
                dbuspath,
                timeOut
            );
        }

        void beefyMessage(
            const std::string                                  &dbuspath,
                  std::uint64_t                                 timeOut,
            const ::com::volvo::ocp::test_service::v1::Payload &payload,
                  bool                                          copyPayload
        ) override {
            itsImplementation->beefyMessage(dbuspath, timeOut, payload, copyPayload);
        }

        static void beefyMessage( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceRequestImplementationProxy&>(*theThis);

            std::string                                  dbuspath;
            std::uint64_t                                timeOut;
            ::com::volvo::ocp::test_service::v1::Payload payload;
            bool                                         copyPayload;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(dbuspath),
                &timeOut
            );
            ::com::volvo::ocp::test_service::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                payload
            );
            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::BooleanReference<typename IpcPolicy::Boolean>(copyPayload)
            );

            theProxy.beefyMessage(
                dbuspath,
                timeOut,
                payload,
                copyPayload
            );
        }

    };

    template <typename IpcPolicy>
    struct TestServiceRequestClientProxy final : public ::com::volvo::ocp::test_service::v1::TestServiceRequest {

        TestServiceRequestClientProxy( const TestServiceRequestClientProxy &)             = delete;
        TestServiceRequestClientProxy( TestServiceRequestClientProxy &&)                  = delete;
        TestServiceRequestClientProxy &operator=( const TestServiceRequestClientProxy & ) = delete;
        TestServiceRequestClientProxy &operator=( TestServiceRequestClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
        lookupTestServiceRequestImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TestServiceRequestClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void ping(
            const std::string   &dbuspath,
                  std::uint64_t  timeOut
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "ping"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                dbuspath.c_str(),
                timeOut
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

        void beefyMessage(
            const std::string                                  &dbuspath,
                  std::uint64_t                                 timeOut,
            const ::com::volvo::ocp::test_service::v1::Payload &payload,
                  bool                                          copyPayload
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "beefyMessage"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                dbuspath.c_str(),
                timeOut
            );
            ::com::volvo::ocp::test_service::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                payload
            );
            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<Boolean>(copyPayload)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TestServiceRequestClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.test_service.v1.TestServiceRequest";


    template <typename IpcPolicy>
    struct TestServiceRequestClientProxyWrapper final :
        public ::com::volvo::ocp::test_service::v1::TestServiceRequest,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
        lookupTestServiceRequestImplementation( std::shared_ptr<Policy>, const char * );

        explicit TestServiceRequestClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void ping(
            const std::string   &dbuspath,
                  std::uint64_t  timeOut
        ) override {
            getItsTransmitter()->ping( dbuspath, timeOut );
        }

        void beefyMessage(
            const std::string                                  &dbuspath,
                  std::uint64_t                                 timeOut,
            const ::com::volvo::ocp::test_service::v1::Payload &payload,
                  bool                                          copyPayload
        ) override {
            getItsTransmitter()->beefyMessage( dbuspath, timeOut, payload, copyPayload );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::test_service::v1::TestServiceRequest>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct TestServiceRequestBroadcastListener final :
        public ::com::volvo::ocp::test_service::v1::TestServiceRequest,
        public IpcPolicy::Implementor {

        ~TestServiceRequestBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.test_service.v1.TestServiceRequest", this);
        }

        TestServiceRequestBroadcastListener( const TestServiceRequestBroadcastListener &)             = delete;
        TestServiceRequestBroadcastListener( TestServiceRequestBroadcastListener &&)                  = delete;
        TestServiceRequestBroadcastListener &operator=( const TestServiceRequestBroadcastListener & ) = delete;
        TestServiceRequestBroadcastListener &operator=( TestServiceRequestBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
        registerTestServiceRequestBroadcastListener(
            std::shared_ptr<Policy>                                                   theIpcPolicy,
            const char *                                                              theObjectPath,
            std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TestServiceRequestBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void ping(
            const std::string   &dbuspath,
                  std::uint64_t  timeOut
        ) override {
            itsImplementation->ping(dbuspath, timeOut);
        }

        static void ping( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceRequestBroadcastListener&>(*theThis);

            std::string   dbuspath;
            std::uint64_t timeOut;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(dbuspath),
                &timeOut
            );

            theProxy.ping(
                dbuspath,
                timeOut
            );
        }

        void beefyMessage(
            const std::string                                  &dbuspath,
                  std::uint64_t                                 timeOut,
            const ::com::volvo::ocp::test_service::v1::Payload &payload,
                  bool                                          copyPayload
        ) override {
            itsImplementation->beefyMessage(dbuspath, timeOut, payload, copyPayload);
        }

        static void beefyMessage( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceRequestBroadcastListener&>(*theThis);

            std::string                                  dbuspath;
            std::uint64_t                                timeOut;
            ::com::volvo::ocp::test_service::v1::Payload payload;
            bool                                         copyPayload;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::StringReference(dbuspath),
                &timeOut
            );
            ::com::volvo::ocp::test_service::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                payload
            );
            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::BooleanReference<typename IpcPolicy::Boolean>(copyPayload)
            );

            theProxy.beefyMessage(
                dbuspath,
                timeOut,
                payload,
                copyPayload
            );
        }

    };

    template <typename IpcPolicy>
    struct TestServiceRequestBroadcastProxy final : public ::com::volvo::ocp::test_service::v1::TestServiceRequest {

        TestServiceRequestBroadcastProxy( const TestServiceRequestBroadcastProxy &)             = delete;
        TestServiceRequestBroadcastProxy( TestServiceRequestBroadcastProxy &&)                  = delete;
        TestServiceRequestBroadcastProxy &operator=( const TestServiceRequestBroadcastProxy & ) = delete;
        TestServiceRequestBroadcastProxy &operator=( TestServiceRequestBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
        getTestServiceRequestBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TestServiceRequestBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void ping(
            const std::string   &dbuspath,
                  std::uint64_t  timeOut
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "ping"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                dbuspath.c_str(),
                timeOut
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

        void beefyMessage(
            const std::string                                  &dbuspath,
                  std::uint64_t                                 timeOut,
            const ::com::volvo::ocp::test_service::v1::Payload &payload,
                  bool                                          copyPayload
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "beefyMessage"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                dbuspath.c_str(),
                timeOut
            );
            ::com::volvo::ocp::test_service::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                payload
            );
            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<Boolean>(copyPayload)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TestServiceRequestBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.test_service.v1.TestServiceRequest";

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_STUBS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    template <typename IpcPolicy>
    struct TestServiceResponseImplementationProxy final :
        public ::com::volvo::ocp::test_service::v1::TestServiceResponse,
        public IpcPolicy::Implementor {

        ~TestServiceResponseImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.test_service.v1.TestServiceResponse", this);
        }

        TestServiceResponseImplementationProxy( const TestServiceResponseImplementationProxy &)             = delete;
        TestServiceResponseImplementationProxy( TestServiceResponseImplementationProxy &&)                  = delete;
        TestServiceResponseImplementationProxy &operator=( const TestServiceResponseImplementationProxy & ) = delete;
        TestServiceResponseImplementationProxy &operator=( TestServiceResponseImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
        registerTestServiceResponseImplementation(
            std::shared_ptr<Policy>                                                    theIpcPolicy,
            const char *                                                               theObjectPath,
            std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TestServiceResponseImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void pong( ::com::volvo::ocp::test_service::v1::PingStatus status ) override {
            itsImplementation->pong(status);
        }

        static void pong( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceResponseImplementationProxy&>(*theThis);

            ::com::volvo::ocp::test_service::v1::PingStatus status;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::test_service::v1::PingStatus,
                    ::com::volvo::ocp::test_service::v1::IpcEnumValidate
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

        void beefyMessageResponse(
                  ::com::volvo::ocp::test_service::v1::PingStatus  status,
            const ::com::volvo::ocp::test_service::v1::Payload    &payload
        ) override {
            itsImplementation->beefyMessageResponse(status, payload);
        }

        static void beefyMessageResponse( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceResponseImplementationProxy&>(*theThis);

            ::com::volvo::ocp::test_service::v1::PingStatus status;
            ::com::volvo::ocp::test_service::v1::Payload    payload;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::test_service::v1::PingStatus,
                    ::com::volvo::ocp::test_service::v1::IpcEnumValidate
                >(status, theErrorString )
            );
            ::com::volvo::ocp::test_service::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                payload
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.beefyMessageResponse(
                status,
                payload
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct TestServiceResponseClientProxy final : public ::com::volvo::ocp::test_service::v1::TestServiceResponse {

        TestServiceResponseClientProxy( const TestServiceResponseClientProxy &)             = delete;
        TestServiceResponseClientProxy( TestServiceResponseClientProxy &&)                  = delete;
        TestServiceResponseClientProxy &operator=( const TestServiceResponseClientProxy & ) = delete;
        TestServiceResponseClientProxy &operator=( TestServiceResponseClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
        lookupTestServiceResponseImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TestServiceResponseClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void pong( ::com::volvo::ocp::test_service::v1::PingStatus status ) override {
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

        void beefyMessageResponse(
                  ::com::volvo::ocp::test_service::v1::PingStatus  status,
            const ::com::volvo::ocp::test_service::v1::Payload    &payload
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "beefyMessageResponse"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );
            ::com::volvo::ocp::test_service::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                payload
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TestServiceResponseClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.test_service.v1.TestServiceResponse";


    template <typename IpcPolicy>
    struct TestServiceResponseClientProxyWrapper final :
        public ::com::volvo::ocp::test_service::v1::TestServiceResponse,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
        lookupTestServiceResponseImplementation( std::shared_ptr<Policy>, const char * );

        explicit TestServiceResponseClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void pong( ::com::volvo::ocp::test_service::v1::PingStatus status ) override {
            getItsTransmitter()->pong( status );
        }

        void beefyMessageResponse(
                  ::com::volvo::ocp::test_service::v1::PingStatus  status,
            const ::com::volvo::ocp::test_service::v1::Payload    &payload
        ) override {
            getItsTransmitter()->beefyMessageResponse( status, payload );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::test_service::v1::TestServiceResponse>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct TestServiceResponseBroadcastListener final :
        public ::com::volvo::ocp::test_service::v1::TestServiceResponse,
        public IpcPolicy::Implementor {

        ~TestServiceResponseBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.test_service.v1.TestServiceResponse", this);
        }

        TestServiceResponseBroadcastListener( const TestServiceResponseBroadcastListener &)             = delete;
        TestServiceResponseBroadcastListener( TestServiceResponseBroadcastListener &&)                  = delete;
        TestServiceResponseBroadcastListener &operator=( const TestServiceResponseBroadcastListener & ) = delete;
        TestServiceResponseBroadcastListener &operator=( TestServiceResponseBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
        registerTestServiceResponseBroadcastListener(
            std::shared_ptr<Policy>                                                    theIpcPolicy,
            const char *                                                               theObjectPath,
            std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        TestServiceResponseBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void pong( ::com::volvo::ocp::test_service::v1::PingStatus status ) override {
            itsImplementation->pong(status);
        }

        static void pong( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceResponseBroadcastListener&>(*theThis);

            ::com::volvo::ocp::test_service::v1::PingStatus status;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::test_service::v1::PingStatus,
                    ::com::volvo::ocp::test_service::v1::IpcEnumValidate
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

        void beefyMessageResponse(
                  ::com::volvo::ocp::test_service::v1::PingStatus  status,
            const ::com::volvo::ocp::test_service::v1::Payload    &payload
        ) override {
            itsImplementation->beefyMessageResponse(status, payload);
        }

        static void beefyMessageResponse( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<TestServiceResponseBroadcastListener&>(*theThis);

            ::com::volvo::ocp::test_service::v1::PingStatus status;
            ::com::volvo::ocp::test_service::v1::Payload    payload;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::test_service::v1::PingStatus,
                    ::com::volvo::ocp::test_service::v1::IpcEnumValidate
                >(status, theErrorString )
            );
            ::com::volvo::ocp::test_service::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                payload
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.beefyMessageResponse(
                status,
                payload
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct TestServiceResponseBroadcastProxy final : public ::com::volvo::ocp::test_service::v1::TestServiceResponse {

        TestServiceResponseBroadcastProxy( const TestServiceResponseBroadcastProxy &)             = delete;
        TestServiceResponseBroadcastProxy( TestServiceResponseBroadcastProxy &&)                  = delete;
        TestServiceResponseBroadcastProxy &operator=( const TestServiceResponseBroadcastProxy & ) = delete;
        TestServiceResponseBroadcastProxy &operator=( TestServiceResponseBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
        getTestServiceResponseBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        TestServiceResponseBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void pong( ::com::volvo::ocp::test_service::v1::PingStatus status ) override {
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

        void beefyMessageResponse(
                  ::com::volvo::ocp::test_service::v1::PingStatus  status,
            const ::com::volvo::ocp::test_service::v1::Payload    &payload
        ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "beefyMessageResponse"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(status)
            );
            ::com::volvo::ocp::test_service::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                payload
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char TestServiceResponseBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.test_service.v1.TestServiceResponse";

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICEREQUEST_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    registerTestServiceRequestImplementation(
        std::shared_ptr<IpcPolicy>                                               theIpcPolicy,
        const char*                                                              theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> theImplementation
    ) 
    {
        using ImplementationProxy = TestServiceRequestImplementationProxy<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.test_service.v1.TestServiceRequest", theProxy )
            .template addMethod< void, const char *, std::uint64_t                                                        >( "ping",         ImplementationProxy::ping )
            .template addMethod< void, const char *, std::uint64_t, ::com::volvo::ocp::test_service::v1::Payload, Boolean >( "beefyMessage", ImplementationProxy::beefyMessage )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::test_service::v1::TestServiceRequest using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    lookupTestServiceRequestImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<TestServiceRequestClientProxyWrapper<IpcPolicy>>(
            new TestServiceRequestClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<TestServiceRequestClientProxy<IpcPolicy>>(
                    new TestServiceRequestClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::test_service::v1::TestServiceRequest>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, TestServiceRequestClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    registerTestServiceRequestBroadcastListener(
        std::shared_ptr<IpcPolicy>                                               theIpcPolicy,
        const char*                                                              theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest> theImplementation
    ) 
    {
        using ImplementationProxy = TestServiceRequestBroadcastListener<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.volvo.ocp.test_service.v1.TestServiceRequest", theProxy )
            .template addSignal< const char *, std::uint64_t                                                        >( "ping",         ImplementationProxy::ping )
            .template addSignal< const char *, std::uint64_t, ::com::volvo::ocp::test_service::v1::Payload, Boolean >( "beefyMessage", ImplementationProxy::beefyMessage )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::volvo::ocp::test_service::v1::TestServiceRequest interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceRequest can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceRequest>
    getTestServiceRequestBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<TestServiceRequest>(new TestServiceRequestBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__TEST_SERVICE__V1__TESTSERVICERESPONSE_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace test_service { namespace v1 { 
#else
namespace com::volvo::ocp::test_service::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    registerTestServiceResponseImplementation(
        std::shared_ptr<IpcPolicy>                                                theIpcPolicy,
        const char*                                                               theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> theImplementation
    ) 
    {
        using ImplementationProxy = TestServiceResponseImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.test_service.v1.TestServiceResponse", theProxy )
            .template addMethod< void, std::uint8_t                                               >( "pong",                 ImplementationProxy::pong )
            .template addMethod< void, std::uint8_t, ::com::volvo::ocp::test_service::v1::Payload >( "beefyMessageResponse", ImplementationProxy::beefyMessageResponse )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::test_service::v1::TestServiceResponse using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    lookupTestServiceResponseImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<TestServiceResponseClientProxyWrapper<IpcPolicy>>(
            new TestServiceResponseClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<TestServiceResponseClientProxy<IpcPolicy>>(
                    new TestServiceResponseClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::test_service::v1::TestServiceResponse>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, TestServiceResponseClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    registerTestServiceResponseBroadcastListener(
        std::shared_ptr<IpcPolicy>                                                theIpcPolicy,
        const char*                                                               theObjectPath,
        std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse> theImplementation
    ) 
    {
        using ImplementationProxy = TestServiceResponseBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.volvo.ocp.test_service.v1.TestServiceResponse", theProxy )
            .template addSignal< std::uint8_t                                               >( "pong",                 ImplementationProxy::pong )
            .template addSignal< std::uint8_t, ::com::volvo::ocp::test_service::v1::Payload >( "beefyMessageResponse", ImplementationProxy::beefyMessageResponse )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::volvo::ocp::test_service::v1::TestServiceResponse interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::test_service::v1::TestServiceResponse can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::test_service::v1::TestServiceResponse>
    getTestServiceResponseBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<TestServiceResponse>(new TestServiceResponseBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#endif
