
#ifndef __TESTS_REFERENCE_OUTPUT_COUNTER_IPC_H__
#define __TESTS_REFERENCE_OUTPUT_COUNTER_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "tests/headers/counter.h"

#ifndef __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_DECLARATIONS__
#define __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_DECLARATIONS__

namespace com::example::metrics::v1 {

    // Registers an implementation of the ::com::example::metrics::v1::CounterService interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    registerCounterServiceImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::metrics::v1::CounterService> theImplementation
    );

    // Looks up a remote implementation of ::com::example::metrics::v1::CounterService using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    lookupCounterServiceImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::com::example::metrics::v1::CounterService interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    registerCounterServiceBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::metrics::v1::CounterService> theImplementation
    );

    // Creates a proxy implementing the ::com::example::metrics::v1::CounterService interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    getCounterServiceBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


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
#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__METRICS__V1__COUNTER_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__METRICS__V1__COUNTER_IPC_DECLARATIONS__

namespace com::example::metrics::v1 {

    void IpcEnumValidate( Counter &theTarget, Counter theValue, std::string &theErrorString ) __attribute__((weak));

}


#endif

#ifndef __HAVE_BABEL__IPC__COM__EXAMPLE__METRICS__V1__COUNTER_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC__COM__EXAMPLE__METRICS__V1__COUNTER_IPC_IMPLEMENTATIONS__

namespace com::example::metrics::v1 {

    void IpcEnumValidate( Counter &theTarget, Counter theValue, std::string &theErrorString )  {
        switch (theValue) {
        case Counter::primary:
        case Counter::secondary:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::com::example::metrics::v1::Counter");
    }

}


#endif

#ifndef __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_STUBS__
#define __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_STUBS__

namespace com::example::metrics::v1 {

    template <typename IpcPolicy>
    struct CounterServiceImplementationProxy final :
        public ::com::example::metrics::v1::CounterService,
        public IpcPolicy::Implementor {

        ~CounterServiceImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.metrics.v1.CounterService", this);
        }

        CounterServiceImplementationProxy( const CounterServiceImplementationProxy &)             = delete;
        CounterServiceImplementationProxy( CounterServiceImplementationProxy &&)                  = delete;
        CounterServiceImplementationProxy &operator=( const CounterServiceImplementationProxy & ) = delete;
        CounterServiceImplementationProxy &operator=( CounterServiceImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::metrics::v1::CounterService>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::metrics::v1::CounterService>
        registerCounterServiceImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::metrics::v1::CounterService>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        CounterServiceImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void reset( ::com::example::metrics::v1::Counter counter ) override {
            itsImplementation->reset(counter);
        }

        static void reset( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<CounterServiceImplementationProxy&>(*theThis);

            ::com::example::metrics::v1::Counter counter;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::metrics::v1::Counter,
                    ::com::example::metrics::v1::IpcEnumValidate
                >(counter, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.reset(
                counter
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct CounterServiceClientProxy final : public ::com::example::metrics::v1::CounterService {

        CounterServiceClientProxy( const CounterServiceClientProxy &)             = delete;
        CounterServiceClientProxy( CounterServiceClientProxy &&)                  = delete;
        CounterServiceClientProxy &operator=( const CounterServiceClientProxy & ) = delete;
        CounterServiceClientProxy &operator=( CounterServiceClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::metrics::v1::CounterService>
        lookupCounterServiceImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        CounterServiceClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void reset( ::com::example::metrics::v1::Counter counter ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "reset"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(counter)
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char CounterServiceClientProxy<IpcPolicy>::theInterfaceName[] = "com.example.metrics.v1.CounterService";


    template <typename IpcPolicy>
    struct CounterServiceClientProxyWrapper final :
        public ::com::example::metrics::v1::CounterService,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::com::example::metrics::v1::CounterService> itsTransmitter;
        std::weak_ptr<::com::example::metrics::v1::CounterService>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::com::example::metrics::v1::CounterService>
        lookupCounterServiceImplementation( std::shared_ptr<Policy>, const char * );

        explicit CounterServiceClientProxyWrapper( const std::shared_ptr<::com::example::metrics::v1::CounterService> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void reset( ::com::example::metrics::v1::Counter counter ) override {
            getItsTransmitter()->reset( counter );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::com::example::metrics::v1::CounterService>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct CounterServiceBroadcastListener final :
        public ::com::example::metrics::v1::CounterService,
        public IpcPolicy::Implementor {

        ~CounterServiceBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "com.example.metrics.v1.CounterService", this);
        }

        CounterServiceBroadcastListener( const CounterServiceBroadcastListener &)             = delete;
        CounterServiceBroadcastListener( CounterServiceBroadcastListener &&)                  = delete;
        CounterServiceBroadcastListener &operator=( const CounterServiceBroadcastListener & ) = delete;
        CounterServiceBroadcastListener &operator=( CounterServiceBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::com::example::metrics::v1::CounterService>;

        template <typename Policy>
        friend std::shared_ptr<::com::example::metrics::v1::CounterService>
        registerCounterServiceBroadcastListener(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::com::example::metrics::v1::CounterService>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        CounterServiceBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void reset( ::com::example::metrics::v1::Counter counter ) override {
            itsImplementation->reset(counter);
        }

        static void reset( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<CounterServiceBroadcastListener&>(*theThis);

            ::com::example::metrics::v1::Counter counter;

            std::string theErrorString;

            IpcPolicy::getMessageArguments(
                theArguments,
                &babel::ipc::EnumReference<
                    ::com::example::metrics::v1::Counter,
                    ::com::example::metrics::v1::IpcEnumValidate
                >(counter, theErrorString )
            );

            if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            theProxy.reset(
                counter
            );
            #pragma GCC diagnostic pop
        }

    };

    template <typename IpcPolicy>
    struct CounterServiceBroadcastProxy final : public ::com::example::metrics::v1::CounterService {

        CounterServiceBroadcastProxy( const CounterServiceBroadcastProxy &)             = delete;
        CounterServiceBroadcastProxy( CounterServiceBroadcastProxy &&)                  = delete;
        CounterServiceBroadcastProxy &operator=( const CounterServiceBroadcastProxy & ) = delete;
        CounterServiceBroadcastProxy &operator=( CounterServiceBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::com::example::metrics::v1::CounterService>
        getCounterServiceBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        CounterServiceBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void reset( ::com::example::metrics::v1::Counter counter ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "reset"
                );

            IpcPolicy::appendMessageArguments(
                theIpcMessage,
                static_cast<std::uint8_t>(counter)
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char CounterServiceBroadcastProxy<IpcPolicy>::theInterfaceName[] = "com.example.metrics.v1.CounterService";

}


#endif

#ifndef __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_IMPLEMENTATIONS__
#define __HAVE__COM__EXAMPLE__METRICS__V1__COUNTERSERVICE_IMPLEMENTATIONS__

namespace com::example::metrics::v1 {

    // Registers an implementation of the ::com::example::metrics::v1::CounterService interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    registerCounterServiceImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::metrics::v1::CounterService> theImplementation
    ) 
    {
        using ImplementationProxy = CounterServiceImplementationProxy<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "com.example.metrics.v1.CounterService", theProxy )
            .template addMethod< void, std::uint8_t >( "reset", ImplementationProxy::reset )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::com::example::metrics::v1::CounterService using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    lookupCounterServiceImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<CounterServiceClientProxyWrapper<IpcPolicy>>(
            new CounterServiceClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<CounterServiceClientProxy<IpcPolicy>>(
                    new CounterServiceClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::com::example::metrics::v1::CounterService>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, CounterServiceClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::com::example::metrics::v1::CounterService interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    registerCounterServiceBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::com::example::metrics::v1::CounterService> theImplementation
    ) 
    {
        using ImplementationProxy = CounterServiceBroadcastListener<IpcPolicy>;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "com.example.metrics.v1.CounterService", theProxy )
            .template addSignal< std::uint8_t >( "reset", ImplementationProxy::reset )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::com::example::metrics::v1::CounterService interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::com::example::metrics::v1::CounterService can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::com::example::metrics::v1::CounterService>
    getCounterServiceBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<CounterService>(new CounterServiceBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

}


#endif

#endif
