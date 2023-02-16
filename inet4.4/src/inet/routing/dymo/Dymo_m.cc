//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/dymo/Dymo.msg.
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
#include "Dymo_m.h"

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
namespace dymo {

Register_Enum(inet::dymo::DymoMetricType, (inet::dymo::DymoMetricType::HOP_COUNT));

Register_Class(AddressBlock)

AddressBlock::AddressBlock() : ::omnetpp::cObject()
{
}

AddressBlock::AddressBlock(const AddressBlock& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

AddressBlock::~AddressBlock()
{
}

AddressBlock& AddressBlock::operator=(const AddressBlock& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void AddressBlock::copy(const AddressBlock& other)
{
    this->address = other.address;
    this->prefixLength = other.prefixLength;
    this->hasValidityTime = other.hasValidityTime;
    this->validityTime = other.validityTime;
    this->hasMetric = other.hasMetric;
    this->metric = other.metric;
    this->hasMetricType = other.hasMetricType;
    this->metricType = other.metricType;
    this->hasSequenceNumber = other.hasSequenceNumber;
    this->sequenceNumber = other.sequenceNumber;
}

void AddressBlock::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->hasValidityTime);
    doParsimPacking(b,this->validityTime);
    doParsimPacking(b,this->hasMetric);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->hasMetricType);
    doParsimPacking(b,this->metricType);
    doParsimPacking(b,this->hasSequenceNumber);
    doParsimPacking(b,this->sequenceNumber);
}

void AddressBlock::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->hasValidityTime);
    doParsimUnpacking(b,this->validityTime);
    doParsimUnpacking(b,this->hasMetric);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->hasMetricType);
    doParsimUnpacking(b,this->metricType);
    doParsimUnpacking(b,this->hasSequenceNumber);
    doParsimUnpacking(b,this->sequenceNumber);
}

const ::inet::L3Address& AddressBlock::getAddress() const
{
    return this->address;
}

void AddressBlock::setAddress(const ::inet::L3Address& address)
{
    this->address = address;
}

int AddressBlock::getPrefixLength() const
{
    return this->prefixLength;
}

void AddressBlock::setPrefixLength(int prefixLength)
{
    this->prefixLength = prefixLength;
}

bool AddressBlock::getHasValidityTime() const
{
    return this->hasValidityTime;
}

void AddressBlock::setHasValidityTime(bool hasValidityTime)
{
    this->hasValidityTime = hasValidityTime;
}

::omnetpp::simtime_t AddressBlock::getValidityTime() const
{
    return this->validityTime;
}

void AddressBlock::setValidityTime(::omnetpp::simtime_t validityTime)
{
    this->validityTime = validityTime;
}

bool AddressBlock::getHasMetric() const
{
    return this->hasMetric;
}

void AddressBlock::setHasMetric(bool hasMetric)
{
    this->hasMetric = hasMetric;
}

double AddressBlock::getMetric() const
{
    return this->metric;
}

void AddressBlock::setMetric(double metric)
{
    this->metric = metric;
}

bool AddressBlock::getHasMetricType() const
{
    return this->hasMetricType;
}

void AddressBlock::setHasMetricType(bool hasMetricType)
{
    this->hasMetricType = hasMetricType;
}

DymoMetricType AddressBlock::getMetricType() const
{
    return this->metricType;
}

void AddressBlock::setMetricType(DymoMetricType metricType)
{
    this->metricType = metricType;
}

bool AddressBlock::getHasSequenceNumber() const
{
    return this->hasSequenceNumber;
}

void AddressBlock::setHasSequenceNumber(bool hasSequenceNumber)
{
    this->hasSequenceNumber = hasSequenceNumber;
}

DymoSequenceNumber AddressBlock::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void AddressBlock::setSequenceNumber(DymoSequenceNumber sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

class AddressBlockDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_prefixLength,
        FIELD_hasValidityTime,
        FIELD_validityTime,
        FIELD_hasMetric,
        FIELD_metric,
        FIELD_hasMetricType,
        FIELD_metricType,
        FIELD_hasSequenceNumber,
        FIELD_sequenceNumber,
    };
  public:
    AddressBlockDescriptor();
    virtual ~AddressBlockDescriptor();

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

Register_ClassDescriptor(AddressBlockDescriptor)

AddressBlockDescriptor::AddressBlockDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::AddressBlock)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

AddressBlockDescriptor::~AddressBlockDescriptor()
{
    delete[] propertyNames;
}

bool AddressBlockDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AddressBlock *>(obj)!=nullptr;
}

const char **AddressBlockDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AddressBlockDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AddressBlockDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int AddressBlockDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_hasValidityTime
        FD_ISEDITABLE,    // FIELD_validityTime
        FD_ISEDITABLE,    // FIELD_hasMetric
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_hasMetricType
        0,    // FIELD_metricType
        FD_ISEDITABLE,    // FIELD_hasSequenceNumber
        0,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *AddressBlockDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "prefixLength",
        "hasValidityTime",
        "validityTime",
        "hasMetric",
        "metric",
        "hasMetricType",
        "metricType",
        "hasSequenceNumber",
        "sequenceNumber",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int AddressBlockDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "prefixLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hasValidityTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "validityTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "hasMetric") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "hasMetricType") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "metricType") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "hasSequenceNumber") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *AddressBlockDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_address
        "int",    // FIELD_prefixLength
        "bool",    // FIELD_hasValidityTime
        "omnetpp::simtime_t",    // FIELD_validityTime
        "bool",    // FIELD_hasMetric
        "double",    // FIELD_metric
        "bool",    // FIELD_hasMetricType
        "inet::dymo::DymoMetricType",    // FIELD_metricType
        "bool",    // FIELD_hasSequenceNumber
        "inet::dymo::DymoSequenceNumber",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **AddressBlockDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_metricType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *AddressBlockDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_metricType:
            if (!strcmp(propertyName, "enum")) return "inet::dymo::DymoMetricType";
            return nullptr;
        default: return nullptr;
    }
}

int AddressBlockDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AddressBlockDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AddressBlock'", field);
    }
}

const char *AddressBlockDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AddressBlockDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_prefixLength: return long2string(pp->getPrefixLength());
        case FIELD_hasValidityTime: return bool2string(pp->getHasValidityTime());
        case FIELD_validityTime: return simtime2string(pp->getValidityTime());
        case FIELD_hasMetric: return bool2string(pp->getHasMetric());
        case FIELD_metric: return double2string(pp->getMetric());
        case FIELD_hasMetricType: return bool2string(pp->getHasMetricType());
        case FIELD_metricType: return enum2string(pp->getMetricType(), "inet::dymo::DymoMetricType");
        case FIELD_hasSequenceNumber: return bool2string(pp->getHasSequenceNumber());
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        default: return "";
    }
}

void AddressBlockDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(string2long(value)); break;
        case FIELD_hasValidityTime: pp->setHasValidityTime(string2bool(value)); break;
        case FIELD_validityTime: pp->setValidityTime(string2simtime(value)); break;
        case FIELD_hasMetric: pp->setHasMetric(string2bool(value)); break;
        case FIELD_metric: pp->setMetric(string2double(value)); break;
        case FIELD_hasMetricType: pp->setHasMetricType(string2bool(value)); break;
        case FIELD_hasSequenceNumber: pp->setHasSequenceNumber(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressBlock'", field);
    }
}

omnetpp::cValue AddressBlockDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_prefixLength: return pp->getPrefixLength();
        case FIELD_hasValidityTime: return pp->getHasValidityTime();
        case FIELD_validityTime: return pp->getValidityTime().dbl();
        case FIELD_hasMetric: return pp->getHasMetric();
        case FIELD_metric: return pp->getMetric();
        case FIELD_hasMetricType: return pp->getHasMetricType();
        case FIELD_metricType: return static_cast<int>(pp->getMetricType());
        case FIELD_hasSequenceNumber: return pp->getHasSequenceNumber();
        case FIELD_sequenceNumber: return (int)pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AddressBlock' as cValue -- field index out of range?", field);
    }
}

void AddressBlockDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hasValidityTime: pp->setHasValidityTime(value.boolValue()); break;
        case FIELD_validityTime: pp->setValidityTime(value.doubleValue()); break;
        case FIELD_hasMetric: pp->setHasMetric(value.boolValue()); break;
        case FIELD_metric: pp->setMetric(value.doubleValue()); break;
        case FIELD_hasMetricType: pp->setHasMetricType(value.boolValue()); break;
        case FIELD_hasSequenceNumber: pp->setHasSequenceNumber(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressBlock'", field);
    }
}

const char *AddressBlockDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr AddressBlockDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AddressBlockDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressBlock *pp = omnetpp::fromAnyPtr<AddressBlock>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressBlock'", field);
    }
}

Register_Class(RreqTimer)

RreqTimer::RreqTimer(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RreqTimer::RreqTimer(const RreqTimer& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RreqTimer::~RreqTimer()
{
}

RreqTimer& RreqTimer::operator=(const RreqTimer& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RreqTimer::copy(const RreqTimer& other)
{
    this->target = other.target;
}

void RreqTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->target);
}

void RreqTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->target);
}

const ::inet::L3Address& RreqTimer::getTarget() const
{
    return this->target;
}

void RreqTimer::setTarget(const ::inet::L3Address& target)
{
    this->target = target;
}

class RreqTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_target,
    };
  public:
    RreqTimerDescriptor();
    virtual ~RreqTimerDescriptor();

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

Register_ClassDescriptor(RreqTimerDescriptor)

RreqTimerDescriptor::RreqTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RreqTimer)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RreqTimerDescriptor::~RreqTimerDescriptor()
{
    delete[] propertyNames;
}

bool RreqTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RreqTimer *>(obj)!=nullptr;
}

const char **RreqTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RreqTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_target
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RreqTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "target",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RreqTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "target") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RreqTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_target
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RreqTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RreqTimer'", field);
    }
}

const char *RreqTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        case FIELD_target: return pp->getTarget().str();
        default: return "";
    }
}

void RreqTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqTimer'", field);
    }
}

omnetpp::cValue RreqTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        case FIELD_target: return omnetpp::toAnyPtr(&pp->getTarget()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RreqTimer' as cValue -- field index out of range?", field);
    }
}

void RreqTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqTimer'", field);
    }
}

const char *RreqTimerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RreqTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        case FIELD_target: return omnetpp::toAnyPtr(&pp->getTarget()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqTimer *pp = omnetpp::fromAnyPtr<RreqTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqTimer'", field);
    }
}

Register_Class(RreqWaitRrepTimer)

RreqWaitRrepTimer::RreqWaitRrepTimer(const char *name, short kind) : ::inet::dymo::RreqTimer(name, kind)
{
}

RreqWaitRrepTimer::RreqWaitRrepTimer(const RreqWaitRrepTimer& other) : ::inet::dymo::RreqTimer(other)
{
    copy(other);
}

RreqWaitRrepTimer::~RreqWaitRrepTimer()
{
}

RreqWaitRrepTimer& RreqWaitRrepTimer::operator=(const RreqWaitRrepTimer& other)
{
    if (this == &other) return *this;
    ::inet::dymo::RreqTimer::operator=(other);
    copy(other);
    return *this;
}

void RreqWaitRrepTimer::copy(const RreqWaitRrepTimer& other)
{
    this->retryCount = other.retryCount;
}

void RreqWaitRrepTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::RreqTimer::parsimPack(b);
    doParsimPacking(b,this->retryCount);
}

void RreqWaitRrepTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::RreqTimer::parsimUnpack(b);
    doParsimUnpacking(b,this->retryCount);
}

int RreqWaitRrepTimer::getRetryCount() const
{
    return this->retryCount;
}

void RreqWaitRrepTimer::setRetryCount(int retryCount)
{
    this->retryCount = retryCount;
}

class RreqWaitRrepTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_retryCount,
    };
  public:
    RreqWaitRrepTimerDescriptor();
    virtual ~RreqWaitRrepTimerDescriptor();

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

Register_ClassDescriptor(RreqWaitRrepTimerDescriptor)

RreqWaitRrepTimerDescriptor::RreqWaitRrepTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RreqWaitRrepTimer)), "inet::dymo::RreqTimer")
{
    propertyNames = nullptr;
}

RreqWaitRrepTimerDescriptor::~RreqWaitRrepTimerDescriptor()
{
    delete[] propertyNames;
}

bool RreqWaitRrepTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RreqWaitRrepTimer *>(obj)!=nullptr;
}

const char **RreqWaitRrepTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqWaitRrepTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqWaitRrepTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RreqWaitRrepTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_retryCount
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RreqWaitRrepTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "retryCount",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RreqWaitRrepTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "retryCount") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RreqWaitRrepTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_retryCount
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RreqWaitRrepTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqWaitRrepTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqWaitRrepTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqWaitRrepTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RreqWaitRrepTimer'", field);
    }
}

const char *RreqWaitRrepTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqWaitRrepTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: return long2string(pp->getRetryCount());
        default: return "";
    }
}

void RreqWaitRrepTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: pp->setRetryCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqWaitRrepTimer'", field);
    }
}

omnetpp::cValue RreqWaitRrepTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: return pp->getRetryCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RreqWaitRrepTimer' as cValue -- field index out of range?", field);
    }
}

void RreqWaitRrepTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: pp->setRetryCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqWaitRrepTimer'", field);
    }
}

const char *RreqWaitRrepTimerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RreqWaitRrepTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqWaitRrepTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqWaitRrepTimer *pp = omnetpp::fromAnyPtr<RreqWaitRrepTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqWaitRrepTimer'", field);
    }
}

Register_Class(RreqBackoffTimer)

RreqBackoffTimer::RreqBackoffTimer(const char *name, short kind) : ::inet::dymo::RreqTimer(name, kind)
{
}

RreqBackoffTimer::RreqBackoffTimer(const RreqBackoffTimer& other) : ::inet::dymo::RreqTimer(other)
{
    copy(other);
}

RreqBackoffTimer::~RreqBackoffTimer()
{
}

RreqBackoffTimer& RreqBackoffTimer::operator=(const RreqBackoffTimer& other)
{
    if (this == &other) return *this;
    ::inet::dymo::RreqTimer::operator=(other);
    copy(other);
    return *this;
}

void RreqBackoffTimer::copy(const RreqBackoffTimer& other)
{
    this->retryCount = other.retryCount;
}

void RreqBackoffTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::RreqTimer::parsimPack(b);
    doParsimPacking(b,this->retryCount);
}

void RreqBackoffTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::RreqTimer::parsimUnpack(b);
    doParsimUnpacking(b,this->retryCount);
}

int RreqBackoffTimer::getRetryCount() const
{
    return this->retryCount;
}

void RreqBackoffTimer::setRetryCount(int retryCount)
{
    this->retryCount = retryCount;
}

class RreqBackoffTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_retryCount,
    };
  public:
    RreqBackoffTimerDescriptor();
    virtual ~RreqBackoffTimerDescriptor();

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

Register_ClassDescriptor(RreqBackoffTimerDescriptor)

RreqBackoffTimerDescriptor::RreqBackoffTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RreqBackoffTimer)), "inet::dymo::RreqTimer")
{
    propertyNames = nullptr;
}

RreqBackoffTimerDescriptor::~RreqBackoffTimerDescriptor()
{
    delete[] propertyNames;
}

bool RreqBackoffTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RreqBackoffTimer *>(obj)!=nullptr;
}

const char **RreqBackoffTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqBackoffTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqBackoffTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RreqBackoffTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_retryCount
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RreqBackoffTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "retryCount",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RreqBackoffTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "retryCount") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RreqBackoffTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_retryCount
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RreqBackoffTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqBackoffTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqBackoffTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqBackoffTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RreqBackoffTimer'", field);
    }
}

const char *RreqBackoffTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqBackoffTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: return long2string(pp->getRetryCount());
        default: return "";
    }
}

void RreqBackoffTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: pp->setRetryCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqBackoffTimer'", field);
    }
}

omnetpp::cValue RreqBackoffTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: return pp->getRetryCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RreqBackoffTimer' as cValue -- field index out of range?", field);
    }
}

void RreqBackoffTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        case FIELD_retryCount: pp->setRetryCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqBackoffTimer'", field);
    }
}

const char *RreqBackoffTimerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RreqBackoffTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqBackoffTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqBackoffTimer *pp = omnetpp::fromAnyPtr<RreqBackoffTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqBackoffTimer'", field);
    }
}

Register_Class(RreqHolddownTimer)

RreqHolddownTimer::RreqHolddownTimer(const char *name, short kind) : ::inet::dymo::RreqTimer(name, kind)
{
}

RreqHolddownTimer::RreqHolddownTimer(const RreqHolddownTimer& other) : ::inet::dymo::RreqTimer(other)
{
    copy(other);
}

RreqHolddownTimer::~RreqHolddownTimer()
{
}

RreqHolddownTimer& RreqHolddownTimer::operator=(const RreqHolddownTimer& other)
{
    if (this == &other) return *this;
    ::inet::dymo::RreqTimer::operator=(other);
    copy(other);
    return *this;
}

void RreqHolddownTimer::copy(const RreqHolddownTimer& other)
{
}

void RreqHolddownTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::RreqTimer::parsimPack(b);
}

void RreqHolddownTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::RreqTimer::parsimUnpack(b);
}

class RreqHolddownTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RreqHolddownTimerDescriptor();
    virtual ~RreqHolddownTimerDescriptor();

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

Register_ClassDescriptor(RreqHolddownTimerDescriptor)

RreqHolddownTimerDescriptor::RreqHolddownTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RreqHolddownTimer)), "inet::dymo::RreqTimer")
{
    propertyNames = nullptr;
}

RreqHolddownTimerDescriptor::~RreqHolddownTimerDescriptor()
{
    delete[] propertyNames;
}

bool RreqHolddownTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RreqHolddownTimer *>(obj)!=nullptr;
}

const char **RreqHolddownTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqHolddownTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqHolddownTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RreqHolddownTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RreqHolddownTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RreqHolddownTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RreqHolddownTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RreqHolddownTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqHolddownTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqHolddownTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqHolddownTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RreqHolddownTimer'", field);
    }
}

const char *RreqHolddownTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqHolddownTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RreqHolddownTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqHolddownTimer'", field);
    }
}

omnetpp::cValue RreqHolddownTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RreqHolddownTimer' as cValue -- field index out of range?", field);
    }
}

void RreqHolddownTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqHolddownTimer'", field);
    }
}

const char *RreqHolddownTimerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RreqHolddownTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqHolddownTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RreqHolddownTimer *pp = omnetpp::fromAnyPtr<RreqHolddownTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RreqHolddownTimer'", field);
    }
}

Register_Class(PacketJitterTimer)

PacketJitterTimer::PacketJitterTimer(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
    if (this->jitteredPacket != nullptr) take(this->jitteredPacket);
}

PacketJitterTimer::PacketJitterTimer(const PacketJitterTimer& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PacketJitterTimer::~PacketJitterTimer()
{
    dropAndDelete(this->jitteredPacket);
}

PacketJitterTimer& PacketJitterTimer::operator=(const PacketJitterTimer& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PacketJitterTimer::copy(const PacketJitterTimer& other)
{
    dropAndDelete(this->jitteredPacket);
    this->jitteredPacket = other.jitteredPacket;
    if (this->jitteredPacket != nullptr) {
        this->jitteredPacket = this->jitteredPacket->dup();
        take(this->jitteredPacket);
        this->jitteredPacket->setName(other.jitteredPacket->getName());
    }
}

void PacketJitterTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->jitteredPacket);
}

void PacketJitterTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->jitteredPacket);
}

const ::omnetpp::cPacket * PacketJitterTimer::getJitteredPacket() const
{
    return this->jitteredPacket;
}

void PacketJitterTimer::setJitteredPacket(::omnetpp::cPacket * jitteredPacket)
{
    if (this->jitteredPacket != nullptr) throw omnetpp::cRuntimeError("setJitteredPacket(): a value is already set, remove it first with removeJitteredPacket()");
    this->jitteredPacket = jitteredPacket;
    if (this->jitteredPacket != nullptr) take(this->jitteredPacket);
}

::omnetpp::cPacket * PacketJitterTimer::removeJitteredPacket()
{
    ::omnetpp::cPacket * retval = this->jitteredPacket;
    if (retval != nullptr) drop(retval);
    this->jitteredPacket = nullptr;
    return retval;
}

class PacketJitterTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_jitteredPacket,
    };
  public:
    PacketJitterTimerDescriptor();
    virtual ~PacketJitterTimerDescriptor();

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

Register_ClassDescriptor(PacketJitterTimerDescriptor)

PacketJitterTimerDescriptor::PacketJitterTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::PacketJitterTimer)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

PacketJitterTimerDescriptor::~PacketJitterTimerDescriptor()
{
    delete[] propertyNames;
}

bool PacketJitterTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PacketJitterTimer *>(obj)!=nullptr;
}

const char **PacketJitterTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PacketJitterTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PacketJitterTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int PacketJitterTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE,    // FIELD_jitteredPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PacketJitterTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "jitteredPacket",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PacketJitterTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "jitteredPacket") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *PacketJitterTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::cPacket",    // FIELD_jitteredPacket
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketJitterTimerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_jitteredPacket: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PacketJitterTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_jitteredPacket:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int PacketJitterTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PacketJitterTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PacketJitterTimer'", field);
    }
}

const char *PacketJitterTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: { const ::omnetpp::cPacket * value = pp->getJitteredPacket(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PacketJitterTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: { auto obj = pp->getJitteredPacket(); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void PacketJitterTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketJitterTimer'", field);
    }
}

omnetpp::cValue PacketJitterTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: return omnetpp::toAnyPtr(pp->getJitteredPacket()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PacketJitterTimer' as cValue -- field index out of range?", field);
    }
}

void PacketJitterTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: pp->setJitteredPacket(omnetpp::fromAnyPtr<::omnetpp::cPacket>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketJitterTimer'", field);
    }
}

const char *PacketJitterTimerDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_jitteredPacket: return omnetpp::opp_typename(typeid(::omnetpp::cPacket));
        default: return nullptr;
    };
}

omnetpp::any_ptr PacketJitterTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: return omnetpp::toAnyPtr(pp->getJitteredPacket()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PacketJitterTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketJitterTimer *pp = omnetpp::fromAnyPtr<PacketJitterTimer>(object); (void)pp;
    switch (field) {
        case FIELD_jitteredPacket: pp->setJitteredPacket(omnetpp::fromAnyPtr<::omnetpp::cPacket>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketJitterTimer'", field);
    }
}

Register_Class(DymoPacket)

DymoPacket::DymoPacket() : ::inet::FieldsChunk()
{
}

DymoPacket::DymoPacket(const DymoPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

DymoPacket::~DymoPacket()
{
}

DymoPacket& DymoPacket::operator=(const DymoPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void DymoPacket::copy(const DymoPacket& other)
{
    this->hopLimit = other.hopLimit;
}

void DymoPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->hopLimit);
}

void DymoPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->hopLimit);
}

int DymoPacket::getHopLimit() const
{
    return this->hopLimit;
}

void DymoPacket::setHopLimit(int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

class DymoPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hopLimit,
    };
  public:
    DymoPacketDescriptor();
    virtual ~DymoPacketDescriptor();

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

Register_ClassDescriptor(DymoPacketDescriptor)

DymoPacketDescriptor::DymoPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::DymoPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

DymoPacketDescriptor::~DymoPacketDescriptor()
{
    delete[] propertyNames;
}

bool DymoPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DymoPacket *>(obj)!=nullptr;
}

const char **DymoPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DymoPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DymoPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int DymoPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopLimit
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *DymoPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopLimit",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int DymoPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hopLimit") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *DymoPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_hopLimit
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **DymoPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *DymoPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int DymoPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DymoPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DymoPacket'", field);
    }
}

const char *DymoPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DymoPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopLimit: return long2string(pp->getHopLimit());
        default: return "";
    }
}

void DymoPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopLimit: pp->setHopLimit(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DymoPacket'", field);
    }
}

omnetpp::cValue DymoPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopLimit: return pp->getHopLimit();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DymoPacket' as cValue -- field index out of range?", field);
    }
}

void DymoPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_hopLimit: pp->setHopLimit(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DymoPacket'", field);
    }
}

const char *DymoPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr DymoPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DymoPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DymoPacket *pp = omnetpp::fromAnyPtr<DymoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DymoPacket'", field);
    }
}

Register_Class(RteMsg)

RteMsg::RteMsg() : ::inet::dymo::DymoPacket()
{
}

RteMsg::RteMsg(const RteMsg& other) : ::inet::dymo::DymoPacket(other)
{
    copy(other);
}

RteMsg::~RteMsg()
{
    delete [] this->addedNode;
}

RteMsg& RteMsg::operator=(const RteMsg& other)
{
    if (this == &other) return *this;
    ::inet::dymo::DymoPacket::operator=(other);
    copy(other);
    return *this;
}

void RteMsg::copy(const RteMsg& other)
{
    this->hopCount = other.hopCount;
    this->originatorNode = other.originatorNode;
    this->targetNode = other.targetNode;
    delete [] this->addedNode;
    this->addedNode = (other.addedNode_arraysize==0) ? nullptr : new AddressBlock[other.addedNode_arraysize];
    addedNode_arraysize = other.addedNode_arraysize;
    for (size_t i = 0; i < addedNode_arraysize; i++) {
        this->addedNode[i] = other.addedNode[i];
    }
}

void RteMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::DymoPacket::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->originatorNode);
    doParsimPacking(b,this->targetNode);
    b->pack(addedNode_arraysize);
    doParsimArrayPacking(b,this->addedNode,addedNode_arraysize);
}

void RteMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::DymoPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->originatorNode);
    doParsimUnpacking(b,this->targetNode);
    delete [] this->addedNode;
    b->unpack(addedNode_arraysize);
    if (addedNode_arraysize == 0) {
        this->addedNode = nullptr;
    } else {
        this->addedNode = new AddressBlock[addedNode_arraysize];
        doParsimArrayUnpacking(b,this->addedNode,addedNode_arraysize);
    }
}

int RteMsg::getHopCount() const
{
    return this->hopCount;
}

void RteMsg::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

const AddressBlock& RteMsg::getOriginatorNode() const
{
    return this->originatorNode;
}

void RteMsg::setOriginatorNode(const AddressBlock& originatorNode)
{
    handleChange();
    this->originatorNode = originatorNode;
}

const AddressBlock& RteMsg::getTargetNode() const
{
    return this->targetNode;
}

void RteMsg::setTargetNode(const AddressBlock& targetNode)
{
    handleChange();
    this->targetNode = targetNode;
}

size_t RteMsg::getAddedNodeArraySize() const
{
    return addedNode_arraysize;
}

const AddressBlock& RteMsg::getAddedNode(size_t k) const
{
    if (k >= addedNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addedNode_arraysize, (unsigned long)k);
    return this->addedNode[k];
}

void RteMsg::setAddedNodeArraySize(size_t newSize)
{
    handleChange();
    AddressBlock *addedNode2 = (newSize==0) ? nullptr : new AddressBlock[newSize];
    size_t minSize = addedNode_arraysize < newSize ? addedNode_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        addedNode2[i] = this->addedNode[i];
    delete [] this->addedNode;
    this->addedNode = addedNode2;
    addedNode_arraysize = newSize;
}

void RteMsg::setAddedNode(size_t k, const AddressBlock& addedNode)
{
    if (k >= addedNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addedNode_arraysize, (unsigned long)k);
    handleChange();
    this->addedNode[k] = addedNode;
}

void RteMsg::insertAddedNode(size_t k, const AddressBlock& addedNode)
{
    if (k > addedNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addedNode_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = addedNode_arraysize + 1;
    AddressBlock *addedNode2 = new AddressBlock[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addedNode2[i] = this->addedNode[i];
    addedNode2[k] = addedNode;
    for (i = k + 1; i < newSize; i++)
        addedNode2[i] = this->addedNode[i-1];
    delete [] this->addedNode;
    this->addedNode = addedNode2;
    addedNode_arraysize = newSize;
}

void RteMsg::appendAddedNode(const AddressBlock& addedNode)
{
    insertAddedNode(addedNode_arraysize, addedNode);
}

void RteMsg::eraseAddedNode(size_t k)
{
    if (k >= addedNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addedNode_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = addedNode_arraysize - 1;
    AddressBlock *addedNode2 = (newSize == 0) ? nullptr : new AddressBlock[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addedNode2[i] = this->addedNode[i];
    for (i = k; i < newSize; i++)
        addedNode2[i] = this->addedNode[i+1];
    delete [] this->addedNode;
    this->addedNode = addedNode2;
    addedNode_arraysize = newSize;
}

class RteMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_originatorNode,
        FIELD_targetNode,
        FIELD_addedNode,
    };
  public:
    RteMsgDescriptor();
    virtual ~RteMsgDescriptor();

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

Register_ClassDescriptor(RteMsgDescriptor)

RteMsgDescriptor::RteMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RteMsg)), "inet::dymo::DymoPacket")
{
    propertyNames = nullptr;
}

RteMsgDescriptor::~RteMsgDescriptor()
{
    delete[] propertyNames;
}

bool RteMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RteMsg *>(obj)!=nullptr;
}

const char **RteMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RteMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RteMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int RteMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_originatorNode
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_targetNode
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_addedNode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *RteMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "originatorNode",
        "targetNode",
        "addedNode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int RteMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "originatorNode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "targetNode") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "addedNode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *RteMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_hopCount
        "inet::dymo::AddressBlock",    // FIELD_originatorNode
        "inet::dymo::AddressBlock",    // FIELD_targetNode
        "inet::dymo::AddressBlock",    // FIELD_addedNode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **RteMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RteMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RteMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_addedNode: return pp->getAddedNodeArraySize();
        default: return 0;
    }
}

void RteMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_addedNode: pp->setAddedNodeArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RteMsg'", field);
    }
}

const char *RteMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RteMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_originatorNode: return pp->getOriginatorNode().str();
        case FIELD_targetNode: return pp->getTargetNode().str();
        case FIELD_addedNode: return pp->getAddedNode(i).str();
        default: return "";
    }
}

void RteMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RteMsg'", field);
    }
}

omnetpp::cValue RteMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_originatorNode: return omnetpp::toAnyPtr(&pp->getOriginatorNode()); break;
        case FIELD_targetNode: return omnetpp::toAnyPtr(&pp->getTargetNode()); break;
        case FIELD_addedNode: return omnetpp::toAnyPtr(&pp->getAddedNode(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RteMsg' as cValue -- field index out of range?", field);
    }
}

void RteMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RteMsg'", field);
    }
}

const char *RteMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_originatorNode: return omnetpp::opp_typename(typeid(AddressBlock));
        case FIELD_targetNode: return omnetpp::opp_typename(typeid(AddressBlock));
        case FIELD_addedNode: return omnetpp::opp_typename(typeid(AddressBlock));
        default: return nullptr;
    };
}

omnetpp::any_ptr RteMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_originatorNode: return omnetpp::toAnyPtr(&pp->getOriginatorNode()); break;
        case FIELD_targetNode: return omnetpp::toAnyPtr(&pp->getTargetNode()); break;
        case FIELD_addedNode: return omnetpp::toAnyPtr(&pp->getAddedNode(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RteMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RteMsg *pp = omnetpp::fromAnyPtr<RteMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RteMsg'", field);
    }
}

Register_Class(Rreq)

Rreq::Rreq() : ::inet::dymo::RteMsg()
{
}

Rreq::Rreq(const Rreq& other) : ::inet::dymo::RteMsg(other)
{
    copy(other);
}

Rreq::~Rreq()
{
}

Rreq& Rreq::operator=(const Rreq& other)
{
    if (this == &other) return *this;
    ::inet::dymo::RteMsg::operator=(other);
    copy(other);
    return *this;
}

void Rreq::copy(const Rreq& other)
{
}

void Rreq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::RteMsg::parsimPack(b);
}

void Rreq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::RteMsg::parsimUnpack(b);
}

class RreqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RreqDescriptor();
    virtual ~RreqDescriptor();

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

Register_ClassDescriptor(RreqDescriptor)

RreqDescriptor::RreqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::Rreq)), "inet::dymo::RteMsg")
{
    propertyNames = nullptr;
}

RreqDescriptor::~RreqDescriptor()
{
    delete[] propertyNames;
}

bool RreqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rreq *>(obj)!=nullptr;
}

const char **RreqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RreqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RreqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RreqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RreqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RreqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RreqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RreqDescriptor::getFieldPropertyNames(int field) const
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

const char *RreqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RreqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RreqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rreq'", field);
    }
}

const char *RreqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RreqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RreqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

omnetpp::cValue RreqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rreq' as cValue -- field index out of range?", field);
    }
}

void RreqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

const char *RreqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RreqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RreqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rreq *pp = omnetpp::fromAnyPtr<Rreq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rreq'", field);
    }
}

Register_Class(Rrep)

Rrep::Rrep() : ::inet::dymo::RteMsg()
{
}

Rrep::Rrep(const Rrep& other) : ::inet::dymo::RteMsg(other)
{
    copy(other);
}

Rrep::~Rrep()
{
}

Rrep& Rrep::operator=(const Rrep& other)
{
    if (this == &other) return *this;
    ::inet::dymo::RteMsg::operator=(other);
    copy(other);
    return *this;
}

void Rrep::copy(const Rrep& other)
{
}

void Rrep::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::RteMsg::parsimPack(b);
}

void Rrep::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::RteMsg::parsimUnpack(b);
}

class RrepDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RrepDescriptor();
    virtual ~RrepDescriptor();

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

Register_ClassDescriptor(RrepDescriptor)

RrepDescriptor::RrepDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::Rrep)), "inet::dymo::RteMsg")
{
    propertyNames = nullptr;
}

RrepDescriptor::~RrepDescriptor()
{
    delete[] propertyNames;
}

bool RrepDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rrep *>(obj)!=nullptr;
}

const char **RrepDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RrepDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RrepDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RrepDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RrepDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RrepDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RrepDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RrepDescriptor::getFieldPropertyNames(int field) const
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

const char *RrepDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RrepDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RrepDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rrep'", field);
    }
}

const char *RrepDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RrepDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

omnetpp::cValue RrepDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rrep' as cValue -- field index out of range?", field);
    }
}

void RrepDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

const char *RrepDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RrepDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RrepDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rrep *pp = omnetpp::fromAnyPtr<Rrep>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rrep'", field);
    }
}

Register_Class(RrepAck)

RrepAck::RrepAck() : ::inet::dymo::DymoPacket()
{
}

RrepAck::RrepAck(const RrepAck& other) : ::inet::dymo::DymoPacket(other)
{
    copy(other);
}

RrepAck::~RrepAck()
{
}

RrepAck& RrepAck::operator=(const RrepAck& other)
{
    if (this == &other) return *this;
    ::inet::dymo::DymoPacket::operator=(other);
    copy(other);
    return *this;
}

void RrepAck::copy(const RrepAck& other)
{
}

void RrepAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::DymoPacket::parsimPack(b);
}

void RrepAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::DymoPacket::parsimUnpack(b);
}

class RrepAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RrepAckDescriptor();
    virtual ~RrepAckDescriptor();

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

Register_ClassDescriptor(RrepAckDescriptor)

RrepAckDescriptor::RrepAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::RrepAck)), "inet::dymo::DymoPacket")
{
    propertyNames = nullptr;
}

RrepAckDescriptor::~RrepAckDescriptor()
{
    delete[] propertyNames;
}

bool RrepAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RrepAck *>(obj)!=nullptr;
}

const char **RrepAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RrepAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RrepAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RrepAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RrepAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RrepAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RrepAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RrepAckDescriptor::getFieldPropertyNames(int field) const
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

const char *RrepAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RrepAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RrepAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RrepAck'", field);
    }
}

const char *RrepAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RrepAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RrepAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

omnetpp::cValue RrepAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RrepAck' as cValue -- field index out of range?", field);
    }
}

void RrepAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

const char *RrepAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RrepAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RrepAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RrepAck *pp = omnetpp::fromAnyPtr<RrepAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RrepAck'", field);
    }
}

Register_Class(Rerr)

Rerr::Rerr() : ::inet::dymo::DymoPacket()
{
}

Rerr::Rerr(const Rerr& other) : ::inet::dymo::DymoPacket(other)
{
    copy(other);
}

Rerr::~Rerr()
{
    delete [] this->unreachableNode;
}

Rerr& Rerr::operator=(const Rerr& other)
{
    if (this == &other) return *this;
    ::inet::dymo::DymoPacket::operator=(other);
    copy(other);
    return *this;
}

void Rerr::copy(const Rerr& other)
{
    delete [] this->unreachableNode;
    this->unreachableNode = (other.unreachableNode_arraysize==0) ? nullptr : new AddressBlock[other.unreachableNode_arraysize];
    unreachableNode_arraysize = other.unreachableNode_arraysize;
    for (size_t i = 0; i < unreachableNode_arraysize; i++) {
        this->unreachableNode[i] = other.unreachableNode[i];
    }
}

void Rerr::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::dymo::DymoPacket::parsimPack(b);
    b->pack(unreachableNode_arraysize);
    doParsimArrayPacking(b,this->unreachableNode,unreachableNode_arraysize);
}

void Rerr::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::dymo::DymoPacket::parsimUnpack(b);
    delete [] this->unreachableNode;
    b->unpack(unreachableNode_arraysize);
    if (unreachableNode_arraysize == 0) {
        this->unreachableNode = nullptr;
    } else {
        this->unreachableNode = new AddressBlock[unreachableNode_arraysize];
        doParsimArrayUnpacking(b,this->unreachableNode,unreachableNode_arraysize);
    }
}

size_t Rerr::getUnreachableNodeArraySize() const
{
    return unreachableNode_arraysize;
}

const AddressBlock& Rerr::getUnreachableNode(size_t k) const
{
    if (k >= unreachableNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNode_arraysize, (unsigned long)k);
    return this->unreachableNode[k];
}

void Rerr::setUnreachableNodeArraySize(size_t newSize)
{
    handleChange();
    AddressBlock *unreachableNode2 = (newSize==0) ? nullptr : new AddressBlock[newSize];
    size_t minSize = unreachableNode_arraysize < newSize ? unreachableNode_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unreachableNode2[i] = this->unreachableNode[i];
    delete [] this->unreachableNode;
    this->unreachableNode = unreachableNode2;
    unreachableNode_arraysize = newSize;
}

void Rerr::setUnreachableNode(size_t k, const AddressBlock& unreachableNode)
{
    if (k >= unreachableNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNode_arraysize, (unsigned long)k);
    handleChange();
    this->unreachableNode[k] = unreachableNode;
}

void Rerr::insertUnreachableNode(size_t k, const AddressBlock& unreachableNode)
{
    if (k > unreachableNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNode_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = unreachableNode_arraysize + 1;
    AddressBlock *unreachableNode2 = new AddressBlock[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNode2[i] = this->unreachableNode[i];
    unreachableNode2[k] = unreachableNode;
    for (i = k + 1; i < newSize; i++)
        unreachableNode2[i] = this->unreachableNode[i-1];
    delete [] this->unreachableNode;
    this->unreachableNode = unreachableNode2;
    unreachableNode_arraysize = newSize;
}

void Rerr::appendUnreachableNode(const AddressBlock& unreachableNode)
{
    insertUnreachableNode(unreachableNode_arraysize, unreachableNode);
}

void Rerr::eraseUnreachableNode(size_t k)
{
    if (k >= unreachableNode_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unreachableNode_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = unreachableNode_arraysize - 1;
    AddressBlock *unreachableNode2 = (newSize == 0) ? nullptr : new AddressBlock[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unreachableNode2[i] = this->unreachableNode[i];
    for (i = k; i < newSize; i++)
        unreachableNode2[i] = this->unreachableNode[i+1];
    delete [] this->unreachableNode;
    this->unreachableNode = unreachableNode2;
    unreachableNode_arraysize = newSize;
}

class RerrDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unreachableNode,
    };
  public:
    RerrDescriptor();
    virtual ~RerrDescriptor();

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

Register_ClassDescriptor(RerrDescriptor)

RerrDescriptor::RerrDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::dymo::Rerr)), "inet::dymo::DymoPacket")
{
    propertyNames = nullptr;
}

RerrDescriptor::~RerrDescriptor()
{
    delete[] propertyNames;
}

bool RerrDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Rerr *>(obj)!=nullptr;
}

const char **RerrDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RerrDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RerrDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RerrDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_unreachableNode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RerrDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unreachableNode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RerrDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unreachableNode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RerrDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::dymo::AddressBlock",    // FIELD_unreachableNode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RerrDescriptor::getFieldPropertyNames(int field) const
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

const char *RerrDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RerrDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNode: return pp->getUnreachableNodeArraySize();
        default: return 0;
    }
}

void RerrDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNode: pp->setUnreachableNodeArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Rerr'", field);
    }
}

const char *RerrDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RerrDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNode: return pp->getUnreachableNode(i).str();
        default: return "";
    }
}

void RerrDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

omnetpp::cValue RerrDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNode: return omnetpp::toAnyPtr(&pp->getUnreachableNode(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Rerr' as cValue -- field index out of range?", field);
    }
}

void RerrDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

const char *RerrDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_unreachableNode: return omnetpp::opp_typename(typeid(AddressBlock));
        default: return nullptr;
    };
}

omnetpp::any_ptr RerrDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        case FIELD_unreachableNode: return omnetpp::toAnyPtr(&pp->getUnreachableNode(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RerrDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Rerr *pp = omnetpp::fromAnyPtr<Rerr>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Rerr'", field);
    }
}

}  // namespace dymo
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

