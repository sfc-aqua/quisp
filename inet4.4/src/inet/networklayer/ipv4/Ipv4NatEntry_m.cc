//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/Ipv4NatEntry.msg.
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
#include "Ipv4NatEntry_m.h"

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

Register_Class(Ipv4NatEntry)

Ipv4NatEntry::Ipv4NatEntry() : ::omnetpp::cObject()
{
}

Ipv4NatEntry::Ipv4NatEntry(const Ipv4NatEntry& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv4NatEntry::~Ipv4NatEntry()
{
}

Ipv4NatEntry& Ipv4NatEntry::operator=(const Ipv4NatEntry& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv4NatEntry::copy(const Ipv4NatEntry& other)
{
    this->destAddress = other.destAddress;
    this->destPort = other.destPort;
    this->srcAddress = other.srcAddress;
    this->srcPort = other.srcPort;
}

void Ipv4NatEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->destPort);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->srcPort);
}

void Ipv4NatEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->destPort);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->srcPort);
}

const Ipv4Address& Ipv4NatEntry::getDestAddress() const
{
    return this->destAddress;
}

void Ipv4NatEntry::setDestAddress(const Ipv4Address& destAddress)
{
    this->destAddress = destAddress;
}

int Ipv4NatEntry::getDestPort() const
{
    return this->destPort;
}

void Ipv4NatEntry::setDestPort(int destPort)
{
    this->destPort = destPort;
}

const Ipv4Address& Ipv4NatEntry::getSrcAddress() const
{
    return this->srcAddress;
}

void Ipv4NatEntry::setSrcAddress(const Ipv4Address& srcAddress)
{
    this->srcAddress = srcAddress;
}

int Ipv4NatEntry::getSrcPort() const
{
    return this->srcPort;
}

void Ipv4NatEntry::setSrcPort(int srcPort)
{
    this->srcPort = srcPort;
}

class Ipv4NatEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destAddress,
        FIELD_destPort,
        FIELD_srcAddress,
        FIELD_srcPort,
    };
  public:
    Ipv4NatEntryDescriptor();
    virtual ~Ipv4NatEntryDescriptor();

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

Register_ClassDescriptor(Ipv4NatEntryDescriptor)

Ipv4NatEntryDescriptor::Ipv4NatEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4NatEntry)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv4NatEntryDescriptor::~Ipv4NatEntryDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4NatEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4NatEntry *>(obj)!=nullptr;
}

const char **Ipv4NatEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4NatEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4NatEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ipv4NatEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destAddress
        FD_ISEDITABLE,    // FIELD_destPort
        0,    // FIELD_srcAddress
        FD_ISEDITABLE,    // FIELD_srcPort
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4NatEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddress",
        "destPort",
        "srcAddress",
        "srcPort",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ipv4NatEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destPort") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4NatEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_destAddress
        "int",    // FIELD_destPort
        "inet::Ipv4Address",    // FIELD_srcAddress
        "int",    // FIELD_srcPort
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4NatEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4NatEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4NatEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4NatEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4NatEntry'", field);
    }
}

const char *Ipv4NatEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4NatEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return pp->getDestAddress().str();
        case FIELD_destPort: return long2string(pp->getDestPort());
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_srcPort: return long2string(pp->getSrcPort());
        default: return "";
    }
}

void Ipv4NatEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destPort: pp->setDestPort(string2long(value)); break;
        case FIELD_srcPort: pp->setSrcPort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4NatEntry'", field);
    }
}

omnetpp::cValue Ipv4NatEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_destPort: return pp->getDestPort();
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_srcPort: return pp->getSrcPort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4NatEntry' as cValue -- field index out of range?", field);
    }
}

void Ipv4NatEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destPort: pp->setDestPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4NatEntry'", field);
    }
}

const char *Ipv4NatEntryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4NatEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4NatEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4NatEntry *pp = omnetpp::fromAnyPtr<Ipv4NatEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4NatEntry'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

