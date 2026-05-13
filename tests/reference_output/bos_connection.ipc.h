
#ifndef ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_BOS_CONNECTION_IPC_H__
#define ___HOME_CALLE_TMP_RELEASE_REPOS_APP_MESSAGE_HANDLER_GEN_FILES_BOS_CONNECTION_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "/home/calle/tmp/release/repos/app-message-handler/include/ocp/ipc/message_handler/bos_connection.h"


#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnection interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
    registerBOSConnectionImplementation(
        std::shared_ptr<IpcPolicy>                                             theIpcPolicy,
        const char*                                                            theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::BOSConnection using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
    lookupBOSConnectionImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_DECLARATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    registerBOSConnectionUpdateImplementation(
        std::shared_ptr<IpcPolicy>                                                   theIpcPolicy,
        const char*                                                                  theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> theImplementation
    );

    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    lookupBOSConnectionUpdateImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    registerBOSConnectionUpdateBroadcastListener(
        std::shared_ptr<IpcPolicy>                                                   theIpcPolicy,
        const char*                                                                  theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> theImplementation
    );

    // Creates a proxy implementing the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    getBOSConnectionUpdateBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__MESSAGE_HANDLER__V1__CONNECTIONCLASS_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__MESSAGE_HANDLER__V1__CONNECTIONCLASS_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    void IpcEnumValidate( ConnectionClass &theTarget, ConnectionClass theValue, std::string &theErrorString ) __attribute__((weak));


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____COM__VOLVO__OCP__MESSAGE_HANDLER__V1__CONNECTIONCLASS_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____COM__VOLVO__OCP__MESSAGE_HANDLER__V1__CONNECTIONCLASS_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    void IpcEnumValidate( ConnectionClass &theTarget, ConnectionClass theValue, std::string &theErrorString )  {
        switch (theValue) {
        case ConnectionClass::NoConnection:
        case ConnectionClass::Fallback:
        case ConnectionClass::Preferred:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::volvo::ocp::message_handler::v1::ConnectionClass");
    }


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_STUBS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    template <typename IpcPolicy>
    struct BOSConnectionImplementationProxy final :
        public ::com::volvo::ocp::message_handler::v1::BOSConnection,
        public IpcPolicy::Implementor {

        ~BOSConnectionImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.message_handler.v1.BOSConnection", this);
        }

        BOSConnectionImplementationProxy( const BOSConnectionImplementationProxy &)             = delete;
        BOSConnectionImplementationProxy( BOSConnectionImplementationProxy &&)                  = delete;
        BOSConnectionImplementationProxy &operator=( const BOSConnectionImplementationProxy & ) = delete;
        BOSConnectionImplementationProxy &operator=( BOSConnectionImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
        registerBOSConnectionImplementation(
            std::shared_ptr<Policy>                                                 theIpcPolicy,
            const char *                                                            theObjectPath,
            std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        BOSConnectionImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        ::com::volvo::ocp::message_handler::v1::ConnectionClass getActiveClass() override {
            return itsImplementation->getActiveClass();
        }

        static void getActiveClass( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<BOSConnectionImplementationProxy&>(*theThis);




            IpcPolicy::appendMessageArguments(
                theReturnValue,
                static_cast<std::uint8_t>(theProxy.getActiveClass())
            );

        }

    };

    template <typename IpcPolicy>
    struct BOSConnectionClientProxy final : public ::com::volvo::ocp::message_handler::v1::BOSConnection {

        BOSConnectionClientProxy( const BOSConnectionClientProxy &)             = delete;
        BOSConnectionClientProxy( BOSConnectionClientProxy &&)                  = delete;
        BOSConnectionClientProxy &operator=( const BOSConnectionClientProxy & ) = delete;
        BOSConnectionClientProxy &operator=( BOSConnectionClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
        lookupBOSConnectionImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        BOSConnectionClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        ::com::volvo::ocp::message_handler::v1::ConnectionClass getActiveClass() override {
            ::com::volvo::ocp::message_handler::v1::ConnectionClass theIpcReturnValue;
            Message                                                 theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getActiveClass"
                );



            auto theMessageReturnValue = itsIpcPolicy->sendMessage( theIpcMessage );

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theMessageReturnValue,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::message_handler::v1::ConnectionClass,
                    ::com::volvo::ocp::message_handler::v1::IpcEnumValidate
                >(theIpcReturnValue, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            return theIpcReturnValue;
        }

    };

    template <typename IpcPolicy>
    const char BOSConnectionClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.message_handler.v1.BOSConnection";


    template <typename IpcPolicy>
    struct BOSConnectionClientProxyWrapper final :
        public ::com::volvo::ocp::message_handler::v1::BOSConnection,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
        lookupBOSConnectionImplementation( std::shared_ptr<Policy>, const char * );

        explicit BOSConnectionClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        ::com::volvo::ocp::message_handler::v1::ConnectionClass getActiveClass() override {
            return getItsTransmitter()->getActiveClass();
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::BOSConnection>(theImplementor);
        }

    };


#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_STUBS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_STUBS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    template <typename IpcPolicy>
    struct BOSConnectionUpdateImplementationProxy final :
        public ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate,
        public IpcPolicy::Implementor {

        ~BOSConnectionUpdateImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.message_handler.v1.BOSConnection", this);
        }

        BOSConnectionUpdateImplementationProxy( const BOSConnectionUpdateImplementationProxy &)             = delete;
        BOSConnectionUpdateImplementationProxy( BOSConnectionUpdateImplementationProxy &&)                  = delete;
        BOSConnectionUpdateImplementationProxy &operator=( const BOSConnectionUpdateImplementationProxy & ) = delete;
        BOSConnectionUpdateImplementationProxy &operator=( BOSConnectionUpdateImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
        registerBOSConnectionUpdateImplementation(
            std::shared_ptr<Policy>                                                       theIpcPolicy,
            const char *                                                                  theObjectPath,
            std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        BOSConnectionUpdateImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void activeBOSConnectionClass( const ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass ) override {
            itsImplementation->activeBOSConnectionClass(connectionClass);
        }

        static void activeBOSConnectionClass( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<BOSConnectionUpdateImplementationProxy&>(*theThis);

            ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::message_handler::v1::ConnectionClass,
                    ::com::volvo::ocp::message_handler::v1::IpcEnumValidate
                >(connectionClass, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.activeBOSConnectionClass(
                connectionClass
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct BOSConnectionUpdateClientProxy final : public ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate {

        BOSConnectionUpdateClientProxy( const BOSConnectionUpdateClientProxy &)             = delete;
        BOSConnectionUpdateClientProxy( BOSConnectionUpdateClientProxy &&)                  = delete;
        BOSConnectionUpdateClientProxy &operator=( const BOSConnectionUpdateClientProxy & ) = delete;
        BOSConnectionUpdateClientProxy &operator=( BOSConnectionUpdateClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
        lookupBOSConnectionUpdateImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        BOSConnectionUpdateClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void activeBOSConnectionClass( const ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "activeBOSConnectionClass"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(connectionClass)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char BOSConnectionUpdateClientProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.message_handler.v1.BOSConnection";


    template <typename IpcPolicy>
    struct BOSConnectionUpdateClientProxyWrapper final :
        public ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> itsTransmitter;
        std::weak_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
        lookupBOSConnectionUpdateImplementation( std::shared_ptr<Policy>, const char * );

        explicit BOSConnectionUpdateClientProxyWrapper( const std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void activeBOSConnectionClass( const ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass ) override {
            getItsTransmitter()->activeBOSConnectionClass( connectionClass );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct BOSConnectionUpdateBroadcastListener final :
        public ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate,
        public IpcPolicy::Implementor {

        ~BOSConnectionUpdateBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.volvo.ocp.message_handler.v1.BOSConnection", this);
        }

        BOSConnectionUpdateBroadcastListener( const BOSConnectionUpdateBroadcastListener &)             = delete;
        BOSConnectionUpdateBroadcastListener( BOSConnectionUpdateBroadcastListener &&)                  = delete;
        BOSConnectionUpdateBroadcastListener &operator=( const BOSConnectionUpdateBroadcastListener & ) = delete;
        BOSConnectionUpdateBroadcastListener &operator=( BOSConnectionUpdateBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
        registerBOSConnectionUpdateBroadcastListener(
            std::shared_ptr<Policy>                                                       theIpcPolicy,
            const char *                                                                  theObjectPath,
            std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        BOSConnectionUpdateBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void activeBOSConnectionClass( const ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass ) override {
            itsImplementation->activeBOSConnectionClass(connectionClass);
        }

        static void activeBOSConnectionClass( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<BOSConnectionUpdateBroadcastListener&>(*theThis);

            ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::volvo::ocp::message_handler::v1::ConnectionClass,
                    ::com::volvo::ocp::message_handler::v1::IpcEnumValidate
                >(connectionClass, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.activeBOSConnectionClass(
                connectionClass
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct BOSConnectionUpdateBroadcastProxy final : public ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate {

        BOSConnectionUpdateBroadcastProxy( const BOSConnectionUpdateBroadcastProxy &)             = delete;
        BOSConnectionUpdateBroadcastProxy( BOSConnectionUpdateBroadcastProxy &&)                  = delete;
        BOSConnectionUpdateBroadcastProxy &operator=( const BOSConnectionUpdateBroadcastProxy & ) = delete;
        BOSConnectionUpdateBroadcastProxy &operator=( BOSConnectionUpdateBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
        getBOSConnectionUpdateBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        BOSConnectionUpdateBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void activeBOSConnectionClass( const ::com::volvo::ocp::message_handler::v1::ConnectionClass connectionClass ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "activeBOSConnectionClass"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(connectionClass)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char BOSConnectionUpdateBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.volvo.ocp.message_handler.v1.BOSConnection";

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTION_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnection interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
    registerBOSConnectionImplementation(
        std::shared_ptr<IpcPolicy>                                             theIpcPolicy,
        const char*                                                            theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection> theImplementation
    ) 
    {
        using ImplementationProxy = BOSConnectionImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.message_handler.v1.BOSConnection", theProxy )
            .template addMethod< std::uint8_t, void >( "getActiveClass", ImplementationProxy::getActiveClass )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::BOSConnection using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnection>
    lookupBOSConnectionImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<BOSConnectionClientProxyWrapper<IpcPolicy>>(
            new BOSConnectionClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<BOSConnectionClientProxy<IpcPolicy>>(
                    new BOSConnectionClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::BOSConnection>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, BOSConnectionClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#ifndef __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_IMPLEMENTATIONS__
#define __HAVE___COM__VOLVO__OCP__MESSAGE_HANDLER__V1__BOSCONNECTIONUPDATE_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace com { namespace volvo { namespace ocp { namespace message_handler { namespace v1 { 
#else
namespace com::volvo::ocp::message_handler::v1 {
#endif

    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    registerBOSConnectionUpdateImplementation(
        std::shared_ptr<IpcPolicy>                                                   theIpcPolicy,
        const char*                                                                  theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> theImplementation
    ) 
    {
        using ImplementationProxy = BOSConnectionUpdateImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.volvo.ocp.message_handler.v1.BOSConnection", theProxy )
            .template addMethod< void, std::uint8_t >( "activeBOSConnectionClass", ImplementationProxy::activeBOSConnectionClass )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    lookupBOSConnectionUpdateImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<BOSConnectionUpdateClientProxyWrapper<IpcPolicy>>(
            new BOSConnectionUpdateClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<BOSConnectionUpdateClientProxy<IpcPolicy>>(
                    new BOSConnectionUpdateClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, BOSConnectionUpdateClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    registerBOSConnectionUpdateBroadcastListener(
        std::shared_ptr<IpcPolicy>                                                   theIpcPolicy,
        const char*                                                                  theObjectPath,
        std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate> theImplementation
    ) 
    {
        using ImplementationProxy = BOSConnectionUpdateBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.volvo.ocp.message_handler.v1.BOSConnection", theProxy )
            .template addSignal< std::uint8_t >( "activeBOSConnectionClass", ImplementationProxy::activeBOSConnectionClass )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::volvo::ocp::message_handler::v1::BOSConnectionUpdate>
    getBOSConnectionUpdateBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<BOSConnectionUpdate>(new BOSConnectionUpdateBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

#if __cplusplus < 201700L
}}}}}
#else
}
#endif


#endif

#endif
