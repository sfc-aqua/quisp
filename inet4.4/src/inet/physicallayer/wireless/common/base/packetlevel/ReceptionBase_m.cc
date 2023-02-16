//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/common/base/packetlevel/ReceptionBase.msg.
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
#include "ReceptionBase_m.h"

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

class ReceptionBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_startTime,
        FIELD_startPosition,
        FIELD_startOrientation,
        FIELD_endTime,
        FIELD_endPosition,
        FIELD_endOrientation,
        FIELD_duration,
        FIELD_preambleDuration,
        FIELD_headerDuration,
        FIELD_dataDuration,
        FIELD_transmission,
    };
  public:
    ReceptionBaseDescriptor();
    virtual ~ReceptionBaseDescriptor();

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

Register_ClassDescriptor(ReceptionBaseDescriptor)

ReceptionBaseDescriptor::ReceptionBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::ReceptionBase)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

ReceptionBaseDescriptor::~ReceptionBaseDescriptor()
{
    delete[] propertyNames;
}

bool ReceptionBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ReceptionBase *>(obj)!=nullptr;
}

const char **ReceptionBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ReceptionBaseDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ReceptionBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int ReceptionBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_startTime
        FD_ISCOMPOUND,    // FIELD_startPosition
        FD_ISCOMPOUND,    // FIELD_startOrientation
        0,    // FIELD_endTime
        FD_ISCOMPOUND,    // FIELD_endPosition
        FD_ISCOMPOUND,    // FIELD_endOrientation
        0,    // FIELD_duration
        0,    // FIELD_preambleDuration
        0,    // FIELD_headerDuration
        0,    // FIELD_dataDuration
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_transmission
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *ReceptionBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "startTime",
        "startPosition",
        "startOrientation",
        "endTime",
        "endPosition",
        "endOrientation",
        "duration",
        "preambleDuration",
        "headerDuration",
        "dataDuration",
        "transmission",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int ReceptionBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "startTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "startPosition") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "startOrientation") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "endTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "endPosition") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "endOrientation") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "duration") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "preambleDuration") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "headerDuration") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "dataDuration") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "transmission") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *ReceptionBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_startTime
        "inet::Coord",    // FIELD_startPosition
        "inet::Quaternion",    // FIELD_startOrientation
        "omnetpp::simtime_t",    // FIELD_endTime
        "inet::Coord",    // FIELD_endPosition
        "inet::Quaternion",    // FIELD_endOrientation
        "omnetpp::simtime_t",    // FIELD_duration
        "omnetpp::simtime_t",    // FIELD_preambleDuration
        "omnetpp::simtime_t",    // FIELD_headerDuration
        "omnetpp::simtime_t",    // FIELD_dataDuration
        "inet::physicallayer::ITransmission",    // FIELD_transmission
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **ReceptionBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *ReceptionBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ReceptionBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ReceptionBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ReceptionBase'", field);
    }
}

const char *ReceptionBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_transmission: { const ITransmission * value = pp->getTransmission(); return omnetpp::opp_typename(typeid(*const_cast<ITransmission *>(value))); }
        default: return nullptr;
    }
}

std::string ReceptionBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return simtime2string(pp->getStartTime());
        case FIELD_startPosition: return "";
        case FIELD_startOrientation: return "";
        case FIELD_endTime: return simtime2string(pp->getEndTime());
        case FIELD_endPosition: return "";
        case FIELD_endOrientation: return "";
        case FIELD_duration: return simtime2string(pp->getDuration());
        case FIELD_preambleDuration: return simtime2string(pp->getPreambleDuration());
        case FIELD_headerDuration: return simtime2string(pp->getHeaderDuration());
        case FIELD_dataDuration: return simtime2string(pp->getDataDuration());
        case FIELD_transmission: return "";
        default: return "";
    }
}

void ReceptionBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionBase'", field);
    }
}

omnetpp::cValue ReceptionBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return pp->getStartTime().dbl();
        case FIELD_startPosition: return omnetpp::toAnyPtr(&pp->getStartPosition()); break;
        case FIELD_startOrientation: return omnetpp::toAnyPtr(&pp->getStartOrientation()); break;
        case FIELD_endTime: return pp->getEndTime().dbl();
        case FIELD_endPosition: return omnetpp::toAnyPtr(&pp->getEndPosition()); break;
        case FIELD_endOrientation: return omnetpp::toAnyPtr(&pp->getEndOrientation()); break;
        case FIELD_duration: return pp->getDuration().dbl();
        case FIELD_preambleDuration: return pp->getPreambleDuration().dbl();
        case FIELD_headerDuration: return pp->getHeaderDuration().dbl();
        case FIELD_dataDuration: return pp->getDataDuration().dbl();
        case FIELD_transmission: return omnetpp::toAnyPtr(pp->getTransmission()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ReceptionBase' as cValue -- field index out of range?", field);
    }
}

void ReceptionBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionBase'", field);
    }
}

const char *ReceptionBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_startPosition: return omnetpp::opp_typename(typeid(::inet::Coord));
        case FIELD_startOrientation: return omnetpp::opp_typename(typeid(::inet::Quaternion));
        case FIELD_endPosition: return omnetpp::opp_typename(typeid(::inet::Coord));
        case FIELD_endOrientation: return omnetpp::opp_typename(typeid(::inet::Quaternion));
        case FIELD_transmission: return omnetpp::opp_typename(typeid(ITransmission));
        default: return nullptr;
    };
}

omnetpp::any_ptr ReceptionBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_startPosition: return omnetpp::toAnyPtr(&pp->getStartPosition()); break;
        case FIELD_startOrientation: return omnetpp::toAnyPtr(&pp->getStartOrientation()); break;
        case FIELD_endPosition: return omnetpp::toAnyPtr(&pp->getEndPosition()); break;
        case FIELD_endOrientation: return omnetpp::toAnyPtr(&pp->getEndOrientation()); break;
        case FIELD_transmission: return omnetpp::toAnyPtr(pp->getTransmission()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ReceptionBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionBase *pp = omnetpp::fromAnyPtr<ReceptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionBase'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

