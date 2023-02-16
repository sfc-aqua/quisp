//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/contract/ipv6/Ipv6SocketCommand.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Ipv6SocketCommand_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Enum(inet::Ipv6CommandCode, (inet::Ipv6CommandCode::IPv6_C_BIND, inet::Ipv6CommandCode::IPv6_C_CONNECT, inet::Ipv6CommandCode::IPv6_C_CLOSE, inet::Ipv6CommandCode::IPv6_C_DESTROY));

Register_Enum(inet::Ipv6StatusInd, (inet::Ipv6StatusInd::IPv6_I_DATA, inet::Ipv6StatusInd::IPv6_I_SOCKET_CLOSED));

Register_Class(Ipv6SocketCommandBase)

Ipv6SocketCommandBase::Ipv6SocketCommandBase() : ::omnetpp::cObject()
{
}

Ipv6SocketCommandBase::Ipv6SocketCommandBase(const Ipv6SocketCommandBase& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6SocketCommandBase::~Ipv6SocketCommandBase()
{
}

Ipv6SocketCommandBase& Ipv6SocketCommandBase::operator=(const Ipv6SocketCommandBase& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketCommandBase::copy(const Ipv6SocketCommandBase& other)
{
}

void Ipv6SocketCommandBase::parsimPack(omnetpp::cCommBuffer *b) const
{
}

void Ipv6SocketCommandBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
}

class Ipv6SocketCommandBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6SocketCommandBaseDescriptor();
    virtual ~Ipv6SocketCommandBaseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketCommandBaseDescriptor)

Ipv6SocketCommandBaseDescriptor::Ipv6SocketCommandBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketCommandBase)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv6SocketCommandBaseDescriptor::~Ipv6SocketCommandBaseDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketCommandBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketCommandBase *>(obj)!=nullptr;
}

const char **Ipv6SocketCommandBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketCommandBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketCommandBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6SocketCommandBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6SocketCommandBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6SocketCommandBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketCommandBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6SocketCommandBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketCommandBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketCommandBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketCommandBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketCommandBase'", field);
    }
}

const char *Ipv6SocketCommandBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6SocketCommandBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6SocketCommandBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCommandBase'", field);
    }
}

omnetpp::cValue Ipv6SocketCommandBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketCommandBase' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketCommandBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCommandBase'", field);
    }
}

const char *Ipv6SocketCommandBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6SocketCommandBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketCommandBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCommandBase *pp = omnetpp::fromAnyPtr<Ipv6SocketCommandBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCommandBase'", field);
    }
}

Register_Class(Ipv6SocketBindCommand)

Ipv6SocketBindCommand::Ipv6SocketBindCommand() : ::inet::Ipv6SocketCommandBase()
{
}

Ipv6SocketBindCommand::Ipv6SocketBindCommand(const Ipv6SocketBindCommand& other) : ::inet::Ipv6SocketCommandBase(other)
{
    copy(other);
}

Ipv6SocketBindCommand::~Ipv6SocketBindCommand()
{
}

Ipv6SocketBindCommand& Ipv6SocketBindCommand::operator=(const Ipv6SocketBindCommand& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6SocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketBindCommand::copy(const Ipv6SocketBindCommand& other)
{
    this->protocol = other.protocol;
    this->localAddress = other.localAddress;
}

void Ipv6SocketBindCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6SocketCommandBase::parsimPack(b);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->localAddress);
}

void Ipv6SocketBindCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6SocketCommandBase::parsimUnpack(b);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->localAddress);
}

const Protocol * Ipv6SocketBindCommand::getProtocol() const
{
    return this->protocol;
}

void Ipv6SocketBindCommand::setProtocol(const Protocol * protocol)
{
    this->protocol = protocol;
}

const Ipv6Address& Ipv6SocketBindCommand::getLocalAddress() const
{
    return this->localAddress;
}

void Ipv6SocketBindCommand::setLocalAddress(const Ipv6Address& localAddress)
{
    this->localAddress = localAddress;
}

class Ipv6SocketBindCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_protocol,
        FIELD_localAddress,
    };
  public:
    Ipv6SocketBindCommandDescriptor();
    virtual ~Ipv6SocketBindCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketBindCommandDescriptor)

Ipv6SocketBindCommandDescriptor::Ipv6SocketBindCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketBindCommand)), "inet::Ipv6SocketCommandBase")
{
    propertyNames = nullptr;
}

Ipv6SocketBindCommandDescriptor::~Ipv6SocketBindCommandDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketBindCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketBindCommand *>(obj)!=nullptr;
}

const char **Ipv6SocketBindCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketBindCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketBindCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv6SocketBindCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_protocol
        0,    // FIELD_localAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6SocketBindCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "protocol",
        "localAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6SocketBindCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "protocol") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "localAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketBindCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Protocol",    // FIELD_protocol
        "inet::Ipv6Address",    // FIELD_localAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6SocketBindCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketBindCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketBindCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketBindCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketBindCommand'", field);
    }
}

const char *Ipv6SocketBindCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: { const Protocol * value = pp->getProtocol(); return omnetpp::opp_typename(typeid(*const_cast<Protocol *>(value))); }
        default: return nullptr;
    }
}

std::string Ipv6SocketBindCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: { auto obj = pp->getProtocol(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_localAddress: return pp->getLocalAddress().str();
        default: return "";
    }
}

void Ipv6SocketBindCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketBindCommand'", field);
    }
}

omnetpp::cValue Ipv6SocketBindCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: return omnetpp::toAnyPtr(pp->getProtocol()); break;
        case FIELD_localAddress: return omnetpp::toAnyPtr(&pp->getLocalAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketBindCommand' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketBindCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketBindCommand'", field);
    }
}

const char *Ipv6SocketBindCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocol: return omnetpp::opp_typename(typeid(Protocol));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6SocketBindCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: return omnetpp::toAnyPtr(pp->getProtocol()); break;
        case FIELD_localAddress: return omnetpp::toAnyPtr(&pp->getLocalAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketBindCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketBindCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketBindCommand'", field);
    }
}

Register_Class(Ipv6SocketConnectCommand)

Ipv6SocketConnectCommand::Ipv6SocketConnectCommand() : ::inet::Ipv6SocketCommandBase()
{
}

Ipv6SocketConnectCommand::Ipv6SocketConnectCommand(const Ipv6SocketConnectCommand& other) : ::inet::Ipv6SocketCommandBase(other)
{
    copy(other);
}

Ipv6SocketConnectCommand::~Ipv6SocketConnectCommand()
{
}

Ipv6SocketConnectCommand& Ipv6SocketConnectCommand::operator=(const Ipv6SocketConnectCommand& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6SocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketConnectCommand::copy(const Ipv6SocketConnectCommand& other)
{
    this->protocol = other.protocol;
    this->remoteAddress = other.remoteAddress;
}

void Ipv6SocketConnectCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6SocketCommandBase::parsimPack(b);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->remoteAddress);
}

void Ipv6SocketConnectCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6SocketCommandBase::parsimUnpack(b);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->remoteAddress);
}

const Protocol * Ipv6SocketConnectCommand::getProtocol() const
{
    return this->protocol;
}

void Ipv6SocketConnectCommand::setProtocol(const Protocol * protocol)
{
    this->protocol = protocol;
}

const Ipv6Address& Ipv6SocketConnectCommand::getRemoteAddress() const
{
    return this->remoteAddress;
}

void Ipv6SocketConnectCommand::setRemoteAddress(const Ipv6Address& remoteAddress)
{
    this->remoteAddress = remoteAddress;
}

class Ipv6SocketConnectCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_protocol,
        FIELD_remoteAddress,
    };
  public:
    Ipv6SocketConnectCommandDescriptor();
    virtual ~Ipv6SocketConnectCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketConnectCommandDescriptor)

Ipv6SocketConnectCommandDescriptor::Ipv6SocketConnectCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketConnectCommand)), "inet::Ipv6SocketCommandBase")
{
    propertyNames = nullptr;
}

Ipv6SocketConnectCommandDescriptor::~Ipv6SocketConnectCommandDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketConnectCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketConnectCommand *>(obj)!=nullptr;
}

const char **Ipv6SocketConnectCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketConnectCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketConnectCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv6SocketConnectCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_protocol
        0,    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6SocketConnectCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "protocol",
        "remoteAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6SocketConnectCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "protocol") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remoteAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketConnectCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Protocol",    // FIELD_protocol
        "inet::Ipv6Address",    // FIELD_remoteAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6SocketConnectCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketConnectCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketConnectCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketConnectCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketConnectCommand'", field);
    }
}

const char *Ipv6SocketConnectCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: { const Protocol * value = pp->getProtocol(); return omnetpp::opp_typename(typeid(*const_cast<Protocol *>(value))); }
        default: return nullptr;
    }
}

std::string Ipv6SocketConnectCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: { auto obj = pp->getProtocol(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_remoteAddress: return pp->getRemoteAddress().str();
        default: return "";
    }
}

void Ipv6SocketConnectCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketConnectCommand'", field);
    }
}

omnetpp::cValue Ipv6SocketConnectCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: return omnetpp::toAnyPtr(pp->getProtocol()); break;
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketConnectCommand' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketConnectCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketConnectCommand'", field);
    }
}

const char *Ipv6SocketConnectCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocol: return omnetpp::opp_typename(typeid(Protocol));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6SocketConnectCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_protocol: return omnetpp::toAnyPtr(pp->getProtocol()); break;
        case FIELD_remoteAddress: return omnetpp::toAnyPtr(&pp->getRemoteAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketConnectCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketConnectCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketConnectCommand'", field);
    }
}

Register_Class(Ipv6SocketCloseCommand)

Ipv6SocketCloseCommand::Ipv6SocketCloseCommand() : ::inet::Ipv6SocketCommandBase()
{
}

Ipv6SocketCloseCommand::Ipv6SocketCloseCommand(const Ipv6SocketCloseCommand& other) : ::inet::Ipv6SocketCommandBase(other)
{
    copy(other);
}

Ipv6SocketCloseCommand::~Ipv6SocketCloseCommand()
{
}

Ipv6SocketCloseCommand& Ipv6SocketCloseCommand::operator=(const Ipv6SocketCloseCommand& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6SocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketCloseCommand::copy(const Ipv6SocketCloseCommand& other)
{
}

void Ipv6SocketCloseCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6SocketCommandBase::parsimPack(b);
}

void Ipv6SocketCloseCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6SocketCommandBase::parsimUnpack(b);
}

class Ipv6SocketCloseCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6SocketCloseCommandDescriptor();
    virtual ~Ipv6SocketCloseCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketCloseCommandDescriptor)

Ipv6SocketCloseCommandDescriptor::Ipv6SocketCloseCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketCloseCommand)), "inet::Ipv6SocketCommandBase")
{
    propertyNames = nullptr;
}

Ipv6SocketCloseCommandDescriptor::~Ipv6SocketCloseCommandDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketCloseCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketCloseCommand *>(obj)!=nullptr;
}

const char **Ipv6SocketCloseCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketCloseCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketCloseCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6SocketCloseCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6SocketCloseCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6SocketCloseCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketCloseCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6SocketCloseCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketCloseCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketCloseCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketCloseCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketCloseCommand'", field);
    }
}

const char *Ipv6SocketCloseCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6SocketCloseCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6SocketCloseCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCloseCommand'", field);
    }
}

omnetpp::cValue Ipv6SocketCloseCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketCloseCommand' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketCloseCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCloseCommand'", field);
    }
}

const char *Ipv6SocketCloseCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6SocketCloseCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketCloseCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketCloseCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketCloseCommand'", field);
    }
}

Register_Class(Ipv6SocketDestroyCommand)

Ipv6SocketDestroyCommand::Ipv6SocketDestroyCommand() : ::inet::Ipv6SocketCommandBase()
{
}

Ipv6SocketDestroyCommand::Ipv6SocketDestroyCommand(const Ipv6SocketDestroyCommand& other) : ::inet::Ipv6SocketCommandBase(other)
{
    copy(other);
}

Ipv6SocketDestroyCommand::~Ipv6SocketDestroyCommand()
{
}

Ipv6SocketDestroyCommand& Ipv6SocketDestroyCommand::operator=(const Ipv6SocketDestroyCommand& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6SocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketDestroyCommand::copy(const Ipv6SocketDestroyCommand& other)
{
}

void Ipv6SocketDestroyCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6SocketCommandBase::parsimPack(b);
}

void Ipv6SocketDestroyCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6SocketCommandBase::parsimUnpack(b);
}

class Ipv6SocketDestroyCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6SocketDestroyCommandDescriptor();
    virtual ~Ipv6SocketDestroyCommandDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketDestroyCommandDescriptor)

Ipv6SocketDestroyCommandDescriptor::Ipv6SocketDestroyCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketDestroyCommand)), "inet::Ipv6SocketCommandBase")
{
    propertyNames = nullptr;
}

Ipv6SocketDestroyCommandDescriptor::~Ipv6SocketDestroyCommandDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketDestroyCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketDestroyCommand *>(obj)!=nullptr;
}

const char **Ipv6SocketDestroyCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketDestroyCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketDestroyCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6SocketDestroyCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6SocketDestroyCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6SocketDestroyCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketDestroyCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6SocketDestroyCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketDestroyCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketDestroyCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketDestroyCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketDestroyCommand'", field);
    }
}

const char *Ipv6SocketDestroyCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6SocketDestroyCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6SocketDestroyCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketDestroyCommand'", field);
    }
}

omnetpp::cValue Ipv6SocketDestroyCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketDestroyCommand' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketDestroyCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketDestroyCommand'", field);
    }
}

const char *Ipv6SocketDestroyCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6SocketDestroyCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketDestroyCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketDestroyCommand *pp = omnetpp::fromAnyPtr<Ipv6SocketDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketDestroyCommand'", field);
    }
}

Register_Class(Ipv6SocketClosedIndication)

Ipv6SocketClosedIndication::Ipv6SocketClosedIndication() : ::inet::Ipv6SocketCommandBase()
{
}

Ipv6SocketClosedIndication::Ipv6SocketClosedIndication(const Ipv6SocketClosedIndication& other) : ::inet::Ipv6SocketCommandBase(other)
{
    copy(other);
}

Ipv6SocketClosedIndication::~Ipv6SocketClosedIndication()
{
}

Ipv6SocketClosedIndication& Ipv6SocketClosedIndication::operator=(const Ipv6SocketClosedIndication& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6SocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6SocketClosedIndication::copy(const Ipv6SocketClosedIndication& other)
{
}

void Ipv6SocketClosedIndication::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6SocketCommandBase::parsimPack(b);
}

void Ipv6SocketClosedIndication::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6SocketCommandBase::parsimUnpack(b);
}

class Ipv6SocketClosedIndicationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6SocketClosedIndicationDescriptor();
    virtual ~Ipv6SocketClosedIndicationDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(Ipv6SocketClosedIndicationDescriptor)

Ipv6SocketClosedIndicationDescriptor::Ipv6SocketClosedIndicationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6SocketClosedIndication)), "inet::Ipv6SocketCommandBase")
{
    propertyNames = nullptr;
}

Ipv6SocketClosedIndicationDescriptor::~Ipv6SocketClosedIndicationDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6SocketClosedIndicationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6SocketClosedIndication *>(obj)!=nullptr;
}

const char **Ipv6SocketClosedIndicationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6SocketClosedIndicationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6SocketClosedIndicationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6SocketClosedIndicationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6SocketClosedIndicationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6SocketClosedIndicationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6SocketClosedIndicationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6SocketClosedIndicationDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *Ipv6SocketClosedIndicationDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int Ipv6SocketClosedIndicationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6SocketClosedIndicationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6SocketClosedIndication'", field);
    }
}

const char *Ipv6SocketClosedIndicationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6SocketClosedIndicationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6SocketClosedIndicationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketClosedIndication'", field);
    }
}

omnetpp::cValue Ipv6SocketClosedIndicationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6SocketClosedIndication' as cValue -- field index out of range?", field);
    }
}

void Ipv6SocketClosedIndicationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketClosedIndication'", field);
    }
}

const char *Ipv6SocketClosedIndicationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6SocketClosedIndicationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6SocketClosedIndicationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6SocketClosedIndication *pp = omnetpp::fromAnyPtr<Ipv6SocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6SocketClosedIndication'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

