//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee80211/mgmt/Ieee80211MgmtFrame.msg.
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
#include "Ieee80211MgmtFrame_m.h"

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
namespace ieee80211 {

Ieee80211CapabilityInformation::Ieee80211CapabilityInformation()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ieee80211CapabilityInformation& a)
{
    doParsimPacking(b,a.ESS);
    doParsimPacking(b,a.IBSS);
    doParsimPacking(b,a.CFPollable);
    doParsimPacking(b,a.CFPollRequest);
    doParsimPacking(b,a.privacy);
    doParsimPacking(b,a.DelayedBlockAck);
    doParsimPacking(b,a.InmediateBlockAck);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ieee80211CapabilityInformation& a)
{
    doParsimUnpacking(b,a.ESS);
    doParsimUnpacking(b,a.IBSS);
    doParsimUnpacking(b,a.CFPollable);
    doParsimUnpacking(b,a.CFPollRequest);
    doParsimUnpacking(b,a.privacy);
    doParsimUnpacking(b,a.DelayedBlockAck);
    doParsimUnpacking(b,a.InmediateBlockAck);
}

class Ieee80211CapabilityInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ESS,
        FIELD_IBSS,
        FIELD_CFPollable,
        FIELD_CFPollRequest,
        FIELD_privacy,
        FIELD_DelayedBlockAck,
        FIELD_InmediateBlockAck,
    };
  public:
    Ieee80211CapabilityInformationDescriptor();
    virtual ~Ieee80211CapabilityInformationDescriptor();

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

Register_ClassDescriptor(Ieee80211CapabilityInformationDescriptor)

Ieee80211CapabilityInformationDescriptor::Ieee80211CapabilityInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211CapabilityInformation)), "")
{
    propertyNames = nullptr;
}

Ieee80211CapabilityInformationDescriptor::~Ieee80211CapabilityInformationDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211CapabilityInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211CapabilityInformation *>(obj)!=nullptr;
}

const char **Ieee80211CapabilityInformationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211CapabilityInformationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211CapabilityInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int Ieee80211CapabilityInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ESS
        FD_ISEDITABLE,    // FIELD_IBSS
        FD_ISEDITABLE,    // FIELD_CFPollable
        FD_ISEDITABLE,    // FIELD_CFPollRequest
        FD_ISEDITABLE,    // FIELD_privacy
        FD_ISEDITABLE,    // FIELD_DelayedBlockAck
        FD_ISEDITABLE,    // FIELD_InmediateBlockAck
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211CapabilityInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ESS",
        "IBSS",
        "CFPollable",
        "CFPollRequest",
        "privacy",
        "DelayedBlockAck",
        "InmediateBlockAck",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ieee80211CapabilityInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ESS") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "IBSS") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "CFPollable") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "CFPollRequest") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "privacy") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "DelayedBlockAck") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "InmediateBlockAck") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211CapabilityInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_ESS
        "bool",    // FIELD_IBSS
        "bool",    // FIELD_CFPollable
        "bool",    // FIELD_CFPollRequest
        "bool",    // FIELD_privacy
        "bool",    // FIELD_DelayedBlockAck
        "bool",    // FIELD_InmediateBlockAck
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211CapabilityInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211CapabilityInformationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211CapabilityInformationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211CapabilityInformationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211CapabilityInformation'", field);
    }
}

const char *Ieee80211CapabilityInformationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211CapabilityInformationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        case FIELD_ESS: return bool2string(pp->ESS);
        case FIELD_IBSS: return bool2string(pp->IBSS);
        case FIELD_CFPollable: return bool2string(pp->CFPollable);
        case FIELD_CFPollRequest: return bool2string(pp->CFPollRequest);
        case FIELD_privacy: return bool2string(pp->privacy);
        case FIELD_DelayedBlockAck: return bool2string(pp->DelayedBlockAck);
        case FIELD_InmediateBlockAck: return bool2string(pp->InmediateBlockAck);
        default: return "";
    }
}

void Ieee80211CapabilityInformationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        case FIELD_ESS: pp->ESS = string2bool(value); break;
        case FIELD_IBSS: pp->IBSS = string2bool(value); break;
        case FIELD_CFPollable: pp->CFPollable = string2bool(value); break;
        case FIELD_CFPollRequest: pp->CFPollRequest = string2bool(value); break;
        case FIELD_privacy: pp->privacy = string2bool(value); break;
        case FIELD_DelayedBlockAck: pp->DelayedBlockAck = string2bool(value); break;
        case FIELD_InmediateBlockAck: pp->InmediateBlockAck = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CapabilityInformation'", field);
    }
}

omnetpp::cValue Ieee80211CapabilityInformationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        case FIELD_ESS: return pp->ESS;
        case FIELD_IBSS: return pp->IBSS;
        case FIELD_CFPollable: return pp->CFPollable;
        case FIELD_CFPollRequest: return pp->CFPollRequest;
        case FIELD_privacy: return pp->privacy;
        case FIELD_DelayedBlockAck: return pp->DelayedBlockAck;
        case FIELD_InmediateBlockAck: return pp->InmediateBlockAck;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211CapabilityInformation' as cValue -- field index out of range?", field);
    }
}

void Ieee80211CapabilityInformationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        case FIELD_ESS: pp->ESS = value.boolValue(); break;
        case FIELD_IBSS: pp->IBSS = value.boolValue(); break;
        case FIELD_CFPollable: pp->CFPollable = value.boolValue(); break;
        case FIELD_CFPollRequest: pp->CFPollRequest = value.boolValue(); break;
        case FIELD_privacy: pp->privacy = value.boolValue(); break;
        case FIELD_DelayedBlockAck: pp->DelayedBlockAck = value.boolValue(); break;
        case FIELD_InmediateBlockAck: pp->InmediateBlockAck = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CapabilityInformation'", field);
    }
}

const char *Ieee80211CapabilityInformationDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211CapabilityInformationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211CapabilityInformationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CapabilityInformation *pp = omnetpp::fromAnyPtr<Ieee80211CapabilityInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CapabilityInformation'", field);
    }
}

Ieee80211HandoverParameters::Ieee80211HandoverParameters()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const Ieee80211HandoverParameters& a)
{
    doParsimPacking(b,a.avgBackoffTime);
    doParsimPacking(b,a.avgWaitTime);
    doParsimPacking(b,a.avgErrorRate);
    doParsimPacking(b,a.estAvailBW);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ieee80211HandoverParameters& a)
{
    doParsimUnpacking(b,a.avgBackoffTime);
    doParsimUnpacking(b,a.avgWaitTime);
    doParsimUnpacking(b,a.avgErrorRate);
    doParsimUnpacking(b,a.estAvailBW);
}

class Ieee80211HandoverParametersDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_avgBackoffTime,
        FIELD_avgWaitTime,
        FIELD_avgErrorRate,
        FIELD_estAvailBW,
    };
  public:
    Ieee80211HandoverParametersDescriptor();
    virtual ~Ieee80211HandoverParametersDescriptor();

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

Register_ClassDescriptor(Ieee80211HandoverParametersDescriptor)

Ieee80211HandoverParametersDescriptor::Ieee80211HandoverParametersDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211HandoverParameters)), "")
{
    propertyNames = nullptr;
}

Ieee80211HandoverParametersDescriptor::~Ieee80211HandoverParametersDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211HandoverParametersDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211HandoverParameters *>(obj)!=nullptr;
}

const char **Ieee80211HandoverParametersDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211HandoverParametersDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211HandoverParametersDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211HandoverParametersDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_avgBackoffTime
        FD_ISEDITABLE,    // FIELD_avgWaitTime
        FD_ISEDITABLE,    // FIELD_avgErrorRate
        FD_ISEDITABLE,    // FIELD_estAvailBW
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211HandoverParametersDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "avgBackoffTime",
        "avgWaitTime",
        "avgErrorRate",
        "estAvailBW",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211HandoverParametersDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "avgBackoffTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "avgWaitTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "avgErrorRate") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "estAvailBW") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211HandoverParametersDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_avgBackoffTime
        "double",    // FIELD_avgWaitTime
        "double",    // FIELD_avgErrorRate
        "double",    // FIELD_estAvailBW
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211HandoverParametersDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211HandoverParametersDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211HandoverParametersDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211HandoverParametersDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211HandoverParameters'", field);
    }
}

const char *Ieee80211HandoverParametersDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211HandoverParametersDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        case FIELD_avgBackoffTime: return double2string(pp->avgBackoffTime);
        case FIELD_avgWaitTime: return double2string(pp->avgWaitTime);
        case FIELD_avgErrorRate: return double2string(pp->avgErrorRate);
        case FIELD_estAvailBW: return double2string(pp->estAvailBW);
        default: return "";
    }
}

void Ieee80211HandoverParametersDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        case FIELD_avgBackoffTime: pp->avgBackoffTime = string2double(value); break;
        case FIELD_avgWaitTime: pp->avgWaitTime = string2double(value); break;
        case FIELD_avgErrorRate: pp->avgErrorRate = string2double(value); break;
        case FIELD_estAvailBW: pp->estAvailBW = string2double(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HandoverParameters'", field);
    }
}

omnetpp::cValue Ieee80211HandoverParametersDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        case FIELD_avgBackoffTime: return pp->avgBackoffTime;
        case FIELD_avgWaitTime: return pp->avgWaitTime;
        case FIELD_avgErrorRate: return pp->avgErrorRate;
        case FIELD_estAvailBW: return pp->estAvailBW;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211HandoverParameters' as cValue -- field index out of range?", field);
    }
}

void Ieee80211HandoverParametersDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        case FIELD_avgBackoffTime: pp->avgBackoffTime = value.doubleValue(); break;
        case FIELD_avgWaitTime: pp->avgWaitTime = value.doubleValue(); break;
        case FIELD_avgErrorRate: pp->avgErrorRate = value.doubleValue(); break;
        case FIELD_estAvailBW: pp->estAvailBW = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HandoverParameters'", field);
    }
}

const char *Ieee80211HandoverParametersDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211HandoverParametersDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211HandoverParametersDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HandoverParameters *pp = omnetpp::fromAnyPtr<Ieee80211HandoverParameters>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HandoverParameters'", field);
    }
}

Register_Enum(inet::ieee80211::Ieee80211ReasonCode, (inet::ieee80211::Ieee80211ReasonCode::RC_UNSPECIFIED, inet::ieee80211::Ieee80211ReasonCode::RC_PREV_AUTH_EXPIRED, inet::ieee80211::Ieee80211ReasonCode::RC_DEAUTH_MS_LEAVING, inet::ieee80211::Ieee80211ReasonCode::RC_DISASS_INACTIVITY, inet::ieee80211::Ieee80211ReasonCode::RC_DISASS_TOO_MANY_MS, inet::ieee80211::Ieee80211ReasonCode::RC_NONAUTH_CLASS2, inet::ieee80211::Ieee80211ReasonCode::RC_NONASS_CLASS3, inet::ieee80211::Ieee80211ReasonCode::RC_DIASS_MS_LEAVING, inet::ieee80211::Ieee80211ReasonCode::RC_NONAUTH_ASS_REQUEST, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_PEERING_CANCELLED, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_MAX_PEERS, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_CONFIGURATION_POLICY_VIOLATION, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_CLOSE_RCVD, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_MAX_RETRIES, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_CONFIRM_TIMEOUT, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_INVALID_GTK, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_INCONSISTENT_PARAMETERS, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_INVALID_SECURITY_CAPABILITY, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_PATH_ERROR_NO_PROXY_INFORMATION, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_PATH_ERROR_NO_FORWARDING_INFORMATION, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_PATH_ERROR_DESTINATION_UNREACHABLE, inet::ieee80211::Ieee80211ReasonCode::RC_MAC_ADDRESS_ALREADY_EXISTS_IN_MBSS, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_CHANNEL_SWITCH_REGULATORY_REQUIREMENTS, inet::ieee80211::Ieee80211ReasonCode::RC_MESH_CHANNEL_SWITCH_UNSPECIFIED));

Register_Enum(inet::ieee80211::Ieee80211StatusCode, (inet::ieee80211::Ieee80211StatusCode::SC_SUCCESSFUL, inet::ieee80211::Ieee80211StatusCode::SC_UNSPECIFIED, inet::ieee80211::Ieee80211StatusCode::SC_UNSUP_CAP, inet::ieee80211::Ieee80211StatusCode::SC_REASS_DENIED, inet::ieee80211::Ieee80211StatusCode::SC_ASS_DENIED_UNKNOWN, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_ALG0_UNSUP, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_OUT_OF_SEQ, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_CHALLENGE_FAIL, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_TIMEOUT, inet::ieee80211::Ieee80211StatusCode::SC_ASS_TOO_MANY_MS, inet::ieee80211::Ieee80211StatusCode::SC_DATARATE_UNSUP, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_REJECT_ANTI_CLOGING, inet::ieee80211::Ieee80211StatusCode::SC_AUTH_REJECT_FINITE_CYC_GROUP_UNS, inet::ieee80211::Ieee80211StatusCode::SC_TBTT_REQUEST));

Register_Enum(inet::ieee80211::Ieee80211HwmpCode, (inet::ieee80211::Ieee80211HwmpCode::IE11S_GANN, inet::ieee80211::Ieee80211HwmpCode::IE11S_RANN, inet::ieee80211::Ieee80211HwmpCode::IE11S_PREQ, inet::ieee80211::Ieee80211HwmpCode::IE11S_PREP, inet::ieee80211::Ieee80211HwmpCode::IE11S_PERR));

Ieee80211SupportedRatesElement::Ieee80211SupportedRatesElement()
{
    for (size_t i = 0; i < 8; i++)
        this->rate[i] = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const Ieee80211SupportedRatesElement& a)
{
    doParsimPacking(b,a.numRates);
    doParsimArrayPacking(b,a.rate,8);
}

void __doUnpacking(omnetpp::cCommBuffer *b, Ieee80211SupportedRatesElement& a)
{
    doParsimUnpacking(b,a.numRates);
    doParsimArrayUnpacking(b,a.rate,8);
}

class Ieee80211SupportedRatesElementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_numRates,
        FIELD_rate,
    };
  public:
    Ieee80211SupportedRatesElementDescriptor();
    virtual ~Ieee80211SupportedRatesElementDescriptor();

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

Register_ClassDescriptor(Ieee80211SupportedRatesElementDescriptor)

Ieee80211SupportedRatesElementDescriptor::Ieee80211SupportedRatesElementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211SupportedRatesElement)), "")
{
    propertyNames = nullptr;
}

Ieee80211SupportedRatesElementDescriptor::~Ieee80211SupportedRatesElementDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211SupportedRatesElementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211SupportedRatesElement *>(obj)!=nullptr;
}

const char **Ieee80211SupportedRatesElementDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211SupportedRatesElementDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211SupportedRatesElementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211SupportedRatesElementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_numRates
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_rate
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211SupportedRatesElementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "numRates",
        "rate",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211SupportedRatesElementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "numRates") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "rate") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211SupportedRatesElementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_numRates
        "double",    // FIELD_rate
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211SupportedRatesElementDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211SupportedRatesElementDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211SupportedRatesElementDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        case FIELD_rate: return 8;
        default: return 0;
    }
}

void Ieee80211SupportedRatesElementDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211SupportedRatesElement'", field);
    }
}

const char *Ieee80211SupportedRatesElementDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211SupportedRatesElementDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        case FIELD_numRates: return long2string(pp->numRates);
        case FIELD_rate: if (i >= 8) return "";
                return double2string(pp->rate[i]);
        default: return "";
    }
}

void Ieee80211SupportedRatesElementDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        case FIELD_numRates: pp->numRates = string2long(value); break;
        case FIELD_rate: if (i < 0 || i >= 8) throw omnetpp::cRuntimeError("Array index %d out of bounds for field %d of class 'Ieee80211SupportedRatesElement'", i, field);
                pp->rate[i] = string2double(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211SupportedRatesElement'", field);
    }
}

omnetpp::cValue Ieee80211SupportedRatesElementDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        case FIELD_numRates: return pp->numRates;
        case FIELD_rate: if (i >= 8) return omnetpp::cValue();
                return pp->rate[i];
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211SupportedRatesElement' as cValue -- field index out of range?", field);
    }
}

void Ieee80211SupportedRatesElementDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        case FIELD_numRates: pp->numRates = omnetpp::checked_int_cast<short>(value.intValue()); break;
        case FIELD_rate: if (i < 0 || i >= 8) throw omnetpp::cRuntimeError("Array index %d out of bounds for field %d of class 'Ieee80211SupportedRatesElement'", i, field);
                pp->rate[i] = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211SupportedRatesElement'", field);
    }
}

const char *Ieee80211SupportedRatesElementDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211SupportedRatesElementDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211SupportedRatesElementDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211SupportedRatesElement *pp = omnetpp::fromAnyPtr<Ieee80211SupportedRatesElement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211SupportedRatesElement'", field);
    }
}

Register_Class(Ieee80211MgmtFrame)

Ieee80211MgmtFrame::Ieee80211MgmtFrame() : ::inet::FieldsChunk()
{
}

Ieee80211MgmtFrame::Ieee80211MgmtFrame(const Ieee80211MgmtFrame& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211MgmtFrame::~Ieee80211MgmtFrame()
{
}

Ieee80211MgmtFrame& Ieee80211MgmtFrame::operator=(const Ieee80211MgmtFrame& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MgmtFrame::copy(const Ieee80211MgmtFrame& other)
{
}

void Ieee80211MgmtFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
}

void Ieee80211MgmtFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
}

class Ieee80211MgmtFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211MgmtFrameDescriptor();
    virtual ~Ieee80211MgmtFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211MgmtFrameDescriptor)

Ieee80211MgmtFrameDescriptor::Ieee80211MgmtFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MgmtFrame)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211MgmtFrameDescriptor::~Ieee80211MgmtFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MgmtFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MgmtFrame *>(obj)!=nullptr;
}

const char **Ieee80211MgmtFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MgmtFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MgmtFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211MgmtFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211MgmtFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211MgmtFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MgmtFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211MgmtFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MgmtFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MgmtFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MgmtFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MgmtFrame'", field);
    }
}

const char *Ieee80211MgmtFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MgmtFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211MgmtFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtFrame'", field);
    }
}

omnetpp::cValue Ieee80211MgmtFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MgmtFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MgmtFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtFrame'", field);
    }
}

const char *Ieee80211MgmtFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211MgmtFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MgmtFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtFrame *pp = omnetpp::fromAnyPtr<Ieee80211MgmtFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtFrame'", field);
    }
}

Register_Class(Ieee80211AuthenticationFrame)

Ieee80211AuthenticationFrame::Ieee80211AuthenticationFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
    this->setChunkLength(B(6));

}

Ieee80211AuthenticationFrame::Ieee80211AuthenticationFrame(const Ieee80211AuthenticationFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211AuthenticationFrame::~Ieee80211AuthenticationFrame()
{
}

Ieee80211AuthenticationFrame& Ieee80211AuthenticationFrame::operator=(const Ieee80211AuthenticationFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AuthenticationFrame::copy(const Ieee80211AuthenticationFrame& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->statusCode = other.statusCode;
    this->isLast_ = other.isLast_;
}

void Ieee80211AuthenticationFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->statusCode);
    doParsimPacking(b,this->isLast_);
}

void Ieee80211AuthenticationFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->statusCode);
    doParsimUnpacking(b,this->isLast_);
}

unsigned short Ieee80211AuthenticationFrame::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void Ieee80211AuthenticationFrame::setSequenceNumber(unsigned short sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

Ieee80211StatusCode Ieee80211AuthenticationFrame::getStatusCode() const
{
    return this->statusCode;
}

void Ieee80211AuthenticationFrame::setStatusCode(Ieee80211StatusCode statusCode)
{
    handleChange();
    this->statusCode = statusCode;
}

bool Ieee80211AuthenticationFrame::isLast() const
{
    return this->isLast_;
}

void Ieee80211AuthenticationFrame::setIsLast(bool isLast)
{
    handleChange();
    this->isLast_ = isLast;
}

class Ieee80211AuthenticationFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_statusCode,
        FIELD_isLast,
    };
  public:
    Ieee80211AuthenticationFrameDescriptor();
    virtual ~Ieee80211AuthenticationFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211AuthenticationFrameDescriptor)

Ieee80211AuthenticationFrameDescriptor::Ieee80211AuthenticationFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AuthenticationFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211AuthenticationFrameDescriptor::~Ieee80211AuthenticationFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AuthenticationFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AuthenticationFrame *>(obj)!=nullptr;
}

const char **Ieee80211AuthenticationFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AuthenticationFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AuthenticationFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211AuthenticationFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        0,    // FIELD_statusCode
        FD_ISEDITABLE,    // FIELD_isLast
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211AuthenticationFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "statusCode",
        "isLast",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211AuthenticationFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "statusCode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "isLast") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AuthenticationFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_sequenceNumber
        "inet::ieee80211::Ieee80211StatusCode",    // FIELD_statusCode
        "bool",    // FIELD_isLast
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211AuthenticationFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_statusCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211AuthenticationFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_statusCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211StatusCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211AuthenticationFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AuthenticationFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AuthenticationFrame'", field);
    }
}

const char *Ieee80211AuthenticationFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AuthenticationFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_statusCode: return enum2string(pp->getStatusCode(), "inet::ieee80211::Ieee80211StatusCode");
        case FIELD_isLast: return bool2string(pp->isLast());
        default: return "";
    }
}

void Ieee80211AuthenticationFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        case FIELD_isLast: pp->setIsLast(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AuthenticationFrame'", field);
    }
}

omnetpp::cValue Ieee80211AuthenticationFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_statusCode: return static_cast<int>(pp->getStatusCode());
        case FIELD_isLast: return pp->isLast();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AuthenticationFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AuthenticationFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_isLast: pp->setIsLast(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AuthenticationFrame'", field);
    }
}

const char *Ieee80211AuthenticationFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211AuthenticationFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AuthenticationFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AuthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211AuthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AuthenticationFrame'", field);
    }
}

Register_Class(Ieee80211DeauthenticationFrame)

Ieee80211DeauthenticationFrame::Ieee80211DeauthenticationFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
    this->setChunkLength(B(2));

}

Ieee80211DeauthenticationFrame::Ieee80211DeauthenticationFrame(const Ieee80211DeauthenticationFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211DeauthenticationFrame::~Ieee80211DeauthenticationFrame()
{
}

Ieee80211DeauthenticationFrame& Ieee80211DeauthenticationFrame::operator=(const Ieee80211DeauthenticationFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DeauthenticationFrame::copy(const Ieee80211DeauthenticationFrame& other)
{
    this->reasonCode = other.reasonCode;
}

void Ieee80211DeauthenticationFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->reasonCode);
}

void Ieee80211DeauthenticationFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->reasonCode);
}

Ieee80211ReasonCode Ieee80211DeauthenticationFrame::getReasonCode() const
{
    return this->reasonCode;
}

void Ieee80211DeauthenticationFrame::setReasonCode(Ieee80211ReasonCode reasonCode)
{
    handleChange();
    this->reasonCode = reasonCode;
}

class Ieee80211DeauthenticationFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reasonCode,
    };
  public:
    Ieee80211DeauthenticationFrameDescriptor();
    virtual ~Ieee80211DeauthenticationFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211DeauthenticationFrameDescriptor)

Ieee80211DeauthenticationFrameDescriptor::Ieee80211DeauthenticationFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211DeauthenticationFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211DeauthenticationFrameDescriptor::~Ieee80211DeauthenticationFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DeauthenticationFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DeauthenticationFrame *>(obj)!=nullptr;
}

const char **Ieee80211DeauthenticationFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DeauthenticationFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DeauthenticationFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211DeauthenticationFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_reasonCode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DeauthenticationFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reasonCode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211DeauthenticationFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reasonCode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DeauthenticationFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211ReasonCode",    // FIELD_reasonCode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DeauthenticationFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211DeauthenticationFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211ReasonCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211DeauthenticationFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DeauthenticationFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DeauthenticationFrame'", field);
    }
}

const char *Ieee80211DeauthenticationFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DeauthenticationFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: return enum2string(pp->getReasonCode(), "inet::ieee80211::Ieee80211ReasonCode");
        default: return "";
    }
}

void Ieee80211DeauthenticationFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DeauthenticationFrame'", field);
    }
}

omnetpp::cValue Ieee80211DeauthenticationFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: return static_cast<int>(pp->getReasonCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DeauthenticationFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DeauthenticationFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DeauthenticationFrame'", field);
    }
}

const char *Ieee80211DeauthenticationFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DeauthenticationFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DeauthenticationFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DeauthenticationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DeauthenticationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DeauthenticationFrame'", field);
    }
}

Register_Class(Ieee80211DisassociationFrame)

Ieee80211DisassociationFrame::Ieee80211DisassociationFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
    this->setChunkLength(B(2));

}

Ieee80211DisassociationFrame::Ieee80211DisassociationFrame(const Ieee80211DisassociationFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211DisassociationFrame::~Ieee80211DisassociationFrame()
{
}

Ieee80211DisassociationFrame& Ieee80211DisassociationFrame::operator=(const Ieee80211DisassociationFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DisassociationFrame::copy(const Ieee80211DisassociationFrame& other)
{
    this->reasonCode = other.reasonCode;
}

void Ieee80211DisassociationFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->reasonCode);
}

void Ieee80211DisassociationFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->reasonCode);
}

Ieee80211ReasonCode Ieee80211DisassociationFrame::getReasonCode() const
{
    return this->reasonCode;
}

void Ieee80211DisassociationFrame::setReasonCode(Ieee80211ReasonCode reasonCode)
{
    handleChange();
    this->reasonCode = reasonCode;
}

class Ieee80211DisassociationFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reasonCode,
    };
  public:
    Ieee80211DisassociationFrameDescriptor();
    virtual ~Ieee80211DisassociationFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211DisassociationFrameDescriptor)

Ieee80211DisassociationFrameDescriptor::Ieee80211DisassociationFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211DisassociationFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211DisassociationFrameDescriptor::~Ieee80211DisassociationFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DisassociationFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DisassociationFrame *>(obj)!=nullptr;
}

const char **Ieee80211DisassociationFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DisassociationFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DisassociationFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211DisassociationFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_reasonCode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DisassociationFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reasonCode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211DisassociationFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reasonCode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DisassociationFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211ReasonCode",    // FIELD_reasonCode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DisassociationFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211DisassociationFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211ReasonCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211DisassociationFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DisassociationFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DisassociationFrame'", field);
    }
}

const char *Ieee80211DisassociationFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DisassociationFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: return enum2string(pp->getReasonCode(), "inet::ieee80211::Ieee80211ReasonCode");
        default: return "";
    }
}

void Ieee80211DisassociationFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DisassociationFrame'", field);
    }
}

omnetpp::cValue Ieee80211DisassociationFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: return static_cast<int>(pp->getReasonCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DisassociationFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DisassociationFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DisassociationFrame'", field);
    }
}

const char *Ieee80211DisassociationFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DisassociationFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DisassociationFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DisassociationFrame *pp = omnetpp::fromAnyPtr<Ieee80211DisassociationFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DisassociationFrame'", field);
    }
}

Register_Class(Ieee80211ProbeRequestFrame)

Ieee80211ProbeRequestFrame::Ieee80211ProbeRequestFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
}

Ieee80211ProbeRequestFrame::Ieee80211ProbeRequestFrame(const Ieee80211ProbeRequestFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211ProbeRequestFrame::~Ieee80211ProbeRequestFrame()
{
}

Ieee80211ProbeRequestFrame& Ieee80211ProbeRequestFrame::operator=(const Ieee80211ProbeRequestFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ProbeRequestFrame::copy(const Ieee80211ProbeRequestFrame& other)
{
    this->SSID = other.SSID;
    this->supportedRates = other.supportedRates;
}

void Ieee80211ProbeRequestFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->SSID);
    doParsimPacking(b,this->supportedRates);
}

void Ieee80211ProbeRequestFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->SSID);
    doParsimUnpacking(b,this->supportedRates);
}

const char * Ieee80211ProbeRequestFrame::getSSID() const
{
    return this->SSID.c_str();
}

void Ieee80211ProbeRequestFrame::setSSID(const char * SSID)
{
    handleChange();
    this->SSID = SSID;
}

const Ieee80211SupportedRatesElement& Ieee80211ProbeRequestFrame::getSupportedRates() const
{
    return this->supportedRates;
}

void Ieee80211ProbeRequestFrame::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    handleChange();
    this->supportedRates = supportedRates;
}

class Ieee80211ProbeRequestFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_SSID,
        FIELD_supportedRates,
    };
  public:
    Ieee80211ProbeRequestFrameDescriptor();
    virtual ~Ieee80211ProbeRequestFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211ProbeRequestFrameDescriptor)

Ieee80211ProbeRequestFrameDescriptor::Ieee80211ProbeRequestFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211ProbeRequestFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211ProbeRequestFrameDescriptor::~Ieee80211ProbeRequestFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ProbeRequestFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ProbeRequestFrame *>(obj)!=nullptr;
}

const char **Ieee80211ProbeRequestFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ProbeRequestFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ProbeRequestFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211ProbeRequestFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_SSID
        FD_ISCOMPOUND,    // FIELD_supportedRates
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211ProbeRequestFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "SSID",
        "supportedRates",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211ProbeRequestFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "SSID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "supportedRates") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ProbeRequestFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_SSID
        "inet::ieee80211::Ieee80211SupportedRatesElement",    // FIELD_supportedRates
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211ProbeRequestFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ProbeRequestFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ProbeRequestFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ProbeRequestFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ProbeRequestFrame'", field);
    }
}

const char *Ieee80211ProbeRequestFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ProbeRequestFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return oppstring2string(pp->getSSID());
        case FIELD_supportedRates: return "";
        default: return "";
    }
}

void Ieee80211ProbeRequestFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeRequestFrame'", field);
    }
}

omnetpp::cValue Ieee80211ProbeRequestFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return pp->getSSID();
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ProbeRequestFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ProbeRequestFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeRequestFrame'", field);
    }
}

const char *Ieee80211ProbeRequestFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_supportedRates: return omnetpp::opp_typename(typeid(Ieee80211SupportedRatesElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211ProbeRequestFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ProbeRequestFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeRequestFrame'", field);
    }
}

Register_Class(Ieee80211AssociationRequestFrame)

Ieee80211AssociationRequestFrame::Ieee80211AssociationRequestFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
}

Ieee80211AssociationRequestFrame::Ieee80211AssociationRequestFrame(const Ieee80211AssociationRequestFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211AssociationRequestFrame::~Ieee80211AssociationRequestFrame()
{
}

Ieee80211AssociationRequestFrame& Ieee80211AssociationRequestFrame::operator=(const Ieee80211AssociationRequestFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AssociationRequestFrame::copy(const Ieee80211AssociationRequestFrame& other)
{
    this->SSID = other.SSID;
    this->supportedRates = other.supportedRates;
}

void Ieee80211AssociationRequestFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->SSID);
    doParsimPacking(b,this->supportedRates);
}

void Ieee80211AssociationRequestFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->SSID);
    doParsimUnpacking(b,this->supportedRates);
}

const char * Ieee80211AssociationRequestFrame::getSSID() const
{
    return this->SSID.c_str();
}

void Ieee80211AssociationRequestFrame::setSSID(const char * SSID)
{
    handleChange();
    this->SSID = SSID;
}

const Ieee80211SupportedRatesElement& Ieee80211AssociationRequestFrame::getSupportedRates() const
{
    return this->supportedRates;
}

void Ieee80211AssociationRequestFrame::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    handleChange();
    this->supportedRates = supportedRates;
}

class Ieee80211AssociationRequestFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_SSID,
        FIELD_supportedRates,
    };
  public:
    Ieee80211AssociationRequestFrameDescriptor();
    virtual ~Ieee80211AssociationRequestFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211AssociationRequestFrameDescriptor)

Ieee80211AssociationRequestFrameDescriptor::Ieee80211AssociationRequestFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AssociationRequestFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211AssociationRequestFrameDescriptor::~Ieee80211AssociationRequestFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AssociationRequestFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AssociationRequestFrame *>(obj)!=nullptr;
}

const char **Ieee80211AssociationRequestFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AssociationRequestFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AssociationRequestFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211AssociationRequestFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_SSID
        FD_ISCOMPOUND,    // FIELD_supportedRates
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211AssociationRequestFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "SSID",
        "supportedRates",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211AssociationRequestFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "SSID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "supportedRates") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AssociationRequestFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_SSID
        "inet::ieee80211::Ieee80211SupportedRatesElement",    // FIELD_supportedRates
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211AssociationRequestFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211AssociationRequestFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211AssociationRequestFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AssociationRequestFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AssociationRequestFrame'", field);
    }
}

const char *Ieee80211AssociationRequestFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AssociationRequestFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return oppstring2string(pp->getSSID());
        case FIELD_supportedRates: return "";
        default: return "";
    }
}

void Ieee80211AssociationRequestFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationRequestFrame'", field);
    }
}

omnetpp::cValue Ieee80211AssociationRequestFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return pp->getSSID();
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AssociationRequestFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AssociationRequestFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationRequestFrame'", field);
    }
}

const char *Ieee80211AssociationRequestFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_supportedRates: return omnetpp::opp_typename(typeid(Ieee80211SupportedRatesElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211AssociationRequestFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AssociationRequestFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationRequestFrame'", field);
    }
}

Register_Class(Ieee80211ReassociationRequestFrame)

Ieee80211ReassociationRequestFrame::Ieee80211ReassociationRequestFrame() : ::inet::ieee80211::Ieee80211AssociationRequestFrame()
{
}

Ieee80211ReassociationRequestFrame::Ieee80211ReassociationRequestFrame(const Ieee80211ReassociationRequestFrame& other) : ::inet::ieee80211::Ieee80211AssociationRequestFrame(other)
{
    copy(other);
}

Ieee80211ReassociationRequestFrame::~Ieee80211ReassociationRequestFrame()
{
}

Ieee80211ReassociationRequestFrame& Ieee80211ReassociationRequestFrame::operator=(const Ieee80211ReassociationRequestFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211AssociationRequestFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ReassociationRequestFrame::copy(const Ieee80211ReassociationRequestFrame& other)
{
    this->currentAP = other.currentAP;
}

void Ieee80211ReassociationRequestFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211AssociationRequestFrame::parsimPack(b);
    doParsimPacking(b,this->currentAP);
}

void Ieee80211ReassociationRequestFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211AssociationRequestFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->currentAP);
}

const ::inet::MacAddress& Ieee80211ReassociationRequestFrame::getCurrentAP() const
{
    return this->currentAP;
}

void Ieee80211ReassociationRequestFrame::setCurrentAP(const ::inet::MacAddress& currentAP)
{
    handleChange();
    this->currentAP = currentAP;
}

class Ieee80211ReassociationRequestFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_currentAP,
    };
  public:
    Ieee80211ReassociationRequestFrameDescriptor();
    virtual ~Ieee80211ReassociationRequestFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211ReassociationRequestFrameDescriptor)

Ieee80211ReassociationRequestFrameDescriptor::Ieee80211ReassociationRequestFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211ReassociationRequestFrame)), "inet::ieee80211::Ieee80211AssociationRequestFrame")
{
    propertyNames = nullptr;
}

Ieee80211ReassociationRequestFrameDescriptor::~Ieee80211ReassociationRequestFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ReassociationRequestFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ReassociationRequestFrame *>(obj)!=nullptr;
}

const char **Ieee80211ReassociationRequestFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ReassociationRequestFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ReassociationRequestFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211ReassociationRequestFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_currentAP
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211ReassociationRequestFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "currentAP",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211ReassociationRequestFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "currentAP") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ReassociationRequestFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_currentAP
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211ReassociationRequestFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ReassociationRequestFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ReassociationRequestFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ReassociationRequestFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ReassociationRequestFrame'", field);
    }
}

const char *Ieee80211ReassociationRequestFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ReassociationRequestFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_currentAP: return pp->getCurrentAP().str();
        default: return "";
    }
}

void Ieee80211ReassociationRequestFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationRequestFrame'", field);
    }
}

omnetpp::cValue Ieee80211ReassociationRequestFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_currentAP: return omnetpp::toAnyPtr(&pp->getCurrentAP()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ReassociationRequestFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ReassociationRequestFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationRequestFrame'", field);
    }
}

const char *Ieee80211ReassociationRequestFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211ReassociationRequestFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        case FIELD_currentAP: return omnetpp::toAnyPtr(&pp->getCurrentAP()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ReassociationRequestFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationRequestFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationRequestFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationRequestFrame'", field);
    }
}

Register_Class(Ieee80211AssociationResponseFrame)

Ieee80211AssociationResponseFrame::Ieee80211AssociationResponseFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
}

Ieee80211AssociationResponseFrame::Ieee80211AssociationResponseFrame(const Ieee80211AssociationResponseFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211AssociationResponseFrame::~Ieee80211AssociationResponseFrame()
{
}

Ieee80211AssociationResponseFrame& Ieee80211AssociationResponseFrame::operator=(const Ieee80211AssociationResponseFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AssociationResponseFrame::copy(const Ieee80211AssociationResponseFrame& other)
{
    this->statusCode = other.statusCode;
    this->aid = other.aid;
    this->supportedRates = other.supportedRates;
}

void Ieee80211AssociationResponseFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->statusCode);
    doParsimPacking(b,this->aid);
    doParsimPacking(b,this->supportedRates);
}

void Ieee80211AssociationResponseFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->statusCode);
    doParsimUnpacking(b,this->aid);
    doParsimUnpacking(b,this->supportedRates);
}

Ieee80211StatusCode Ieee80211AssociationResponseFrame::getStatusCode() const
{
    return this->statusCode;
}

void Ieee80211AssociationResponseFrame::setStatusCode(Ieee80211StatusCode statusCode)
{
    handleChange();
    this->statusCode = statusCode;
}

short Ieee80211AssociationResponseFrame::getAid() const
{
    return this->aid;
}

void Ieee80211AssociationResponseFrame::setAid(short aid)
{
    handleChange();
    this->aid = aid;
}

const Ieee80211SupportedRatesElement& Ieee80211AssociationResponseFrame::getSupportedRates() const
{
    return this->supportedRates;
}

void Ieee80211AssociationResponseFrame::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    handleChange();
    this->supportedRates = supportedRates;
}

class Ieee80211AssociationResponseFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_statusCode,
        FIELD_aid,
        FIELD_supportedRates,
    };
  public:
    Ieee80211AssociationResponseFrameDescriptor();
    virtual ~Ieee80211AssociationResponseFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211AssociationResponseFrameDescriptor)

Ieee80211AssociationResponseFrameDescriptor::Ieee80211AssociationResponseFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AssociationResponseFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211AssociationResponseFrameDescriptor::~Ieee80211AssociationResponseFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AssociationResponseFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AssociationResponseFrame *>(obj)!=nullptr;
}

const char **Ieee80211AssociationResponseFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AssociationResponseFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AssociationResponseFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211AssociationResponseFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_statusCode
        FD_ISEDITABLE,    // FIELD_aid
        FD_ISCOMPOUND,    // FIELD_supportedRates
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211AssociationResponseFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "statusCode",
        "aid",
        "supportedRates",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211AssociationResponseFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "statusCode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "aid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "supportedRates") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AssociationResponseFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211StatusCode",    // FIELD_statusCode
        "short",    // FIELD_aid
        "inet::ieee80211::Ieee80211SupportedRatesElement",    // FIELD_supportedRates
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211AssociationResponseFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_statusCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211AssociationResponseFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_statusCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211StatusCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211AssociationResponseFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AssociationResponseFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AssociationResponseFrame'", field);
    }
}

const char *Ieee80211AssociationResponseFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AssociationResponseFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: return enum2string(pp->getStatusCode(), "inet::ieee80211::Ieee80211StatusCode");
        case FIELD_aid: return long2string(pp->getAid());
        case FIELD_supportedRates: return "";
        default: return "";
    }
}

void Ieee80211AssociationResponseFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        case FIELD_aid: pp->setAid(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationResponseFrame'", field);
    }
}

omnetpp::cValue Ieee80211AssociationResponseFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: return static_cast<int>(pp->getStatusCode());
        case FIELD_aid: return pp->getAid();
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AssociationResponseFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AssociationResponseFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        case FIELD_aid: pp->setAid(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationResponseFrame'", field);
    }
}

const char *Ieee80211AssociationResponseFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_supportedRates: return omnetpp::opp_typename(typeid(Ieee80211SupportedRatesElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211AssociationResponseFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AssociationResponseFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AssociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211AssociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AssociationResponseFrame'", field);
    }
}

Register_Class(Ieee80211ReassociationResponseFrame)

Ieee80211ReassociationResponseFrame::Ieee80211ReassociationResponseFrame() : ::inet::ieee80211::Ieee80211AssociationResponseFrame()
{
}

Ieee80211ReassociationResponseFrame::Ieee80211ReassociationResponseFrame(const Ieee80211ReassociationResponseFrame& other) : ::inet::ieee80211::Ieee80211AssociationResponseFrame(other)
{
    copy(other);
}

Ieee80211ReassociationResponseFrame::~Ieee80211ReassociationResponseFrame()
{
}

Ieee80211ReassociationResponseFrame& Ieee80211ReassociationResponseFrame::operator=(const Ieee80211ReassociationResponseFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211AssociationResponseFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ReassociationResponseFrame::copy(const Ieee80211ReassociationResponseFrame& other)
{
}

void Ieee80211ReassociationResponseFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211AssociationResponseFrame::parsimPack(b);
}

void Ieee80211ReassociationResponseFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211AssociationResponseFrame::parsimUnpack(b);
}

class Ieee80211ReassociationResponseFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211ReassociationResponseFrameDescriptor();
    virtual ~Ieee80211ReassociationResponseFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211ReassociationResponseFrameDescriptor)

Ieee80211ReassociationResponseFrameDescriptor::Ieee80211ReassociationResponseFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211ReassociationResponseFrame)), "inet::ieee80211::Ieee80211AssociationResponseFrame")
{
    propertyNames = nullptr;
}

Ieee80211ReassociationResponseFrameDescriptor::~Ieee80211ReassociationResponseFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ReassociationResponseFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ReassociationResponseFrame *>(obj)!=nullptr;
}

const char **Ieee80211ReassociationResponseFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ReassociationResponseFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ReassociationResponseFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211ReassociationResponseFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211ReassociationResponseFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211ReassociationResponseFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ReassociationResponseFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211ReassociationResponseFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ReassociationResponseFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ReassociationResponseFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ReassociationResponseFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ReassociationResponseFrame'", field);
    }
}

const char *Ieee80211ReassociationResponseFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ReassociationResponseFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211ReassociationResponseFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationResponseFrame'", field);
    }
}

omnetpp::cValue Ieee80211ReassociationResponseFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ReassociationResponseFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ReassociationResponseFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationResponseFrame'", field);
    }
}

const char *Ieee80211ReassociationResponseFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211ReassociationResponseFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ReassociationResponseFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ReassociationResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ReassociationResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ReassociationResponseFrame'", field);
    }
}

Register_Class(Ieee80211BeaconFrame)

Ieee80211BeaconFrame::Ieee80211BeaconFrame() : ::inet::ieee80211::Ieee80211MgmtFrame()
{
}

Ieee80211BeaconFrame::Ieee80211BeaconFrame(const Ieee80211BeaconFrame& other) : ::inet::ieee80211::Ieee80211MgmtFrame(other)
{
    copy(other);
}

Ieee80211BeaconFrame::~Ieee80211BeaconFrame()
{
}

Ieee80211BeaconFrame& Ieee80211BeaconFrame::operator=(const Ieee80211BeaconFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211BeaconFrame::copy(const Ieee80211BeaconFrame& other)
{
    this->SSID = other.SSID;
    this->supportedRates = other.supportedRates;
    this->beaconInterval = other.beaconInterval;
    this->channelNumber = other.channelNumber;
    this->handoverParameters = other.handoverParameters;
}

void Ieee80211BeaconFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimPack(b);
    doParsimPacking(b,this->SSID);
    doParsimPacking(b,this->supportedRates);
    doParsimPacking(b,this->beaconInterval);
    doParsimPacking(b,this->channelNumber);
    doParsimPacking(b,this->handoverParameters);
}

void Ieee80211BeaconFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->SSID);
    doParsimUnpacking(b,this->supportedRates);
    doParsimUnpacking(b,this->beaconInterval);
    doParsimUnpacking(b,this->channelNumber);
    doParsimUnpacking(b,this->handoverParameters);
}

const char * Ieee80211BeaconFrame::getSSID() const
{
    return this->SSID.c_str();
}

void Ieee80211BeaconFrame::setSSID(const char * SSID)
{
    handleChange();
    this->SSID = SSID;
}

const Ieee80211SupportedRatesElement& Ieee80211BeaconFrame::getSupportedRates() const
{
    return this->supportedRates;
}

void Ieee80211BeaconFrame::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    handleChange();
    this->supportedRates = supportedRates;
}

::omnetpp::simtime_t Ieee80211BeaconFrame::getBeaconInterval() const
{
    return this->beaconInterval;
}

void Ieee80211BeaconFrame::setBeaconInterval(::omnetpp::simtime_t beaconInterval)
{
    handleChange();
    this->beaconInterval = beaconInterval;
}

int Ieee80211BeaconFrame::getChannelNumber() const
{
    return this->channelNumber;
}

void Ieee80211BeaconFrame::setChannelNumber(int channelNumber)
{
    handleChange();
    this->channelNumber = channelNumber;
}

const Ieee80211HandoverParameters& Ieee80211BeaconFrame::getHandoverParameters() const
{
    return this->handoverParameters;
}

void Ieee80211BeaconFrame::setHandoverParameters(const Ieee80211HandoverParameters& handoverParameters)
{
    handleChange();
    this->handoverParameters = handoverParameters;
}

class Ieee80211BeaconFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_SSID,
        FIELD_supportedRates,
        FIELD_beaconInterval,
        FIELD_channelNumber,
        FIELD_handoverParameters,
    };
  public:
    Ieee80211BeaconFrameDescriptor();
    virtual ~Ieee80211BeaconFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211BeaconFrameDescriptor)

Ieee80211BeaconFrameDescriptor::Ieee80211BeaconFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211BeaconFrame)), "inet::ieee80211::Ieee80211MgmtFrame")
{
    propertyNames = nullptr;
}

Ieee80211BeaconFrameDescriptor::~Ieee80211BeaconFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211BeaconFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211BeaconFrame *>(obj)!=nullptr;
}

const char **Ieee80211BeaconFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211BeaconFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211BeaconFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ieee80211BeaconFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_SSID
        FD_ISCOMPOUND,    // FIELD_supportedRates
        FD_ISEDITABLE,    // FIELD_beaconInterval
        FD_ISEDITABLE,    // FIELD_channelNumber
        FD_ISCOMPOUND,    // FIELD_handoverParameters
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211BeaconFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "SSID",
        "supportedRates",
        "beaconInterval",
        "channelNumber",
        "handoverParameters",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ieee80211BeaconFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "SSID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "supportedRates") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "beaconInterval") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "channelNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "handoverParameters") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211BeaconFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_SSID
        "inet::ieee80211::Ieee80211SupportedRatesElement",    // FIELD_supportedRates
        "omnetpp::simtime_t",    // FIELD_beaconInterval
        "int",    // FIELD_channelNumber
        "inet::ieee80211::Ieee80211HandoverParameters",    // FIELD_handoverParameters
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211BeaconFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211BeaconFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211BeaconFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211BeaconFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211BeaconFrame'", field);
    }
}

const char *Ieee80211BeaconFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211BeaconFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return oppstring2string(pp->getSSID());
        case FIELD_supportedRates: return "";
        case FIELD_beaconInterval: return simtime2string(pp->getBeaconInterval());
        case FIELD_channelNumber: return long2string(pp->getChannelNumber());
        case FIELD_handoverParameters: return "";
        default: return "";
    }
}

void Ieee80211BeaconFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID((value)); break;
        case FIELD_beaconInterval: pp->setBeaconInterval(string2simtime(value)); break;
        case FIELD_channelNumber: pp->setChannelNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BeaconFrame'", field);
    }
}

omnetpp::cValue Ieee80211BeaconFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: return pp->getSSID();
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        case FIELD_beaconInterval: return pp->getBeaconInterval().dbl();
        case FIELD_channelNumber: return pp->getChannelNumber();
        case FIELD_handoverParameters: return omnetpp::toAnyPtr(&pp->getHandoverParameters()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211BeaconFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211BeaconFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID(value.stringValue()); break;
        case FIELD_beaconInterval: pp->setBeaconInterval(value.doubleValue()); break;
        case FIELD_channelNumber: pp->setChannelNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BeaconFrame'", field);
    }
}

const char *Ieee80211BeaconFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_supportedRates: return omnetpp::opp_typename(typeid(Ieee80211SupportedRatesElement));
        case FIELD_handoverParameters: return omnetpp::opp_typename(typeid(Ieee80211HandoverParameters));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211BeaconFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        case FIELD_handoverParameters: return omnetpp::toAnyPtr(&pp->getHandoverParameters()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211BeaconFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BeaconFrame *pp = omnetpp::fromAnyPtr<Ieee80211BeaconFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BeaconFrame'", field);
    }
}

Register_Class(Ieee80211ProbeResponseFrame)

Ieee80211ProbeResponseFrame::Ieee80211ProbeResponseFrame() : ::inet::ieee80211::Ieee80211BeaconFrame()
{
}

Ieee80211ProbeResponseFrame::Ieee80211ProbeResponseFrame(const Ieee80211ProbeResponseFrame& other) : ::inet::ieee80211::Ieee80211BeaconFrame(other)
{
    copy(other);
}

Ieee80211ProbeResponseFrame::~Ieee80211ProbeResponseFrame()
{
}

Ieee80211ProbeResponseFrame& Ieee80211ProbeResponseFrame::operator=(const Ieee80211ProbeResponseFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BeaconFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ProbeResponseFrame::copy(const Ieee80211ProbeResponseFrame& other)
{
}

void Ieee80211ProbeResponseFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BeaconFrame::parsimPack(b);
}

void Ieee80211ProbeResponseFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BeaconFrame::parsimUnpack(b);
}

class Ieee80211ProbeResponseFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211ProbeResponseFrameDescriptor();
    virtual ~Ieee80211ProbeResponseFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211ProbeResponseFrameDescriptor)

Ieee80211ProbeResponseFrameDescriptor::Ieee80211ProbeResponseFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211ProbeResponseFrame)), "inet::ieee80211::Ieee80211BeaconFrame")
{
    propertyNames = nullptr;
}

Ieee80211ProbeResponseFrameDescriptor::~Ieee80211ProbeResponseFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ProbeResponseFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ProbeResponseFrame *>(obj)!=nullptr;
}

const char **Ieee80211ProbeResponseFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ProbeResponseFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ProbeResponseFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211ProbeResponseFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211ProbeResponseFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211ProbeResponseFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ProbeResponseFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211ProbeResponseFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ProbeResponseFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ProbeResponseFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ProbeResponseFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ProbeResponseFrame'", field);
    }
}

const char *Ieee80211ProbeResponseFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ProbeResponseFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211ProbeResponseFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeResponseFrame'", field);
    }
}

omnetpp::cValue Ieee80211ProbeResponseFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ProbeResponseFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ProbeResponseFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeResponseFrame'", field);
    }
}

const char *Ieee80211ProbeResponseFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211ProbeResponseFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ProbeResponseFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ProbeResponseFrame *pp = omnetpp::fromAnyPtr<Ieee80211ProbeResponseFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ProbeResponseFrame'", field);
    }
}

}  // namespace ieee80211
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

