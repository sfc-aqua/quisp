//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ldp/LdpPacket.msg.
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
#include "LdpPacket_m.h"

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

Register_Enum(inet::LdpMessageTypes, (inet::LdpMessageTypes::NOTIFICATION, inet::LdpMessageTypes::HELLO, inet::LdpMessageTypes::INITIALIZATION, inet::LdpMessageTypes::KEEP_ALIVE, inet::LdpMessageTypes::ADDRESS, inet::LdpMessageTypes::ADDRESS_WITHDRAW, inet::LdpMessageTypes::LABEL_MAPPING, inet::LdpMessageTypes::LABEL_REQUEST, inet::LdpMessageTypes::LABEL_WITHDRAW, inet::LdpMessageTypes::LABEL_RELEASE, inet::LdpMessageTypes::UNKNOWN));

Register_Enum(inet::LdpStatusTypes, (inet::LdpStatusTypes::NO_ROUTE));

FecTlv::FecTlv()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FecTlv& a)
{
    doParsimPacking(b,a.addr);
    doParsimPacking(b,a.length);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FecTlv& a)
{
    doParsimUnpacking(b,a.addr);
    doParsimUnpacking(b,a.length);
}

class FecTlvDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_addr,
        FIELD_length,
    };
  public:
    FecTlvDescriptor();
    virtual ~FecTlvDescriptor();

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

Register_ClassDescriptor(FecTlvDescriptor)

FecTlvDescriptor::FecTlvDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FecTlv)), "")
{
    propertyNames = nullptr;
}

FecTlvDescriptor::~FecTlvDescriptor()
{
    delete[] propertyNames;
}

bool FecTlvDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FecTlv *>(obj)!=nullptr;
}

const char **FecTlvDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FecTlvDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FecTlvDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int FecTlvDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_addr
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *FecTlvDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "addr",
        "length",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int FecTlvDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "addr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *FecTlvDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_addr
        "int",    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **FecTlvDescriptor::getFieldPropertyNames(int field) const
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

const char *FecTlvDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FecTlvDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FecTlvDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FecTlv'", field);
    }
}

const char *FecTlvDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FecTlvDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return pp->addr.str();
        case FIELD_length: return long2string(pp->length);
        default: return "";
    }
}

void FecTlvDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FecTlv'", field);
    }
}

omnetpp::cValue FecTlvDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return omnetpp::toAnyPtr(&pp->addr); break;
        case FIELD_length: return pp->length;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FecTlv' as cValue -- field index out of range?", field);
    }
}

void FecTlvDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FecTlv'", field);
    }
}

const char *FecTlvDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr FecTlvDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return omnetpp::toAnyPtr(&pp->addr); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FecTlvDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FecTlv *pp = omnetpp::fromAnyPtr<FecTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FecTlv'", field);
    }
}

Register_Class(LdpPacket)

LdpPacket::LdpPacket() : ::inet::FieldsChunk()
{
}

LdpPacket::LdpPacket(const LdpPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LdpPacket::~LdpPacket()
{
}

LdpPacket& LdpPacket::operator=(const LdpPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LdpPacket::copy(const LdpPacket& other)
{
    this->type = other.type;
    this->senderAddress = other.senderAddress;
    this->receiverAddress = other.receiverAddress;
}

void LdpPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->receiverAddress);
}

void LdpPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->receiverAddress);
}

int LdpPacket::getType() const
{
    return this->type;
}

void LdpPacket::setType(int type)
{
    handleChange();
    this->type = type;
}

const Ipv4Address& LdpPacket::getSenderAddress() const
{
    return this->senderAddress;
}

void LdpPacket::setSenderAddress(const Ipv4Address& senderAddress)
{
    handleChange();
    this->senderAddress = senderAddress;
}

const Ipv4Address& LdpPacket::getReceiverAddress() const
{
    return this->receiverAddress;
}

void LdpPacket::setReceiverAddress(const Ipv4Address& receiverAddress)
{
    handleChange();
    this->receiverAddress = receiverAddress;
}

class LdpPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_senderAddress,
        FIELD_receiverAddress,
    };
  public:
    LdpPacketDescriptor();
    virtual ~LdpPacketDescriptor();

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

Register_ClassDescriptor(LdpPacketDescriptor)

LdpPacketDescriptor::LdpPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LdpPacketDescriptor::~LdpPacketDescriptor()
{
    delete[] propertyNames;
}

bool LdpPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpPacket *>(obj)!=nullptr;
}

const char **LdpPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LdpPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        0,    // FIELD_senderAddress
        0,    // FIELD_receiverAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LdpPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "senderAddress",
        "receiverAddress",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LdpPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "senderAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "receiverAddress") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_type
        "inet::Ipv4Address",    // FIELD_senderAddress
        "inet::Ipv4Address",    // FIELD_receiverAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpPacket'", field);
    }
}

const char *LdpPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: return long2string(pp->getType());
        case FIELD_senderAddress: return pp->getSenderAddress().str();
        case FIELD_receiverAddress: return pp->getReceiverAddress().str();
        default: return "";
    }
}

void LdpPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpPacket'", field);
    }
}

omnetpp::cValue LdpPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: return pp->getType();
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpPacket' as cValue -- field index out of range?", field);
    }
}

void LdpPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpPacket'", field);
    }
}

const char *LdpPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LdpPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpPacket *pp = omnetpp::fromAnyPtr<LdpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpPacket'", field);
    }
}

Register_Class(LdpLabelMapping)

LdpLabelMapping::LdpLabelMapping() : ::inet::LdpPacket()
{
}

LdpLabelMapping::LdpLabelMapping(const LdpLabelMapping& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpLabelMapping::~LdpLabelMapping()
{
}

LdpLabelMapping& LdpLabelMapping::operator=(const LdpLabelMapping& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpLabelMapping::copy(const LdpLabelMapping& other)
{
    this->fec = other.fec;
    this->label = other.label;
}

void LdpLabelMapping::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->fec);
    doParsimPacking(b,this->label);
}

void LdpLabelMapping::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->fec);
    doParsimUnpacking(b,this->label);
}

const FecTlv& LdpLabelMapping::getFec() const
{
    return this->fec;
}

void LdpLabelMapping::setFec(const FecTlv& fec)
{
    handleChange();
    this->fec = fec;
}

int LdpLabelMapping::getLabel() const
{
    return this->label;
}

void LdpLabelMapping::setLabel(int label)
{
    handleChange();
    this->label = label;
}

class LdpLabelMappingDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fec,
        FIELD_label,
    };
  public:
    LdpLabelMappingDescriptor();
    virtual ~LdpLabelMappingDescriptor();

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

Register_ClassDescriptor(LdpLabelMappingDescriptor)

LdpLabelMappingDescriptor::LdpLabelMappingDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpLabelMapping)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpLabelMappingDescriptor::~LdpLabelMappingDescriptor()
{
    delete[] propertyNames;
}

bool LdpLabelMappingDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpLabelMapping *>(obj)!=nullptr;
}

const char **LdpLabelMappingDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpLabelMappingDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpLabelMappingDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int LdpLabelMappingDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_fec
        FD_ISEDITABLE,    // FIELD_label
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *LdpLabelMappingDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fec",
        "label",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int LdpLabelMappingDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fec") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "label") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpLabelMappingDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::FecTlv",    // FIELD_fec
        "int",    // FIELD_label
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpLabelMappingDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpLabelMappingDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpLabelMappingDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpLabelMappingDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpLabelMapping'", field);
    }
}

const char *LdpLabelMappingDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpLabelMappingDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return "";
        case FIELD_label: return long2string(pp->getLabel());
        default: return "";
    }
}

void LdpLabelMappingDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelMapping'", field);
    }
}

omnetpp::cValue LdpLabelMappingDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        case FIELD_label: return pp->getLabel();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpLabelMapping' as cValue -- field index out of range?", field);
    }
}

void LdpLabelMappingDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->setLabel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelMapping'", field);
    }
}

const char *LdpLabelMappingDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fec: return omnetpp::opp_typename(typeid(FecTlv));
        default: return nullptr;
    };
}

omnetpp::any_ptr LdpLabelMappingDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpLabelMappingDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelMapping *pp = omnetpp::fromAnyPtr<LdpLabelMapping>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelMapping'", field);
    }
}

Register_Class(LdpLabelRequest)

LdpLabelRequest::LdpLabelRequest() : ::inet::LdpPacket()
{
}

LdpLabelRequest::LdpLabelRequest(const LdpLabelRequest& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpLabelRequest::~LdpLabelRequest()
{
}

LdpLabelRequest& LdpLabelRequest::operator=(const LdpLabelRequest& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpLabelRequest::copy(const LdpLabelRequest& other)
{
    this->fec = other.fec;
}

void LdpLabelRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->fec);
}

void LdpLabelRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->fec);
}

const FecTlv& LdpLabelRequest::getFec() const
{
    return this->fec;
}

void LdpLabelRequest::setFec(const FecTlv& fec)
{
    handleChange();
    this->fec = fec;
}

class LdpLabelRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fec,
    };
  public:
    LdpLabelRequestDescriptor();
    virtual ~LdpLabelRequestDescriptor();

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

Register_ClassDescriptor(LdpLabelRequestDescriptor)

LdpLabelRequestDescriptor::LdpLabelRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpLabelRequest)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpLabelRequestDescriptor::~LdpLabelRequestDescriptor()
{
    delete[] propertyNames;
}

bool LdpLabelRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpLabelRequest *>(obj)!=nullptr;
}

const char **LdpLabelRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpLabelRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpLabelRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LdpLabelRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_fec
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LdpLabelRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fec",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LdpLabelRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fec") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpLabelRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::FecTlv",    // FIELD_fec
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpLabelRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpLabelRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpLabelRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpLabelRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpLabelRequest'", field);
    }
}

const char *LdpLabelRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpLabelRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return "";
        default: return "";
    }
}

void LdpLabelRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelRequest'", field);
    }
}

omnetpp::cValue LdpLabelRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpLabelRequest' as cValue -- field index out of range?", field);
    }
}

void LdpLabelRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelRequest'", field);
    }
}

const char *LdpLabelRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fec: return omnetpp::opp_typename(typeid(FecTlv));
        default: return nullptr;
    };
}

omnetpp::any_ptr LdpLabelRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpLabelRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpLabelRequest *pp = omnetpp::fromAnyPtr<LdpLabelRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpLabelRequest'", field);
    }
}

Register_Class(LdpHello)

LdpHello::LdpHello() : ::inet::LdpPacket()
{
}

LdpHello::LdpHello(const LdpHello& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpHello::~LdpHello()
{
}

LdpHello& LdpHello::operator=(const LdpHello& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpHello::copy(const LdpHello& other)
{
    this->holdTime = other.holdTime;
    this->tbit = other.tbit;
    this->rbit = other.rbit;
}

void LdpHello::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->holdTime);
    doParsimPacking(b,this->tbit);
    doParsimPacking(b,this->rbit);
}

void LdpHello::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->holdTime);
    doParsimUnpacking(b,this->tbit);
    doParsimUnpacking(b,this->rbit);
}

double LdpHello::getHoldTime() const
{
    return this->holdTime;
}

void LdpHello::setHoldTime(double holdTime)
{
    handleChange();
    this->holdTime = holdTime;
}

bool LdpHello::getTbit() const
{
    return this->tbit;
}

void LdpHello::setTbit(bool tbit)
{
    handleChange();
    this->tbit = tbit;
}

bool LdpHello::getRbit() const
{
    return this->rbit;
}

void LdpHello::setRbit(bool rbit)
{
    handleChange();
    this->rbit = rbit;
}

class LdpHelloDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_holdTime,
        FIELD_tbit,
        FIELD_rbit,
    };
  public:
    LdpHelloDescriptor();
    virtual ~LdpHelloDescriptor();

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

Register_ClassDescriptor(LdpHelloDescriptor)

LdpHelloDescriptor::LdpHelloDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpHello)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpHelloDescriptor::~LdpHelloDescriptor()
{
    delete[] propertyNames;
}

bool LdpHelloDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpHello *>(obj)!=nullptr;
}

const char **LdpHelloDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpHelloDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpHelloDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LdpHelloDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_holdTime
        FD_ISEDITABLE,    // FIELD_tbit
        FD_ISEDITABLE,    // FIELD_rbit
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LdpHelloDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "holdTime",
        "tbit",
        "rbit",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LdpHelloDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "holdTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tbit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "rbit") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpHelloDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_holdTime
        "bool",    // FIELD_tbit
        "bool",    // FIELD_rbit
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpHelloDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpHelloDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpHelloDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpHelloDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpHello'", field);
    }
}

const char *LdpHelloDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpHelloDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: return double2string(pp->getHoldTime());
        case FIELD_tbit: return bool2string(pp->getTbit());
        case FIELD_rbit: return bool2string(pp->getRbit());
        default: return "";
    }
}

void LdpHelloDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: pp->setHoldTime(string2double(value)); break;
        case FIELD_tbit: pp->setTbit(string2bool(value)); break;
        case FIELD_rbit: pp->setRbit(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpHello'", field);
    }
}

omnetpp::cValue LdpHelloDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: return pp->getHoldTime();
        case FIELD_tbit: return pp->getTbit();
        case FIELD_rbit: return pp->getRbit();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpHello' as cValue -- field index out of range?", field);
    }
}

void LdpHelloDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: pp->setHoldTime(value.doubleValue()); break;
        case FIELD_tbit: pp->setTbit(value.boolValue()); break;
        case FIELD_rbit: pp->setRbit(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpHello'", field);
    }
}

const char *LdpHelloDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LdpHelloDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpHelloDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpHello *pp = omnetpp::fromAnyPtr<LdpHello>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpHello'", field);
    }
}

Register_Class(LdpNotify)

LdpNotify::LdpNotify() : ::inet::LdpPacket()
{
}

LdpNotify::LdpNotify(const LdpNotify& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpNotify::~LdpNotify()
{
}

LdpNotify& LdpNotify::operator=(const LdpNotify& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpNotify::copy(const LdpNotify& other)
{
    this->status = other.status;
    this->fec = other.fec;
}

void LdpNotify::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->fec);
}

void LdpNotify::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->fec);
}

int LdpNotify::getStatus() const
{
    return this->status;
}

void LdpNotify::setStatus(int status)
{
    handleChange();
    this->status = status;
}

const FecTlv& LdpNotify::getFec() const
{
    return this->fec;
}

void LdpNotify::setFec(const FecTlv& fec)
{
    handleChange();
    this->fec = fec;
}

class LdpNotifyDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_status,
        FIELD_fec,
    };
  public:
    LdpNotifyDescriptor();
    virtual ~LdpNotifyDescriptor();

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

Register_ClassDescriptor(LdpNotifyDescriptor)

LdpNotifyDescriptor::LdpNotifyDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpNotify)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpNotifyDescriptor::~LdpNotifyDescriptor()
{
    delete[] propertyNames;
}

bool LdpNotifyDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpNotify *>(obj)!=nullptr;
}

const char **LdpNotifyDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpNotifyDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpNotifyDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int LdpNotifyDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_status
        FD_ISCOMPOUND,    // FIELD_fec
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *LdpNotifyDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "status",
        "fec",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int LdpNotifyDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fec") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpNotifyDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_status
        "inet::FecTlv",    // FIELD_fec
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpNotifyDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpNotifyDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpNotifyDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpNotifyDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpNotify'", field);
    }
}

const char *LdpNotifyDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpNotifyDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        case FIELD_status: return long2string(pp->getStatus());
        case FIELD_fec: return "";
        default: return "";
    }
}

void LdpNotifyDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpNotify'", field);
    }
}

omnetpp::cValue LdpNotifyDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        case FIELD_status: return pp->getStatus();
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpNotify' as cValue -- field index out of range?", field);
    }
}

void LdpNotifyDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpNotify'", field);
    }
}

const char *LdpNotifyDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fec: return omnetpp::opp_typename(typeid(FecTlv));
        default: return nullptr;
    };
}

omnetpp::any_ptr LdpNotifyDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        case FIELD_fec: return omnetpp::toAnyPtr(&pp->getFec()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpNotifyDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpNotify *pp = omnetpp::fromAnyPtr<LdpNotify>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpNotify'", field);
    }
}

Register_Class(LdpIni)

LdpIni::LdpIni() : ::inet::LdpPacket()
{
}

LdpIni::LdpIni(const LdpIni& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpIni::~LdpIni()
{
}

LdpIni& LdpIni::operator=(const LdpIni& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpIni::copy(const LdpIni& other)
{
    this->keepAliveTime = other.keepAliveTime;
    this->abit = other.abit;
    this->dbit = other.dbit;
    this->pvLim = other.pvLim;
    this->receiverLDPIdentifier = other.receiverLDPIdentifier;
}

void LdpIni::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->keepAliveTime);
    doParsimPacking(b,this->abit);
    doParsimPacking(b,this->dbit);
    doParsimPacking(b,this->pvLim);
    doParsimPacking(b,this->receiverLDPIdentifier);
}

void LdpIni::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->keepAliveTime);
    doParsimUnpacking(b,this->abit);
    doParsimUnpacking(b,this->dbit);
    doParsimUnpacking(b,this->pvLim);
    doParsimUnpacking(b,this->receiverLDPIdentifier);
}

double LdpIni::getKeepAliveTime() const
{
    return this->keepAliveTime;
}

void LdpIni::setKeepAliveTime(double keepAliveTime)
{
    handleChange();
    this->keepAliveTime = keepAliveTime;
}

bool LdpIni::getAbit() const
{
    return this->abit;
}

void LdpIni::setAbit(bool abit)
{
    handleChange();
    this->abit = abit;
}

bool LdpIni::getDbit() const
{
    return this->dbit;
}

void LdpIni::setDbit(bool dbit)
{
    handleChange();
    this->dbit = dbit;
}

int LdpIni::getPvLim() const
{
    return this->pvLim;
}

void LdpIni::setPvLim(int pvLim)
{
    handleChange();
    this->pvLim = pvLim;
}

const char * LdpIni::getReceiverLDPIdentifier() const
{
    return this->receiverLDPIdentifier.c_str();
}

void LdpIni::setReceiverLDPIdentifier(const char * receiverLDPIdentifier)
{
    handleChange();
    this->receiverLDPIdentifier = receiverLDPIdentifier;
}

class LdpIniDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_keepAliveTime,
        FIELD_abit,
        FIELD_dbit,
        FIELD_pvLim,
        FIELD_receiverLDPIdentifier,
    };
  public:
    LdpIniDescriptor();
    virtual ~LdpIniDescriptor();

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

Register_ClassDescriptor(LdpIniDescriptor)

LdpIniDescriptor::LdpIniDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpIni)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpIniDescriptor::~LdpIniDescriptor()
{
    delete[] propertyNames;
}

bool LdpIniDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpIni *>(obj)!=nullptr;
}

const char **LdpIniDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpIniDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpIniDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LdpIniDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_keepAliveTime
        FD_ISEDITABLE,    // FIELD_abit
        FD_ISEDITABLE,    // FIELD_dbit
        FD_ISEDITABLE,    // FIELD_pvLim
        FD_ISEDITABLE,    // FIELD_receiverLDPIdentifier
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LdpIniDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "keepAliveTime",
        "abit",
        "dbit",
        "pvLim",
        "receiverLDPIdentifier",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LdpIniDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "keepAliveTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "abit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dbit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pvLim") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "receiverLDPIdentifier") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpIniDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_keepAliveTime
        "bool",    // FIELD_abit
        "bool",    // FIELD_dbit
        "int",    // FIELD_pvLim
        "string",    // FIELD_receiverLDPIdentifier
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpIniDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpIniDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpIniDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LdpIniDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpIni'", field);
    }
}

const char *LdpIniDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpIniDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        case FIELD_keepAliveTime: return double2string(pp->getKeepAliveTime());
        case FIELD_abit: return bool2string(pp->getAbit());
        case FIELD_dbit: return bool2string(pp->getDbit());
        case FIELD_pvLim: return long2string(pp->getPvLim());
        case FIELD_receiverLDPIdentifier: return oppstring2string(pp->getReceiverLDPIdentifier());
        default: return "";
    }
}

void LdpIniDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        case FIELD_keepAliveTime: pp->setKeepAliveTime(string2double(value)); break;
        case FIELD_abit: pp->setAbit(string2bool(value)); break;
        case FIELD_dbit: pp->setDbit(string2bool(value)); break;
        case FIELD_pvLim: pp->setPvLim(string2long(value)); break;
        case FIELD_receiverLDPIdentifier: pp->setReceiverLDPIdentifier((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpIni'", field);
    }
}

omnetpp::cValue LdpIniDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        case FIELD_keepAliveTime: return pp->getKeepAliveTime();
        case FIELD_abit: return pp->getAbit();
        case FIELD_dbit: return pp->getDbit();
        case FIELD_pvLim: return pp->getPvLim();
        case FIELD_receiverLDPIdentifier: return pp->getReceiverLDPIdentifier();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpIni' as cValue -- field index out of range?", field);
    }
}

void LdpIniDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        case FIELD_keepAliveTime: pp->setKeepAliveTime(value.doubleValue()); break;
        case FIELD_abit: pp->setAbit(value.boolValue()); break;
        case FIELD_dbit: pp->setDbit(value.boolValue()); break;
        case FIELD_pvLim: pp->setPvLim(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_receiverLDPIdentifier: pp->setReceiverLDPIdentifier(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpIni'", field);
    }
}

const char *LdpIniDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LdpIniDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpIniDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpIni *pp = omnetpp::fromAnyPtr<LdpIni>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpIni'", field);
    }
}

Register_Class(LdpAddress)

LdpAddress::LdpAddress() : ::inet::LdpPacket()
{
}

LdpAddress::LdpAddress(const LdpAddress& other) : ::inet::LdpPacket(other)
{
    copy(other);
}

LdpAddress::~LdpAddress()
{
    delete [] this->addresses;
}

LdpAddress& LdpAddress::operator=(const LdpAddress& other)
{
    if (this == &other) return *this;
    ::inet::LdpPacket::operator=(other);
    copy(other);
    return *this;
}

void LdpAddress::copy(const LdpAddress& other)
{
    this->isWithdraw_ = other.isWithdraw_;
    this->family = other.family;
    delete [] this->addresses;
    this->addresses = (other.addresses_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.addresses_arraysize];
    addresses_arraysize = other.addresses_arraysize;
    for (size_t i = 0; i < addresses_arraysize; i++) {
        this->addresses[i] = other.addresses[i];
    }
}

void LdpAddress::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::LdpPacket::parsimPack(b);
    doParsimPacking(b,this->isWithdraw_);
    doParsimPacking(b,this->family);
    b->pack(addresses_arraysize);
    doParsimArrayPacking(b,this->addresses,addresses_arraysize);
}

void LdpAddress::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::LdpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->isWithdraw_);
    doParsimUnpacking(b,this->family);
    delete [] this->addresses;
    b->unpack(addresses_arraysize);
    if (addresses_arraysize == 0) {
        this->addresses = nullptr;
    } else {
        this->addresses = new ::omnetpp::opp_string[addresses_arraysize];
        doParsimArrayUnpacking(b,this->addresses,addresses_arraysize);
    }
}

bool LdpAddress::isWithdraw() const
{
    return this->isWithdraw_;
}

void LdpAddress::setIsWithdraw(bool isWithdraw)
{
    handleChange();
    this->isWithdraw_ = isWithdraw;
}

const char * LdpAddress::getFamily() const
{
    return this->family.c_str();
}

void LdpAddress::setFamily(const char * family)
{
    handleChange();
    this->family = family;
}

size_t LdpAddress::getAddressesArraySize() const
{
    return addresses_arraysize;
}

const char * LdpAddress::getAddresses(size_t k) const
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    return this->addresses[k].c_str();
}

void LdpAddress::setAddressesArraySize(size_t newSize)
{
    handleChange();
    ::omnetpp::opp_string *addresses2 = (newSize==0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t minSize = addresses_arraysize < newSize ? addresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        addresses2[i] = this->addresses[i];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void LdpAddress::setAddresses(size_t k, const char * addresses)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    handleChange();
    this->addresses[k] = addresses;
}

void LdpAddress::insertAddresses(size_t k, const char * addresses)
{
    if (k > addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = addresses_arraysize + 1;
    ::omnetpp::opp_string *addresses2 = new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    addresses2[k] = addresses;
    for (i = k + 1; i < newSize; i++)
        addresses2[i] = this->addresses[i-1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void LdpAddress::appendAddresses(const char * addresses)
{
    insertAddresses(addresses_arraysize, addresses);
}

void LdpAddress::eraseAddresses(size_t k)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = addresses_arraysize - 1;
    ::omnetpp::opp_string *addresses2 = (newSize == 0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    for (i = k; i < newSize; i++)
        addresses2[i] = this->addresses[i+1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

class LdpAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_isWithdraw,
        FIELD_family,
        FIELD_addresses,
    };
  public:
    LdpAddressDescriptor();
    virtual ~LdpAddressDescriptor();

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

Register_ClassDescriptor(LdpAddressDescriptor)

LdpAddressDescriptor::LdpAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LdpAddress)), "inet::LdpPacket")
{
    propertyNames = nullptr;
}

LdpAddressDescriptor::~LdpAddressDescriptor()
{
    delete[] propertyNames;
}

bool LdpAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LdpAddress *>(obj)!=nullptr;
}

const char **LdpAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LdpAddressDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LdpAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LdpAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isWithdraw
        FD_ISEDITABLE,    // FIELD_family
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_addresses
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LdpAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isWithdraw",
        "family",
        "addresses",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LdpAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "isWithdraw") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "family") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "addresses") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LdpAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isWithdraw
        "string",    // FIELD_family
        "string",    // FIELD_addresses
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LdpAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *LdpAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LdpAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: return pp->getAddressesArraySize();
        default: return 0;
    }
}

void LdpAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: pp->setAddressesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LdpAddress'", field);
    }
}

const char *LdpAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LdpAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_isWithdraw: return bool2string(pp->isWithdraw());
        case FIELD_family: return oppstring2string(pp->getFamily());
        case FIELD_addresses: return oppstring2string(pp->getAddresses(i));
        default: return "";
    }
}

void LdpAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_isWithdraw: pp->setIsWithdraw(string2bool(value)); break;
        case FIELD_family: pp->setFamily((value)); break;
        case FIELD_addresses: pp->setAddresses(i,(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpAddress'", field);
    }
}

omnetpp::cValue LdpAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_isWithdraw: return pp->isWithdraw();
        case FIELD_family: return pp->getFamily();
        case FIELD_addresses: return pp->getAddresses(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LdpAddress' as cValue -- field index out of range?", field);
    }
}

void LdpAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        case FIELD_isWithdraw: pp->setIsWithdraw(value.boolValue()); break;
        case FIELD_family: pp->setFamily(value.stringValue()); break;
        case FIELD_addresses: pp->setAddresses(i,value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpAddress'", field);
    }
}

const char *LdpAddressDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LdpAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LdpAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LdpAddress *pp = omnetpp::fromAnyPtr<LdpAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LdpAddress'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

