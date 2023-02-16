//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/pim/PimPacket.msg.
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
#include "PimPacket_m.h"

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

Register_Enum(inet::PimPacketType, (inet::PimPacketType::Hello, inet::PimPacketType::Register, inet::PimPacketType::RegisterStop, inet::PimPacketType::JoinPrune, inet::PimPacketType::Bootstrap, inet::PimPacketType::Assert, inet::PimPacketType::Graft, inet::PimPacketType::GraftAck, inet::PimPacketType::CandidateRPAdvertisement, inet::PimPacketType::StateRefresh));

Register_Enum(inet::PimHelloOptionType, (inet::PimHelloOptionType::Holdtime, inet::PimHelloOptionType::LANPruneDelay, inet::PimHelloOptionType::DRPriority, inet::PimHelloOptionType::GenerationID, inet::PimHelloOptionType::StateRefreshCapable, inet::PimHelloOptionType::AddressList));

EncodedUnicastAddress::EncodedUnicastAddress()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const EncodedUnicastAddress& a)
{
    doParsimPacking(b,a.unicastAddress);
}

void __doUnpacking(omnetpp::cCommBuffer *b, EncodedUnicastAddress& a)
{
    doParsimUnpacking(b,a.unicastAddress);
}

class EncodedUnicastAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unicastAddress,
    };
  public:
    EncodedUnicastAddressDescriptor();
    virtual ~EncodedUnicastAddressDescriptor();

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

Register_ClassDescriptor(EncodedUnicastAddressDescriptor)

EncodedUnicastAddressDescriptor::EncodedUnicastAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EncodedUnicastAddress)), "")
{
    propertyNames = nullptr;
}

EncodedUnicastAddressDescriptor::~EncodedUnicastAddressDescriptor()
{
    delete[] propertyNames;
}

bool EncodedUnicastAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EncodedUnicastAddress *>(obj)!=nullptr;
}

const char **EncodedUnicastAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EncodedUnicastAddressDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EncodedUnicastAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int EncodedUnicastAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_unicastAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *EncodedUnicastAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unicastAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int EncodedUnicastAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unicastAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *EncodedUnicastAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_unicastAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **EncodedUnicastAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *EncodedUnicastAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EncodedUnicastAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EncodedUnicastAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EncodedUnicastAddress'", field);
    }
}

const char *EncodedUnicastAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EncodedUnicastAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        case FIELD_unicastAddress: return pp->unicastAddress.str();
        default: return "";
    }
}

void EncodedUnicastAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedUnicastAddress'", field);
    }
}

omnetpp::cValue EncodedUnicastAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        case FIELD_unicastAddress: return omnetpp::toAnyPtr(&pp->unicastAddress); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EncodedUnicastAddress' as cValue -- field index out of range?", field);
    }
}

void EncodedUnicastAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedUnicastAddress'", field);
    }
}

const char *EncodedUnicastAddressDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EncodedUnicastAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        case FIELD_unicastAddress: return omnetpp::toAnyPtr(&pp->unicastAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EncodedUnicastAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedUnicastAddress *pp = omnetpp::fromAnyPtr<EncodedUnicastAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedUnicastAddress'", field);
    }
}

EncodedGroupAddress::EncodedGroupAddress()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const EncodedGroupAddress& a)
{
    doParsimPacking(b,a.B);
    doParsimPacking(b,a.reserved);
    doParsimPacking(b,a.Z);
    doParsimPacking(b,a.maskLength);
    doParsimPacking(b,a.groupAddress);
}

void __doUnpacking(omnetpp::cCommBuffer *b, EncodedGroupAddress& a)
{
    doParsimUnpacking(b,a.B);
    doParsimUnpacking(b,a.reserved);
    doParsimUnpacking(b,a.Z);
    doParsimUnpacking(b,a.maskLength);
    doParsimUnpacking(b,a.groupAddress);
}

class EncodedGroupAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_B,
        FIELD_reserved,
        FIELD_Z,
        FIELD_maskLength,
        FIELD_groupAddress,
    };
  public:
    EncodedGroupAddressDescriptor();
    virtual ~EncodedGroupAddressDescriptor();

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

Register_ClassDescriptor(EncodedGroupAddressDescriptor)

EncodedGroupAddressDescriptor::EncodedGroupAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EncodedGroupAddress)), "")
{
    propertyNames = nullptr;
}

EncodedGroupAddressDescriptor::~EncodedGroupAddressDescriptor()
{
    delete[] propertyNames;
}

bool EncodedGroupAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EncodedGroupAddress *>(obj)!=nullptr;
}

const char **EncodedGroupAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EncodedGroupAddressDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EncodedGroupAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int EncodedGroupAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_B
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_Z
        FD_ISEDITABLE,    // FIELD_maskLength
        0,    // FIELD_groupAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *EncodedGroupAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "B",
        "reserved",
        "Z",
        "maskLength",
        "groupAddress",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int EncodedGroupAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "B") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "Z") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "maskLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *EncodedGroupAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_B
        "short",    // FIELD_reserved
        "bool",    // FIELD_Z
        "short",    // FIELD_maskLength
        "inet::L3Address",    // FIELD_groupAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **EncodedGroupAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *EncodedGroupAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EncodedGroupAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EncodedGroupAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EncodedGroupAddress'", field);
    }
}

const char *EncodedGroupAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EncodedGroupAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        case FIELD_B: return bool2string(pp->B);
        case FIELD_reserved: return long2string(pp->reserved);
        case FIELD_Z: return bool2string(pp->Z);
        case FIELD_maskLength: return long2string(pp->maskLength);
        case FIELD_groupAddress: return pp->groupAddress.str();
        default: return "";
    }
}

void EncodedGroupAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        case FIELD_B: pp->B = string2bool(value); break;
        case FIELD_reserved: pp->reserved = string2long(value); break;
        case FIELD_Z: pp->Z = string2bool(value); break;
        case FIELD_maskLength: pp->maskLength = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedGroupAddress'", field);
    }
}

omnetpp::cValue EncodedGroupAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        case FIELD_B: return pp->B;
        case FIELD_reserved: return pp->reserved;
        case FIELD_Z: return pp->Z;
        case FIELD_maskLength: return pp->maskLength;
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->groupAddress); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EncodedGroupAddress' as cValue -- field index out of range?", field);
    }
}

void EncodedGroupAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        case FIELD_B: pp->B = value.boolValue(); break;
        case FIELD_reserved: pp->reserved = omnetpp::checked_int_cast<short>(value.intValue()); break;
        case FIELD_Z: pp->Z = value.boolValue(); break;
        case FIELD_maskLength: pp->maskLength = omnetpp::checked_int_cast<short>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedGroupAddress'", field);
    }
}

const char *EncodedGroupAddressDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EncodedGroupAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->groupAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EncodedGroupAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedGroupAddress *pp = omnetpp::fromAnyPtr<EncodedGroupAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedGroupAddress'", field);
    }
}

EncodedSourceAddress::EncodedSourceAddress()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const EncodedSourceAddress& a)
{
    doParsimPacking(b,a.reserved);
    doParsimPacking(b,a.S);
    doParsimPacking(b,a.W);
    doParsimPacking(b,a.R);
    doParsimPacking(b,a.maskLength);
    doParsimPacking(b,a.sourceAddress);
}

void __doUnpacking(omnetpp::cCommBuffer *b, EncodedSourceAddress& a)
{
    doParsimUnpacking(b,a.reserved);
    doParsimUnpacking(b,a.S);
    doParsimUnpacking(b,a.W);
    doParsimUnpacking(b,a.R);
    doParsimUnpacking(b,a.maskLength);
    doParsimUnpacking(b,a.sourceAddress);
}

class EncodedSourceAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_S,
        FIELD_W,
        FIELD_R,
        FIELD_maskLength,
        FIELD_sourceAddress,
    };
  public:
    EncodedSourceAddressDescriptor();
    virtual ~EncodedSourceAddressDescriptor();

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

Register_ClassDescriptor(EncodedSourceAddressDescriptor)

EncodedSourceAddressDescriptor::EncodedSourceAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EncodedSourceAddress)), "")
{
    propertyNames = nullptr;
}

EncodedSourceAddressDescriptor::~EncodedSourceAddressDescriptor()
{
    delete[] propertyNames;
}

bool EncodedSourceAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EncodedSourceAddress *>(obj)!=nullptr;
}

const char **EncodedSourceAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EncodedSourceAddressDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EncodedSourceAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int EncodedSourceAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_S
        FD_ISEDITABLE,    // FIELD_W
        FD_ISEDITABLE,    // FIELD_R
        FD_ISEDITABLE,    // FIELD_maskLength
        0,    // FIELD_sourceAddress
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *EncodedSourceAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "S",
        "W",
        "R",
        "maskLength",
        "sourceAddress",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int EncodedSourceAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "S") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "W") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "R") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "maskLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "sourceAddress") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *EncodedSourceAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_reserved
        "bool",    // FIELD_S
        "bool",    // FIELD_W
        "bool",    // FIELD_R
        "short",    // FIELD_maskLength
        "inet::L3Address",    // FIELD_sourceAddress
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **EncodedSourceAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *EncodedSourceAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EncodedSourceAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EncodedSourceAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EncodedSourceAddress'", field);
    }
}

const char *EncodedSourceAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EncodedSourceAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return long2string(pp->reserved);
        case FIELD_S: return bool2string(pp->S);
        case FIELD_W: return bool2string(pp->W);
        case FIELD_R: return bool2string(pp->R);
        case FIELD_maskLength: return long2string(pp->maskLength);
        case FIELD_sourceAddress: return pp->sourceAddress.str();
        default: return "";
    }
}

void EncodedSourceAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = string2long(value); break;
        case FIELD_S: pp->S = string2bool(value); break;
        case FIELD_W: pp->W = string2bool(value); break;
        case FIELD_R: pp->R = string2bool(value); break;
        case FIELD_maskLength: pp->maskLength = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedSourceAddress'", field);
    }
}

omnetpp::cValue EncodedSourceAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return pp->reserved;
        case FIELD_S: return pp->S;
        case FIELD_W: return pp->W;
        case FIELD_R: return pp->R;
        case FIELD_maskLength: return pp->maskLength;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->sourceAddress); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EncodedSourceAddress' as cValue -- field index out of range?", field);
    }
}

void EncodedSourceAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = omnetpp::checked_int_cast<short>(value.intValue()); break;
        case FIELD_S: pp->S = value.boolValue(); break;
        case FIELD_W: pp->W = value.boolValue(); break;
        case FIELD_R: pp->R = value.boolValue(); break;
        case FIELD_maskLength: pp->maskLength = omnetpp::checked_int_cast<short>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedSourceAddress'", field);
    }
}

const char *EncodedSourceAddressDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EncodedSourceAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->sourceAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EncodedSourceAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EncodedSourceAddress *pp = omnetpp::fromAnyPtr<EncodedSourceAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EncodedSourceAddress'", field);
    }
}

Register_Class(HelloOption)

HelloOption::HelloOption() : ::omnetpp::cObject()
{
}

HelloOption::HelloOption(const HelloOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

HelloOption::~HelloOption()
{
}

HelloOption& HelloOption::operator=(const HelloOption& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void HelloOption::copy(const HelloOption& other)
{
    this->type = other.type;
}

void HelloOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
}

void HelloOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
}

PimHelloOptionType HelloOption::getType() const
{
    return this->type;
}

void HelloOption::setType(PimHelloOptionType type)
{
    this->type = type;
}

class HelloOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
    };
  public:
    HelloOptionDescriptor();
    virtual ~HelloOptionDescriptor();

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

Register_ClassDescriptor(HelloOptionDescriptor)

HelloOptionDescriptor::HelloOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HelloOption)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

HelloOptionDescriptor::~HelloOptionDescriptor()
{
    delete[] propertyNames;
}

bool HelloOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HelloOption *>(obj)!=nullptr;
}

const char **HelloOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HelloOptionDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HelloOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HelloOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HelloOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HelloOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HelloOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::PimHelloOptionType",    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloOptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HelloOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::PimHelloOptionType";
            return nullptr;
        default: return nullptr;
    }
}

int HelloOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HelloOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HelloOption'", field);
    }
}

const char *HelloOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HelloOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::PimHelloOptionType");
        default: return "";
    }
}

void HelloOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloOption'", field);
    }
}

omnetpp::cValue HelloOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HelloOption' as cValue -- field index out of range?", field);
    }
}

void HelloOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloOption'", field);
    }
}

const char *HelloOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HelloOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HelloOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloOption *pp = omnetpp::fromAnyPtr<HelloOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloOption'", field);
    }
}

Register_Class(HoldtimeOption)

HoldtimeOption::HoldtimeOption() : ::inet::HelloOption()
{
    this->setType(Holdtime);

}

HoldtimeOption::HoldtimeOption(const HoldtimeOption& other) : ::inet::HelloOption(other)
{
    copy(other);
}

HoldtimeOption::~HoldtimeOption()
{
}

HoldtimeOption& HoldtimeOption::operator=(const HoldtimeOption& other)
{
    if (this == &other) return *this;
    ::inet::HelloOption::operator=(other);
    copy(other);
    return *this;
}

void HoldtimeOption::copy(const HoldtimeOption& other)
{
    this->holdTime = other.holdTime;
}

void HoldtimeOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::HelloOption::parsimPack(b);
    doParsimPacking(b,this->holdTime);
}

void HoldtimeOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::HelloOption::parsimUnpack(b);
    doParsimUnpacking(b,this->holdTime);
}

uint16_t HoldtimeOption::getHoldTime() const
{
    return this->holdTime;
}

void HoldtimeOption::setHoldTime(uint16_t holdTime)
{
    this->holdTime = holdTime;
}

class HoldtimeOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_holdTime,
    };
  public:
    HoldtimeOptionDescriptor();
    virtual ~HoldtimeOptionDescriptor();

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

Register_ClassDescriptor(HoldtimeOptionDescriptor)

HoldtimeOptionDescriptor::HoldtimeOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HoldtimeOption)), "inet::HelloOption")
{
    propertyNames = nullptr;
}

HoldtimeOptionDescriptor::~HoldtimeOptionDescriptor()
{
    delete[] propertyNames;
}

bool HoldtimeOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HoldtimeOption *>(obj)!=nullptr;
}

const char **HoldtimeOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HoldtimeOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HoldtimeOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HoldtimeOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_holdTime
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HoldtimeOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "holdTime",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HoldtimeOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "holdTime") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HoldtimeOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_holdTime
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HoldtimeOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *HoldtimeOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HoldtimeOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HoldtimeOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HoldtimeOption'", field);
    }
}

const char *HoldtimeOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HoldtimeOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: return ulong2string(pp->getHoldTime());
        default: return "";
    }
}

void HoldtimeOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: pp->setHoldTime(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HoldtimeOption'", field);
    }
}

omnetpp::cValue HoldtimeOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: return (omnetpp::intval_t)(pp->getHoldTime());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HoldtimeOption' as cValue -- field index out of range?", field);
    }
}

void HoldtimeOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        case FIELD_holdTime: pp->setHoldTime(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HoldtimeOption'", field);
    }
}

const char *HoldtimeOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HoldtimeOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HoldtimeOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HoldtimeOption *pp = omnetpp::fromAnyPtr<HoldtimeOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HoldtimeOption'", field);
    }
}

Register_Class(LanPruneDelayOption)

LanPruneDelayOption::LanPruneDelayOption() : ::inet::HelloOption()
{
    this->setType(LANPruneDelay);

}

LanPruneDelayOption::LanPruneDelayOption(const LanPruneDelayOption& other) : ::inet::HelloOption(other)
{
    copy(other);
}

LanPruneDelayOption::~LanPruneDelayOption()
{
}

LanPruneDelayOption& LanPruneDelayOption::operator=(const LanPruneDelayOption& other)
{
    if (this == &other) return *this;
    ::inet::HelloOption::operator=(other);
    copy(other);
    return *this;
}

void LanPruneDelayOption::copy(const LanPruneDelayOption& other)
{
    this->T = other.T;
    this->propagationDelay = other.propagationDelay;
    this->overrideInterval = other.overrideInterval;
}

void LanPruneDelayOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::HelloOption::parsimPack(b);
    doParsimPacking(b,this->T);
    doParsimPacking(b,this->propagationDelay);
    doParsimPacking(b,this->overrideInterval);
}

void LanPruneDelayOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::HelloOption::parsimUnpack(b);
    doParsimUnpacking(b,this->T);
    doParsimUnpacking(b,this->propagationDelay);
    doParsimUnpacking(b,this->overrideInterval);
}

bool LanPruneDelayOption::getT() const
{
    return this->T;
}

void LanPruneDelayOption::setT(bool T)
{
    this->T = T;
}

uint16_t LanPruneDelayOption::getPropagationDelay() const
{
    return this->propagationDelay;
}

void LanPruneDelayOption::setPropagationDelay(uint16_t propagationDelay)
{
    this->propagationDelay = propagationDelay;
}

uint16_t LanPruneDelayOption::getOverrideInterval() const
{
    return this->overrideInterval;
}

void LanPruneDelayOption::setOverrideInterval(uint16_t overrideInterval)
{
    this->overrideInterval = overrideInterval;
}

class LanPruneDelayOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_T,
        FIELD_propagationDelay,
        FIELD_overrideInterval,
    };
  public:
    LanPruneDelayOptionDescriptor();
    virtual ~LanPruneDelayOptionDescriptor();

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

Register_ClassDescriptor(LanPruneDelayOptionDescriptor)

LanPruneDelayOptionDescriptor::LanPruneDelayOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LanPruneDelayOption)), "inet::HelloOption")
{
    propertyNames = nullptr;
}

LanPruneDelayOptionDescriptor::~LanPruneDelayOptionDescriptor()
{
    delete[] propertyNames;
}

bool LanPruneDelayOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LanPruneDelayOption *>(obj)!=nullptr;
}

const char **LanPruneDelayOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LanPruneDelayOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LanPruneDelayOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int LanPruneDelayOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_T
        FD_ISEDITABLE,    // FIELD_propagationDelay
        FD_ISEDITABLE,    // FIELD_overrideInterval
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *LanPruneDelayOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "T",
        "propagationDelay",
        "overrideInterval",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int LanPruneDelayOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "T") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "propagationDelay") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "overrideInterval") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *LanPruneDelayOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_T
        "uint16_t",    // FIELD_propagationDelay
        "uint16_t",    // FIELD_overrideInterval
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **LanPruneDelayOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *LanPruneDelayOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LanPruneDelayOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LanPruneDelayOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LanPruneDelayOption'", field);
    }
}

const char *LanPruneDelayOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LanPruneDelayOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        case FIELD_T: return bool2string(pp->getT());
        case FIELD_propagationDelay: return ulong2string(pp->getPropagationDelay());
        case FIELD_overrideInterval: return ulong2string(pp->getOverrideInterval());
        default: return "";
    }
}

void LanPruneDelayOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        case FIELD_T: pp->setT(string2bool(value)); break;
        case FIELD_propagationDelay: pp->setPropagationDelay(string2ulong(value)); break;
        case FIELD_overrideInterval: pp->setOverrideInterval(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LanPruneDelayOption'", field);
    }
}

omnetpp::cValue LanPruneDelayOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        case FIELD_T: return pp->getT();
        case FIELD_propagationDelay: return (omnetpp::intval_t)(pp->getPropagationDelay());
        case FIELD_overrideInterval: return (omnetpp::intval_t)(pp->getOverrideInterval());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LanPruneDelayOption' as cValue -- field index out of range?", field);
    }
}

void LanPruneDelayOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        case FIELD_T: pp->setT(value.boolValue()); break;
        case FIELD_propagationDelay: pp->setPropagationDelay(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_overrideInterval: pp->setOverrideInterval(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LanPruneDelayOption'", field);
    }
}

const char *LanPruneDelayOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LanPruneDelayOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LanPruneDelayOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LanPruneDelayOption *pp = omnetpp::fromAnyPtr<LanPruneDelayOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LanPruneDelayOption'", field);
    }
}

Register_Class(DrPriorityOption)

DrPriorityOption::DrPriorityOption() : ::inet::HelloOption()
{
    this->setType(DRPriority);

}

DrPriorityOption::DrPriorityOption(const DrPriorityOption& other) : ::inet::HelloOption(other)
{
    copy(other);
}

DrPriorityOption::~DrPriorityOption()
{
}

DrPriorityOption& DrPriorityOption::operator=(const DrPriorityOption& other)
{
    if (this == &other) return *this;
    ::inet::HelloOption::operator=(other);
    copy(other);
    return *this;
}

void DrPriorityOption::copy(const DrPriorityOption& other)
{
    this->priority = other.priority;
}

void DrPriorityOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::HelloOption::parsimPack(b);
    doParsimPacking(b,this->priority);
}

void DrPriorityOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::HelloOption::parsimUnpack(b);
    doParsimUnpacking(b,this->priority);
}

uint32_t DrPriorityOption::getPriority() const
{
    return this->priority;
}

void DrPriorityOption::setPriority(uint32_t priority)
{
    this->priority = priority;
}

class DrPriorityOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_priority,
    };
  public:
    DrPriorityOptionDescriptor();
    virtual ~DrPriorityOptionDescriptor();

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

Register_ClassDescriptor(DrPriorityOptionDescriptor)

DrPriorityOptionDescriptor::DrPriorityOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::DrPriorityOption)), "inet::HelloOption")
{
    propertyNames = nullptr;
}

DrPriorityOptionDescriptor::~DrPriorityOptionDescriptor()
{
    delete[] propertyNames;
}

bool DrPriorityOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DrPriorityOption *>(obj)!=nullptr;
}

const char **DrPriorityOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DrPriorityOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DrPriorityOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int DrPriorityOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_priority
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *DrPriorityOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "priority",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int DrPriorityOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *DrPriorityOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_priority
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **DrPriorityOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *DrPriorityOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int DrPriorityOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DrPriorityOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DrPriorityOption'", field);
    }
}

const char *DrPriorityOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DrPriorityOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return ulong2string(pp->getPriority());
        default: return "";
    }
}

void DrPriorityOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DrPriorityOption'", field);
    }
}

omnetpp::cValue DrPriorityOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        case FIELD_priority: return (omnetpp::intval_t)(pp->getPriority());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DrPriorityOption' as cValue -- field index out of range?", field);
    }
}

void DrPriorityOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DrPriorityOption'", field);
    }
}

const char *DrPriorityOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr DrPriorityOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DrPriorityOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DrPriorityOption *pp = omnetpp::fromAnyPtr<DrPriorityOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DrPriorityOption'", field);
    }
}

Register_Class(GenerationIdOption)

GenerationIdOption::GenerationIdOption() : ::inet::HelloOption()
{
    this->setType(GenerationID);

}

GenerationIdOption::GenerationIdOption(const GenerationIdOption& other) : ::inet::HelloOption(other)
{
    copy(other);
}

GenerationIdOption::~GenerationIdOption()
{
}

GenerationIdOption& GenerationIdOption::operator=(const GenerationIdOption& other)
{
    if (this == &other) return *this;
    ::inet::HelloOption::operator=(other);
    copy(other);
    return *this;
}

void GenerationIdOption::copy(const GenerationIdOption& other)
{
    this->generationID = other.generationID;
}

void GenerationIdOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::HelloOption::parsimPack(b);
    doParsimPacking(b,this->generationID);
}

void GenerationIdOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::HelloOption::parsimUnpack(b);
    doParsimUnpacking(b,this->generationID);
}

uint32_t GenerationIdOption::getGenerationID() const
{
    return this->generationID;
}

void GenerationIdOption::setGenerationID(uint32_t generationID)
{
    this->generationID = generationID;
}

class GenerationIdOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_generationID,
    };
  public:
    GenerationIdOptionDescriptor();
    virtual ~GenerationIdOptionDescriptor();

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

Register_ClassDescriptor(GenerationIdOptionDescriptor)

GenerationIdOptionDescriptor::GenerationIdOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GenerationIdOption)), "inet::HelloOption")
{
    propertyNames = nullptr;
}

GenerationIdOptionDescriptor::~GenerationIdOptionDescriptor()
{
    delete[] propertyNames;
}

bool GenerationIdOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenerationIdOption *>(obj)!=nullptr;
}

const char **GenerationIdOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GenerationIdOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GenerationIdOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int GenerationIdOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_generationID
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *GenerationIdOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "generationID",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int GenerationIdOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "generationID") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *GenerationIdOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_generationID
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **GenerationIdOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *GenerationIdOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GenerationIdOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GenerationIdOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GenerationIdOption'", field);
    }
}

const char *GenerationIdOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GenerationIdOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        case FIELD_generationID: return ulong2string(pp->getGenerationID());
        default: return "";
    }
}

void GenerationIdOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        case FIELD_generationID: pp->setGenerationID(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenerationIdOption'", field);
    }
}

omnetpp::cValue GenerationIdOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        case FIELD_generationID: return (omnetpp::intval_t)(pp->getGenerationID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GenerationIdOption' as cValue -- field index out of range?", field);
    }
}

void GenerationIdOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        case FIELD_generationID: pp->setGenerationID(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenerationIdOption'", field);
    }
}

const char *GenerationIdOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GenerationIdOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GenerationIdOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GenerationIdOption *pp = omnetpp::fromAnyPtr<GenerationIdOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenerationIdOption'", field);
    }
}

Register_Class(AddressListOption)

AddressListOption::AddressListOption() : ::inet::HelloOption()
{
}

AddressListOption::AddressListOption(const AddressListOption& other) : ::inet::HelloOption(other)
{
    copy(other);
}

AddressListOption::~AddressListOption()
{
    delete [] this->secondaryAddresses;
}

AddressListOption& AddressListOption::operator=(const AddressListOption& other)
{
    if (this == &other) return *this;
    ::inet::HelloOption::operator=(other);
    copy(other);
    return *this;
}

void AddressListOption::copy(const AddressListOption& other)
{
    delete [] this->secondaryAddresses;
    this->secondaryAddresses = (other.secondaryAddresses_arraysize==0) ? nullptr : new EncodedUnicastAddress[other.secondaryAddresses_arraysize];
    secondaryAddresses_arraysize = other.secondaryAddresses_arraysize;
    for (size_t i = 0; i < secondaryAddresses_arraysize; i++) {
        this->secondaryAddresses[i] = other.secondaryAddresses[i];
    }
}

void AddressListOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::HelloOption::parsimPack(b);
    b->pack(secondaryAddresses_arraysize);
    doParsimArrayPacking(b,this->secondaryAddresses,secondaryAddresses_arraysize);
}

void AddressListOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::HelloOption::parsimUnpack(b);
    delete [] this->secondaryAddresses;
    b->unpack(secondaryAddresses_arraysize);
    if (secondaryAddresses_arraysize == 0) {
        this->secondaryAddresses = nullptr;
    } else {
        this->secondaryAddresses = new EncodedUnicastAddress[secondaryAddresses_arraysize];
        doParsimArrayUnpacking(b,this->secondaryAddresses,secondaryAddresses_arraysize);
    }
}

size_t AddressListOption::getSecondaryAddressesArraySize() const
{
    return secondaryAddresses_arraysize;
}

const EncodedUnicastAddress& AddressListOption::getSecondaryAddresses(size_t k) const
{
    if (k >= secondaryAddresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)secondaryAddresses_arraysize, (unsigned long)k);
    return this->secondaryAddresses[k];
}

void AddressListOption::setSecondaryAddressesArraySize(size_t newSize)
{
    EncodedUnicastAddress *secondaryAddresses2 = (newSize==0) ? nullptr : new EncodedUnicastAddress[newSize];
    size_t minSize = secondaryAddresses_arraysize < newSize ? secondaryAddresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        secondaryAddresses2[i] = this->secondaryAddresses[i];
    delete [] this->secondaryAddresses;
    this->secondaryAddresses = secondaryAddresses2;
    secondaryAddresses_arraysize = newSize;
}

void AddressListOption::setSecondaryAddresses(size_t k, const EncodedUnicastAddress& secondaryAddresses)
{
    if (k >= secondaryAddresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)secondaryAddresses_arraysize, (unsigned long)k);
    this->secondaryAddresses[k] = secondaryAddresses;
}

void AddressListOption::insertSecondaryAddresses(size_t k, const EncodedUnicastAddress& secondaryAddresses)
{
    if (k > secondaryAddresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)secondaryAddresses_arraysize, (unsigned long)k);
    size_t newSize = secondaryAddresses_arraysize + 1;
    EncodedUnicastAddress *secondaryAddresses2 = new EncodedUnicastAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        secondaryAddresses2[i] = this->secondaryAddresses[i];
    secondaryAddresses2[k] = secondaryAddresses;
    for (i = k + 1; i < newSize; i++)
        secondaryAddresses2[i] = this->secondaryAddresses[i-1];
    delete [] this->secondaryAddresses;
    this->secondaryAddresses = secondaryAddresses2;
    secondaryAddresses_arraysize = newSize;
}

void AddressListOption::appendSecondaryAddresses(const EncodedUnicastAddress& secondaryAddresses)
{
    insertSecondaryAddresses(secondaryAddresses_arraysize, secondaryAddresses);
}

void AddressListOption::eraseSecondaryAddresses(size_t k)
{
    if (k >= secondaryAddresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)secondaryAddresses_arraysize, (unsigned long)k);
    size_t newSize = secondaryAddresses_arraysize - 1;
    EncodedUnicastAddress *secondaryAddresses2 = (newSize == 0) ? nullptr : new EncodedUnicastAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        secondaryAddresses2[i] = this->secondaryAddresses[i];
    for (i = k; i < newSize; i++)
        secondaryAddresses2[i] = this->secondaryAddresses[i+1];
    delete [] this->secondaryAddresses;
    this->secondaryAddresses = secondaryAddresses2;
    secondaryAddresses_arraysize = newSize;
}

class AddressListOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_secondaryAddresses,
    };
  public:
    AddressListOptionDescriptor();
    virtual ~AddressListOptionDescriptor();

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

Register_ClassDescriptor(AddressListOptionDescriptor)

AddressListOptionDescriptor::AddressListOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::AddressListOption)), "inet::HelloOption")
{
    propertyNames = nullptr;
}

AddressListOptionDescriptor::~AddressListOptionDescriptor()
{
    delete[] propertyNames;
}

bool AddressListOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AddressListOption *>(obj)!=nullptr;
}

const char **AddressListOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AddressListOptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AddressListOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int AddressListOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_secondaryAddresses
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *AddressListOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "secondaryAddresses",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int AddressListOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "secondaryAddresses") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *AddressListOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedUnicastAddress",    // FIELD_secondaryAddresses
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **AddressListOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *AddressListOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int AddressListOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        case FIELD_secondaryAddresses: return pp->getSecondaryAddressesArraySize();
        default: return 0;
    }
}

void AddressListOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        case FIELD_secondaryAddresses: pp->setSecondaryAddressesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AddressListOption'", field);
    }
}

const char *AddressListOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AddressListOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        case FIELD_secondaryAddresses: return "";
        default: return "";
    }
}

void AddressListOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressListOption'", field);
    }
}

omnetpp::cValue AddressListOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        case FIELD_secondaryAddresses: return omnetpp::toAnyPtr(&pp->getSecondaryAddresses(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AddressListOption' as cValue -- field index out of range?", field);
    }
}

void AddressListOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressListOption'", field);
    }
}

const char *AddressListOptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_secondaryAddresses: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        default: return nullptr;
    };
}

omnetpp::any_ptr AddressListOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        case FIELD_secondaryAddresses: return omnetpp::toAnyPtr(&pp->getSecondaryAddresses(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AddressListOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AddressListOption *pp = omnetpp::fromAnyPtr<AddressListOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AddressListOption'", field);
    }
}

Register_Class(PimPacket)

PimPacket::PimPacket() : ::inet::FieldsChunk()
{
}

PimPacket::PimPacket(const PimPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

PimPacket::~PimPacket()
{
}

PimPacket& PimPacket::operator=(const PimPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void PimPacket::copy(const PimPacket& other)
{
    this->version = other.version;
    this->type = other.type;
    this->reserved = other.reserved;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void PimPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void PimPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

short PimPacket::getVersion() const
{
    return this->version;
}

void PimPacket::setVersion(short version)
{
    handleChange();
    this->version = version;
}

PimPacketType PimPacket::getType() const
{
    return this->type;
}

void PimPacket::setType(PimPacketType type)
{
    handleChange();
    this->type = type;
}

short PimPacket::getReserved() const
{
    return this->reserved;
}

void PimPacket::setReserved(short reserved)
{
    handleChange();
    this->reserved = reserved;
}

uint16_t PimPacket::getCrc() const
{
    return this->crc;
}

void PimPacket::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

CrcMode PimPacket::getCrcMode() const
{
    return this->crcMode;
}

void PimPacket::setCrcMode(CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class PimPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_type,
        FIELD_reserved,
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    PimPacketDescriptor();
    virtual ~PimPacketDescriptor();

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

Register_ClassDescriptor(PimPacketDescriptor)

PimPacketDescriptor::PimPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

PimPacketDescriptor::~PimPacketDescriptor()
{
    delete[] propertyNames;
}

bool PimPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimPacket *>(obj)!=nullptr;
}

const char **PimPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int PimPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *PimPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "type",
        "reserved",
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int PimPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *PimPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_version
        "inet::PimPacketType",    // FIELD_type
        "short",    // FIELD_reserved
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **PimPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PimPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::PimPacketType";
            return nullptr;
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int PimPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimPacket'", field);
    }
}

const char *PimPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: return long2string(pp->getVersion());
        case FIELD_type: return enum2string(pp->getType(), "inet::PimPacketType");
        case FIELD_reserved: return long2string(pp->getReserved());
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void PimPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2long(value)); break;
        case FIELD_reserved: pp->setReserved(string2long(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimPacket'", field);
    }
}

omnetpp::cValue PimPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: return pp->getVersion();
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_reserved: return pp->getReserved();
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimPacket' as cValue -- field index out of range?", field);
    }
}

void PimPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimPacket'", field);
    }
}

const char *PimPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PimPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimPacket *pp = omnetpp::fromAnyPtr<PimPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimPacket'", field);
    }
}

Register_Class(PimHello)

PimHello::PimHello() : ::inet::PimPacket()
{
    this->setType(Hello);

}

PimHello::PimHello(const PimHello& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimHello::~PimHello()
{
    for (size_t i = 0; i < options_arraysize; i++)
        delete this->options[i];
    delete [] this->options;
}

PimHello& PimHello::operator=(const PimHello& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimHello::copy(const PimHello& other)
{
    for (size_t i = 0; i < options_arraysize; i++)
        delete this->options[i];
    delete [] this->options;
    this->options = (other.options_arraysize==0) ? nullptr : new HelloOption *[other.options_arraysize];
    options_arraysize = other.options_arraysize;
    for (size_t i = 0; i < options_arraysize; i++) {
        this->options[i] = other.options[i];
        if (this->options[i] != nullptr) {
            this->options[i] = this->options[i]->dup();
        }
    }
}

void PimHello::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    b->pack(options_arraysize);
    doParsimArrayPacking(b,this->options,options_arraysize);
}

void PimHello::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    delete [] this->options;
    b->unpack(options_arraysize);
    if (options_arraysize == 0) {
        this->options = nullptr;
    } else {
        this->options = new HelloOption *[options_arraysize];
        doParsimArrayUnpacking(b,this->options,options_arraysize);
    }
}

size_t PimHello::getOptionsArraySize() const
{
    return options_arraysize;
}

const HelloOption * PimHello::getOptions(size_t k) const
{
    if (k >= options_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)options_arraysize, (unsigned long)k);
    return this->options[k];
}

void PimHello::setOptionsArraySize(size_t newSize)
{
    handleChange();
    HelloOption * *options2 = (newSize==0) ? nullptr : new HelloOption *[newSize];
    size_t minSize = options_arraysize < newSize ? options_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        options2[i] = this->options[i];
    for (size_t i = minSize; i < newSize; i++)
        options2[i] = nullptr;
    for (size_t i = newSize; i < options_arraysize; i++)
        delete options[i];
    delete [] this->options;
    this->options = options2;
    options_arraysize = newSize;
}

void PimHello::setOptions(size_t k, HelloOption * options)
{
    if (k >= options_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)options_arraysize, (unsigned long)k);
    handleChange();
    if (options == this->options[k]) return;
    if (this->options[k] != nullptr && this->options[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->options[k]); else delete this->options[k];
    this->options[k] = options;
    if (this->options[k] != nullptr && this->options[k]->isOwnedObject()) take((cOwnedObject*)this->options[k]);
}

HelloOption * PimHello::removeOptions(size_t k)
{
    if (k >= options_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)options_arraysize, (unsigned long)k);
    handleChange();
    HelloOption * retval = this->options[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->options[k] = nullptr;
    return retval;
}

void PimHello::insertOptions(size_t k, HelloOption * options)
{
    if (k > options_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)options_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = options_arraysize + 1;
    HelloOption * *options2 = new HelloOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        options2[i] = this->options[i];
    options2[k] = options;
    if (options2[k] != nullptr && options2[k]->isOwnedObject()) take((cOwnedObject*)options2[k]);
    for (i = k + 1; i < newSize; i++)
        options2[i] = this->options[i-1];
    delete [] this->options;
    this->options = options2;
    options_arraysize = newSize;
}

void PimHello::appendOptions(HelloOption * options)
{
    insertOptions(options_arraysize, options);
}

void PimHello::eraseOptions(size_t k)
{
    if (k >= options_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)options_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = options_arraysize - 1;
    HelloOption * *options2 = (newSize == 0) ? nullptr : new HelloOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        options2[i] = this->options[i];
    for (i = k; i < newSize; i++)
        options2[i] = this->options[i+1];
    if (this->options[k] != nullptr && this->options[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->options[k]); else delete this->options[k];
    delete [] this->options;
    this->options = options2;
    options_arraysize = newSize;
}

class PimHelloDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_options,
    };
  public:
    PimHelloDescriptor();
    virtual ~PimHelloDescriptor();

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

Register_ClassDescriptor(PimHelloDescriptor)

PimHelloDescriptor::PimHelloDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimHello)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimHelloDescriptor::~PimHelloDescriptor()
{
    delete[] propertyNames;
}

bool PimHelloDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimHello *>(obj)!=nullptr;
}

const char **PimHelloDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimHelloDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimHelloDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int PimHelloDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_options
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PimHelloDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "options",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PimHelloDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *PimHelloDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::HelloOption",    // FIELD_options
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PimHelloDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: {
            static const char *names[] = { "owned", "allowReplace",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PimHelloDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options:
            if (!strcmp(propertyName, "owned")) return "";
            if (!strcmp(propertyName, "allowReplace")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int PimHelloDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: return pp->getOptionsArraySize();
        default: return 0;
    }
}

void PimHelloDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: pp->setOptionsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimHello'", field);
    }
}

const char *PimHelloDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: { const HelloOption * value = pp->getOptions(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string PimHelloDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: { auto obj = pp->getOptions(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void PimHelloDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimHello'", field);
    }
}

omnetpp::cValue PimHelloDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(pp->getOptions(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimHello' as cValue -- field index out of range?", field);
    }
}

void PimHelloDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: pp->setOptions(i,omnetpp::fromAnyPtr<HelloOption>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimHello'", field);
    }
}

const char *PimHelloDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(HelloOption));
        default: return nullptr;
    };
}

omnetpp::any_ptr PimHelloDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(pp->getOptions(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimHelloDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimHello *pp = omnetpp::fromAnyPtr<PimHello>(object); (void)pp;
    switch (field) {
        case FIELD_options: pp->setOptions(i,omnetpp::fromAnyPtr<HelloOption>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimHello'", field);
    }
}

Register_Class(JoinPruneGroup)

JoinPruneGroup::JoinPruneGroup() : ::omnetpp::cObject()
{
}

JoinPruneGroup::JoinPruneGroup(const JoinPruneGroup& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

JoinPruneGroup::~JoinPruneGroup()
{
    delete [] this->joinedSourceAddress;
    delete [] this->prunedSourceAddress;
}

JoinPruneGroup& JoinPruneGroup::operator=(const JoinPruneGroup& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void JoinPruneGroup::copy(const JoinPruneGroup& other)
{
    this->groupAddress = other.groupAddress;
    delete [] this->joinedSourceAddress;
    this->joinedSourceAddress = (other.joinedSourceAddress_arraysize==0) ? nullptr : new EncodedSourceAddress[other.joinedSourceAddress_arraysize];
    joinedSourceAddress_arraysize = other.joinedSourceAddress_arraysize;
    for (size_t i = 0; i < joinedSourceAddress_arraysize; i++) {
        this->joinedSourceAddress[i] = other.joinedSourceAddress[i];
    }
    delete [] this->prunedSourceAddress;
    this->prunedSourceAddress = (other.prunedSourceAddress_arraysize==0) ? nullptr : new EncodedSourceAddress[other.prunedSourceAddress_arraysize];
    prunedSourceAddress_arraysize = other.prunedSourceAddress_arraysize;
    for (size_t i = 0; i < prunedSourceAddress_arraysize; i++) {
        this->prunedSourceAddress[i] = other.prunedSourceAddress[i];
    }
}

void JoinPruneGroup::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->groupAddress);
    b->pack(joinedSourceAddress_arraysize);
    doParsimArrayPacking(b,this->joinedSourceAddress,joinedSourceAddress_arraysize);
    b->pack(prunedSourceAddress_arraysize);
    doParsimArrayPacking(b,this->prunedSourceAddress,prunedSourceAddress_arraysize);
}

void JoinPruneGroup::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->groupAddress);
    delete [] this->joinedSourceAddress;
    b->unpack(joinedSourceAddress_arraysize);
    if (joinedSourceAddress_arraysize == 0) {
        this->joinedSourceAddress = nullptr;
    } else {
        this->joinedSourceAddress = new EncodedSourceAddress[joinedSourceAddress_arraysize];
        doParsimArrayUnpacking(b,this->joinedSourceAddress,joinedSourceAddress_arraysize);
    }
    delete [] this->prunedSourceAddress;
    b->unpack(prunedSourceAddress_arraysize);
    if (prunedSourceAddress_arraysize == 0) {
        this->prunedSourceAddress = nullptr;
    } else {
        this->prunedSourceAddress = new EncodedSourceAddress[prunedSourceAddress_arraysize];
        doParsimArrayUnpacking(b,this->prunedSourceAddress,prunedSourceAddress_arraysize);
    }
}

const EncodedGroupAddress& JoinPruneGroup::getGroupAddress() const
{
    return this->groupAddress;
}

void JoinPruneGroup::setGroupAddress(const EncodedGroupAddress& groupAddress)
{
    this->groupAddress = groupAddress;
}

size_t JoinPruneGroup::getJoinedSourceAddressArraySize() const
{
    return joinedSourceAddress_arraysize;
}

const EncodedSourceAddress& JoinPruneGroup::getJoinedSourceAddress(size_t k) const
{
    if (k >= joinedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinedSourceAddress_arraysize, (unsigned long)k);
    return this->joinedSourceAddress[k];
}

void JoinPruneGroup::setJoinedSourceAddressArraySize(size_t newSize)
{
    EncodedSourceAddress *joinedSourceAddress2 = (newSize==0) ? nullptr : new EncodedSourceAddress[newSize];
    size_t minSize = joinedSourceAddress_arraysize < newSize ? joinedSourceAddress_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        joinedSourceAddress2[i] = this->joinedSourceAddress[i];
    delete [] this->joinedSourceAddress;
    this->joinedSourceAddress = joinedSourceAddress2;
    joinedSourceAddress_arraysize = newSize;
}

void JoinPruneGroup::setJoinedSourceAddress(size_t k, const EncodedSourceAddress& joinedSourceAddress)
{
    if (k >= joinedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinedSourceAddress_arraysize, (unsigned long)k);
    this->joinedSourceAddress[k] = joinedSourceAddress;
}

void JoinPruneGroup::insertJoinedSourceAddress(size_t k, const EncodedSourceAddress& joinedSourceAddress)
{
    if (k > joinedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinedSourceAddress_arraysize, (unsigned long)k);
    size_t newSize = joinedSourceAddress_arraysize + 1;
    EncodedSourceAddress *joinedSourceAddress2 = new EncodedSourceAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        joinedSourceAddress2[i] = this->joinedSourceAddress[i];
    joinedSourceAddress2[k] = joinedSourceAddress;
    for (i = k + 1; i < newSize; i++)
        joinedSourceAddress2[i] = this->joinedSourceAddress[i-1];
    delete [] this->joinedSourceAddress;
    this->joinedSourceAddress = joinedSourceAddress2;
    joinedSourceAddress_arraysize = newSize;
}

void JoinPruneGroup::appendJoinedSourceAddress(const EncodedSourceAddress& joinedSourceAddress)
{
    insertJoinedSourceAddress(joinedSourceAddress_arraysize, joinedSourceAddress);
}

void JoinPruneGroup::eraseJoinedSourceAddress(size_t k)
{
    if (k >= joinedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinedSourceAddress_arraysize, (unsigned long)k);
    size_t newSize = joinedSourceAddress_arraysize - 1;
    EncodedSourceAddress *joinedSourceAddress2 = (newSize == 0) ? nullptr : new EncodedSourceAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        joinedSourceAddress2[i] = this->joinedSourceAddress[i];
    for (i = k; i < newSize; i++)
        joinedSourceAddress2[i] = this->joinedSourceAddress[i+1];
    delete [] this->joinedSourceAddress;
    this->joinedSourceAddress = joinedSourceAddress2;
    joinedSourceAddress_arraysize = newSize;
}

size_t JoinPruneGroup::getPrunedSourceAddressArraySize() const
{
    return prunedSourceAddress_arraysize;
}

const EncodedSourceAddress& JoinPruneGroup::getPrunedSourceAddress(size_t k) const
{
    if (k >= prunedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prunedSourceAddress_arraysize, (unsigned long)k);
    return this->prunedSourceAddress[k];
}

void JoinPruneGroup::setPrunedSourceAddressArraySize(size_t newSize)
{
    EncodedSourceAddress *prunedSourceAddress2 = (newSize==0) ? nullptr : new EncodedSourceAddress[newSize];
    size_t minSize = prunedSourceAddress_arraysize < newSize ? prunedSourceAddress_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        prunedSourceAddress2[i] = this->prunedSourceAddress[i];
    delete [] this->prunedSourceAddress;
    this->prunedSourceAddress = prunedSourceAddress2;
    prunedSourceAddress_arraysize = newSize;
}

void JoinPruneGroup::setPrunedSourceAddress(size_t k, const EncodedSourceAddress& prunedSourceAddress)
{
    if (k >= prunedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prunedSourceAddress_arraysize, (unsigned long)k);
    this->prunedSourceAddress[k] = prunedSourceAddress;
}

void JoinPruneGroup::insertPrunedSourceAddress(size_t k, const EncodedSourceAddress& prunedSourceAddress)
{
    if (k > prunedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prunedSourceAddress_arraysize, (unsigned long)k);
    size_t newSize = prunedSourceAddress_arraysize + 1;
    EncodedSourceAddress *prunedSourceAddress2 = new EncodedSourceAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prunedSourceAddress2[i] = this->prunedSourceAddress[i];
    prunedSourceAddress2[k] = prunedSourceAddress;
    for (i = k + 1; i < newSize; i++)
        prunedSourceAddress2[i] = this->prunedSourceAddress[i-1];
    delete [] this->prunedSourceAddress;
    this->prunedSourceAddress = prunedSourceAddress2;
    prunedSourceAddress_arraysize = newSize;
}

void JoinPruneGroup::appendPrunedSourceAddress(const EncodedSourceAddress& prunedSourceAddress)
{
    insertPrunedSourceAddress(prunedSourceAddress_arraysize, prunedSourceAddress);
}

void JoinPruneGroup::erasePrunedSourceAddress(size_t k)
{
    if (k >= prunedSourceAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prunedSourceAddress_arraysize, (unsigned long)k);
    size_t newSize = prunedSourceAddress_arraysize - 1;
    EncodedSourceAddress *prunedSourceAddress2 = (newSize == 0) ? nullptr : new EncodedSourceAddress[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prunedSourceAddress2[i] = this->prunedSourceAddress[i];
    for (i = k; i < newSize; i++)
        prunedSourceAddress2[i] = this->prunedSourceAddress[i+1];
    delete [] this->prunedSourceAddress;
    this->prunedSourceAddress = prunedSourceAddress2;
    prunedSourceAddress_arraysize = newSize;
}

class JoinPruneGroupDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_groupAddress,
        FIELD_joinedSourceAddress,
        FIELD_prunedSourceAddress,
    };
  public:
    JoinPruneGroupDescriptor();
    virtual ~JoinPruneGroupDescriptor();

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

Register_ClassDescriptor(JoinPruneGroupDescriptor)

JoinPruneGroupDescriptor::JoinPruneGroupDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::JoinPruneGroup)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

JoinPruneGroupDescriptor::~JoinPruneGroupDescriptor()
{
    delete[] propertyNames;
}

bool JoinPruneGroupDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<JoinPruneGroup *>(obj)!=nullptr;
}

const char **JoinPruneGroupDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *JoinPruneGroupDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int JoinPruneGroupDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int JoinPruneGroupDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_groupAddress
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_joinedSourceAddress
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_prunedSourceAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *JoinPruneGroupDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "groupAddress",
        "joinedSourceAddress",
        "prunedSourceAddress",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int JoinPruneGroupDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "joinedSourceAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "prunedSourceAddress") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *JoinPruneGroupDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedGroupAddress",    // FIELD_groupAddress
        "inet::EncodedSourceAddress",    // FIELD_joinedSourceAddress
        "inet::EncodedSourceAddress",    // FIELD_prunedSourceAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **JoinPruneGroupDescriptor::getFieldPropertyNames(int field) const
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

const char *JoinPruneGroupDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int JoinPruneGroupDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        case FIELD_joinedSourceAddress: return pp->getJoinedSourceAddressArraySize();
        case FIELD_prunedSourceAddress: return pp->getPrunedSourceAddressArraySize();
        default: return 0;
    }
}

void JoinPruneGroupDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        case FIELD_joinedSourceAddress: pp->setJoinedSourceAddressArraySize(size); break;
        case FIELD_prunedSourceAddress: pp->setPrunedSourceAddressArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'JoinPruneGroup'", field);
    }
}

const char *JoinPruneGroupDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JoinPruneGroupDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return "";
        case FIELD_joinedSourceAddress: return "";
        case FIELD_prunedSourceAddress: return "";
        default: return "";
    }
}

void JoinPruneGroupDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'JoinPruneGroup'", field);
    }
}

omnetpp::cValue JoinPruneGroupDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_joinedSourceAddress: return omnetpp::toAnyPtr(&pp->getJoinedSourceAddress(i)); break;
        case FIELD_prunedSourceAddress: return omnetpp::toAnyPtr(&pp->getPrunedSourceAddress(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'JoinPruneGroup' as cValue -- field index out of range?", field);
    }
}

void JoinPruneGroupDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'JoinPruneGroup'", field);
    }
}

const char *JoinPruneGroupDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_groupAddress: return omnetpp::opp_typename(typeid(EncodedGroupAddress));
        case FIELD_joinedSourceAddress: return omnetpp::opp_typename(typeid(EncodedSourceAddress));
        case FIELD_prunedSourceAddress: return omnetpp::opp_typename(typeid(EncodedSourceAddress));
        default: return nullptr;
    };
}

omnetpp::any_ptr JoinPruneGroupDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_joinedSourceAddress: return omnetpp::toAnyPtr(&pp->getJoinedSourceAddress(i)); break;
        case FIELD_prunedSourceAddress: return omnetpp::toAnyPtr(&pp->getPrunedSourceAddress(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void JoinPruneGroupDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    JoinPruneGroup *pp = omnetpp::fromAnyPtr<JoinPruneGroup>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'JoinPruneGroup'", field);
    }
}

Register_Class(PimJoinPrune)

PimJoinPrune::PimJoinPrune() : ::inet::PimPacket()
{
    this->setType(JoinPrune);

}

PimJoinPrune::PimJoinPrune(const PimJoinPrune& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimJoinPrune::~PimJoinPrune()
{
    delete [] this->joinPruneGroups;
}

PimJoinPrune& PimJoinPrune::operator=(const PimJoinPrune& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimJoinPrune::copy(const PimJoinPrune& other)
{
    this->upstreamNeighborAddress = other.upstreamNeighborAddress;
    this->reserved2 = other.reserved2;
    this->holdTime = other.holdTime;
    delete [] this->joinPruneGroups;
    this->joinPruneGroups = (other.joinPruneGroups_arraysize==0) ? nullptr : new JoinPruneGroup[other.joinPruneGroups_arraysize];
    joinPruneGroups_arraysize = other.joinPruneGroups_arraysize;
    for (size_t i = 0; i < joinPruneGroups_arraysize; i++) {
        this->joinPruneGroups[i] = other.joinPruneGroups[i];
    }
}

void PimJoinPrune::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    doParsimPacking(b,this->upstreamNeighborAddress);
    doParsimPacking(b,this->reserved2);
    doParsimPacking(b,this->holdTime);
    b->pack(joinPruneGroups_arraysize);
    doParsimArrayPacking(b,this->joinPruneGroups,joinPruneGroups_arraysize);
}

void PimJoinPrune::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->upstreamNeighborAddress);
    doParsimUnpacking(b,this->reserved2);
    doParsimUnpacking(b,this->holdTime);
    delete [] this->joinPruneGroups;
    b->unpack(joinPruneGroups_arraysize);
    if (joinPruneGroups_arraysize == 0) {
        this->joinPruneGroups = nullptr;
    } else {
        this->joinPruneGroups = new JoinPruneGroup[joinPruneGroups_arraysize];
        doParsimArrayUnpacking(b,this->joinPruneGroups,joinPruneGroups_arraysize);
    }
}

const EncodedUnicastAddress& PimJoinPrune::getUpstreamNeighborAddress() const
{
    return this->upstreamNeighborAddress;
}

void PimJoinPrune::setUpstreamNeighborAddress(const EncodedUnicastAddress& upstreamNeighborAddress)
{
    handleChange();
    this->upstreamNeighborAddress = upstreamNeighborAddress;
}

int PimJoinPrune::getReserved2() const
{
    return this->reserved2;
}

void PimJoinPrune::setReserved2(int reserved2)
{
    handleChange();
    this->reserved2 = reserved2;
}

int PimJoinPrune::getHoldTime() const
{
    return this->holdTime;
}

void PimJoinPrune::setHoldTime(int holdTime)
{
    handleChange();
    this->holdTime = holdTime;
}

size_t PimJoinPrune::getJoinPruneGroupsArraySize() const
{
    return joinPruneGroups_arraysize;
}

const JoinPruneGroup& PimJoinPrune::getJoinPruneGroups(size_t k) const
{
    if (k >= joinPruneGroups_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinPruneGroups_arraysize, (unsigned long)k);
    return this->joinPruneGroups[k];
}

void PimJoinPrune::setJoinPruneGroupsArraySize(size_t newSize)
{
    handleChange();
    JoinPruneGroup *joinPruneGroups2 = (newSize==0) ? nullptr : new JoinPruneGroup[newSize];
    size_t minSize = joinPruneGroups_arraysize < newSize ? joinPruneGroups_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        joinPruneGroups2[i] = this->joinPruneGroups[i];
    delete [] this->joinPruneGroups;
    this->joinPruneGroups = joinPruneGroups2;
    joinPruneGroups_arraysize = newSize;
}

void PimJoinPrune::setJoinPruneGroups(size_t k, const JoinPruneGroup& joinPruneGroups)
{
    if (k >= joinPruneGroups_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinPruneGroups_arraysize, (unsigned long)k);
    handleChange();
    this->joinPruneGroups[k] = joinPruneGroups;
}

void PimJoinPrune::insertJoinPruneGroups(size_t k, const JoinPruneGroup& joinPruneGroups)
{
    if (k > joinPruneGroups_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinPruneGroups_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = joinPruneGroups_arraysize + 1;
    JoinPruneGroup *joinPruneGroups2 = new JoinPruneGroup[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        joinPruneGroups2[i] = this->joinPruneGroups[i];
    joinPruneGroups2[k] = joinPruneGroups;
    for (i = k + 1; i < newSize; i++)
        joinPruneGroups2[i] = this->joinPruneGroups[i-1];
    delete [] this->joinPruneGroups;
    this->joinPruneGroups = joinPruneGroups2;
    joinPruneGroups_arraysize = newSize;
}

void PimJoinPrune::appendJoinPruneGroups(const JoinPruneGroup& joinPruneGroups)
{
    insertJoinPruneGroups(joinPruneGroups_arraysize, joinPruneGroups);
}

void PimJoinPrune::eraseJoinPruneGroups(size_t k)
{
    if (k >= joinPruneGroups_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)joinPruneGroups_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = joinPruneGroups_arraysize - 1;
    JoinPruneGroup *joinPruneGroups2 = (newSize == 0) ? nullptr : new JoinPruneGroup[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        joinPruneGroups2[i] = this->joinPruneGroups[i];
    for (i = k; i < newSize; i++)
        joinPruneGroups2[i] = this->joinPruneGroups[i+1];
    delete [] this->joinPruneGroups;
    this->joinPruneGroups = joinPruneGroups2;
    joinPruneGroups_arraysize = newSize;
}

class PimJoinPruneDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_upstreamNeighborAddress,
        FIELD_reserved2,
        FIELD_holdTime,
        FIELD_joinPruneGroups,
    };
  public:
    PimJoinPruneDescriptor();
    virtual ~PimJoinPruneDescriptor();

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

Register_ClassDescriptor(PimJoinPruneDescriptor)

PimJoinPruneDescriptor::PimJoinPruneDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimJoinPrune)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimJoinPruneDescriptor::~PimJoinPruneDescriptor()
{
    delete[] propertyNames;
}

bool PimJoinPruneDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimJoinPrune *>(obj)!=nullptr;
}

const char **PimJoinPruneDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimJoinPruneDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimJoinPruneDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int PimJoinPruneDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_upstreamNeighborAddress
        FD_ISEDITABLE,    // FIELD_reserved2
        FD_ISEDITABLE,    // FIELD_holdTime
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_joinPruneGroups
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *PimJoinPruneDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "upstreamNeighborAddress",
        "reserved2",
        "holdTime",
        "joinPruneGroups",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int PimJoinPruneDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "upstreamNeighborAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "holdTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "joinPruneGroups") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *PimJoinPruneDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedUnicastAddress",    // FIELD_upstreamNeighborAddress
        "int",    // FIELD_reserved2
        "int",    // FIELD_holdTime
        "inet::JoinPruneGroup",    // FIELD_joinPruneGroups
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **PimJoinPruneDescriptor::getFieldPropertyNames(int field) const
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

const char *PimJoinPruneDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimJoinPruneDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_joinPruneGroups: return pp->getJoinPruneGroupsArraySize();
        default: return 0;
    }
}

void PimJoinPruneDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_joinPruneGroups: pp->setJoinPruneGroupsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimJoinPrune'", field);
    }
}

const char *PimJoinPruneDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimJoinPruneDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_upstreamNeighborAddress: return "";
        case FIELD_reserved2: return long2string(pp->getReserved2());
        case FIELD_holdTime: return long2string(pp->getHoldTime());
        case FIELD_joinPruneGroups: return pp->getJoinPruneGroups(i).str();
        default: return "";
    }
}

void PimJoinPruneDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_reserved2: pp->setReserved2(string2long(value)); break;
        case FIELD_holdTime: pp->setHoldTime(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimJoinPrune'", field);
    }
}

omnetpp::cValue PimJoinPruneDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_upstreamNeighborAddress: return omnetpp::toAnyPtr(&pp->getUpstreamNeighborAddress()); break;
        case FIELD_reserved2: return pp->getReserved2();
        case FIELD_holdTime: return pp->getHoldTime();
        case FIELD_joinPruneGroups: return omnetpp::toAnyPtr(&pp->getJoinPruneGroups(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimJoinPrune' as cValue -- field index out of range?", field);
    }
}

void PimJoinPruneDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_reserved2: pp->setReserved2(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_holdTime: pp->setHoldTime(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimJoinPrune'", field);
    }
}

const char *PimJoinPruneDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_upstreamNeighborAddress: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        case FIELD_joinPruneGroups: return omnetpp::opp_typename(typeid(JoinPruneGroup));
        default: return nullptr;
    };
}

omnetpp::any_ptr PimJoinPruneDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        case FIELD_upstreamNeighborAddress: return omnetpp::toAnyPtr(&pp->getUpstreamNeighborAddress()); break;
        case FIELD_joinPruneGroups: return omnetpp::toAnyPtr(&pp->getJoinPruneGroups(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimJoinPruneDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimJoinPrune *pp = omnetpp::fromAnyPtr<PimJoinPrune>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimJoinPrune'", field);
    }
}

Register_Class(PimAssert)

PimAssert::PimAssert() : ::inet::PimPacket()
{
    this->setType(Assert);

}

PimAssert::PimAssert(const PimAssert& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimAssert::~PimAssert()
{
}

PimAssert& PimAssert::operator=(const PimAssert& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimAssert::copy(const PimAssert& other)
{
    this->groupAddress = other.groupAddress;
    this->sourceAddress = other.sourceAddress;
    this->R = other.R;
    this->metric = other.metric;
    this->metricPreference = other.metricPreference;
}

void PimAssert::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    doParsimPacking(b,this->groupAddress);
    doParsimPacking(b,this->sourceAddress);
    doParsimPacking(b,this->R);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->metricPreference);
}

void PimAssert::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->groupAddress);
    doParsimUnpacking(b,this->sourceAddress);
    doParsimUnpacking(b,this->R);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->metricPreference);
}

const EncodedGroupAddress& PimAssert::getGroupAddress() const
{
    return this->groupAddress;
}

void PimAssert::setGroupAddress(const EncodedGroupAddress& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

const EncodedUnicastAddress& PimAssert::getSourceAddress() const
{
    return this->sourceAddress;
}

void PimAssert::setSourceAddress(const EncodedUnicastAddress& sourceAddress)
{
    handleChange();
    this->sourceAddress = sourceAddress;
}

bool PimAssert::getR() const
{
    return this->R;
}

void PimAssert::setR(bool R)
{
    handleChange();
    this->R = R;
}

int PimAssert::getMetric() const
{
    return this->metric;
}

void PimAssert::setMetric(int metric)
{
    handleChange();
    this->metric = metric;
}

int PimAssert::getMetricPreference() const
{
    return this->metricPreference;
}

void PimAssert::setMetricPreference(int metricPreference)
{
    handleChange();
    this->metricPreference = metricPreference;
}

class PimAssertDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_groupAddress,
        FIELD_sourceAddress,
        FIELD_R,
        FIELD_metric,
        FIELD_metricPreference,
    };
  public:
    PimAssertDescriptor();
    virtual ~PimAssertDescriptor();

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

Register_ClassDescriptor(PimAssertDescriptor)

PimAssertDescriptor::PimAssertDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimAssert)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimAssertDescriptor::~PimAssertDescriptor()
{
    delete[] propertyNames;
}

bool PimAssertDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimAssert *>(obj)!=nullptr;
}

const char **PimAssertDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimAssertDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimAssertDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int PimAssertDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_groupAddress
        FD_ISCOMPOUND,    // FIELD_sourceAddress
        FD_ISEDITABLE,    // FIELD_R
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_metricPreference
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *PimAssertDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "groupAddress",
        "sourceAddress",
        "R",
        "metric",
        "metricPreference",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int PimAssertDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "R") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "metricPreference") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *PimAssertDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedGroupAddress",    // FIELD_groupAddress
        "inet::EncodedUnicastAddress",    // FIELD_sourceAddress
        "bool",    // FIELD_R
        "int",    // FIELD_metric
        "int",    // FIELD_metricPreference
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **PimAssertDescriptor::getFieldPropertyNames(int field) const
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

const char *PimAssertDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimAssertDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimAssertDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimAssert'", field);
    }
}

const char *PimAssertDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimAssertDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return "";
        case FIELD_sourceAddress: return "";
        case FIELD_R: return bool2string(pp->getR());
        case FIELD_metric: return long2string(pp->getMetric());
        case FIELD_metricPreference: return long2string(pp->getMetricPreference());
        default: return "";
    }
}

void PimAssertDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        case FIELD_R: pp->setR(string2bool(value)); break;
        case FIELD_metric: pp->setMetric(string2long(value)); break;
        case FIELD_metricPreference: pp->setMetricPreference(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimAssert'", field);
    }
}

omnetpp::cValue PimAssertDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        case FIELD_R: return pp->getR();
        case FIELD_metric: return pp->getMetric();
        case FIELD_metricPreference: return pp->getMetricPreference();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimAssert' as cValue -- field index out of range?", field);
    }
}

void PimAssertDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        case FIELD_R: pp->setR(value.boolValue()); break;
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_metricPreference: pp->setMetricPreference(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimAssert'", field);
    }
}

const char *PimAssertDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_groupAddress: return omnetpp::opp_typename(typeid(EncodedGroupAddress));
        case FIELD_sourceAddress: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        default: return nullptr;
    };
}

omnetpp::any_ptr PimAssertDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimAssertDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimAssert *pp = omnetpp::fromAnyPtr<PimAssert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimAssert'", field);
    }
}

Register_Class(PimGraft)

PimGraft::PimGraft() : ::inet::PimJoinPrune()
{
    this->setType(Graft);
    this->setHoldTime(0);
}

PimGraft::PimGraft(const PimGraft& other) : ::inet::PimJoinPrune(other)
{
    copy(other);
}

PimGraft::~PimGraft()
{
}

PimGraft& PimGraft::operator=(const PimGraft& other)
{
    if (this == &other) return *this;
    ::inet::PimJoinPrune::operator=(other);
    copy(other);
    return *this;
}

void PimGraft::copy(const PimGraft& other)
{
}

void PimGraft::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimJoinPrune::parsimPack(b);
}

void PimGraft::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimJoinPrune::parsimUnpack(b);
}

class PimGraftDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    PimGraftDescriptor();
    virtual ~PimGraftDescriptor();

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

Register_ClassDescriptor(PimGraftDescriptor)

PimGraftDescriptor::PimGraftDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimGraft)), "inet::PimJoinPrune")
{
    propertyNames = nullptr;
}

PimGraftDescriptor::~PimGraftDescriptor()
{
    delete[] propertyNames;
}

bool PimGraftDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimGraft *>(obj)!=nullptr;
}

const char **PimGraftDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimGraftDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimGraftDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int PimGraftDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *PimGraftDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int PimGraftDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *PimGraftDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **PimGraftDescriptor::getFieldPropertyNames(int field) const
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

const char *PimGraftDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimGraftDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimGraftDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimGraft'", field);
    }
}

const char *PimGraftDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimGraftDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void PimGraftDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimGraft'", field);
    }
}

omnetpp::cValue PimGraftDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimGraft' as cValue -- field index out of range?", field);
    }
}

void PimGraftDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimGraft'", field);
    }
}

const char *PimGraftDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr PimGraftDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimGraftDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimGraft *pp = omnetpp::fromAnyPtr<PimGraft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimGraft'", field);
    }
}

Register_Class(PimStateRefresh)

PimStateRefresh::PimStateRefresh() : ::inet::PimPacket()
{
    this->setType(StateRefresh);

}

PimStateRefresh::PimStateRefresh(const PimStateRefresh& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimStateRefresh::~PimStateRefresh()
{
}

PimStateRefresh& PimStateRefresh::operator=(const PimStateRefresh& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimStateRefresh::copy(const PimStateRefresh& other)
{
    this->groupAddress = other.groupAddress;
    this->sourceAddress = other.sourceAddress;
    this->originatorAddress = other.originatorAddress;
    this->R = other.R;
    this->metricPreference = other.metricPreference;
    this->metric = other.metric;
    this->maskLen = other.maskLen;
    this->ttl = other.ttl;
    this->P = other.P;
    this->N = other.N;
    this->O = other.O;
    this->reserved2 = other.reserved2;
    this->interval = other.interval;
}

void PimStateRefresh::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    doParsimPacking(b,this->groupAddress);
    doParsimPacking(b,this->sourceAddress);
    doParsimPacking(b,this->originatorAddress);
    doParsimPacking(b,this->R);
    doParsimPacking(b,this->metricPreference);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->maskLen);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->P);
    doParsimPacking(b,this->N);
    doParsimPacking(b,this->O);
    doParsimPacking(b,this->reserved2);
    doParsimPacking(b,this->interval);
}

void PimStateRefresh::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->groupAddress);
    doParsimUnpacking(b,this->sourceAddress);
    doParsimUnpacking(b,this->originatorAddress);
    doParsimUnpacking(b,this->R);
    doParsimUnpacking(b,this->metricPreference);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->maskLen);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->P);
    doParsimUnpacking(b,this->N);
    doParsimUnpacking(b,this->O);
    doParsimUnpacking(b,this->reserved2);
    doParsimUnpacking(b,this->interval);
}

const EncodedGroupAddress& PimStateRefresh::getGroupAddress() const
{
    return this->groupAddress;
}

void PimStateRefresh::setGroupAddress(const EncodedGroupAddress& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

const EncodedUnicastAddress& PimStateRefresh::getSourceAddress() const
{
    return this->sourceAddress;
}

void PimStateRefresh::setSourceAddress(const EncodedUnicastAddress& sourceAddress)
{
    handleChange();
    this->sourceAddress = sourceAddress;
}

const EncodedUnicastAddress& PimStateRefresh::getOriginatorAddress() const
{
    return this->originatorAddress;
}

void PimStateRefresh::setOriginatorAddress(const EncodedUnicastAddress& originatorAddress)
{
    handleChange();
    this->originatorAddress = originatorAddress;
}

bool PimStateRefresh::getR() const
{
    return this->R;
}

void PimStateRefresh::setR(bool R)
{
    handleChange();
    this->R = R;
}

int PimStateRefresh::getMetricPreference() const
{
    return this->metricPreference;
}

void PimStateRefresh::setMetricPreference(int metricPreference)
{
    handleChange();
    this->metricPreference = metricPreference;
}

int PimStateRefresh::getMetric() const
{
    return this->metric;
}

void PimStateRefresh::setMetric(int metric)
{
    handleChange();
    this->metric = metric;
}

short PimStateRefresh::getMaskLen() const
{
    return this->maskLen;
}

void PimStateRefresh::setMaskLen(short maskLen)
{
    handleChange();
    this->maskLen = maskLen;
}

short PimStateRefresh::getTtl() const
{
    return this->ttl;
}

void PimStateRefresh::setTtl(short ttl)
{
    handleChange();
    this->ttl = ttl;
}

bool PimStateRefresh::getP() const
{
    return this->P;
}

void PimStateRefresh::setP(bool P)
{
    handleChange();
    this->P = P;
}

bool PimStateRefresh::getN() const
{
    return this->N;
}

void PimStateRefresh::setN(bool N)
{
    handleChange();
    this->N = N;
}

bool PimStateRefresh::getO() const
{
    return this->O;
}

void PimStateRefresh::setO(bool O)
{
    handleChange();
    this->O = O;
}

short PimStateRefresh::getReserved2() const
{
    return this->reserved2;
}

void PimStateRefresh::setReserved2(short reserved2)
{
    handleChange();
    this->reserved2 = reserved2;
}

short PimStateRefresh::getInterval() const
{
    return this->interval;
}

void PimStateRefresh::setInterval(short interval)
{
    handleChange();
    this->interval = interval;
}

class PimStateRefreshDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_groupAddress,
        FIELD_sourceAddress,
        FIELD_originatorAddress,
        FIELD_R,
        FIELD_metricPreference,
        FIELD_metric,
        FIELD_maskLen,
        FIELD_ttl,
        FIELD_P,
        FIELD_N,
        FIELD_O,
        FIELD_reserved2,
        FIELD_interval,
    };
  public:
    PimStateRefreshDescriptor();
    virtual ~PimStateRefreshDescriptor();

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

Register_ClassDescriptor(PimStateRefreshDescriptor)

PimStateRefreshDescriptor::PimStateRefreshDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimStateRefresh)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimStateRefreshDescriptor::~PimStateRefreshDescriptor()
{
    delete[] propertyNames;
}

bool PimStateRefreshDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimStateRefresh *>(obj)!=nullptr;
}

const char **PimStateRefreshDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimStateRefreshDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimStateRefreshDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 13+base->getFieldCount() : 13;
}

unsigned int PimStateRefreshDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_groupAddress
        FD_ISCOMPOUND,    // FIELD_sourceAddress
        FD_ISCOMPOUND,    // FIELD_originatorAddress
        FD_ISEDITABLE,    // FIELD_R
        FD_ISEDITABLE,    // FIELD_metricPreference
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_maskLen
        FD_ISEDITABLE,    // FIELD_ttl
        FD_ISEDITABLE,    // FIELD_P
        FD_ISEDITABLE,    // FIELD_N
        FD_ISEDITABLE,    // FIELD_O
        FD_ISEDITABLE,    // FIELD_reserved2
        FD_ISEDITABLE,    // FIELD_interval
    };
    return (field >= 0 && field < 13) ? fieldTypeFlags[field] : 0;
}

const char *PimStateRefreshDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "groupAddress",
        "sourceAddress",
        "originatorAddress",
        "R",
        "metricPreference",
        "metric",
        "maskLen",
        "ttl",
        "P",
        "N",
        "O",
        "reserved2",
        "interval",
    };
    return (field >= 0 && field < 13) ? fieldNames[field] : nullptr;
}

int PimStateRefreshDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "originatorAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "R") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "metricPreference") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "maskLen") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "P") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "N") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "O") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "interval") == 0) return baseIndex + 12;
    return base ? base->findField(fieldName) : -1;
}

const char *PimStateRefreshDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedGroupAddress",    // FIELD_groupAddress
        "inet::EncodedUnicastAddress",    // FIELD_sourceAddress
        "inet::EncodedUnicastAddress",    // FIELD_originatorAddress
        "bool",    // FIELD_R
        "int",    // FIELD_metricPreference
        "int",    // FIELD_metric
        "short",    // FIELD_maskLen
        "short",    // FIELD_ttl
        "bool",    // FIELD_P
        "bool",    // FIELD_N
        "bool",    // FIELD_O
        "short",    // FIELD_reserved2
        "short",    // FIELD_interval
    };
    return (field >= 0 && field < 13) ? fieldTypeStrings[field] : nullptr;
}

const char **PimStateRefreshDescriptor::getFieldPropertyNames(int field) const
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

const char *PimStateRefreshDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimStateRefreshDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimStateRefreshDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimStateRefresh'", field);
    }
}

const char *PimStateRefreshDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimStateRefreshDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return "";
        case FIELD_sourceAddress: return "";
        case FIELD_originatorAddress: return "";
        case FIELD_R: return bool2string(pp->getR());
        case FIELD_metricPreference: return long2string(pp->getMetricPreference());
        case FIELD_metric: return long2string(pp->getMetric());
        case FIELD_maskLen: return long2string(pp->getMaskLen());
        case FIELD_ttl: return long2string(pp->getTtl());
        case FIELD_P: return bool2string(pp->getP());
        case FIELD_N: return bool2string(pp->getN());
        case FIELD_O: return bool2string(pp->getO());
        case FIELD_reserved2: return long2string(pp->getReserved2());
        case FIELD_interval: return long2string(pp->getInterval());
        default: return "";
    }
}

void PimStateRefreshDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        case FIELD_R: pp->setR(string2bool(value)); break;
        case FIELD_metricPreference: pp->setMetricPreference(string2long(value)); break;
        case FIELD_metric: pp->setMetric(string2long(value)); break;
        case FIELD_maskLen: pp->setMaskLen(string2long(value)); break;
        case FIELD_ttl: pp->setTtl(string2long(value)); break;
        case FIELD_P: pp->setP(string2bool(value)); break;
        case FIELD_N: pp->setN(string2bool(value)); break;
        case FIELD_O: pp->setO(string2bool(value)); break;
        case FIELD_reserved2: pp->setReserved2(string2long(value)); break;
        case FIELD_interval: pp->setInterval(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimStateRefresh'", field);
    }
}

omnetpp::cValue PimStateRefreshDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        case FIELD_originatorAddress: return omnetpp::toAnyPtr(&pp->getOriginatorAddress()); break;
        case FIELD_R: return pp->getR();
        case FIELD_metricPreference: return pp->getMetricPreference();
        case FIELD_metric: return pp->getMetric();
        case FIELD_maskLen: return pp->getMaskLen();
        case FIELD_ttl: return pp->getTtl();
        case FIELD_P: return pp->getP();
        case FIELD_N: return pp->getN();
        case FIELD_O: return pp->getO();
        case FIELD_reserved2: return pp->getReserved2();
        case FIELD_interval: return pp->getInterval();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimStateRefresh' as cValue -- field index out of range?", field);
    }
}

void PimStateRefreshDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        case FIELD_R: pp->setR(value.boolValue()); break;
        case FIELD_metricPreference: pp->setMetricPreference(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_maskLen: pp->setMaskLen(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_ttl: pp->setTtl(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_P: pp->setP(value.boolValue()); break;
        case FIELD_N: pp->setN(value.boolValue()); break;
        case FIELD_O: pp->setO(value.boolValue()); break;
        case FIELD_reserved2: pp->setReserved2(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_interval: pp->setInterval(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimStateRefresh'", field);
    }
}

const char *PimStateRefreshDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_groupAddress: return omnetpp::opp_typename(typeid(EncodedGroupAddress));
        case FIELD_sourceAddress: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        case FIELD_originatorAddress: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        default: return nullptr;
    };
}

omnetpp::any_ptr PimStateRefreshDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        case FIELD_originatorAddress: return omnetpp::toAnyPtr(&pp->getOriginatorAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimStateRefreshDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimStateRefresh *pp = omnetpp::fromAnyPtr<PimStateRefresh>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimStateRefresh'", field);
    }
}

Register_Class(PimRegister)

PimRegister::PimRegister() : ::inet::PimPacket()
{
    this->setType(Register);

}

PimRegister::PimRegister(const PimRegister& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimRegister::~PimRegister()
{
}

PimRegister& PimRegister::operator=(const PimRegister& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimRegister::copy(const PimRegister& other)
{
    this->B = other.B;
    this->N = other.N;
    this->reserved2 = other.reserved2;
}

void PimRegister::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    doParsimPacking(b,this->B);
    doParsimPacking(b,this->N);
    doParsimPacking(b,this->reserved2);
}

void PimRegister::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->B);
    doParsimUnpacking(b,this->N);
    doParsimUnpacking(b,this->reserved2);
}

bool PimRegister::getB() const
{
    return this->B;
}

void PimRegister::setB(bool B)
{
    handleChange();
    this->B = B;
}

bool PimRegister::getN() const
{
    return this->N;
}

void PimRegister::setN(bool N)
{
    handleChange();
    this->N = N;
}

uint32_t PimRegister::getReserved2() const
{
    return this->reserved2;
}

void PimRegister::setReserved2(uint32_t reserved2)
{
    handleChange();
    this->reserved2 = reserved2;
}

class PimRegisterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_B,
        FIELD_N,
        FIELD_reserved2,
    };
  public:
    PimRegisterDescriptor();
    virtual ~PimRegisterDescriptor();

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

Register_ClassDescriptor(PimRegisterDescriptor)

PimRegisterDescriptor::PimRegisterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimRegister)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimRegisterDescriptor::~PimRegisterDescriptor()
{
    delete[] propertyNames;
}

bool PimRegisterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimRegister *>(obj)!=nullptr;
}

const char **PimRegisterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimRegisterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimRegisterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int PimRegisterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_B
        FD_ISEDITABLE,    // FIELD_N
        FD_ISEDITABLE,    // FIELD_reserved2
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *PimRegisterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "B",
        "N",
        "reserved2",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int PimRegisterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "B") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "N") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *PimRegisterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_B
        "bool",    // FIELD_N
        "uint32_t",    // FIELD_reserved2
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **PimRegisterDescriptor::getFieldPropertyNames(int field) const
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

const char *PimRegisterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimRegisterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimRegisterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimRegister'", field);
    }
}

const char *PimRegisterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimRegisterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        case FIELD_B: return bool2string(pp->getB());
        case FIELD_N: return bool2string(pp->getN());
        case FIELD_reserved2: return ulong2string(pp->getReserved2());
        default: return "";
    }
}

void PimRegisterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        case FIELD_B: pp->setB(string2bool(value)); break;
        case FIELD_N: pp->setN(string2bool(value)); break;
        case FIELD_reserved2: pp->setReserved2(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegister'", field);
    }
}

omnetpp::cValue PimRegisterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        case FIELD_B: return pp->getB();
        case FIELD_N: return pp->getN();
        case FIELD_reserved2: return (omnetpp::intval_t)(pp->getReserved2());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimRegister' as cValue -- field index out of range?", field);
    }
}

void PimRegisterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        case FIELD_B: pp->setB(value.boolValue()); break;
        case FIELD_N: pp->setN(value.boolValue()); break;
        case FIELD_reserved2: pp->setReserved2(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegister'", field);
    }
}

const char *PimRegisterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PimRegisterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimRegisterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegister *pp = omnetpp::fromAnyPtr<PimRegister>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegister'", field);
    }
}

Register_Class(PimRegisterStop)

PimRegisterStop::PimRegisterStop() : ::inet::PimPacket()
{
    this->setType(RegisterStop);

}

PimRegisterStop::PimRegisterStop(const PimRegisterStop& other) : ::inet::PimPacket(other)
{
    copy(other);
}

PimRegisterStop::~PimRegisterStop()
{
}

PimRegisterStop& PimRegisterStop::operator=(const PimRegisterStop& other)
{
    if (this == &other) return *this;
    ::inet::PimPacket::operator=(other);
    copy(other);
    return *this;
}

void PimRegisterStop::copy(const PimRegisterStop& other)
{
    this->groupAddress = other.groupAddress;
    this->sourceAddress = other.sourceAddress;
}

void PimRegisterStop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::PimPacket::parsimPack(b);
    doParsimPacking(b,this->groupAddress);
    doParsimPacking(b,this->sourceAddress);
}

void PimRegisterStop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::PimPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->groupAddress);
    doParsimUnpacking(b,this->sourceAddress);
}

const EncodedGroupAddress& PimRegisterStop::getGroupAddress() const
{
    return this->groupAddress;
}

void PimRegisterStop::setGroupAddress(const EncodedGroupAddress& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

const EncodedUnicastAddress& PimRegisterStop::getSourceAddress() const
{
    return this->sourceAddress;
}

void PimRegisterStop::setSourceAddress(const EncodedUnicastAddress& sourceAddress)
{
    handleChange();
    this->sourceAddress = sourceAddress;
}

class PimRegisterStopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_groupAddress,
        FIELD_sourceAddress,
    };
  public:
    PimRegisterStopDescriptor();
    virtual ~PimRegisterStopDescriptor();

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

Register_ClassDescriptor(PimRegisterStopDescriptor)

PimRegisterStopDescriptor::PimRegisterStopDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PimRegisterStop)), "inet::PimPacket")
{
    propertyNames = nullptr;
}

PimRegisterStopDescriptor::~PimRegisterStopDescriptor()
{
    delete[] propertyNames;
}

bool PimRegisterStopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PimRegisterStop *>(obj)!=nullptr;
}

const char **PimRegisterStopDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PimRegisterStopDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PimRegisterStopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int PimRegisterStopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_groupAddress
        FD_ISCOMPOUND,    // FIELD_sourceAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *PimRegisterStopDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "groupAddress",
        "sourceAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int PimRegisterStopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *PimRegisterStopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::EncodedGroupAddress",    // FIELD_groupAddress
        "inet::EncodedUnicastAddress",    // FIELD_sourceAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **PimRegisterStopDescriptor::getFieldPropertyNames(int field) const
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

const char *PimRegisterStopDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PimRegisterStopDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PimRegisterStopDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PimRegisterStop'", field);
    }
}

const char *PimRegisterStopDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PimRegisterStopDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return "";
        case FIELD_sourceAddress: return "";
        default: return "";
    }
}

void PimRegisterStopDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegisterStop'", field);
    }
}

omnetpp::cValue PimRegisterStopDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PimRegisterStop' as cValue -- field index out of range?", field);
    }
}

void PimRegisterStopDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegisterStop'", field);
    }
}

const char *PimRegisterStopDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_groupAddress: return omnetpp::opp_typename(typeid(EncodedGroupAddress));
        case FIELD_sourceAddress: return omnetpp::opp_typename(typeid(EncodedUnicastAddress));
        default: return nullptr;
    };
}

omnetpp::any_ptr PimRegisterStopDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceAddress: return omnetpp::toAnyPtr(&pp->getSourceAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PimRegisterStopDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PimRegisterStop *pp = omnetpp::fromAnyPtr<PimRegisterStop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PimRegisterStop'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

