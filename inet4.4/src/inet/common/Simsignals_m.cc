//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/Simsignals.msg.
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
#include "Simsignals_m.h"

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

Register_Enum(inet::PacketDropReason, (inet::PacketDropReason::ADDRESS_RESOLUTION_FAILED, inet::PacketDropReason::FORWARDING_DISABLED, inet::PacketDropReason::HOP_LIMIT_REACHED, inet::PacketDropReason::INCORRECTLY_RECEIVED, inet::PacketDropReason::INTERFACE_DOWN, inet::PacketDropReason::NO_CARRIER, inet::PacketDropReason::NO_INTERFACE_FOUND, inet::PacketDropReason::NO_ROUTE_FOUND, inet::PacketDropReason::NOT_ADDRESSED_TO_US, inet::PacketDropReason::QUEUE_OVERFLOW, inet::PacketDropReason::RETRY_LIMIT_REACHED, inet::PacketDropReason::LIFETIME_EXPIRED, inet::PacketDropReason::CONGESTION, inet::PacketDropReason::NO_PROTOCOL_FOUND, inet::PacketDropReason::NO_PORT_FOUND, inet::PacketDropReason::DUPLICATE_DETECTED, inet::PacketDropReason::OTHER_PACKET_DROP));

Register_Class(PacketDropDetails)

PacketDropDetails::PacketDropDetails() : ::omnetpp::cObject()
{
}

PacketDropDetails::PacketDropDetails(const PacketDropDetails& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

PacketDropDetails::~PacketDropDetails()
{
}

PacketDropDetails& PacketDropDetails::operator=(const PacketDropDetails& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void PacketDropDetails::copy(const PacketDropDetails& other)
{
    this->reason = other.reason;
    this->limit = other.limit;
}

void PacketDropDetails::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->reason);
    doParsimPacking(b,this->limit);
}

void PacketDropDetails::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->reason);
    doParsimUnpacking(b,this->limit);
}

PacketDropReason PacketDropDetails::getReason() const
{
    return this->reason;
}

void PacketDropDetails::setReason(PacketDropReason reason)
{
    this->reason = reason;
}

int PacketDropDetails::getLimit() const
{
    return this->limit;
}

void PacketDropDetails::setLimit(int limit)
{
    this->limit = limit;
}

class PacketDropDetailsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reason,
        FIELD_limit,
    };
  public:
    PacketDropDetailsDescriptor();
    virtual ~PacketDropDetailsDescriptor();

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

Register_ClassDescriptor(PacketDropDetailsDescriptor)

PacketDropDetailsDescriptor::PacketDropDetailsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PacketDropDetails)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

PacketDropDetailsDescriptor::~PacketDropDetailsDescriptor()
{
    delete[] propertyNames;
}

bool PacketDropDetailsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PacketDropDetails *>(obj)!=nullptr;
}

const char **PacketDropDetailsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PacketDropDetailsDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PacketDropDetailsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int PacketDropDetailsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_reason
        FD_ISEDITABLE,    // FIELD_limit
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *PacketDropDetailsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reason",
        "limit",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int PacketDropDetailsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reason") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "limit") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *PacketDropDetailsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::PacketDropReason",    // FIELD_reason
        "int",    // FIELD_limit
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **PacketDropDetailsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reason: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PacketDropDetailsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reason:
            if (!strcmp(propertyName, "enum")) return "inet::PacketDropReason";
            return nullptr;
        default: return nullptr;
    }
}

int PacketDropDetailsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PacketDropDetailsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PacketDropDetails'", field);
    }
}

const char *PacketDropDetailsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PacketDropDetailsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        case FIELD_reason: return enum2string(pp->getReason(), "inet::PacketDropReason");
        case FIELD_limit: return long2string(pp->getLimit());
        default: return "";
    }
}

void PacketDropDetailsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        case FIELD_limit: pp->setLimit(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDropDetails'", field);
    }
}

omnetpp::cValue PacketDropDetailsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        case FIELD_reason: return static_cast<int>(pp->getReason());
        case FIELD_limit: return pp->getLimit();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PacketDropDetails' as cValue -- field index out of range?", field);
    }
}

void PacketDropDetailsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        case FIELD_limit: pp->setLimit(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDropDetails'", field);
    }
}

const char *PacketDropDetailsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PacketDropDetailsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PacketDropDetailsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PacketDropDetails *pp = omnetpp::fromAnyPtr<PacketDropDetails>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PacketDropDetails'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

