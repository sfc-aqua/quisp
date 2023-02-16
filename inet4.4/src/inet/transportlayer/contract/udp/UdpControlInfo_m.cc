//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/contract/udp/UdpControlInfo.msg.
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
#include "UdpControlInfo_m.h"

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

Register_Enum(inet::UdpCommandCode, (inet::UdpCommandCode::UDP_C_DATA, inet::UdpCommandCode::UDP_C_BIND, inet::UdpCommandCode::UDP_C_CONNECT, inet::UdpCommandCode::UDP_C_SETOPTION, inet::UdpCommandCode::UDP_C_CLOSE, inet::UdpCommandCode::UDP_C_DESTROY));

Register_Enum(inet::UdpSetOptionSubcode, (inet::UdpSetOptionSubcode::UDP_C_SETOPTION_TTL, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_DSCP, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_TOS, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_BROADCAST, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_MCAST_IFACE, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_MCAST_LOOP, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_REUSEADDR, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_JOIN_MCAST_GRP, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_LEAVE_MCAST_GRP, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_JOIN_MCAST_SRC, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_BLOCK_MCAST_SRC, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_UNBLOCK_MCAST_SRC, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_LEAVE_MCAST_SRC, inet::UdpSetOptionSubcode::UDP_C_SETOPTION_SET_MCAST_SRC_FILTER));

Register_Enum(inet::UdpStatusInd, (inet::UdpStatusInd::UDP_I_DATA, inet::UdpStatusInd::UDP_I_ERROR, inet::UdpStatusInd::UDP_I_SOCKET_CLOSED));

Register_Class(UdpControlInfo)

UdpControlInfo::UdpControlInfo() : ::omnetpp::cObject()
{
}

UdpControlInfo::UdpControlInfo(const UdpControlInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

UdpControlInfo::~UdpControlInfo()
{
}

UdpControlInfo& UdpControlInfo::operator=(const UdpControlInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void UdpControlInfo::copy(const UdpControlInfo& other)
{
}

void UdpControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
}

void UdpControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
}

class UdpControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    UdpControlInfoDescriptor();
    virtual ~UdpControlInfoDescriptor();

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

Register_ClassDescriptor(UdpControlInfoDescriptor)

UdpControlInfoDescriptor::UdpControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpControlInfo)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

UdpControlInfoDescriptor::~UdpControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool UdpControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpControlInfo *>(obj)!=nullptr;
}

const char **UdpControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int UdpControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *UdpControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int UdpControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *UdpControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **UdpControlInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpControlInfo'", field);
    }
}

const char *UdpControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void UdpControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpControlInfo'", field);
    }
}

omnetpp::cValue UdpControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpControlInfo' as cValue -- field index out of range?", field);
    }
}

void UdpControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpControlInfo'", field);
    }
}

const char *UdpControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr UdpControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpControlInfo *pp = omnetpp::fromAnyPtr<UdpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpControlInfo'", field);
    }
}

Register_Class(UdpBindCommand)

UdpBindCommand::UdpBindCommand() : ::inet::UdpControlInfo()
{
}

UdpBindCommand::UdpBindCommand(const UdpBindCommand& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpBindCommand::~UdpBindCommand()
{
}

UdpBindCommand& UdpBindCommand::operator=(const UdpBindCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpBindCommand::copy(const UdpBindCommand& other)
{
    this->localAddr = other.localAddr;
    this->localPort = other.localPort;
}

void UdpBindCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->localPort);
}

void UdpBindCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->localPort);
}

const L3Address& UdpBindCommand::getLocalAddr() const
{
    return this->localAddr;
}

void UdpBindCommand::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

int UdpBindCommand::getLocalPort() const
{
    return this->localPort;
}

void UdpBindCommand::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

class UdpBindCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_localPort,
    };
  public:
    UdpBindCommandDescriptor();
    virtual ~UdpBindCommandDescriptor();

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

Register_ClassDescriptor(UdpBindCommandDescriptor)

UdpBindCommandDescriptor::UdpBindCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpBindCommand)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpBindCommandDescriptor::~UdpBindCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpBindCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpBindCommand *>(obj)!=nullptr;
}

const char **UdpBindCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpBindCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpBindCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int UdpBindCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        FD_ISEDITABLE,    // FIELD_localPort
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *UdpBindCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "localPort",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int UdpBindCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpBindCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "int",    // FIELD_localPort
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpBindCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpBindCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpBindCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpBindCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpBindCommand'", field);
    }
}

const char *UdpBindCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpBindCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        default: return "";
    }
}

void UdpBindCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBindCommand'", field);
    }
}

omnetpp::cValue UdpBindCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpBindCommand' as cValue -- field index out of range?", field);
    }
}

void UdpBindCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBindCommand'", field);
    }
}

const char *UdpBindCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpBindCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpBindCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBindCommand *pp = omnetpp::fromAnyPtr<UdpBindCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBindCommand'", field);
    }
}

Register_Class(UdpConnectCommand)

UdpConnectCommand::UdpConnectCommand() : ::inet::UdpControlInfo()
{
}

UdpConnectCommand::UdpConnectCommand(const UdpConnectCommand& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpConnectCommand::~UdpConnectCommand()
{
}

UdpConnectCommand& UdpConnectCommand::operator=(const UdpConnectCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpConnectCommand::copy(const UdpConnectCommand& other)
{
    this->remoteAddr = other.remoteAddr;
    this->remotePort = other.remotePort;
}

void UdpConnectCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->remotePort);
}

void UdpConnectCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->remotePort);
}

const L3Address& UdpConnectCommand::getRemoteAddr() const
{
    return this->remoteAddr;
}

void UdpConnectCommand::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int UdpConnectCommand::getRemotePort() const
{
    return this->remotePort;
}

void UdpConnectCommand::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

class UdpConnectCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddr,
        FIELD_remotePort,
    };
  public:
    UdpConnectCommandDescriptor();
    virtual ~UdpConnectCommandDescriptor();

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

Register_ClassDescriptor(UdpConnectCommandDescriptor)

UdpConnectCommandDescriptor::UdpConnectCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpConnectCommand)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpConnectCommandDescriptor::~UdpConnectCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpConnectCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpConnectCommand *>(obj)!=nullptr;
}

const char **UdpConnectCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpConnectCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpConnectCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int UdpConnectCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_remotePort
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *UdpConnectCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddr",
        "remotePort",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int UdpConnectCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpConnectCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_remotePort
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpConnectCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpConnectCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpConnectCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpConnectCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpConnectCommand'", field);
    }
}

const char *UdpConnectCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpConnectCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        default: return "";
    }
}

void UdpConnectCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpConnectCommand'", field);
    }
}

omnetpp::cValue UdpConnectCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_remotePort: return pp->getRemotePort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpConnectCommand' as cValue -- field index out of range?", field);
    }
}

void UdpConnectCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpConnectCommand'", field);
    }
}

const char *UdpConnectCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpConnectCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpConnectCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpConnectCommand *pp = omnetpp::fromAnyPtr<UdpConnectCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpConnectCommand'", field);
    }
}

Register_Class(UdpCloseCommand)

UdpCloseCommand::UdpCloseCommand() : ::inet::UdpControlInfo()
{
}

UdpCloseCommand::UdpCloseCommand(const UdpCloseCommand& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpCloseCommand::~UdpCloseCommand()
{
}

UdpCloseCommand& UdpCloseCommand::operator=(const UdpCloseCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpCloseCommand::copy(const UdpCloseCommand& other)
{
}

void UdpCloseCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
}

void UdpCloseCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
}

class UdpCloseCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    UdpCloseCommandDescriptor();
    virtual ~UdpCloseCommandDescriptor();

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

Register_ClassDescriptor(UdpCloseCommandDescriptor)

UdpCloseCommandDescriptor::UdpCloseCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpCloseCommand)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpCloseCommandDescriptor::~UdpCloseCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpCloseCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpCloseCommand *>(obj)!=nullptr;
}

const char **UdpCloseCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpCloseCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpCloseCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int UdpCloseCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *UdpCloseCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int UdpCloseCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *UdpCloseCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **UdpCloseCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpCloseCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpCloseCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpCloseCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpCloseCommand'", field);
    }
}

const char *UdpCloseCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpCloseCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void UdpCloseCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpCloseCommand'", field);
    }
}

omnetpp::cValue UdpCloseCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpCloseCommand' as cValue -- field index out of range?", field);
    }
}

void UdpCloseCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpCloseCommand'", field);
    }
}

const char *UdpCloseCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr UdpCloseCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpCloseCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpCloseCommand *pp = omnetpp::fromAnyPtr<UdpCloseCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpCloseCommand'", field);
    }
}

Register_Class(UdpSocketClosedIndication)

UdpSocketClosedIndication::UdpSocketClosedIndication() : ::inet::UdpControlInfo()
{
}

UdpSocketClosedIndication::UdpSocketClosedIndication(const UdpSocketClosedIndication& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpSocketClosedIndication::~UdpSocketClosedIndication()
{
}

UdpSocketClosedIndication& UdpSocketClosedIndication::operator=(const UdpSocketClosedIndication& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpSocketClosedIndication::copy(const UdpSocketClosedIndication& other)
{
}

void UdpSocketClosedIndication::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
}

void UdpSocketClosedIndication::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
}

class UdpSocketClosedIndicationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    UdpSocketClosedIndicationDescriptor();
    virtual ~UdpSocketClosedIndicationDescriptor();

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

Register_ClassDescriptor(UdpSocketClosedIndicationDescriptor)

UdpSocketClosedIndicationDescriptor::UdpSocketClosedIndicationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSocketClosedIndication)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpSocketClosedIndicationDescriptor::~UdpSocketClosedIndicationDescriptor()
{
    delete[] propertyNames;
}

bool UdpSocketClosedIndicationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSocketClosedIndication *>(obj)!=nullptr;
}

const char **UdpSocketClosedIndicationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSocketClosedIndicationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSocketClosedIndicationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int UdpSocketClosedIndicationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *UdpSocketClosedIndicationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int UdpSocketClosedIndicationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSocketClosedIndicationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **UdpSocketClosedIndicationDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSocketClosedIndicationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSocketClosedIndicationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSocketClosedIndicationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSocketClosedIndication'", field);
    }
}

const char *UdpSocketClosedIndicationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSocketClosedIndicationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void UdpSocketClosedIndicationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSocketClosedIndication'", field);
    }
}

omnetpp::cValue UdpSocketClosedIndicationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSocketClosedIndication' as cValue -- field index out of range?", field);
    }
}

void UdpSocketClosedIndicationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSocketClosedIndication'", field);
    }
}

const char *UdpSocketClosedIndicationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr UdpSocketClosedIndicationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSocketClosedIndicationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSocketClosedIndication *pp = omnetpp::fromAnyPtr<UdpSocketClosedIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSocketClosedIndication'", field);
    }
}

Register_Class(UdpDestroyCommand)

UdpDestroyCommand::UdpDestroyCommand() : ::inet::UdpControlInfo()
{
}

UdpDestroyCommand::UdpDestroyCommand(const UdpDestroyCommand& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpDestroyCommand::~UdpDestroyCommand()
{
}

UdpDestroyCommand& UdpDestroyCommand::operator=(const UdpDestroyCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpDestroyCommand::copy(const UdpDestroyCommand& other)
{
}

void UdpDestroyCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
}

void UdpDestroyCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
}

class UdpDestroyCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    UdpDestroyCommandDescriptor();
    virtual ~UdpDestroyCommandDescriptor();

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

Register_ClassDescriptor(UdpDestroyCommandDescriptor)

UdpDestroyCommandDescriptor::UdpDestroyCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpDestroyCommand)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpDestroyCommandDescriptor::~UdpDestroyCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpDestroyCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpDestroyCommand *>(obj)!=nullptr;
}

const char **UdpDestroyCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpDestroyCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpDestroyCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int UdpDestroyCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *UdpDestroyCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int UdpDestroyCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *UdpDestroyCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **UdpDestroyCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpDestroyCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpDestroyCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpDestroyCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpDestroyCommand'", field);
    }
}

const char *UdpDestroyCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpDestroyCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void UdpDestroyCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpDestroyCommand'", field);
    }
}

omnetpp::cValue UdpDestroyCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpDestroyCommand' as cValue -- field index out of range?", field);
    }
}

void UdpDestroyCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpDestroyCommand'", field);
    }
}

const char *UdpDestroyCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr UdpDestroyCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpDestroyCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpDestroyCommand *pp = omnetpp::fromAnyPtr<UdpDestroyCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpDestroyCommand'", field);
    }
}

Register_Class(UdpErrorIndication)

UdpErrorIndication::UdpErrorIndication() : ::inet::UdpControlInfo()
{
}

UdpErrorIndication::UdpErrorIndication(const UdpErrorIndication& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpErrorIndication::~UdpErrorIndication()
{
}

UdpErrorIndication& UdpErrorIndication::operator=(const UdpErrorIndication& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpErrorIndication::copy(const UdpErrorIndication& other)
{
}

void UdpErrorIndication::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
}

void UdpErrorIndication::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
}

class UdpErrorIndicationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    UdpErrorIndicationDescriptor();
    virtual ~UdpErrorIndicationDescriptor();

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

Register_ClassDescriptor(UdpErrorIndicationDescriptor)

UdpErrorIndicationDescriptor::UdpErrorIndicationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpErrorIndication)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpErrorIndicationDescriptor::~UdpErrorIndicationDescriptor()
{
    delete[] propertyNames;
}

bool UdpErrorIndicationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpErrorIndication *>(obj)!=nullptr;
}

const char **UdpErrorIndicationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpErrorIndicationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpErrorIndicationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int UdpErrorIndicationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *UdpErrorIndicationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int UdpErrorIndicationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *UdpErrorIndicationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **UdpErrorIndicationDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpErrorIndicationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpErrorIndicationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpErrorIndicationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpErrorIndication'", field);
    }
}

const char *UdpErrorIndicationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpErrorIndicationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void UdpErrorIndicationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpErrorIndication'", field);
    }
}

omnetpp::cValue UdpErrorIndicationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpErrorIndication' as cValue -- field index out of range?", field);
    }
}

void UdpErrorIndicationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpErrorIndication'", field);
    }
}

const char *UdpErrorIndicationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr UdpErrorIndicationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpErrorIndicationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpErrorIndication *pp = omnetpp::fromAnyPtr<UdpErrorIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpErrorIndication'", field);
    }
}

Register_Class(UdpSetOptionCommand)

UdpSetOptionCommand::UdpSetOptionCommand() : ::inet::UdpControlInfo()
{
}

UdpSetOptionCommand::UdpSetOptionCommand(const UdpSetOptionCommand& other) : ::inet::UdpControlInfo(other)
{
    copy(other);
}

UdpSetOptionCommand::~UdpSetOptionCommand()
{
}

UdpSetOptionCommand& UdpSetOptionCommand::operator=(const UdpSetOptionCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void UdpSetOptionCommand::copy(const UdpSetOptionCommand& other)
{
    this->optionCode = other.optionCode;
}

void UdpSetOptionCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpControlInfo::parsimPack(b);
    doParsimPacking(b,this->optionCode);
}

void UdpSetOptionCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->optionCode);
}

UdpSetOptionSubcode UdpSetOptionCommand::getOptionCode() const
{
    return this->optionCode;
}

void UdpSetOptionCommand::setOptionCode(UdpSetOptionSubcode optionCode)
{
    this->optionCode = optionCode;
}

class UdpSetOptionCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_optionCode,
    };
  public:
    UdpSetOptionCommandDescriptor();
    virtual ~UdpSetOptionCommandDescriptor();

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

Register_ClassDescriptor(UdpSetOptionCommandDescriptor)

UdpSetOptionCommandDescriptor::UdpSetOptionCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetOptionCommand)), "inet::UdpControlInfo")
{
    propertyNames = nullptr;
}

UdpSetOptionCommandDescriptor::~UdpSetOptionCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetOptionCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetOptionCommand *>(obj)!=nullptr;
}

const char **UdpSetOptionCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetOptionCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetOptionCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetOptionCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_optionCode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetOptionCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "optionCode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetOptionCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "optionCode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetOptionCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::UdpSetOptionSubcode",    // FIELD_optionCode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetOptionCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_optionCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *UdpSetOptionCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_optionCode:
            if (!strcmp(propertyName, "enum")) return "inet::UdpSetOptionSubcode";
            return nullptr;
        default: return nullptr;
    }
}

int UdpSetOptionCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetOptionCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetOptionCommand'", field);
    }
}

const char *UdpSetOptionCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetOptionCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        case FIELD_optionCode: return enum2string(pp->getOptionCode(), "inet::UdpSetOptionSubcode");
        default: return "";
    }
}

void UdpSetOptionCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetOptionCommand'", field);
    }
}

omnetpp::cValue UdpSetOptionCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        case FIELD_optionCode: return static_cast<int>(pp->getOptionCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetOptionCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetOptionCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetOptionCommand'", field);
    }
}

const char *UdpSetOptionCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetOptionCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetOptionCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetOptionCommand *pp = omnetpp::fromAnyPtr<UdpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetOptionCommand'", field);
    }
}

Register_Class(UdpSetTimeToLiveCommand)

UdpSetTimeToLiveCommand::UdpSetTimeToLiveCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_TTL);

}

UdpSetTimeToLiveCommand::UdpSetTimeToLiveCommand(const UdpSetTimeToLiveCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetTimeToLiveCommand::~UdpSetTimeToLiveCommand()
{
}

UdpSetTimeToLiveCommand& UdpSetTimeToLiveCommand::operator=(const UdpSetTimeToLiveCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetTimeToLiveCommand::copy(const UdpSetTimeToLiveCommand& other)
{
    this->ttl = other.ttl;
}

void UdpSetTimeToLiveCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->ttl);
}

void UdpSetTimeToLiveCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->ttl);
}

int UdpSetTimeToLiveCommand::getTtl() const
{
    return this->ttl;
}

void UdpSetTimeToLiveCommand::setTtl(int ttl)
{
    this->ttl = ttl;
}

class UdpSetTimeToLiveCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ttl,
    };
  public:
    UdpSetTimeToLiveCommandDescriptor();
    virtual ~UdpSetTimeToLiveCommandDescriptor();

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

Register_ClassDescriptor(UdpSetTimeToLiveCommandDescriptor)

UdpSetTimeToLiveCommandDescriptor::UdpSetTimeToLiveCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetTimeToLiveCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetTimeToLiveCommandDescriptor::~UdpSetTimeToLiveCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetTimeToLiveCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetTimeToLiveCommand *>(obj)!=nullptr;
}

const char **UdpSetTimeToLiveCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetTimeToLiveCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetTimeToLiveCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetTimeToLiveCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ttl
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetTimeToLiveCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ttl",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetTimeToLiveCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetTimeToLiveCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_ttl
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetTimeToLiveCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetTimeToLiveCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetTimeToLiveCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetTimeToLiveCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetTimeToLiveCommand'", field);
    }
}

const char *UdpSetTimeToLiveCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetTimeToLiveCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: return long2string(pp->getTtl());
        default: return "";
    }
}

void UdpSetTimeToLiveCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: pp->setTtl(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTimeToLiveCommand'", field);
    }
}

omnetpp::cValue UdpSetTimeToLiveCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: return pp->getTtl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetTimeToLiveCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetTimeToLiveCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: pp->setTtl(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTimeToLiveCommand'", field);
    }
}

const char *UdpSetTimeToLiveCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetTimeToLiveCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetTimeToLiveCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<UdpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTimeToLiveCommand'", field);
    }
}

Register_Class(UdpSetDscpCommand)

UdpSetDscpCommand::UdpSetDscpCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_DSCP);

}

UdpSetDscpCommand::UdpSetDscpCommand(const UdpSetDscpCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetDscpCommand::~UdpSetDscpCommand()
{
}

UdpSetDscpCommand& UdpSetDscpCommand::operator=(const UdpSetDscpCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetDscpCommand::copy(const UdpSetDscpCommand& other)
{
    this->dscp = other.dscp;
}

void UdpSetDscpCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->dscp);
}

void UdpSetDscpCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->dscp);
}

short UdpSetDscpCommand::getDscp() const
{
    return this->dscp;
}

void UdpSetDscpCommand::setDscp(short dscp)
{
    this->dscp = dscp;
}

class UdpSetDscpCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dscp,
    };
  public:
    UdpSetDscpCommandDescriptor();
    virtual ~UdpSetDscpCommandDescriptor();

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

Register_ClassDescriptor(UdpSetDscpCommandDescriptor)

UdpSetDscpCommandDescriptor::UdpSetDscpCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetDscpCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetDscpCommandDescriptor::~UdpSetDscpCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetDscpCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetDscpCommand *>(obj)!=nullptr;
}

const char **UdpSetDscpCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetDscpCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetDscpCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetDscpCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dscp
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetDscpCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dscp",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetDscpCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dscp") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetDscpCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_dscp
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetDscpCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetDscpCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetDscpCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetDscpCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetDscpCommand'", field);
    }
}

const char *UdpSetDscpCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetDscpCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: return long2string(pp->getDscp());
        default: return "";
    }
}

void UdpSetDscpCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: pp->setDscp(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetDscpCommand'", field);
    }
}

omnetpp::cValue UdpSetDscpCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: return pp->getDscp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetDscpCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetDscpCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: pp->setDscp(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetDscpCommand'", field);
    }
}

const char *UdpSetDscpCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetDscpCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetDscpCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetDscpCommand *pp = omnetpp::fromAnyPtr<UdpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetDscpCommand'", field);
    }
}

Register_Class(UdpSetTosCommand)

UdpSetTosCommand::UdpSetTosCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_TOS);

}

UdpSetTosCommand::UdpSetTosCommand(const UdpSetTosCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetTosCommand::~UdpSetTosCommand()
{
}

UdpSetTosCommand& UdpSetTosCommand::operator=(const UdpSetTosCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetTosCommand::copy(const UdpSetTosCommand& other)
{
    this->tos = other.tos;
}

void UdpSetTosCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->tos);
}

void UdpSetTosCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->tos);
}

short UdpSetTosCommand::getTos() const
{
    return this->tos;
}

void UdpSetTosCommand::setTos(short tos)
{
    this->tos = tos;
}

class UdpSetTosCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tos,
    };
  public:
    UdpSetTosCommandDescriptor();
    virtual ~UdpSetTosCommandDescriptor();

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

Register_ClassDescriptor(UdpSetTosCommandDescriptor)

UdpSetTosCommandDescriptor::UdpSetTosCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetTosCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetTosCommandDescriptor::~UdpSetTosCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetTosCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetTosCommand *>(obj)!=nullptr;
}

const char **UdpSetTosCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetTosCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetTosCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetTosCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tos
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetTosCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tos",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetTosCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tos") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetTosCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_tos
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetTosCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetTosCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetTosCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetTosCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetTosCommand'", field);
    }
}

const char *UdpSetTosCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetTosCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return long2string(pp->getTos());
        default: return "";
    }
}

void UdpSetTosCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->setTos(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTosCommand'", field);
    }
}

omnetpp::cValue UdpSetTosCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return pp->getTos();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetTosCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetTosCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->setTos(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTosCommand'", field);
    }
}

const char *UdpSetTosCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetTosCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetTosCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetTosCommand *pp = omnetpp::fromAnyPtr<UdpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetTosCommand'", field);
    }
}

Register_Class(UdpSetBroadcastCommand)

UdpSetBroadcastCommand::UdpSetBroadcastCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_BROADCAST);

}

UdpSetBroadcastCommand::UdpSetBroadcastCommand(const UdpSetBroadcastCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetBroadcastCommand::~UdpSetBroadcastCommand()
{
}

UdpSetBroadcastCommand& UdpSetBroadcastCommand::operator=(const UdpSetBroadcastCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetBroadcastCommand::copy(const UdpSetBroadcastCommand& other)
{
    this->broadcast = other.broadcast;
}

void UdpSetBroadcastCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->broadcast);
}

void UdpSetBroadcastCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->broadcast);
}

bool UdpSetBroadcastCommand::getBroadcast() const
{
    return this->broadcast;
}

void UdpSetBroadcastCommand::setBroadcast(bool broadcast)
{
    this->broadcast = broadcast;
}

class UdpSetBroadcastCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_broadcast,
    };
  public:
    UdpSetBroadcastCommandDescriptor();
    virtual ~UdpSetBroadcastCommandDescriptor();

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

Register_ClassDescriptor(UdpSetBroadcastCommandDescriptor)

UdpSetBroadcastCommandDescriptor::UdpSetBroadcastCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetBroadcastCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetBroadcastCommandDescriptor::~UdpSetBroadcastCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetBroadcastCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetBroadcastCommand *>(obj)!=nullptr;
}

const char **UdpSetBroadcastCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetBroadcastCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetBroadcastCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetBroadcastCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_broadcast
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetBroadcastCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "broadcast",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetBroadcastCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "broadcast") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetBroadcastCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_broadcast
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetBroadcastCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetBroadcastCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetBroadcastCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetBroadcastCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetBroadcastCommand'", field);
    }
}

const char *UdpSetBroadcastCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetBroadcastCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        case FIELD_broadcast: return bool2string(pp->getBroadcast());
        default: return "";
    }
}

void UdpSetBroadcastCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        case FIELD_broadcast: pp->setBroadcast(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetBroadcastCommand'", field);
    }
}

omnetpp::cValue UdpSetBroadcastCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        case FIELD_broadcast: return pp->getBroadcast();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetBroadcastCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetBroadcastCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        case FIELD_broadcast: pp->setBroadcast(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetBroadcastCommand'", field);
    }
}

const char *UdpSetBroadcastCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetBroadcastCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetBroadcastCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetBroadcastCommand *pp = omnetpp::fromAnyPtr<UdpSetBroadcastCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetBroadcastCommand'", field);
    }
}

Register_Class(UdpSetMulticastInterfaceCommand)

UdpSetMulticastInterfaceCommand::UdpSetMulticastInterfaceCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_MCAST_IFACE);

}

UdpSetMulticastInterfaceCommand::UdpSetMulticastInterfaceCommand(const UdpSetMulticastInterfaceCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetMulticastInterfaceCommand::~UdpSetMulticastInterfaceCommand()
{
}

UdpSetMulticastInterfaceCommand& UdpSetMulticastInterfaceCommand::operator=(const UdpSetMulticastInterfaceCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetMulticastInterfaceCommand::copy(const UdpSetMulticastInterfaceCommand& other)
{
    this->interfaceId = other.interfaceId;
}

void UdpSetMulticastInterfaceCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
}

void UdpSetMulticastInterfaceCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
}

int UdpSetMulticastInterfaceCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpSetMulticastInterfaceCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

class UdpSetMulticastInterfaceCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
    };
  public:
    UdpSetMulticastInterfaceCommandDescriptor();
    virtual ~UdpSetMulticastInterfaceCommandDescriptor();

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

Register_ClassDescriptor(UdpSetMulticastInterfaceCommandDescriptor)

UdpSetMulticastInterfaceCommandDescriptor::UdpSetMulticastInterfaceCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetMulticastInterfaceCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetMulticastInterfaceCommandDescriptor::~UdpSetMulticastInterfaceCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetMulticastInterfaceCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetMulticastInterfaceCommand *>(obj)!=nullptr;
}

const char **UdpSetMulticastInterfaceCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetMulticastInterfaceCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetMulticastInterfaceCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetMulticastInterfaceCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetMulticastInterfaceCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetMulticastInterfaceCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetMulticastInterfaceCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetMulticastInterfaceCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetMulticastInterfaceCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetMulticastInterfaceCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetMulticastInterfaceCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetMulticastInterfaceCommand'", field);
    }
}

const char *UdpSetMulticastInterfaceCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetMulticastInterfaceCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        default: return "";
    }
}

void UdpSetMulticastInterfaceCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastInterfaceCommand'", field);
    }
}

omnetpp::cValue UdpSetMulticastInterfaceCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetMulticastInterfaceCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetMulticastInterfaceCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastInterfaceCommand'", field);
    }
}

const char *UdpSetMulticastInterfaceCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetMulticastInterfaceCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetMulticastInterfaceCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastInterfaceCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastInterfaceCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastInterfaceCommand'", field);
    }
}

Register_Class(UdpSetMulticastLoopCommand)

UdpSetMulticastLoopCommand::UdpSetMulticastLoopCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_MCAST_LOOP);

}

UdpSetMulticastLoopCommand::UdpSetMulticastLoopCommand(const UdpSetMulticastLoopCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetMulticastLoopCommand::~UdpSetMulticastLoopCommand()
{
}

UdpSetMulticastLoopCommand& UdpSetMulticastLoopCommand::operator=(const UdpSetMulticastLoopCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetMulticastLoopCommand::copy(const UdpSetMulticastLoopCommand& other)
{
    this->loop = other.loop;
}

void UdpSetMulticastLoopCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->loop);
}

void UdpSetMulticastLoopCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->loop);
}

bool UdpSetMulticastLoopCommand::getLoop() const
{
    return this->loop;
}

void UdpSetMulticastLoopCommand::setLoop(bool loop)
{
    this->loop = loop;
}

class UdpSetMulticastLoopCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_loop,
    };
  public:
    UdpSetMulticastLoopCommandDescriptor();
    virtual ~UdpSetMulticastLoopCommandDescriptor();

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

Register_ClassDescriptor(UdpSetMulticastLoopCommandDescriptor)

UdpSetMulticastLoopCommandDescriptor::UdpSetMulticastLoopCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetMulticastLoopCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetMulticastLoopCommandDescriptor::~UdpSetMulticastLoopCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetMulticastLoopCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetMulticastLoopCommand *>(obj)!=nullptr;
}

const char **UdpSetMulticastLoopCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetMulticastLoopCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetMulticastLoopCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetMulticastLoopCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_loop
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetMulticastLoopCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "loop",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetMulticastLoopCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "loop") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetMulticastLoopCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_loop
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetMulticastLoopCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetMulticastLoopCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetMulticastLoopCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetMulticastLoopCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetMulticastLoopCommand'", field);
    }
}

const char *UdpSetMulticastLoopCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetMulticastLoopCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        case FIELD_loop: return bool2string(pp->getLoop());
        default: return "";
    }
}

void UdpSetMulticastLoopCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        case FIELD_loop: pp->setLoop(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastLoopCommand'", field);
    }
}

omnetpp::cValue UdpSetMulticastLoopCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        case FIELD_loop: return pp->getLoop();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetMulticastLoopCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetMulticastLoopCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        case FIELD_loop: pp->setLoop(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastLoopCommand'", field);
    }
}

const char *UdpSetMulticastLoopCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetMulticastLoopCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetMulticastLoopCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastLoopCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastLoopCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastLoopCommand'", field);
    }
}

Register_Class(UdpSetReuseAddressCommand)

UdpSetReuseAddressCommand::UdpSetReuseAddressCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_REUSEADDR);

}

UdpSetReuseAddressCommand::UdpSetReuseAddressCommand(const UdpSetReuseAddressCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetReuseAddressCommand::~UdpSetReuseAddressCommand()
{
}

UdpSetReuseAddressCommand& UdpSetReuseAddressCommand::operator=(const UdpSetReuseAddressCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetReuseAddressCommand::copy(const UdpSetReuseAddressCommand& other)
{
    this->reuseAddress = other.reuseAddress;
}

void UdpSetReuseAddressCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->reuseAddress);
}

void UdpSetReuseAddressCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->reuseAddress);
}

bool UdpSetReuseAddressCommand::getReuseAddress() const
{
    return this->reuseAddress;
}

void UdpSetReuseAddressCommand::setReuseAddress(bool reuseAddress)
{
    this->reuseAddress = reuseAddress;
}

class UdpSetReuseAddressCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reuseAddress,
    };
  public:
    UdpSetReuseAddressCommandDescriptor();
    virtual ~UdpSetReuseAddressCommandDescriptor();

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

Register_ClassDescriptor(UdpSetReuseAddressCommandDescriptor)

UdpSetReuseAddressCommandDescriptor::UdpSetReuseAddressCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetReuseAddressCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetReuseAddressCommandDescriptor::~UdpSetReuseAddressCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetReuseAddressCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetReuseAddressCommand *>(obj)!=nullptr;
}

const char **UdpSetReuseAddressCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetReuseAddressCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetReuseAddressCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpSetReuseAddressCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reuseAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetReuseAddressCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reuseAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpSetReuseAddressCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reuseAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetReuseAddressCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_reuseAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetReuseAddressCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpSetReuseAddressCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpSetReuseAddressCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UdpSetReuseAddressCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetReuseAddressCommand'", field);
    }
}

const char *UdpSetReuseAddressCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetReuseAddressCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        case FIELD_reuseAddress: return bool2string(pp->getReuseAddress());
        default: return "";
    }
}

void UdpSetReuseAddressCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        case FIELD_reuseAddress: pp->setReuseAddress(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetReuseAddressCommand'", field);
    }
}

omnetpp::cValue UdpSetReuseAddressCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        case FIELD_reuseAddress: return pp->getReuseAddress();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetReuseAddressCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetReuseAddressCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        case FIELD_reuseAddress: pp->setReuseAddress(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetReuseAddressCommand'", field);
    }
}

const char *UdpSetReuseAddressCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetReuseAddressCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetReuseAddressCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetReuseAddressCommand *pp = omnetpp::fromAnyPtr<UdpSetReuseAddressCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetReuseAddressCommand'", field);
    }
}

Register_Class(UdpJoinMulticastGroupsCommand)

UdpJoinMulticastGroupsCommand::UdpJoinMulticastGroupsCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_JOIN_MCAST_GRP);

}

UdpJoinMulticastGroupsCommand::UdpJoinMulticastGroupsCommand(const UdpJoinMulticastGroupsCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpJoinMulticastGroupsCommand::~UdpJoinMulticastGroupsCommand()
{
    delete [] this->multicastAddr;
    delete [] this->interfaceId;
}

UdpJoinMulticastGroupsCommand& UdpJoinMulticastGroupsCommand::operator=(const UdpJoinMulticastGroupsCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpJoinMulticastGroupsCommand::copy(const UdpJoinMulticastGroupsCommand& other)
{
    delete [] this->multicastAddr;
    this->multicastAddr = (other.multicastAddr_arraysize==0) ? nullptr : new L3Address[other.multicastAddr_arraysize];
    multicastAddr_arraysize = other.multicastAddr_arraysize;
    for (size_t i = 0; i < multicastAddr_arraysize; i++) {
        this->multicastAddr[i] = other.multicastAddr[i];
    }
    delete [] this->interfaceId;
    this->interfaceId = (other.interfaceId_arraysize==0) ? nullptr : new int[other.interfaceId_arraysize];
    interfaceId_arraysize = other.interfaceId_arraysize;
    for (size_t i = 0; i < interfaceId_arraysize; i++) {
        this->interfaceId[i] = other.interfaceId[i];
    }
}

void UdpJoinMulticastGroupsCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    b->pack(multicastAddr_arraysize);
    doParsimArrayPacking(b,this->multicastAddr,multicastAddr_arraysize);
    b->pack(interfaceId_arraysize);
    doParsimArrayPacking(b,this->interfaceId,interfaceId_arraysize);
}

void UdpJoinMulticastGroupsCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    delete [] this->multicastAddr;
    b->unpack(multicastAddr_arraysize);
    if (multicastAddr_arraysize == 0) {
        this->multicastAddr = nullptr;
    } else {
        this->multicastAddr = new L3Address[multicastAddr_arraysize];
        doParsimArrayUnpacking(b,this->multicastAddr,multicastAddr_arraysize);
    }
    delete [] this->interfaceId;
    b->unpack(interfaceId_arraysize);
    if (interfaceId_arraysize == 0) {
        this->interfaceId = nullptr;
    } else {
        this->interfaceId = new int[interfaceId_arraysize];
        doParsimArrayUnpacking(b,this->interfaceId,interfaceId_arraysize);
    }
}

size_t UdpJoinMulticastGroupsCommand::getMulticastAddrArraySize() const
{
    return multicastAddr_arraysize;
}

const L3Address& UdpJoinMulticastGroupsCommand::getMulticastAddr(size_t k) const
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    return this->multicastAddr[k];
}

void UdpJoinMulticastGroupsCommand::setMulticastAddrArraySize(size_t newSize)
{
    L3Address *multicastAddr2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = multicastAddr_arraysize < newSize ? multicastAddr_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

void UdpJoinMulticastGroupsCommand::setMulticastAddr(size_t k, const L3Address& multicastAddr)
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    this->multicastAddr[k] = multicastAddr;
}

void UdpJoinMulticastGroupsCommand::insertMulticastAddr(size_t k, const L3Address& multicastAddr)
{
    if (k > multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    size_t newSize = multicastAddr_arraysize + 1;
    L3Address *multicastAddr2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    multicastAddr2[k] = multicastAddr;
    for (i = k + 1; i < newSize; i++)
        multicastAddr2[i] = this->multicastAddr[i-1];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

void UdpJoinMulticastGroupsCommand::appendMulticastAddr(const L3Address& multicastAddr)
{
    insertMulticastAddr(multicastAddr_arraysize, multicastAddr);
}

void UdpJoinMulticastGroupsCommand::eraseMulticastAddr(size_t k)
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    size_t newSize = multicastAddr_arraysize - 1;
    L3Address *multicastAddr2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    for (i = k; i < newSize; i++)
        multicastAddr2[i] = this->multicastAddr[i+1];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

size_t UdpJoinMulticastGroupsCommand::getInterfaceIdArraySize() const
{
    return interfaceId_arraysize;
}

int UdpJoinMulticastGroupsCommand::getInterfaceId(size_t k) const
{
    if (k >= interfaceId_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)interfaceId_arraysize, (unsigned long)k);
    return this->interfaceId[k];
}

void UdpJoinMulticastGroupsCommand::setInterfaceIdArraySize(size_t newSize)
{
    int *interfaceId2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = interfaceId_arraysize < newSize ? interfaceId_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        interfaceId2[i] = this->interfaceId[i];
    for (size_t i = minSize; i < newSize; i++)
        interfaceId2[i] = 0;
    delete [] this->interfaceId;
    this->interfaceId = interfaceId2;
    interfaceId_arraysize = newSize;
}

void UdpJoinMulticastGroupsCommand::setInterfaceId(size_t k, int interfaceId)
{
    if (k >= interfaceId_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)interfaceId_arraysize, (unsigned long)k);
    this->interfaceId[k] = interfaceId;
}

void UdpJoinMulticastGroupsCommand::insertInterfaceId(size_t k, int interfaceId)
{
    if (k > interfaceId_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)interfaceId_arraysize, (unsigned long)k);
    size_t newSize = interfaceId_arraysize + 1;
    int *interfaceId2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interfaceId2[i] = this->interfaceId[i];
    interfaceId2[k] = interfaceId;
    for (i = k + 1; i < newSize; i++)
        interfaceId2[i] = this->interfaceId[i-1];
    delete [] this->interfaceId;
    this->interfaceId = interfaceId2;
    interfaceId_arraysize = newSize;
}

void UdpJoinMulticastGroupsCommand::appendInterfaceId(int interfaceId)
{
    insertInterfaceId(interfaceId_arraysize, interfaceId);
}

void UdpJoinMulticastGroupsCommand::eraseInterfaceId(size_t k)
{
    if (k >= interfaceId_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)interfaceId_arraysize, (unsigned long)k);
    size_t newSize = interfaceId_arraysize - 1;
    int *interfaceId2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interfaceId2[i] = this->interfaceId[i];
    for (i = k; i < newSize; i++)
        interfaceId2[i] = this->interfaceId[i+1];
    delete [] this->interfaceId;
    this->interfaceId = interfaceId2;
    interfaceId_arraysize = newSize;
}

class UdpJoinMulticastGroupsCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_multicastAddr,
        FIELD_interfaceId,
    };
  public:
    UdpJoinMulticastGroupsCommandDescriptor();
    virtual ~UdpJoinMulticastGroupsCommandDescriptor();

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

Register_ClassDescriptor(UdpJoinMulticastGroupsCommandDescriptor)

UdpJoinMulticastGroupsCommandDescriptor::UdpJoinMulticastGroupsCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpJoinMulticastGroupsCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpJoinMulticastGroupsCommandDescriptor::~UdpJoinMulticastGroupsCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpJoinMulticastGroupsCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpJoinMulticastGroupsCommand *>(obj)!=nullptr;
}

const char **UdpJoinMulticastGroupsCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpJoinMulticastGroupsCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpJoinMulticastGroupsCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int UdpJoinMulticastGroupsCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_multicastAddr
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_interfaceId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *UdpJoinMulticastGroupsCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "multicastAddr",
        "interfaceId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int UdpJoinMulticastGroupsCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpJoinMulticastGroupsCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_multicastAddr
        "int",    // FIELD_interfaceId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpJoinMulticastGroupsCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpJoinMulticastGroupsCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpJoinMulticastGroupsCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return pp->getMulticastAddrArraySize();
        case FIELD_interfaceId: return pp->getInterfaceIdArraySize();
        default: return 0;
    }
}

void UdpJoinMulticastGroupsCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: pp->setMulticastAddrArraySize(size); break;
        case FIELD_interfaceId: pp->setInterfaceIdArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpJoinMulticastGroupsCommand'", field);
    }
}

const char *UdpJoinMulticastGroupsCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpJoinMulticastGroupsCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return pp->getMulticastAddr(i).str();
        case FIELD_interfaceId: return long2string(pp->getInterfaceId(i));
        default: return "";
    }
}

void UdpJoinMulticastGroupsCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastGroupsCommand'", field);
    }
}

omnetpp::cValue UdpJoinMulticastGroupsCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr(i)); break;
        case FIELD_interfaceId: return pp->getInterfaceId(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpJoinMulticastGroupsCommand' as cValue -- field index out of range?", field);
    }
}

void UdpJoinMulticastGroupsCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastGroupsCommand'", field);
    }
}

const char *UdpJoinMulticastGroupsCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpJoinMulticastGroupsCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpJoinMulticastGroupsCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastGroupsCommand'", field);
    }
}

Register_Class(UdpLeaveMulticastGroupsCommand)

UdpLeaveMulticastGroupsCommand::UdpLeaveMulticastGroupsCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_LEAVE_MCAST_GRP);

}

UdpLeaveMulticastGroupsCommand::UdpLeaveMulticastGroupsCommand(const UdpLeaveMulticastGroupsCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpLeaveMulticastGroupsCommand::~UdpLeaveMulticastGroupsCommand()
{
    delete [] this->multicastAddr;
}

UdpLeaveMulticastGroupsCommand& UdpLeaveMulticastGroupsCommand::operator=(const UdpLeaveMulticastGroupsCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpLeaveMulticastGroupsCommand::copy(const UdpLeaveMulticastGroupsCommand& other)
{
    delete [] this->multicastAddr;
    this->multicastAddr = (other.multicastAddr_arraysize==0) ? nullptr : new L3Address[other.multicastAddr_arraysize];
    multicastAddr_arraysize = other.multicastAddr_arraysize;
    for (size_t i = 0; i < multicastAddr_arraysize; i++) {
        this->multicastAddr[i] = other.multicastAddr[i];
    }
}

void UdpLeaveMulticastGroupsCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    b->pack(multicastAddr_arraysize);
    doParsimArrayPacking(b,this->multicastAddr,multicastAddr_arraysize);
}

void UdpLeaveMulticastGroupsCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    delete [] this->multicastAddr;
    b->unpack(multicastAddr_arraysize);
    if (multicastAddr_arraysize == 0) {
        this->multicastAddr = nullptr;
    } else {
        this->multicastAddr = new L3Address[multicastAddr_arraysize];
        doParsimArrayUnpacking(b,this->multicastAddr,multicastAddr_arraysize);
    }
}

size_t UdpLeaveMulticastGroupsCommand::getMulticastAddrArraySize() const
{
    return multicastAddr_arraysize;
}

const L3Address& UdpLeaveMulticastGroupsCommand::getMulticastAddr(size_t k) const
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    return this->multicastAddr[k];
}

void UdpLeaveMulticastGroupsCommand::setMulticastAddrArraySize(size_t newSize)
{
    L3Address *multicastAddr2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = multicastAddr_arraysize < newSize ? multicastAddr_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

void UdpLeaveMulticastGroupsCommand::setMulticastAddr(size_t k, const L3Address& multicastAddr)
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    this->multicastAddr[k] = multicastAddr;
}

void UdpLeaveMulticastGroupsCommand::insertMulticastAddr(size_t k, const L3Address& multicastAddr)
{
    if (k > multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    size_t newSize = multicastAddr_arraysize + 1;
    L3Address *multicastAddr2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    multicastAddr2[k] = multicastAddr;
    for (i = k + 1; i < newSize; i++)
        multicastAddr2[i] = this->multicastAddr[i-1];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

void UdpLeaveMulticastGroupsCommand::appendMulticastAddr(const L3Address& multicastAddr)
{
    insertMulticastAddr(multicastAddr_arraysize, multicastAddr);
}

void UdpLeaveMulticastGroupsCommand::eraseMulticastAddr(size_t k)
{
    if (k >= multicastAddr_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)multicastAddr_arraysize, (unsigned long)k);
    size_t newSize = multicastAddr_arraysize - 1;
    L3Address *multicastAddr2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        multicastAddr2[i] = this->multicastAddr[i];
    for (i = k; i < newSize; i++)
        multicastAddr2[i] = this->multicastAddr[i+1];
    delete [] this->multicastAddr;
    this->multicastAddr = multicastAddr2;
    multicastAddr_arraysize = newSize;
}

class UdpLeaveMulticastGroupsCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_multicastAddr,
    };
  public:
    UdpLeaveMulticastGroupsCommandDescriptor();
    virtual ~UdpLeaveMulticastGroupsCommandDescriptor();

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

Register_ClassDescriptor(UdpLeaveMulticastGroupsCommandDescriptor)

UdpLeaveMulticastGroupsCommandDescriptor::UdpLeaveMulticastGroupsCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpLeaveMulticastGroupsCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpLeaveMulticastGroupsCommandDescriptor::~UdpLeaveMulticastGroupsCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpLeaveMulticastGroupsCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpLeaveMulticastGroupsCommand *>(obj)!=nullptr;
}

const char **UdpLeaveMulticastGroupsCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpLeaveMulticastGroupsCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpLeaveMulticastGroupsCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int UdpLeaveMulticastGroupsCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_multicastAddr
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *UdpLeaveMulticastGroupsCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "multicastAddr",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int UdpLeaveMulticastGroupsCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpLeaveMulticastGroupsCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_multicastAddr
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpLeaveMulticastGroupsCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpLeaveMulticastGroupsCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpLeaveMulticastGroupsCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return pp->getMulticastAddrArraySize();
        default: return 0;
    }
}

void UdpLeaveMulticastGroupsCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: pp->setMulticastAddrArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpLeaveMulticastGroupsCommand'", field);
    }
}

const char *UdpLeaveMulticastGroupsCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpLeaveMulticastGroupsCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return pp->getMulticastAddr(i).str();
        default: return "";
    }
}

void UdpLeaveMulticastGroupsCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastGroupsCommand'", field);
    }
}

omnetpp::cValue UdpLeaveMulticastGroupsCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpLeaveMulticastGroupsCommand' as cValue -- field index out of range?", field);
    }
}

void UdpLeaveMulticastGroupsCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastGroupsCommand'", field);
    }
}

const char *UdpLeaveMulticastGroupsCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpLeaveMulticastGroupsCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpLeaveMulticastGroupsCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastGroupsCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastGroupsCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastGroupsCommand'", field);
    }
}

Register_Class(UdpBlockMulticastSourcesCommand)

UdpBlockMulticastSourcesCommand::UdpBlockMulticastSourcesCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_BLOCK_MCAST_SRC);

}

UdpBlockMulticastSourcesCommand::UdpBlockMulticastSourcesCommand(const UdpBlockMulticastSourcesCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpBlockMulticastSourcesCommand::~UdpBlockMulticastSourcesCommand()
{
    delete [] this->sourceList;
}

UdpBlockMulticastSourcesCommand& UdpBlockMulticastSourcesCommand::operator=(const UdpBlockMulticastSourcesCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpBlockMulticastSourcesCommand::copy(const UdpBlockMulticastSourcesCommand& other)
{
    this->interfaceId = other.interfaceId;
    this->multicastAddr = other.multicastAddr;
    delete [] this->sourceList;
    this->sourceList = (other.sourceList_arraysize==0) ? nullptr : new L3Address[other.sourceList_arraysize];
    sourceList_arraysize = other.sourceList_arraysize;
    for (size_t i = 0; i < sourceList_arraysize; i++) {
        this->sourceList[i] = other.sourceList[i];
    }
}

void UdpBlockMulticastSourcesCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->multicastAddr);
    b->pack(sourceList_arraysize);
    doParsimArrayPacking(b,this->sourceList,sourceList_arraysize);
}

void UdpBlockMulticastSourcesCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->multicastAddr);
    delete [] this->sourceList;
    b->unpack(sourceList_arraysize);
    if (sourceList_arraysize == 0) {
        this->sourceList = nullptr;
    } else {
        this->sourceList = new L3Address[sourceList_arraysize];
        doParsimArrayUnpacking(b,this->sourceList,sourceList_arraysize);
    }
}

int UdpBlockMulticastSourcesCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpBlockMulticastSourcesCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

const L3Address& UdpBlockMulticastSourcesCommand::getMulticastAddr() const
{
    return this->multicastAddr;
}

void UdpBlockMulticastSourcesCommand::setMulticastAddr(const L3Address& multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

size_t UdpBlockMulticastSourcesCommand::getSourceListArraySize() const
{
    return sourceList_arraysize;
}

const L3Address& UdpBlockMulticastSourcesCommand::getSourceList(size_t k) const
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    return this->sourceList[k];
}

void UdpBlockMulticastSourcesCommand::setSourceListArraySize(size_t newSize)
{
    L3Address *sourceList2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = sourceList_arraysize < newSize ? sourceList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sourceList2[i] = this->sourceList[i];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpBlockMulticastSourcesCommand::setSourceList(size_t k, const L3Address& sourceList)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    this->sourceList[k] = sourceList;
}

void UdpBlockMulticastSourcesCommand::insertSourceList(size_t k, const L3Address& sourceList)
{
    if (k > sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize + 1;
    L3Address *sourceList2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    sourceList2[k] = sourceList;
    for (i = k + 1; i < newSize; i++)
        sourceList2[i] = this->sourceList[i-1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpBlockMulticastSourcesCommand::appendSourceList(const L3Address& sourceList)
{
    insertSourceList(sourceList_arraysize, sourceList);
}

void UdpBlockMulticastSourcesCommand::eraseSourceList(size_t k)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize - 1;
    L3Address *sourceList2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    for (i = k; i < newSize; i++)
        sourceList2[i] = this->sourceList[i+1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

class UdpBlockMulticastSourcesCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
        FIELD_multicastAddr,
        FIELD_sourceList,
    };
  public:
    UdpBlockMulticastSourcesCommandDescriptor();
    virtual ~UdpBlockMulticastSourcesCommandDescriptor();

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

Register_ClassDescriptor(UdpBlockMulticastSourcesCommandDescriptor)

UdpBlockMulticastSourcesCommandDescriptor::UdpBlockMulticastSourcesCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpBlockMulticastSourcesCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpBlockMulticastSourcesCommandDescriptor::~UdpBlockMulticastSourcesCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpBlockMulticastSourcesCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpBlockMulticastSourcesCommand *>(obj)!=nullptr;
}

const char **UdpBlockMulticastSourcesCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpBlockMulticastSourcesCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpBlockMulticastSourcesCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int UdpBlockMulticastSourcesCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
        0,    // FIELD_multicastAddr
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *UdpBlockMulticastSourcesCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
        "multicastAddr",
        "sourceList",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int UdpBlockMulticastSourcesCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpBlockMulticastSourcesCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
        "inet::L3Address",    // FIELD_multicastAddr
        "inet::L3Address",    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpBlockMulticastSourcesCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpBlockMulticastSourcesCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpBlockMulticastSourcesCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return pp->getSourceListArraySize();
        default: return 0;
    }
}

void UdpBlockMulticastSourcesCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: pp->setSourceListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpBlockMulticastSourcesCommand'", field);
    }
}

const char *UdpBlockMulticastSourcesCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpBlockMulticastSourcesCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_multicastAddr: return pp->getMulticastAddr().str();
        case FIELD_sourceList: return pp->getSourceList(i).str();
        default: return "";
    }
}

void UdpBlockMulticastSourcesCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBlockMulticastSourcesCommand'", field);
    }
}

omnetpp::cValue UdpBlockMulticastSourcesCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpBlockMulticastSourcesCommand' as cValue -- field index out of range?", field);
    }
}

void UdpBlockMulticastSourcesCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBlockMulticastSourcesCommand'", field);
    }
}

const char *UdpBlockMulticastSourcesCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpBlockMulticastSourcesCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpBlockMulticastSourcesCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpBlockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpBlockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpBlockMulticastSourcesCommand'", field);
    }
}

Register_Class(UdpUnblockMulticastSourcesCommand)

UdpUnblockMulticastSourcesCommand::UdpUnblockMulticastSourcesCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_UNBLOCK_MCAST_SRC);

}

UdpUnblockMulticastSourcesCommand::UdpUnblockMulticastSourcesCommand(const UdpUnblockMulticastSourcesCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpUnblockMulticastSourcesCommand::~UdpUnblockMulticastSourcesCommand()
{
    delete [] this->sourceList;
}

UdpUnblockMulticastSourcesCommand& UdpUnblockMulticastSourcesCommand::operator=(const UdpUnblockMulticastSourcesCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpUnblockMulticastSourcesCommand::copy(const UdpUnblockMulticastSourcesCommand& other)
{
    this->interfaceId = other.interfaceId;
    this->multicastAddr = other.multicastAddr;
    delete [] this->sourceList;
    this->sourceList = (other.sourceList_arraysize==0) ? nullptr : new L3Address[other.sourceList_arraysize];
    sourceList_arraysize = other.sourceList_arraysize;
    for (size_t i = 0; i < sourceList_arraysize; i++) {
        this->sourceList[i] = other.sourceList[i];
    }
}

void UdpUnblockMulticastSourcesCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->multicastAddr);
    b->pack(sourceList_arraysize);
    doParsimArrayPacking(b,this->sourceList,sourceList_arraysize);
}

void UdpUnblockMulticastSourcesCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->multicastAddr);
    delete [] this->sourceList;
    b->unpack(sourceList_arraysize);
    if (sourceList_arraysize == 0) {
        this->sourceList = nullptr;
    } else {
        this->sourceList = new L3Address[sourceList_arraysize];
        doParsimArrayUnpacking(b,this->sourceList,sourceList_arraysize);
    }
}

int UdpUnblockMulticastSourcesCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpUnblockMulticastSourcesCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

const L3Address& UdpUnblockMulticastSourcesCommand::getMulticastAddr() const
{
    return this->multicastAddr;
}

void UdpUnblockMulticastSourcesCommand::setMulticastAddr(const L3Address& multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

size_t UdpUnblockMulticastSourcesCommand::getSourceListArraySize() const
{
    return sourceList_arraysize;
}

const L3Address& UdpUnblockMulticastSourcesCommand::getSourceList(size_t k) const
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    return this->sourceList[k];
}

void UdpUnblockMulticastSourcesCommand::setSourceListArraySize(size_t newSize)
{
    L3Address *sourceList2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = sourceList_arraysize < newSize ? sourceList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sourceList2[i] = this->sourceList[i];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpUnblockMulticastSourcesCommand::setSourceList(size_t k, const L3Address& sourceList)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    this->sourceList[k] = sourceList;
}

void UdpUnblockMulticastSourcesCommand::insertSourceList(size_t k, const L3Address& sourceList)
{
    if (k > sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize + 1;
    L3Address *sourceList2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    sourceList2[k] = sourceList;
    for (i = k + 1; i < newSize; i++)
        sourceList2[i] = this->sourceList[i-1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpUnblockMulticastSourcesCommand::appendSourceList(const L3Address& sourceList)
{
    insertSourceList(sourceList_arraysize, sourceList);
}

void UdpUnblockMulticastSourcesCommand::eraseSourceList(size_t k)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize - 1;
    L3Address *sourceList2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    for (i = k; i < newSize; i++)
        sourceList2[i] = this->sourceList[i+1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

class UdpUnblockMulticastSourcesCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
        FIELD_multicastAddr,
        FIELD_sourceList,
    };
  public:
    UdpUnblockMulticastSourcesCommandDescriptor();
    virtual ~UdpUnblockMulticastSourcesCommandDescriptor();

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

Register_ClassDescriptor(UdpUnblockMulticastSourcesCommandDescriptor)

UdpUnblockMulticastSourcesCommandDescriptor::UdpUnblockMulticastSourcesCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpUnblockMulticastSourcesCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpUnblockMulticastSourcesCommandDescriptor::~UdpUnblockMulticastSourcesCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpUnblockMulticastSourcesCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpUnblockMulticastSourcesCommand *>(obj)!=nullptr;
}

const char **UdpUnblockMulticastSourcesCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpUnblockMulticastSourcesCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpUnblockMulticastSourcesCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int UdpUnblockMulticastSourcesCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
        0,    // FIELD_multicastAddr
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *UdpUnblockMulticastSourcesCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
        "multicastAddr",
        "sourceList",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int UdpUnblockMulticastSourcesCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpUnblockMulticastSourcesCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
        "inet::L3Address",    // FIELD_multicastAddr
        "inet::L3Address",    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpUnblockMulticastSourcesCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpUnblockMulticastSourcesCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpUnblockMulticastSourcesCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return pp->getSourceListArraySize();
        default: return 0;
    }
}

void UdpUnblockMulticastSourcesCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: pp->setSourceListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpUnblockMulticastSourcesCommand'", field);
    }
}

const char *UdpUnblockMulticastSourcesCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpUnblockMulticastSourcesCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_multicastAddr: return pp->getMulticastAddr().str();
        case FIELD_sourceList: return pp->getSourceList(i).str();
        default: return "";
    }
}

void UdpUnblockMulticastSourcesCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpUnblockMulticastSourcesCommand'", field);
    }
}

omnetpp::cValue UdpUnblockMulticastSourcesCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpUnblockMulticastSourcesCommand' as cValue -- field index out of range?", field);
    }
}

void UdpUnblockMulticastSourcesCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpUnblockMulticastSourcesCommand'", field);
    }
}

const char *UdpUnblockMulticastSourcesCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpUnblockMulticastSourcesCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpUnblockMulticastSourcesCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpUnblockMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpUnblockMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpUnblockMulticastSourcesCommand'", field);
    }
}

Register_Class(UdpJoinMulticastSourcesCommand)

UdpJoinMulticastSourcesCommand::UdpJoinMulticastSourcesCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_JOIN_MCAST_SRC);

}

UdpJoinMulticastSourcesCommand::UdpJoinMulticastSourcesCommand(const UdpJoinMulticastSourcesCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpJoinMulticastSourcesCommand::~UdpJoinMulticastSourcesCommand()
{
    delete [] this->sourceList;
}

UdpJoinMulticastSourcesCommand& UdpJoinMulticastSourcesCommand::operator=(const UdpJoinMulticastSourcesCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpJoinMulticastSourcesCommand::copy(const UdpJoinMulticastSourcesCommand& other)
{
    this->interfaceId = other.interfaceId;
    this->multicastAddr = other.multicastAddr;
    delete [] this->sourceList;
    this->sourceList = (other.sourceList_arraysize==0) ? nullptr : new L3Address[other.sourceList_arraysize];
    sourceList_arraysize = other.sourceList_arraysize;
    for (size_t i = 0; i < sourceList_arraysize; i++) {
        this->sourceList[i] = other.sourceList[i];
    }
}

void UdpJoinMulticastSourcesCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->multicastAddr);
    b->pack(sourceList_arraysize);
    doParsimArrayPacking(b,this->sourceList,sourceList_arraysize);
}

void UdpJoinMulticastSourcesCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->multicastAddr);
    delete [] this->sourceList;
    b->unpack(sourceList_arraysize);
    if (sourceList_arraysize == 0) {
        this->sourceList = nullptr;
    } else {
        this->sourceList = new L3Address[sourceList_arraysize];
        doParsimArrayUnpacking(b,this->sourceList,sourceList_arraysize);
    }
}

int UdpJoinMulticastSourcesCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpJoinMulticastSourcesCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

const L3Address& UdpJoinMulticastSourcesCommand::getMulticastAddr() const
{
    return this->multicastAddr;
}

void UdpJoinMulticastSourcesCommand::setMulticastAddr(const L3Address& multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

size_t UdpJoinMulticastSourcesCommand::getSourceListArraySize() const
{
    return sourceList_arraysize;
}

const L3Address& UdpJoinMulticastSourcesCommand::getSourceList(size_t k) const
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    return this->sourceList[k];
}

void UdpJoinMulticastSourcesCommand::setSourceListArraySize(size_t newSize)
{
    L3Address *sourceList2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = sourceList_arraysize < newSize ? sourceList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sourceList2[i] = this->sourceList[i];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpJoinMulticastSourcesCommand::setSourceList(size_t k, const L3Address& sourceList)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    this->sourceList[k] = sourceList;
}

void UdpJoinMulticastSourcesCommand::insertSourceList(size_t k, const L3Address& sourceList)
{
    if (k > sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize + 1;
    L3Address *sourceList2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    sourceList2[k] = sourceList;
    for (i = k + 1; i < newSize; i++)
        sourceList2[i] = this->sourceList[i-1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpJoinMulticastSourcesCommand::appendSourceList(const L3Address& sourceList)
{
    insertSourceList(sourceList_arraysize, sourceList);
}

void UdpJoinMulticastSourcesCommand::eraseSourceList(size_t k)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize - 1;
    L3Address *sourceList2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    for (i = k; i < newSize; i++)
        sourceList2[i] = this->sourceList[i+1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

class UdpJoinMulticastSourcesCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
        FIELD_multicastAddr,
        FIELD_sourceList,
    };
  public:
    UdpJoinMulticastSourcesCommandDescriptor();
    virtual ~UdpJoinMulticastSourcesCommandDescriptor();

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

Register_ClassDescriptor(UdpJoinMulticastSourcesCommandDescriptor)

UdpJoinMulticastSourcesCommandDescriptor::UdpJoinMulticastSourcesCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpJoinMulticastSourcesCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpJoinMulticastSourcesCommandDescriptor::~UdpJoinMulticastSourcesCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpJoinMulticastSourcesCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpJoinMulticastSourcesCommand *>(obj)!=nullptr;
}

const char **UdpJoinMulticastSourcesCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpJoinMulticastSourcesCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpJoinMulticastSourcesCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int UdpJoinMulticastSourcesCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
        0,    // FIELD_multicastAddr
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *UdpJoinMulticastSourcesCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
        "multicastAddr",
        "sourceList",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int UdpJoinMulticastSourcesCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpJoinMulticastSourcesCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
        "inet::L3Address",    // FIELD_multicastAddr
        "inet::L3Address",    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpJoinMulticastSourcesCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpJoinMulticastSourcesCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpJoinMulticastSourcesCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return pp->getSourceListArraySize();
        default: return 0;
    }
}

void UdpJoinMulticastSourcesCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: pp->setSourceListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpJoinMulticastSourcesCommand'", field);
    }
}

const char *UdpJoinMulticastSourcesCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpJoinMulticastSourcesCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_multicastAddr: return pp->getMulticastAddr().str();
        case FIELD_sourceList: return pp->getSourceList(i).str();
        default: return "";
    }
}

void UdpJoinMulticastSourcesCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastSourcesCommand'", field);
    }
}

omnetpp::cValue UdpJoinMulticastSourcesCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpJoinMulticastSourcesCommand' as cValue -- field index out of range?", field);
    }
}

void UdpJoinMulticastSourcesCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastSourcesCommand'", field);
    }
}

const char *UdpJoinMulticastSourcesCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpJoinMulticastSourcesCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpJoinMulticastSourcesCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpJoinMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpJoinMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpJoinMulticastSourcesCommand'", field);
    }
}

Register_Class(UdpLeaveMulticastSourcesCommand)

UdpLeaveMulticastSourcesCommand::UdpLeaveMulticastSourcesCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_LEAVE_MCAST_SRC);

}

UdpLeaveMulticastSourcesCommand::UdpLeaveMulticastSourcesCommand(const UdpLeaveMulticastSourcesCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpLeaveMulticastSourcesCommand::~UdpLeaveMulticastSourcesCommand()
{
    delete [] this->sourceList;
}

UdpLeaveMulticastSourcesCommand& UdpLeaveMulticastSourcesCommand::operator=(const UdpLeaveMulticastSourcesCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpLeaveMulticastSourcesCommand::copy(const UdpLeaveMulticastSourcesCommand& other)
{
    this->interfaceId = other.interfaceId;
    this->multicastAddr = other.multicastAddr;
    delete [] this->sourceList;
    this->sourceList = (other.sourceList_arraysize==0) ? nullptr : new L3Address[other.sourceList_arraysize];
    sourceList_arraysize = other.sourceList_arraysize;
    for (size_t i = 0; i < sourceList_arraysize; i++) {
        this->sourceList[i] = other.sourceList[i];
    }
}

void UdpLeaveMulticastSourcesCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->multicastAddr);
    b->pack(sourceList_arraysize);
    doParsimArrayPacking(b,this->sourceList,sourceList_arraysize);
}

void UdpLeaveMulticastSourcesCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->multicastAddr);
    delete [] this->sourceList;
    b->unpack(sourceList_arraysize);
    if (sourceList_arraysize == 0) {
        this->sourceList = nullptr;
    } else {
        this->sourceList = new L3Address[sourceList_arraysize];
        doParsimArrayUnpacking(b,this->sourceList,sourceList_arraysize);
    }
}

int UdpLeaveMulticastSourcesCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpLeaveMulticastSourcesCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

const L3Address& UdpLeaveMulticastSourcesCommand::getMulticastAddr() const
{
    return this->multicastAddr;
}

void UdpLeaveMulticastSourcesCommand::setMulticastAddr(const L3Address& multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

size_t UdpLeaveMulticastSourcesCommand::getSourceListArraySize() const
{
    return sourceList_arraysize;
}

const L3Address& UdpLeaveMulticastSourcesCommand::getSourceList(size_t k) const
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    return this->sourceList[k];
}

void UdpLeaveMulticastSourcesCommand::setSourceListArraySize(size_t newSize)
{
    L3Address *sourceList2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = sourceList_arraysize < newSize ? sourceList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sourceList2[i] = this->sourceList[i];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpLeaveMulticastSourcesCommand::setSourceList(size_t k, const L3Address& sourceList)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    this->sourceList[k] = sourceList;
}

void UdpLeaveMulticastSourcesCommand::insertSourceList(size_t k, const L3Address& sourceList)
{
    if (k > sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize + 1;
    L3Address *sourceList2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    sourceList2[k] = sourceList;
    for (i = k + 1; i < newSize; i++)
        sourceList2[i] = this->sourceList[i-1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpLeaveMulticastSourcesCommand::appendSourceList(const L3Address& sourceList)
{
    insertSourceList(sourceList_arraysize, sourceList);
}

void UdpLeaveMulticastSourcesCommand::eraseSourceList(size_t k)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize - 1;
    L3Address *sourceList2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    for (i = k; i < newSize; i++)
        sourceList2[i] = this->sourceList[i+1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

class UdpLeaveMulticastSourcesCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
        FIELD_multicastAddr,
        FIELD_sourceList,
    };
  public:
    UdpLeaveMulticastSourcesCommandDescriptor();
    virtual ~UdpLeaveMulticastSourcesCommandDescriptor();

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

Register_ClassDescriptor(UdpLeaveMulticastSourcesCommandDescriptor)

UdpLeaveMulticastSourcesCommandDescriptor::UdpLeaveMulticastSourcesCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpLeaveMulticastSourcesCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpLeaveMulticastSourcesCommandDescriptor::~UdpLeaveMulticastSourcesCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpLeaveMulticastSourcesCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpLeaveMulticastSourcesCommand *>(obj)!=nullptr;
}

const char **UdpLeaveMulticastSourcesCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpLeaveMulticastSourcesCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpLeaveMulticastSourcesCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int UdpLeaveMulticastSourcesCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
        0,    // FIELD_multicastAddr
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *UdpLeaveMulticastSourcesCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
        "multicastAddr",
        "sourceList",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int UdpLeaveMulticastSourcesCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpLeaveMulticastSourcesCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
        "inet::L3Address",    // FIELD_multicastAddr
        "inet::L3Address",    // FIELD_sourceList
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpLeaveMulticastSourcesCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *UdpLeaveMulticastSourcesCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int UdpLeaveMulticastSourcesCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return pp->getSourceListArraySize();
        default: return 0;
    }
}

void UdpLeaveMulticastSourcesCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: pp->setSourceListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpLeaveMulticastSourcesCommand'", field);
    }
}

const char *UdpLeaveMulticastSourcesCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpLeaveMulticastSourcesCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_multicastAddr: return pp->getMulticastAddr().str();
        case FIELD_sourceList: return pp->getSourceList(i).str();
        default: return "";
    }
}

void UdpLeaveMulticastSourcesCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastSourcesCommand'", field);
    }
}

omnetpp::cValue UdpLeaveMulticastSourcesCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpLeaveMulticastSourcesCommand' as cValue -- field index out of range?", field);
    }
}

void UdpLeaveMulticastSourcesCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastSourcesCommand'", field);
    }
}

const char *UdpLeaveMulticastSourcesCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpLeaveMulticastSourcesCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpLeaveMulticastSourcesCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpLeaveMulticastSourcesCommand *pp = omnetpp::fromAnyPtr<UdpLeaveMulticastSourcesCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpLeaveMulticastSourcesCommand'", field);
    }
}

Register_Enum(inet::UdpSourceFilterMode, (inet::UdpSourceFilterMode::UDP_INCLUDE_MCAST_SOURCES, inet::UdpSourceFilterMode::UDP_EXCLUDE_MCAST_SOURCES));

Register_Class(UdpSetMulticastSourceFilterCommand)

UdpSetMulticastSourceFilterCommand::UdpSetMulticastSourceFilterCommand() : ::inet::UdpSetOptionCommand()
{
    this->setOptionCode(UDP_C_SETOPTION_SET_MCAST_SRC_FILTER);

}

UdpSetMulticastSourceFilterCommand::UdpSetMulticastSourceFilterCommand(const UdpSetMulticastSourceFilterCommand& other) : ::inet::UdpSetOptionCommand(other)
{
    copy(other);
}

UdpSetMulticastSourceFilterCommand::~UdpSetMulticastSourceFilterCommand()
{
    delete [] this->sourceList;
}

UdpSetMulticastSourceFilterCommand& UdpSetMulticastSourceFilterCommand::operator=(const UdpSetMulticastSourceFilterCommand& other)
{
    if (this == &other) return *this;
    ::inet::UdpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void UdpSetMulticastSourceFilterCommand::copy(const UdpSetMulticastSourceFilterCommand& other)
{
    this->interfaceId = other.interfaceId;
    this->multicastAddr = other.multicastAddr;
    this->filterMode = other.filterMode;
    delete [] this->sourceList;
    this->sourceList = (other.sourceList_arraysize==0) ? nullptr : new L3Address[other.sourceList_arraysize];
    sourceList_arraysize = other.sourceList_arraysize;
    for (size_t i = 0; i < sourceList_arraysize; i++) {
        this->sourceList[i] = other.sourceList[i];
    }
}

void UdpSetMulticastSourceFilterCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::UdpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->multicastAddr);
    doParsimPacking(b,this->filterMode);
    b->pack(sourceList_arraysize);
    doParsimArrayPacking(b,this->sourceList,sourceList_arraysize);
}

void UdpSetMulticastSourceFilterCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::UdpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->multicastAddr);
    doParsimUnpacking(b,this->filterMode);
    delete [] this->sourceList;
    b->unpack(sourceList_arraysize);
    if (sourceList_arraysize == 0) {
        this->sourceList = nullptr;
    } else {
        this->sourceList = new L3Address[sourceList_arraysize];
        doParsimArrayUnpacking(b,this->sourceList,sourceList_arraysize);
    }
}

int UdpSetMulticastSourceFilterCommand::getInterfaceId() const
{
    return this->interfaceId;
}

void UdpSetMulticastSourceFilterCommand::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

const L3Address& UdpSetMulticastSourceFilterCommand::getMulticastAddr() const
{
    return this->multicastAddr;
}

void UdpSetMulticastSourceFilterCommand::setMulticastAddr(const L3Address& multicastAddr)
{
    this->multicastAddr = multicastAddr;
}

UdpSourceFilterMode UdpSetMulticastSourceFilterCommand::getFilterMode() const
{
    return this->filterMode;
}

void UdpSetMulticastSourceFilterCommand::setFilterMode(UdpSourceFilterMode filterMode)
{
    this->filterMode = filterMode;
}

size_t UdpSetMulticastSourceFilterCommand::getSourceListArraySize() const
{
    return sourceList_arraysize;
}

const L3Address& UdpSetMulticastSourceFilterCommand::getSourceList(size_t k) const
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    return this->sourceList[k];
}

void UdpSetMulticastSourceFilterCommand::setSourceListArraySize(size_t newSize)
{
    L3Address *sourceList2 = (newSize==0) ? nullptr : new L3Address[newSize];
    size_t minSize = sourceList_arraysize < newSize ? sourceList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sourceList2[i] = this->sourceList[i];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpSetMulticastSourceFilterCommand::setSourceList(size_t k, const L3Address& sourceList)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    this->sourceList[k] = sourceList;
}

void UdpSetMulticastSourceFilterCommand::insertSourceList(size_t k, const L3Address& sourceList)
{
    if (k > sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize + 1;
    L3Address *sourceList2 = new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    sourceList2[k] = sourceList;
    for (i = k + 1; i < newSize; i++)
        sourceList2[i] = this->sourceList[i-1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

void UdpSetMulticastSourceFilterCommand::appendSourceList(const L3Address& sourceList)
{
    insertSourceList(sourceList_arraysize, sourceList);
}

void UdpSetMulticastSourceFilterCommand::eraseSourceList(size_t k)
{
    if (k >= sourceList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sourceList_arraysize, (unsigned long)k);
    size_t newSize = sourceList_arraysize - 1;
    L3Address *sourceList2 = (newSize == 0) ? nullptr : new L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sourceList2[i] = this->sourceList[i];
    for (i = k; i < newSize; i++)
        sourceList2[i] = this->sourceList[i+1];
    delete [] this->sourceList;
    this->sourceList = sourceList2;
    sourceList_arraysize = newSize;
}

class UdpSetMulticastSourceFilterCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceId,
        FIELD_multicastAddr,
        FIELD_filterMode,
        FIELD_sourceList,
    };
  public:
    UdpSetMulticastSourceFilterCommandDescriptor();
    virtual ~UdpSetMulticastSourceFilterCommandDescriptor();

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

Register_ClassDescriptor(UdpSetMulticastSourceFilterCommandDescriptor)

UdpSetMulticastSourceFilterCommandDescriptor::UdpSetMulticastSourceFilterCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::UdpSetMulticastSourceFilterCommand)), "inet::UdpSetOptionCommand")
{
    propertyNames = nullptr;
}

UdpSetMulticastSourceFilterCommandDescriptor::~UdpSetMulticastSourceFilterCommandDescriptor()
{
    delete[] propertyNames;
}

bool UdpSetMulticastSourceFilterCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UdpSetMulticastSourceFilterCommand *>(obj)!=nullptr;
}

const char **UdpSetMulticastSourceFilterCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UdpSetMulticastSourceFilterCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int UdpSetMulticastSourceFilterCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceId
        0,    // FIELD_multicastAddr
        0,    // FIELD_filterMode
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_sourceList
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceId",
        "multicastAddr",
        "filterMode",
        "sourceList",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int UdpSetMulticastSourceFilterCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multicastAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "filterMode") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_interfaceId
        "inet::L3Address",    // FIELD_multicastAddr
        "inet::UdpSourceFilterMode",    // FIELD_filterMode
        "inet::L3Address",    // FIELD_sourceList
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **UdpSetMulticastSourceFilterCommandDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_filterMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_filterMode:
            if (!strcmp(propertyName, "enum")) return "inet::UdpSourceFilterMode";
            return nullptr;
        default: return nullptr;
    }
}

int UdpSetMulticastSourceFilterCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return pp->getSourceListArraySize();
        default: return 0;
    }
}

void UdpSetMulticastSourceFilterCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: pp->setSourceListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UdpSetMulticastSourceFilterCommand'", field);
    }
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UdpSetMulticastSourceFilterCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_multicastAddr: return pp->getMulticastAddr().str();
        case FIELD_filterMode: return enum2string(pp->getFilterMode(), "inet::UdpSourceFilterMode");
        case FIELD_sourceList: return pp->getSourceList(i).str();
        default: return "";
    }
}

void UdpSetMulticastSourceFilterCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastSourceFilterCommand'", field);
    }
}

omnetpp::cValue UdpSetMulticastSourceFilterCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_filterMode: return static_cast<int>(pp->getFilterMode());
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UdpSetMulticastSourceFilterCommand' as cValue -- field index out of range?", field);
    }
}

void UdpSetMulticastSourceFilterCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastSourceFilterCommand'", field);
    }
}

const char *UdpSetMulticastSourceFilterCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UdpSetMulticastSourceFilterCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        case FIELD_multicastAddr: return omnetpp::toAnyPtr(&pp->getMulticastAddr()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UdpSetMulticastSourceFilterCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UdpSetMulticastSourceFilterCommand *pp = omnetpp::fromAnyPtr<UdpSetMulticastSourceFilterCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UdpSetMulticastSourceFilterCommand'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

