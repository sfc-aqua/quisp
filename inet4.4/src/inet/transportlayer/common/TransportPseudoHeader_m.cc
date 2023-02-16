//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/common/TransportPseudoHeader.msg.
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
#include "TransportPseudoHeader_m.h"

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

Register_Class(TransportPseudoHeader)

TransportPseudoHeader::TransportPseudoHeader() : ::inet::FieldsChunk()
{
}

TransportPseudoHeader::TransportPseudoHeader(const TransportPseudoHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

TransportPseudoHeader::~TransportPseudoHeader()
{
}

TransportPseudoHeader& TransportPseudoHeader::operator=(const TransportPseudoHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void TransportPseudoHeader::copy(const TransportPseudoHeader& other)
{
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->networkProtocolId = other.networkProtocolId;
    this->protocolId = other.protocolId;
    this->packetLength = other.packetLength;
}

void TransportPseudoHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->networkProtocolId);
    doParsimPacking(b,this->protocolId);
    doParsimPacking(b,this->packetLength);
}

void TransportPseudoHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->networkProtocolId);
    doParsimUnpacking(b,this->protocolId);
    doParsimUnpacking(b,this->packetLength);
}

const L3Address& TransportPseudoHeader::getSrcAddress() const
{
    return this->srcAddress;
}

void TransportPseudoHeader::setSrcAddress(const L3Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

const L3Address& TransportPseudoHeader::getDestAddress() const
{
    return this->destAddress;
}

void TransportPseudoHeader::setDestAddress(const L3Address& destAddress)
{
    handleChange();
    this->destAddress = destAddress;
}

int TransportPseudoHeader::getNetworkProtocolId() const
{
    return this->networkProtocolId;
}

void TransportPseudoHeader::setNetworkProtocolId(int networkProtocolId)
{
    handleChange();
    this->networkProtocolId = networkProtocolId;
}

int TransportPseudoHeader::getProtocolId() const
{
    return this->protocolId;
}

void TransportPseudoHeader::setProtocolId(int protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

B TransportPseudoHeader::getPacketLength() const
{
    return this->packetLength;
}

void TransportPseudoHeader::setPacketLength(B packetLength)
{
    handleChange();
    this->packetLength = packetLength;
}

class TransportPseudoHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddress,
        FIELD_destAddress,
        FIELD_networkProtocolId,
        FIELD_protocolId,
        FIELD_packetLength,
    };
  public:
    TransportPseudoHeaderDescriptor();
    virtual ~TransportPseudoHeaderDescriptor();

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

Register_ClassDescriptor(TransportPseudoHeaderDescriptor)

TransportPseudoHeaderDescriptor::TransportPseudoHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TransportPseudoHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

TransportPseudoHeaderDescriptor::~TransportPseudoHeaderDescriptor()
{
    delete[] propertyNames;
}

bool TransportPseudoHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TransportPseudoHeader *>(obj)!=nullptr;
}

const char **TransportPseudoHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TransportPseudoHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TransportPseudoHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int TransportPseudoHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddress
        0,    // FIELD_destAddress
        FD_ISEDITABLE,    // FIELD_networkProtocolId
        FD_ISEDITABLE,    // FIELD_protocolId
        FD_ISEDITABLE,    // FIELD_packetLength
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TransportPseudoHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddress",
        "destAddress",
        "networkProtocolId",
        "protocolId",
        "packetLength",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TransportPseudoHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "networkProtocolId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "packetLength") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *TransportPseudoHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_srcAddress
        "inet::L3Address",    // FIELD_destAddress
        "int",    // FIELD_networkProtocolId
        "int",    // FIELD_protocolId
        "inet::B",    // FIELD_packetLength
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TransportPseudoHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *TransportPseudoHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TransportPseudoHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TransportPseudoHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TransportPseudoHeader'", field);
    }
}

const char *TransportPseudoHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TransportPseudoHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_destAddress: return pp->getDestAddress().str();
        case FIELD_networkProtocolId: return long2string(pp->getNetworkProtocolId());
        case FIELD_protocolId: return long2string(pp->getProtocolId());
        case FIELD_packetLength: return unit2string(pp->getPacketLength());
        default: return "";
    }
}

void TransportPseudoHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocolId: pp->setNetworkProtocolId(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId(string2long(value)); break;
        case FIELD_packetLength: pp->setPacketLength(B(string2long(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransportPseudoHeader'", field);
    }
}

omnetpp::cValue TransportPseudoHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_networkProtocolId: return pp->getNetworkProtocolId();
        case FIELD_protocolId: return pp->getProtocolId();
        case FIELD_packetLength: return cValue(pp->getPacketLength().get(),"B");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TransportPseudoHeader' as cValue -- field index out of range?", field);
    }
}

void TransportPseudoHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocolId: pp->setNetworkProtocolId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_packetLength: pp->setPacketLength(B(value.intValueInUnit("B"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransportPseudoHeader'", field);
    }
}

const char *TransportPseudoHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TransportPseudoHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TransportPseudoHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TransportPseudoHeader *pp = omnetpp::fromAnyPtr<TransportPseudoHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransportPseudoHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

