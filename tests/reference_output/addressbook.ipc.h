
#ifndef ___TMP_BABELC_REF_ADDRESSBOOK_IPC_H__
#define ___TMP_BABELC_REF_ADDRESSBOOK_IPC_H__

#include <memory>
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <array>

#include "addressbook.h"


#ifndef __HAVE___ADDRESSBOOK__V1__SERVER_DECLARATIONS__
#define __HAVE___ADDRESSBOOK__V1__SERVER_DECLARATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    // Registers an implementation of the ::addressbook::v1::Server interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    registerServerImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::addressbook::v1::Server> theImplementation
    );

    // Looks up a remote implementation of ::addressbook::v1::Server using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    lookupServerImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );

    // Registers an implementation of the ::addressbook::v1::Server interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    registerServerBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::addressbook::v1::Server> theImplementation
    );

    // Creates a proxy implementing the ::addressbook::v1::Server interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    getServerBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath );


#if __cplusplus < 201700L
}}
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

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PHONENUMBERS_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PHONENUMBERS_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    template <typename Boolean,typename IpcPolicy>
    using PhoneNumbers_ArrayView = std::array<::addressbook::v1::PhoneNumber,1>;

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::addressbook::v1::PhoneNumbers &theVaryingLengthContainer );

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::addressbook::v1::PhoneNumbers &theVaryingLengthContainer );


#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__SEX_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__SEX_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    void IpcEnumValidate( Sex &theTarget, Sex theValue, std::string &theErrorString ) __attribute__((weak));


#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PERSON_IPC_DECLARATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PERSON_IPC_DECLARATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    template <typename Boolean,typename IpcPolicy>
    using Person_TupleView = std::tuple< 
            const char *,
            std::uint8_t,
            ::addressbook::v1::PhoneNumbers
        >;

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::addressbook::v1::Person &theStruct );

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::addressbook::v1::Person &theStruct );


#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PHONENUMBERS_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PHONENUMBERS_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::addressbook::v1::PhoneNumbers &theVaryingLengthContainer ) {
        const ::addressbook::v1::PhoneNumbers::value_type *theValues     = nullptr;
        ::addressbook::v1::PhoneNumbers::size_type         theNoOfValues = 0;

        IpcPolicy::getMessageArray( theMessage, theValues, theNoOfValues );

        theVaryingLengthContainer.assign( theValues, (theValues+theNoOfValues) );
    }
    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::addressbook::v1::PhoneNumbers &theVaryingLengthContainer ) {
        IpcPolicy::appendMessageArray(
            theMessage,
            &theVaryingLengthContainer.front(),
            theVaryingLengthContainer.size()
        );
    }

#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__SEX_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__SEX_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    void IpcEnumValidate( Sex &theTarget, Sex theValue, std::string &theErrorString )  {
        switch (theValue) {
        case Sex::Unknown:
        case Sex::Male:
        case Sex::Female:
        case Sex::Neither:
            theTarget = theValue;
            return;
        }
        if (!theErrorString.empty()) { theErrorString += ", "; };    theErrorString += (std::to_string(static_cast<std::uint8_t>(theValue)) + " not valid for ::addressbook::v1::Sex");
    }


#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PERSON_IPC_IMPLEMENTATIONS__
#define __HAVE_BABEL__IPC____ADDRESSBOOK__V1__PERSON_IPC_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcReadContainer( MessageT &&theMessage, ::addressbook::v1::Person &theStruct ) {
        typename IpcPolicy::template ReadContainerScope<::addressbook::v1::Person_TupleView<Boolean,IpcPolicy>> theContainer( theMessage, false );

        std::string theErrorString;

        IpcPolicy::getMessageArguments(
            theMessage,
            &babel::ipc::StringReference(theStruct.itsName),
            &babel::ipc::EnumReference<
                ::addressbook::v1::Sex,
                ::addressbook::v1::IpcEnumValidate
            >(theStruct.itsSex, theErrorString )
        );
        ::addressbook::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
            theMessage,
            theStruct.itsPhoneNumbers
        );

        if (!theErrorString.empty()) { throw std::invalid_argument( theErrorString ); };
    }
    template <class IpcPolicy, typename Boolean, typename MessageT>
    void IpcWriteContainer(  MessageT &&theMessage, const ::addressbook::v1::Person &theStruct ) {
        typename IpcPolicy::template WriteContainerScope<::addressbook::v1::Person_TupleView<Boolean,IpcPolicy>> theContainer( theMessage );

        IpcPolicy::appendMessageArguments(
            theMessage,
            theStruct.itsName.c_str(),
            static_cast<std::uint8_t>(theStruct.itsSex)
        );
        ::addressbook::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
            theMessage,
            theStruct.itsPhoneNumbers
        );

    }

#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE___ADDRESSBOOK__V1__SERVER_STUBS__
#define __HAVE___ADDRESSBOOK__V1__SERVER_STUBS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    template <typename IpcPolicy>
    struct ServerImplementationProxy final :
        public ::addressbook::v1::Server,
        public IpcPolicy::Implementor {

        ~ServerImplementationProxy() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "addressbook.v1.Server", this);
        }

        ServerImplementationProxy( const ServerImplementationProxy &)             = delete;
        ServerImplementationProxy( ServerImplementationProxy &&)                  = delete;
        ServerImplementationProxy &operator=( const ServerImplementationProxy & ) = delete;
        ServerImplementationProxy &operator=( ServerImplementationProxy && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::addressbook::v1::Server>;

        template <typename Policy>
        friend std::shared_ptr<::addressbook::v1::Server>
        registerServerImplementation(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::addressbook::v1::Server>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        ServerImplementationProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void add( const ::addressbook::v1::Person &thePerson ) override {
            itsImplementation->add(thePerson);
        }

        static void add( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<ServerImplementationProxy&>(*theThis);

            ::addressbook::v1::Person thePerson;

            ::addressbook::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                thePerson
            );

            theProxy.add(
                thePerson
            );
        }

    };

    template <typename IpcPolicy>
    struct ServerClientProxy final : public ::addressbook::v1::Server {

        ServerClientProxy( const ServerClientProxy &)             = delete;
        ServerClientProxy( ServerClientProxy &&)                  = delete;
        ServerClientProxy &operator=( const ServerClientProxy & ) = delete;
        ServerClientProxy &operator=( ServerClientProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::addressbook::v1::Server>
        lookupServerImplementation( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        ServerClientProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void add( const ::addressbook::v1::Person &thePerson ) override {
            Message theIpcMessage =
                itsIpcPolicy->createMethodMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "add"
                );

            ::addressbook::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                thePerson
            );

            (void)itsIpcPolicy->sendMessage( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char ServerClientProxy<IpcPolicy>::theInterfaceName[] = "addressbook.v1.Server";


    template <typename IpcPolicy>
    struct ServerClientProxyWrapper final :
        public ::addressbook::v1::Server,
        public IpcPolicy::Client {

    private:
        const std::shared_ptr<::addressbook::v1::Server> itsTransmitter;
        std::weak_ptr<::addressbook::v1::Server>         itsShortcut;

        auto getItsTransmitter() const {
            const auto theShortcut = itsShortcut.lock();
            return theShortcut ? theShortcut : itsTransmitter;
        }

        template <typename Policy>
        friend std::shared_ptr<::addressbook::v1::Server>
        lookupServerImplementation( std::shared_ptr<Policy>, const char * );

        explicit ServerClientProxyWrapper( const std::shared_ptr<::addressbook::v1::Server> theTransmitter )
            : itsTransmitter(theTransmitter),
              itsShortcut() {
        }

        void add( const ::addressbook::v1::Person &thePerson ) override {
            getItsTransmitter()->add( thePerson );
        }

        void implementorIsRegistered( const typename IpcPolicy::Implementor::SharedPtr &theImplementor ) override {
            itsShortcut = std::dynamic_pointer_cast<::addressbook::v1::Server>(theImplementor);
        }

    };

    template <typename IpcPolicy>
    struct ServerBroadcastListener final :
        public ::addressbook::v1::Server,
        public IpcPolicy::Implementor {

        ~ServerBroadcastListener() {
            itsIpcPolicy->deregisterImplementor( itsObjectPath.c_str(), "addressbook.v1.Server", this);
        }

        ServerBroadcastListener( const ServerBroadcastListener &)             = delete;
        ServerBroadcastListener( ServerBroadcastListener &&)                  = delete;
        ServerBroadcastListener &operator=( const ServerBroadcastListener & ) = delete;
        ServerBroadcastListener &operator=( ServerBroadcastListener && )      = delete;

    private:

        using IpcPolicyPtr    = std::shared_ptr<IpcPolicy>;
        using Implementor     = typename IpcPolicy::Implementor;
        using ImplementorPtr  = const typename Implementor::SharedPtr &;
        using Boolean         = typename IpcPolicy::Boolean;
        using Message         = typename IpcPolicy::Message;
        using InterfacePtr    = std::shared_ptr<::addressbook::v1::Server>;

        template <typename Policy>
        friend std::shared_ptr<::addressbook::v1::Server>
        registerServerBroadcastListener(
            std::shared_ptr<Policy>                     theIpcPolicy,
            const char *                                theObjectPath,
            std::shared_ptr<::addressbook::v1::Server>  theImplementation
        );

        IpcPolicyPtr      itsIpcPolicy;
        InterfacePtr      itsImplementation;
        const std::string itsObjectPath;

        ServerBroadcastListener( IpcPolicyPtr theIpcPolicy, const char *theObjectPath, InterfacePtr theImplementation )
        : itsIpcPolicy(theIpcPolicy), itsImplementation(theImplementation), itsObjectPath(theObjectPath) {
        }

        void add( const ::addressbook::v1::Person &thePerson ) override {
            itsImplementation->add(thePerson);
        }

        static void add( ImplementorPtr theThis, Message &theArguments, Message & ) {
            auto &theProxy = dynamic_cast<ServerBroadcastListener&>(*theThis);

            ::addressbook::v1::Person thePerson;

            ::addressbook::v1::IpcReadContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theArguments,
                thePerson
            );

            theProxy.add(
                thePerson
            );
        }

    };

    template <typename IpcPolicy>
    struct ServerBroadcastProxy final : public ::addressbook::v1::Server {

        ServerBroadcastProxy( const ServerBroadcastProxy &)             = delete;
        ServerBroadcastProxy( ServerBroadcastProxy &&)                  = delete;
        ServerBroadcastProxy &operator=( const ServerBroadcastProxy & ) = delete;
        ServerBroadcastProxy &operator=( ServerBroadcastProxy && )      = delete;

    private:
        static const char theInterfaceName[];

        using IpcPolicyPtr = std::shared_ptr<IpcPolicy>;
        using Boolean      = typename IpcPolicy::Boolean;
        using Message      = typename IpcPolicy::Message;

        template <typename Policy>
        friend std::shared_ptr<::addressbook::v1::Server>
        getServerBroadcastProxy( std::shared_ptr<Policy>, const char * );
        
        IpcPolicyPtr      itsIpcPolicy;
        const std::string itsObjectPath;
        
        ServerBroadcastProxy( IpcPolicyPtr theIpcPolicy, const char *theObjectPath )
            : itsIpcPolicy(theIpcPolicy),
              itsObjectPath(theObjectPath) {
        }

        void add( const ::addressbook::v1::Person &thePerson ) override {
            Message theIpcMessage =
                itsIpcPolicy->createSignalMessage(
                    itsObjectPath.c_str(),
                    theInterfaceName,
                    "add"
                );

            ::addressbook::v1::IpcWriteContainer<IpcPolicy, typename IpcPolicy::Boolean>(
                theIpcMessage,
                thePerson
            );

            (void)itsIpcPolicy->emitSignal( theIpcMessage );
        }

    };

    template <typename IpcPolicy>
    const char ServerBroadcastProxy<IpcPolicy>::theInterfaceName[] = "addressbook.v1.Server";

#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#ifndef __HAVE___ADDRESSBOOK__V1__SERVER_IMPLEMENTATIONS__
#define __HAVE___ADDRESSBOOK__V1__SERVER_IMPLEMENTATIONS__

#if __cplusplus < 201700L
namespace addressbook { namespace v1 { 
#else
namespace addressbook::v1 {
#endif

    // Registers an implementation of the ::addressbook::v1::Server interface at the passed IPC Policy.
    // All remote IPC calls will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    registerServerImplementation(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::addressbook::v1::Server> theImplementation
    ) 
    {
        using ImplementationProxy = ServerImplementationProxy<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerImplementor(theObjectPath, "addressbook.v1.Server", theProxy )
            .template addMethod< void, ::addressbook::v1::Person_TupleView<Boolean,IpcPolicy> >( "add", ImplementationProxy::add )
            .publish();

        return theProxy;
    }
    // Looks up a remote implementation of ::addressbook::v1::Server using the passed IPC Policy.
    // Returns a stub which will forward its calls to the remote implementation.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    lookupServerImplementation( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        const auto theProxy = std::shared_ptr<ServerClientProxyWrapper<IpcPolicy>>(
            new ServerClientProxyWrapper<IpcPolicy>( 
                std::shared_ptr<ServerClientProxy<IpcPolicy>>(
                    new ServerClientProxy<IpcPolicy>(theIpcPolicy,theObjectPath)
                )
            )
        );
        theProxy->itsShortcut = 
            std::dynamic_pointer_cast<::addressbook::v1::Server>(
                theIpcPolicy->registerClient( theProxy, theObjectPath, ServerClientProxy<IpcPolicy>::theInterfaceName )
            );
        return theProxy;
    }
    // Registers an implementation of the ::addressbook::v1::Server interface at the passed IPC Policy.
    // All broadcast IPC calls to the interface will be forwarded to the passed instance.
    // Returns a shared pointer to the "stub class" which fulfills the same interface. Calls to the
    // methods of the returned instance will also be forwarded to the implementation passed as second argument.
    // "Forgetting" the returned instance will deregister the implementation from the bus interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    registerServerBroadcastListener(
        std::shared_ptr<IpcPolicy>                 theIpcPolicy,
        const char*                                theObjectPath,
        std::shared_ptr<::addressbook::v1::Server> theImplementation
    ) 
    {
        using ImplementationProxy = ServerBroadcastListener<IpcPolicy>;
        using Boolean             = typename IpcPolicy::Boolean;

        auto theProxy = std::shared_ptr<ImplementationProxy>(
            new ImplementationProxy(theIpcPolicy, theObjectPath, theImplementation)
        );

        theIpcPolicy->registerListener(theObjectPath, "addressbook.v1.Server", theProxy )
            .template addSignal< ::addressbook::v1::Person_TupleView<Boolean,IpcPolicy> >( "add", ImplementationProxy::add )
            .publish();

        return theProxy;
    }
    // Creates a proxy implementing the ::addressbook::v1::Server interface using the passed IPC Policy.
    // The proxy could be used to broadcast messages from the given interface.
    //
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    // * ::addressbook::v1::Server can be registered both as a broadcast 
    // * and a call interface since none of its methods has a return value.
    // * Be sure to use the correct register functions for both client and server!
    // ***** WARNING *** WARNING *** WARNING *** WARNING *** WARNING **********
    //
    template <typename IpcPolicy>
    std::shared_ptr<::addressbook::v1::Server>
    getServerBroadcastProxy( std::shared_ptr<IpcPolicy> theIpcPolicy, const char *theObjectPath ) 
    {
        return std::shared_ptr<Server>(new ServerBroadcastProxy<IpcPolicy>(theIpcPolicy,theObjectPath));
    }

#if __cplusplus < 201700L
}}
#else
}
#endif


#endif

#endif
