//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/nexthop/NextHopForwardingHeader.msg.
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
#include "NextHopForwardingHeader_m.h"

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

Register_Enum(inet::NextHopTlvOptionTypes, (inet::NextHopTlvOptionTypes::NEXTHOP_TLVOPTION_NOP1, inet::NextHopTlvOptionTypes::NEXTHOP_TLVOPTION_NOPN, inet::NextHopTlvOptionTypes::NEXTHOP_TLVOPTION_TLV_GPSR));

Register_Class(NextHopForwardingHeader)

NextHopForwardingHeader::NextHopForwardingHeader() : ::inet::NetworkHeaderBase()
{
}

NextHopForwardingHeader::NextHopForwardingHeader(const NextHopForwardingHeader& other) : ::inet::NetworkHeaderBase(other)
{
    copy(other);
}

NextHopForwardingHeader::~NextHopForwardingHeader()
{
}

NextHopForwardingHeader& NextHopForwardingHeader::operator=(const NextHopForwardingHeader& other)
{
    if (this == &other) return *this;
    ::inet::NetworkHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void NextHopForwardingHeader::copy(const NextHopForwardingHeader& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->protocolId = other.protocolId;
    this->hopLimit = other.hopLimit;
    this->payloadLengthField = other.payloadLengthField;
    this->tlvOptions = other.tlvOptions;
}

void NextHopForwardingHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NetworkHeaderBase::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->protocolId);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->payloadLengthField);
    doParsimPacking(b,this->tlvOptions);
}

void NextHopForwardingHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NetworkHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->protocolId);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->payloadLengthField);
    doParsimUnpacking(b,this->tlvOptions);
}

const L3Address& NextHopForwardingHeader::getSrcAddr() const
{
    return this->srcAddr;
}

void NextHopForwardingHeader::setSrcAddr(const L3Address& srcAddr)
{
    handleChange();
    this->srcAddr = srcAddr;
}

const L3Address& NextHopForwardingHeader::getDestAddr() const
{
    return this->destAddr;
}

void NextHopForwardingHeader::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

IpProtocolId NextHopForwardingHeader::getProtocolId() const
{
    return this->protocolId;
}

void NextHopForwardingHeader::setProtocolId(IpProtocolId protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

short NextHopForwardingHeader::getHopLimit() const
{
    return this->hopLimit;
}

void NextHopForwardingHeader::setHopLimit(short hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

B NextHopForwardingHeader::getPayloadLengthField() const
{
    return this->payloadLengthField;
}

void NextHopForwardingHeader::setPayloadLengthField(B payloadLengthField)
{
    handleChange();
    this->payloadLengthField = payloadLengthField;
}

const TlvOptions& NextHopForwardingHeader::getTlvOptions() const
{
    return this->tlvOptions;
}

void NextHopForwardingHeader::setTlvOptions(const TlvOptions& tlvOptions)
{
    handleChange();
    this->tlvOptions = tlvOptions;
}

class NextHopForwardingHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_protocolId,
        FIELD_hopLimit,
        FIELD_payloadLengthField,
        FIELD_tlvOptions,
    };
  public:
    NextHopForwardingHeaderDescriptor();
    virtual ~NextHopForwardingHeaderDescriptor();

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

Register_ClassDescriptor(NextHopForwardingHeaderDescriptor)

NextHopForwardingHeaderDescriptor::NextHopForwardingHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::NextHopForwardingHeader)), "inet::NetworkHeaderBase")
{
    propertyNames = nullptr;
}

NextHopForwardingHeaderDescriptor::~NextHopForwardingHeaderDescriptor()
{
    delete[] propertyNames;
}

bool NextHopForwardingHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NextHopForwardingHeader *>(obj)!=nullptr;
}

const char **NextHopForwardingHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NextHopForwardingHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NextHopForwardingHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int NextHopForwardingHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddr
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_protocolId
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_payloadLengthField
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *NextHopForwardingHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "protocolId",
        "hopLimit",
        "payloadLengthField",
        "tlvOptions",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int NextHopForwardingHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopLimit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "payloadLengthField") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "tlvOptions") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *NextHopForwardingHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_srcAddr
        "inet::L3Address",    // FIELD_destAddr
        "inet::IpProtocolId",    // FIELD_protocolId
        "short",    // FIELD_hopLimit
        "inet::B",    // FIELD_payloadLengthField
        "inet::TlvOptions",    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **NextHopForwardingHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NextHopForwardingHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId:
            if (!strcmp(propertyName, "enum")) return "inet::IpProtocolId";
            return nullptr;
        default: return nullptr;
    }
}

int NextHopForwardingHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NextHopForwardingHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NextHopForwardingHeader'", field);
    }
}

const char *NextHopForwardingHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NextHopForwardingHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr().str();
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_protocolId: return enum2string(pp->getProtocolId(), "inet::IpProtocolId");
        case FIELD_hopLimit: return long2string(pp->getHopLimit());
        case FIELD_payloadLengthField: return unit2string(pp->getPayloadLengthField());
        case FIELD_tlvOptions: return pp->getTlvOptions().str();
        default: return "";
    }
}

void NextHopForwardingHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_protocolId: pp->setProtocolId((inet::IpProtocolId)string2enum(value, "inet::IpProtocolId")); break;
        case FIELD_hopLimit: pp->setHopLimit(string2long(value)); break;
        case FIELD_payloadLengthField: pp->setPayloadLengthField(B(string2long(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextHopForwardingHeader'", field);
    }
}

omnetpp::cValue NextHopForwardingHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_protocolId: return static_cast<int>(pp->getProtocolId());
        case FIELD_hopLimit: return pp->getHopLimit();
        case FIELD_payloadLengthField: return cValue(pp->getPayloadLengthField().get(),"B");
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NextHopForwardingHeader' as cValue -- field index out of range?", field);
    }
}

void NextHopForwardingHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_protocolId: pp->setProtocolId(static_cast<inet::IpProtocolId>(value.intValue())); break;
        case FIELD_hopLimit: pp->setHopLimit(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_payloadLengthField: pp->setPayloadLengthField(B(value.intValueInUnit("B"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextHopForwardingHeader'", field);
    }
}

const char *NextHopForwardingHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::opp_typename(typeid(TlvOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr NextHopForwardingHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NextHopForwardingHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NextHopForwardingHeader *pp = omnetpp::fromAnyPtr<NextHopForwardingHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NextHopForwardingHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

