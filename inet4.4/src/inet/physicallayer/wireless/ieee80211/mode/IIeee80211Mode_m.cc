//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/ieee80211/mode/IIeee80211Mode.msg.
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
#include "IIeee80211Mode_m.h"

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
namespace physicallayer {

class IIeee80211PreambleModeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_duration,
    };
  public:
    IIeee80211PreambleModeDescriptor();
    virtual ~IIeee80211PreambleModeDescriptor();

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

Register_ClassDescriptor(IIeee80211PreambleModeDescriptor)

IIeee80211PreambleModeDescriptor::IIeee80211PreambleModeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::IIeee80211PreambleMode)), "")
{
    propertyNames = nullptr;
}

IIeee80211PreambleModeDescriptor::~IIeee80211PreambleModeDescriptor()
{
    delete[] propertyNames;
}

bool IIeee80211PreambleModeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IIeee80211PreambleMode *>(obj)!=nullptr;
}

const char **IIeee80211PreambleModeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IIeee80211PreambleModeDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IIeee80211PreambleModeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int IIeee80211PreambleModeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_duration
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *IIeee80211PreambleModeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "duration",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int IIeee80211PreambleModeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "duration") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *IIeee80211PreambleModeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_duration
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **IIeee80211PreambleModeDescriptor::getFieldPropertyNames(int field) const
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

const char *IIeee80211PreambleModeDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IIeee80211PreambleModeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IIeee80211PreambleModeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IIeee80211PreambleMode'", field);
    }
}

const char *IIeee80211PreambleModeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IIeee80211PreambleModeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        case FIELD_duration: return simtime2string(pp->getDuration());
        default: return "";
    }
}

void IIeee80211PreambleModeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211PreambleMode'", field);
    }
}

omnetpp::cValue IIeee80211PreambleModeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        case FIELD_duration: return pp->getDuration().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IIeee80211PreambleMode' as cValue -- field index out of range?", field);
    }
}

void IIeee80211PreambleModeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211PreambleMode'", field);
    }
}

const char *IIeee80211PreambleModeDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IIeee80211PreambleModeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IIeee80211PreambleModeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211PreambleMode *pp = omnetpp::fromAnyPtr<IIeee80211PreambleMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211PreambleMode'", field);
    }
}

class IIeee80211HeaderModeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_netBitrate,
        FIELD_grossBitrate,
        FIELD_Length,
        FIELD_duration,
        FIELD_modulation,
    };
  public:
    IIeee80211HeaderModeDescriptor();
    virtual ~IIeee80211HeaderModeDescriptor();

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

Register_ClassDescriptor(IIeee80211HeaderModeDescriptor)

IIeee80211HeaderModeDescriptor::IIeee80211HeaderModeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::IIeee80211HeaderMode)), "")
{
    propertyNames = nullptr;
}

IIeee80211HeaderModeDescriptor::~IIeee80211HeaderModeDescriptor()
{
    delete[] propertyNames;
}

bool IIeee80211HeaderModeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IIeee80211HeaderMode *>(obj)!=nullptr;
}

const char **IIeee80211HeaderModeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IIeee80211HeaderModeDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IIeee80211HeaderModeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int IIeee80211HeaderModeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_netBitrate
        0,    // FIELD_grossBitrate
        0,    // FIELD_Length
        0,    // FIELD_duration
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_modulation
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *IIeee80211HeaderModeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "netBitrate",
        "grossBitrate",
        "Length",
        "duration",
        "modulation",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int IIeee80211HeaderModeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "netBitrate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "grossBitrate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "Length") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "duration") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "modulation") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *IIeee80211HeaderModeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bps",    // FIELD_netBitrate
        "inet::bps",    // FIELD_grossBitrate
        "inet::b",    // FIELD_Length
        "omnetpp::simtime_t",    // FIELD_duration
        "inet::physicallayer::IModulation",    // FIELD_modulation
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **IIeee80211HeaderModeDescriptor::getFieldPropertyNames(int field) const
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

const char *IIeee80211HeaderModeDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IIeee80211HeaderModeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IIeee80211HeaderModeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IIeee80211HeaderMode'", field);
    }
}

const char *IIeee80211HeaderModeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: { const IModulation * value = pp->getModulation(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string IIeee80211HeaderModeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        case FIELD_netBitrate: return unit2string(pp->getNetBitrate());
        case FIELD_grossBitrate: return unit2string(pp->getGrossBitrate());
        case FIELD_Length: return unit2string(pp->getLength());
        case FIELD_duration: return simtime2string(pp->getDuration());
        case FIELD_modulation: return "";
        default: return "";
    }
}

void IIeee80211HeaderModeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211HeaderMode'", field);
    }
}

omnetpp::cValue IIeee80211HeaderModeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        case FIELD_netBitrate: return cValue(pp->getNetBitrate().get(),"bps");
        case FIELD_grossBitrate: return cValue(pp->getGrossBitrate().get(),"bps");
        case FIELD_Length: return cValue(pp->getLength().get(),"b");
        case FIELD_duration: return pp->getDuration().dbl();
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IIeee80211HeaderMode' as cValue -- field index out of range?", field);
    }
}

void IIeee80211HeaderModeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211HeaderMode'", field);
    }
}

const char *IIeee80211HeaderModeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_modulation: return omnetpp::opp_typename(typeid(IModulation));
        default: return nullptr;
    };
}

omnetpp::any_ptr IIeee80211HeaderModeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IIeee80211HeaderModeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211HeaderMode *pp = omnetpp::fromAnyPtr<IIeee80211HeaderMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211HeaderMode'", field);
    }
}

class IIeee80211DataModeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_netBitrate,
        FIELD_grossBitrate,
        FIELD_modulation,
        FIELD_numberOfSpatialStreams,
    };
  public:
    IIeee80211DataModeDescriptor();
    virtual ~IIeee80211DataModeDescriptor();

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

Register_ClassDescriptor(IIeee80211DataModeDescriptor)

IIeee80211DataModeDescriptor::IIeee80211DataModeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::IIeee80211DataMode)), "")
{
    propertyNames = nullptr;
}

IIeee80211DataModeDescriptor::~IIeee80211DataModeDescriptor()
{
    delete[] propertyNames;
}

bool IIeee80211DataModeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IIeee80211DataMode *>(obj)!=nullptr;
}

const char **IIeee80211DataModeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IIeee80211DataModeDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IIeee80211DataModeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int IIeee80211DataModeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_netBitrate
        0,    // FIELD_grossBitrate
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_modulation
        0,    // FIELD_numberOfSpatialStreams
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *IIeee80211DataModeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "netBitrate",
        "grossBitrate",
        "modulation",
        "numberOfSpatialStreams",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int IIeee80211DataModeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "netBitrate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "grossBitrate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "modulation") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "numberOfSpatialStreams") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *IIeee80211DataModeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bps",    // FIELD_netBitrate
        "inet::bps",    // FIELD_grossBitrate
        "inet::physicallayer::IModulation",    // FIELD_modulation
        "int",    // FIELD_numberOfSpatialStreams
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **IIeee80211DataModeDescriptor::getFieldPropertyNames(int field) const
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

const char *IIeee80211DataModeDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IIeee80211DataModeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IIeee80211DataModeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IIeee80211DataMode'", field);
    }
}

const char *IIeee80211DataModeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: { const IModulation * value = pp->getModulation(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string IIeee80211DataModeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        case FIELD_netBitrate: return unit2string(pp->getNetBitrate());
        case FIELD_grossBitrate: return unit2string(pp->getGrossBitrate());
        case FIELD_modulation: return "";
        case FIELD_numberOfSpatialStreams: return long2string(pp->getNumberOfSpatialStreams());
        default: return "";
    }
}

void IIeee80211DataModeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211DataMode'", field);
    }
}

omnetpp::cValue IIeee80211DataModeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        case FIELD_netBitrate: return cValue(pp->getNetBitrate().get(),"bps");
        case FIELD_grossBitrate: return cValue(pp->getGrossBitrate().get(),"bps");
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        case FIELD_numberOfSpatialStreams: return pp->getNumberOfSpatialStreams();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IIeee80211DataMode' as cValue -- field index out of range?", field);
    }
}

void IIeee80211DataModeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211DataMode'", field);
    }
}

const char *IIeee80211DataModeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_modulation: return omnetpp::opp_typename(typeid(IModulation));
        default: return nullptr;
    };
}

omnetpp::any_ptr IIeee80211DataModeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        case FIELD_modulation: return omnetpp::toAnyPtr(pp->getModulation()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IIeee80211DataModeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211DataMode *pp = omnetpp::fromAnyPtr<IIeee80211DataMode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211DataMode'", field);
    }
}

class IIeee80211ModeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_legacyCwMin,
        FIELD_legacyCwMax,
        FIELD_name,
        FIELD_preambleMode,
        FIELD_headerMode,
        FIELD_dataMode,
        FIELD_slotTime,
        FIELD_sifsTime,
        FIELD_rifsTime,
        FIELD_ccaTime,
        FIELD_phyRxStartDelay,
        FIELD_rxTxTurnaroundTime,
        FIELD_preambleLength,
        FIELD_plcpHeaderLength,
        FIELD_mpduMaxLength,
    };
  public:
    IIeee80211ModeDescriptor();
    virtual ~IIeee80211ModeDescriptor();

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

Register_ClassDescriptor(IIeee80211ModeDescriptor)

IIeee80211ModeDescriptor::IIeee80211ModeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::IIeee80211Mode)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

IIeee80211ModeDescriptor::~IIeee80211ModeDescriptor()
{
    delete[] propertyNames;
}

bool IIeee80211ModeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IIeee80211Mode *>(obj)!=nullptr;
}

const char **IIeee80211ModeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IIeee80211ModeDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IIeee80211ModeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 15+base->getFieldCount() : 15;
}

unsigned int IIeee80211ModeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_legacyCwMin
        0,    // FIELD_legacyCwMax
        0,    // FIELD_name
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_preambleMode
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_headerMode
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_dataMode
        0,    // FIELD_slotTime
        0,    // FIELD_sifsTime
        0,    // FIELD_rifsTime
        0,    // FIELD_ccaTime
        0,    // FIELD_phyRxStartDelay
        0,    // FIELD_rxTxTurnaroundTime
        0,    // FIELD_preambleLength
        0,    // FIELD_plcpHeaderLength
        0,    // FIELD_mpduMaxLength
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
}

const char *IIeee80211ModeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "legacyCwMin",
        "legacyCwMax",
        "name",
        "preambleMode",
        "headerMode",
        "dataMode",
        "slotTime",
        "sifsTime",
        "rifsTime",
        "ccaTime",
        "phyRxStartDelay",
        "rxTxTurnaroundTime",
        "preambleLength",
        "plcpHeaderLength",
        "mpduMaxLength",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int IIeee80211ModeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "legacyCwMin") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "legacyCwMax") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "name") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "preambleMode") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "headerMode") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "dataMode") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "slotTime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sifsTime") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "rifsTime") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "ccaTime") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "phyRxStartDelay") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "rxTxTurnaroundTime") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "preambleLength") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "plcpHeaderLength") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "mpduMaxLength") == 0) return baseIndex + 14;
    return base ? base->findField(fieldName) : -1;
}

const char *IIeee80211ModeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_legacyCwMin
        "int",    // FIELD_legacyCwMax
        "string",    // FIELD_name
        "inet::physicallayer::IIeee80211PreambleMode",    // FIELD_preambleMode
        "inet::physicallayer::IIeee80211HeaderMode",    // FIELD_headerMode
        "inet::physicallayer::IIeee80211DataMode",    // FIELD_dataMode
        "omnetpp::simtime_t",    // FIELD_slotTime
        "omnetpp::simtime_t",    // FIELD_sifsTime
        "omnetpp::simtime_t",    // FIELD_rifsTime
        "omnetpp::simtime_t",    // FIELD_ccaTime
        "omnetpp::simtime_t",    // FIELD_phyRxStartDelay
        "omnetpp::simtime_t",    // FIELD_rxTxTurnaroundTime
        "omnetpp::simtime_t",    // FIELD_preambleLength
        "omnetpp::simtime_t",    // FIELD_plcpHeaderLength
        "int",    // FIELD_mpduMaxLength
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
}

const char **IIeee80211ModeDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_preambleMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_headerMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_dataMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *IIeee80211ModeDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_preambleMode:
            if (!strcmp(propertyName, "getter")) return "_getPreambleMode";
            return nullptr;
        case FIELD_headerMode:
            if (!strcmp(propertyName, "getter")) return "_getHeaderMode";
            return nullptr;
        case FIELD_dataMode:
            if (!strcmp(propertyName, "getter")) return "_getDataMode";
            return nullptr;
        default: return nullptr;
    }
}

int IIeee80211ModeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IIeee80211ModeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IIeee80211Mode'", field);
    }
}

const char *IIeee80211ModeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        case FIELD_preambleMode: { const IIeee80211PreambleMode * value = pp->_getPreambleMode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_headerMode: { const IIeee80211HeaderMode * value = pp->_getHeaderMode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_dataMode: { const IIeee80211DataMode * value = pp->_getDataMode(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string IIeee80211ModeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        case FIELD_legacyCwMin: return long2string(pp->getLegacyCwMin());
        case FIELD_legacyCwMax: return long2string(pp->getLegacyCwMax());
        case FIELD_name: return oppstring2string(pp->getName());
        case FIELD_preambleMode: return "";
        case FIELD_headerMode: return "";
        case FIELD_dataMode: return "";
        case FIELD_slotTime: return simtime2string(pp->getSlotTime());
        case FIELD_sifsTime: return simtime2string(pp->getSifsTime());
        case FIELD_rifsTime: return simtime2string(pp->getRifsTime());
        case FIELD_ccaTime: return simtime2string(pp->getCcaTime());
        case FIELD_phyRxStartDelay: return simtime2string(pp->getPhyRxStartDelay());
        case FIELD_rxTxTurnaroundTime: return simtime2string(pp->getRxTxTurnaroundTime());
        case FIELD_preambleLength: return simtime2string(pp->getPreambleLength());
        case FIELD_plcpHeaderLength: return simtime2string(pp->getPlcpHeaderLength());
        case FIELD_mpduMaxLength: return long2string(pp->getMpduMaxLength());
        default: return "";
    }
}

void IIeee80211ModeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211Mode'", field);
    }
}

omnetpp::cValue IIeee80211ModeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        case FIELD_legacyCwMin: return pp->getLegacyCwMin();
        case FIELD_legacyCwMax: return pp->getLegacyCwMax();
        case FIELD_name: return pp->getName();
        case FIELD_preambleMode: return omnetpp::toAnyPtr(pp->_getPreambleMode()); break;
        case FIELD_headerMode: return omnetpp::toAnyPtr(pp->_getHeaderMode()); break;
        case FIELD_dataMode: return omnetpp::toAnyPtr(pp->_getDataMode()); break;
        case FIELD_slotTime: return pp->getSlotTime().dbl();
        case FIELD_sifsTime: return pp->getSifsTime().dbl();
        case FIELD_rifsTime: return pp->getRifsTime().dbl();
        case FIELD_ccaTime: return pp->getCcaTime().dbl();
        case FIELD_phyRxStartDelay: return pp->getPhyRxStartDelay().dbl();
        case FIELD_rxTxTurnaroundTime: return pp->getRxTxTurnaroundTime().dbl();
        case FIELD_preambleLength: return pp->getPreambleLength().dbl();
        case FIELD_plcpHeaderLength: return pp->getPlcpHeaderLength().dbl();
        case FIELD_mpduMaxLength: return pp->getMpduMaxLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IIeee80211Mode' as cValue -- field index out of range?", field);
    }
}

void IIeee80211ModeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211Mode'", field);
    }
}

const char *IIeee80211ModeDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_preambleMode: return omnetpp::opp_typename(typeid(IIeee80211PreambleMode));
        case FIELD_headerMode: return omnetpp::opp_typename(typeid(IIeee80211HeaderMode));
        case FIELD_dataMode: return omnetpp::opp_typename(typeid(IIeee80211DataMode));
        default: return nullptr;
    };
}

omnetpp::any_ptr IIeee80211ModeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        case FIELD_preambleMode: return omnetpp::toAnyPtr(pp->_getPreambleMode()); break;
        case FIELD_headerMode: return omnetpp::toAnyPtr(pp->_getHeaderMode()); break;
        case FIELD_dataMode: return omnetpp::toAnyPtr(pp->_getDataMode()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IIeee80211ModeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IIeee80211Mode *pp = omnetpp::fromAnyPtr<IIeee80211Mode>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IIeee80211Mode'", field);
    }
}

class Ieee80211ModeSetDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_slowestMode,
        FIELD_fastestMode,
        FIELD_slowestMandatoryMode,
        FIELD_fastestMandatoryMode,
        FIELD_sifsTime,
        FIELD_slotTime,
        FIELD_phyRxStartDelay,
        FIELD_cwMin,
        FIELD_cwMax,
    };
  public:
    Ieee80211ModeSetDescriptor();
    virtual ~Ieee80211ModeSetDescriptor();

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

Register_ClassDescriptor(Ieee80211ModeSetDescriptor)

Ieee80211ModeSetDescriptor::Ieee80211ModeSetDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211ModeSet)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ieee80211ModeSetDescriptor::~Ieee80211ModeSetDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ModeSetDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ModeSet *>(obj)!=nullptr;
}

const char **Ieee80211ModeSetDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ModeSetDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ModeSetDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ieee80211ModeSetDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_slowestMode
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_fastestMode
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_slowestMandatoryMode
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_fastestMandatoryMode
        0,    // FIELD_sifsTime
        0,    // FIELD_slotTime
        0,    // FIELD_phyRxStartDelay
        0,    // FIELD_cwMin
        0,    // FIELD_cwMax
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211ModeSetDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "slowestMode",
        "fastestMode",
        "slowestMandatoryMode",
        "fastestMandatoryMode",
        "sifsTime",
        "slotTime",
        "phyRxStartDelay",
        "cwMin",
        "cwMax",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ieee80211ModeSetDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "slowestMode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fastestMode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "slowestMandatoryMode") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "fastestMandatoryMode") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sifsTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "slotTime") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "phyRxStartDelay") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "cwMin") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "cwMax") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ModeSetDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::physicallayer::IIeee80211Mode",    // FIELD_slowestMode
        "inet::physicallayer::IIeee80211Mode",    // FIELD_fastestMode
        "inet::physicallayer::IIeee80211Mode",    // FIELD_slowestMandatoryMode
        "inet::physicallayer::IIeee80211Mode",    // FIELD_fastestMandatoryMode
        "omnetpp::simtime_t",    // FIELD_sifsTime
        "omnetpp::simtime_t",    // FIELD_slotTime
        "omnetpp::simtime_t",    // FIELD_phyRxStartDelay
        "int",    // FIELD_cwMin
        "int",    // FIELD_cwMax
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211ModeSetDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_slowestMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_fastestMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_slowestMandatoryMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        case FIELD_fastestMandatoryMode: {
            static const char *names[] = { "getter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211ModeSetDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_slowestMode:
            if (!strcmp(propertyName, "getter")) return "_getSlowestMode";
            return nullptr;
        case FIELD_fastestMode:
            if (!strcmp(propertyName, "getter")) return "_getFastestMode";
            return nullptr;
        case FIELD_slowestMandatoryMode:
            if (!strcmp(propertyName, "getter")) return "_getSlowestMandatoryMode";
            return nullptr;
        case FIELD_fastestMandatoryMode:
            if (!strcmp(propertyName, "getter")) return "_getFastestMandatoryMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211ModeSetDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ModeSetDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ModeSet'", field);
    }
}

const char *Ieee80211ModeSetDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        case FIELD_slowestMode: { const IIeee80211Mode * value = pp->_getSlowestMode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_fastestMode: { const IIeee80211Mode * value = pp->_getFastestMode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_slowestMandatoryMode: { const IIeee80211Mode * value = pp->_getSlowestMandatoryMode(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_fastestMandatoryMode: { const IIeee80211Mode * value = pp->_getFastestMandatoryMode(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ieee80211ModeSetDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        case FIELD_slowestMode: { auto obj = pp->_getSlowestMode(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_fastestMode: { auto obj = pp->_getFastestMode(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_slowestMandatoryMode: { auto obj = pp->_getSlowestMandatoryMode(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_fastestMandatoryMode: { auto obj = pp->_getFastestMandatoryMode(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_sifsTime: return simtime2string(pp->getSifsTime());
        case FIELD_slotTime: return simtime2string(pp->getSlotTime());
        case FIELD_phyRxStartDelay: return simtime2string(pp->getPhyRxStartDelay());
        case FIELD_cwMin: return long2string(pp->getCwMin());
        case FIELD_cwMax: return long2string(pp->getCwMax());
        default: return "";
    }
}

void Ieee80211ModeSetDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ModeSet'", field);
    }
}

omnetpp::cValue Ieee80211ModeSetDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        case FIELD_slowestMode: return omnetpp::toAnyPtr(pp->_getSlowestMode()); break;
        case FIELD_fastestMode: return omnetpp::toAnyPtr(pp->_getFastestMode()); break;
        case FIELD_slowestMandatoryMode: return omnetpp::toAnyPtr(pp->_getSlowestMandatoryMode()); break;
        case FIELD_fastestMandatoryMode: return omnetpp::toAnyPtr(pp->_getFastestMandatoryMode()); break;
        case FIELD_sifsTime: return pp->getSifsTime().dbl();
        case FIELD_slotTime: return pp->getSlotTime().dbl();
        case FIELD_phyRxStartDelay: return pp->getPhyRxStartDelay().dbl();
        case FIELD_cwMin: return pp->getCwMin();
        case FIELD_cwMax: return pp->getCwMax();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ModeSet' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ModeSetDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ModeSet'", field);
    }
}

const char *Ieee80211ModeSetDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_slowestMode: return omnetpp::opp_typename(typeid(IIeee80211Mode));
        case FIELD_fastestMode: return omnetpp::opp_typename(typeid(IIeee80211Mode));
        case FIELD_slowestMandatoryMode: return omnetpp::opp_typename(typeid(IIeee80211Mode));
        case FIELD_fastestMandatoryMode: return omnetpp::opp_typename(typeid(IIeee80211Mode));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211ModeSetDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        case FIELD_slowestMode: return omnetpp::toAnyPtr(pp->_getSlowestMode()); break;
        case FIELD_fastestMode: return omnetpp::toAnyPtr(pp->_getFastestMode()); break;
        case FIELD_slowestMandatoryMode: return omnetpp::toAnyPtr(pp->_getSlowestMandatoryMode()); break;
        case FIELD_fastestMandatoryMode: return omnetpp::toAnyPtr(pp->_getFastestMandatoryMode()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ModeSetDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ModeSet *pp = omnetpp::fromAnyPtr<Ieee80211ModeSet>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ModeSet'", field);
    }
}

class Ieee80211OfdmModulationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_subcarrierModulation,
    };
  public:
    Ieee80211OfdmModulationDescriptor();
    virtual ~Ieee80211OfdmModulationDescriptor();

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

Register_ClassDescriptor(Ieee80211OfdmModulationDescriptor)

Ieee80211OfdmModulationDescriptor::Ieee80211OfdmModulationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211OfdmModulation)), "inet::physicallayer::IModulation")
{
    propertyNames = nullptr;
}

Ieee80211OfdmModulationDescriptor::~Ieee80211OfdmModulationDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211OfdmModulationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211OfdmModulation *>(obj)!=nullptr;
}

const char **Ieee80211OfdmModulationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211OfdmModulationDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211OfdmModulationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211OfdmModulationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_subcarrierModulation
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211OfdmModulationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "subcarrierModulation",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211OfdmModulationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "subcarrierModulation") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211OfdmModulationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::physicallayer::IModulation",    // FIELD_subcarrierModulation
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211OfdmModulationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211OfdmModulationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211OfdmModulationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211OfdmModulationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211OfdmModulation'", field);
    }
}

const char *Ieee80211OfdmModulationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        case FIELD_subcarrierModulation: { const IModulation * value = pp->getSubcarrierModulation(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ieee80211OfdmModulationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        case FIELD_subcarrierModulation: return "";
        default: return "";
    }
}

void Ieee80211OfdmModulationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmModulation'", field);
    }
}

omnetpp::cValue Ieee80211OfdmModulationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        case FIELD_subcarrierModulation: return omnetpp::toAnyPtr(pp->getSubcarrierModulation()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211OfdmModulation' as cValue -- field index out of range?", field);
    }
}

void Ieee80211OfdmModulationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmModulation'", field);
    }
}

const char *Ieee80211OfdmModulationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_subcarrierModulation: return omnetpp::opp_typename(typeid(IModulation));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211OfdmModulationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        case FIELD_subcarrierModulation: return omnetpp::toAnyPtr(pp->getSubcarrierModulation()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211OfdmModulationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmModulation *pp = omnetpp::fromAnyPtr<Ieee80211OfdmModulation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmModulation'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

