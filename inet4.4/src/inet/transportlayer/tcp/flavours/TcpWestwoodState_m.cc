//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/flavours/TcpWestwoodState.msg.
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
#include "TcpWestwoodState_m.h"

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
namespace tcp {

TcpWestwoodStateVariables::TcpWestwoodStateVariables()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const TcpWestwoodStateVariables& a)
{
    doParsimPacking(b,(::inet::tcp::TcpBaseAlgStateVariables&)a);
    doParsimPacking(b,a.ssthresh);
    doParsimPacking(b,a.w_RTTmin);
    doParsimPacking(b,a.w_a);
    doParsimPacking(b,a.w_lastAckTime);
    doParsimPacking(b,a.w_bwe);
    doParsimPacking(b,a.w_sample_bwe);
    doParsimPacking(b,a.regions);
}

void __doUnpacking(omnetpp::cCommBuffer *b, TcpWestwoodStateVariables& a)
{
    doParsimUnpacking(b,(::inet::tcp::TcpBaseAlgStateVariables&)a);
    doParsimUnpacking(b,a.ssthresh);
    doParsimUnpacking(b,a.w_RTTmin);
    doParsimUnpacking(b,a.w_a);
    doParsimUnpacking(b,a.w_lastAckTime);
    doParsimUnpacking(b,a.w_bwe);
    doParsimUnpacking(b,a.w_sample_bwe);
    doParsimUnpacking(b,a.regions);
}

class TcpWestwoodStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssthresh,
        FIELD_w_RTTmin,
        FIELD_w_a,
        FIELD_w_lastAckTime,
        FIELD_w_bwe,
        FIELD_w_sample_bwe,
        FIELD_regions,
    };
  public:
    TcpWestwoodStateVariablesDescriptor();
    virtual ~TcpWestwoodStateVariablesDescriptor();

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

Register_ClassDescriptor(TcpWestwoodStateVariablesDescriptor)

TcpWestwoodStateVariablesDescriptor::TcpWestwoodStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpWestwoodStateVariables)), "inet::tcp::TcpBaseAlgStateVariables")
{
    propertyNames = nullptr;
}

TcpWestwoodStateVariablesDescriptor::~TcpWestwoodStateVariablesDescriptor()
{
    delete[] propertyNames;
}

bool TcpWestwoodStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpWestwoodStateVariables *>(obj)!=nullptr;
}

const char **TcpWestwoodStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpWestwoodStateVariablesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpWestwoodStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int TcpWestwoodStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_ssthresh
        0,    // FIELD_w_RTTmin
        0,    // FIELD_w_a
        0,    // FIELD_w_lastAckTime
        0,    // FIELD_w_bwe
        0,    // FIELD_w_sample_bwe
        0,    // FIELD_regions
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *TcpWestwoodStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ssthresh",
        "w_RTTmin",
        "w_a",
        "w_lastAckTime",
        "w_bwe",
        "w_sample_bwe",
        "regions",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int TcpWestwoodStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssthresh") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "w_RTTmin") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "w_a") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "w_lastAckTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "w_bwe") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "w_sample_bwe") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "regions") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpWestwoodStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ssthresh
        "omnetpp::simtime_t",    // FIELD_w_RTTmin
        "double",    // FIELD_w_a
        "omnetpp::simtime_t",    // FIELD_w_lastAckTime
        "double",    // FIELD_w_bwe
        "double",    // FIELD_w_sample_bwe
        "inet::tcp::TcpSegmentTransmitInfoList",    // FIELD_regions
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpWestwoodStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpWestwoodStateVariablesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpWestwoodStateVariablesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpWestwoodStateVariablesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpWestwoodStateVariables'", field);
    }
}

const char *TcpWestwoodStateVariablesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpWestwoodStateVariablesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_ssthresh: return ulong2string(pp->ssthresh);
        case FIELD_w_RTTmin: return simtime2string(pp->w_RTTmin);
        case FIELD_w_a: return double2string(pp->w_a);
        case FIELD_w_lastAckTime: return simtime2string(pp->w_lastAckTime);
        case FIELD_w_bwe: return double2string(pp->w_bwe);
        case FIELD_w_sample_bwe: return double2string(pp->w_sample_bwe);
        case FIELD_regions: return "";
        default: return "";
    }
}

void TcpWestwoodStateVariablesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpWestwoodStateVariables'", field);
    }
}

omnetpp::cValue TcpWestwoodStateVariablesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_ssthresh: return (omnetpp::intval_t)(pp->ssthresh);
        case FIELD_w_RTTmin: return pp->w_RTTmin.dbl();
        case FIELD_w_a: return pp->w_a;
        case FIELD_w_lastAckTime: return pp->w_lastAckTime.dbl();
        case FIELD_w_bwe: return pp->w_bwe;
        case FIELD_w_sample_bwe: return pp->w_sample_bwe;
        case FIELD_regions: return omnetpp::toAnyPtr(&pp->regions); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpWestwoodStateVariables' as cValue -- field index out of range?", field);
    }
}

void TcpWestwoodStateVariablesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpWestwoodStateVariables'", field);
    }
}

const char *TcpWestwoodStateVariablesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpWestwoodStateVariablesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_regions: return omnetpp::toAnyPtr(&pp->regions); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpWestwoodStateVariablesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpWestwoodStateVariables *pp = omnetpp::fromAnyPtr<TcpWestwoodStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpWestwoodStateVariables'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

template<> inet::tcp::TcpWestwoodStateVariables *fromAnyPtr(any_ptr ptr) {
    if (ptr.contains<inet::tcp::TcpStateVariables>()) return static_cast<inet::tcp::TcpWestwoodStateVariables*>(ptr.get<inet::tcp::TcpStateVariables>());
    if (ptr.contains<omnetpp::cObject>()) return static_cast<inet::tcp::TcpWestwoodStateVariables*>(ptr.get<omnetpp::cObject>());
    throw cRuntimeError("Unable to obtain inet::tcp::TcpWestwoodStateVariables* pointer from any_ptr(%s)", ptr.pointerTypeName());
}
}  // namespace omnetpp

