
#ifndef __TESTS_REFERENCE_OUTPUT_DEVICE_STATUS_IPC_H__
#define __TESTS_REFERENCE_OUTPUT_DEVICE_STATUS_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "tests/headers/device_status.h"

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_DECLARATIONS__

namespace com::example::device::v1 {

    // Registers an implementation of the ::com::example::device::v1::DeviceStatus interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatus>
    registerDeviceStatusImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatus> theImplementation
    );

    // Looks up a remote implementation of ::com::example::device::v1::DeviceStatus using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatus>
    lookupDeviceStatusImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_DECLARATIONS__

namespace com::example::device::v1 {

    // Registers an implementation of the ::com::example::device::v1::DeviceStatusUpdate interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    registerDeviceStatusUpdateImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> theImplementation
    );

    // Looks up a remote implementation of ::com::example::device::v1::DeviceStatusUpdate using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    lookupDeviceStatusUpdateImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::example::device::v1::DeviceStatusUpdate interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    registerDeviceStatusUpdateBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> theImplementation
    );

    // Creates a proxy implementing the ::com::example::device::v1::DeviceStatusUpdate interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    getDeviceStatusUpdateBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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
#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__DEVICE__V1__CONNECTIONSTATE_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__DEVICE__V1__CONNECTIONSTATE_IPC_DECLARATIONS__

namespace com::example::device::v1 {

    void IpcEnumValidate( ConnectionState &theTarget, ConnectionState theValue, std::string &theErrorString ) __attribute__((weak));

}


#endif

#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__DEVICE__V1__CONNECTIONSTATE_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__DEVICE__V1__CONNECTIONSTATE_IPC_IMPLEMENTATIONS__

namespace com::example::device::v1 {

    void IpcEnumValidate( ConnectionState &theTarget, ConnectionState theValue, std::string &theErrorString )  {
        switch (theValue) {
        case ConnectionState::Disconnected:
        case ConnectionState::Connecting:
        case ConnectionState::Connected:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::example::device::v1::ConnectionState");
    }

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_STUBS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_STUBS__

namespace com::example::device::v1 {

    template <typename IpcPolicy>
    struct DeviceStatusImplementationProxy final :
        public ::com::example::device::v1::DeviceStatus,
        public IpcPolicy::Implementor {

        ~DeviceStatusImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.device.v1.DeviceStatus", this);
        }

        DeviceStatusImplementationProxy( const DeviceStatusImplementationProxy &)             = delete;
        DeviceStatusImplementationProxy( DeviceStatusImplementationProxy &&)                  = delete;
        DeviceStatusImplementationProxy &operator=( const DeviceStatusImplementationProxy & ) = delete;
        DeviceStatusImplementationProxy &operator=( DeviceStatusImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::device::v1::DeviceStatus>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatus>
        registerDeviceStatusImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::device::v1::DeviceStatus>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        DeviceStatusImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        ::com::example::device::v1::ConnectionState getState(  ) override {
            return itsImplementation->getState();
        }

        static void getState( ImplementorPtr theThis, Message &, Message &theReturnValue ) {
            auto &theProxy = dynamic_cast<DeviceStatusImplementationProxy&>(*theThis);

            IpcPolicy::appendMessageArguments(
                theReturnValue,
                static_cast<std::uint8_t>(theProxy.getState())
            );

        }

    };

    template <typename IpcPolicy>
    struct DeviceStatusClientProxy final : public ::com::example::device::v1::DeviceStatus {

        DeviceStatusClientProxy( const DeviceStatusClientProxy &)             = delete;
        DeviceStatusClientProxy( DeviceStatusClientProxy &&)                  = delete;
        DeviceStatusClientProxy &operator=( const DeviceStatusClientProxy & ) = delete;
        DeviceStatusClientProxy &operator=( DeviceStatusClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatus>
        lookupDeviceStatusImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        DeviceStatusClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        ::com::example::device::v1::ConnectionState getState(  ) override {
            ::com::example::device::v1::ConnectionState theIpcReturnValue;
            Message     theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "getState"
                );

            auto theMessageReturnValue = itsIpcPolicy->sendMessage( theIpcMessage );

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theMessageReturnValue,
                &babel::ipc::EnumReference<
                    ::com::example::device::v1::ConnectionState,
                    ::com::example::device::v1::IpcEnumValidate
                >(theIpcReturnValue, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            return theIpcReturnValue;
        }

    };

    template <typename IpcPolicy>
    const char DeviceStatusClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.device.v1.DeviceStatus";


    template <typename IpcPolicy>
    struct DeviceStatusClientProxyWrapper final :
        public ::com::example::device::v1::DeviceStatus,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::device::v1::DeviceStatus> itsTransmitter;
        std::weak_ptr<::com::example::device::v1::DeviceStatus>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatus>
        lookupDeviceStatusImplementation( std::shared_ptr<Policy>, const char * );

        explicit DeviceStatusClientProxyWrapper( const std::shared_ptr<::com::example::device::v1::DeviceStatus> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        ::com::example::device::v1::ConnectionState getState(  ) override {
            return getItsTransmitter()->getState(  );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::device::v1::DeviceStatus>(theImplementor);
        }

    };

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_STUBS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_STUBS__

namespace com::example::device::v1 {

    template <typename IpcPolicy>
    struct DeviceStatusUpdateImplementationProxy final :
        public ::com::example::device::v1::DeviceStatusUpdate,
        public IpcPolicy::Implementor {

        ~DeviceStatusUpdateImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.device.v1.DeviceStatus", this);
        }

        DeviceStatusUpdateImplementationProxy( const DeviceStatusUpdateImplementationProxy &)             = delete;
        DeviceStatusUpdateImplementationProxy( DeviceStatusUpdateImplementationProxy &&)                  = delete;
        DeviceStatusUpdateImplementationProxy &operator=( const DeviceStatusUpdateImplementationProxy & ) = delete;
        DeviceStatusUpdateImplementationProxy &operator=( DeviceStatusUpdateImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
        registerDeviceStatusUpdateImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        DeviceStatusUpdateImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void stateChanged( const ::com::example::device::v1::ConnectionState state ) override {
            itsImplementation->stateChanged(state);
        }

        static void stateChanged( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<DeviceStatusUpdateImplementationProxy&>(*theThis);

            ::com::example::device::v1::ConnectionState state;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::device::v1::ConnectionState,
                    ::com::example::device::v1::IpcEnumValidate
                >(state, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.stateChanged(
                state
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct DeviceStatusUpdateClientProxy final : public ::com::example::device::v1::DeviceStatusUpdate {

        DeviceStatusUpdateClientProxy( const DeviceStatusUpdateClientProxy &)             = delete;
        DeviceStatusUpdateClientProxy( DeviceStatusUpdateClientProxy &&)                  = delete;
        DeviceStatusUpdateClientProxy &operator=( const DeviceStatusUpdateClientProxy & ) = delete;
        DeviceStatusUpdateClientProxy &operator=( DeviceStatusUpdateClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
        lookupDeviceStatusUpdateImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        DeviceStatusUpdateClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void stateChanged( const ::com::example::device::v1::ConnectionState state ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "stateChanged"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(state)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char DeviceStatusUpdateClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.device.v1.DeviceStatus";


    template <typename IpcPolicy>
    struct DeviceStatusUpdateClientProxyWrapper final :
        public ::com::example::device::v1::DeviceStatusUpdate,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> itsTransmitter;
        std::weak_ptr<::com::example::device::v1::DeviceStatusUpdate>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
        lookupDeviceStatusUpdateImplementation( std::shared_ptr<Policy>, const char * );

        explicit DeviceStatusUpdateClientProxyWrapper( const std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void stateChanged( const ::com::example::device::v1::ConnectionState state ) override {
            getItsTransmitter()->stateChanged( state );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::device::v1::DeviceStatusUpdate>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct DeviceStatusUpdateBroadcastListener final :
        public ::com::example::device::v1::DeviceStatusUpdate,
        public IpcPolicy::Implementor {

        ~DeviceStatusUpdateBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.device.v1.DeviceStatus", this);
        }

        DeviceStatusUpdateBroadcastListener( const DeviceStatusUpdateBroadcastListener &)             = delete;
        DeviceStatusUpdateBroadcastListener( DeviceStatusUpdateBroadcastListener &&)                  = delete;
        DeviceStatusUpdateBroadcastListener &operator=( const DeviceStatusUpdateBroadcastListener & ) = delete;
        DeviceStatusUpdateBroadcastListener &operator=( DeviceStatusUpdateBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
        registerDeviceStatusUpdateBroadcastListener(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        DeviceStatusUpdateBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void stateChanged( const ::com::example::device::v1::ConnectionState state ) override {
            itsImplementation->stateChanged(state);
        }

        static void stateChanged( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<DeviceStatusUpdateBroadcastListener&>(*theThis);

            ::com::example::device::v1::ConnectionState state;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::device::v1::ConnectionState,
                    ::com::example::device::v1::IpcEnumValidate
                >(state, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.stateChanged(
                state
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct DeviceStatusUpdateBroadcastProxy final : public ::com::example::device::v1::DeviceStatusUpdate {

        DeviceStatusUpdateBroadcastProxy( const DeviceStatusUpdateBroadcastProxy &)             = delete;
        DeviceStatusUpdateBroadcastProxy( DeviceStatusUpdateBroadcastProxy &&)                  = delete;
        DeviceStatusUpdateBroadcastProxy &operator=( const DeviceStatusUpdateBroadcastProxy & ) = delete;
        DeviceStatusUpdateBroadcastProxy &operator=( DeviceStatusUpdateBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
        getDeviceStatusUpdateBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        DeviceStatusUpdateBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void stateChanged( const ::com::example::device::v1::ConnectionState state ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "stateChanged"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(state)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char DeviceStatusUpdateBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.example.device.v1.DeviceStatus";

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUS_IMPLEMENTATIONS__

namespace com::example::device::v1 {

    // Registers an implementation of the ::com::example::device::v1::DeviceStatus interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatus>
    registerDeviceStatusImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatus> theImplementation
    ) 
    {
        using ImplementationProxy = DeviceStatusImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.device.v1.DeviceStatus", theProxy )
            .template addMethod< std::uint8_t, void >( "getState", ImplementationProxy::getState )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::device::v1::DeviceStatus using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatus>
    lookupDeviceStatusImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<DeviceStatusClientProxyWrapper<IpcPolicy>>(
            new DeviceStatusClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<DeviceStatusClientProxy<IpcPolicy>>(
                    new DeviceStatusClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::device::v1::DeviceStatus>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, DeviceStatusClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }

}


#endif

#ifndef __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__DEVICE__V1__DEVICESTATUSUPDATE_IMPLEMENTATIONS__

namespace com::example::device::v1 {

    // Registers an implementation of the ::com::example::device::v1::DeviceStatusUpdate interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    registerDeviceStatusUpdateImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> theImplementation
    ) 
    {
        using ImplementationProxy = DeviceStatusUpdateImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.device.v1.DeviceStatus", theProxy )
            .template addMethod< void, std::uint8_t >( "stateChanged", ImplementationProxy::stateChanged )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::device::v1::DeviceStatusUpdate using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    lookupDeviceStatusUpdateImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<DeviceStatusUpdateClientProxyWrapper<IpcPolicy>>(
            new DeviceStatusUpdateClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<DeviceStatusUpdateClientProxy<IpcPolicy>>(
                    new DeviceStatusUpdateClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::device::v1::DeviceStatusUpdate>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, DeviceStatusUpdateClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::example::device::v1::DeviceStatusUpdate interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    registerDeviceStatusUpdateBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate> theImplementation
    ) 
    {
        using ImplementationProxy = DeviceStatusUpdateBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.example.device.v1.DeviceStatus", theProxy )
            .template addSignal< std::uint8_t >( "stateChanged", ImplementationProxy::stateChanged )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::example::device::v1::DeviceStatusUpdate interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::device::v1::DeviceStatusUpdate can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::device::v1::DeviceStatusUpdate>
    getDeviceStatusUpdateBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<DeviceStatusUpdate>(new DeviceStatusUpdateBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

}


#endif

#endif
