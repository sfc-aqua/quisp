//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/ospfv3/Ospfv3Packet.msg.
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
#include "Ospfv3Packet_m.h"

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
namespace ospfv3 {

Register_Class(Ospfv3Packet)

Ospfv3Packet::Ospfv3Packet() : ::inet::ospf::OspfPacketBase()
{
    this->setChunkLength(B(16));
    this->setVersion(3);

}

Ospfv3Packet::Ospfv3Packet(const Ospfv3Packet& other) : ::inet::ospf::OspfPacketBase(other)
{
    copy(other);
}

Ospfv3Packet::~Ospfv3Packet()
{
}

Ospfv3Packet& Ospfv3Packet::operator=(const Ospfv3Packet& other)
{
    if (this == &other) return *this;
    ::inet::ospf::OspfPacketBase::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3Packet::copy(const Ospfv3Packet& other)
{
    this->instanceID = other.instanceID;
    this->reserved = other.reserved;
}

void Ospfv3Packet::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospf::OspfPacketBase::parsimPack(b);
    doParsimPacking(b,this->instanceID);
    doParsimPacking(b,this->reserved);
}

void Ospfv3Packet::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospf::OspfPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->instanceID);
    doParsimUnpacking(b,this->reserved);
}

int8_t Ospfv3Packet::getInstanceID() const
{
    return this->instanceID;
}

void Ospfv3Packet::setInstanceID(int8_t instanceID)
{
    handleChange();
    this->instanceID = instanceID;
}

uint8_t Ospfv3Packet::getReserved() const
{
    return this->reserved;
}

void Ospfv3Packet::setReserved(uint8_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

class Ospfv3PacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_instanceID,
        FIELD_reserved,
    };
  public:
    Ospfv3PacketDescriptor();
    virtual ~Ospfv3PacketDescriptor();

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

Register_ClassDescriptor(Ospfv3PacketDescriptor)

Ospfv3PacketDescriptor::Ospfv3PacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3Packet)), "inet::ospf::OspfPacketBase")
{
    propertyNames = nullptr;
}

Ospfv3PacketDescriptor::~Ospfv3PacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3PacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3Packet *>(obj)!=nullptr;
}

const char **Ospfv3PacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3PacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3PacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv3PacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_instanceID
        FD_ISEDITABLE,    // FIELD_reserved
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3PacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "instanceID",
        "reserved",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv3PacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "instanceID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3PacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int8_t",    // FIELD_instanceID
        "uint8_t",    // FIELD_reserved
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3PacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3PacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3PacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3PacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3Packet'", field);
    }
}

const char *Ospfv3PacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3PacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_instanceID: return long2string(pp->getInstanceID());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        default: return "";
    }
}

void Ospfv3PacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_instanceID: pp->setInstanceID(string2long(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Packet'", field);
    }
}

omnetpp::cValue Ospfv3PacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_instanceID: return pp->getInstanceID();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3Packet' as cValue -- field index out of range?", field);
    }
}

void Ospfv3PacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        case FIELD_instanceID: pp->setInstanceID(omnetpp::checked_int_cast<int8_t>(value.intValue())); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Packet'", field);
    }
}

const char *Ospfv3PacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3PacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3PacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Packet *pp = omnetpp::fromAnyPtr<Ospfv3Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Packet'", field);
    }
}

Ospfv3Options::Ospfv3Options()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3Options& a)
{
    doParsimPacking(b,a.reserved);
    doParsimPacking(b,a.reservedOne);
    doParsimPacking(b,a.reservedTwo);
    doParsimPacking(b,a.dcBit);
    doParsimPacking(b,a.rBit);
    doParsimPacking(b,a.nBit);
    doParsimPacking(b,a.xBit);
    doParsimPacking(b,a.eBit);
    doParsimPacking(b,a.v6Bit);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3Options& a)
{
    doParsimUnpacking(b,a.reserved);
    doParsimUnpacking(b,a.reservedOne);
    doParsimUnpacking(b,a.reservedTwo);
    doParsimUnpacking(b,a.dcBit);
    doParsimUnpacking(b,a.rBit);
    doParsimUnpacking(b,a.nBit);
    doParsimUnpacking(b,a.xBit);
    doParsimUnpacking(b,a.eBit);
    doParsimUnpacking(b,a.v6Bit);
}

class Ospfv3OptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_reservedOne,
        FIELD_reservedTwo,
        FIELD_dcBit,
        FIELD_rBit,
        FIELD_nBit,
        FIELD_xBit,
        FIELD_eBit,
        FIELD_v6Bit,
    };
  public:
    Ospfv3OptionsDescriptor();
    virtual ~Ospfv3OptionsDescriptor();

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

Register_ClassDescriptor(Ospfv3OptionsDescriptor)

Ospfv3OptionsDescriptor::Ospfv3OptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3Options)), "")
{
    propertyNames = nullptr;
}

Ospfv3OptionsDescriptor::~Ospfv3OptionsDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3OptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3Options *>(obj)!=nullptr;
}

const char **Ospfv3OptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3OptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3OptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ospfv3OptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_reservedOne
        FD_ISEDITABLE,    // FIELD_reservedTwo
        FD_ISEDITABLE,    // FIELD_dcBit
        FD_ISEDITABLE,    // FIELD_rBit
        FD_ISEDITABLE,    // FIELD_nBit
        FD_ISEDITABLE,    // FIELD_xBit
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_v6Bit
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3OptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "reservedOne",
        "reservedTwo",
        "dcBit",
        "rBit",
        "nBit",
        "xBit",
        "eBit",
        "v6Bit",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ospfv3OptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reservedOne") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reservedTwo") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dcBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "rBit") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "nBit") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "xBit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "v6Bit") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3OptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "bool",    // FIELD_reservedOne
        "bool",    // FIELD_reservedTwo
        "bool",    // FIELD_dcBit
        "bool",    // FIELD_rBit
        "bool",    // FIELD_nBit
        "bool",    // FIELD_xBit
        "bool",    // FIELD_eBit
        "bool",    // FIELD_v6Bit
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3OptionsDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3OptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3OptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3OptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3Options'", field);
    }
}

const char *Ospfv3OptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3OptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->reserved);
        case FIELD_reservedOne: return bool2string(pp->reservedOne);
        case FIELD_reservedTwo: return bool2string(pp->reservedTwo);
        case FIELD_dcBit: return bool2string(pp->dcBit);
        case FIELD_rBit: return bool2string(pp->rBit);
        case FIELD_nBit: return bool2string(pp->nBit);
        case FIELD_xBit: return bool2string(pp->xBit);
        case FIELD_eBit: return bool2string(pp->eBit);
        case FIELD_v6Bit: return bool2string(pp->v6Bit);
        default: return "";
    }
}

void Ospfv3OptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = string2ulong(value); break;
        case FIELD_reservedOne: pp->reservedOne = string2bool(value); break;
        case FIELD_reservedTwo: pp->reservedTwo = string2bool(value); break;
        case FIELD_dcBit: pp->dcBit = string2bool(value); break;
        case FIELD_rBit: pp->rBit = string2bool(value); break;
        case FIELD_nBit: pp->nBit = string2bool(value); break;
        case FIELD_xBit: pp->xBit = string2bool(value); break;
        case FIELD_eBit: pp->eBit = string2bool(value); break;
        case FIELD_v6Bit: pp->v6Bit = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Options'", field);
    }
}

omnetpp::cValue Ospfv3OptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->reserved);
        case FIELD_reservedOne: return pp->reservedOne;
        case FIELD_reservedTwo: return pp->reservedTwo;
        case FIELD_dcBit: return pp->dcBit;
        case FIELD_rBit: return pp->rBit;
        case FIELD_nBit: return pp->nBit;
        case FIELD_xBit: return pp->xBit;
        case FIELD_eBit: return pp->eBit;
        case FIELD_v6Bit: return pp->v6Bit;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3Options' as cValue -- field index out of range?", field);
    }
}

void Ospfv3OptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        case FIELD_reservedOne: pp->reservedOne = value.boolValue(); break;
        case FIELD_reservedTwo: pp->reservedTwo = value.boolValue(); break;
        case FIELD_dcBit: pp->dcBit = value.boolValue(); break;
        case FIELD_rBit: pp->rBit = value.boolValue(); break;
        case FIELD_nBit: pp->nBit = value.boolValue(); break;
        case FIELD_xBit: pp->xBit = value.boolValue(); break;
        case FIELD_eBit: pp->eBit = value.boolValue(); break;
        case FIELD_v6Bit: pp->v6Bit = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Options'", field);
    }
}

const char *Ospfv3OptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3OptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3OptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Options *pp = omnetpp::fromAnyPtr<Ospfv3Options>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Options'", field);
    }
}

Register_Class(Ospfv3HelloPacket)

Ospfv3HelloPacket::Ospfv3HelloPacket() : ::inet::ospfv3::Ospfv3Packet()
{
    this->setType(ospf::HELLO_PACKET);

}

Ospfv3HelloPacket::Ospfv3HelloPacket(const Ospfv3HelloPacket& other) : ::inet::ospfv3::Ospfv3Packet(other)
{
    copy(other);
}

Ospfv3HelloPacket::~Ospfv3HelloPacket()
{
    delete [] this->neighborID;
}

Ospfv3HelloPacket& Ospfv3HelloPacket::operator=(const Ospfv3HelloPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3HelloPacket::copy(const Ospfv3HelloPacket& other)
{
    this->interfaceID = other.interfaceID;
    this->routerPriority = other.routerPriority;
    this->options = other.options;
    this->helloInterval = other.helloInterval;
    this->deadInterval = other.deadInterval;
    this->designatedRouterID = other.designatedRouterID;
    this->backupDesignatedRouterID = other.backupDesignatedRouterID;
    delete [] this->neighborID;
    this->neighborID = (other.neighborID_arraysize==0) ? nullptr : new ::inet::Ipv4Address[other.neighborID_arraysize];
    neighborID_arraysize = other.neighborID_arraysize;
    for (size_t i = 0; i < neighborID_arraysize; i++) {
        this->neighborID[i] = other.neighborID[i];
    }
}

void Ospfv3HelloPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Packet::parsimPack(b);
    doParsimPacking(b,this->interfaceID);
    doParsimPacking(b,this->routerPriority);
    doParsimPacking(b,this->options);
    doParsimPacking(b,this->helloInterval);
    doParsimPacking(b,this->deadInterval);
    doParsimPacking(b,this->designatedRouterID);
    doParsimPacking(b,this->backupDesignatedRouterID);
    b->pack(neighborID_arraysize);
    doParsimArrayPacking(b,this->neighborID,neighborID_arraysize);
}

void Ospfv3HelloPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceID);
    doParsimUnpacking(b,this->routerPriority);
    doParsimUnpacking(b,this->options);
    doParsimUnpacking(b,this->helloInterval);
    doParsimUnpacking(b,this->deadInterval);
    doParsimUnpacking(b,this->designatedRouterID);
    doParsimUnpacking(b,this->backupDesignatedRouterID);
    delete [] this->neighborID;
    b->unpack(neighborID_arraysize);
    if (neighborID_arraysize == 0) {
        this->neighborID = nullptr;
    } else {
        this->neighborID = new ::inet::Ipv4Address[neighborID_arraysize];
        doParsimArrayUnpacking(b,this->neighborID,neighborID_arraysize);
    }
}

uint32_t Ospfv3HelloPacket::getInterfaceID() const
{
    return this->interfaceID;
}

void Ospfv3HelloPacket::setInterfaceID(uint32_t interfaceID)
{
    handleChange();
    this->interfaceID = interfaceID;
}

char Ospfv3HelloPacket::getRouterPriority() const
{
    return this->routerPriority;
}

void Ospfv3HelloPacket::setRouterPriority(char routerPriority)
{
    handleChange();
    this->routerPriority = routerPriority;
}

const Ospfv3Options& Ospfv3HelloPacket::getOptions() const
{
    return this->options;
}

void Ospfv3HelloPacket::setOptions(const Ospfv3Options& options)
{
    handleChange();
    this->options = options;
}

uint16_t Ospfv3HelloPacket::getHelloInterval() const
{
    return this->helloInterval;
}

void Ospfv3HelloPacket::setHelloInterval(uint16_t helloInterval)
{
    handleChange();
    this->helloInterval = helloInterval;
}

uint16_t Ospfv3HelloPacket::getDeadInterval() const
{
    return this->deadInterval;
}

void Ospfv3HelloPacket::setDeadInterval(uint16_t deadInterval)
{
    handleChange();
    this->deadInterval = deadInterval;
}

const ::inet::Ipv4Address& Ospfv3HelloPacket::getDesignatedRouterID() const
{
    return this->designatedRouterID;
}

void Ospfv3HelloPacket::setDesignatedRouterID(const ::inet::Ipv4Address& designatedRouterID)
{
    handleChange();
    this->designatedRouterID = designatedRouterID;
}

const ::inet::Ipv4Address& Ospfv3HelloPacket::getBackupDesignatedRouterID() const
{
    return this->backupDesignatedRouterID;
}

void Ospfv3HelloPacket::setBackupDesignatedRouterID(const ::inet::Ipv4Address& backupDesignatedRouterID)
{
    handleChange();
    this->backupDesignatedRouterID = backupDesignatedRouterID;
}

size_t Ospfv3HelloPacket::getNeighborIDArraySize() const
{
    return neighborID_arraysize;
}

const ::inet::Ipv4Address& Ospfv3HelloPacket::getNeighborID(size_t k) const
{
    if (k >= neighborID_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborID_arraysize, (unsigned long)k);
    return this->neighborID[k];
}

void Ospfv3HelloPacket::setNeighborIDArraySize(size_t newSize)
{
    handleChange();
    ::inet::Ipv4Address *neighborID2 = (newSize==0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t minSize = neighborID_arraysize < newSize ? neighborID_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighborID2[i] = this->neighborID[i];
    delete [] this->neighborID;
    this->neighborID = neighborID2;
    neighborID_arraysize = newSize;
}

void Ospfv3HelloPacket::setNeighborID(size_t k, const ::inet::Ipv4Address& neighborID)
{
    if (k >= neighborID_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborID_arraysize, (unsigned long)k);
    handleChange();
    this->neighborID[k] = neighborID;
}

void Ospfv3HelloPacket::insertNeighborID(size_t k, const ::inet::Ipv4Address& neighborID)
{
    if (k > neighborID_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborID_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborID_arraysize + 1;
    ::inet::Ipv4Address *neighborID2 = new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborID2[i] = this->neighborID[i];
    neighborID2[k] = neighborID;
    for (i = k + 1; i < newSize; i++)
        neighborID2[i] = this->neighborID[i-1];
    delete [] this->neighborID;
    this->neighborID = neighborID2;
    neighborID_arraysize = newSize;
}

void Ospfv3HelloPacket::appendNeighborID(const ::inet::Ipv4Address& neighborID)
{
    insertNeighborID(neighborID_arraysize, neighborID);
}

void Ospfv3HelloPacket::eraseNeighborID(size_t k)
{
    if (k >= neighborID_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborID_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborID_arraysize - 1;
    ::inet::Ipv4Address *neighborID2 = (newSize == 0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborID2[i] = this->neighborID[i];
    for (i = k; i < newSize; i++)
        neighborID2[i] = this->neighborID[i+1];
    delete [] this->neighborID;
    this->neighborID = neighborID2;
    neighborID_arraysize = newSize;
}

class Ospfv3HelloPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceID,
        FIELD_routerPriority,
        FIELD_options,
        FIELD_helloInterval,
        FIELD_deadInterval,
        FIELD_designatedRouterID,
        FIELD_backupDesignatedRouterID,
        FIELD_neighborID,
    };
  public:
    Ospfv3HelloPacketDescriptor();
    virtual ~Ospfv3HelloPacketDescriptor();

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

Register_ClassDescriptor(Ospfv3HelloPacketDescriptor)

Ospfv3HelloPacketDescriptor::Ospfv3HelloPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3HelloPacket)), "inet::ospfv3::Ospfv3Packet")
{
    propertyNames = nullptr;
}

Ospfv3HelloPacketDescriptor::~Ospfv3HelloPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3HelloPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3HelloPacket *>(obj)!=nullptr;
}

const char **Ospfv3HelloPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3HelloPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3HelloPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ospfv3HelloPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceID
        FD_ISEDITABLE,    // FIELD_routerPriority
        FD_ISCOMPOUND,    // FIELD_options
        FD_ISEDITABLE,    // FIELD_helloInterval
        FD_ISEDITABLE,    // FIELD_deadInterval
        0,    // FIELD_designatedRouterID
        0,    // FIELD_backupDesignatedRouterID
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_neighborID
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3HelloPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceID",
        "routerPriority",
        "options",
        "helloInterval",
        "deadInterval",
        "designatedRouterID",
        "backupDesignatedRouterID",
        "neighborID",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ospfv3HelloPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "routerPriority") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "helloInterval") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "deadInterval") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "designatedRouterID") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "backupDesignatedRouterID") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "neighborID") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3HelloPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_interfaceID
        "char",    // FIELD_routerPriority
        "inet::ospfv3::Ospfv3Options",    // FIELD_options
        "uint16_t",    // FIELD_helloInterval
        "uint16_t",    // FIELD_deadInterval
        "inet::Ipv4Address",    // FIELD_designatedRouterID
        "inet::Ipv4Address",    // FIELD_backupDesignatedRouterID
        "inet::Ipv4Address",    // FIELD_neighborID
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3HelloPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3HelloPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3HelloPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborID: return pp->getNeighborIDArraySize();
        default: return 0;
    }
}

void Ospfv3HelloPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborID: pp->setNeighborIDArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3HelloPacket'", field);
    }
}

const char *Ospfv3HelloPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3HelloPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceID: return ulong2string(pp->getInterfaceID());
        case FIELD_routerPriority: return long2string(pp->getRouterPriority());
        case FIELD_options: return "";
        case FIELD_helloInterval: return ulong2string(pp->getHelloInterval());
        case FIELD_deadInterval: return ulong2string(pp->getDeadInterval());
        case FIELD_designatedRouterID: return pp->getDesignatedRouterID().str();
        case FIELD_backupDesignatedRouterID: return pp->getBackupDesignatedRouterID().str();
        case FIELD_neighborID: return pp->getNeighborID(i).str();
        default: return "";
    }
}

void Ospfv3HelloPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceID: pp->setInterfaceID(string2ulong(value)); break;
        case FIELD_routerPriority: pp->setRouterPriority(string2long(value)); break;
        case FIELD_helloInterval: pp->setHelloInterval(string2ulong(value)); break;
        case FIELD_deadInterval: pp->setDeadInterval(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3HelloPacket'", field);
    }
}

omnetpp::cValue Ospfv3HelloPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceID: return (omnetpp::intval_t)(pp->getInterfaceID());
        case FIELD_routerPriority: return pp->getRouterPriority();
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_helloInterval: return (omnetpp::intval_t)(pp->getHelloInterval());
        case FIELD_deadInterval: return (omnetpp::intval_t)(pp->getDeadInterval());
        case FIELD_designatedRouterID: return omnetpp::toAnyPtr(&pp->getDesignatedRouterID()); break;
        case FIELD_backupDesignatedRouterID: return omnetpp::toAnyPtr(&pp->getBackupDesignatedRouterID()); break;
        case FIELD_neighborID: return omnetpp::toAnyPtr(&pp->getNeighborID(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3HelloPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv3HelloPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceID: pp->setInterfaceID(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_routerPriority: pp->setRouterPriority(omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_helloInterval: pp->setHelloInterval(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_deadInterval: pp->setDeadInterval(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3HelloPacket'", field);
    }
}

const char *Ospfv3HelloPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ospfv3Options));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3HelloPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_designatedRouterID: return omnetpp::toAnyPtr(&pp->getDesignatedRouterID()); break;
        case FIELD_backupDesignatedRouterID: return omnetpp::toAnyPtr(&pp->getBackupDesignatedRouterID()); break;
        case FIELD_neighborID: return omnetpp::toAnyPtr(&pp->getNeighborID(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3HelloPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv3HelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3HelloPacket'", field);
    }
}

Register_Class(Ospfv3LsaHeader)

Ospfv3LsaHeader::Ospfv3LsaHeader() : ::omnetpp::cObject()
{
}

Ospfv3LsaHeader::Ospfv3LsaHeader(const Ospfv3LsaHeader& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv3LsaHeader::~Ospfv3LsaHeader()
{
}

Ospfv3LsaHeader& Ospfv3LsaHeader::operator=(const Ospfv3LsaHeader& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3LsaHeader::copy(const Ospfv3LsaHeader& other)
{
    this->lsaAge = other.lsaAge;
    this->options = other.options;
    this->lsaType = other.lsaType;
    this->linkStateID = other.linkStateID;
    this->advertisingRouter = other.advertisingRouter;
    this->lsaSequenceNumber = other.lsaSequenceNumber;
    this->lsaChecksum = other.lsaChecksum;
    this->lsCrcMode = other.lsCrcMode;
    this->lsaLength = other.lsaLength;
}

void Ospfv3LsaHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->lsaAge);
    doParsimPacking(b,this->options);
    doParsimPacking(b,this->lsaType);
    doParsimPacking(b,this->linkStateID);
    doParsimPacking(b,this->advertisingRouter);
    doParsimPacking(b,this->lsaSequenceNumber);
    doParsimPacking(b,this->lsaChecksum);
    doParsimPacking(b,this->lsCrcMode);
    doParsimPacking(b,this->lsaLength);
}

void Ospfv3LsaHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->lsaAge);
    doParsimUnpacking(b,this->options);
    doParsimUnpacking(b,this->lsaType);
    doParsimUnpacking(b,this->linkStateID);
    doParsimUnpacking(b,this->advertisingRouter);
    doParsimUnpacking(b,this->lsaSequenceNumber);
    doParsimUnpacking(b,this->lsaChecksum);
    doParsimUnpacking(b,this->lsCrcMode);
    doParsimUnpacking(b,this->lsaLength);
}

unsigned short Ospfv3LsaHeader::getLsaAge() const
{
    return this->lsaAge;
}

void Ospfv3LsaHeader::setLsaAge(unsigned short lsaAge)
{
    this->lsaAge = lsaAge;
}

unsigned short Ospfv3LsaHeader::getOptions() const
{
    return this->options;
}

void Ospfv3LsaHeader::setOptions(unsigned short options)
{
    this->options = options;
}

unsigned short Ospfv3LsaHeader::getLsaType() const
{
    return this->lsaType;
}

void Ospfv3LsaHeader::setLsaType(unsigned short lsaType)
{
    this->lsaType = lsaType;
}

const ::inet::Ipv4Address& Ospfv3LsaHeader::getLinkStateID() const
{
    return this->linkStateID;
}

void Ospfv3LsaHeader::setLinkStateID(const ::inet::Ipv4Address& linkStateID)
{
    this->linkStateID = linkStateID;
}

const ::inet::Ipv4Address& Ospfv3LsaHeader::getAdvertisingRouter() const
{
    return this->advertisingRouter;
}

void Ospfv3LsaHeader::setAdvertisingRouter(const ::inet::Ipv4Address& advertisingRouter)
{
    this->advertisingRouter = advertisingRouter;
}

uint32_t Ospfv3LsaHeader::getLsaSequenceNumber() const
{
    return this->lsaSequenceNumber;
}

void Ospfv3LsaHeader::setLsaSequenceNumber(uint32_t lsaSequenceNumber)
{
    this->lsaSequenceNumber = lsaSequenceNumber;
}

uint16_t Ospfv3LsaHeader::getLsaChecksum() const
{
    return this->lsaChecksum;
}

void Ospfv3LsaHeader::setLsaChecksum(uint16_t lsaChecksum)
{
    this->lsaChecksum = lsaChecksum;
}

::inet::CrcMode Ospfv3LsaHeader::getLsCrcMode() const
{
    return this->lsCrcMode;
}

void Ospfv3LsaHeader::setLsCrcMode(::inet::CrcMode lsCrcMode)
{
    this->lsCrcMode = lsCrcMode;
}

uint16_t Ospfv3LsaHeader::getLsaLength() const
{
    return this->lsaLength;
}

void Ospfv3LsaHeader::setLsaLength(uint16_t lsaLength)
{
    this->lsaLength = lsaLength;
}

class Ospfv3LsaHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsaAge,
        FIELD_options,
        FIELD_lsaType,
        FIELD_linkStateID,
        FIELD_advertisingRouter,
        FIELD_lsaSequenceNumber,
        FIELD_lsaChecksum,
        FIELD_lsCrcMode,
        FIELD_lsaLength,
    };
  public:
    Ospfv3LsaHeaderDescriptor();
    virtual ~Ospfv3LsaHeaderDescriptor();

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

Register_ClassDescriptor(Ospfv3LsaHeaderDescriptor)

Ospfv3LsaHeaderDescriptor::Ospfv3LsaHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LsaHeader)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv3LsaHeaderDescriptor::~Ospfv3LsaHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LsaHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LsaHeader *>(obj)!=nullptr;
}

const char **Ospfv3LsaHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LsaHeaderDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LsaHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ospfv3LsaHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsaAge
        FD_ISEDITABLE,    // FIELD_options
        FD_ISEDITABLE,    // FIELD_lsaType
        0,    // FIELD_linkStateID
        0,    // FIELD_advertisingRouter
        FD_ISEDITABLE,    // FIELD_lsaSequenceNumber
        FD_ISEDITABLE,    // FIELD_lsaChecksum
        FD_ISEDITABLE,    // FIELD_lsCrcMode
        FD_ISEDITABLE,    // FIELD_lsaLength
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LsaHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsaAge",
        "options",
        "lsaType",
        "linkStateID",
        "advertisingRouter",
        "lsaSequenceNumber",
        "lsaChecksum",
        "lsCrcMode",
        "lsaLength",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ospfv3LsaHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsaAge") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "lsaType") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "linkStateID") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "advertisingRouter") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lsaSequenceNumber") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "lsaChecksum") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "lsCrcMode") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "lsaLength") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LsaHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_lsaAge
        "unsigned short",    // FIELD_options
        "unsigned short",    // FIELD_lsaType
        "inet::Ipv4Address",    // FIELD_linkStateID
        "inet::Ipv4Address",    // FIELD_advertisingRouter
        "uint32_t",    // FIELD_lsaSequenceNumber
        "uint16_t",    // FIELD_lsaChecksum
        "inet::CrcMode",    // FIELD_lsCrcMode
        "uint16_t",    // FIELD_lsaLength
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LsaHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsCrcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ospfv3LsaHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsCrcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ospfv3LsaHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3LsaHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LsaHeader'", field);
    }
}

const char *Ospfv3LsaHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LsaHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsaAge: return ulong2string(pp->getLsaAge());
        case FIELD_options: return ulong2string(pp->getOptions());
        case FIELD_lsaType: return ulong2string(pp->getLsaType());
        case FIELD_linkStateID: return pp->getLinkStateID().str();
        case FIELD_advertisingRouter: return pp->getAdvertisingRouter().str();
        case FIELD_lsaSequenceNumber: return ulong2string(pp->getLsaSequenceNumber());
        case FIELD_lsaChecksum: return ulong2string(pp->getLsaChecksum());
        case FIELD_lsCrcMode: return enum2string(pp->getLsCrcMode(), "inet::CrcMode");
        case FIELD_lsaLength: return ulong2string(pp->getLsaLength());
        default: return "";
    }
}

void Ospfv3LsaHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsaAge: pp->setLsaAge(string2ulong(value)); break;
        case FIELD_options: pp->setOptions(string2ulong(value)); break;
        case FIELD_lsaType: pp->setLsaType(string2ulong(value)); break;
        case FIELD_lsaSequenceNumber: pp->setLsaSequenceNumber(string2ulong(value)); break;
        case FIELD_lsaChecksum: pp->setLsaChecksum(string2ulong(value)); break;
        case FIELD_lsCrcMode: pp->setLsCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        case FIELD_lsaLength: pp->setLsaLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaHeader'", field);
    }
}

omnetpp::cValue Ospfv3LsaHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsaAge: return (omnetpp::intval_t)(pp->getLsaAge());
        case FIELD_options: return (omnetpp::intval_t)(pp->getOptions());
        case FIELD_lsaType: return (omnetpp::intval_t)(pp->getLsaType());
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->getLinkStateID()); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->getAdvertisingRouter()); break;
        case FIELD_lsaSequenceNumber: return (omnetpp::intval_t)(pp->getLsaSequenceNumber());
        case FIELD_lsaChecksum: return (omnetpp::intval_t)(pp->getLsaChecksum());
        case FIELD_lsCrcMode: return static_cast<int>(pp->getLsCrcMode());
        case FIELD_lsaLength: return (omnetpp::intval_t)(pp->getLsaLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LsaHeader' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LsaHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsaAge: pp->setLsaAge(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_options: pp->setOptions(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_lsaType: pp->setLsaType(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_lsaSequenceNumber: pp->setLsaSequenceNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_lsaChecksum: pp->setLsaChecksum(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_lsCrcMode: pp->setLsCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        case FIELD_lsaLength: pp->setLsaLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaHeader'", field);
    }
}

const char *Ospfv3LsaHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3LsaHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->getLinkStateID()); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->getAdvertisingRouter()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LsaHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv3LsaHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaHeader'", field);
    }
}

Register_Class(Ospfv3Lsa)

Ospfv3Lsa::Ospfv3Lsa() : ::omnetpp::cObject()
{
}

Ospfv3Lsa::Ospfv3Lsa(const Ospfv3Lsa& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv3Lsa::~Ospfv3Lsa()
{
}

Ospfv3Lsa& Ospfv3Lsa::operator=(const Ospfv3Lsa& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3Lsa::copy(const Ospfv3Lsa& other)
{
    this->header = other.header;
}

void Ospfv3Lsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->header);
}

void Ospfv3Lsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->header);
}

const Ospfv3LsaHeader& Ospfv3Lsa::getHeader() const
{
    return this->header;
}

void Ospfv3Lsa::setHeader(const Ospfv3LsaHeader& header)
{
    this->header = header;
}

class Ospfv3LsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_header,
    };
  public:
    Ospfv3LsaDescriptor();
    virtual ~Ospfv3LsaDescriptor();

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

Register_ClassDescriptor(Ospfv3LsaDescriptor)

Ospfv3LsaDescriptor::Ospfv3LsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3Lsa)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv3LsaDescriptor::~Ospfv3LsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3Lsa *>(obj)!=nullptr;
}

const char **Ospfv3LsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LsaDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv3LsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_header
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "header",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ospfv3LsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "header") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv3::Ospfv3LsaHeader",    // FIELD_header
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3LsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3Lsa'", field);
    }
}

const char *Ospfv3LsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return pp->getHeader().str();
        default: return "";
    }
}

void Ospfv3LsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Lsa'", field);
    }
}

omnetpp::cValue Ospfv3LsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return omnetpp::toAnyPtr(&pp->getHeader()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3Lsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Lsa'", field);
    }
}

const char *Ospfv3LsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_header: return omnetpp::opp_typename(typeid(Ospfv3LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3LsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return omnetpp::toAnyPtr(&pp->getHeader()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3Lsa *pp = omnetpp::fromAnyPtr<Ospfv3Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3Lsa'", field);
    }
}

Register_Enum(inet::ospfv3::Ospfv3LsaFunctionCode, (inet::ospfv3::Ospfv3LsaFunctionCode::ROUTER_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::NETWORK_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::INTER_AREA_PREFIX_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::INTER_AREA_ROUTER_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::AS_EXTERNAL_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::DEPRECATED, inet::ospfv3::Ospfv3LsaFunctionCode::NSSA_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::LINK_LSA, inet::ospfv3::Ospfv3LsaFunctionCode::INTRA_AREA_PREFIX_LSA));

Ospfv3LsaPrefixMetric::Ospfv3LsaPrefixMetric()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3LsaPrefixMetric& a)
{
    doParsimPacking(b,a.reserved1);
    doParsimPacking(b,a.reserved2);
    doParsimPacking(b,a.reserved3);
    doParsimPacking(b,a.dnBit);
    doParsimPacking(b,a.pBit);
    doParsimPacking(b,a.xBit);
    doParsimPacking(b,a.laBit);
    doParsimPacking(b,a.nuBit);
    doParsimPacking(b,a.prefixLen);
    doParsimPacking(b,a.metric);
    doParsimPacking(b,a.addressPrefix);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3LsaPrefixMetric& a)
{
    doParsimUnpacking(b,a.reserved1);
    doParsimUnpacking(b,a.reserved2);
    doParsimUnpacking(b,a.reserved3);
    doParsimUnpacking(b,a.dnBit);
    doParsimUnpacking(b,a.pBit);
    doParsimUnpacking(b,a.xBit);
    doParsimUnpacking(b,a.laBit);
    doParsimUnpacking(b,a.nuBit);
    doParsimUnpacking(b,a.prefixLen);
    doParsimUnpacking(b,a.metric);
    doParsimUnpacking(b,a.addressPrefix);
}

class Ospfv3LsaPrefixMetricDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_reserved2,
        FIELD_reserved3,
        FIELD_dnBit,
        FIELD_pBit,
        FIELD_xBit,
        FIELD_laBit,
        FIELD_nuBit,
        FIELD_prefixLen,
        FIELD_metric,
        FIELD_addressPrefix,
    };
  public:
    Ospfv3LsaPrefixMetricDescriptor();
    virtual ~Ospfv3LsaPrefixMetricDescriptor();

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

Register_ClassDescriptor(Ospfv3LsaPrefixMetricDescriptor)

Ospfv3LsaPrefixMetricDescriptor::Ospfv3LsaPrefixMetricDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LsaPrefixMetric)), "")
{
    propertyNames = nullptr;
}

Ospfv3LsaPrefixMetricDescriptor::~Ospfv3LsaPrefixMetricDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LsaPrefixMetricDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LsaPrefixMetric *>(obj)!=nullptr;
}

const char **Ospfv3LsaPrefixMetricDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LsaPrefixMetricDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LsaPrefixMetricDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int Ospfv3LsaPrefixMetricDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISEDITABLE,    // FIELD_reserved2
        FD_ISEDITABLE,    // FIELD_reserved3
        FD_ISEDITABLE,    // FIELD_dnBit
        FD_ISEDITABLE,    // FIELD_pBit
        FD_ISEDITABLE,    // FIELD_xBit
        FD_ISEDITABLE,    // FIELD_laBit
        FD_ISEDITABLE,    // FIELD_nuBit
        FD_ISEDITABLE,    // FIELD_prefixLen
        FD_ISEDITABLE,    // FIELD_metric
        0,    // FIELD_addressPrefix
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LsaPrefixMetricDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "reserved2",
        "reserved3",
        "dnBit",
        "pBit",
        "xBit",
        "laBit",
        "nuBit",
        "prefixLen",
        "metric",
        "addressPrefix",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int Ospfv3LsaPrefixMetricDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved3") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dnBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "pBit") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "xBit") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "laBit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "nuBit") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "prefixLen") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "addressPrefix") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LsaPrefixMetricDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_reserved1
        "bool",    // FIELD_reserved2
        "bool",    // FIELD_reserved3
        "bool",    // FIELD_dnBit
        "bool",    // FIELD_pBit
        "bool",    // FIELD_xBit
        "bool",    // FIELD_laBit
        "bool",    // FIELD_nuBit
        "uint8_t",    // FIELD_prefixLen
        "uint16_t",    // FIELD_metric
        "inet::L3Address",    // FIELD_addressPrefix
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LsaPrefixMetricDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LsaPrefixMetricDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LsaPrefixMetricDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3LsaPrefixMetricDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LsaPrefixMetric'", field);
    }
}

const char *Ospfv3LsaPrefixMetricDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LsaPrefixMetricDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return bool2string(pp->reserved1);
        case FIELD_reserved2: return bool2string(pp->reserved2);
        case FIELD_reserved3: return bool2string(pp->reserved3);
        case FIELD_dnBit: return bool2string(pp->dnBit);
        case FIELD_pBit: return bool2string(pp->pBit);
        case FIELD_xBit: return bool2string(pp->xBit);
        case FIELD_laBit: return bool2string(pp->laBit);
        case FIELD_nuBit: return bool2string(pp->nuBit);
        case FIELD_prefixLen: return ulong2string(pp->prefixLen);
        case FIELD_metric: return ulong2string(pp->metric);
        case FIELD_addressPrefix: return pp->addressPrefix.str();
        default: return "";
    }
}

void Ospfv3LsaPrefixMetricDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->reserved1 = string2bool(value); break;
        case FIELD_reserved2: pp->reserved2 = string2bool(value); break;
        case FIELD_reserved3: pp->reserved3 = string2bool(value); break;
        case FIELD_dnBit: pp->dnBit = string2bool(value); break;
        case FIELD_pBit: pp->pBit = string2bool(value); break;
        case FIELD_xBit: pp->xBit = string2bool(value); break;
        case FIELD_laBit: pp->laBit = string2bool(value); break;
        case FIELD_nuBit: pp->nuBit = string2bool(value); break;
        case FIELD_prefixLen: pp->prefixLen = string2ulong(value); break;
        case FIELD_metric: pp->metric = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefixMetric'", field);
    }
}

omnetpp::cValue Ospfv3LsaPrefixMetricDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return pp->reserved1;
        case FIELD_reserved2: return pp->reserved2;
        case FIELD_reserved3: return pp->reserved3;
        case FIELD_dnBit: return pp->dnBit;
        case FIELD_pBit: return pp->pBit;
        case FIELD_xBit: return pp->xBit;
        case FIELD_laBit: return pp->laBit;
        case FIELD_nuBit: return pp->nuBit;
        case FIELD_prefixLen: return (omnetpp::intval_t)(pp->prefixLen);
        case FIELD_metric: return (omnetpp::intval_t)(pp->metric);
        case FIELD_addressPrefix: return omnetpp::toAnyPtr(&pp->addressPrefix); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LsaPrefixMetric' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LsaPrefixMetricDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->reserved1 = value.boolValue(); break;
        case FIELD_reserved2: pp->reserved2 = value.boolValue(); break;
        case FIELD_reserved3: pp->reserved3 = value.boolValue(); break;
        case FIELD_dnBit: pp->dnBit = value.boolValue(); break;
        case FIELD_pBit: pp->pBit = value.boolValue(); break;
        case FIELD_xBit: pp->xBit = value.boolValue(); break;
        case FIELD_laBit: pp->laBit = value.boolValue(); break;
        case FIELD_nuBit: pp->nuBit = value.boolValue(); break;
        case FIELD_prefixLen: pp->prefixLen = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_metric: pp->metric = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefixMetric'", field);
    }
}

const char *Ospfv3LsaPrefixMetricDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3LsaPrefixMetricDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        case FIELD_addressPrefix: return omnetpp::toAnyPtr(&pp->addressPrefix); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LsaPrefixMetricDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefixMetric *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefixMetric>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefixMetric'", field);
    }
}

Ospfv3LsaPrefix0::Ospfv3LsaPrefix0()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3LsaPrefix0& a)
{
    doParsimPacking(b,a.reserved1);
    doParsimPacking(b,a.reserved2);
    doParsimPacking(b,a.reserved3);
    doParsimPacking(b,a.dnBit);
    doParsimPacking(b,a.pBit);
    doParsimPacking(b,a.xBit);
    doParsimPacking(b,a.laBit);
    doParsimPacking(b,a.nuBit);
    doParsimPacking(b,a.prefixLen);
    doParsimPacking(b,a.reserved);
    doParsimPacking(b,a.addressPrefix);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3LsaPrefix0& a)
{
    doParsimUnpacking(b,a.reserved1);
    doParsimUnpacking(b,a.reserved2);
    doParsimUnpacking(b,a.reserved3);
    doParsimUnpacking(b,a.dnBit);
    doParsimUnpacking(b,a.pBit);
    doParsimUnpacking(b,a.xBit);
    doParsimUnpacking(b,a.laBit);
    doParsimUnpacking(b,a.nuBit);
    doParsimUnpacking(b,a.prefixLen);
    doParsimUnpacking(b,a.reserved);
    doParsimUnpacking(b,a.addressPrefix);
}

class Ospfv3LsaPrefix0Descriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_reserved2,
        FIELD_reserved3,
        FIELD_dnBit,
        FIELD_pBit,
        FIELD_xBit,
        FIELD_laBit,
        FIELD_nuBit,
        FIELD_prefixLen,
        FIELD_reserved,
        FIELD_addressPrefix,
    };
  public:
    Ospfv3LsaPrefix0Descriptor();
    virtual ~Ospfv3LsaPrefix0Descriptor();

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

Register_ClassDescriptor(Ospfv3LsaPrefix0Descriptor)

Ospfv3LsaPrefix0Descriptor::Ospfv3LsaPrefix0Descriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LsaPrefix0)), "")
{
    propertyNames = nullptr;
}

Ospfv3LsaPrefix0Descriptor::~Ospfv3LsaPrefix0Descriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LsaPrefix0Descriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LsaPrefix0 *>(obj)!=nullptr;
}

const char **Ospfv3LsaPrefix0Descriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LsaPrefix0Descriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LsaPrefix0Descriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int Ospfv3LsaPrefix0Descriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISEDITABLE,    // FIELD_reserved2
        FD_ISEDITABLE,    // FIELD_reserved3
        FD_ISEDITABLE,    // FIELD_dnBit
        FD_ISEDITABLE,    // FIELD_pBit
        FD_ISEDITABLE,    // FIELD_xBit
        FD_ISEDITABLE,    // FIELD_laBit
        FD_ISEDITABLE,    // FIELD_nuBit
        FD_ISEDITABLE,    // FIELD_prefixLen
        FD_ISEDITABLE,    // FIELD_reserved
        0,    // FIELD_addressPrefix
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LsaPrefix0Descriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "reserved2",
        "reserved3",
        "dnBit",
        "pBit",
        "xBit",
        "laBit",
        "nuBit",
        "prefixLen",
        "reserved",
        "addressPrefix",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int Ospfv3LsaPrefix0Descriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved3") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dnBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "pBit") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "xBit") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "laBit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "nuBit") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "prefixLen") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "addressPrefix") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LsaPrefix0Descriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_reserved1
        "bool",    // FIELD_reserved2
        "bool",    // FIELD_reserved3
        "bool",    // FIELD_dnBit
        "bool",    // FIELD_pBit
        "bool",    // FIELD_xBit
        "bool",    // FIELD_laBit
        "bool",    // FIELD_nuBit
        "uint8_t",    // FIELD_prefixLen
        "uint16_t",    // FIELD_reserved
        "inet::L3Address",    // FIELD_addressPrefix
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LsaPrefix0Descriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LsaPrefix0Descriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LsaPrefix0Descriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3LsaPrefix0Descriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LsaPrefix0'", field);
    }
}

const char *Ospfv3LsaPrefix0Descriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LsaPrefix0Descriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return bool2string(pp->reserved1);
        case FIELD_reserved2: return bool2string(pp->reserved2);
        case FIELD_reserved3: return bool2string(pp->reserved3);
        case FIELD_dnBit: return bool2string(pp->dnBit);
        case FIELD_pBit: return bool2string(pp->pBit);
        case FIELD_xBit: return bool2string(pp->xBit);
        case FIELD_laBit: return bool2string(pp->laBit);
        case FIELD_nuBit: return bool2string(pp->nuBit);
        case FIELD_prefixLen: return ulong2string(pp->prefixLen);
        case FIELD_reserved: return ulong2string(pp->reserved);
        case FIELD_addressPrefix: return pp->addressPrefix.str();
        default: return "";
    }
}

void Ospfv3LsaPrefix0Descriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->reserved1 = string2bool(value); break;
        case FIELD_reserved2: pp->reserved2 = string2bool(value); break;
        case FIELD_reserved3: pp->reserved3 = string2bool(value); break;
        case FIELD_dnBit: pp->dnBit = string2bool(value); break;
        case FIELD_pBit: pp->pBit = string2bool(value); break;
        case FIELD_xBit: pp->xBit = string2bool(value); break;
        case FIELD_laBit: pp->laBit = string2bool(value); break;
        case FIELD_nuBit: pp->nuBit = string2bool(value); break;
        case FIELD_prefixLen: pp->prefixLen = string2ulong(value); break;
        case FIELD_reserved: pp->reserved = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefix0'", field);
    }
}

omnetpp::cValue Ospfv3LsaPrefix0Descriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return pp->reserved1;
        case FIELD_reserved2: return pp->reserved2;
        case FIELD_reserved3: return pp->reserved3;
        case FIELD_dnBit: return pp->dnBit;
        case FIELD_pBit: return pp->pBit;
        case FIELD_xBit: return pp->xBit;
        case FIELD_laBit: return pp->laBit;
        case FIELD_nuBit: return pp->nuBit;
        case FIELD_prefixLen: return (omnetpp::intval_t)(pp->prefixLen);
        case FIELD_reserved: return (omnetpp::intval_t)(pp->reserved);
        case FIELD_addressPrefix: return omnetpp::toAnyPtr(&pp->addressPrefix); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LsaPrefix0' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LsaPrefix0Descriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->reserved1 = value.boolValue(); break;
        case FIELD_reserved2: pp->reserved2 = value.boolValue(); break;
        case FIELD_reserved3: pp->reserved3 = value.boolValue(); break;
        case FIELD_dnBit: pp->dnBit = value.boolValue(); break;
        case FIELD_pBit: pp->pBit = value.boolValue(); break;
        case FIELD_xBit: pp->xBit = value.boolValue(); break;
        case FIELD_laBit: pp->laBit = value.boolValue(); break;
        case FIELD_nuBit: pp->nuBit = value.boolValue(); break;
        case FIELD_prefixLen: pp->prefixLen = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_reserved: pp->reserved = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefix0'", field);
    }
}

const char *Ospfv3LsaPrefix0Descriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3LsaPrefix0Descriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        case FIELD_addressPrefix: return omnetpp::toAnyPtr(&pp->addressPrefix); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LsaPrefix0Descriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsaPrefix0 *pp = omnetpp::fromAnyPtr<Ospfv3LsaPrefix0>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsaPrefix0'", field);
    }
}

Register_Enum(inet::ospfv3::Ospfv3RouterLsaType, (inet::ospfv3::Ospfv3RouterLsaType::POINT_TO_POINT, inet::ospfv3::Ospfv3RouterLsaType::TRANSIT_NETWORK, inet::ospfv3::Ospfv3RouterLsaType::RESERVED, inet::ospfv3::Ospfv3RouterLsaType::VIRTUAL_LINK));

Ospfv3RouterLsaBody::Ospfv3RouterLsaBody()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3RouterLsaBody& a)
{
    doParsimPacking(b,a.type);
    doParsimPacking(b,a.metric);
    doParsimPacking(b,a.interfaceID);
    doParsimPacking(b,a.neighborInterfaceID);
    doParsimPacking(b,a.neighborRouterID);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3RouterLsaBody& a)
{
    doParsimUnpacking(b,a.type);
    doParsimUnpacking(b,a.metric);
    doParsimUnpacking(b,a.interfaceID);
    doParsimUnpacking(b,a.neighborInterfaceID);
    doParsimUnpacking(b,a.neighborRouterID);
}

class Ospfv3RouterLsaBodyDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_metric,
        FIELD_interfaceID,
        FIELD_neighborInterfaceID,
        FIELD_neighborRouterID,
    };
  public:
    Ospfv3RouterLsaBodyDescriptor();
    virtual ~Ospfv3RouterLsaBodyDescriptor();

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

Register_ClassDescriptor(Ospfv3RouterLsaBodyDescriptor)

Ospfv3RouterLsaBodyDescriptor::Ospfv3RouterLsaBodyDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3RouterLsaBody)), "")
{
    propertyNames = nullptr;
}

Ospfv3RouterLsaBodyDescriptor::~Ospfv3RouterLsaBodyDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3RouterLsaBodyDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3RouterLsaBody *>(obj)!=nullptr;
}

const char **Ospfv3RouterLsaBodyDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3RouterLsaBodyDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3RouterLsaBodyDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ospfv3RouterLsaBodyDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_interfaceID
        FD_ISEDITABLE,    // FIELD_neighborInterfaceID
        0,    // FIELD_neighborRouterID
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3RouterLsaBodyDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "metric",
        "interfaceID",
        "neighborInterfaceID",
        "neighborRouterID",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ospfv3RouterLsaBodyDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "interfaceID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "neighborInterfaceID") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "neighborRouterID") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3RouterLsaBodyDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_type
        "uint16_t",    // FIELD_metric
        "uint32_t",    // FIELD_interfaceID
        "uint32_t",    // FIELD_neighborInterfaceID
        "inet::Ipv4Address",    // FIELD_neighborRouterID
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3RouterLsaBodyDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3RouterLsaBodyDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3RouterLsaBodyDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3RouterLsaBodyDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3RouterLsaBody'", field);
    }
}

const char *Ospfv3RouterLsaBodyDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3RouterLsaBodyDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        case FIELD_type: return ulong2string(pp->type);
        case FIELD_metric: return ulong2string(pp->metric);
        case FIELD_interfaceID: return ulong2string(pp->interfaceID);
        case FIELD_neighborInterfaceID: return ulong2string(pp->neighborInterfaceID);
        case FIELD_neighborRouterID: return pp->neighborRouterID.str();
        default: return "";
    }
}

void Ospfv3RouterLsaBodyDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->type = string2ulong(value); break;
        case FIELD_metric: pp->metric = string2ulong(value); break;
        case FIELD_interfaceID: pp->interfaceID = string2ulong(value); break;
        case FIELD_neighborInterfaceID: pp->neighborInterfaceID = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsaBody'", field);
    }
}

omnetpp::cValue Ospfv3RouterLsaBodyDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        case FIELD_type: return (omnetpp::intval_t)(pp->type);
        case FIELD_metric: return (omnetpp::intval_t)(pp->metric);
        case FIELD_interfaceID: return (omnetpp::intval_t)(pp->interfaceID);
        case FIELD_neighborInterfaceID: return (omnetpp::intval_t)(pp->neighborInterfaceID);
        case FIELD_neighborRouterID: return omnetpp::toAnyPtr(&pp->neighborRouterID); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3RouterLsaBody' as cValue -- field index out of range?", field);
    }
}

void Ospfv3RouterLsaBodyDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->type = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_metric: pp->metric = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        case FIELD_interfaceID: pp->interfaceID = omnetpp::checked_int_cast<uint32_t>(value.intValue()); break;
        case FIELD_neighborInterfaceID: pp->neighborInterfaceID = omnetpp::checked_int_cast<uint32_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsaBody'", field);
    }
}

const char *Ospfv3RouterLsaBodyDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3RouterLsaBodyDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        case FIELD_neighborRouterID: return omnetpp::toAnyPtr(&pp->neighborRouterID); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3RouterLsaBodyDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsaBody *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsaBody>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsaBody'", field);
    }
}

Register_Class(Ospfv3RouterLsa)

Ospfv3RouterLsa::Ospfv3RouterLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3RouterLsa::Ospfv3RouterLsa(const Ospfv3RouterLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3RouterLsa::~Ospfv3RouterLsa()
{
    delete [] this->routers;
}

Ospfv3RouterLsa& Ospfv3RouterLsa::operator=(const Ospfv3RouterLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3RouterLsa::copy(const Ospfv3RouterLsa& other)
{
    this->ntBit = other.ntBit;
    this->xBit = other.xBit;
    this->vBit = other.vBit;
    this->eBit = other.eBit;
    this->bBit = other.bBit;
    this->ospfOptions = other.ospfOptions;
    delete [] this->routers;
    this->routers = (other.routers_arraysize==0) ? nullptr : new Ospfv3RouterLsaBody[other.routers_arraysize];
    routers_arraysize = other.routers_arraysize;
    for (size_t i = 0; i < routers_arraysize; i++) {
        this->routers[i] = other.routers[i];
    }
}

void Ospfv3RouterLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->ntBit);
    doParsimPacking(b,this->xBit);
    doParsimPacking(b,this->vBit);
    doParsimPacking(b,this->eBit);
    doParsimPacking(b,this->bBit);
    doParsimPacking(b,this->ospfOptions);
    b->pack(routers_arraysize);
    doParsimArrayPacking(b,this->routers,routers_arraysize);
}

void Ospfv3RouterLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->ntBit);
    doParsimUnpacking(b,this->xBit);
    doParsimUnpacking(b,this->vBit);
    doParsimUnpacking(b,this->eBit);
    doParsimUnpacking(b,this->bBit);
    doParsimUnpacking(b,this->ospfOptions);
    delete [] this->routers;
    b->unpack(routers_arraysize);
    if (routers_arraysize == 0) {
        this->routers = nullptr;
    } else {
        this->routers = new Ospfv3RouterLsaBody[routers_arraysize];
        doParsimArrayUnpacking(b,this->routers,routers_arraysize);
    }
}

bool Ospfv3RouterLsa::getNtBit() const
{
    return this->ntBit;
}

void Ospfv3RouterLsa::setNtBit(bool ntBit)
{
    this->ntBit = ntBit;
}

bool Ospfv3RouterLsa::getXBit() const
{
    return this->xBit;
}

void Ospfv3RouterLsa::setXBit(bool xBit)
{
    this->xBit = xBit;
}

bool Ospfv3RouterLsa::getVBit() const
{
    return this->vBit;
}

void Ospfv3RouterLsa::setVBit(bool vBit)
{
    this->vBit = vBit;
}

bool Ospfv3RouterLsa::getEBit() const
{
    return this->eBit;
}

void Ospfv3RouterLsa::setEBit(bool eBit)
{
    this->eBit = eBit;
}

bool Ospfv3RouterLsa::getBBit() const
{
    return this->bBit;
}

void Ospfv3RouterLsa::setBBit(bool bBit)
{
    this->bBit = bBit;
}

const Ospfv3Options& Ospfv3RouterLsa::getOspfOptions() const
{
    return this->ospfOptions;
}

void Ospfv3RouterLsa::setOspfOptions(const Ospfv3Options& ospfOptions)
{
    this->ospfOptions = ospfOptions;
}

size_t Ospfv3RouterLsa::getRoutersArraySize() const
{
    return routers_arraysize;
}

const Ospfv3RouterLsaBody& Ospfv3RouterLsa::getRouters(size_t k) const
{
    if (k >= routers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routers_arraysize, (unsigned long)k);
    return this->routers[k];
}

void Ospfv3RouterLsa::setRoutersArraySize(size_t newSize)
{
    Ospfv3RouterLsaBody *routers2 = (newSize==0) ? nullptr : new Ospfv3RouterLsaBody[newSize];
    size_t minSize = routers_arraysize < newSize ? routers_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        routers2[i] = this->routers[i];
    delete [] this->routers;
    this->routers = routers2;
    routers_arraysize = newSize;
}

void Ospfv3RouterLsa::setRouters(size_t k, const Ospfv3RouterLsaBody& routers)
{
    if (k >= routers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routers_arraysize, (unsigned long)k);
    this->routers[k] = routers;
}

void Ospfv3RouterLsa::insertRouters(size_t k, const Ospfv3RouterLsaBody& routers)
{
    if (k > routers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routers_arraysize, (unsigned long)k);
    size_t newSize = routers_arraysize + 1;
    Ospfv3RouterLsaBody *routers2 = new Ospfv3RouterLsaBody[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        routers2[i] = this->routers[i];
    routers2[k] = routers;
    for (i = k + 1; i < newSize; i++)
        routers2[i] = this->routers[i-1];
    delete [] this->routers;
    this->routers = routers2;
    routers_arraysize = newSize;
}

void Ospfv3RouterLsa::appendRouters(const Ospfv3RouterLsaBody& routers)
{
    insertRouters(routers_arraysize, routers);
}

void Ospfv3RouterLsa::eraseRouters(size_t k)
{
    if (k >= routers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)routers_arraysize, (unsigned long)k);
    size_t newSize = routers_arraysize - 1;
    Ospfv3RouterLsaBody *routers2 = (newSize == 0) ? nullptr : new Ospfv3RouterLsaBody[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        routers2[i] = this->routers[i];
    for (i = k; i < newSize; i++)
        routers2[i] = this->routers[i+1];
    delete [] this->routers;
    this->routers = routers2;
    routers_arraysize = newSize;
}

class Ospfv3RouterLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ntBit,
        FIELD_xBit,
        FIELD_vBit,
        FIELD_eBit,
        FIELD_bBit,
        FIELD_ospfOptions,
        FIELD_routers,
    };
  public:
    Ospfv3RouterLsaDescriptor();
    virtual ~Ospfv3RouterLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3RouterLsaDescriptor)

Ospfv3RouterLsaDescriptor::Ospfv3RouterLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3RouterLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3RouterLsaDescriptor::~Ospfv3RouterLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3RouterLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3RouterLsa *>(obj)!=nullptr;
}

const char **Ospfv3RouterLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3RouterLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3RouterLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int Ospfv3RouterLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ntBit
        FD_ISEDITABLE,    // FIELD_xBit
        FD_ISEDITABLE,    // FIELD_vBit
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_bBit
        FD_ISCOMPOUND,    // FIELD_ospfOptions
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_routers
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3RouterLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ntBit",
        "xBit",
        "vBit",
        "eBit",
        "bBit",
        "ospfOptions",
        "routers",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ospfv3RouterLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ntBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "xBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "vBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "bBit") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "ospfOptions") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "routers") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3RouterLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_ntBit
        "bool",    // FIELD_xBit
        "bool",    // FIELD_vBit
        "bool",    // FIELD_eBit
        "bool",    // FIELD_bBit
        "inet::ospfv3::Ospfv3Options",    // FIELD_ospfOptions
        "inet::ospfv3::Ospfv3RouterLsaBody",    // FIELD_routers
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3RouterLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3RouterLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3RouterLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routers: return pp->getRoutersArraySize();
        default: return 0;
    }
}

void Ospfv3RouterLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routers: pp->setRoutersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3RouterLsa'", field);
    }
}

const char *Ospfv3RouterLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3RouterLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ntBit: return bool2string(pp->getNtBit());
        case FIELD_xBit: return bool2string(pp->getXBit());
        case FIELD_vBit: return bool2string(pp->getVBit());
        case FIELD_eBit: return bool2string(pp->getEBit());
        case FIELD_bBit: return bool2string(pp->getBBit());
        case FIELD_ospfOptions: return "";
        case FIELD_routers: return "";
        default: return "";
    }
}

void Ospfv3RouterLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ntBit: pp->setNtBit(string2bool(value)); break;
        case FIELD_xBit: pp->setXBit(string2bool(value)); break;
        case FIELD_vBit: pp->setVBit(string2bool(value)); break;
        case FIELD_eBit: pp->setEBit(string2bool(value)); break;
        case FIELD_bBit: pp->setBBit(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsa'", field);
    }
}

omnetpp::cValue Ospfv3RouterLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ntBit: return pp->getNtBit();
        case FIELD_xBit: return pp->getXBit();
        case FIELD_vBit: return pp->getVBit();
        case FIELD_eBit: return pp->getEBit();
        case FIELD_bBit: return pp->getBBit();
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_routers: return omnetpp::toAnyPtr(&pp->getRouters(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3RouterLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3RouterLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ntBit: pp->setNtBit(value.boolValue()); break;
        case FIELD_xBit: pp->setXBit(value.boolValue()); break;
        case FIELD_vBit: pp->setVBit(value.boolValue()); break;
        case FIELD_eBit: pp->setEBit(value.boolValue()); break;
        case FIELD_bBit: pp->setBBit(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsa'", field);
    }
}

const char *Ospfv3RouterLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::opp_typename(typeid(Ospfv3Options));
        case FIELD_routers: return omnetpp::opp_typename(typeid(Ospfv3RouterLsaBody));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3RouterLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_routers: return omnetpp::toAnyPtr(&pp->getRouters(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3RouterLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3RouterLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3RouterLsa'", field);
    }
}

Register_Class(Ospfv3NetworkLsa)

Ospfv3NetworkLsa::Ospfv3NetworkLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3NetworkLsa::Ospfv3NetworkLsa(const Ospfv3NetworkLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3NetworkLsa::~Ospfv3NetworkLsa()
{
    delete [] this->attachedRouter;
}

Ospfv3NetworkLsa& Ospfv3NetworkLsa::operator=(const Ospfv3NetworkLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3NetworkLsa::copy(const Ospfv3NetworkLsa& other)
{
    this->ospfOptions = other.ospfOptions;
    delete [] this->attachedRouter;
    this->attachedRouter = (other.attachedRouter_arraysize==0) ? nullptr : new ::inet::Ipv4Address[other.attachedRouter_arraysize];
    attachedRouter_arraysize = other.attachedRouter_arraysize;
    for (size_t i = 0; i < attachedRouter_arraysize; i++) {
        this->attachedRouter[i] = other.attachedRouter[i];
    }
}

void Ospfv3NetworkLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->ospfOptions);
    b->pack(attachedRouter_arraysize);
    doParsimArrayPacking(b,this->attachedRouter,attachedRouter_arraysize);
}

void Ospfv3NetworkLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->ospfOptions);
    delete [] this->attachedRouter;
    b->unpack(attachedRouter_arraysize);
    if (attachedRouter_arraysize == 0) {
        this->attachedRouter = nullptr;
    } else {
        this->attachedRouter = new ::inet::Ipv4Address[attachedRouter_arraysize];
        doParsimArrayUnpacking(b,this->attachedRouter,attachedRouter_arraysize);
    }
}

const Ospfv3Options& Ospfv3NetworkLsa::getOspfOptions() const
{
    return this->ospfOptions;
}

void Ospfv3NetworkLsa::setOspfOptions(const Ospfv3Options& ospfOptions)
{
    this->ospfOptions = ospfOptions;
}

size_t Ospfv3NetworkLsa::getAttachedRouterArraySize() const
{
    return attachedRouter_arraysize;
}

const ::inet::Ipv4Address& Ospfv3NetworkLsa::getAttachedRouter(size_t k) const
{
    if (k >= attachedRouter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouter_arraysize, (unsigned long)k);
    return this->attachedRouter[k];
}

void Ospfv3NetworkLsa::setAttachedRouterArraySize(size_t newSize)
{
    ::inet::Ipv4Address *attachedRouter2 = (newSize==0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t minSize = attachedRouter_arraysize < newSize ? attachedRouter_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        attachedRouter2[i] = this->attachedRouter[i];
    delete [] this->attachedRouter;
    this->attachedRouter = attachedRouter2;
    attachedRouter_arraysize = newSize;
}

void Ospfv3NetworkLsa::setAttachedRouter(size_t k, const ::inet::Ipv4Address& attachedRouter)
{
    if (k >= attachedRouter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouter_arraysize, (unsigned long)k);
    this->attachedRouter[k] = attachedRouter;
}

void Ospfv3NetworkLsa::insertAttachedRouter(size_t k, const ::inet::Ipv4Address& attachedRouter)
{
    if (k > attachedRouter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouter_arraysize, (unsigned long)k);
    size_t newSize = attachedRouter_arraysize + 1;
    ::inet::Ipv4Address *attachedRouter2 = new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        attachedRouter2[i] = this->attachedRouter[i];
    attachedRouter2[k] = attachedRouter;
    for (i = k + 1; i < newSize; i++)
        attachedRouter2[i] = this->attachedRouter[i-1];
    delete [] this->attachedRouter;
    this->attachedRouter = attachedRouter2;
    attachedRouter_arraysize = newSize;
}

void Ospfv3NetworkLsa::appendAttachedRouter(const ::inet::Ipv4Address& attachedRouter)
{
    insertAttachedRouter(attachedRouter_arraysize, attachedRouter);
}

void Ospfv3NetworkLsa::eraseAttachedRouter(size_t k)
{
    if (k >= attachedRouter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouter_arraysize, (unsigned long)k);
    size_t newSize = attachedRouter_arraysize - 1;
    ::inet::Ipv4Address *attachedRouter2 = (newSize == 0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        attachedRouter2[i] = this->attachedRouter[i];
    for (i = k; i < newSize; i++)
        attachedRouter2[i] = this->attachedRouter[i+1];
    delete [] this->attachedRouter;
    this->attachedRouter = attachedRouter2;
    attachedRouter_arraysize = newSize;
}

class Ospfv3NetworkLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ospfOptions,
        FIELD_attachedRouter,
    };
  public:
    Ospfv3NetworkLsaDescriptor();
    virtual ~Ospfv3NetworkLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3NetworkLsaDescriptor)

Ospfv3NetworkLsaDescriptor::Ospfv3NetworkLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3NetworkLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3NetworkLsaDescriptor::~Ospfv3NetworkLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3NetworkLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3NetworkLsa *>(obj)!=nullptr;
}

const char **Ospfv3NetworkLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3NetworkLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3NetworkLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv3NetworkLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_ospfOptions
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_attachedRouter
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3NetworkLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ospfOptions",
        "attachedRouter",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv3NetworkLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ospfOptions") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "attachedRouter") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3NetworkLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv3::Ospfv3Options",    // FIELD_ospfOptions
        "inet::Ipv4Address",    // FIELD_attachedRouter
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3NetworkLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3NetworkLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3NetworkLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_attachedRouter: return pp->getAttachedRouterArraySize();
        default: return 0;
    }
}

void Ospfv3NetworkLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_attachedRouter: pp->setAttachedRouterArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3NetworkLsa'", field);
    }
}

const char *Ospfv3NetworkLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3NetworkLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return "";
        case FIELD_attachedRouter: return pp->getAttachedRouter(i).str();
        default: return "";
    }
}

void Ospfv3NetworkLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NetworkLsa'", field);
    }
}

omnetpp::cValue Ospfv3NetworkLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_attachedRouter: return omnetpp::toAnyPtr(&pp->getAttachedRouter(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3NetworkLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3NetworkLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NetworkLsa'", field);
    }
}

const char *Ospfv3NetworkLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::opp_typename(typeid(Ospfv3Options));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3NetworkLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_attachedRouter: return omnetpp::toAnyPtr(&pp->getAttachedRouter(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3NetworkLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv3NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NetworkLsa'", field);
    }
}

Register_Class(Ospfv3InterAreaPrefixLsa)

Ospfv3InterAreaPrefixLsa::Ospfv3InterAreaPrefixLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3InterAreaPrefixLsa::Ospfv3InterAreaPrefixLsa(const Ospfv3InterAreaPrefixLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3InterAreaPrefixLsa::~Ospfv3InterAreaPrefixLsa()
{
}

Ospfv3InterAreaPrefixLsa& Ospfv3InterAreaPrefixLsa::operator=(const Ospfv3InterAreaPrefixLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3InterAreaPrefixLsa::copy(const Ospfv3InterAreaPrefixLsa& other)
{
    this->reserved1 = other.reserved1;
    this->metric = other.metric;
    this->prefix = other.prefix;
}

void Ospfv3InterAreaPrefixLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->prefix);
}

void Ospfv3InterAreaPrefixLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->prefix);
}

uint8_t Ospfv3InterAreaPrefixLsa::getReserved1() const
{
    return this->reserved1;
}

void Ospfv3InterAreaPrefixLsa::setReserved1(uint8_t reserved1)
{
    this->reserved1 = reserved1;
}

uint32_t Ospfv3InterAreaPrefixLsa::getMetric() const
{
    return this->metric;
}

void Ospfv3InterAreaPrefixLsa::setMetric(uint32_t metric)
{
    this->metric = metric;
}

const Ospfv3LsaPrefix0& Ospfv3InterAreaPrefixLsa::getPrefix() const
{
    return this->prefix;
}

void Ospfv3InterAreaPrefixLsa::setPrefix(const Ospfv3LsaPrefix0& prefix)
{
    this->prefix = prefix;
}

class Ospfv3InterAreaPrefixLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_metric,
        FIELD_prefix,
    };
  public:
    Ospfv3InterAreaPrefixLsaDescriptor();
    virtual ~Ospfv3InterAreaPrefixLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3InterAreaPrefixLsaDescriptor)

Ospfv3InterAreaPrefixLsaDescriptor::Ospfv3InterAreaPrefixLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3InterAreaPrefixLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3InterAreaPrefixLsaDescriptor::~Ospfv3InterAreaPrefixLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3InterAreaPrefixLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3InterAreaPrefixLsa *>(obj)!=nullptr;
}

const char **Ospfv3InterAreaPrefixLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3InterAreaPrefixLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3InterAreaPrefixLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ospfv3InterAreaPrefixLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISCOMPOUND,    // FIELD_prefix
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3InterAreaPrefixLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "metric",
        "prefix",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ospfv3InterAreaPrefixLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "prefix") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3InterAreaPrefixLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_reserved1
        "uint32_t",    // FIELD_metric
        "inet::ospfv3::Ospfv3LsaPrefix0",    // FIELD_prefix
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3InterAreaPrefixLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3InterAreaPrefixLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3InterAreaPrefixLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3InterAreaPrefixLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3InterAreaPrefixLsa'", field);
    }
}

const char *Ospfv3InterAreaPrefixLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3InterAreaPrefixLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return ulong2string(pp->getReserved1());
        case FIELD_metric: return ulong2string(pp->getMetric());
        case FIELD_prefix: return "";
        default: return "";
    }
}

void Ospfv3InterAreaPrefixLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(string2ulong(value)); break;
        case FIELD_metric: pp->setMetric(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaPrefixLsa'", field);
    }
}

omnetpp::cValue Ospfv3InterAreaPrefixLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return (omnetpp::intval_t)(pp->getReserved1());
        case FIELD_metric: return (omnetpp::intval_t)(pp->getMetric());
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->getPrefix()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3InterAreaPrefixLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3InterAreaPrefixLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaPrefixLsa'", field);
    }
}

const char *Ospfv3InterAreaPrefixLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_prefix: return omnetpp::opp_typename(typeid(Ospfv3LsaPrefix0));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3InterAreaPrefixLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->getPrefix()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3InterAreaPrefixLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaPrefixLsa'", field);
    }
}

Register_Class(Ospfv3InterAreaRouterLsa)

Ospfv3InterAreaRouterLsa::Ospfv3InterAreaRouterLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3InterAreaRouterLsa::Ospfv3InterAreaRouterLsa(const Ospfv3InterAreaRouterLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3InterAreaRouterLsa::~Ospfv3InterAreaRouterLsa()
{
}

Ospfv3InterAreaRouterLsa& Ospfv3InterAreaRouterLsa::operator=(const Ospfv3InterAreaRouterLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3InterAreaRouterLsa::copy(const Ospfv3InterAreaRouterLsa& other)
{
    this->ospfOptions = other.ospfOptions;
    this->metric = other.metric;
    this->destinationRouter = other.destinationRouter;
}

void Ospfv3InterAreaRouterLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->ospfOptions);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->destinationRouter);
}

void Ospfv3InterAreaRouterLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->ospfOptions);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->destinationRouter);
}

const Ospfv3Options& Ospfv3InterAreaRouterLsa::getOspfOptions() const
{
    return this->ospfOptions;
}

void Ospfv3InterAreaRouterLsa::setOspfOptions(const Ospfv3Options& ospfOptions)
{
    this->ospfOptions = ospfOptions;
}

uint32_t Ospfv3InterAreaRouterLsa::getMetric() const
{
    return this->metric;
}

void Ospfv3InterAreaRouterLsa::setMetric(uint32_t metric)
{
    this->metric = metric;
}

uint32_t Ospfv3InterAreaRouterLsa::getDestinationRouter() const
{
    return this->destinationRouter;
}

void Ospfv3InterAreaRouterLsa::setDestinationRouter(uint32_t destinationRouter)
{
    this->destinationRouter = destinationRouter;
}

class Ospfv3InterAreaRouterLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ospfOptions,
        FIELD_metric,
        FIELD_destinationRouter,
    };
  public:
    Ospfv3InterAreaRouterLsaDescriptor();
    virtual ~Ospfv3InterAreaRouterLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3InterAreaRouterLsaDescriptor)

Ospfv3InterAreaRouterLsaDescriptor::Ospfv3InterAreaRouterLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3InterAreaRouterLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3InterAreaRouterLsaDescriptor::~Ospfv3InterAreaRouterLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3InterAreaRouterLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3InterAreaRouterLsa *>(obj)!=nullptr;
}

const char **Ospfv3InterAreaRouterLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3InterAreaRouterLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3InterAreaRouterLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ospfv3InterAreaRouterLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_ospfOptions
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_destinationRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3InterAreaRouterLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ospfOptions",
        "metric",
        "destinationRouter",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ospfv3InterAreaRouterLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ospfOptions") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "destinationRouter") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3InterAreaRouterLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv3::Ospfv3Options",    // FIELD_ospfOptions
        "uint32_t",    // FIELD_metric
        "uint32_t",    // FIELD_destinationRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3InterAreaRouterLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3InterAreaRouterLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3InterAreaRouterLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3InterAreaRouterLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3InterAreaRouterLsa'", field);
    }
}

const char *Ospfv3InterAreaRouterLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3InterAreaRouterLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return "";
        case FIELD_metric: return ulong2string(pp->getMetric());
        case FIELD_destinationRouter: return ulong2string(pp->getDestinationRouter());
        default: return "";
    }
}

void Ospfv3InterAreaRouterLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_metric: pp->setMetric(string2ulong(value)); break;
        case FIELD_destinationRouter: pp->setDestinationRouter(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaRouterLsa'", field);
    }
}

omnetpp::cValue Ospfv3InterAreaRouterLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_metric: return (omnetpp::intval_t)(pp->getMetric());
        case FIELD_destinationRouter: return (omnetpp::intval_t)(pp->getDestinationRouter());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3InterAreaRouterLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3InterAreaRouterLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_destinationRouter: pp->setDestinationRouter(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaRouterLsa'", field);
    }
}

const char *Ospfv3InterAreaRouterLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::opp_typename(typeid(Ospfv3Options));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3InterAreaRouterLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3InterAreaRouterLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3InterAreaRouterLsa *pp = omnetpp::fromAnyPtr<Ospfv3InterAreaRouterLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3InterAreaRouterLsa'", field);
    }
}

Register_Class(Ospfv3AsExternalLsa)

Ospfv3AsExternalLsa::Ospfv3AsExternalLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3AsExternalLsa::Ospfv3AsExternalLsa(const Ospfv3AsExternalLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3AsExternalLsa::~Ospfv3AsExternalLsa()
{
}

Ospfv3AsExternalLsa& Ospfv3AsExternalLsa::operator=(const Ospfv3AsExternalLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3AsExternalLsa::copy(const Ospfv3AsExternalLsa& other)
{
    this->eBit = other.eBit;
    this->fBit = other.fBit;
    this->tBit = other.tBit;
    this->metric = other.metric;
    this->referencedLSType = other.referencedLSType;
    this->forwardingAddress = other.forwardingAddress;
    this->externalRouteTag = other.externalRouteTag;
    this->referencedLSID = other.referencedLSID;
}

void Ospfv3AsExternalLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->eBit);
    doParsimPacking(b,this->fBit);
    doParsimPacking(b,this->tBit);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->referencedLSType);
    doParsimPacking(b,this->forwardingAddress);
    doParsimPacking(b,this->externalRouteTag);
    doParsimPacking(b,this->referencedLSID);
}

void Ospfv3AsExternalLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->eBit);
    doParsimUnpacking(b,this->fBit);
    doParsimUnpacking(b,this->tBit);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->referencedLSType);
    doParsimUnpacking(b,this->forwardingAddress);
    doParsimUnpacking(b,this->externalRouteTag);
    doParsimUnpacking(b,this->referencedLSID);
}

bool Ospfv3AsExternalLsa::getEBit() const
{
    return this->eBit;
}

void Ospfv3AsExternalLsa::setEBit(bool eBit)
{
    this->eBit = eBit;
}

bool Ospfv3AsExternalLsa::getFBit() const
{
    return this->fBit;
}

void Ospfv3AsExternalLsa::setFBit(bool fBit)
{
    this->fBit = fBit;
}

bool Ospfv3AsExternalLsa::getTBit() const
{
    return this->tBit;
}

void Ospfv3AsExternalLsa::setTBit(bool tBit)
{
    this->tBit = tBit;
}

uint32_t Ospfv3AsExternalLsa::getMetric() const
{
    return this->metric;
}

void Ospfv3AsExternalLsa::setMetric(uint32_t metric)
{
    this->metric = metric;
}

uint16_t Ospfv3AsExternalLsa::getReferencedLSType() const
{
    return this->referencedLSType;
}

void Ospfv3AsExternalLsa::setReferencedLSType(uint16_t referencedLSType)
{
    this->referencedLSType = referencedLSType;
}

const ::inet::Ipv6Address& Ospfv3AsExternalLsa::getForwardingAddress() const
{
    return this->forwardingAddress;
}

void Ospfv3AsExternalLsa::setForwardingAddress(const ::inet::Ipv6Address& forwardingAddress)
{
    this->forwardingAddress = forwardingAddress;
}

uint32_t Ospfv3AsExternalLsa::getExternalRouteTag() const
{
    return this->externalRouteTag;
}

void Ospfv3AsExternalLsa::setExternalRouteTag(uint32_t externalRouteTag)
{
    this->externalRouteTag = externalRouteTag;
}

uint32_t Ospfv3AsExternalLsa::getReferencedLSID() const
{
    return this->referencedLSID;
}

void Ospfv3AsExternalLsa::setReferencedLSID(uint32_t referencedLSID)
{
    this->referencedLSID = referencedLSID;
}

class Ospfv3AsExternalLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_eBit,
        FIELD_fBit,
        FIELD_tBit,
        FIELD_metric,
        FIELD_referencedLSType,
        FIELD_forwardingAddress,
        FIELD_externalRouteTag,
        FIELD_referencedLSID,
    };
  public:
    Ospfv3AsExternalLsaDescriptor();
    virtual ~Ospfv3AsExternalLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3AsExternalLsaDescriptor)

Ospfv3AsExternalLsaDescriptor::Ospfv3AsExternalLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3AsExternalLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3AsExternalLsaDescriptor::~Ospfv3AsExternalLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3AsExternalLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3AsExternalLsa *>(obj)!=nullptr;
}

const char **Ospfv3AsExternalLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3AsExternalLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3AsExternalLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ospfv3AsExternalLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_fBit
        FD_ISEDITABLE,    // FIELD_tBit
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_referencedLSType
        0,    // FIELD_forwardingAddress
        FD_ISEDITABLE,    // FIELD_externalRouteTag
        FD_ISEDITABLE,    // FIELD_referencedLSID
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3AsExternalLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "eBit",
        "fBit",
        "tBit",
        "metric",
        "referencedLSType",
        "forwardingAddress",
        "externalRouteTag",
        "referencedLSID",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ospfv3AsExternalLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "referencedLSType") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "forwardingAddress") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "externalRouteTag") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "referencedLSID") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3AsExternalLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_eBit
        "bool",    // FIELD_fBit
        "bool",    // FIELD_tBit
        "uint32_t",    // FIELD_metric
        "uint16_t",    // FIELD_referencedLSType
        "inet::Ipv6Address",    // FIELD_forwardingAddress
        "uint32_t",    // FIELD_externalRouteTag
        "uint32_t",    // FIELD_referencedLSID
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3AsExternalLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3AsExternalLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3AsExternalLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3AsExternalLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3AsExternalLsa'", field);
    }
}

const char *Ospfv3AsExternalLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3AsExternalLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return bool2string(pp->getEBit());
        case FIELD_fBit: return bool2string(pp->getFBit());
        case FIELD_tBit: return bool2string(pp->getTBit());
        case FIELD_metric: return ulong2string(pp->getMetric());
        case FIELD_referencedLSType: return ulong2string(pp->getReferencedLSType());
        case FIELD_forwardingAddress: return pp->getForwardingAddress().str();
        case FIELD_externalRouteTag: return ulong2string(pp->getExternalRouteTag());
        case FIELD_referencedLSID: return ulong2string(pp->getReferencedLSID());
        default: return "";
    }
}

void Ospfv3AsExternalLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(string2bool(value)); break;
        case FIELD_fBit: pp->setFBit(string2bool(value)); break;
        case FIELD_tBit: pp->setTBit(string2bool(value)); break;
        case FIELD_metric: pp->setMetric(string2ulong(value)); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(string2ulong(value)); break;
        case FIELD_externalRouteTag: pp->setExternalRouteTag(string2ulong(value)); break;
        case FIELD_referencedLSID: pp->setReferencedLSID(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3AsExternalLsa'", field);
    }
}

omnetpp::cValue Ospfv3AsExternalLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return pp->getEBit();
        case FIELD_fBit: return pp->getFBit();
        case FIELD_tBit: return pp->getTBit();
        case FIELD_metric: return (omnetpp::intval_t)(pp->getMetric());
        case FIELD_referencedLSType: return (omnetpp::intval_t)(pp->getReferencedLSType());
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->getForwardingAddress()); break;
        case FIELD_externalRouteTag: return (omnetpp::intval_t)(pp->getExternalRouteTag());
        case FIELD_referencedLSID: return (omnetpp::intval_t)(pp->getReferencedLSID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3AsExternalLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3AsExternalLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(value.boolValue()); break;
        case FIELD_fBit: pp->setFBit(value.boolValue()); break;
        case FIELD_tBit: pp->setTBit(value.boolValue()); break;
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_externalRouteTag: pp->setExternalRouteTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_referencedLSID: pp->setReferencedLSID(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3AsExternalLsa'", field);
    }
}

const char *Ospfv3AsExternalLsaDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3AsExternalLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->getForwardingAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3AsExternalLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv3AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3AsExternalLsa'", field);
    }
}

Register_Class(Ospfv3NssaLsa)

Ospfv3NssaLsa::Ospfv3NssaLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3NssaLsa::Ospfv3NssaLsa(const Ospfv3NssaLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3NssaLsa::~Ospfv3NssaLsa()
{
}

Ospfv3NssaLsa& Ospfv3NssaLsa::operator=(const Ospfv3NssaLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3NssaLsa::copy(const Ospfv3NssaLsa& other)
{
    this->eBit = other.eBit;
    this->fBit = other.fBit;
    this->tBit = other.tBit;
    this->metric = other.metric;
    this->prefOptions = other.prefOptions;
    this->referencedLSType = other.referencedLSType;
    this->forwardingAddress = other.forwardingAddress;
    this->externalRouteTag = other.externalRouteTag;
    this->referencedLSID = other.referencedLSID;
}

void Ospfv3NssaLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->eBit);
    doParsimPacking(b,this->fBit);
    doParsimPacking(b,this->tBit);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->prefOptions);
    doParsimPacking(b,this->referencedLSType);
    doParsimPacking(b,this->forwardingAddress);
    doParsimPacking(b,this->externalRouteTag);
    doParsimPacking(b,this->referencedLSID);
}

void Ospfv3NssaLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->eBit);
    doParsimUnpacking(b,this->fBit);
    doParsimUnpacking(b,this->tBit);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->prefOptions);
    doParsimUnpacking(b,this->referencedLSType);
    doParsimUnpacking(b,this->forwardingAddress);
    doParsimUnpacking(b,this->externalRouteTag);
    doParsimUnpacking(b,this->referencedLSID);
}

bool Ospfv3NssaLsa::getEBit() const
{
    return this->eBit;
}

void Ospfv3NssaLsa::setEBit(bool eBit)
{
    this->eBit = eBit;
}

bool Ospfv3NssaLsa::getFBit() const
{
    return this->fBit;
}

void Ospfv3NssaLsa::setFBit(bool fBit)
{
    this->fBit = fBit;
}

bool Ospfv3NssaLsa::getTBit() const
{
    return this->tBit;
}

void Ospfv3NssaLsa::setTBit(bool tBit)
{
    this->tBit = tBit;
}

uint32_t Ospfv3NssaLsa::getMetric() const
{
    return this->metric;
}

void Ospfv3NssaLsa::setMetric(uint32_t metric)
{
    this->metric = metric;
}

const Ospfv3LsaPrefixMetric& Ospfv3NssaLsa::getPrefOptions() const
{
    return this->prefOptions;
}

void Ospfv3NssaLsa::setPrefOptions(const Ospfv3LsaPrefixMetric& prefOptions)
{
    this->prefOptions = prefOptions;
}

uint16_t Ospfv3NssaLsa::getReferencedLSType() const
{
    return this->referencedLSType;
}

void Ospfv3NssaLsa::setReferencedLSType(uint16_t referencedLSType)
{
    this->referencedLSType = referencedLSType;
}

const ::inet::Ipv6Address& Ospfv3NssaLsa::getForwardingAddress() const
{
    return this->forwardingAddress;
}

void Ospfv3NssaLsa::setForwardingAddress(const ::inet::Ipv6Address& forwardingAddress)
{
    this->forwardingAddress = forwardingAddress;
}

uint32_t Ospfv3NssaLsa::getExternalRouteTag() const
{
    return this->externalRouteTag;
}

void Ospfv3NssaLsa::setExternalRouteTag(uint32_t externalRouteTag)
{
    this->externalRouteTag = externalRouteTag;
}

uint32_t Ospfv3NssaLsa::getReferencedLSID() const
{
    return this->referencedLSID;
}

void Ospfv3NssaLsa::setReferencedLSID(uint32_t referencedLSID)
{
    this->referencedLSID = referencedLSID;
}

class Ospfv3NssaLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_eBit,
        FIELD_fBit,
        FIELD_tBit,
        FIELD_metric,
        FIELD_prefOptions,
        FIELD_referencedLSType,
        FIELD_forwardingAddress,
        FIELD_externalRouteTag,
        FIELD_referencedLSID,
    };
  public:
    Ospfv3NssaLsaDescriptor();
    virtual ~Ospfv3NssaLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3NssaLsaDescriptor)

Ospfv3NssaLsaDescriptor::Ospfv3NssaLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3NssaLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3NssaLsaDescriptor::~Ospfv3NssaLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3NssaLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3NssaLsa *>(obj)!=nullptr;
}

const char **Ospfv3NssaLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3NssaLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3NssaLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ospfv3NssaLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_fBit
        FD_ISEDITABLE,    // FIELD_tBit
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISCOMPOUND,    // FIELD_prefOptions
        FD_ISEDITABLE,    // FIELD_referencedLSType
        0,    // FIELD_forwardingAddress
        FD_ISEDITABLE,    // FIELD_externalRouteTag
        FD_ISEDITABLE,    // FIELD_referencedLSID
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3NssaLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "eBit",
        "fBit",
        "tBit",
        "metric",
        "prefOptions",
        "referencedLSType",
        "forwardingAddress",
        "externalRouteTag",
        "referencedLSID",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ospfv3NssaLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "prefOptions") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "referencedLSType") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "forwardingAddress") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "externalRouteTag") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "referencedLSID") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3NssaLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_eBit
        "bool",    // FIELD_fBit
        "bool",    // FIELD_tBit
        "uint32_t",    // FIELD_metric
        "inet::ospfv3::Ospfv3LsaPrefixMetric",    // FIELD_prefOptions
        "uint16_t",    // FIELD_referencedLSType
        "inet::Ipv6Address",    // FIELD_forwardingAddress
        "uint32_t",    // FIELD_externalRouteTag
        "uint32_t",    // FIELD_referencedLSID
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3NssaLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3NssaLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3NssaLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3NssaLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3NssaLsa'", field);
    }
}

const char *Ospfv3NssaLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3NssaLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return bool2string(pp->getEBit());
        case FIELD_fBit: return bool2string(pp->getFBit());
        case FIELD_tBit: return bool2string(pp->getTBit());
        case FIELD_metric: return ulong2string(pp->getMetric());
        case FIELD_prefOptions: return "";
        case FIELD_referencedLSType: return ulong2string(pp->getReferencedLSType());
        case FIELD_forwardingAddress: return pp->getForwardingAddress().str();
        case FIELD_externalRouteTag: return ulong2string(pp->getExternalRouteTag());
        case FIELD_referencedLSID: return ulong2string(pp->getReferencedLSID());
        default: return "";
    }
}

void Ospfv3NssaLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(string2bool(value)); break;
        case FIELD_fBit: pp->setFBit(string2bool(value)); break;
        case FIELD_tBit: pp->setTBit(string2bool(value)); break;
        case FIELD_metric: pp->setMetric(string2ulong(value)); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(string2ulong(value)); break;
        case FIELD_externalRouteTag: pp->setExternalRouteTag(string2ulong(value)); break;
        case FIELD_referencedLSID: pp->setReferencedLSID(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NssaLsa'", field);
    }
}

omnetpp::cValue Ospfv3NssaLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return pp->getEBit();
        case FIELD_fBit: return pp->getFBit();
        case FIELD_tBit: return pp->getTBit();
        case FIELD_metric: return (omnetpp::intval_t)(pp->getMetric());
        case FIELD_prefOptions: return omnetpp::toAnyPtr(&pp->getPrefOptions()); break;
        case FIELD_referencedLSType: return (omnetpp::intval_t)(pp->getReferencedLSType());
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->getForwardingAddress()); break;
        case FIELD_externalRouteTag: return (omnetpp::intval_t)(pp->getExternalRouteTag());
        case FIELD_referencedLSID: return (omnetpp::intval_t)(pp->getReferencedLSID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3NssaLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3NssaLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(value.boolValue()); break;
        case FIELD_fBit: pp->setFBit(value.boolValue()); break;
        case FIELD_tBit: pp->setTBit(value.boolValue()); break;
        case FIELD_metric: pp->setMetric(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_externalRouteTag: pp->setExternalRouteTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_referencedLSID: pp->setReferencedLSID(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NssaLsa'", field);
    }
}

const char *Ospfv3NssaLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_prefOptions: return omnetpp::opp_typename(typeid(Ospfv3LsaPrefixMetric));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3NssaLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefOptions: return omnetpp::toAnyPtr(&pp->getPrefOptions()); break;
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->getForwardingAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3NssaLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3NssaLsa *pp = omnetpp::fromAnyPtr<Ospfv3NssaLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3NssaLsa'", field);
    }
}

Register_Class(Ospfv3LinkLsa)

Ospfv3LinkLsa::Ospfv3LinkLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3LinkLsa::Ospfv3LinkLsa(const Ospfv3LinkLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3LinkLsa::~Ospfv3LinkLsa()
{
    delete [] this->prefixes;
}

Ospfv3LinkLsa& Ospfv3LinkLsa::operator=(const Ospfv3LinkLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3LinkLsa::copy(const Ospfv3LinkLsa& other)
{
    this->routerPriority = other.routerPriority;
    this->ospfOptions = other.ospfOptions;
    this->linkLocalInterfaceAdd = other.linkLocalInterfaceAdd;
    this->numPrefixes = other.numPrefixes;
    delete [] this->prefixes;
    this->prefixes = (other.prefixes_arraysize==0) ? nullptr : new Ospfv3LsaPrefix0[other.prefixes_arraysize];
    prefixes_arraysize = other.prefixes_arraysize;
    for (size_t i = 0; i < prefixes_arraysize; i++) {
        this->prefixes[i] = other.prefixes[i];
    }
}

void Ospfv3LinkLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->routerPriority);
    doParsimPacking(b,this->ospfOptions);
    doParsimPacking(b,this->linkLocalInterfaceAdd);
    doParsimPacking(b,this->numPrefixes);
    b->pack(prefixes_arraysize);
    doParsimArrayPacking(b,this->prefixes,prefixes_arraysize);
}

void Ospfv3LinkLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->routerPriority);
    doParsimUnpacking(b,this->ospfOptions);
    doParsimUnpacking(b,this->linkLocalInterfaceAdd);
    doParsimUnpacking(b,this->numPrefixes);
    delete [] this->prefixes;
    b->unpack(prefixes_arraysize);
    if (prefixes_arraysize == 0) {
        this->prefixes = nullptr;
    } else {
        this->prefixes = new Ospfv3LsaPrefix0[prefixes_arraysize];
        doParsimArrayUnpacking(b,this->prefixes,prefixes_arraysize);
    }
}

uint8_t Ospfv3LinkLsa::getRouterPriority() const
{
    return this->routerPriority;
}

void Ospfv3LinkLsa::setRouterPriority(uint8_t routerPriority)
{
    this->routerPriority = routerPriority;
}

const Ospfv3Options& Ospfv3LinkLsa::getOspfOptions() const
{
    return this->ospfOptions;
}

void Ospfv3LinkLsa::setOspfOptions(const Ospfv3Options& ospfOptions)
{
    this->ospfOptions = ospfOptions;
}

const ::inet::L3Address& Ospfv3LinkLsa::getLinkLocalInterfaceAdd() const
{
    return this->linkLocalInterfaceAdd;
}

void Ospfv3LinkLsa::setLinkLocalInterfaceAdd(const ::inet::L3Address& linkLocalInterfaceAdd)
{
    this->linkLocalInterfaceAdd = linkLocalInterfaceAdd;
}

uint32_t Ospfv3LinkLsa::getNumPrefixes() const
{
    return this->numPrefixes;
}

void Ospfv3LinkLsa::setNumPrefixes(uint32_t numPrefixes)
{
    this->numPrefixes = numPrefixes;
}

size_t Ospfv3LinkLsa::getPrefixesArraySize() const
{
    return prefixes_arraysize;
}

const Ospfv3LsaPrefix0& Ospfv3LinkLsa::getPrefixes(size_t k) const
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    return this->prefixes[k];
}

void Ospfv3LinkLsa::setPrefixesArraySize(size_t newSize)
{
    Ospfv3LsaPrefix0 *prefixes2 = (newSize==0) ? nullptr : new Ospfv3LsaPrefix0[newSize];
    size_t minSize = prefixes_arraysize < newSize ? prefixes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        prefixes2[i] = this->prefixes[i];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

void Ospfv3LinkLsa::setPrefixes(size_t k, const Ospfv3LsaPrefix0& prefixes)
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    this->prefixes[k] = prefixes;
}

void Ospfv3LinkLsa::insertPrefixes(size_t k, const Ospfv3LsaPrefix0& prefixes)
{
    if (k > prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    size_t newSize = prefixes_arraysize + 1;
    Ospfv3LsaPrefix0 *prefixes2 = new Ospfv3LsaPrefix0[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixes2[i] = this->prefixes[i];
    prefixes2[k] = prefixes;
    for (i = k + 1; i < newSize; i++)
        prefixes2[i] = this->prefixes[i-1];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

void Ospfv3LinkLsa::appendPrefixes(const Ospfv3LsaPrefix0& prefixes)
{
    insertPrefixes(prefixes_arraysize, prefixes);
}

void Ospfv3LinkLsa::erasePrefixes(size_t k)
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    size_t newSize = prefixes_arraysize - 1;
    Ospfv3LsaPrefix0 *prefixes2 = (newSize == 0) ? nullptr : new Ospfv3LsaPrefix0[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixes2[i] = this->prefixes[i];
    for (i = k; i < newSize; i++)
        prefixes2[i] = this->prefixes[i+1];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

class Ospfv3LinkLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_routerPriority,
        FIELD_ospfOptions,
        FIELD_linkLocalInterfaceAdd,
        FIELD_numPrefixes,
        FIELD_prefixes,
    };
  public:
    Ospfv3LinkLsaDescriptor();
    virtual ~Ospfv3LinkLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3LinkLsaDescriptor)

Ospfv3LinkLsaDescriptor::Ospfv3LinkLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LinkLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3LinkLsaDescriptor::~Ospfv3LinkLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LinkLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LinkLsa *>(obj)!=nullptr;
}

const char **Ospfv3LinkLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LinkLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LinkLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ospfv3LinkLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routerPriority
        FD_ISCOMPOUND,    // FIELD_ospfOptions
        0,    // FIELD_linkLocalInterfaceAdd
        FD_ISEDITABLE,    // FIELD_numPrefixes
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_prefixes
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LinkLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerPriority",
        "ospfOptions",
        "linkLocalInterfaceAdd",
        "numPrefixes",
        "prefixes",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ospfv3LinkLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "routerPriority") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ospfOptions") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "linkLocalInterfaceAdd") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "numPrefixes") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "prefixes") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LinkLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_routerPriority
        "inet::ospfv3::Ospfv3Options",    // FIELD_ospfOptions
        "inet::L3Address",    // FIELD_linkLocalInterfaceAdd
        "uint32_t",    // FIELD_numPrefixes
        "inet::ospfv3::Ospfv3LsaPrefix0",    // FIELD_prefixes
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LinkLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LinkLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LinkLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefixes: return pp->getPrefixesArraySize();
        default: return 0;
    }
}

void Ospfv3LinkLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefixes: pp->setPrefixesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LinkLsa'", field);
    }
}

const char *Ospfv3LinkLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LinkLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routerPriority: return ulong2string(pp->getRouterPriority());
        case FIELD_ospfOptions: return "";
        case FIELD_linkLocalInterfaceAdd: return pp->getLinkLocalInterfaceAdd().str();
        case FIELD_numPrefixes: return ulong2string(pp->getNumPrefixes());
        case FIELD_prefixes: return "";
        default: return "";
    }
}

void Ospfv3LinkLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routerPriority: pp->setRouterPriority(string2ulong(value)); break;
        case FIELD_numPrefixes: pp->setNumPrefixes(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkLsa'", field);
    }
}

omnetpp::cValue Ospfv3LinkLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routerPriority: return (omnetpp::intval_t)(pp->getRouterPriority());
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_linkLocalInterfaceAdd: return omnetpp::toAnyPtr(&pp->getLinkLocalInterfaceAdd()); break;
        case FIELD_numPrefixes: return (omnetpp::intval_t)(pp->getNumPrefixes());
        case FIELD_prefixes: return omnetpp::toAnyPtr(&pp->getPrefixes(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LinkLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LinkLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routerPriority: pp->setRouterPriority(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_numPrefixes: pp->setNumPrefixes(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkLsa'", field);
    }
}

const char *Ospfv3LinkLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::opp_typename(typeid(Ospfv3Options));
        case FIELD_prefixes: return omnetpp::opp_typename(typeid(Ospfv3LsaPrefix0));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3LinkLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_ospfOptions: return omnetpp::toAnyPtr(&pp->getOspfOptions()); break;
        case FIELD_linkLocalInterfaceAdd: return omnetpp::toAnyPtr(&pp->getLinkLocalInterfaceAdd()); break;
        case FIELD_prefixes: return omnetpp::toAnyPtr(&pp->getPrefixes(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LinkLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkLsa *pp = omnetpp::fromAnyPtr<Ospfv3LinkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkLsa'", field);
    }
}

Register_Class(Ospfv3IntraAreaPrefixLsa)

Ospfv3IntraAreaPrefixLsa::Ospfv3IntraAreaPrefixLsa() : ::inet::ospfv3::Ospfv3Lsa()
{
}

Ospfv3IntraAreaPrefixLsa::Ospfv3IntraAreaPrefixLsa(const Ospfv3IntraAreaPrefixLsa& other) : ::inet::ospfv3::Ospfv3Lsa(other)
{
    copy(other);
}

Ospfv3IntraAreaPrefixLsa::~Ospfv3IntraAreaPrefixLsa()
{
    delete [] this->prefixes;
}

Ospfv3IntraAreaPrefixLsa& Ospfv3IntraAreaPrefixLsa::operator=(const Ospfv3IntraAreaPrefixLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3IntraAreaPrefixLsa::copy(const Ospfv3IntraAreaPrefixLsa& other)
{
    this->numPrefixes = other.numPrefixes;
    this->referencedLSType = other.referencedLSType;
    this->referencedLSID = other.referencedLSID;
    this->referencedAdvRtr = other.referencedAdvRtr;
    delete [] this->prefixes;
    this->prefixes = (other.prefixes_arraysize==0) ? nullptr : new Ospfv3LsaPrefixMetric[other.prefixes_arraysize];
    prefixes_arraysize = other.prefixes_arraysize;
    for (size_t i = 0; i < prefixes_arraysize; i++) {
        this->prefixes[i] = other.prefixes[i];
    }
}

void Ospfv3IntraAreaPrefixLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Lsa::parsimPack(b);
    doParsimPacking(b,this->numPrefixes);
    doParsimPacking(b,this->referencedLSType);
    doParsimPacking(b,this->referencedLSID);
    doParsimPacking(b,this->referencedAdvRtr);
    b->pack(prefixes_arraysize);
    doParsimArrayPacking(b,this->prefixes,prefixes_arraysize);
}

void Ospfv3IntraAreaPrefixLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->numPrefixes);
    doParsimUnpacking(b,this->referencedLSType);
    doParsimUnpacking(b,this->referencedLSID);
    doParsimUnpacking(b,this->referencedAdvRtr);
    delete [] this->prefixes;
    b->unpack(prefixes_arraysize);
    if (prefixes_arraysize == 0) {
        this->prefixes = nullptr;
    } else {
        this->prefixes = new Ospfv3LsaPrefixMetric[prefixes_arraysize];
        doParsimArrayUnpacking(b,this->prefixes,prefixes_arraysize);
    }
}

unsigned short Ospfv3IntraAreaPrefixLsa::getNumPrefixes() const
{
    return this->numPrefixes;
}

void Ospfv3IntraAreaPrefixLsa::setNumPrefixes(unsigned short numPrefixes)
{
    this->numPrefixes = numPrefixes;
}

unsigned short Ospfv3IntraAreaPrefixLsa::getReferencedLSType() const
{
    return this->referencedLSType;
}

void Ospfv3IntraAreaPrefixLsa::setReferencedLSType(unsigned short referencedLSType)
{
    this->referencedLSType = referencedLSType;
}

const ::inet::Ipv4Address& Ospfv3IntraAreaPrefixLsa::getReferencedLSID() const
{
    return this->referencedLSID;
}

void Ospfv3IntraAreaPrefixLsa::setReferencedLSID(const ::inet::Ipv4Address& referencedLSID)
{
    this->referencedLSID = referencedLSID;
}

const ::inet::Ipv4Address& Ospfv3IntraAreaPrefixLsa::getReferencedAdvRtr() const
{
    return this->referencedAdvRtr;
}

void Ospfv3IntraAreaPrefixLsa::setReferencedAdvRtr(const ::inet::Ipv4Address& referencedAdvRtr)
{
    this->referencedAdvRtr = referencedAdvRtr;
}

size_t Ospfv3IntraAreaPrefixLsa::getPrefixesArraySize() const
{
    return prefixes_arraysize;
}

const Ospfv3LsaPrefixMetric& Ospfv3IntraAreaPrefixLsa::getPrefixes(size_t k) const
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    return this->prefixes[k];
}

void Ospfv3IntraAreaPrefixLsa::setPrefixesArraySize(size_t newSize)
{
    Ospfv3LsaPrefixMetric *prefixes2 = (newSize==0) ? nullptr : new Ospfv3LsaPrefixMetric[newSize];
    size_t minSize = prefixes_arraysize < newSize ? prefixes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        prefixes2[i] = this->prefixes[i];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

void Ospfv3IntraAreaPrefixLsa::setPrefixes(size_t k, const Ospfv3LsaPrefixMetric& prefixes)
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    this->prefixes[k] = prefixes;
}

void Ospfv3IntraAreaPrefixLsa::insertPrefixes(size_t k, const Ospfv3LsaPrefixMetric& prefixes)
{
    if (k > prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    size_t newSize = prefixes_arraysize + 1;
    Ospfv3LsaPrefixMetric *prefixes2 = new Ospfv3LsaPrefixMetric[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixes2[i] = this->prefixes[i];
    prefixes2[k] = prefixes;
    for (i = k + 1; i < newSize; i++)
        prefixes2[i] = this->prefixes[i-1];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

void Ospfv3IntraAreaPrefixLsa::appendPrefixes(const Ospfv3LsaPrefixMetric& prefixes)
{
    insertPrefixes(prefixes_arraysize, prefixes);
}

void Ospfv3IntraAreaPrefixLsa::erasePrefixes(size_t k)
{
    if (k >= prefixes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)prefixes_arraysize, (unsigned long)k);
    size_t newSize = prefixes_arraysize - 1;
    Ospfv3LsaPrefixMetric *prefixes2 = (newSize == 0) ? nullptr : new Ospfv3LsaPrefixMetric[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixes2[i] = this->prefixes[i];
    for (i = k; i < newSize; i++)
        prefixes2[i] = this->prefixes[i+1];
    delete [] this->prefixes;
    this->prefixes = prefixes2;
    prefixes_arraysize = newSize;
}

class Ospfv3IntraAreaPrefixLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_numPrefixes,
        FIELD_referencedLSType,
        FIELD_referencedLSID,
        FIELD_referencedAdvRtr,
        FIELD_prefixes,
    };
  public:
    Ospfv3IntraAreaPrefixLsaDescriptor();
    virtual ~Ospfv3IntraAreaPrefixLsaDescriptor();

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

Register_ClassDescriptor(Ospfv3IntraAreaPrefixLsaDescriptor)

Ospfv3IntraAreaPrefixLsaDescriptor::Ospfv3IntraAreaPrefixLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3IntraAreaPrefixLsa)), "inet::ospfv3::Ospfv3Lsa")
{
    propertyNames = nullptr;
}

Ospfv3IntraAreaPrefixLsaDescriptor::~Ospfv3IntraAreaPrefixLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3IntraAreaPrefixLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3IntraAreaPrefixLsa *>(obj)!=nullptr;
}

const char **Ospfv3IntraAreaPrefixLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3IntraAreaPrefixLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ospfv3IntraAreaPrefixLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_numPrefixes
        FD_ISEDITABLE,    // FIELD_referencedLSType
        0,    // FIELD_referencedLSID
        0,    // FIELD_referencedAdvRtr
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_prefixes
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numPrefixes",
        "referencedLSType",
        "referencedLSID",
        "referencedAdvRtr",
        "prefixes",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ospfv3IntraAreaPrefixLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "numPrefixes") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "referencedLSType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "referencedLSID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "referencedAdvRtr") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "prefixes") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_numPrefixes
        "unsigned short",    // FIELD_referencedLSType
        "inet::Ipv4Address",    // FIELD_referencedLSID
        "inet::Ipv4Address",    // FIELD_referencedAdvRtr
        "inet::ospfv3::Ospfv3LsaPrefixMetric",    // FIELD_prefixes
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3IntraAreaPrefixLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3IntraAreaPrefixLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefixes: return pp->getPrefixesArraySize();
        default: return 0;
    }
}

void Ospfv3IntraAreaPrefixLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_prefixes: pp->setPrefixesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3IntraAreaPrefixLsa'", field);
    }
}

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3IntraAreaPrefixLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_numPrefixes: return ulong2string(pp->getNumPrefixes());
        case FIELD_referencedLSType: return ulong2string(pp->getReferencedLSType());
        case FIELD_referencedLSID: return pp->getReferencedLSID().str();
        case FIELD_referencedAdvRtr: return pp->getReferencedAdvRtr().str();
        case FIELD_prefixes: return "";
        default: return "";
    }
}

void Ospfv3IntraAreaPrefixLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_numPrefixes: pp->setNumPrefixes(string2ulong(value)); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3IntraAreaPrefixLsa'", field);
    }
}

omnetpp::cValue Ospfv3IntraAreaPrefixLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_numPrefixes: return (omnetpp::intval_t)(pp->getNumPrefixes());
        case FIELD_referencedLSType: return (omnetpp::intval_t)(pp->getReferencedLSType());
        case FIELD_referencedLSID: return omnetpp::toAnyPtr(&pp->getReferencedLSID()); break;
        case FIELD_referencedAdvRtr: return omnetpp::toAnyPtr(&pp->getReferencedAdvRtr()); break;
        case FIELD_prefixes: return omnetpp::toAnyPtr(&pp->getPrefixes(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3IntraAreaPrefixLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv3IntraAreaPrefixLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_numPrefixes: pp->setNumPrefixes(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_referencedLSType: pp->setReferencedLSType(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3IntraAreaPrefixLsa'", field);
    }
}

const char *Ospfv3IntraAreaPrefixLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_prefixes: return omnetpp::opp_typename(typeid(Ospfv3LsaPrefixMetric));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3IntraAreaPrefixLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        case FIELD_referencedLSID: return omnetpp::toAnyPtr(&pp->getReferencedLSID()); break;
        case FIELD_referencedAdvRtr: return omnetpp::toAnyPtr(&pp->getReferencedAdvRtr()); break;
        case FIELD_prefixes: return omnetpp::toAnyPtr(&pp->getPrefixes(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3IntraAreaPrefixLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3IntraAreaPrefixLsa *pp = omnetpp::fromAnyPtr<Ospfv3IntraAreaPrefixLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3IntraAreaPrefixLsa'", field);
    }
}

Ospfv3DdOptions::Ospfv3DdOptions()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3DdOptions& a)
{
    doParsimPacking(b,a.reserved);
    doParsimPacking(b,a.iBit);
    doParsimPacking(b,a.mBit);
    doParsimPacking(b,a.msBit);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3DdOptions& a)
{
    doParsimUnpacking(b,a.reserved);
    doParsimUnpacking(b,a.iBit);
    doParsimUnpacking(b,a.mBit);
    doParsimUnpacking(b,a.msBit);
}

class Ospfv3DdOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_iBit,
        FIELD_mBit,
        FIELD_msBit,
    };
  public:
    Ospfv3DdOptionsDescriptor();
    virtual ~Ospfv3DdOptionsDescriptor();

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

Register_ClassDescriptor(Ospfv3DdOptionsDescriptor)

Ospfv3DdOptionsDescriptor::Ospfv3DdOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3DdOptions)), "")
{
    propertyNames = nullptr;
}

Ospfv3DdOptionsDescriptor::~Ospfv3DdOptionsDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3DdOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3DdOptions *>(obj)!=nullptr;
}

const char **Ospfv3DdOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3DdOptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3DdOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ospfv3DdOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_iBit
        FD_ISEDITABLE,    // FIELD_mBit
        FD_ISEDITABLE,    // FIELD_msBit
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3DdOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "iBit",
        "mBit",
        "msBit",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ospfv3DdOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "iBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "mBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "msBit") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3DdOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "bool",    // FIELD_iBit
        "bool",    // FIELD_mBit
        "bool",    // FIELD_msBit
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3DdOptionsDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3DdOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3DdOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3DdOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3DdOptions'", field);
    }
}

const char *Ospfv3DdOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3DdOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->reserved);
        case FIELD_iBit: return bool2string(pp->iBit);
        case FIELD_mBit: return bool2string(pp->mBit);
        case FIELD_msBit: return bool2string(pp->msBit);
        default: return "";
    }
}

void Ospfv3DdOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = string2ulong(value); break;
        case FIELD_iBit: pp->iBit = string2bool(value); break;
        case FIELD_mBit: pp->mBit = string2bool(value); break;
        case FIELD_msBit: pp->msBit = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DdOptions'", field);
    }
}

omnetpp::cValue Ospfv3DdOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->reserved);
        case FIELD_iBit: return pp->iBit;
        case FIELD_mBit: return pp->mBit;
        case FIELD_msBit: return pp->msBit;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3DdOptions' as cValue -- field index out of range?", field);
    }
}

void Ospfv3DdOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->reserved = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        case FIELD_iBit: pp->iBit = value.boolValue(); break;
        case FIELD_mBit: pp->mBit = value.boolValue(); break;
        case FIELD_msBit: pp->msBit = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DdOptions'", field);
    }
}

const char *Ospfv3DdOptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3DdOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3DdOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DdOptions *pp = omnetpp::fromAnyPtr<Ospfv3DdOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DdOptions'", field);
    }
}

Register_Class(Ospfv3DatabaseDescriptionPacket)

Ospfv3DatabaseDescriptionPacket::Ospfv3DatabaseDescriptionPacket() : ::inet::ospfv3::Ospfv3Packet()
{
    this->setType(ospf::DATABASE_DESCRIPTION_PACKET);

}

Ospfv3DatabaseDescriptionPacket::Ospfv3DatabaseDescriptionPacket(const Ospfv3DatabaseDescriptionPacket& other) : ::inet::ospfv3::Ospfv3Packet(other)
{
    copy(other);
}

Ospfv3DatabaseDescriptionPacket::~Ospfv3DatabaseDescriptionPacket()
{
    delete [] this->lsaHeaders;
}

Ospfv3DatabaseDescriptionPacket& Ospfv3DatabaseDescriptionPacket::operator=(const Ospfv3DatabaseDescriptionPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3DatabaseDescriptionPacket::copy(const Ospfv3DatabaseDescriptionPacket& other)
{
    this->reserved1 = other.reserved1;
    this->options = other.options;
    this->interfaceMTU = other.interfaceMTU;
    this->ddOptions = other.ddOptions;
    this->sequenceNumber = other.sequenceNumber;
    delete [] this->lsaHeaders;
    this->lsaHeaders = (other.lsaHeaders_arraysize==0) ? nullptr : new Ospfv3LsaHeader[other.lsaHeaders_arraysize];
    lsaHeaders_arraysize = other.lsaHeaders_arraysize;
    for (size_t i = 0; i < lsaHeaders_arraysize; i++) {
        this->lsaHeaders[i] = other.lsaHeaders[i];
    }
}

void Ospfv3DatabaseDescriptionPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Packet::parsimPack(b);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->options);
    doParsimPacking(b,this->interfaceMTU);
    doParsimPacking(b,this->ddOptions);
    doParsimPacking(b,this->sequenceNumber);
    b->pack(lsaHeaders_arraysize);
    doParsimArrayPacking(b,this->lsaHeaders,lsaHeaders_arraysize);
}

void Ospfv3DatabaseDescriptionPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->options);
    doParsimUnpacking(b,this->interfaceMTU);
    doParsimUnpacking(b,this->ddOptions);
    doParsimUnpacking(b,this->sequenceNumber);
    delete [] this->lsaHeaders;
    b->unpack(lsaHeaders_arraysize);
    if (lsaHeaders_arraysize == 0) {
        this->lsaHeaders = nullptr;
    } else {
        this->lsaHeaders = new Ospfv3LsaHeader[lsaHeaders_arraysize];
        doParsimArrayUnpacking(b,this->lsaHeaders,lsaHeaders_arraysize);
    }
}

uint8_t Ospfv3DatabaseDescriptionPacket::getReserved1() const
{
    return this->reserved1;
}

void Ospfv3DatabaseDescriptionPacket::setReserved1(uint8_t reserved1)
{
    handleChange();
    this->reserved1 = reserved1;
}

const Ospfv3Options& Ospfv3DatabaseDescriptionPacket::getOptions() const
{
    return this->options;
}

void Ospfv3DatabaseDescriptionPacket::setOptions(const Ospfv3Options& options)
{
    handleChange();
    this->options = options;
}

uint16_t Ospfv3DatabaseDescriptionPacket::getInterfaceMTU() const
{
    return this->interfaceMTU;
}

void Ospfv3DatabaseDescriptionPacket::setInterfaceMTU(uint16_t interfaceMTU)
{
    handleChange();
    this->interfaceMTU = interfaceMTU;
}

const Ospfv3DdOptions& Ospfv3DatabaseDescriptionPacket::getDdOptions() const
{
    return this->ddOptions;
}

void Ospfv3DatabaseDescriptionPacket::setDdOptions(const Ospfv3DdOptions& ddOptions)
{
    handleChange();
    this->ddOptions = ddOptions;
}

uint32_t Ospfv3DatabaseDescriptionPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void Ospfv3DatabaseDescriptionPacket::setSequenceNumber(uint32_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

size_t Ospfv3DatabaseDescriptionPacket::getLsaHeadersArraySize() const
{
    return lsaHeaders_arraysize;
}

const Ospfv3LsaHeader& Ospfv3DatabaseDescriptionPacket::getLsaHeaders(size_t k) const
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    return this->lsaHeaders[k];
}

void Ospfv3DatabaseDescriptionPacket::setLsaHeadersArraySize(size_t newSize)
{
    handleChange();
    Ospfv3LsaHeader *lsaHeaders2 = (newSize==0) ? nullptr : new Ospfv3LsaHeader[newSize];
    size_t minSize = lsaHeaders_arraysize < newSize ? lsaHeaders_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv3DatabaseDescriptionPacket::setLsaHeaders(size_t k, const Ospfv3LsaHeader& lsaHeaders)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    this->lsaHeaders[k] = lsaHeaders;
}

void Ospfv3DatabaseDescriptionPacket::insertLsaHeaders(size_t k, const Ospfv3LsaHeader& lsaHeaders)
{
    if (k > lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize + 1;
    Ospfv3LsaHeader *lsaHeaders2 = new Ospfv3LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    lsaHeaders2[k] = lsaHeaders;
    for (i = k + 1; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i-1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv3DatabaseDescriptionPacket::appendLsaHeaders(const Ospfv3LsaHeader& lsaHeaders)
{
    insertLsaHeaders(lsaHeaders_arraysize, lsaHeaders);
}

void Ospfv3DatabaseDescriptionPacket::eraseLsaHeaders(size_t k)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize - 1;
    Ospfv3LsaHeader *lsaHeaders2 = (newSize == 0) ? nullptr : new Ospfv3LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    for (i = k; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i+1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

class Ospfv3DatabaseDescriptionPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_options,
        FIELD_interfaceMTU,
        FIELD_ddOptions,
        FIELD_sequenceNumber,
        FIELD_lsaHeaders,
    };
  public:
    Ospfv3DatabaseDescriptionPacketDescriptor();
    virtual ~Ospfv3DatabaseDescriptionPacketDescriptor();

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

Register_ClassDescriptor(Ospfv3DatabaseDescriptionPacketDescriptor)

Ospfv3DatabaseDescriptionPacketDescriptor::Ospfv3DatabaseDescriptionPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3DatabaseDescriptionPacket)), "inet::ospfv3::Ospfv3Packet")
{
    propertyNames = nullptr;
}

Ospfv3DatabaseDescriptionPacketDescriptor::~Ospfv3DatabaseDescriptionPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3DatabaseDescriptionPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3DatabaseDescriptionPacket *>(obj)!=nullptr;
}

const char **Ospfv3DatabaseDescriptionPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3DatabaseDescriptionPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int Ospfv3DatabaseDescriptionPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISCOMPOUND,    // FIELD_options
        FD_ISEDITABLE,    // FIELD_interfaceMTU
        FD_ISCOMPOUND,    // FIELD_ddOptions
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "options",
        "interfaceMTU",
        "ddOptions",
        "sequenceNumber",
        "lsaHeaders",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int Ospfv3DatabaseDescriptionPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "interfaceMTU") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ddOptions") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lsaHeaders") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_reserved1
        "inet::ospfv3::Ospfv3Options",    // FIELD_options
        "uint16_t",    // FIELD_interfaceMTU
        "inet::ospfv3::Ospfv3DdOptions",    // FIELD_ddOptions
        "uint32_t",    // FIELD_sequenceNumber
        "inet::ospfv3::Ospfv3LsaHeader",    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3DatabaseDescriptionPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3DatabaseDescriptionPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeadersArraySize();
        default: return 0;
    }
}

void Ospfv3DatabaseDescriptionPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: pp->setLsaHeadersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3DatabaseDescriptionPacket'", field);
    }
}

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3DatabaseDescriptionPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return ulong2string(pp->getReserved1());
        case FIELD_options: return "";
        case FIELD_interfaceMTU: return ulong2string(pp->getInterfaceMTU());
        case FIELD_ddOptions: return "";
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_lsaHeaders: return pp->getLsaHeaders(i).str();
        default: return "";
    }
}

void Ospfv3DatabaseDescriptionPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(string2ulong(value)); break;
        case FIELD_interfaceMTU: pp->setInterfaceMTU(string2ulong(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DatabaseDescriptionPacket'", field);
    }
}

omnetpp::cValue Ospfv3DatabaseDescriptionPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return (omnetpp::intval_t)(pp->getReserved1());
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_interfaceMTU: return (omnetpp::intval_t)(pp->getInterfaceMTU());
        case FIELD_ddOptions: return omnetpp::toAnyPtr(&pp->getDdOptions()); break;
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3DatabaseDescriptionPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv3DatabaseDescriptionPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_interfaceMTU: pp->setInterfaceMTU(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DatabaseDescriptionPacket'", field);
    }
}

const char *Ospfv3DatabaseDescriptionPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ospfv3Options));
        case FIELD_ddOptions: return omnetpp::opp_typename(typeid(Ospfv3DdOptions));
        case FIELD_lsaHeaders: return omnetpp::opp_typename(typeid(Ospfv3LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3DatabaseDescriptionPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_ddOptions: return omnetpp::toAnyPtr(&pp->getDdOptions()); break;
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3DatabaseDescriptionPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv3DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3DatabaseDescriptionPacket'", field);
    }
}

Ospfv3LsRequest::Ospfv3LsRequest()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv3LsRequest& a)
{
    doParsimPacking(b,a.lsaType);
    doParsimPacking(b,a.lsaID);
    doParsimPacking(b,a.advertisingRouter);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv3LsRequest& a)
{
    doParsimUnpacking(b,a.lsaType);
    doParsimUnpacking(b,a.lsaID);
    doParsimUnpacking(b,a.advertisingRouter);
}

class Ospfv3LsRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsaType,
        FIELD_lsaID,
        FIELD_advertisingRouter,
    };
  public:
    Ospfv3LsRequestDescriptor();
    virtual ~Ospfv3LsRequestDescriptor();

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

Register_ClassDescriptor(Ospfv3LsRequestDescriptor)

Ospfv3LsRequestDescriptor::Ospfv3LsRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LsRequest)), "")
{
    propertyNames = nullptr;
}

Ospfv3LsRequestDescriptor::~Ospfv3LsRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LsRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LsRequest *>(obj)!=nullptr;
}

const char **Ospfv3LsRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LsRequestDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LsRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ospfv3LsRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsaType
        0,    // FIELD_lsaID
        0,    // FIELD_advertisingRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LsRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsaType",
        "lsaID",
        "advertisingRouter",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ospfv3LsRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsaType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lsaID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "advertisingRouter") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LsRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_lsaType
        "inet::Ipv4Address",    // FIELD_lsaID
        "inet::Ipv4Address",    // FIELD_advertisingRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LsRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LsRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LsRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv3LsRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LsRequest'", field);
    }
}

const char *Ospfv3LsRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LsRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsaType: return ulong2string(pp->lsaType);
        case FIELD_lsaID: return pp->lsaID.str();
        case FIELD_advertisingRouter: return pp->advertisingRouter.str();
        default: return "";
    }
}

void Ospfv3LsRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsaType: pp->lsaType = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsRequest'", field);
    }
}

omnetpp::cValue Ospfv3LsRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsaType: return (omnetpp::intval_t)(pp->lsaType);
        case FIELD_lsaID: return omnetpp::toAnyPtr(&pp->lsaID); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->advertisingRouter); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LsRequest' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LsRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsaType: pp->lsaType = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsRequest'", field);
    }
}

const char *Ospfv3LsRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv3LsRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsaID: return omnetpp::toAnyPtr(&pp->lsaID); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->advertisingRouter); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LsRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LsRequest *pp = omnetpp::fromAnyPtr<Ospfv3LsRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LsRequest'", field);
    }
}

Register_Class(Ospfv3LinkStateRequestPacket)

Ospfv3LinkStateRequestPacket::Ospfv3LinkStateRequestPacket() : ::inet::ospfv3::Ospfv3Packet()
{
}

Ospfv3LinkStateRequestPacket::Ospfv3LinkStateRequestPacket(const Ospfv3LinkStateRequestPacket& other) : ::inet::ospfv3::Ospfv3Packet(other)
{
    copy(other);
}

Ospfv3LinkStateRequestPacket::~Ospfv3LinkStateRequestPacket()
{
    delete [] this->requests;
}

Ospfv3LinkStateRequestPacket& Ospfv3LinkStateRequestPacket::operator=(const Ospfv3LinkStateRequestPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3LinkStateRequestPacket::copy(const Ospfv3LinkStateRequestPacket& other)
{
    delete [] this->requests;
    this->requests = (other.requests_arraysize==0) ? nullptr : new Ospfv3LsRequest[other.requests_arraysize];
    requests_arraysize = other.requests_arraysize;
    for (size_t i = 0; i < requests_arraysize; i++) {
        this->requests[i] = other.requests[i];
    }
}

void Ospfv3LinkStateRequestPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Packet::parsimPack(b);
    b->pack(requests_arraysize);
    doParsimArrayPacking(b,this->requests,requests_arraysize);
}

void Ospfv3LinkStateRequestPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Packet::parsimUnpack(b);
    delete [] this->requests;
    b->unpack(requests_arraysize);
    if (requests_arraysize == 0) {
        this->requests = nullptr;
    } else {
        this->requests = new Ospfv3LsRequest[requests_arraysize];
        doParsimArrayUnpacking(b,this->requests,requests_arraysize);
    }
}

size_t Ospfv3LinkStateRequestPacket::getRequestsArraySize() const
{
    return requests_arraysize;
}

const Ospfv3LsRequest& Ospfv3LinkStateRequestPacket::getRequests(size_t k) const
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    return this->requests[k];
}

void Ospfv3LinkStateRequestPacket::setRequestsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3LsRequest *requests2 = (newSize==0) ? nullptr : new Ospfv3LsRequest[newSize];
    size_t minSize = requests_arraysize < newSize ? requests_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        requests2[i] = this->requests[i];
    delete [] this->requests;
    this->requests = requests2;
    requests_arraysize = newSize;
}

void Ospfv3LinkStateRequestPacket::setRequests(size_t k, const Ospfv3LsRequest& requests)
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    this->requests[k] = requests;
}

void Ospfv3LinkStateRequestPacket::insertRequests(size_t k, const Ospfv3LsRequest& requests)
{
    if (k > requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = requests_arraysize + 1;
    Ospfv3LsRequest *requests2 = new Ospfv3LsRequest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        requests2[i] = this->requests[i];
    requests2[k] = requests;
    for (i = k + 1; i < newSize; i++)
        requests2[i] = this->requests[i-1];
    delete [] this->requests;
    this->requests = requests2;
    requests_arraysize = newSize;
}

void Ospfv3LinkStateRequestPacket::appendRequests(const Ospfv3LsRequest& requests)
{
    insertRequests(requests_arraysize, requests);
}

void Ospfv3LinkStateRequestPacket::eraseRequests(size_t k)
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = requests_arraysize - 1;
    Ospfv3LsRequest *requests2 = (newSize == 0) ? nullptr : new Ospfv3LsRequest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        requests2[i] = this->requests[i];
    for (i = k; i < newSize; i++)
        requests2[i] = this->requests[i+1];
    delete [] this->requests;
    this->requests = requests2;
    requests_arraysize = newSize;
}

class Ospfv3LinkStateRequestPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requests,
    };
  public:
    Ospfv3LinkStateRequestPacketDescriptor();
    virtual ~Ospfv3LinkStateRequestPacketDescriptor();

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

Register_ClassDescriptor(Ospfv3LinkStateRequestPacketDescriptor)

Ospfv3LinkStateRequestPacketDescriptor::Ospfv3LinkStateRequestPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LinkStateRequestPacket)), "inet::ospfv3::Ospfv3Packet")
{
    propertyNames = nullptr;
}

Ospfv3LinkStateRequestPacketDescriptor::~Ospfv3LinkStateRequestPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LinkStateRequestPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LinkStateRequestPacket *>(obj)!=nullptr;
}

const char **Ospfv3LinkStateRequestPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LinkStateRequestPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LinkStateRequestPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv3LinkStateRequestPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_requests
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LinkStateRequestPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requests",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ospfv3LinkStateRequestPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requests") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LinkStateRequestPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv3::Ospfv3LsRequest",    // FIELD_requests
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LinkStateRequestPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LinkStateRequestPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LinkStateRequestPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return pp->getRequestsArraySize();
        default: return 0;
    }
}

void Ospfv3LinkStateRequestPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: pp->setRequestsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LinkStateRequestPacket'", field);
    }
}

const char *Ospfv3LinkStateRequestPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LinkStateRequestPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return "";
        default: return "";
    }
}

void Ospfv3LinkStateRequestPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateRequestPacket'", field);
    }
}

omnetpp::cValue Ospfv3LinkStateRequestPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return omnetpp::toAnyPtr(&pp->getRequests(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LinkStateRequestPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LinkStateRequestPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateRequestPacket'", field);
    }
}

const char *Ospfv3LinkStateRequestPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_requests: return omnetpp::opp_typename(typeid(Ospfv3LsRequest));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3LinkStateRequestPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return omnetpp::toAnyPtr(&pp->getRequests(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LinkStateRequestPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateRequestPacket'", field);
    }
}

Register_Class(Ospfv3LinkStateUpdatePacket)

Ospfv3LinkStateUpdatePacket::Ospfv3LinkStateUpdatePacket() : ::inet::ospfv3::Ospfv3Packet()
{
}

Ospfv3LinkStateUpdatePacket::Ospfv3LinkStateUpdatePacket(const Ospfv3LinkStateUpdatePacket& other) : ::inet::ospfv3::Ospfv3Packet(other)
{
    copy(other);
}

Ospfv3LinkStateUpdatePacket::~Ospfv3LinkStateUpdatePacket()
{
    delete [] this->RouterLSAs;
    delete [] this->NetworkLSAs;
    delete [] this->InterAreaPrefixLSAs;
    delete [] this->LinkLSAs;
    delete [] this->IntraAreaPrefixLSAs;
}

Ospfv3LinkStateUpdatePacket& Ospfv3LinkStateUpdatePacket::operator=(const Ospfv3LinkStateUpdatePacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3LinkStateUpdatePacket::copy(const Ospfv3LinkStateUpdatePacket& other)
{
    this->lsaCount = other.lsaCount;
    delete [] this->RouterLSAs;
    this->RouterLSAs = (other.RouterLSAs_arraysize==0) ? nullptr : new Ospfv3RouterLsa[other.RouterLSAs_arraysize];
    RouterLSAs_arraysize = other.RouterLSAs_arraysize;
    for (size_t i = 0; i < RouterLSAs_arraysize; i++) {
        this->RouterLSAs[i] = other.RouterLSAs[i];
    }
    delete [] this->NetworkLSAs;
    this->NetworkLSAs = (other.NetworkLSAs_arraysize==0) ? nullptr : new Ospfv3NetworkLsa[other.NetworkLSAs_arraysize];
    NetworkLSAs_arraysize = other.NetworkLSAs_arraysize;
    for (size_t i = 0; i < NetworkLSAs_arraysize; i++) {
        this->NetworkLSAs[i] = other.NetworkLSAs[i];
    }
    delete [] this->InterAreaPrefixLSAs;
    this->InterAreaPrefixLSAs = (other.InterAreaPrefixLSAs_arraysize==0) ? nullptr : new Ospfv3InterAreaPrefixLsa[other.InterAreaPrefixLSAs_arraysize];
    InterAreaPrefixLSAs_arraysize = other.InterAreaPrefixLSAs_arraysize;
    for (size_t i = 0; i < InterAreaPrefixLSAs_arraysize; i++) {
        this->InterAreaPrefixLSAs[i] = other.InterAreaPrefixLSAs[i];
    }
    delete [] this->LinkLSAs;
    this->LinkLSAs = (other.LinkLSAs_arraysize==0) ? nullptr : new Ospfv3LinkLsa[other.LinkLSAs_arraysize];
    LinkLSAs_arraysize = other.LinkLSAs_arraysize;
    for (size_t i = 0; i < LinkLSAs_arraysize; i++) {
        this->LinkLSAs[i] = other.LinkLSAs[i];
    }
    delete [] this->IntraAreaPrefixLSAs;
    this->IntraAreaPrefixLSAs = (other.IntraAreaPrefixLSAs_arraysize==0) ? nullptr : new Ospfv3IntraAreaPrefixLsa[other.IntraAreaPrefixLSAs_arraysize];
    IntraAreaPrefixLSAs_arraysize = other.IntraAreaPrefixLSAs_arraysize;
    for (size_t i = 0; i < IntraAreaPrefixLSAs_arraysize; i++) {
        this->IntraAreaPrefixLSAs[i] = other.IntraAreaPrefixLSAs[i];
    }
}

void Ospfv3LinkStateUpdatePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Packet::parsimPack(b);
    doParsimPacking(b,this->lsaCount);
    b->pack(RouterLSAs_arraysize);
    doParsimArrayPacking(b,this->RouterLSAs,RouterLSAs_arraysize);
    b->pack(NetworkLSAs_arraysize);
    doParsimArrayPacking(b,this->NetworkLSAs,NetworkLSAs_arraysize);
    b->pack(InterAreaPrefixLSAs_arraysize);
    doParsimArrayPacking(b,this->InterAreaPrefixLSAs,InterAreaPrefixLSAs_arraysize);
    b->pack(LinkLSAs_arraysize);
    doParsimArrayPacking(b,this->LinkLSAs,LinkLSAs_arraysize);
    b->pack(IntraAreaPrefixLSAs_arraysize);
    doParsimArrayPacking(b,this->IntraAreaPrefixLSAs,IntraAreaPrefixLSAs_arraysize);
}

void Ospfv3LinkStateUpdatePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->lsaCount);
    delete [] this->RouterLSAs;
    b->unpack(RouterLSAs_arraysize);
    if (RouterLSAs_arraysize == 0) {
        this->RouterLSAs = nullptr;
    } else {
        this->RouterLSAs = new Ospfv3RouterLsa[RouterLSAs_arraysize];
        doParsimArrayUnpacking(b,this->RouterLSAs,RouterLSAs_arraysize);
    }
    delete [] this->NetworkLSAs;
    b->unpack(NetworkLSAs_arraysize);
    if (NetworkLSAs_arraysize == 0) {
        this->NetworkLSAs = nullptr;
    } else {
        this->NetworkLSAs = new Ospfv3NetworkLsa[NetworkLSAs_arraysize];
        doParsimArrayUnpacking(b,this->NetworkLSAs,NetworkLSAs_arraysize);
    }
    delete [] this->InterAreaPrefixLSAs;
    b->unpack(InterAreaPrefixLSAs_arraysize);
    if (InterAreaPrefixLSAs_arraysize == 0) {
        this->InterAreaPrefixLSAs = nullptr;
    } else {
        this->InterAreaPrefixLSAs = new Ospfv3InterAreaPrefixLsa[InterAreaPrefixLSAs_arraysize];
        doParsimArrayUnpacking(b,this->InterAreaPrefixLSAs,InterAreaPrefixLSAs_arraysize);
    }
    delete [] this->LinkLSAs;
    b->unpack(LinkLSAs_arraysize);
    if (LinkLSAs_arraysize == 0) {
        this->LinkLSAs = nullptr;
    } else {
        this->LinkLSAs = new Ospfv3LinkLsa[LinkLSAs_arraysize];
        doParsimArrayUnpacking(b,this->LinkLSAs,LinkLSAs_arraysize);
    }
    delete [] this->IntraAreaPrefixLSAs;
    b->unpack(IntraAreaPrefixLSAs_arraysize);
    if (IntraAreaPrefixLSAs_arraysize == 0) {
        this->IntraAreaPrefixLSAs = nullptr;
    } else {
        this->IntraAreaPrefixLSAs = new Ospfv3IntraAreaPrefixLsa[IntraAreaPrefixLSAs_arraysize];
        doParsimArrayUnpacking(b,this->IntraAreaPrefixLSAs,IntraAreaPrefixLSAs_arraysize);
    }
}

uint32_t Ospfv3LinkStateUpdatePacket::getLsaCount() const
{
    return this->lsaCount;
}

void Ospfv3LinkStateUpdatePacket::setLsaCount(uint32_t lsaCount)
{
    handleChange();
    this->lsaCount = lsaCount;
}

size_t Ospfv3LinkStateUpdatePacket::getRouterLSAsArraySize() const
{
    return RouterLSAs_arraysize;
}

const Ospfv3RouterLsa& Ospfv3LinkStateUpdatePacket::getRouterLSAs(size_t k) const
{
    if (k >= RouterLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)RouterLSAs_arraysize, (unsigned long)k);
    return this->RouterLSAs[k];
}

void Ospfv3LinkStateUpdatePacket::setRouterLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3RouterLsa *RouterLSAs2 = (newSize==0) ? nullptr : new Ospfv3RouterLsa[newSize];
    size_t minSize = RouterLSAs_arraysize < newSize ? RouterLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        RouterLSAs2[i] = this->RouterLSAs[i];
    delete [] this->RouterLSAs;
    this->RouterLSAs = RouterLSAs2;
    RouterLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::setRouterLSAs(size_t k, const Ospfv3RouterLsa& RouterLSAs)
{
    if (k >= RouterLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)RouterLSAs_arraysize, (unsigned long)k);
    handleChange();
    this->RouterLSAs[k] = RouterLSAs;
}

void Ospfv3LinkStateUpdatePacket::insertRouterLSAs(size_t k, const Ospfv3RouterLsa& RouterLSAs)
{
    if (k > RouterLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)RouterLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = RouterLSAs_arraysize + 1;
    Ospfv3RouterLsa *RouterLSAs2 = new Ospfv3RouterLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        RouterLSAs2[i] = this->RouterLSAs[i];
    RouterLSAs2[k] = RouterLSAs;
    for (i = k + 1; i < newSize; i++)
        RouterLSAs2[i] = this->RouterLSAs[i-1];
    delete [] this->RouterLSAs;
    this->RouterLSAs = RouterLSAs2;
    RouterLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::appendRouterLSAs(const Ospfv3RouterLsa& RouterLSAs)
{
    insertRouterLSAs(RouterLSAs_arraysize, RouterLSAs);
}

void Ospfv3LinkStateUpdatePacket::eraseRouterLSAs(size_t k)
{
    if (k >= RouterLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)RouterLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = RouterLSAs_arraysize - 1;
    Ospfv3RouterLsa *RouterLSAs2 = (newSize == 0) ? nullptr : new Ospfv3RouterLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        RouterLSAs2[i] = this->RouterLSAs[i];
    for (i = k; i < newSize; i++)
        RouterLSAs2[i] = this->RouterLSAs[i+1];
    delete [] this->RouterLSAs;
    this->RouterLSAs = RouterLSAs2;
    RouterLSAs_arraysize = newSize;
}

size_t Ospfv3LinkStateUpdatePacket::getNetworkLSAsArraySize() const
{
    return NetworkLSAs_arraysize;
}

const Ospfv3NetworkLsa& Ospfv3LinkStateUpdatePacket::getNetworkLSAs(size_t k) const
{
    if (k >= NetworkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NetworkLSAs_arraysize, (unsigned long)k);
    return this->NetworkLSAs[k];
}

void Ospfv3LinkStateUpdatePacket::setNetworkLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3NetworkLsa *NetworkLSAs2 = (newSize==0) ? nullptr : new Ospfv3NetworkLsa[newSize];
    size_t minSize = NetworkLSAs_arraysize < newSize ? NetworkLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        NetworkLSAs2[i] = this->NetworkLSAs[i];
    delete [] this->NetworkLSAs;
    this->NetworkLSAs = NetworkLSAs2;
    NetworkLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::setNetworkLSAs(size_t k, const Ospfv3NetworkLsa& NetworkLSAs)
{
    if (k >= NetworkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NetworkLSAs_arraysize, (unsigned long)k);
    handleChange();
    this->NetworkLSAs[k] = NetworkLSAs;
}

void Ospfv3LinkStateUpdatePacket::insertNetworkLSAs(size_t k, const Ospfv3NetworkLsa& NetworkLSAs)
{
    if (k > NetworkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NetworkLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = NetworkLSAs_arraysize + 1;
    Ospfv3NetworkLsa *NetworkLSAs2 = new Ospfv3NetworkLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        NetworkLSAs2[i] = this->NetworkLSAs[i];
    NetworkLSAs2[k] = NetworkLSAs;
    for (i = k + 1; i < newSize; i++)
        NetworkLSAs2[i] = this->NetworkLSAs[i-1];
    delete [] this->NetworkLSAs;
    this->NetworkLSAs = NetworkLSAs2;
    NetworkLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::appendNetworkLSAs(const Ospfv3NetworkLsa& NetworkLSAs)
{
    insertNetworkLSAs(NetworkLSAs_arraysize, NetworkLSAs);
}

void Ospfv3LinkStateUpdatePacket::eraseNetworkLSAs(size_t k)
{
    if (k >= NetworkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NetworkLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = NetworkLSAs_arraysize - 1;
    Ospfv3NetworkLsa *NetworkLSAs2 = (newSize == 0) ? nullptr : new Ospfv3NetworkLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        NetworkLSAs2[i] = this->NetworkLSAs[i];
    for (i = k; i < newSize; i++)
        NetworkLSAs2[i] = this->NetworkLSAs[i+1];
    delete [] this->NetworkLSAs;
    this->NetworkLSAs = NetworkLSAs2;
    NetworkLSAs_arraysize = newSize;
}

size_t Ospfv3LinkStateUpdatePacket::getInterAreaPrefixLSAsArraySize() const
{
    return InterAreaPrefixLSAs_arraysize;
}

const Ospfv3InterAreaPrefixLsa& Ospfv3LinkStateUpdatePacket::getInterAreaPrefixLSAs(size_t k) const
{
    if (k >= InterAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)InterAreaPrefixLSAs_arraysize, (unsigned long)k);
    return this->InterAreaPrefixLSAs[k];
}

void Ospfv3LinkStateUpdatePacket::setInterAreaPrefixLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3InterAreaPrefixLsa *InterAreaPrefixLSAs2 = (newSize==0) ? nullptr : new Ospfv3InterAreaPrefixLsa[newSize];
    size_t minSize = InterAreaPrefixLSAs_arraysize < newSize ? InterAreaPrefixLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        InterAreaPrefixLSAs2[i] = this->InterAreaPrefixLSAs[i];
    delete [] this->InterAreaPrefixLSAs;
    this->InterAreaPrefixLSAs = InterAreaPrefixLSAs2;
    InterAreaPrefixLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::setInterAreaPrefixLSAs(size_t k, const Ospfv3InterAreaPrefixLsa& InterAreaPrefixLSAs)
{
    if (k >= InterAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)InterAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    this->InterAreaPrefixLSAs[k] = InterAreaPrefixLSAs;
}

void Ospfv3LinkStateUpdatePacket::insertInterAreaPrefixLSAs(size_t k, const Ospfv3InterAreaPrefixLsa& InterAreaPrefixLSAs)
{
    if (k > InterAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)InterAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = InterAreaPrefixLSAs_arraysize + 1;
    Ospfv3InterAreaPrefixLsa *InterAreaPrefixLSAs2 = new Ospfv3InterAreaPrefixLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        InterAreaPrefixLSAs2[i] = this->InterAreaPrefixLSAs[i];
    InterAreaPrefixLSAs2[k] = InterAreaPrefixLSAs;
    for (i = k + 1; i < newSize; i++)
        InterAreaPrefixLSAs2[i] = this->InterAreaPrefixLSAs[i-1];
    delete [] this->InterAreaPrefixLSAs;
    this->InterAreaPrefixLSAs = InterAreaPrefixLSAs2;
    InterAreaPrefixLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::appendInterAreaPrefixLSAs(const Ospfv3InterAreaPrefixLsa& InterAreaPrefixLSAs)
{
    insertInterAreaPrefixLSAs(InterAreaPrefixLSAs_arraysize, InterAreaPrefixLSAs);
}

void Ospfv3LinkStateUpdatePacket::eraseInterAreaPrefixLSAs(size_t k)
{
    if (k >= InterAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)InterAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = InterAreaPrefixLSAs_arraysize - 1;
    Ospfv3InterAreaPrefixLsa *InterAreaPrefixLSAs2 = (newSize == 0) ? nullptr : new Ospfv3InterAreaPrefixLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        InterAreaPrefixLSAs2[i] = this->InterAreaPrefixLSAs[i];
    for (i = k; i < newSize; i++)
        InterAreaPrefixLSAs2[i] = this->InterAreaPrefixLSAs[i+1];
    delete [] this->InterAreaPrefixLSAs;
    this->InterAreaPrefixLSAs = InterAreaPrefixLSAs2;
    InterAreaPrefixLSAs_arraysize = newSize;
}

size_t Ospfv3LinkStateUpdatePacket::getLinkLSAsArraySize() const
{
    return LinkLSAs_arraysize;
}

const Ospfv3LinkLsa& Ospfv3LinkStateUpdatePacket::getLinkLSAs(size_t k) const
{
    if (k >= LinkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)LinkLSAs_arraysize, (unsigned long)k);
    return this->LinkLSAs[k];
}

void Ospfv3LinkStateUpdatePacket::setLinkLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3LinkLsa *LinkLSAs2 = (newSize==0) ? nullptr : new Ospfv3LinkLsa[newSize];
    size_t minSize = LinkLSAs_arraysize < newSize ? LinkLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        LinkLSAs2[i] = this->LinkLSAs[i];
    delete [] this->LinkLSAs;
    this->LinkLSAs = LinkLSAs2;
    LinkLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::setLinkLSAs(size_t k, const Ospfv3LinkLsa& LinkLSAs)
{
    if (k >= LinkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)LinkLSAs_arraysize, (unsigned long)k);
    handleChange();
    this->LinkLSAs[k] = LinkLSAs;
}

void Ospfv3LinkStateUpdatePacket::insertLinkLSAs(size_t k, const Ospfv3LinkLsa& LinkLSAs)
{
    if (k > LinkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)LinkLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = LinkLSAs_arraysize + 1;
    Ospfv3LinkLsa *LinkLSAs2 = new Ospfv3LinkLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        LinkLSAs2[i] = this->LinkLSAs[i];
    LinkLSAs2[k] = LinkLSAs;
    for (i = k + 1; i < newSize; i++)
        LinkLSAs2[i] = this->LinkLSAs[i-1];
    delete [] this->LinkLSAs;
    this->LinkLSAs = LinkLSAs2;
    LinkLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::appendLinkLSAs(const Ospfv3LinkLsa& LinkLSAs)
{
    insertLinkLSAs(LinkLSAs_arraysize, LinkLSAs);
}

void Ospfv3LinkStateUpdatePacket::eraseLinkLSAs(size_t k)
{
    if (k >= LinkLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)LinkLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = LinkLSAs_arraysize - 1;
    Ospfv3LinkLsa *LinkLSAs2 = (newSize == 0) ? nullptr : new Ospfv3LinkLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        LinkLSAs2[i] = this->LinkLSAs[i];
    for (i = k; i < newSize; i++)
        LinkLSAs2[i] = this->LinkLSAs[i+1];
    delete [] this->LinkLSAs;
    this->LinkLSAs = LinkLSAs2;
    LinkLSAs_arraysize = newSize;
}

size_t Ospfv3LinkStateUpdatePacket::getIntraAreaPrefixLSAsArraySize() const
{
    return IntraAreaPrefixLSAs_arraysize;
}

const Ospfv3IntraAreaPrefixLsa& Ospfv3LinkStateUpdatePacket::getIntraAreaPrefixLSAs(size_t k) const
{
    if (k >= IntraAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)IntraAreaPrefixLSAs_arraysize, (unsigned long)k);
    return this->IntraAreaPrefixLSAs[k];
}

void Ospfv3LinkStateUpdatePacket::setIntraAreaPrefixLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv3IntraAreaPrefixLsa *IntraAreaPrefixLSAs2 = (newSize==0) ? nullptr : new Ospfv3IntraAreaPrefixLsa[newSize];
    size_t minSize = IntraAreaPrefixLSAs_arraysize < newSize ? IntraAreaPrefixLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        IntraAreaPrefixLSAs2[i] = this->IntraAreaPrefixLSAs[i];
    delete [] this->IntraAreaPrefixLSAs;
    this->IntraAreaPrefixLSAs = IntraAreaPrefixLSAs2;
    IntraAreaPrefixLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::setIntraAreaPrefixLSAs(size_t k, const Ospfv3IntraAreaPrefixLsa& IntraAreaPrefixLSAs)
{
    if (k >= IntraAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)IntraAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    this->IntraAreaPrefixLSAs[k] = IntraAreaPrefixLSAs;
}

void Ospfv3LinkStateUpdatePacket::insertIntraAreaPrefixLSAs(size_t k, const Ospfv3IntraAreaPrefixLsa& IntraAreaPrefixLSAs)
{
    if (k > IntraAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)IntraAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = IntraAreaPrefixLSAs_arraysize + 1;
    Ospfv3IntraAreaPrefixLsa *IntraAreaPrefixLSAs2 = new Ospfv3IntraAreaPrefixLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        IntraAreaPrefixLSAs2[i] = this->IntraAreaPrefixLSAs[i];
    IntraAreaPrefixLSAs2[k] = IntraAreaPrefixLSAs;
    for (i = k + 1; i < newSize; i++)
        IntraAreaPrefixLSAs2[i] = this->IntraAreaPrefixLSAs[i-1];
    delete [] this->IntraAreaPrefixLSAs;
    this->IntraAreaPrefixLSAs = IntraAreaPrefixLSAs2;
    IntraAreaPrefixLSAs_arraysize = newSize;
}

void Ospfv3LinkStateUpdatePacket::appendIntraAreaPrefixLSAs(const Ospfv3IntraAreaPrefixLsa& IntraAreaPrefixLSAs)
{
    insertIntraAreaPrefixLSAs(IntraAreaPrefixLSAs_arraysize, IntraAreaPrefixLSAs);
}

void Ospfv3LinkStateUpdatePacket::eraseIntraAreaPrefixLSAs(size_t k)
{
    if (k >= IntraAreaPrefixLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)IntraAreaPrefixLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = IntraAreaPrefixLSAs_arraysize - 1;
    Ospfv3IntraAreaPrefixLsa *IntraAreaPrefixLSAs2 = (newSize == 0) ? nullptr : new Ospfv3IntraAreaPrefixLsa[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        IntraAreaPrefixLSAs2[i] = this->IntraAreaPrefixLSAs[i];
    for (i = k; i < newSize; i++)
        IntraAreaPrefixLSAs2[i] = this->IntraAreaPrefixLSAs[i+1];
    delete [] this->IntraAreaPrefixLSAs;
    this->IntraAreaPrefixLSAs = IntraAreaPrefixLSAs2;
    IntraAreaPrefixLSAs_arraysize = newSize;
}

class Ospfv3LinkStateUpdatePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsaCount,
        FIELD_RouterLSAs,
        FIELD_NetworkLSAs,
        FIELD_InterAreaPrefixLSAs,
        FIELD_LinkLSAs,
        FIELD_IntraAreaPrefixLSAs,
    };
  public:
    Ospfv3LinkStateUpdatePacketDescriptor();
    virtual ~Ospfv3LinkStateUpdatePacketDescriptor();

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

Register_ClassDescriptor(Ospfv3LinkStateUpdatePacketDescriptor)

Ospfv3LinkStateUpdatePacketDescriptor::Ospfv3LinkStateUpdatePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LinkStateUpdatePacket)), "inet::ospfv3::Ospfv3Packet")
{
    propertyNames = nullptr;
}

Ospfv3LinkStateUpdatePacketDescriptor::~Ospfv3LinkStateUpdatePacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LinkStateUpdatePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LinkStateUpdatePacket *>(obj)!=nullptr;
}

const char **Ospfv3LinkStateUpdatePacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LinkStateUpdatePacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LinkStateUpdatePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int Ospfv3LinkStateUpdatePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsaCount
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_RouterLSAs
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_NetworkLSAs
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_InterAreaPrefixLSAs
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_LinkLSAs
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_IntraAreaPrefixLSAs
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LinkStateUpdatePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsaCount",
        "RouterLSAs",
        "NetworkLSAs",
        "InterAreaPrefixLSAs",
        "LinkLSAs",
        "IntraAreaPrefixLSAs",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int Ospfv3LinkStateUpdatePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsaCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "RouterLSAs") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "NetworkLSAs") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "InterAreaPrefixLSAs") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "LinkLSAs") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "IntraAreaPrefixLSAs") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LinkStateUpdatePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_lsaCount
        "inet::ospfv3::Ospfv3RouterLsa",    // FIELD_RouterLSAs
        "inet::ospfv3::Ospfv3NetworkLsa",    // FIELD_NetworkLSAs
        "inet::ospfv3::Ospfv3InterAreaPrefixLsa",    // FIELD_InterAreaPrefixLSAs
        "inet::ospfv3::Ospfv3LinkLsa",    // FIELD_LinkLSAs
        "inet::ospfv3::Ospfv3IntraAreaPrefixLsa",    // FIELD_IntraAreaPrefixLSAs
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LinkStateUpdatePacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LinkStateUpdatePacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LinkStateUpdatePacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_RouterLSAs: return pp->getRouterLSAsArraySize();
        case FIELD_NetworkLSAs: return pp->getNetworkLSAsArraySize();
        case FIELD_InterAreaPrefixLSAs: return pp->getInterAreaPrefixLSAsArraySize();
        case FIELD_LinkLSAs: return pp->getLinkLSAsArraySize();
        case FIELD_IntraAreaPrefixLSAs: return pp->getIntraAreaPrefixLSAsArraySize();
        default: return 0;
    }
}

void Ospfv3LinkStateUpdatePacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_RouterLSAs: pp->setRouterLSAsArraySize(size); break;
        case FIELD_NetworkLSAs: pp->setNetworkLSAsArraySize(size); break;
        case FIELD_InterAreaPrefixLSAs: pp->setInterAreaPrefixLSAsArraySize(size); break;
        case FIELD_LinkLSAs: pp->setLinkLSAsArraySize(size); break;
        case FIELD_IntraAreaPrefixLSAs: pp->setIntraAreaPrefixLSAsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LinkStateUpdatePacket'", field);
    }
}

const char *Ospfv3LinkStateUpdatePacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LinkStateUpdatePacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaCount: return ulong2string(pp->getLsaCount());
        case FIELD_RouterLSAs: return pp->getRouterLSAs(i).str();
        case FIELD_NetworkLSAs: return pp->getNetworkLSAs(i).str();
        case FIELD_InterAreaPrefixLSAs: return pp->getInterAreaPrefixLSAs(i).str();
        case FIELD_LinkLSAs: return pp->getLinkLSAs(i).str();
        case FIELD_IntraAreaPrefixLSAs: return pp->getIntraAreaPrefixLSAs(i).str();
        default: return "";
    }
}

void Ospfv3LinkStateUpdatePacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaCount: pp->setLsaCount(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateUpdatePacket'", field);
    }
}

omnetpp::cValue Ospfv3LinkStateUpdatePacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaCount: return (omnetpp::intval_t)(pp->getLsaCount());
        case FIELD_RouterLSAs: return omnetpp::toAnyPtr(&pp->getRouterLSAs(i)); break;
        case FIELD_NetworkLSAs: return omnetpp::toAnyPtr(&pp->getNetworkLSAs(i)); break;
        case FIELD_InterAreaPrefixLSAs: return omnetpp::toAnyPtr(&pp->getInterAreaPrefixLSAs(i)); break;
        case FIELD_LinkLSAs: return omnetpp::toAnyPtr(&pp->getLinkLSAs(i)); break;
        case FIELD_IntraAreaPrefixLSAs: return omnetpp::toAnyPtr(&pp->getIntraAreaPrefixLSAs(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LinkStateUpdatePacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LinkStateUpdatePacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaCount: pp->setLsaCount(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateUpdatePacket'", field);
    }
}

const char *Ospfv3LinkStateUpdatePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_RouterLSAs: return omnetpp::opp_typename(typeid(Ospfv3RouterLsa));
        case FIELD_NetworkLSAs: return omnetpp::opp_typename(typeid(Ospfv3NetworkLsa));
        case FIELD_InterAreaPrefixLSAs: return omnetpp::opp_typename(typeid(Ospfv3InterAreaPrefixLsa));
        case FIELD_LinkLSAs: return omnetpp::opp_typename(typeid(Ospfv3LinkLsa));
        case FIELD_IntraAreaPrefixLSAs: return omnetpp::opp_typename(typeid(Ospfv3IntraAreaPrefixLsa));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3LinkStateUpdatePacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_RouterLSAs: return omnetpp::toAnyPtr(&pp->getRouterLSAs(i)); break;
        case FIELD_NetworkLSAs: return omnetpp::toAnyPtr(&pp->getNetworkLSAs(i)); break;
        case FIELD_InterAreaPrefixLSAs: return omnetpp::toAnyPtr(&pp->getInterAreaPrefixLSAs(i)); break;
        case FIELD_LinkLSAs: return omnetpp::toAnyPtr(&pp->getLinkLSAs(i)); break;
        case FIELD_IntraAreaPrefixLSAs: return omnetpp::toAnyPtr(&pp->getIntraAreaPrefixLSAs(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LinkStateUpdatePacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateUpdatePacket'", field);
    }
}

Register_Class(Ospfv3LinkStateAcknowledgementPacket)

Ospfv3LinkStateAcknowledgementPacket::Ospfv3LinkStateAcknowledgementPacket() : ::inet::ospfv3::Ospfv3Packet()
{
}

Ospfv3LinkStateAcknowledgementPacket::Ospfv3LinkStateAcknowledgementPacket(const Ospfv3LinkStateAcknowledgementPacket& other) : ::inet::ospfv3::Ospfv3Packet(other)
{
    copy(other);
}

Ospfv3LinkStateAcknowledgementPacket::~Ospfv3LinkStateAcknowledgementPacket()
{
    delete [] this->lsaHeaders;
}

Ospfv3LinkStateAcknowledgementPacket& Ospfv3LinkStateAcknowledgementPacket::operator=(const Ospfv3LinkStateAcknowledgementPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv3::Ospfv3Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv3LinkStateAcknowledgementPacket::copy(const Ospfv3LinkStateAcknowledgementPacket& other)
{
    delete [] this->lsaHeaders;
    this->lsaHeaders = (other.lsaHeaders_arraysize==0) ? nullptr : new Ospfv3LsaHeader[other.lsaHeaders_arraysize];
    lsaHeaders_arraysize = other.lsaHeaders_arraysize;
    for (size_t i = 0; i < lsaHeaders_arraysize; i++) {
        this->lsaHeaders[i] = other.lsaHeaders[i];
    }
}

void Ospfv3LinkStateAcknowledgementPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv3::Ospfv3Packet::parsimPack(b);
    b->pack(lsaHeaders_arraysize);
    doParsimArrayPacking(b,this->lsaHeaders,lsaHeaders_arraysize);
}

void Ospfv3LinkStateAcknowledgementPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv3::Ospfv3Packet::parsimUnpack(b);
    delete [] this->lsaHeaders;
    b->unpack(lsaHeaders_arraysize);
    if (lsaHeaders_arraysize == 0) {
        this->lsaHeaders = nullptr;
    } else {
        this->lsaHeaders = new Ospfv3LsaHeader[lsaHeaders_arraysize];
        doParsimArrayUnpacking(b,this->lsaHeaders,lsaHeaders_arraysize);
    }
}

size_t Ospfv3LinkStateAcknowledgementPacket::getLsaHeadersArraySize() const
{
    return lsaHeaders_arraysize;
}

const Ospfv3LsaHeader& Ospfv3LinkStateAcknowledgementPacket::getLsaHeaders(size_t k) const
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    return this->lsaHeaders[k];
}

void Ospfv3LinkStateAcknowledgementPacket::setLsaHeadersArraySize(size_t newSize)
{
    handleChange();
    Ospfv3LsaHeader *lsaHeaders2 = (newSize==0) ? nullptr : new Ospfv3LsaHeader[newSize];
    size_t minSize = lsaHeaders_arraysize < newSize ? lsaHeaders_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv3LinkStateAcknowledgementPacket::setLsaHeaders(size_t k, const Ospfv3LsaHeader& lsaHeaders)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    this->lsaHeaders[k] = lsaHeaders;
}

void Ospfv3LinkStateAcknowledgementPacket::insertLsaHeaders(size_t k, const Ospfv3LsaHeader& lsaHeaders)
{
    if (k > lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize + 1;
    Ospfv3LsaHeader *lsaHeaders2 = new Ospfv3LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    lsaHeaders2[k] = lsaHeaders;
    for (i = k + 1; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i-1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv3LinkStateAcknowledgementPacket::appendLsaHeaders(const Ospfv3LsaHeader& lsaHeaders)
{
    insertLsaHeaders(lsaHeaders_arraysize, lsaHeaders);
}

void Ospfv3LinkStateAcknowledgementPacket::eraseLsaHeaders(size_t k)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize - 1;
    Ospfv3LsaHeader *lsaHeaders2 = (newSize == 0) ? nullptr : new Ospfv3LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    for (i = k; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i+1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

class Ospfv3LinkStateAcknowledgementPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsaHeaders,
    };
  public:
    Ospfv3LinkStateAcknowledgementPacketDescriptor();
    virtual ~Ospfv3LinkStateAcknowledgementPacketDescriptor();

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

Register_ClassDescriptor(Ospfv3LinkStateAcknowledgementPacketDescriptor)

Ospfv3LinkStateAcknowledgementPacketDescriptor::Ospfv3LinkStateAcknowledgementPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv3::Ospfv3LinkStateAcknowledgementPacket)), "inet::ospfv3::Ospfv3Packet")
{
    propertyNames = nullptr;
}

Ospfv3LinkStateAcknowledgementPacketDescriptor::~Ospfv3LinkStateAcknowledgementPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv3LinkStateAcknowledgementPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv3LinkStateAcknowledgementPacket *>(obj)!=nullptr;
}

const char **Ospfv3LinkStateAcknowledgementPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsaHeaders",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ospfv3LinkStateAcknowledgementPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsaHeaders") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv3::Ospfv3LsaHeader",    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeadersArraySize();
        default: return 0;
    }
}

void Ospfv3LinkStateAcknowledgementPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: pp->setLsaHeadersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv3LinkStateAcknowledgementPacket'", field);
    }
}

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeaders(i).str();
        default: return "";
    }
}

void Ospfv3LinkStateAcknowledgementPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateAcknowledgementPacket'", field);
    }
}

omnetpp::cValue Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv3LinkStateAcknowledgementPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv3LinkStateAcknowledgementPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateAcknowledgementPacket'", field);
    }
}

const char *Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::opp_typename(typeid(Ospfv3LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv3LinkStateAcknowledgementPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv3LinkStateAcknowledgementPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv3LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv3LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv3LinkStateAcknowledgementPacket'", field);
    }
}

}  // namespace ospfv3
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

