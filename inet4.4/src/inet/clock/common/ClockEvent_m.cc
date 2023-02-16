//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/clock/common/ClockEvent.msg.
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
#include "ClockEvent_m.h"

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

Register_Enum(inet::OverdueClockEventHandlingMode, (inet::OverdueClockEventHandlingMode::UNSPECIFIED, inet::OverdueClockEventHandlingMode::EXECUTE, inet::OverdueClockEventHandlingMode::SKIP, inet::OverdueClockEventHandlingMode::ERROR));

ClockEvent_Base::ClockEvent_Base(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ClockEvent_Base::ClockEvent_Base(const ClockEvent_Base& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ClockEvent_Base::~ClockEvent_Base()
{
}

ClockEvent_Base& ClockEvent_Base::operator=(const ClockEvent_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ClockEvent_Base::copy(const ClockEvent_Base& other)
{
    this->clock = other.clock;
    this->relative = other.relative;
    this->arrivalClockTime = other.arrivalClockTime;
    this->overdueClockEventHandlingMode = other.overdueClockEventHandlingMode;
}

void ClockEvent_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->clock);
    doParsimPacking(b,this->relative);
    doParsimPacking(b,this->arrivalClockTime);
    doParsimPacking(b,this->overdueClockEventHandlingMode);
}

void ClockEvent_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->clock);
    doParsimUnpacking(b,this->relative);
    doParsimUnpacking(b,this->arrivalClockTime);
    doParsimUnpacking(b,this->overdueClockEventHandlingMode);
}

const IClock * ClockEvent_Base::getClock() const
{
    return this->clock;
}

void ClockEvent_Base::setClock(IClock * clock)
{
    this->clock = clock;
}

bool ClockEvent_Base::getRelative() const
{
    return this->relative;
}

void ClockEvent_Base::setRelative(bool relative)
{
    this->relative = relative;
}

clocktime_t ClockEvent_Base::getArrivalClockTime() const
{
    return this->arrivalClockTime;
}

void ClockEvent_Base::setArrivalClockTime(clocktime_t arrivalClockTime)
{
    this->arrivalClockTime = arrivalClockTime;
}

OverdueClockEventHandlingMode ClockEvent_Base::getOverdueClockEventHandlingMode() const
{
    return this->overdueClockEventHandlingMode;
}

void ClockEvent_Base::setOverdueClockEventHandlingMode(OverdueClockEventHandlingMode overdueClockEventHandlingMode)
{
    this->overdueClockEventHandlingMode = overdueClockEventHandlingMode;
}

class ClockEventDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clock,
        FIELD_relative,
        FIELD_arrivalClockTime,
        FIELD_overdueClockEventHandlingMode,
    };
  public:
    ClockEventDescriptor();
    virtual ~ClockEventDescriptor();

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

Register_ClassDescriptor(ClockEventDescriptor)

ClockEventDescriptor::ClockEventDescriptor() : omnetpp::cClassDescriptor("inet::ClockEvent", "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ClockEventDescriptor::~ClockEventDescriptor()
{
    delete[] propertyNames;
}

bool ClockEventDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ClockEvent_Base *>(obj)!=nullptr;
}

const char **ClockEventDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ClockEventDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ClockEventDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ClockEventDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_clock
        FD_ISEDITABLE,    // FIELD_relative
        0,    // FIELD_arrivalClockTime
        0,    // FIELD_overdueClockEventHandlingMode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ClockEventDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clock",
        "relative",
        "arrivalClockTime",
        "overdueClockEventHandlingMode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ClockEventDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clock") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "relative") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "arrivalClockTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "overdueClockEventHandlingMode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ClockEventDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::IClock",    // FIELD_clock
        "bool",    // FIELD_relative
        "inet::clocktime_t",    // FIELD_arrivalClockTime
        "inet::OverdueClockEventHandlingMode",    // FIELD_overdueClockEventHandlingMode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ClockEventDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_overdueClockEventHandlingMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *ClockEventDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_overdueClockEventHandlingMode:
            if (!strcmp(propertyName, "enum")) return "inet::OverdueClockEventHandlingMode";
            return nullptr;
        default: return nullptr;
    }
}

int ClockEventDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ClockEventDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ClockEvent_Base'", field);
    }
}

const char *ClockEventDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: { const IClock * value = pp->getClock(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string ClockEventDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: return "";
        case FIELD_relative: return bool2string(pp->getRelative());
        case FIELD_arrivalClockTime: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getArrivalClockTime()));
        case FIELD_overdueClockEventHandlingMode: return enum2string(pp->getOverdueClockEventHandlingMode(), "inet::OverdueClockEventHandlingMode");
        default: return "";
    }
}

void ClockEventDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_relative: pp->setRelative(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClockEvent_Base'", field);
    }
}

omnetpp::cValue ClockEventDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: return omnetpp::toAnyPtr(pp->getClock()); break;
        case FIELD_relative: return pp->getRelative();
        case FIELD_arrivalClockTime: return cValue(pp->getArrivalClockTime().dbl(),"s");
        case FIELD_overdueClockEventHandlingMode: return static_cast<int>(pp->getOverdueClockEventHandlingMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ClockEvent_Base' as cValue -- field index out of range?", field);
    }
}

void ClockEventDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: pp->setClock(omnetpp::fromAnyPtr<IClock>(value.pointerValue())); break;
        case FIELD_relative: pp->setRelative(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClockEvent_Base'", field);
    }
}

const char *ClockEventDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_clock: return omnetpp::opp_typename(typeid(IClock));
        default: return nullptr;
    };
}

omnetpp::any_ptr ClockEventDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: return omnetpp::toAnyPtr(pp->getClock()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ClockEventDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ClockEvent_Base *pp = omnetpp::fromAnyPtr<ClockEvent_Base>(object); (void)pp;
    switch (field) {
        case FIELD_clock: pp->setClock(omnetpp::fromAnyPtr<IClock>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClockEvent_Base'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

