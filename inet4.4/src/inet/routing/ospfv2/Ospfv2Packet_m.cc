//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/ospfv2/Ospfv2Packet.msg.
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
#include "Ospfv2Packet_m.h"

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
namespace ospfv2 {

Register_Enum(inet::ospfv2::Ospfv2TimerType, (inet::ospfv2::Ospfv2TimerType::INTERFACE_HELLO_TIMER, inet::ospfv2::Ospfv2TimerType::INTERFACE_WAIT_TIMER, inet::ospfv2::Ospfv2TimerType::INTERFACE_ACKNOWLEDGEMENT_TIMER, inet::ospfv2::Ospfv2TimerType::NEIGHBOR_INACTIVITY_TIMER, inet::ospfv2::Ospfv2TimerType::NEIGHBOR_POLL_TIMER, inet::ospfv2::Ospfv2TimerType::NEIGHBOR_DD_RETRANSMISSION_TIMER, inet::ospfv2::Ospfv2TimerType::NEIGHBOR_UPDATE_RETRANSMISSION_TIMER, inet::ospfv2::Ospfv2TimerType::NEIGHBOR_REQUEST_RETRANSMISSION_TIMER, inet::ospfv2::Ospfv2TimerType::DATABASE_AGE_TIMER));

Ospfv2Options::Ospfv2Options()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv2Options& a)
{
    doParsimPacking(b,a.unused_1);
    doParsimPacking(b,a.E_ExternalRoutingCapability);
    doParsimPacking(b,a.MC_MulticastForwarding);
    doParsimPacking(b,a.NP_Type7LSA);
    doParsimPacking(b,a.EA_ForwardExternalLSAs);
    doParsimPacking(b,a.DC_DemandCircuits);
    doParsimPacking(b,a.unused_2);
    doParsimPacking(b,a.unused_3);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv2Options& a)
{
    doParsimUnpacking(b,a.unused_1);
    doParsimUnpacking(b,a.E_ExternalRoutingCapability);
    doParsimUnpacking(b,a.MC_MulticastForwarding);
    doParsimUnpacking(b,a.NP_Type7LSA);
    doParsimUnpacking(b,a.EA_ForwardExternalLSAs);
    doParsimUnpacking(b,a.DC_DemandCircuits);
    doParsimUnpacking(b,a.unused_2);
    doParsimUnpacking(b,a.unused_3);
}

class Ospfv2OptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unused_1,
        FIELD_E_ExternalRoutingCapability,
        FIELD_MC_MulticastForwarding,
        FIELD_NP_Type7LSA,
        FIELD_EA_ForwardExternalLSAs,
        FIELD_DC_DemandCircuits,
        FIELD_unused_2,
        FIELD_unused_3,
    };
  public:
    Ospfv2OptionsDescriptor();
    virtual ~Ospfv2OptionsDescriptor();

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

Register_ClassDescriptor(Ospfv2OptionsDescriptor)

Ospfv2OptionsDescriptor::Ospfv2OptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2Options)), "")
{
    propertyNames = nullptr;
}

Ospfv2OptionsDescriptor::~Ospfv2OptionsDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2OptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2Options *>(obj)!=nullptr;
}

const char **Ospfv2OptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2OptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2OptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ospfv2OptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_unused_1
        FD_ISEDITABLE,    // FIELD_E_ExternalRoutingCapability
        FD_ISEDITABLE,    // FIELD_MC_MulticastForwarding
        FD_ISEDITABLE,    // FIELD_NP_Type7LSA
        FD_ISEDITABLE,    // FIELD_EA_ForwardExternalLSAs
        FD_ISEDITABLE,    // FIELD_DC_DemandCircuits
        FD_ISEDITABLE,    // FIELD_unused_2
        FD_ISEDITABLE,    // FIELD_unused_3
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2OptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unused_1",
        "E_ExternalRoutingCapability",
        "MC_MulticastForwarding",
        "NP_Type7LSA",
        "EA_ForwardExternalLSAs",
        "DC_DemandCircuits",
        "unused_2",
        "unused_3",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ospfv2OptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unused_1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "E_ExternalRoutingCapability") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "MC_MulticastForwarding") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "NP_Type7LSA") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "EA_ForwardExternalLSAs") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "DC_DemandCircuits") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "unused_2") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "unused_3") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2OptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_unused_1
        "bool",    // FIELD_E_ExternalRoutingCapability
        "bool",    // FIELD_MC_MulticastForwarding
        "bool",    // FIELD_NP_Type7LSA
        "bool",    // FIELD_EA_ForwardExternalLSAs
        "bool",    // FIELD_DC_DemandCircuits
        "bool",    // FIELD_unused_2
        "bool",    // FIELD_unused_3
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2OptionsDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2OptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2OptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2OptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2Options'", field);
    }
}

const char *Ospfv2OptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2OptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        case FIELD_unused_1: return bool2string(pp->unused_1);
        case FIELD_E_ExternalRoutingCapability: return bool2string(pp->E_ExternalRoutingCapability);
        case FIELD_MC_MulticastForwarding: return bool2string(pp->MC_MulticastForwarding);
        case FIELD_NP_Type7LSA: return bool2string(pp->NP_Type7LSA);
        case FIELD_EA_ForwardExternalLSAs: return bool2string(pp->EA_ForwardExternalLSAs);
        case FIELD_DC_DemandCircuits: return bool2string(pp->DC_DemandCircuits);
        case FIELD_unused_2: return bool2string(pp->unused_2);
        case FIELD_unused_3: return bool2string(pp->unused_3);
        default: return "";
    }
}

void Ospfv2OptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        case FIELD_unused_1: pp->unused_1 = string2bool(value); break;
        case FIELD_E_ExternalRoutingCapability: pp->E_ExternalRoutingCapability = string2bool(value); break;
        case FIELD_MC_MulticastForwarding: pp->MC_MulticastForwarding = string2bool(value); break;
        case FIELD_NP_Type7LSA: pp->NP_Type7LSA = string2bool(value); break;
        case FIELD_EA_ForwardExternalLSAs: pp->EA_ForwardExternalLSAs = string2bool(value); break;
        case FIELD_DC_DemandCircuits: pp->DC_DemandCircuits = string2bool(value); break;
        case FIELD_unused_2: pp->unused_2 = string2bool(value); break;
        case FIELD_unused_3: pp->unused_3 = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Options'", field);
    }
}

omnetpp::cValue Ospfv2OptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        case FIELD_unused_1: return pp->unused_1;
        case FIELD_E_ExternalRoutingCapability: return pp->E_ExternalRoutingCapability;
        case FIELD_MC_MulticastForwarding: return pp->MC_MulticastForwarding;
        case FIELD_NP_Type7LSA: return pp->NP_Type7LSA;
        case FIELD_EA_ForwardExternalLSAs: return pp->EA_ForwardExternalLSAs;
        case FIELD_DC_DemandCircuits: return pp->DC_DemandCircuits;
        case FIELD_unused_2: return pp->unused_2;
        case FIELD_unused_3: return pp->unused_3;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2Options' as cValue -- field index out of range?", field);
    }
}

void Ospfv2OptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        case FIELD_unused_1: pp->unused_1 = value.boolValue(); break;
        case FIELD_E_ExternalRoutingCapability: pp->E_ExternalRoutingCapability = value.boolValue(); break;
        case FIELD_MC_MulticastForwarding: pp->MC_MulticastForwarding = value.boolValue(); break;
        case FIELD_NP_Type7LSA: pp->NP_Type7LSA = value.boolValue(); break;
        case FIELD_EA_ForwardExternalLSAs: pp->EA_ForwardExternalLSAs = value.boolValue(); break;
        case FIELD_DC_DemandCircuits: pp->DC_DemandCircuits = value.boolValue(); break;
        case FIELD_unused_2: pp->unused_2 = value.boolValue(); break;
        case FIELD_unused_3: pp->unused_3 = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Options'", field);
    }
}

const char *Ospfv2OptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2OptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2OptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Options *pp = omnetpp::fromAnyPtr<Ospfv2Options>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Options'", field);
    }
}

Register_Class(Ospfv2Packet)

Ospfv2Packet::Ospfv2Packet() : ::inet::ospf::OspfPacketBase()
{
    this->setChunkLength(B(24));
    this->setVersion(2);

}

Ospfv2Packet::Ospfv2Packet(const Ospfv2Packet& other) : ::inet::ospf::OspfPacketBase(other)
{
    copy(other);
}

Ospfv2Packet::~Ospfv2Packet()
{
}

Ospfv2Packet& Ospfv2Packet::operator=(const Ospfv2Packet& other)
{
    if (this == &other) return *this;
    ::inet::ospf::OspfPacketBase::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2Packet::copy(const Ospfv2Packet& other)
{
    this->authenticationType = other.authenticationType;
    for (size_t i = 0; i < 8; i++) {
        this->authentication[i] = other.authentication[i];
    }
}

void Ospfv2Packet::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospf::OspfPacketBase::parsimPack(b);
    doParsimPacking(b,this->authenticationType);
    doParsimArrayPacking(b,this->authentication,8);
}

void Ospfv2Packet::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospf::OspfPacketBase::parsimUnpack(b);
    doParsimUnpacking(b,this->authenticationType);
    doParsimArrayUnpacking(b,this->authentication,8);
}

short Ospfv2Packet::getAuthenticationType() const
{
    return this->authenticationType;
}

void Ospfv2Packet::setAuthenticationType(short authenticationType)
{
    handleChange();
    this->authenticationType = authenticationType;
}

size_t Ospfv2Packet::getAuthenticationArraySize() const
{
    return 8;
}

char Ospfv2Packet::getAuthentication(size_t k) const
{
    if (k >= 8) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)8, (unsigned long)k);
    return this->authentication[k];
}

void Ospfv2Packet::setAuthentication(size_t k, char authentication)
{
    if (k >= 8) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)8, (unsigned long)k);
    handleChange();
    this->authentication[k] = authentication;
}

class Ospfv2PacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_authenticationType,
        FIELD_authentication,
    };
  public:
    Ospfv2PacketDescriptor();
    virtual ~Ospfv2PacketDescriptor();

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

Register_ClassDescriptor(Ospfv2PacketDescriptor)

Ospfv2PacketDescriptor::Ospfv2PacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2Packet)), "inet::ospf::OspfPacketBase")
{
    propertyNames = nullptr;
}

Ospfv2PacketDescriptor::~Ospfv2PacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2PacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2Packet *>(obj)!=nullptr;
}

const char **Ospfv2PacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2PacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2PacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv2PacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_authenticationType
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_authentication
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2PacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "authenticationType",
        "authentication",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv2PacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "authenticationType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "authentication") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2PacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_authenticationType
        "char",    // FIELD_authentication
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2PacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2PacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2PacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        case FIELD_authentication: return 8;
        default: return 0;
    }
}

void Ospfv2PacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2Packet'", field);
    }
}

const char *Ospfv2PacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2PacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        case FIELD_authenticationType: return long2string(pp->getAuthenticationType());
        case FIELD_authentication: return long2string(pp->getAuthentication(i));
        default: return "";
    }
}

void Ospfv2PacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        case FIELD_authenticationType: pp->setAuthenticationType(string2long(value)); break;
        case FIELD_authentication: pp->setAuthentication(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Packet'", field);
    }
}

omnetpp::cValue Ospfv2PacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        case FIELD_authenticationType: return pp->getAuthenticationType();
        case FIELD_authentication: return pp->getAuthentication(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2Packet' as cValue -- field index out of range?", field);
    }
}

void Ospfv2PacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        case FIELD_authenticationType: pp->setAuthenticationType(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_authentication: pp->setAuthentication(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Packet'", field);
    }
}

const char *Ospfv2PacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2PacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2PacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Packet *pp = omnetpp::fromAnyPtr<Ospfv2Packet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Packet'", field);
    }
}

Register_Class(Ospfv2HelloPacket)

Ospfv2HelloPacket::Ospfv2HelloPacket() : ::inet::ospfv2::Ospfv2Packet()
{
    this->setType(HELLO_PACKET);

}

Ospfv2HelloPacket::Ospfv2HelloPacket(const Ospfv2HelloPacket& other) : ::inet::ospfv2::Ospfv2Packet(other)
{
    copy(other);
}

Ospfv2HelloPacket::~Ospfv2HelloPacket()
{
    delete [] this->neighbor;
}

Ospfv2HelloPacket& Ospfv2HelloPacket::operator=(const Ospfv2HelloPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2HelloPacket::copy(const Ospfv2HelloPacket& other)
{
    this->networkMask = other.networkMask;
    this->helloInterval = other.helloInterval;
    this->options = other.options;
    this->routerPriority = other.routerPriority;
    this->routerDeadInterval = other.routerDeadInterval;
    this->designatedRouter = other.designatedRouter;
    this->backupDesignatedRouter = other.backupDesignatedRouter;
    delete [] this->neighbor;
    this->neighbor = (other.neighbor_arraysize==0) ? nullptr : new ::inet::Ipv4Address[other.neighbor_arraysize];
    neighbor_arraysize = other.neighbor_arraysize;
    for (size_t i = 0; i < neighbor_arraysize; i++) {
        this->neighbor[i] = other.neighbor[i];
    }
}

void Ospfv2HelloPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Packet::parsimPack(b);
    doParsimPacking(b,this->networkMask);
    doParsimPacking(b,this->helloInterval);
    doParsimPacking(b,this->options);
    doParsimPacking(b,this->routerPriority);
    doParsimPacking(b,this->routerDeadInterval);
    doParsimPacking(b,this->designatedRouter);
    doParsimPacking(b,this->backupDesignatedRouter);
    b->pack(neighbor_arraysize);
    doParsimArrayPacking(b,this->neighbor,neighbor_arraysize);
}

void Ospfv2HelloPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->networkMask);
    doParsimUnpacking(b,this->helloInterval);
    doParsimUnpacking(b,this->options);
    doParsimUnpacking(b,this->routerPriority);
    doParsimUnpacking(b,this->routerDeadInterval);
    doParsimUnpacking(b,this->designatedRouter);
    doParsimUnpacking(b,this->backupDesignatedRouter);
    delete [] this->neighbor;
    b->unpack(neighbor_arraysize);
    if (neighbor_arraysize == 0) {
        this->neighbor = nullptr;
    } else {
        this->neighbor = new ::inet::Ipv4Address[neighbor_arraysize];
        doParsimArrayUnpacking(b,this->neighbor,neighbor_arraysize);
    }
}

const ::inet::Ipv4Address& Ospfv2HelloPacket::getNetworkMask() const
{
    return this->networkMask;
}

void Ospfv2HelloPacket::setNetworkMask(const ::inet::Ipv4Address& networkMask)
{
    handleChange();
    this->networkMask = networkMask;
}

short Ospfv2HelloPacket::getHelloInterval() const
{
    return this->helloInterval;
}

void Ospfv2HelloPacket::setHelloInterval(short helloInterval)
{
    handleChange();
    this->helloInterval = helloInterval;
}

const Ospfv2Options& Ospfv2HelloPacket::getOptions() const
{
    return this->options;
}

void Ospfv2HelloPacket::setOptions(const Ospfv2Options& options)
{
    handleChange();
    this->options = options;
}

char Ospfv2HelloPacket::getRouterPriority() const
{
    return this->routerPriority;
}

void Ospfv2HelloPacket::setRouterPriority(char routerPriority)
{
    handleChange();
    this->routerPriority = routerPriority;
}

long Ospfv2HelloPacket::getRouterDeadInterval() const
{
    return this->routerDeadInterval;
}

void Ospfv2HelloPacket::setRouterDeadInterval(long routerDeadInterval)
{
    handleChange();
    this->routerDeadInterval = routerDeadInterval;
}

const ::inet::Ipv4Address& Ospfv2HelloPacket::getDesignatedRouter() const
{
    return this->designatedRouter;
}

void Ospfv2HelloPacket::setDesignatedRouter(const ::inet::Ipv4Address& designatedRouter)
{
    handleChange();
    this->designatedRouter = designatedRouter;
}

const ::inet::Ipv4Address& Ospfv2HelloPacket::getBackupDesignatedRouter() const
{
    return this->backupDesignatedRouter;
}

void Ospfv2HelloPacket::setBackupDesignatedRouter(const ::inet::Ipv4Address& backupDesignatedRouter)
{
    handleChange();
    this->backupDesignatedRouter = backupDesignatedRouter;
}

size_t Ospfv2HelloPacket::getNeighborArraySize() const
{
    return neighbor_arraysize;
}

const ::inet::Ipv4Address& Ospfv2HelloPacket::getNeighbor(size_t k) const
{
    if (k >= neighbor_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbor_arraysize, (unsigned long)k);
    return this->neighbor[k];
}

void Ospfv2HelloPacket::setNeighborArraySize(size_t newSize)
{
    handleChange();
    ::inet::Ipv4Address *neighbor2 = (newSize==0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t minSize = neighbor_arraysize < newSize ? neighbor_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighbor2[i] = this->neighbor[i];
    delete [] this->neighbor;
    this->neighbor = neighbor2;
    neighbor_arraysize = newSize;
}

void Ospfv2HelloPacket::setNeighbor(size_t k, const ::inet::Ipv4Address& neighbor)
{
    if (k >= neighbor_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbor_arraysize, (unsigned long)k);
    handleChange();
    this->neighbor[k] = neighbor;
}

void Ospfv2HelloPacket::insertNeighbor(size_t k, const ::inet::Ipv4Address& neighbor)
{
    if (k > neighbor_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbor_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighbor_arraysize + 1;
    ::inet::Ipv4Address *neighbor2 = new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighbor2[i] = this->neighbor[i];
    neighbor2[k] = neighbor;
    for (i = k + 1; i < newSize; i++)
        neighbor2[i] = this->neighbor[i-1];
    delete [] this->neighbor;
    this->neighbor = neighbor2;
    neighbor_arraysize = newSize;
}

void Ospfv2HelloPacket::appendNeighbor(const ::inet::Ipv4Address& neighbor)
{
    insertNeighbor(neighbor_arraysize, neighbor);
}

void Ospfv2HelloPacket::eraseNeighbor(size_t k)
{
    if (k >= neighbor_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbor_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighbor_arraysize - 1;
    ::inet::Ipv4Address *neighbor2 = (newSize == 0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighbor2[i] = this->neighbor[i];
    for (i = k; i < newSize; i++)
        neighbor2[i] = this->neighbor[i+1];
    delete [] this->neighbor;
    this->neighbor = neighbor2;
    neighbor_arraysize = newSize;
}

class Ospfv2HelloPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkMask,
        FIELD_helloInterval,
        FIELD_options,
        FIELD_routerPriority,
        FIELD_routerDeadInterval,
        FIELD_designatedRouter,
        FIELD_backupDesignatedRouter,
        FIELD_neighbor,
    };
  public:
    Ospfv2HelloPacketDescriptor();
    virtual ~Ospfv2HelloPacketDescriptor();

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

Register_ClassDescriptor(Ospfv2HelloPacketDescriptor)

Ospfv2HelloPacketDescriptor::Ospfv2HelloPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2HelloPacket)), "inet::ospfv2::Ospfv2Packet")
{
    propertyNames = nullptr;
}

Ospfv2HelloPacketDescriptor::~Ospfv2HelloPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2HelloPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2HelloPacket *>(obj)!=nullptr;
}

const char **Ospfv2HelloPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2HelloPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2HelloPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ospfv2HelloPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_networkMask
        FD_ISEDITABLE,    // FIELD_helloInterval
        FD_ISCOMPOUND,    // FIELD_options
        FD_ISEDITABLE,    // FIELD_routerPriority
        FD_ISEDITABLE,    // FIELD_routerDeadInterval
        0,    // FIELD_designatedRouter
        0,    // FIELD_backupDesignatedRouter
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_neighbor
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2HelloPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkMask",
        "helloInterval",
        "options",
        "routerPriority",
        "routerDeadInterval",
        "designatedRouter",
        "backupDesignatedRouter",
        "neighbor",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ospfv2HelloPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkMask") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "helloInterval") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "routerPriority") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "routerDeadInterval") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "designatedRouter") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "backupDesignatedRouter") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "neighbor") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2HelloPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_networkMask
        "short",    // FIELD_helloInterval
        "inet::ospfv2::Ospfv2Options",    // FIELD_options
        "char",    // FIELD_routerPriority
        "long",    // FIELD_routerDeadInterval
        "inet::Ipv4Address",    // FIELD_designatedRouter
        "inet::Ipv4Address",    // FIELD_backupDesignatedRouter
        "inet::Ipv4Address",    // FIELD_neighbor
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2HelloPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2HelloPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2HelloPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: return pp->getNeighborArraySize();
        default: return 0;
    }
}

void Ospfv2HelloPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: pp->setNeighborArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2HelloPacket'", field);
    }
}

const char *Ospfv2HelloPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2HelloPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return pp->getNetworkMask().str();
        case FIELD_helloInterval: return long2string(pp->getHelloInterval());
        case FIELD_options: return "";
        case FIELD_routerPriority: return long2string(pp->getRouterPriority());
        case FIELD_routerDeadInterval: return long2string(pp->getRouterDeadInterval());
        case FIELD_designatedRouter: return pp->getDesignatedRouter().str();
        case FIELD_backupDesignatedRouter: return pp->getBackupDesignatedRouter().str();
        case FIELD_neighbor: return pp->getNeighbor(i).str();
        default: return "";
    }
}

void Ospfv2HelloPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_helloInterval: pp->setHelloInterval(string2long(value)); break;
        case FIELD_routerPriority: pp->setRouterPriority(string2long(value)); break;
        case FIELD_routerDeadInterval: pp->setRouterDeadInterval(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2HelloPacket'", field);
    }
}

omnetpp::cValue Ospfv2HelloPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_helloInterval: return pp->getHelloInterval();
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_routerPriority: return pp->getRouterPriority();
        case FIELD_routerDeadInterval: return (omnetpp::intval_t)(pp->getRouterDeadInterval());
        case FIELD_designatedRouter: return omnetpp::toAnyPtr(&pp->getDesignatedRouter()); break;
        case FIELD_backupDesignatedRouter: return omnetpp::toAnyPtr(&pp->getBackupDesignatedRouter()); break;
        case FIELD_neighbor: return omnetpp::toAnyPtr(&pp->getNeighbor(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2HelloPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv2HelloPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_helloInterval: pp->setHelloInterval(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_routerPriority: pp->setRouterPriority(omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_routerDeadInterval: pp->setRouterDeadInterval(omnetpp::checked_int_cast<long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2HelloPacket'", field);
    }
}

const char *Ospfv2HelloPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ospfv2Options));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2HelloPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_designatedRouter: return omnetpp::toAnyPtr(&pp->getDesignatedRouter()); break;
        case FIELD_backupDesignatedRouter: return omnetpp::toAnyPtr(&pp->getBackupDesignatedRouter()); break;
        case FIELD_neighbor: return omnetpp::toAnyPtr(&pp->getNeighbor(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2HelloPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2HelloPacket *pp = omnetpp::fromAnyPtr<Ospfv2HelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2HelloPacket'", field);
    }
}

Register_Enum(inet::ospfv2::Ospfv2LsaType, (inet::ospfv2::Ospfv2LsaType::ROUTERLSA_TYPE, inet::ospfv2::Ospfv2LsaType::NETWORKLSA_TYPE, inet::ospfv2::Ospfv2LsaType::SUMMARYLSA_NETWORKS_TYPE, inet::ospfv2::Ospfv2LsaType::SUMMARYLSA_ASBOUNDARYROUTERS_TYPE, inet::ospfv2::Ospfv2LsaType::AS_EXTERNAL_LSA_TYPE));

Register_Class(Ospfv2LsaHeader)

Ospfv2LsaHeader::Ospfv2LsaHeader() : ::omnetpp::cObject()
{
}

Ospfv2LsaHeader::Ospfv2LsaHeader(const Ospfv2LsaHeader& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv2LsaHeader::~Ospfv2LsaHeader()
{
}

Ospfv2LsaHeader& Ospfv2LsaHeader::operator=(const Ospfv2LsaHeader& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2LsaHeader::copy(const Ospfv2LsaHeader& other)
{
    this->lsAge = other.lsAge;
    this->lsOptions = other.lsOptions;
    this->lsType = other.lsType;
    this->linkStateID = other.linkStateID;
    this->advertisingRouter = other.advertisingRouter;
    this->lsSequenceNumber = other.lsSequenceNumber;
    this->lsCrc = other.lsCrc;
    this->lsCrcMode = other.lsCrcMode;
    this->lsaLength = other.lsaLength;
}

void Ospfv2LsaHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->lsAge);
    doParsimPacking(b,this->lsOptions);
    doParsimPacking(b,this->lsType);
    doParsimPacking(b,this->linkStateID);
    doParsimPacking(b,this->advertisingRouter);
    doParsimPacking(b,this->lsSequenceNumber);
    doParsimPacking(b,this->lsCrc);
    doParsimPacking(b,this->lsCrcMode);
    doParsimPacking(b,this->lsaLength);
}

void Ospfv2LsaHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->lsAge);
    doParsimUnpacking(b,this->lsOptions);
    doParsimUnpacking(b,this->lsType);
    doParsimUnpacking(b,this->linkStateID);
    doParsimUnpacking(b,this->advertisingRouter);
    doParsimUnpacking(b,this->lsSequenceNumber);
    doParsimUnpacking(b,this->lsCrc);
    doParsimUnpacking(b,this->lsCrcMode);
    doParsimUnpacking(b,this->lsaLength);
}

unsigned short Ospfv2LsaHeader::getLsAge() const
{
    return this->lsAge;
}

void Ospfv2LsaHeader::setLsAge(unsigned short lsAge)
{
    this->lsAge = lsAge;
}

const Ospfv2Options& Ospfv2LsaHeader::getLsOptions() const
{
    return this->lsOptions;
}

void Ospfv2LsaHeader::setLsOptions(const Ospfv2Options& lsOptions)
{
    this->lsOptions = lsOptions;
}

Ospfv2LsaType Ospfv2LsaHeader::getLsType() const
{
    return this->lsType;
}

void Ospfv2LsaHeader::setLsType(Ospfv2LsaType lsType)
{
    this->lsType = lsType;
}

const ::inet::Ipv4Address& Ospfv2LsaHeader::getLinkStateID() const
{
    return this->linkStateID;
}

void Ospfv2LsaHeader::setLinkStateID(const ::inet::Ipv4Address& linkStateID)
{
    this->linkStateID = linkStateID;
}

const ::inet::Ipv4Address& Ospfv2LsaHeader::getAdvertisingRouter() const
{
    return this->advertisingRouter;
}

void Ospfv2LsaHeader::setAdvertisingRouter(const ::inet::Ipv4Address& advertisingRouter)
{
    this->advertisingRouter = advertisingRouter;
}

int32_t Ospfv2LsaHeader::getLsSequenceNumber() const
{
    return this->lsSequenceNumber;
}

void Ospfv2LsaHeader::setLsSequenceNumber(int32_t lsSequenceNumber)
{
    this->lsSequenceNumber = lsSequenceNumber;
}

uint16_t Ospfv2LsaHeader::getLsCrc() const
{
    return this->lsCrc;
}

void Ospfv2LsaHeader::setLsCrc(uint16_t lsCrc)
{
    this->lsCrc = lsCrc;
}

::inet::CrcMode Ospfv2LsaHeader::getLsCrcMode() const
{
    return this->lsCrcMode;
}

void Ospfv2LsaHeader::setLsCrcMode(::inet::CrcMode lsCrcMode)
{
    this->lsCrcMode = lsCrcMode;
}

uint16_t Ospfv2LsaHeader::getLsaLength() const
{
    return this->lsaLength;
}

void Ospfv2LsaHeader::setLsaLength(uint16_t lsaLength)
{
    this->lsaLength = lsaLength;
}

class Ospfv2LsaHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsAge,
        FIELD_lsOptions,
        FIELD_lsType,
        FIELD_linkStateID,
        FIELD_advertisingRouter,
        FIELD_lsSequenceNumber,
        FIELD_lsCrc,
        FIELD_lsCrcMode,
        FIELD_lsaLength,
    };
  public:
    Ospfv2LsaHeaderDescriptor();
    virtual ~Ospfv2LsaHeaderDescriptor();

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

Register_ClassDescriptor(Ospfv2LsaHeaderDescriptor)

Ospfv2LsaHeaderDescriptor::Ospfv2LsaHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2LsaHeader)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv2LsaHeaderDescriptor::~Ospfv2LsaHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LsaHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2LsaHeader *>(obj)!=nullptr;
}

const char **Ospfv2LsaHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LsaHeaderDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LsaHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ospfv2LsaHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsAge
        FD_ISCOMPOUND,    // FIELD_lsOptions
        0,    // FIELD_lsType
        0,    // FIELD_linkStateID
        0,    // FIELD_advertisingRouter
        FD_ISEDITABLE,    // FIELD_lsSequenceNumber
        FD_ISEDITABLE,    // FIELD_lsCrc
        FD_ISEDITABLE,    // FIELD_lsCrcMode
        FD_ISEDITABLE,    // FIELD_lsaLength
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2LsaHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsAge",
        "lsOptions",
        "lsType",
        "linkStateID",
        "advertisingRouter",
        "lsSequenceNumber",
        "lsCrc",
        "lsCrcMode",
        "lsaLength",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ospfv2LsaHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsAge") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lsOptions") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "lsType") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "linkStateID") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "advertisingRouter") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lsSequenceNumber") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "lsCrc") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "lsCrcMode") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "lsaLength") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LsaHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_lsAge
        "inet::ospfv2::Ospfv2Options",    // FIELD_lsOptions
        "inet::ospfv2::Ospfv2LsaType",    // FIELD_lsType
        "inet::Ipv4Address",    // FIELD_linkStateID
        "inet::Ipv4Address",    // FIELD_advertisingRouter
        "int32_t",    // FIELD_lsSequenceNumber
        "uint16_t",    // FIELD_lsCrc
        "inet::CrcMode",    // FIELD_lsCrcMode
        "uint16_t",    // FIELD_lsaLength
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LsaHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_lsCrcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ospfv2LsaHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType:
            if (!strcmp(propertyName, "enum")) return "inet::ospfv2::Ospfv2LsaType";
            return nullptr;
        case FIELD_lsCrcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ospfv2LsaHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2LsaHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2LsaHeader'", field);
    }
}

const char *Ospfv2LsaHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LsaHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsAge: return ulong2string(pp->getLsAge());
        case FIELD_lsOptions: return "";
        case FIELD_lsType: return enum2string(pp->getLsType(), "inet::ospfv2::Ospfv2LsaType");
        case FIELD_linkStateID: return pp->getLinkStateID().str();
        case FIELD_advertisingRouter: return pp->getAdvertisingRouter().str();
        case FIELD_lsSequenceNumber: return long2string(pp->getLsSequenceNumber());
        case FIELD_lsCrc: return ulong2string(pp->getLsCrc());
        case FIELD_lsCrcMode: return enum2string(pp->getLsCrcMode(), "inet::CrcMode");
        case FIELD_lsaLength: return ulong2string(pp->getLsaLength());
        default: return "";
    }
}

void Ospfv2LsaHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsAge: pp->setLsAge(string2ulong(value)); break;
        case FIELD_lsSequenceNumber: pp->setLsSequenceNumber(string2long(value)); break;
        case FIELD_lsCrc: pp->setLsCrc(string2ulong(value)); break;
        case FIELD_lsCrcMode: pp->setLsCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        case FIELD_lsaLength: pp->setLsaLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaHeader'", field);
    }
}

omnetpp::cValue Ospfv2LsaHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsAge: return (omnetpp::intval_t)(pp->getLsAge());
        case FIELD_lsOptions: return omnetpp::toAnyPtr(&pp->getLsOptions()); break;
        case FIELD_lsType: return static_cast<int>(pp->getLsType());
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->getLinkStateID()); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->getAdvertisingRouter()); break;
        case FIELD_lsSequenceNumber: return pp->getLsSequenceNumber();
        case FIELD_lsCrc: return (omnetpp::intval_t)(pp->getLsCrc());
        case FIELD_lsCrcMode: return static_cast<int>(pp->getLsCrcMode());
        case FIELD_lsaLength: return (omnetpp::intval_t)(pp->getLsaLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2LsaHeader' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LsaHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsAge: pp->setLsAge(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_lsSequenceNumber: pp->setLsSequenceNumber(omnetpp::checked_int_cast<int32_t>(value.intValue())); break;
        case FIELD_lsCrc: pp->setLsCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_lsCrcMode: pp->setLsCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        case FIELD_lsaLength: pp->setLsaLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaHeader'", field);
    }
}

const char *Ospfv2LsaHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsOptions: return omnetpp::opp_typename(typeid(Ospfv2Options));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LsaHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lsOptions: return omnetpp::toAnyPtr(&pp->getLsOptions()); break;
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->getLinkStateID()); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->getAdvertisingRouter()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LsaHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaHeader *pp = omnetpp::fromAnyPtr<Ospfv2LsaHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaHeader'", field);
    }
}

Register_Class(Ospfv2Lsa)

Ospfv2Lsa::Ospfv2Lsa() : ::omnetpp::cObject()
{
}

Ospfv2Lsa::Ospfv2Lsa(const Ospfv2Lsa& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv2Lsa::~Ospfv2Lsa()
{
}

Ospfv2Lsa& Ospfv2Lsa::operator=(const Ospfv2Lsa& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2Lsa::copy(const Ospfv2Lsa& other)
{
    this->header = other.header;
}

void Ospfv2Lsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->header);
}

void Ospfv2Lsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->header);
}

const Ospfv2LsaHeader& Ospfv2Lsa::getHeader() const
{
    return this->header;
}

void Ospfv2Lsa::setHeader(const Ospfv2LsaHeader& header)
{
    this->header = header;
}

class Ospfv2LsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_header,
    };
  public:
    Ospfv2LsaDescriptor();
    virtual ~Ospfv2LsaDescriptor();

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

Register_ClassDescriptor(Ospfv2LsaDescriptor)

Ospfv2LsaDescriptor::Ospfv2LsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2Lsa)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv2LsaDescriptor::~Ospfv2LsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2Lsa *>(obj)!=nullptr;
}

const char **Ospfv2LsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LsaDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv2LsaDescriptor::getFieldTypeFlags(int field) const
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

const char *Ospfv2LsaDescriptor::getFieldName(int field) const
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

int Ospfv2LsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "header") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv2::Ospfv2LsaHeader",    // FIELD_header
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2LsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2LsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2LsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2Lsa'", field);
    }
}

const char *Ospfv2LsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return pp->getHeader().str();
        default: return "";
    }
}

void Ospfv2LsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Lsa'", field);
    }
}

omnetpp::cValue Ospfv2LsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return omnetpp::toAnyPtr(&pp->getHeader()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2Lsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Lsa'", field);
    }
}

const char *Ospfv2LsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_header: return omnetpp::opp_typename(typeid(Ospfv2LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        case FIELD_header: return omnetpp::toAnyPtr(&pp->getHeader()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Lsa *pp = omnetpp::fromAnyPtr<Ospfv2Lsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Lsa'", field);
    }
}

Register_Enum(inet::ospfv2::LinkType, (inet::ospfv2::LinkType::POINTTOPOINT_LINK, inet::ospfv2::LinkType::TRANSIT_LINK, inet::ospfv2::LinkType::STUB_LINK, inet::ospfv2::LinkType::VIRTUAL_LINK));

Ospfv2TosData::Ospfv2TosData()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv2TosData& a)
{
    doParsimPacking(b,a.tos);
    doParsimPacking(b,a.tosMetric);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv2TosData& a)
{
    doParsimUnpacking(b,a.tos);
    doParsimUnpacking(b,a.tosMetric);
}

class Ospfv2TosDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tos,
        FIELD_tosMetric,
    };
  public:
    Ospfv2TosDataDescriptor();
    virtual ~Ospfv2TosDataDescriptor();

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

Register_ClassDescriptor(Ospfv2TosDataDescriptor)

Ospfv2TosDataDescriptor::Ospfv2TosDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2TosData)), "")
{
    propertyNames = nullptr;
}

Ospfv2TosDataDescriptor::~Ospfv2TosDataDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2TosDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2TosData *>(obj)!=nullptr;
}

const char **Ospfv2TosDataDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2TosDataDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2TosDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv2TosDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tos
        FD_ISEDITABLE,    // FIELD_tosMetric
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2TosDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tos",
        "tosMetric",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv2TosDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tos") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tosMetric") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2TosDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",    // FIELD_tos
        "unsigned long",    // FIELD_tosMetric
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2TosDataDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2TosDataDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2TosDataDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2TosDataDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2TosData'", field);
    }
}

const char *Ospfv2TosDataDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2TosDataDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return ulong2string(pp->tos);
        case FIELD_tosMetric: return ulong2string(pp->tosMetric);
        default: return "";
    }
}

void Ospfv2TosDataDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->tos = string2ulong(value); break;
        case FIELD_tosMetric: pp->tosMetric = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2TosData'", field);
    }
}

omnetpp::cValue Ospfv2TosDataDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return (omnetpp::intval_t)(pp->tos);
        case FIELD_tosMetric: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->tosMetric);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2TosData' as cValue -- field index out of range?", field);
    }
}

void Ospfv2TosDataDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->tos = omnetpp::checked_int_cast<unsigned char>(value.intValue()); break;
        case FIELD_tosMetric: pp->tosMetric = omnetpp::checked_int_cast<unsigned long>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2TosData'", field);
    }
}

const char *Ospfv2TosDataDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2TosDataDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2TosDataDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2TosData *pp = omnetpp::fromAnyPtr<Ospfv2TosData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2TosData'", field);
    }
}

Register_Class(Ospfv2Link)

Ospfv2Link::Ospfv2Link() : ::omnetpp::cObject()
{
}

Ospfv2Link::Ospfv2Link(const Ospfv2Link& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv2Link::~Ospfv2Link()
{
    delete [] this->tosData;
}

Ospfv2Link& Ospfv2Link::operator=(const Ospfv2Link& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2Link::copy(const Ospfv2Link& other)
{
    this->linkID = other.linkID;
    this->linkData = other.linkData;
    this->type = other.type;
    this->numberOfTOS = other.numberOfTOS;
    this->linkCost = other.linkCost;
    delete [] this->tosData;
    this->tosData = (other.tosData_arraysize==0) ? nullptr : new Ospfv2TosData[other.tosData_arraysize];
    tosData_arraysize = other.tosData_arraysize;
    for (size_t i = 0; i < tosData_arraysize; i++) {
        this->tosData[i] = other.tosData[i];
    }
}

void Ospfv2Link::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->linkID);
    doParsimPacking(b,this->linkData);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->numberOfTOS);
    doParsimPacking(b,this->linkCost);
    b->pack(tosData_arraysize);
    doParsimArrayPacking(b,this->tosData,tosData_arraysize);
}

void Ospfv2Link::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->linkID);
    doParsimUnpacking(b,this->linkData);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->numberOfTOS);
    doParsimUnpacking(b,this->linkCost);
    delete [] this->tosData;
    b->unpack(tosData_arraysize);
    if (tosData_arraysize == 0) {
        this->tosData = nullptr;
    } else {
        this->tosData = new Ospfv2TosData[tosData_arraysize];
        doParsimArrayUnpacking(b,this->tosData,tosData_arraysize);
    }
}

const ::inet::Ipv4Address& Ospfv2Link::getLinkID() const
{
    return this->linkID;
}

void Ospfv2Link::setLinkID(const ::inet::Ipv4Address& linkID)
{
    this->linkID = linkID;
}

unsigned long Ospfv2Link::getLinkData() const
{
    return this->linkData;
}

void Ospfv2Link::setLinkData(unsigned long linkData)
{
    this->linkData = linkData;
}

LinkType Ospfv2Link::getType() const
{
    return this->type;
}

void Ospfv2Link::setType(LinkType type)
{
    this->type = type;
}

unsigned char Ospfv2Link::getNumberOfTOS() const
{
    return this->numberOfTOS;
}

void Ospfv2Link::setNumberOfTOS(unsigned char numberOfTOS)
{
    this->numberOfTOS = numberOfTOS;
}

unsigned long Ospfv2Link::getLinkCost() const
{
    return this->linkCost;
}

void Ospfv2Link::setLinkCost(unsigned long linkCost)
{
    this->linkCost = linkCost;
}

size_t Ospfv2Link::getTosDataArraySize() const
{
    return tosData_arraysize;
}

const Ospfv2TosData& Ospfv2Link::getTosData(size_t k) const
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    return this->tosData[k];
}

void Ospfv2Link::setTosDataArraySize(size_t newSize)
{
    Ospfv2TosData *tosData2 = (newSize==0) ? nullptr : new Ospfv2TosData[newSize];
    size_t minSize = tosData_arraysize < newSize ? tosData_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        tosData2[i] = this->tosData[i];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

void Ospfv2Link::setTosData(size_t k, const Ospfv2TosData& tosData)
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    this->tosData[k] = tosData;
}

void Ospfv2Link::insertTosData(size_t k, const Ospfv2TosData& tosData)
{
    if (k > tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    size_t newSize = tosData_arraysize + 1;
    Ospfv2TosData *tosData2 = new Ospfv2TosData[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tosData2[i] = this->tosData[i];
    tosData2[k] = tosData;
    for (i = k + 1; i < newSize; i++)
        tosData2[i] = this->tosData[i-1];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

void Ospfv2Link::appendTosData(const Ospfv2TosData& tosData)
{
    insertTosData(tosData_arraysize, tosData);
}

void Ospfv2Link::eraseTosData(size_t k)
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    size_t newSize = tosData_arraysize - 1;
    Ospfv2TosData *tosData2 = (newSize == 0) ? nullptr : new Ospfv2TosData[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tosData2[i] = this->tosData[i];
    for (i = k; i < newSize; i++)
        tosData2[i] = this->tosData[i+1];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

class Ospfv2LinkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_linkID,
        FIELD_linkData,
        FIELD_type,
        FIELD_numberOfTOS,
        FIELD_linkCost,
        FIELD_tosData,
    };
  public:
    Ospfv2LinkDescriptor();
    virtual ~Ospfv2LinkDescriptor();

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

Register_ClassDescriptor(Ospfv2LinkDescriptor)

Ospfv2LinkDescriptor::Ospfv2LinkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2Link)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv2LinkDescriptor::~Ospfv2LinkDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LinkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2Link *>(obj)!=nullptr;
}

const char **Ospfv2LinkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LinkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LinkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int Ospfv2LinkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_linkID
        FD_ISEDITABLE,    // FIELD_linkData
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_numberOfTOS
        FD_ISEDITABLE,    // FIELD_linkCost
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_tosData
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2LinkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "linkID",
        "linkData",
        "type",
        "numberOfTOS",
        "linkCost",
        "tosData",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int Ospfv2LinkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "linkID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "linkData") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "numberOfTOS") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "linkCost") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "tosData") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LinkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_linkID
        "unsigned long",    // FIELD_linkData
        "inet::ospfv2::LinkType",    // FIELD_type
        "unsigned char",    // FIELD_numberOfTOS
        "unsigned long",    // FIELD_linkCost
        "inet::ospfv2::Ospfv2TosData",    // FIELD_tosData
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LinkDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2LinkDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::ospfv2::LinkType";
            return nullptr;
        default: return nullptr;
    }
}

int Ospfv2LinkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_tosData: return pp->getTosDataArraySize();
        default: return 0;
    }
}

void Ospfv2LinkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_tosData: pp->setTosDataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2Link'", field);
    }
}

const char *Ospfv2LinkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LinkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_linkID: return pp->getLinkID().str();
        case FIELD_linkData: return ulong2string(pp->getLinkData());
        case FIELD_type: return enum2string(pp->getType(), "inet::ospfv2::LinkType");
        case FIELD_numberOfTOS: return ulong2string(pp->getNumberOfTOS());
        case FIELD_linkCost: return ulong2string(pp->getLinkCost());
        case FIELD_tosData: return "";
        default: return "";
    }
}

void Ospfv2LinkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_linkData: pp->setLinkData(string2ulong(value)); break;
        case FIELD_numberOfTOS: pp->setNumberOfTOS(string2ulong(value)); break;
        case FIELD_linkCost: pp->setLinkCost(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Link'", field);
    }
}

omnetpp::cValue Ospfv2LinkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_linkID: return omnetpp::toAnyPtr(&pp->getLinkID()); break;
        case FIELD_linkData: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getLinkData());
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_numberOfTOS: return (omnetpp::intval_t)(pp->getNumberOfTOS());
        case FIELD_linkCost: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getLinkCost());
        case FIELD_tosData: return omnetpp::toAnyPtr(&pp->getTosData(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2Link' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LinkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_linkData: pp->setLinkData(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        case FIELD_numberOfTOS: pp->setNumberOfTOS(omnetpp::checked_int_cast<unsigned char>(value.intValue())); break;
        case FIELD_linkCost: pp->setLinkCost(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Link'", field);
    }
}

const char *Ospfv2LinkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tosData: return omnetpp::opp_typename(typeid(Ospfv2TosData));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LinkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        case FIELD_linkID: return omnetpp::toAnyPtr(&pp->getLinkID()); break;
        case FIELD_tosData: return omnetpp::toAnyPtr(&pp->getTosData(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LinkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2Link *pp = omnetpp::fromAnyPtr<Ospfv2Link>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2Link'", field);
    }
}

Register_Class(Ospfv2RouterLsa)

Ospfv2RouterLsa::Ospfv2RouterLsa() : ::inet::ospfv2::Ospfv2Lsa()
{
}

Ospfv2RouterLsa::Ospfv2RouterLsa(const Ospfv2RouterLsa& other) : ::inet::ospfv2::Ospfv2Lsa(other)
{
    copy(other);
}

Ospfv2RouterLsa::~Ospfv2RouterLsa()
{
    delete [] this->links;
}

Ospfv2RouterLsa& Ospfv2RouterLsa::operator=(const Ospfv2RouterLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2RouterLsa::copy(const Ospfv2RouterLsa& other)
{
    this->reserved1 = other.reserved1;
    this->V_VirtualLinkEndpoint = other.V_VirtualLinkEndpoint;
    this->E_ASBoundaryRouter = other.E_ASBoundaryRouter;
    this->B_AreaBorderRouter = other.B_AreaBorderRouter;
    this->reserved2 = other.reserved2;
    this->numberOfLinks = other.numberOfLinks;
    delete [] this->links;
    this->links = (other.links_arraysize==0) ? nullptr : new Ospfv2Link[other.links_arraysize];
    links_arraysize = other.links_arraysize;
    for (size_t i = 0; i < links_arraysize; i++) {
        this->links[i] = other.links[i];
    }
}

void Ospfv2RouterLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Lsa::parsimPack(b);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->V_VirtualLinkEndpoint);
    doParsimPacking(b,this->E_ASBoundaryRouter);
    doParsimPacking(b,this->B_AreaBorderRouter);
    doParsimPacking(b,this->reserved2);
    doParsimPacking(b,this->numberOfLinks);
    b->pack(links_arraysize);
    doParsimArrayPacking(b,this->links,links_arraysize);
}

void Ospfv2RouterLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->V_VirtualLinkEndpoint);
    doParsimUnpacking(b,this->E_ASBoundaryRouter);
    doParsimUnpacking(b,this->B_AreaBorderRouter);
    doParsimUnpacking(b,this->reserved2);
    doParsimUnpacking(b,this->numberOfLinks);
    delete [] this->links;
    b->unpack(links_arraysize);
    if (links_arraysize == 0) {
        this->links = nullptr;
    } else {
        this->links = new Ospfv2Link[links_arraysize];
        doParsimArrayUnpacking(b,this->links,links_arraysize);
    }
}

unsigned short Ospfv2RouterLsa::getReserved1() const
{
    return this->reserved1;
}

void Ospfv2RouterLsa::setReserved1(unsigned short reserved1)
{
    this->reserved1 = reserved1;
}

bool Ospfv2RouterLsa::getV_VirtualLinkEndpoint() const
{
    return this->V_VirtualLinkEndpoint;
}

void Ospfv2RouterLsa::setV_VirtualLinkEndpoint(bool V_VirtualLinkEndpoint)
{
    this->V_VirtualLinkEndpoint = V_VirtualLinkEndpoint;
}

bool Ospfv2RouterLsa::getE_ASBoundaryRouter() const
{
    return this->E_ASBoundaryRouter;
}

void Ospfv2RouterLsa::setE_ASBoundaryRouter(bool E_ASBoundaryRouter)
{
    this->E_ASBoundaryRouter = E_ASBoundaryRouter;
}

bool Ospfv2RouterLsa::getB_AreaBorderRouter() const
{
    return this->B_AreaBorderRouter;
}

void Ospfv2RouterLsa::setB_AreaBorderRouter(bool B_AreaBorderRouter)
{
    this->B_AreaBorderRouter = B_AreaBorderRouter;
}

unsigned short Ospfv2RouterLsa::getReserved2() const
{
    return this->reserved2;
}

void Ospfv2RouterLsa::setReserved2(unsigned short reserved2)
{
    this->reserved2 = reserved2;
}

unsigned short Ospfv2RouterLsa::getNumberOfLinks() const
{
    return this->numberOfLinks;
}

void Ospfv2RouterLsa::setNumberOfLinks(unsigned short numberOfLinks)
{
    this->numberOfLinks = numberOfLinks;
}

size_t Ospfv2RouterLsa::getLinksArraySize() const
{
    return links_arraysize;
}

const Ospfv2Link& Ospfv2RouterLsa::getLinks(size_t k) const
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    return this->links[k];
}

void Ospfv2RouterLsa::setLinksArraySize(size_t newSize)
{
    Ospfv2Link *links2 = (newSize==0) ? nullptr : new Ospfv2Link[newSize];
    size_t minSize = links_arraysize < newSize ? links_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        links2[i] = this->links[i];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

void Ospfv2RouterLsa::setLinks(size_t k, const Ospfv2Link& links)
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    this->links[k] = links;
}

void Ospfv2RouterLsa::insertLinks(size_t k, const Ospfv2Link& links)
{
    if (k > links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    size_t newSize = links_arraysize + 1;
    Ospfv2Link *links2 = new Ospfv2Link[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        links2[i] = this->links[i];
    links2[k] = links;
    for (i = k + 1; i < newSize; i++)
        links2[i] = this->links[i-1];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

void Ospfv2RouterLsa::appendLinks(const Ospfv2Link& links)
{
    insertLinks(links_arraysize, links);
}

void Ospfv2RouterLsa::eraseLinks(size_t k)
{
    if (k >= links_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)links_arraysize, (unsigned long)k);
    size_t newSize = links_arraysize - 1;
    Ospfv2Link *links2 = (newSize == 0) ? nullptr : new Ospfv2Link[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        links2[i] = this->links[i];
    for (i = k; i < newSize; i++)
        links2[i] = this->links[i+1];
    delete [] this->links;
    this->links = links2;
    links_arraysize = newSize;
}

class Ospfv2RouterLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_V_VirtualLinkEndpoint,
        FIELD_E_ASBoundaryRouter,
        FIELD_B_AreaBorderRouter,
        FIELD_reserved2,
        FIELD_numberOfLinks,
        FIELD_links,
    };
  public:
    Ospfv2RouterLsaDescriptor();
    virtual ~Ospfv2RouterLsaDescriptor();

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

Register_ClassDescriptor(Ospfv2RouterLsaDescriptor)

Ospfv2RouterLsaDescriptor::Ospfv2RouterLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2RouterLsa)), "inet::ospfv2::Ospfv2Lsa")
{
    propertyNames = nullptr;
}

Ospfv2RouterLsaDescriptor::~Ospfv2RouterLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2RouterLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2RouterLsa *>(obj)!=nullptr;
}

const char **Ospfv2RouterLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2RouterLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2RouterLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int Ospfv2RouterLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISEDITABLE,    // FIELD_V_VirtualLinkEndpoint
        FD_ISEDITABLE,    // FIELD_E_ASBoundaryRouter
        FD_ISEDITABLE,    // FIELD_B_AreaBorderRouter
        FD_ISEDITABLE,    // FIELD_reserved2
        FD_ISEDITABLE,    // FIELD_numberOfLinks
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_links
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2RouterLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "V_VirtualLinkEndpoint",
        "E_ASBoundaryRouter",
        "B_AreaBorderRouter",
        "reserved2",
        "numberOfLinks",
        "links",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ospfv2RouterLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "V_VirtualLinkEndpoint") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "E_ASBoundaryRouter") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "B_AreaBorderRouter") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "numberOfLinks") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "links") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2RouterLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_reserved1
        "bool",    // FIELD_V_VirtualLinkEndpoint
        "bool",    // FIELD_E_ASBoundaryRouter
        "bool",    // FIELD_B_AreaBorderRouter
        "unsigned short",    // FIELD_reserved2
        "unsigned short",    // FIELD_numberOfLinks
        "inet::ospfv2::Ospfv2Link",    // FIELD_links
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2RouterLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2RouterLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2RouterLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_links: return pp->getLinksArraySize();
        default: return 0;
    }
}

void Ospfv2RouterLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_links: pp->setLinksArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2RouterLsa'", field);
    }
}

const char *Ospfv2RouterLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2RouterLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return ulong2string(pp->getReserved1());
        case FIELD_V_VirtualLinkEndpoint: return bool2string(pp->getV_VirtualLinkEndpoint());
        case FIELD_E_ASBoundaryRouter: return bool2string(pp->getE_ASBoundaryRouter());
        case FIELD_B_AreaBorderRouter: return bool2string(pp->getB_AreaBorderRouter());
        case FIELD_reserved2: return ulong2string(pp->getReserved2());
        case FIELD_numberOfLinks: return ulong2string(pp->getNumberOfLinks());
        case FIELD_links: return pp->getLinks(i).str();
        default: return "";
    }
}

void Ospfv2RouterLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(string2ulong(value)); break;
        case FIELD_V_VirtualLinkEndpoint: pp->setV_VirtualLinkEndpoint(string2bool(value)); break;
        case FIELD_E_ASBoundaryRouter: pp->setE_ASBoundaryRouter(string2bool(value)); break;
        case FIELD_B_AreaBorderRouter: pp->setB_AreaBorderRouter(string2bool(value)); break;
        case FIELD_reserved2: pp->setReserved2(string2ulong(value)); break;
        case FIELD_numberOfLinks: pp->setNumberOfLinks(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2RouterLsa'", field);
    }
}

omnetpp::cValue Ospfv2RouterLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return (omnetpp::intval_t)(pp->getReserved1());
        case FIELD_V_VirtualLinkEndpoint: return pp->getV_VirtualLinkEndpoint();
        case FIELD_E_ASBoundaryRouter: return pp->getE_ASBoundaryRouter();
        case FIELD_B_AreaBorderRouter: return pp->getB_AreaBorderRouter();
        case FIELD_reserved2: return (omnetpp::intval_t)(pp->getReserved2());
        case FIELD_numberOfLinks: return (omnetpp::intval_t)(pp->getNumberOfLinks());
        case FIELD_links: return omnetpp::toAnyPtr(&pp->getLinks(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2RouterLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv2RouterLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: pp->setReserved1(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_V_VirtualLinkEndpoint: pp->setV_VirtualLinkEndpoint(value.boolValue()); break;
        case FIELD_E_ASBoundaryRouter: pp->setE_ASBoundaryRouter(value.boolValue()); break;
        case FIELD_B_AreaBorderRouter: pp->setB_AreaBorderRouter(value.boolValue()); break;
        case FIELD_reserved2: pp->setReserved2(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_numberOfLinks: pp->setNumberOfLinks(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2RouterLsa'", field);
    }
}

const char *Ospfv2RouterLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_links: return omnetpp::opp_typename(typeid(Ospfv2Link));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2RouterLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        case FIELD_links: return omnetpp::toAnyPtr(&pp->getLinks(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2RouterLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2RouterLsa *pp = omnetpp::fromAnyPtr<Ospfv2RouterLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2RouterLsa'", field);
    }
}

Register_Class(Ospfv2NetworkLsa)

Ospfv2NetworkLsa::Ospfv2NetworkLsa() : ::inet::ospfv2::Ospfv2Lsa()
{
}

Ospfv2NetworkLsa::Ospfv2NetworkLsa(const Ospfv2NetworkLsa& other) : ::inet::ospfv2::Ospfv2Lsa(other)
{
    copy(other);
}

Ospfv2NetworkLsa::~Ospfv2NetworkLsa()
{
    delete [] this->attachedRouters;
}

Ospfv2NetworkLsa& Ospfv2NetworkLsa::operator=(const Ospfv2NetworkLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2NetworkLsa::copy(const Ospfv2NetworkLsa& other)
{
    this->networkMask = other.networkMask;
    delete [] this->attachedRouters;
    this->attachedRouters = (other.attachedRouters_arraysize==0) ? nullptr : new ::inet::Ipv4Address[other.attachedRouters_arraysize];
    attachedRouters_arraysize = other.attachedRouters_arraysize;
    for (size_t i = 0; i < attachedRouters_arraysize; i++) {
        this->attachedRouters[i] = other.attachedRouters[i];
    }
}

void Ospfv2NetworkLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Lsa::parsimPack(b);
    doParsimPacking(b,this->networkMask);
    b->pack(attachedRouters_arraysize);
    doParsimArrayPacking(b,this->attachedRouters,attachedRouters_arraysize);
}

void Ospfv2NetworkLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->networkMask);
    delete [] this->attachedRouters;
    b->unpack(attachedRouters_arraysize);
    if (attachedRouters_arraysize == 0) {
        this->attachedRouters = nullptr;
    } else {
        this->attachedRouters = new ::inet::Ipv4Address[attachedRouters_arraysize];
        doParsimArrayUnpacking(b,this->attachedRouters,attachedRouters_arraysize);
    }
}

const ::inet::Ipv4Address& Ospfv2NetworkLsa::getNetworkMask() const
{
    return this->networkMask;
}

void Ospfv2NetworkLsa::setNetworkMask(const ::inet::Ipv4Address& networkMask)
{
    this->networkMask = networkMask;
}

size_t Ospfv2NetworkLsa::getAttachedRoutersArraySize() const
{
    return attachedRouters_arraysize;
}

const ::inet::Ipv4Address& Ospfv2NetworkLsa::getAttachedRouters(size_t k) const
{
    if (k >= attachedRouters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouters_arraysize, (unsigned long)k);
    return this->attachedRouters[k];
}

void Ospfv2NetworkLsa::setAttachedRoutersArraySize(size_t newSize)
{
    ::inet::Ipv4Address *attachedRouters2 = (newSize==0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t minSize = attachedRouters_arraysize < newSize ? attachedRouters_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        attachedRouters2[i] = this->attachedRouters[i];
    delete [] this->attachedRouters;
    this->attachedRouters = attachedRouters2;
    attachedRouters_arraysize = newSize;
}

void Ospfv2NetworkLsa::setAttachedRouters(size_t k, const ::inet::Ipv4Address& attachedRouters)
{
    if (k >= attachedRouters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouters_arraysize, (unsigned long)k);
    this->attachedRouters[k] = attachedRouters;
}

void Ospfv2NetworkLsa::insertAttachedRouters(size_t k, const ::inet::Ipv4Address& attachedRouters)
{
    if (k > attachedRouters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouters_arraysize, (unsigned long)k);
    size_t newSize = attachedRouters_arraysize + 1;
    ::inet::Ipv4Address *attachedRouters2 = new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        attachedRouters2[i] = this->attachedRouters[i];
    attachedRouters2[k] = attachedRouters;
    for (i = k + 1; i < newSize; i++)
        attachedRouters2[i] = this->attachedRouters[i-1];
    delete [] this->attachedRouters;
    this->attachedRouters = attachedRouters2;
    attachedRouters_arraysize = newSize;
}

void Ospfv2NetworkLsa::appendAttachedRouters(const ::inet::Ipv4Address& attachedRouters)
{
    insertAttachedRouters(attachedRouters_arraysize, attachedRouters);
}

void Ospfv2NetworkLsa::eraseAttachedRouters(size_t k)
{
    if (k >= attachedRouters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)attachedRouters_arraysize, (unsigned long)k);
    size_t newSize = attachedRouters_arraysize - 1;
    ::inet::Ipv4Address *attachedRouters2 = (newSize == 0) ? nullptr : new ::inet::Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        attachedRouters2[i] = this->attachedRouters[i];
    for (i = k; i < newSize; i++)
        attachedRouters2[i] = this->attachedRouters[i+1];
    delete [] this->attachedRouters;
    this->attachedRouters = attachedRouters2;
    attachedRouters_arraysize = newSize;
}

class Ospfv2NetworkLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkMask,
        FIELD_attachedRouters,
    };
  public:
    Ospfv2NetworkLsaDescriptor();
    virtual ~Ospfv2NetworkLsaDescriptor();

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

Register_ClassDescriptor(Ospfv2NetworkLsaDescriptor)

Ospfv2NetworkLsaDescriptor::Ospfv2NetworkLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2NetworkLsa)), "inet::ospfv2::Ospfv2Lsa")
{
    propertyNames = nullptr;
}

Ospfv2NetworkLsaDescriptor::~Ospfv2NetworkLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2NetworkLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2NetworkLsa *>(obj)!=nullptr;
}

const char **Ospfv2NetworkLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2NetworkLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2NetworkLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv2NetworkLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_networkMask
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_attachedRouters
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2NetworkLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkMask",
        "attachedRouters",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv2NetworkLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkMask") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "attachedRouters") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2NetworkLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_networkMask
        "inet::Ipv4Address",    // FIELD_attachedRouters
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2NetworkLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2NetworkLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2NetworkLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_attachedRouters: return pp->getAttachedRoutersArraySize();
        default: return 0;
    }
}

void Ospfv2NetworkLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_attachedRouters: pp->setAttachedRoutersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2NetworkLsa'", field);
    }
}

const char *Ospfv2NetworkLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2NetworkLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return pp->getNetworkMask().str();
        case FIELD_attachedRouters: return pp->getAttachedRouters(i).str();
        default: return "";
    }
}

void Ospfv2NetworkLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2NetworkLsa'", field);
    }
}

omnetpp::cValue Ospfv2NetworkLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_attachedRouters: return omnetpp::toAnyPtr(&pp->getAttachedRouters(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2NetworkLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv2NetworkLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2NetworkLsa'", field);
    }
}

const char *Ospfv2NetworkLsaDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2NetworkLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_attachedRouters: return omnetpp::toAnyPtr(&pp->getAttachedRouters(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2NetworkLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2NetworkLsa *pp = omnetpp::fromAnyPtr<Ospfv2NetworkLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2NetworkLsa'", field);
    }
}

Register_Class(Ospfv2SummaryLsa)

Ospfv2SummaryLsa::Ospfv2SummaryLsa() : ::inet::ospfv2::Ospfv2Lsa()
{
}

Ospfv2SummaryLsa::Ospfv2SummaryLsa(const Ospfv2SummaryLsa& other) : ::inet::ospfv2::Ospfv2Lsa(other)
{
    copy(other);
}

Ospfv2SummaryLsa::~Ospfv2SummaryLsa()
{
    delete [] this->tosData;
}

Ospfv2SummaryLsa& Ospfv2SummaryLsa::operator=(const Ospfv2SummaryLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2SummaryLsa::copy(const Ospfv2SummaryLsa& other)
{
    this->networkMask = other.networkMask;
    this->routeCost = other.routeCost;
    delete [] this->tosData;
    this->tosData = (other.tosData_arraysize==0) ? nullptr : new Ospfv2TosData[other.tosData_arraysize];
    tosData_arraysize = other.tosData_arraysize;
    for (size_t i = 0; i < tosData_arraysize; i++) {
        this->tosData[i] = other.tosData[i];
    }
}

void Ospfv2SummaryLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Lsa::parsimPack(b);
    doParsimPacking(b,this->networkMask);
    doParsimPacking(b,this->routeCost);
    b->pack(tosData_arraysize);
    doParsimArrayPacking(b,this->tosData,tosData_arraysize);
}

void Ospfv2SummaryLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->networkMask);
    doParsimUnpacking(b,this->routeCost);
    delete [] this->tosData;
    b->unpack(tosData_arraysize);
    if (tosData_arraysize == 0) {
        this->tosData = nullptr;
    } else {
        this->tosData = new Ospfv2TosData[tosData_arraysize];
        doParsimArrayUnpacking(b,this->tosData,tosData_arraysize);
    }
}

const ::inet::Ipv4Address& Ospfv2SummaryLsa::getNetworkMask() const
{
    return this->networkMask;
}

void Ospfv2SummaryLsa::setNetworkMask(const ::inet::Ipv4Address& networkMask)
{
    this->networkMask = networkMask;
}

unsigned long Ospfv2SummaryLsa::getRouteCost() const
{
    return this->routeCost;
}

void Ospfv2SummaryLsa::setRouteCost(unsigned long routeCost)
{
    this->routeCost = routeCost;
}

size_t Ospfv2SummaryLsa::getTosDataArraySize() const
{
    return tosData_arraysize;
}

const Ospfv2TosData& Ospfv2SummaryLsa::getTosData(size_t k) const
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    return this->tosData[k];
}

void Ospfv2SummaryLsa::setTosDataArraySize(size_t newSize)
{
    Ospfv2TosData *tosData2 = (newSize==0) ? nullptr : new Ospfv2TosData[newSize];
    size_t minSize = tosData_arraysize < newSize ? tosData_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        tosData2[i] = this->tosData[i];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

void Ospfv2SummaryLsa::setTosData(size_t k, const Ospfv2TosData& tosData)
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    this->tosData[k] = tosData;
}

void Ospfv2SummaryLsa::insertTosData(size_t k, const Ospfv2TosData& tosData)
{
    if (k > tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    size_t newSize = tosData_arraysize + 1;
    Ospfv2TosData *tosData2 = new Ospfv2TosData[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tosData2[i] = this->tosData[i];
    tosData2[k] = tosData;
    for (i = k + 1; i < newSize; i++)
        tosData2[i] = this->tosData[i-1];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

void Ospfv2SummaryLsa::appendTosData(const Ospfv2TosData& tosData)
{
    insertTosData(tosData_arraysize, tosData);
}

void Ospfv2SummaryLsa::eraseTosData(size_t k)
{
    if (k >= tosData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tosData_arraysize, (unsigned long)k);
    size_t newSize = tosData_arraysize - 1;
    Ospfv2TosData *tosData2 = (newSize == 0) ? nullptr : new Ospfv2TosData[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tosData2[i] = this->tosData[i];
    for (i = k; i < newSize; i++)
        tosData2[i] = this->tosData[i+1];
    delete [] this->tosData;
    this->tosData = tosData2;
    tosData_arraysize = newSize;
}

class Ospfv2SummaryLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkMask,
        FIELD_routeCost,
        FIELD_tosData,
    };
  public:
    Ospfv2SummaryLsaDescriptor();
    virtual ~Ospfv2SummaryLsaDescriptor();

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

Register_ClassDescriptor(Ospfv2SummaryLsaDescriptor)

Ospfv2SummaryLsaDescriptor::Ospfv2SummaryLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2SummaryLsa)), "inet::ospfv2::Ospfv2Lsa")
{
    propertyNames = nullptr;
}

Ospfv2SummaryLsaDescriptor::~Ospfv2SummaryLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2SummaryLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2SummaryLsa *>(obj)!=nullptr;
}

const char **Ospfv2SummaryLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2SummaryLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2SummaryLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ospfv2SummaryLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_networkMask
        FD_ISEDITABLE,    // FIELD_routeCost
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_tosData
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2SummaryLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkMask",
        "routeCost",
        "tosData",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ospfv2SummaryLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkMask") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "routeCost") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tosData") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2SummaryLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_networkMask
        "unsigned long",    // FIELD_routeCost
        "inet::ospfv2::Ospfv2TosData",    // FIELD_tosData
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2SummaryLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2SummaryLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2SummaryLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_tosData: return pp->getTosDataArraySize();
        default: return 0;
    }
}

void Ospfv2SummaryLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_tosData: pp->setTosDataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2SummaryLsa'", field);
    }
}

const char *Ospfv2SummaryLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2SummaryLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return pp->getNetworkMask().str();
        case FIELD_routeCost: return ulong2string(pp->getRouteCost());
        case FIELD_tosData: return "";
        default: return "";
    }
}

void Ospfv2SummaryLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routeCost: pp->setRouteCost(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2SummaryLsa'", field);
    }
}

omnetpp::cValue Ospfv2SummaryLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_routeCost: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getRouteCost());
        case FIELD_tosData: return omnetpp::toAnyPtr(&pp->getTosData(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2SummaryLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv2SummaryLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_routeCost: pp->setRouteCost(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2SummaryLsa'", field);
    }
}

const char *Ospfv2SummaryLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tosData: return omnetpp::opp_typename(typeid(Ospfv2TosData));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2SummaryLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_tosData: return omnetpp::toAnyPtr(&pp->getTosData(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2SummaryLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2SummaryLsa *pp = omnetpp::fromAnyPtr<Ospfv2SummaryLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2SummaryLsa'", field);
    }
}

Ospfv2ExternalTosInfo::Ospfv2ExternalTosInfo()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv2ExternalTosInfo& a)
{
    doParsimPacking(b,a.tos);
    doParsimPacking(b,a.E_ExternalMetricType);
    doParsimPacking(b,a.routeCost);
    doParsimPacking(b,a.forwardingAddress);
    doParsimPacking(b,a.externalRouteTag);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv2ExternalTosInfo& a)
{
    doParsimUnpacking(b,a.tos);
    doParsimUnpacking(b,a.E_ExternalMetricType);
    doParsimUnpacking(b,a.routeCost);
    doParsimUnpacking(b,a.forwardingAddress);
    doParsimUnpacking(b,a.externalRouteTag);
}

class Ospfv2ExternalTosInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tos,
        FIELD_E_ExternalMetricType,
        FIELD_routeCost,
        FIELD_forwardingAddress,
        FIELD_externalRouteTag,
    };
  public:
    Ospfv2ExternalTosInfoDescriptor();
    virtual ~Ospfv2ExternalTosInfoDescriptor();

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

Register_ClassDescriptor(Ospfv2ExternalTosInfoDescriptor)

Ospfv2ExternalTosInfoDescriptor::Ospfv2ExternalTosInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2ExternalTosInfo)), "")
{
    propertyNames = nullptr;
}

Ospfv2ExternalTosInfoDescriptor::~Ospfv2ExternalTosInfoDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2ExternalTosInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2ExternalTosInfo *>(obj)!=nullptr;
}

const char **Ospfv2ExternalTosInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2ExternalTosInfoDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2ExternalTosInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ospfv2ExternalTosInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tos
        FD_ISEDITABLE,    // FIELD_E_ExternalMetricType
        FD_ISEDITABLE,    // FIELD_routeCost
        0,    // FIELD_forwardingAddress
        FD_ISEDITABLE,    // FIELD_externalRouteTag
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2ExternalTosInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tos",
        "E_ExternalMetricType",
        "routeCost",
        "forwardingAddress",
        "externalRouteTag",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ospfv2ExternalTosInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tos") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "E_ExternalMetricType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "routeCost") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "forwardingAddress") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "externalRouteTag") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2ExternalTosInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_tos
        "bool",    // FIELD_E_ExternalMetricType
        "unsigned long",    // FIELD_routeCost
        "inet::Ipv4Address",    // FIELD_forwardingAddress
        "long",    // FIELD_externalRouteTag
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2ExternalTosInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2ExternalTosInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2ExternalTosInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2ExternalTosInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2ExternalTosInfo'", field);
    }
}

const char *Ospfv2ExternalTosInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2ExternalTosInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return ulong2string(pp->tos);
        case FIELD_E_ExternalMetricType: return bool2string(pp->E_ExternalMetricType);
        case FIELD_routeCost: return ulong2string(pp->routeCost);
        case FIELD_forwardingAddress: return pp->forwardingAddress.str();
        case FIELD_externalRouteTag: return long2string(pp->externalRouteTag);
        default: return "";
    }
}

void Ospfv2ExternalTosInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->tos = string2ulong(value); break;
        case FIELD_E_ExternalMetricType: pp->E_ExternalMetricType = string2bool(value); break;
        case FIELD_routeCost: pp->routeCost = string2ulong(value); break;
        case FIELD_externalRouteTag: pp->externalRouteTag = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2ExternalTosInfo'", field);
    }
}

omnetpp::cValue Ospfv2ExternalTosInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return (omnetpp::intval_t)(pp->tos);
        case FIELD_E_ExternalMetricType: return pp->E_ExternalMetricType;
        case FIELD_routeCost: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->routeCost);
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->forwardingAddress); break;
        case FIELD_externalRouteTag: return (omnetpp::intval_t)(pp->externalRouteTag);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2ExternalTosInfo' as cValue -- field index out of range?", field);
    }
}

void Ospfv2ExternalTosInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->tos = omnetpp::checked_int_cast<unsigned short>(value.intValue()); break;
        case FIELD_E_ExternalMetricType: pp->E_ExternalMetricType = value.boolValue(); break;
        case FIELD_routeCost: pp->routeCost = omnetpp::checked_int_cast<unsigned long>(value.intValue()); break;
        case FIELD_externalRouteTag: pp->externalRouteTag = omnetpp::checked_int_cast<long>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2ExternalTosInfo'", field);
    }
}

const char *Ospfv2ExternalTosInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2ExternalTosInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        case FIELD_forwardingAddress: return omnetpp::toAnyPtr(&pp->forwardingAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2ExternalTosInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2ExternalTosInfo *pp = omnetpp::fromAnyPtr<Ospfv2ExternalTosInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2ExternalTosInfo'", field);
    }
}

Register_Class(Ospfv2AsExternalLsaContents)

Ospfv2AsExternalLsaContents::Ospfv2AsExternalLsaContents() : ::omnetpp::cObject()
{
}

Ospfv2AsExternalLsaContents::Ospfv2AsExternalLsaContents(const Ospfv2AsExternalLsaContents& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ospfv2AsExternalLsaContents::~Ospfv2AsExternalLsaContents()
{
    delete [] this->externalTOSInfo;
}

Ospfv2AsExternalLsaContents& Ospfv2AsExternalLsaContents::operator=(const Ospfv2AsExternalLsaContents& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2AsExternalLsaContents::copy(const Ospfv2AsExternalLsaContents& other)
{
    this->networkMask = other.networkMask;
    delete [] this->externalTOSInfo;
    this->externalTOSInfo = (other.externalTOSInfo_arraysize==0) ? nullptr : new Ospfv2ExternalTosInfo[other.externalTOSInfo_arraysize];
    externalTOSInfo_arraysize = other.externalTOSInfo_arraysize;
    for (size_t i = 0; i < externalTOSInfo_arraysize; i++) {
        this->externalTOSInfo[i] = other.externalTOSInfo[i];
    }
}

void Ospfv2AsExternalLsaContents::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->networkMask);
    b->pack(externalTOSInfo_arraysize);
    doParsimArrayPacking(b,this->externalTOSInfo,externalTOSInfo_arraysize);
}

void Ospfv2AsExternalLsaContents::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->networkMask);
    delete [] this->externalTOSInfo;
    b->unpack(externalTOSInfo_arraysize);
    if (externalTOSInfo_arraysize == 0) {
        this->externalTOSInfo = nullptr;
    } else {
        this->externalTOSInfo = new Ospfv2ExternalTosInfo[externalTOSInfo_arraysize];
        doParsimArrayUnpacking(b,this->externalTOSInfo,externalTOSInfo_arraysize);
    }
}

const ::inet::Ipv4Address& Ospfv2AsExternalLsaContents::getNetworkMask() const
{
    return this->networkMask;
}

void Ospfv2AsExternalLsaContents::setNetworkMask(const ::inet::Ipv4Address& networkMask)
{
    this->networkMask = networkMask;
}

size_t Ospfv2AsExternalLsaContents::getExternalTOSInfoArraySize() const
{
    return externalTOSInfo_arraysize;
}

const Ospfv2ExternalTosInfo& Ospfv2AsExternalLsaContents::getExternalTOSInfo(size_t k) const
{
    if (k >= externalTOSInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)externalTOSInfo_arraysize, (unsigned long)k);
    return this->externalTOSInfo[k];
}

void Ospfv2AsExternalLsaContents::setExternalTOSInfoArraySize(size_t newSize)
{
    Ospfv2ExternalTosInfo *externalTOSInfo2 = (newSize==0) ? nullptr : new Ospfv2ExternalTosInfo[newSize];
    size_t minSize = externalTOSInfo_arraysize < newSize ? externalTOSInfo_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        externalTOSInfo2[i] = this->externalTOSInfo[i];
    delete [] this->externalTOSInfo;
    this->externalTOSInfo = externalTOSInfo2;
    externalTOSInfo_arraysize = newSize;
}

void Ospfv2AsExternalLsaContents::setExternalTOSInfo(size_t k, const Ospfv2ExternalTosInfo& externalTOSInfo)
{
    if (k >= externalTOSInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)externalTOSInfo_arraysize, (unsigned long)k);
    this->externalTOSInfo[k] = externalTOSInfo;
}

void Ospfv2AsExternalLsaContents::insertExternalTOSInfo(size_t k, const Ospfv2ExternalTosInfo& externalTOSInfo)
{
    if (k > externalTOSInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)externalTOSInfo_arraysize, (unsigned long)k);
    size_t newSize = externalTOSInfo_arraysize + 1;
    Ospfv2ExternalTosInfo *externalTOSInfo2 = new Ospfv2ExternalTosInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        externalTOSInfo2[i] = this->externalTOSInfo[i];
    externalTOSInfo2[k] = externalTOSInfo;
    for (i = k + 1; i < newSize; i++)
        externalTOSInfo2[i] = this->externalTOSInfo[i-1];
    delete [] this->externalTOSInfo;
    this->externalTOSInfo = externalTOSInfo2;
    externalTOSInfo_arraysize = newSize;
}

void Ospfv2AsExternalLsaContents::appendExternalTOSInfo(const Ospfv2ExternalTosInfo& externalTOSInfo)
{
    insertExternalTOSInfo(externalTOSInfo_arraysize, externalTOSInfo);
}

void Ospfv2AsExternalLsaContents::eraseExternalTOSInfo(size_t k)
{
    if (k >= externalTOSInfo_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)externalTOSInfo_arraysize, (unsigned long)k);
    size_t newSize = externalTOSInfo_arraysize - 1;
    Ospfv2ExternalTosInfo *externalTOSInfo2 = (newSize == 0) ? nullptr : new Ospfv2ExternalTosInfo[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        externalTOSInfo2[i] = this->externalTOSInfo[i];
    for (i = k; i < newSize; i++)
        externalTOSInfo2[i] = this->externalTOSInfo[i+1];
    delete [] this->externalTOSInfo;
    this->externalTOSInfo = externalTOSInfo2;
    externalTOSInfo_arraysize = newSize;
}

class Ospfv2AsExternalLsaContentsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkMask,
        FIELD_externalTOSInfo,
    };
  public:
    Ospfv2AsExternalLsaContentsDescriptor();
    virtual ~Ospfv2AsExternalLsaContentsDescriptor();

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

Register_ClassDescriptor(Ospfv2AsExternalLsaContentsDescriptor)

Ospfv2AsExternalLsaContentsDescriptor::Ospfv2AsExternalLsaContentsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2AsExternalLsaContents)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ospfv2AsExternalLsaContentsDescriptor::~Ospfv2AsExternalLsaContentsDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2AsExternalLsaContentsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2AsExternalLsaContents *>(obj)!=nullptr;
}

const char **Ospfv2AsExternalLsaContentsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2AsExternalLsaContentsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2AsExternalLsaContentsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ospfv2AsExternalLsaContentsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_networkMask
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_externalTOSInfo
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2AsExternalLsaContentsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkMask",
        "externalTOSInfo",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ospfv2AsExternalLsaContentsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkMask") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "externalTOSInfo") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2AsExternalLsaContentsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_networkMask
        "inet::ospfv2::Ospfv2ExternalTosInfo",    // FIELD_externalTOSInfo
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2AsExternalLsaContentsDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2AsExternalLsaContentsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2AsExternalLsaContentsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        case FIELD_externalTOSInfo: return pp->getExternalTOSInfoArraySize();
        default: return 0;
    }
}

void Ospfv2AsExternalLsaContentsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        case FIELD_externalTOSInfo: pp->setExternalTOSInfoArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2AsExternalLsaContents'", field);
    }
}

const char *Ospfv2AsExternalLsaContentsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2AsExternalLsaContentsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return pp->getNetworkMask().str();
        case FIELD_externalTOSInfo: return "";
        default: return "";
    }
}

void Ospfv2AsExternalLsaContentsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsaContents'", field);
    }
}

omnetpp::cValue Ospfv2AsExternalLsaContentsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_externalTOSInfo: return omnetpp::toAnyPtr(&pp->getExternalTOSInfo(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2AsExternalLsaContents' as cValue -- field index out of range?", field);
    }
}

void Ospfv2AsExternalLsaContentsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsaContents'", field);
    }
}

const char *Ospfv2AsExternalLsaContentsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_externalTOSInfo: return omnetpp::opp_typename(typeid(Ospfv2ExternalTosInfo));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2AsExternalLsaContentsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        case FIELD_networkMask: return omnetpp::toAnyPtr(&pp->getNetworkMask()); break;
        case FIELD_externalTOSInfo: return omnetpp::toAnyPtr(&pp->getExternalTOSInfo(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2AsExternalLsaContentsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsaContents *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsaContents>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsaContents'", field);
    }
}

Register_Class(Ospfv2AsExternalLsa)

Ospfv2AsExternalLsa::Ospfv2AsExternalLsa() : ::inet::ospfv2::Ospfv2Lsa()
{
}

Ospfv2AsExternalLsa::Ospfv2AsExternalLsa(const Ospfv2AsExternalLsa& other) : ::inet::ospfv2::Ospfv2Lsa(other)
{
    copy(other);
}

Ospfv2AsExternalLsa::~Ospfv2AsExternalLsa()
{
}

Ospfv2AsExternalLsa& Ospfv2AsExternalLsa::operator=(const Ospfv2AsExternalLsa& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Lsa::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2AsExternalLsa::copy(const Ospfv2AsExternalLsa& other)
{
    this->contents = other.contents;
}

void Ospfv2AsExternalLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Lsa::parsimPack(b);
    doParsimPacking(b,this->contents);
}

void Ospfv2AsExternalLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Lsa::parsimUnpack(b);
    doParsimUnpacking(b,this->contents);
}

const Ospfv2AsExternalLsaContents& Ospfv2AsExternalLsa::getContents() const
{
    return this->contents;
}

void Ospfv2AsExternalLsa::setContents(const Ospfv2AsExternalLsaContents& contents)
{
    this->contents = contents;
}

class Ospfv2AsExternalLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_contents,
    };
  public:
    Ospfv2AsExternalLsaDescriptor();
    virtual ~Ospfv2AsExternalLsaDescriptor();

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

Register_ClassDescriptor(Ospfv2AsExternalLsaDescriptor)

Ospfv2AsExternalLsaDescriptor::Ospfv2AsExternalLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2AsExternalLsa)), "inet::ospfv2::Ospfv2Lsa")
{
    propertyNames = nullptr;
}

Ospfv2AsExternalLsaDescriptor::~Ospfv2AsExternalLsaDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2AsExternalLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2AsExternalLsa *>(obj)!=nullptr;
}

const char **Ospfv2AsExternalLsaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2AsExternalLsaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2AsExternalLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv2AsExternalLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_contents
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2AsExternalLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "contents",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ospfv2AsExternalLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "contents") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2AsExternalLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv2::Ospfv2AsExternalLsaContents",    // FIELD_contents
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2AsExternalLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2AsExternalLsaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2AsExternalLsaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2AsExternalLsaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2AsExternalLsa'", field);
    }
}

const char *Ospfv2AsExternalLsaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2AsExternalLsaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_contents: return pp->getContents().str();
        default: return "";
    }
}

void Ospfv2AsExternalLsaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsa'", field);
    }
}

omnetpp::cValue Ospfv2AsExternalLsaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_contents: return omnetpp::toAnyPtr(&pp->getContents()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2AsExternalLsa' as cValue -- field index out of range?", field);
    }
}

void Ospfv2AsExternalLsaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsa'", field);
    }
}

const char *Ospfv2AsExternalLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_contents: return omnetpp::opp_typename(typeid(Ospfv2AsExternalLsaContents));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2AsExternalLsaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        case FIELD_contents: return omnetpp::toAnyPtr(&pp->getContents()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2AsExternalLsaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2AsExternalLsa *pp = omnetpp::fromAnyPtr<Ospfv2AsExternalLsa>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2AsExternalLsa'", field);
    }
}

Ospfv2DdOptions::Ospfv2DdOptions()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv2DdOptions& a)
{
    doParsimPacking(b,a.unused);
    doParsimPacking(b,a.I_Init);
    doParsimPacking(b,a.M_More);
    doParsimPacking(b,a.MS_MasterSlave);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv2DdOptions& a)
{
    doParsimUnpacking(b,a.unused);
    doParsimUnpacking(b,a.I_Init);
    doParsimUnpacking(b,a.M_More);
    doParsimUnpacking(b,a.MS_MasterSlave);
}

class Ospfv2DdOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unused,
        FIELD_I_Init,
        FIELD_M_More,
        FIELD_MS_MasterSlave,
    };
  public:
    Ospfv2DdOptionsDescriptor();
    virtual ~Ospfv2DdOptionsDescriptor();

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

Register_ClassDescriptor(Ospfv2DdOptionsDescriptor)

Ospfv2DdOptionsDescriptor::Ospfv2DdOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2DdOptions)), "")
{
    propertyNames = nullptr;
}

Ospfv2DdOptionsDescriptor::~Ospfv2DdOptionsDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2DdOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2DdOptions *>(obj)!=nullptr;
}

const char **Ospfv2DdOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2DdOptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2DdOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ospfv2DdOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_unused
        FD_ISEDITABLE,    // FIELD_I_Init
        FD_ISEDITABLE,    // FIELD_M_More
        FD_ISEDITABLE,    // FIELD_MS_MasterSlave
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2DdOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unused",
        "I_Init",
        "M_More",
        "MS_MasterSlave",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ospfv2DdOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unused") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "I_Init") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "M_More") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "MS_MasterSlave") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2DdOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_unused
        "bool",    // FIELD_I_Init
        "bool",    // FIELD_M_More
        "bool",    // FIELD_MS_MasterSlave
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2DdOptionsDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2DdOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2DdOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2DdOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2DdOptions'", field);
    }
}

const char *Ospfv2DdOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2DdOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return ulong2string(pp->unused);
        case FIELD_I_Init: return bool2string(pp->I_Init);
        case FIELD_M_More: return bool2string(pp->M_More);
        case FIELD_MS_MasterSlave: return bool2string(pp->MS_MasterSlave);
        default: return "";
    }
}

void Ospfv2DdOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->unused = string2ulong(value); break;
        case FIELD_I_Init: pp->I_Init = string2bool(value); break;
        case FIELD_M_More: pp->M_More = string2bool(value); break;
        case FIELD_MS_MasterSlave: pp->MS_MasterSlave = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DdOptions'", field);
    }
}

omnetpp::cValue Ospfv2DdOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return (omnetpp::intval_t)(pp->unused);
        case FIELD_I_Init: return pp->I_Init;
        case FIELD_M_More: return pp->M_More;
        case FIELD_MS_MasterSlave: return pp->MS_MasterSlave;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2DdOptions' as cValue -- field index out of range?", field);
    }
}

void Ospfv2DdOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->unused = omnetpp::checked_int_cast<unsigned short>(value.intValue()); break;
        case FIELD_I_Init: pp->I_Init = value.boolValue(); break;
        case FIELD_M_More: pp->M_More = value.boolValue(); break;
        case FIELD_MS_MasterSlave: pp->MS_MasterSlave = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DdOptions'", field);
    }
}

const char *Ospfv2DdOptionsDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2DdOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2DdOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DdOptions *pp = omnetpp::fromAnyPtr<Ospfv2DdOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DdOptions'", field);
    }
}

Register_Class(Ospfv2DatabaseDescriptionPacket)

Ospfv2DatabaseDescriptionPacket::Ospfv2DatabaseDescriptionPacket() : ::inet::ospfv2::Ospfv2Packet()
{
}

Ospfv2DatabaseDescriptionPacket::Ospfv2DatabaseDescriptionPacket(const Ospfv2DatabaseDescriptionPacket& other) : ::inet::ospfv2::Ospfv2Packet(other)
{
    copy(other);
}

Ospfv2DatabaseDescriptionPacket::~Ospfv2DatabaseDescriptionPacket()
{
    delete [] this->lsaHeaders;
}

Ospfv2DatabaseDescriptionPacket& Ospfv2DatabaseDescriptionPacket::operator=(const Ospfv2DatabaseDescriptionPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2DatabaseDescriptionPacket::copy(const Ospfv2DatabaseDescriptionPacket& other)
{
    this->interfaceMTU = other.interfaceMTU;
    this->options = other.options;
    this->ddOptions = other.ddOptions;
    this->ddSequenceNumber = other.ddSequenceNumber;
    delete [] this->lsaHeaders;
    this->lsaHeaders = (other.lsaHeaders_arraysize==0) ? nullptr : new Ospfv2LsaHeader[other.lsaHeaders_arraysize];
    lsaHeaders_arraysize = other.lsaHeaders_arraysize;
    for (size_t i = 0; i < lsaHeaders_arraysize; i++) {
        this->lsaHeaders[i] = other.lsaHeaders[i];
    }
}

void Ospfv2DatabaseDescriptionPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Packet::parsimPack(b);
    doParsimPacking(b,this->interfaceMTU);
    doParsimPacking(b,this->options);
    doParsimPacking(b,this->ddOptions);
    doParsimPacking(b,this->ddSequenceNumber);
    b->pack(lsaHeaders_arraysize);
    doParsimArrayPacking(b,this->lsaHeaders,lsaHeaders_arraysize);
}

void Ospfv2DatabaseDescriptionPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Packet::parsimUnpack(b);
    doParsimUnpacking(b,this->interfaceMTU);
    doParsimUnpacking(b,this->options);
    doParsimUnpacking(b,this->ddOptions);
    doParsimUnpacking(b,this->ddSequenceNumber);
    delete [] this->lsaHeaders;
    b->unpack(lsaHeaders_arraysize);
    if (lsaHeaders_arraysize == 0) {
        this->lsaHeaders = nullptr;
    } else {
        this->lsaHeaders = new Ospfv2LsaHeader[lsaHeaders_arraysize];
        doParsimArrayUnpacking(b,this->lsaHeaders,lsaHeaders_arraysize);
    }
}

unsigned short Ospfv2DatabaseDescriptionPacket::getInterfaceMTU() const
{
    return this->interfaceMTU;
}

void Ospfv2DatabaseDescriptionPacket::setInterfaceMTU(unsigned short interfaceMTU)
{
    handleChange();
    this->interfaceMTU = interfaceMTU;
}

const Ospfv2Options& Ospfv2DatabaseDescriptionPacket::getOptions() const
{
    return this->options;
}

void Ospfv2DatabaseDescriptionPacket::setOptions(const Ospfv2Options& options)
{
    handleChange();
    this->options = options;
}

const Ospfv2DdOptions& Ospfv2DatabaseDescriptionPacket::getDdOptions() const
{
    return this->ddOptions;
}

void Ospfv2DatabaseDescriptionPacket::setDdOptions(const Ospfv2DdOptions& ddOptions)
{
    handleChange();
    this->ddOptions = ddOptions;
}

unsigned long Ospfv2DatabaseDescriptionPacket::getDdSequenceNumber() const
{
    return this->ddSequenceNumber;
}

void Ospfv2DatabaseDescriptionPacket::setDdSequenceNumber(unsigned long ddSequenceNumber)
{
    handleChange();
    this->ddSequenceNumber = ddSequenceNumber;
}

size_t Ospfv2DatabaseDescriptionPacket::getLsaHeadersArraySize() const
{
    return lsaHeaders_arraysize;
}

const Ospfv2LsaHeader& Ospfv2DatabaseDescriptionPacket::getLsaHeaders(size_t k) const
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    return this->lsaHeaders[k];
}

void Ospfv2DatabaseDescriptionPacket::setLsaHeadersArraySize(size_t newSize)
{
    handleChange();
    Ospfv2LsaHeader *lsaHeaders2 = (newSize==0) ? nullptr : new Ospfv2LsaHeader[newSize];
    size_t minSize = lsaHeaders_arraysize < newSize ? lsaHeaders_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv2DatabaseDescriptionPacket::setLsaHeaders(size_t k, const Ospfv2LsaHeader& lsaHeaders)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    this->lsaHeaders[k] = lsaHeaders;
}

void Ospfv2DatabaseDescriptionPacket::insertLsaHeaders(size_t k, const Ospfv2LsaHeader& lsaHeaders)
{
    if (k > lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize + 1;
    Ospfv2LsaHeader *lsaHeaders2 = new Ospfv2LsaHeader[newSize];
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

void Ospfv2DatabaseDescriptionPacket::appendLsaHeaders(const Ospfv2LsaHeader& lsaHeaders)
{
    insertLsaHeaders(lsaHeaders_arraysize, lsaHeaders);
}

void Ospfv2DatabaseDescriptionPacket::eraseLsaHeaders(size_t k)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize - 1;
    Ospfv2LsaHeader *lsaHeaders2 = (newSize == 0) ? nullptr : new Ospfv2LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    for (i = k; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i+1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

class Ospfv2DatabaseDescriptionPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_interfaceMTU,
        FIELD_options,
        FIELD_ddOptions,
        FIELD_ddSequenceNumber,
        FIELD_lsaHeaders,
    };
  public:
    Ospfv2DatabaseDescriptionPacketDescriptor();
    virtual ~Ospfv2DatabaseDescriptionPacketDescriptor();

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

Register_ClassDescriptor(Ospfv2DatabaseDescriptionPacketDescriptor)

Ospfv2DatabaseDescriptionPacketDescriptor::Ospfv2DatabaseDescriptionPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2DatabaseDescriptionPacket)), "inet::ospfv2::Ospfv2Packet")
{
    propertyNames = nullptr;
}

Ospfv2DatabaseDescriptionPacketDescriptor::~Ospfv2DatabaseDescriptionPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2DatabaseDescriptionPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2DatabaseDescriptionPacket *>(obj)!=nullptr;
}

const char **Ospfv2DatabaseDescriptionPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2DatabaseDescriptionPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ospfv2DatabaseDescriptionPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_interfaceMTU
        FD_ISCOMPOUND,    // FIELD_options
        FD_ISCOMPOUND,    // FIELD_ddOptions
        FD_ISEDITABLE,    // FIELD_ddSequenceNumber
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interfaceMTU",
        "options",
        "ddOptions",
        "ddSequenceNumber",
        "lsaHeaders",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ospfv2DatabaseDescriptionPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "interfaceMTU") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ddOptions") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ddSequenceNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "lsaHeaders") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_interfaceMTU
        "inet::ospfv2::Ospfv2Options",    // FIELD_options
        "inet::ospfv2::Ospfv2DdOptions",    // FIELD_ddOptions
        "unsigned long",    // FIELD_ddSequenceNumber
        "inet::ospfv2::Ospfv2LsaHeader",    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2DatabaseDescriptionPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2DatabaseDescriptionPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeadersArraySize();
        default: return 0;
    }
}

void Ospfv2DatabaseDescriptionPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: pp->setLsaHeadersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2DatabaseDescriptionPacket'", field);
    }
}

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2DatabaseDescriptionPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceMTU: return ulong2string(pp->getInterfaceMTU());
        case FIELD_options: return "";
        case FIELD_ddOptions: return "";
        case FIELD_ddSequenceNumber: return ulong2string(pp->getDdSequenceNumber());
        case FIELD_lsaHeaders: return pp->getLsaHeaders(i).str();
        default: return "";
    }
}

void Ospfv2DatabaseDescriptionPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceMTU: pp->setInterfaceMTU(string2ulong(value)); break;
        case FIELD_ddSequenceNumber: pp->setDdSequenceNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DatabaseDescriptionPacket'", field);
    }
}

omnetpp::cValue Ospfv2DatabaseDescriptionPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceMTU: return (omnetpp::intval_t)(pp->getInterfaceMTU());
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_ddOptions: return omnetpp::toAnyPtr(&pp->getDdOptions()); break;
        case FIELD_ddSequenceNumber: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->getDdSequenceNumber());
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2DatabaseDescriptionPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv2DatabaseDescriptionPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceMTU: pp->setInterfaceMTU(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_ddSequenceNumber: pp->setDdSequenceNumber(omnetpp::checked_int_cast<unsigned long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DatabaseDescriptionPacket'", field);
    }
}

const char *Ospfv2DatabaseDescriptionPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ospfv2Options));
        case FIELD_ddOptions: return omnetpp::opp_typename(typeid(Ospfv2DdOptions));
        case FIELD_lsaHeaders: return omnetpp::opp_typename(typeid(Ospfv2LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2DatabaseDescriptionPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        case FIELD_ddOptions: return omnetpp::toAnyPtr(&pp->getDdOptions()); break;
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2DatabaseDescriptionPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2DatabaseDescriptionPacket *pp = omnetpp::fromAnyPtr<Ospfv2DatabaseDescriptionPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2DatabaseDescriptionPacket'", field);
    }
}

Ospfv2LsaRequest::Ospfv2LsaRequest()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ospfv2LsaRequest& a)
{
    doParsimPacking(b,a.lsType);
    doParsimPacking(b,a.linkStateID);
    doParsimPacking(b,a.advertisingRouter);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ospfv2LsaRequest& a)
{
    doParsimUnpacking(b,a.lsType);
    doParsimUnpacking(b,a.linkStateID);
    doParsimUnpacking(b,a.advertisingRouter);
}

class Ospfv2LsaRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsType,
        FIELD_linkStateID,
        FIELD_advertisingRouter,
    };
  public:
    Ospfv2LsaRequestDescriptor();
    virtual ~Ospfv2LsaRequestDescriptor();

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

Register_ClassDescriptor(Ospfv2LsaRequestDescriptor)

Ospfv2LsaRequestDescriptor::Ospfv2LsaRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2LsaRequest)), "")
{
    propertyNames = nullptr;
}

Ospfv2LsaRequestDescriptor::~Ospfv2LsaRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LsaRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2LsaRequest *>(obj)!=nullptr;
}

const char **Ospfv2LsaRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LsaRequestDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LsaRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ospfv2LsaRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsType
        0,    // FIELD_linkStateID
        0,    // FIELD_advertisingRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2LsaRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsType",
        "linkStateID",
        "advertisingRouter",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ospfv2LsaRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "linkStateID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "advertisingRouter") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LsaRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",    // FIELD_lsType
        "inet::Ipv4Address",    // FIELD_linkStateID
        "inet::Ipv4Address",    // FIELD_advertisingRouter
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LsaRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2LsaRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2LsaRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ospfv2LsaRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2LsaRequest'", field);
    }
}

const char *Ospfv2LsaRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LsaRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsType: return ulong2string(pp->lsType);
        case FIELD_linkStateID: return pp->linkStateID.str();
        case FIELD_advertisingRouter: return pp->advertisingRouter.str();
        default: return "";
    }
}

void Ospfv2LsaRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsType: pp->lsType = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaRequest'", field);
    }
}

omnetpp::cValue Ospfv2LsaRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsType: return omnetpp::checked_int_cast<omnetpp::intval_t>(pp->lsType);
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->linkStateID); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->advertisingRouter); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2LsaRequest' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LsaRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_lsType: pp->lsType = omnetpp::checked_int_cast<unsigned long>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaRequest'", field);
    }
}

const char *Ospfv2LsaRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ospfv2LsaRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_linkStateID: return omnetpp::toAnyPtr(&pp->linkStateID); break;
        case FIELD_advertisingRouter: return omnetpp::toAnyPtr(&pp->advertisingRouter); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LsaRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LsaRequest *pp = omnetpp::fromAnyPtr<Ospfv2LsaRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LsaRequest'", field);
    }
}

Register_Class(Ospfv2LinkStateRequestPacket)

Ospfv2LinkStateRequestPacket::Ospfv2LinkStateRequestPacket() : ::inet::ospfv2::Ospfv2Packet()
{
}

Ospfv2LinkStateRequestPacket::Ospfv2LinkStateRequestPacket(const Ospfv2LinkStateRequestPacket& other) : ::inet::ospfv2::Ospfv2Packet(other)
{
    copy(other);
}

Ospfv2LinkStateRequestPacket::~Ospfv2LinkStateRequestPacket()
{
    delete [] this->requests;
}

Ospfv2LinkStateRequestPacket& Ospfv2LinkStateRequestPacket::operator=(const Ospfv2LinkStateRequestPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2LinkStateRequestPacket::copy(const Ospfv2LinkStateRequestPacket& other)
{
    delete [] this->requests;
    this->requests = (other.requests_arraysize==0) ? nullptr : new Ospfv2LsaRequest[other.requests_arraysize];
    requests_arraysize = other.requests_arraysize;
    for (size_t i = 0; i < requests_arraysize; i++) {
        this->requests[i] = other.requests[i];
    }
}

void Ospfv2LinkStateRequestPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Packet::parsimPack(b);
    b->pack(requests_arraysize);
    doParsimArrayPacking(b,this->requests,requests_arraysize);
}

void Ospfv2LinkStateRequestPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Packet::parsimUnpack(b);
    delete [] this->requests;
    b->unpack(requests_arraysize);
    if (requests_arraysize == 0) {
        this->requests = nullptr;
    } else {
        this->requests = new Ospfv2LsaRequest[requests_arraysize];
        doParsimArrayUnpacking(b,this->requests,requests_arraysize);
    }
}

size_t Ospfv2LinkStateRequestPacket::getRequestsArraySize() const
{
    return requests_arraysize;
}

const Ospfv2LsaRequest& Ospfv2LinkStateRequestPacket::getRequests(size_t k) const
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    return this->requests[k];
}

void Ospfv2LinkStateRequestPacket::setRequestsArraySize(size_t newSize)
{
    handleChange();
    Ospfv2LsaRequest *requests2 = (newSize==0) ? nullptr : new Ospfv2LsaRequest[newSize];
    size_t minSize = requests_arraysize < newSize ? requests_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        requests2[i] = this->requests[i];
    delete [] this->requests;
    this->requests = requests2;
    requests_arraysize = newSize;
}

void Ospfv2LinkStateRequestPacket::setRequests(size_t k, const Ospfv2LsaRequest& requests)
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    this->requests[k] = requests;
}

void Ospfv2LinkStateRequestPacket::insertRequests(size_t k, const Ospfv2LsaRequest& requests)
{
    if (k > requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = requests_arraysize + 1;
    Ospfv2LsaRequest *requests2 = new Ospfv2LsaRequest[newSize];
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

void Ospfv2LinkStateRequestPacket::appendRequests(const Ospfv2LsaRequest& requests)
{
    insertRequests(requests_arraysize, requests);
}

void Ospfv2LinkStateRequestPacket::eraseRequests(size_t k)
{
    if (k >= requests_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)requests_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = requests_arraysize - 1;
    Ospfv2LsaRequest *requests2 = (newSize == 0) ? nullptr : new Ospfv2LsaRequest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        requests2[i] = this->requests[i];
    for (i = k; i < newSize; i++)
        requests2[i] = this->requests[i+1];
    delete [] this->requests;
    this->requests = requests2;
    requests_arraysize = newSize;
}

class Ospfv2LinkStateRequestPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requests,
    };
  public:
    Ospfv2LinkStateRequestPacketDescriptor();
    virtual ~Ospfv2LinkStateRequestPacketDescriptor();

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

Register_ClassDescriptor(Ospfv2LinkStateRequestPacketDescriptor)

Ospfv2LinkStateRequestPacketDescriptor::Ospfv2LinkStateRequestPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2LinkStateRequestPacket)), "inet::ospfv2::Ospfv2Packet")
{
    propertyNames = nullptr;
}

Ospfv2LinkStateRequestPacketDescriptor::~Ospfv2LinkStateRequestPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LinkStateRequestPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2LinkStateRequestPacket *>(obj)!=nullptr;
}

const char **Ospfv2LinkStateRequestPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LinkStateRequestPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LinkStateRequestPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv2LinkStateRequestPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *Ospfv2LinkStateRequestPacketDescriptor::getFieldName(int field) const
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

int Ospfv2LinkStateRequestPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requests") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LinkStateRequestPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv2::Ospfv2LsaRequest",    // FIELD_requests
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LinkStateRequestPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2LinkStateRequestPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2LinkStateRequestPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return pp->getRequestsArraySize();
        default: return 0;
    }
}

void Ospfv2LinkStateRequestPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: pp->setRequestsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2LinkStateRequestPacket'", field);
    }
}

const char *Ospfv2LinkStateRequestPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LinkStateRequestPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return "";
        default: return "";
    }
}

void Ospfv2LinkStateRequestPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateRequestPacket'", field);
    }
}

omnetpp::cValue Ospfv2LinkStateRequestPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return omnetpp::toAnyPtr(&pp->getRequests(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2LinkStateRequestPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LinkStateRequestPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateRequestPacket'", field);
    }
}

const char *Ospfv2LinkStateRequestPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_requests: return omnetpp::opp_typename(typeid(Ospfv2LsaRequest));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LinkStateRequestPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        case FIELD_requests: return omnetpp::toAnyPtr(&pp->getRequests(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LinkStateRequestPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateRequestPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateRequestPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateRequestPacket'", field);
    }
}

Register_Class(Ospfv2LinkStateUpdatePacket)

Ospfv2LinkStateUpdatePacket::Ospfv2LinkStateUpdatePacket() : ::inet::ospfv2::Ospfv2Packet()
{
}

Ospfv2LinkStateUpdatePacket::Ospfv2LinkStateUpdatePacket(const Ospfv2LinkStateUpdatePacket& other) : ::inet::ospfv2::Ospfv2Packet(other)
{
    copy(other);
}

Ospfv2LinkStateUpdatePacket::~Ospfv2LinkStateUpdatePacket()
{
    for (size_t i = 0; i < ospfLSAs_arraysize; i++)
        delete this->ospfLSAs[i];
    delete [] this->ospfLSAs;
}

Ospfv2LinkStateUpdatePacket& Ospfv2LinkStateUpdatePacket::operator=(const Ospfv2LinkStateUpdatePacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2LinkStateUpdatePacket::copy(const Ospfv2LinkStateUpdatePacket& other)
{
    for (size_t i = 0; i < ospfLSAs_arraysize; i++)
        delete this->ospfLSAs[i];
    delete [] this->ospfLSAs;
    this->ospfLSAs = (other.ospfLSAs_arraysize==0) ? nullptr : new Ospfv2Lsa *[other.ospfLSAs_arraysize];
    ospfLSAs_arraysize = other.ospfLSAs_arraysize;
    for (size_t i = 0; i < ospfLSAs_arraysize; i++) {
        this->ospfLSAs[i] = other.ospfLSAs[i];
        if (this->ospfLSAs[i] != nullptr) {
            this->ospfLSAs[i] = this->ospfLSAs[i]->dup();
        }
    }
}

void Ospfv2LinkStateUpdatePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Packet::parsimPack(b);
    b->pack(ospfLSAs_arraysize);
    doParsimArrayPacking(b,this->ospfLSAs,ospfLSAs_arraysize);
}

void Ospfv2LinkStateUpdatePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Packet::parsimUnpack(b);
    delete [] this->ospfLSAs;
    b->unpack(ospfLSAs_arraysize);
    if (ospfLSAs_arraysize == 0) {
        this->ospfLSAs = nullptr;
    } else {
        this->ospfLSAs = new Ospfv2Lsa *[ospfLSAs_arraysize];
        doParsimArrayUnpacking(b,this->ospfLSAs,ospfLSAs_arraysize);
    }
}

size_t Ospfv2LinkStateUpdatePacket::getOspfLSAsArraySize() const
{
    return ospfLSAs_arraysize;
}

const Ospfv2Lsa * Ospfv2LinkStateUpdatePacket::getOspfLSAs(size_t k) const
{
    if (k >= ospfLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ospfLSAs_arraysize, (unsigned long)k);
    return this->ospfLSAs[k];
}

void Ospfv2LinkStateUpdatePacket::setOspfLSAsArraySize(size_t newSize)
{
    handleChange();
    Ospfv2Lsa * *ospfLSAs2 = (newSize==0) ? nullptr : new Ospfv2Lsa *[newSize];
    size_t minSize = ospfLSAs_arraysize < newSize ? ospfLSAs_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        ospfLSAs2[i] = this->ospfLSAs[i];
    for (size_t i = minSize; i < newSize; i++)
        ospfLSAs2[i] = nullptr;
    for (size_t i = newSize; i < ospfLSAs_arraysize; i++)
        delete ospfLSAs[i];
    delete [] this->ospfLSAs;
    this->ospfLSAs = ospfLSAs2;
    ospfLSAs_arraysize = newSize;
}

void Ospfv2LinkStateUpdatePacket::setOspfLSAs(size_t k, Ospfv2Lsa * ospfLSAs)
{
    if (k >= ospfLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ospfLSAs_arraysize, (unsigned long)k);
    handleChange();
    if (ospfLSAs == this->ospfLSAs[k]) return;
    if (this->ospfLSAs[k] != nullptr && this->ospfLSAs[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->ospfLSAs[k]); else delete this->ospfLSAs[k];
    this->ospfLSAs[k] = ospfLSAs;
    if (this->ospfLSAs[k] != nullptr && this->ospfLSAs[k]->isOwnedObject()) take((cOwnedObject*)this->ospfLSAs[k]);
}

Ospfv2Lsa * Ospfv2LinkStateUpdatePacket::removeOspfLSAs(size_t k)
{
    if (k >= ospfLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ospfLSAs_arraysize, (unsigned long)k);
    handleChange();
    Ospfv2Lsa * retval = this->ospfLSAs[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->ospfLSAs[k] = nullptr;
    return retval;
}

void Ospfv2LinkStateUpdatePacket::insertOspfLSAs(size_t k, Ospfv2Lsa * ospfLSAs)
{
    if (k > ospfLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ospfLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ospfLSAs_arraysize + 1;
    Ospfv2Lsa * *ospfLSAs2 = new Ospfv2Lsa *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ospfLSAs2[i] = this->ospfLSAs[i];
    ospfLSAs2[k] = ospfLSAs;
    if (ospfLSAs2[k] != nullptr && ospfLSAs2[k]->isOwnedObject()) take((cOwnedObject*)ospfLSAs2[k]);
    for (i = k + 1; i < newSize; i++)
        ospfLSAs2[i] = this->ospfLSAs[i-1];
    delete [] this->ospfLSAs;
    this->ospfLSAs = ospfLSAs2;
    ospfLSAs_arraysize = newSize;
}

void Ospfv2LinkStateUpdatePacket::appendOspfLSAs(Ospfv2Lsa * ospfLSAs)
{
    insertOspfLSAs(ospfLSAs_arraysize, ospfLSAs);
}

void Ospfv2LinkStateUpdatePacket::eraseOspfLSAs(size_t k)
{
    if (k >= ospfLSAs_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ospfLSAs_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = ospfLSAs_arraysize - 1;
    Ospfv2Lsa * *ospfLSAs2 = (newSize == 0) ? nullptr : new Ospfv2Lsa *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ospfLSAs2[i] = this->ospfLSAs[i];
    for (i = k; i < newSize; i++)
        ospfLSAs2[i] = this->ospfLSAs[i+1];
    if (this->ospfLSAs[k] != nullptr && this->ospfLSAs[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->ospfLSAs[k]); else delete this->ospfLSAs[k];
    delete [] this->ospfLSAs;
    this->ospfLSAs = ospfLSAs2;
    ospfLSAs_arraysize = newSize;
}

class Ospfv2LinkStateUpdatePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ospfLSAs,
    };
  public:
    Ospfv2LinkStateUpdatePacketDescriptor();
    virtual ~Ospfv2LinkStateUpdatePacketDescriptor();

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

Register_ClassDescriptor(Ospfv2LinkStateUpdatePacketDescriptor)

Ospfv2LinkStateUpdatePacketDescriptor::Ospfv2LinkStateUpdatePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2LinkStateUpdatePacket)), "inet::ospfv2::Ospfv2Packet")
{
    propertyNames = nullptr;
}

Ospfv2LinkStateUpdatePacketDescriptor::~Ospfv2LinkStateUpdatePacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LinkStateUpdatePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2LinkStateUpdatePacket *>(obj)!=nullptr;
}

const char **Ospfv2LinkStateUpdatePacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LinkStateUpdatePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv2LinkStateUpdatePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_ospfLSAs
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ospfLSAs",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ospfv2LinkStateUpdatePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ospfLSAs") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv2::Ospfv2Lsa",    // FIELD_ospfLSAs
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LinkStateUpdatePacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfLSAs: {
            static const char *names[] = { "owned", "allowReplace",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfLSAs:
            if (!strcmp(propertyName, "owned")) return "";
            if (!strcmp(propertyName, "allowReplace")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int Ospfv2LinkStateUpdatePacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: return pp->getOspfLSAsArraySize();
        default: return 0;
    }
}

void Ospfv2LinkStateUpdatePacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: pp->setOspfLSAsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2LinkStateUpdatePacket'", field);
    }
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: { const Ospfv2Lsa * value = pp->getOspfLSAs(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ospfv2LinkStateUpdatePacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: { auto obj = pp->getOspfLSAs(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void Ospfv2LinkStateUpdatePacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateUpdatePacket'", field);
    }
}

omnetpp::cValue Ospfv2LinkStateUpdatePacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: return omnetpp::toAnyPtr(pp->getOspfLSAs(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2LinkStateUpdatePacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LinkStateUpdatePacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: pp->setOspfLSAs(i,omnetpp::fromAnyPtr<Ospfv2Lsa>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateUpdatePacket'", field);
    }
}

const char *Ospfv2LinkStateUpdatePacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ospfLSAs: return omnetpp::opp_typename(typeid(Ospfv2Lsa));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LinkStateUpdatePacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: return omnetpp::toAnyPtr(pp->getOspfLSAs(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LinkStateUpdatePacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateUpdatePacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateUpdatePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ospfLSAs: pp->setOspfLSAs(i,omnetpp::fromAnyPtr<Ospfv2Lsa>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateUpdatePacket'", field);
    }
}

Register_Class(Ospfv2LinkStateAcknowledgementPacket)

Ospfv2LinkStateAcknowledgementPacket::Ospfv2LinkStateAcknowledgementPacket() : ::inet::ospfv2::Ospfv2Packet()
{
}

Ospfv2LinkStateAcknowledgementPacket::Ospfv2LinkStateAcknowledgementPacket(const Ospfv2LinkStateAcknowledgementPacket& other) : ::inet::ospfv2::Ospfv2Packet(other)
{
    copy(other);
}

Ospfv2LinkStateAcknowledgementPacket::~Ospfv2LinkStateAcknowledgementPacket()
{
    delete [] this->lsaHeaders;
}

Ospfv2LinkStateAcknowledgementPacket& Ospfv2LinkStateAcknowledgementPacket::operator=(const Ospfv2LinkStateAcknowledgementPacket& other)
{
    if (this == &other) return *this;
    ::inet::ospfv2::Ospfv2Packet::operator=(other);
    copy(other);
    return *this;
}

void Ospfv2LinkStateAcknowledgementPacket::copy(const Ospfv2LinkStateAcknowledgementPacket& other)
{
    delete [] this->lsaHeaders;
    this->lsaHeaders = (other.lsaHeaders_arraysize==0) ? nullptr : new Ospfv2LsaHeader[other.lsaHeaders_arraysize];
    lsaHeaders_arraysize = other.lsaHeaders_arraysize;
    for (size_t i = 0; i < lsaHeaders_arraysize; i++) {
        this->lsaHeaders[i] = other.lsaHeaders[i];
    }
}

void Ospfv2LinkStateAcknowledgementPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ospfv2::Ospfv2Packet::parsimPack(b);
    b->pack(lsaHeaders_arraysize);
    doParsimArrayPacking(b,this->lsaHeaders,lsaHeaders_arraysize);
}

void Ospfv2LinkStateAcknowledgementPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ospfv2::Ospfv2Packet::parsimUnpack(b);
    delete [] this->lsaHeaders;
    b->unpack(lsaHeaders_arraysize);
    if (lsaHeaders_arraysize == 0) {
        this->lsaHeaders = nullptr;
    } else {
        this->lsaHeaders = new Ospfv2LsaHeader[lsaHeaders_arraysize];
        doParsimArrayUnpacking(b,this->lsaHeaders,lsaHeaders_arraysize);
    }
}

size_t Ospfv2LinkStateAcknowledgementPacket::getLsaHeadersArraySize() const
{
    return lsaHeaders_arraysize;
}

const Ospfv2LsaHeader& Ospfv2LinkStateAcknowledgementPacket::getLsaHeaders(size_t k) const
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    return this->lsaHeaders[k];
}

void Ospfv2LinkStateAcknowledgementPacket::setLsaHeadersArraySize(size_t newSize)
{
    handleChange();
    Ospfv2LsaHeader *lsaHeaders2 = (newSize==0) ? nullptr : new Ospfv2LsaHeader[newSize];
    size_t minSize = lsaHeaders_arraysize < newSize ? lsaHeaders_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

void Ospfv2LinkStateAcknowledgementPacket::setLsaHeaders(size_t k, const Ospfv2LsaHeader& lsaHeaders)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    this->lsaHeaders[k] = lsaHeaders;
}

void Ospfv2LinkStateAcknowledgementPacket::insertLsaHeaders(size_t k, const Ospfv2LsaHeader& lsaHeaders)
{
    if (k > lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize + 1;
    Ospfv2LsaHeader *lsaHeaders2 = new Ospfv2LsaHeader[newSize];
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

void Ospfv2LinkStateAcknowledgementPacket::appendLsaHeaders(const Ospfv2LsaHeader& lsaHeaders)
{
    insertLsaHeaders(lsaHeaders_arraysize, lsaHeaders);
}

void Ospfv2LinkStateAcknowledgementPacket::eraseLsaHeaders(size_t k)
{
    if (k >= lsaHeaders_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)lsaHeaders_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = lsaHeaders_arraysize - 1;
    Ospfv2LsaHeader *lsaHeaders2 = (newSize == 0) ? nullptr : new Ospfv2LsaHeader[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        lsaHeaders2[i] = this->lsaHeaders[i];
    for (i = k; i < newSize; i++)
        lsaHeaders2[i] = this->lsaHeaders[i+1];
    delete [] this->lsaHeaders;
    this->lsaHeaders = lsaHeaders2;
    lsaHeaders_arraysize = newSize;
}

class Ospfv2LinkStateAcknowledgementPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lsaHeaders,
    };
  public:
    Ospfv2LinkStateAcknowledgementPacketDescriptor();
    virtual ~Ospfv2LinkStateAcknowledgementPacketDescriptor();

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

Register_ClassDescriptor(Ospfv2LinkStateAcknowledgementPacketDescriptor)

Ospfv2LinkStateAcknowledgementPacketDescriptor::Ospfv2LinkStateAcknowledgementPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospfv2::Ospfv2LinkStateAcknowledgementPacket)), "inet::ospfv2::Ospfv2Packet")
{
    propertyNames = nullptr;
}

Ospfv2LinkStateAcknowledgementPacketDescriptor::~Ospfv2LinkStateAcknowledgementPacketDescriptor()
{
    delete[] propertyNames;
}

bool Ospfv2LinkStateAcknowledgementPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ospfv2LinkStateAcknowledgementPacket *>(obj)!=nullptr;
}

const char **Ospfv2LinkStateAcknowledgementPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldName(int field) const
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

int Ospfv2LinkStateAcknowledgementPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lsaHeaders") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ospfv2::Ospfv2LsaHeader",    // FIELD_lsaHeaders
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeadersArraySize();
        default: return 0;
    }
}

void Ospfv2LinkStateAcknowledgementPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: pp->setLsaHeadersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ospfv2LinkStateAcknowledgementPacket'", field);
    }
}

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return pp->getLsaHeaders(i).str();
        default: return "";
    }
}

void Ospfv2LinkStateAcknowledgementPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateAcknowledgementPacket'", field);
    }
}

omnetpp::cValue Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ospfv2LinkStateAcknowledgementPacket' as cValue -- field index out of range?", field);
    }
}

void Ospfv2LinkStateAcknowledgementPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateAcknowledgementPacket'", field);
    }
}

const char *Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::opp_typename(typeid(Ospfv2LsaHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ospfv2LinkStateAcknowledgementPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        case FIELD_lsaHeaders: return omnetpp::toAnyPtr(&pp->getLsaHeaders(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ospfv2LinkStateAcknowledgementPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ospfv2LinkStateAcknowledgementPacket *pp = omnetpp::fromAnyPtr<Ospfv2LinkStateAcknowledgementPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ospfv2LinkStateAcknowledgementPacket'", field);
    }
}

}  // namespace ospfv2
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

