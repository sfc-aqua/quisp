//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/arp/ipv4/ArpPacket.msg.
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
#include "ArpPacket_m.h"

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

Register_Enum(inet::ArpOpcode, (inet::ArpOpcode::ARP_REQUEST, inet::ArpOpcode::ARP_REPLY, inet::ArpOpcode::ARP_RARP_REQUEST, inet::ArpOpcode::ARP_RARP_REPLY));

Register_Class(ArpPacket)

ArpPacket::ArpPacket() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(28));

}

ArpPacket::ArpPacket(const ArpPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

ArpPacket::~ArpPacket()
{
}

ArpPacket& ArpPacket::operator=(const ArpPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void ArpPacket::copy(const ArpPacket& other)
{
    this->opcode = other.opcode;
    this->srcMacAddress = other.srcMacAddress;
    this->destMacAddress = other.destMacAddress;
    this->srcIpAddress = other.srcIpAddress;
    this->destIpAddress = other.destIpAddress;
}

void ArpPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->opcode);
    doParsimPacking(b,this->srcMacAddress);
    doParsimPacking(b,this->destMacAddress);
    doParsimPacking(b,this->srcIpAddress);
    doParsimPacking(b,this->destIpAddress);
}

void ArpPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->opcode);
    doParsimUnpacking(b,this->srcMacAddress);
    doParsimUnpacking(b,this->destMacAddress);
    doParsimUnpacking(b,this->srcIpAddress);
    doParsimUnpacking(b,this->destIpAddress);
}

ArpOpcode ArpPacket::getOpcode() const
{
    return this->opcode;
}

void ArpPacket::setOpcode(ArpOpcode opcode)
{
    handleChange();
    this->opcode = opcode;
}

const MacAddress& ArpPacket::getSrcMacAddress() const
{
    return this->srcMacAddress;
}

void ArpPacket::setSrcMacAddress(const MacAddress& srcMacAddress)
{
    handleChange();
    this->srcMacAddress = srcMacAddress;
}

const MacAddress& ArpPacket::getDestMacAddress() const
{
    return this->destMacAddress;
}

void ArpPacket::setDestMacAddress(const MacAddress& destMacAddress)
{
    handleChange();
    this->destMacAddress = destMacAddress;
}

const Ipv4Address& ArpPacket::getSrcIpAddress() const
{
    return this->srcIpAddress;
}

void ArpPacket::setSrcIpAddress(const Ipv4Address& srcIpAddress)
{
    handleChange();
    this->srcIpAddress = srcIpAddress;
}

const Ipv4Address& ArpPacket::getDestIpAddress() const
{
    return this->destIpAddress;
}

void ArpPacket::setDestIpAddress(const Ipv4Address& destIpAddress)
{
    handleChange();
    this->destIpAddress = destIpAddress;
}

class ArpPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_opcode,
        FIELD_srcMacAddress,
        FIELD_destMacAddress,
        FIELD_srcIpAddress,
        FIELD_destIpAddress,
    };
  public:
    ArpPacketDescriptor();
    virtual ~ArpPacketDescriptor();

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

Register_ClassDescriptor(ArpPacketDescriptor)

ArpPacketDescriptor::ArpPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ArpPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

ArpPacketDescriptor::~ArpPacketDescriptor()
{
    delete[] propertyNames;
}

bool ArpPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ArpPacket *>(obj)!=nullptr;
}

const char **ArpPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ArpPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ArpPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int ArpPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_opcode
        0,    // FIELD_srcMacAddress
        0,    // FIELD_destMacAddress
        0,    // FIELD_srcIpAddress
        0,    // FIELD_destIpAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *ArpPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "opcode",
        "srcMacAddress",
        "destMacAddress",
        "srcIpAddress",
        "destIpAddress",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int ArpPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "opcode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "srcMacAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "destMacAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "srcIpAddress") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "destIpAddress") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *ArpPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ArpOpcode",    // FIELD_opcode
        "inet::MacAddress",    // FIELD_srcMacAddress
        "inet::MacAddress",    // FIELD_destMacAddress
        "inet::Ipv4Address",    // FIELD_srcIpAddress
        "inet::Ipv4Address",    // FIELD_destIpAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **ArpPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_opcode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *ArpPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_opcode:
            if (!strcmp(propertyName, "enum")) return "inet::ArpOpcode";
            return nullptr;
        default: return nullptr;
    }
}

int ArpPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ArpPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ArpPacket'", field);
    }
}

const char *ArpPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ArpPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_opcode: return enum2string(pp->getOpcode(), "inet::ArpOpcode");
        case FIELD_srcMacAddress: return pp->getSrcMacAddress().str();
        case FIELD_destMacAddress: return pp->getDestMacAddress().str();
        case FIELD_srcIpAddress: return pp->getSrcIpAddress().str();
        case FIELD_destIpAddress: return pp->getDestIpAddress().str();
        default: return "";
    }
}

void ArpPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArpPacket'", field);
    }
}

omnetpp::cValue ArpPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_opcode: return static_cast<int>(pp->getOpcode());
        case FIELD_srcMacAddress: return omnetpp::toAnyPtr(&pp->getSrcMacAddress()); break;
        case FIELD_destMacAddress: return omnetpp::toAnyPtr(&pp->getDestMacAddress()); break;
        case FIELD_srcIpAddress: return omnetpp::toAnyPtr(&pp->getSrcIpAddress()); break;
        case FIELD_destIpAddress: return omnetpp::toAnyPtr(&pp->getDestIpAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ArpPacket' as cValue -- field index out of range?", field);
    }
}

void ArpPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArpPacket'", field);
    }
}

const char *ArpPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ArpPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_srcMacAddress: return omnetpp::toAnyPtr(&pp->getSrcMacAddress()); break;
        case FIELD_destMacAddress: return omnetpp::toAnyPtr(&pp->getDestMacAddress()); break;
        case FIELD_srcIpAddress: return omnetpp::toAnyPtr(&pp->getSrcIpAddress()); break;
        case FIELD_destIpAddress: return omnetpp::toAnyPtr(&pp->getDestIpAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ArpPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ArpPacket *pp = omnetpp::fromAnyPtr<ArpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ArpPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

