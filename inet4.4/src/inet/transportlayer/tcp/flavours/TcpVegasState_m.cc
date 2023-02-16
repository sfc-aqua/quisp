//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/flavours/TcpVegasState.msg.
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
#include "TcpVegasState_m.h"

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

TcpVegasStateVariables::TcpVegasStateVariables()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const TcpVegasStateVariables& a)
{
    doParsimPacking(b,(::inet::tcp::TcpBaseAlgStateVariables&)a);
    doParsimPacking(b,a.v_recoverypoint);
    doParsimPacking(b,a.v_cwnd_changed);
    doParsimPacking(b,a.v_baseRTT);
    doParsimPacking(b,a.v_sumRTT);
    doParsimPacking(b,a.v_cntRTT);
    doParsimPacking(b,a.v_begseq);
    doParsimPacking(b,a.v_begtime);
    doParsimPacking(b,a.v_rtt_timeout);
    doParsimPacking(b,a.v_sa);
    doParsimPacking(b,a.v_sd);
    doParsimPacking(b,a.regions);
    doParsimPacking(b,a.ssthresh);
    doParsimPacking(b,a.v_inc_flag);
    doParsimPacking(b,a.v_incr_ss);
    doParsimPacking(b,a.v_incr);
    doParsimPacking(b,a.v_worried);
}

void __doUnpacking(omnetpp::cCommBuffer *b, TcpVegasStateVariables& a)
{
    doParsimUnpacking(b,(::inet::tcp::TcpBaseAlgStateVariables&)a);
    doParsimUnpacking(b,a.v_recoverypoint);
    doParsimUnpacking(b,a.v_cwnd_changed);
    doParsimUnpacking(b,a.v_baseRTT);
    doParsimUnpacking(b,a.v_sumRTT);
    doParsimUnpacking(b,a.v_cntRTT);
    doParsimUnpacking(b,a.v_begseq);
    doParsimUnpacking(b,a.v_begtime);
    doParsimUnpacking(b,a.v_rtt_timeout);
    doParsimUnpacking(b,a.v_sa);
    doParsimUnpacking(b,a.v_sd);
    doParsimUnpacking(b,a.regions);
    doParsimUnpacking(b,a.ssthresh);
    doParsimUnpacking(b,a.v_inc_flag);
    doParsimUnpacking(b,a.v_incr_ss);
    doParsimUnpacking(b,a.v_incr);
    doParsimUnpacking(b,a.v_worried);
}

class TcpVegasStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_v_recoverypoint,
        FIELD_v_cwnd_changed,
        FIELD_v_baseRTT,
        FIELD_v_sumRTT,
        FIELD_v_cntRTT,
        FIELD_v_begseq,
        FIELD_v_begtime,
        FIELD_v_rtt_timeout,
        FIELD_v_sa,
        FIELD_v_sd,
        FIELD_regions,
        FIELD_ssthresh,
        FIELD_v_inc_flag,
        FIELD_v_incr_ss,
        FIELD_v_incr,
        FIELD_v_worried,
    };
  public:
    TcpVegasStateVariablesDescriptor();
    virtual ~TcpVegasStateVariablesDescriptor();

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

Register_ClassDescriptor(TcpVegasStateVariablesDescriptor)

TcpVegasStateVariablesDescriptor::TcpVegasStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpVegasStateVariables)), "inet::tcp::TcpBaseAlgStateVariables")
{
    propertyNames = nullptr;
}

TcpVegasStateVariablesDescriptor::~TcpVegasStateVariablesDescriptor()
{
    delete[] propertyNames;
}

bool TcpVegasStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpVegasStateVariables *>(obj)!=nullptr;
}

const char **TcpVegasStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpVegasStateVariablesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpVegasStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 16+base->getFieldCount() : 16;
}

unsigned int TcpVegasStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_v_recoverypoint
        0,    // FIELD_v_cwnd_changed
        0,    // FIELD_v_baseRTT
        0,    // FIELD_v_sumRTT
        0,    // FIELD_v_cntRTT
        0,    // FIELD_v_begseq
        0,    // FIELD_v_begtime
        0,    // FIELD_v_rtt_timeout
        0,    // FIELD_v_sa
        0,    // FIELD_v_sd
        0,    // FIELD_regions
        0,    // FIELD_ssthresh
        0,    // FIELD_v_inc_flag
        0,    // FIELD_v_incr_ss
        0,    // FIELD_v_incr
        0,    // FIELD_v_worried
    };
    return (field >= 0 && field < 16) ? fieldTypeFlags[field] : 0;
}

const char *TcpVegasStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "v_recoverypoint",
        "v_cwnd_changed",
        "v_baseRTT",
        "v_sumRTT",
        "v_cntRTT",
        "v_begseq",
        "v_begtime",
        "v_rtt_timeout",
        "v_sa",
        "v_sd",
        "regions",
        "ssthresh",
        "v_inc_flag",
        "v_incr_ss",
        "v_incr",
        "v_worried",
    };
    return (field >= 0 && field < 16) ? fieldNames[field] : nullptr;
}

int TcpVegasStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "v_recoverypoint") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "v_cwnd_changed") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "v_baseRTT") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "v_sumRTT") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "v_cntRTT") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "v_begseq") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "v_begtime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "v_rtt_timeout") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "v_sa") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "v_sd") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "regions") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "ssthresh") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "v_inc_flag") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "v_incr_ss") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "v_incr") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "v_worried") == 0) return baseIndex + 15;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpVegasStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_v_recoverypoint
        "omnetpp::simtime_t",    // FIELD_v_cwnd_changed
        "omnetpp::simtime_t",    // FIELD_v_baseRTT
        "omnetpp::simtime_t",    // FIELD_v_sumRTT
        "int",    // FIELD_v_cntRTT
        "uint32_t",    // FIELD_v_begseq
        "omnetpp::simtime_t",    // FIELD_v_begtime
        "omnetpp::simtime_t",    // FIELD_v_rtt_timeout
        "omnetpp::simtime_t",    // FIELD_v_sa
        "omnetpp::simtime_t",    // FIELD_v_sd
        "inet::tcp::TcpSegmentTransmitInfoList",    // FIELD_regions
        "uint32_t",    // FIELD_ssthresh
        "bool",    // FIELD_v_inc_flag
        "bool",    // FIELD_v_incr_ss
        "int32_t",    // FIELD_v_incr
        "uint32_t",    // FIELD_v_worried
    };
    return (field >= 0 && field < 16) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpVegasStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpVegasStateVariablesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpVegasStateVariablesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpVegasStateVariablesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpVegasStateVariables'", field);
    }
}

const char *TcpVegasStateVariablesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpVegasStateVariablesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_v_recoverypoint: return ulong2string(pp->v_recoverypoint);
        case FIELD_v_cwnd_changed: return simtime2string(pp->v_cwnd_changed);
        case FIELD_v_baseRTT: return simtime2string(pp->v_baseRTT);
        case FIELD_v_sumRTT: return simtime2string(pp->v_sumRTT);
        case FIELD_v_cntRTT: return long2string(pp->v_cntRTT);
        case FIELD_v_begseq: return ulong2string(pp->v_begseq);
        case FIELD_v_begtime: return simtime2string(pp->v_begtime);
        case FIELD_v_rtt_timeout: return simtime2string(pp->v_rtt_timeout);
        case FIELD_v_sa: return simtime2string(pp->v_sa);
        case FIELD_v_sd: return simtime2string(pp->v_sd);
        case FIELD_regions: return "";
        case FIELD_ssthresh: return ulong2string(pp->ssthresh);
        case FIELD_v_inc_flag: return bool2string(pp->v_inc_flag);
        case FIELD_v_incr_ss: return bool2string(pp->v_incr_ss);
        case FIELD_v_incr: return long2string(pp->v_incr);
        case FIELD_v_worried: return ulong2string(pp->v_worried);
        default: return "";
    }
}

void TcpVegasStateVariablesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpVegasStateVariables'", field);
    }
}

omnetpp::cValue TcpVegasStateVariablesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_v_recoverypoint: return (omnetpp::intval_t)(pp->v_recoverypoint);
        case FIELD_v_cwnd_changed: return pp->v_cwnd_changed.dbl();
        case FIELD_v_baseRTT: return pp->v_baseRTT.dbl();
        case FIELD_v_sumRTT: return pp->v_sumRTT.dbl();
        case FIELD_v_cntRTT: return pp->v_cntRTT;
        case FIELD_v_begseq: return (omnetpp::intval_t)(pp->v_begseq);
        case FIELD_v_begtime: return pp->v_begtime.dbl();
        case FIELD_v_rtt_timeout: return pp->v_rtt_timeout.dbl();
        case FIELD_v_sa: return pp->v_sa.dbl();
        case FIELD_v_sd: return pp->v_sd.dbl();
        case FIELD_regions: return omnetpp::toAnyPtr(&pp->regions); break;
        case FIELD_ssthresh: return (omnetpp::intval_t)(pp->ssthresh);
        case FIELD_v_inc_flag: return pp->v_inc_flag;
        case FIELD_v_incr_ss: return pp->v_incr_ss;
        case FIELD_v_incr: return pp->v_incr;
        case FIELD_v_worried: return (omnetpp::intval_t)(pp->v_worried);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpVegasStateVariables' as cValue -- field index out of range?", field);
    }
}

void TcpVegasStateVariablesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpVegasStateVariables'", field);
    }
}

const char *TcpVegasStateVariablesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpVegasStateVariablesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_regions: return omnetpp::toAnyPtr(&pp->regions); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpVegasStateVariablesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpVegasStateVariables *pp = omnetpp::fromAnyPtr<TcpVegasStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpVegasStateVariables'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

template<> inet::tcp::TcpVegasStateVariables *fromAnyPtr(any_ptr ptr) {
    if (ptr.contains<inet::tcp::TcpStateVariables>()) return static_cast<inet::tcp::TcpVegasStateVariables*>(ptr.get<inet::tcp::TcpStateVariables>());
    if (ptr.contains<omnetpp::cObject>()) return static_cast<inet::tcp::TcpVegasStateVariables*>(ptr.get<omnetpp::cObject>());
    throw cRuntimeError("Unable to obtain inet::tcp::TcpVegasStateVariables* pointer from any_ptr(%s)", ptr.pointerTypeName());
}
}  // namespace omnetpp

