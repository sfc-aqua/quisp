//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/flavours/TcpBaseAlgState.msg.
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
#include "TcpBaseAlgState_m.h"

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

TcpBaseAlgStateVariables::TcpBaseAlgStateVariables()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const TcpBaseAlgStateVariables& a)
{
    doParsimPacking(b,(::inet::tcp::TcpStateVariables&)a);
    doParsimPacking(b,a.rexmit_count);
    doParsimPacking(b,a.rexmit_timeout);
    doParsimPacking(b,a.persist_factor);
    doParsimPacking(b,a.persist_timeout);
    doParsimPacking(b,a.snd_cwnd);
    doParsimPacking(b,a.rtseq);
    doParsimPacking(b,a.rtseq_sendtime);
    doParsimPacking(b,a.srtt);
    doParsimPacking(b,a.rttvar);
    doParsimPacking(b,a.numRtos);
    doParsimPacking(b,a.recover);
    doParsimPacking(b,a.firstPartialACK);
}

void __doUnpacking(omnetpp::cCommBuffer *b, TcpBaseAlgStateVariables& a)
{
    doParsimUnpacking(b,(::inet::tcp::TcpStateVariables&)a);
    doParsimUnpacking(b,a.rexmit_count);
    doParsimUnpacking(b,a.rexmit_timeout);
    doParsimUnpacking(b,a.persist_factor);
    doParsimUnpacking(b,a.persist_timeout);
    doParsimUnpacking(b,a.snd_cwnd);
    doParsimUnpacking(b,a.rtseq);
    doParsimUnpacking(b,a.rtseq_sendtime);
    doParsimUnpacking(b,a.srtt);
    doParsimUnpacking(b,a.rttvar);
    doParsimUnpacking(b,a.numRtos);
    doParsimUnpacking(b,a.recover);
    doParsimUnpacking(b,a.firstPartialACK);
}

class TcpBaseAlgStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rexmit_count,
        FIELD_rexmit_timeout,
        FIELD_persist_factor,
        FIELD_persist_timeout,
        FIELD_snd_cwnd,
        FIELD_rtseq,
        FIELD_rtseq_sendtime,
        FIELD_srtt,
        FIELD_rttvar,
        FIELD_numRtos,
        FIELD_recover,
        FIELD_firstPartialACK,
    };
  public:
    TcpBaseAlgStateVariablesDescriptor();
    virtual ~TcpBaseAlgStateVariablesDescriptor();

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

Register_ClassDescriptor(TcpBaseAlgStateVariablesDescriptor)

TcpBaseAlgStateVariablesDescriptor::TcpBaseAlgStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpBaseAlgStateVariables)), "inet::tcp::TcpStateVariables")
{
    propertyNames = nullptr;
}

TcpBaseAlgStateVariablesDescriptor::~TcpBaseAlgStateVariablesDescriptor()
{
    delete[] propertyNames;
}

bool TcpBaseAlgStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpBaseAlgStateVariables *>(obj)!=nullptr;
}

const char **TcpBaseAlgStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpBaseAlgStateVariablesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpBaseAlgStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int TcpBaseAlgStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_rexmit_count
        0,    // FIELD_rexmit_timeout
        0,    // FIELD_persist_factor
        0,    // FIELD_persist_timeout
        0,    // FIELD_snd_cwnd
        0,    // FIELD_rtseq
        0,    // FIELD_rtseq_sendtime
        0,    // FIELD_srtt
        0,    // FIELD_rttvar
        0,    // FIELD_numRtos
        0,    // FIELD_recover
        0,    // FIELD_firstPartialACK
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *TcpBaseAlgStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rexmit_count",
        "rexmit_timeout",
        "persist_factor",
        "persist_timeout",
        "snd_cwnd",
        "rtseq",
        "rtseq_sendtime",
        "srtt",
        "rttvar",
        "numRtos",
        "recover",
        "firstPartialACK",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int TcpBaseAlgStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rexmit_count") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "rexmit_timeout") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "persist_factor") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "persist_timeout") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "snd_cwnd") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "rtseq") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "rtseq_sendtime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "srtt") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "rttvar") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "numRtos") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "recover") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "firstPartialACK") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpBaseAlgStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_rexmit_count
        "omnetpp::simtime_t",    // FIELD_rexmit_timeout
        "unsigned int",    // FIELD_persist_factor
        "omnetpp::simtime_t",    // FIELD_persist_timeout
        "uint32_t",    // FIELD_snd_cwnd
        "uint32_t",    // FIELD_rtseq
        "omnetpp::simtime_t",    // FIELD_rtseq_sendtime
        "omnetpp::simtime_t",    // FIELD_srtt
        "omnetpp::simtime_t",    // FIELD_rttvar
        "uint32_t",    // FIELD_numRtos
        "uint32_t",    // FIELD_recover
        "bool",    // FIELD_firstPartialACK
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpBaseAlgStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpBaseAlgStateVariablesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpBaseAlgStateVariablesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpBaseAlgStateVariablesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpBaseAlgStateVariables'", field);
    }
}

const char *TcpBaseAlgStateVariablesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpBaseAlgStateVariablesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_rexmit_count: return long2string(pp->rexmit_count);
        case FIELD_rexmit_timeout: return simtime2string(pp->rexmit_timeout);
        case FIELD_persist_factor: return ulong2string(pp->persist_factor);
        case FIELD_persist_timeout: return simtime2string(pp->persist_timeout);
        case FIELD_snd_cwnd: return ulong2string(pp->snd_cwnd);
        case FIELD_rtseq: return ulong2string(pp->rtseq);
        case FIELD_rtseq_sendtime: return simtime2string(pp->rtseq_sendtime);
        case FIELD_srtt: return simtime2string(pp->srtt);
        case FIELD_rttvar: return simtime2string(pp->rttvar);
        case FIELD_numRtos: return ulong2string(pp->numRtos);
        case FIELD_recover: return ulong2string(pp->recover);
        case FIELD_firstPartialACK: return bool2string(pp->firstPartialACK);
        default: return "";
    }
}

void TcpBaseAlgStateVariablesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpBaseAlgStateVariables'", field);
    }
}

omnetpp::cValue TcpBaseAlgStateVariablesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_rexmit_count: return pp->rexmit_count;
        case FIELD_rexmit_timeout: return pp->rexmit_timeout.dbl();
        case FIELD_persist_factor: return (omnetpp::intval_t)(pp->persist_factor);
        case FIELD_persist_timeout: return pp->persist_timeout.dbl();
        case FIELD_snd_cwnd: return (omnetpp::intval_t)(pp->snd_cwnd);
        case FIELD_rtseq: return (omnetpp::intval_t)(pp->rtseq);
        case FIELD_rtseq_sendtime: return pp->rtseq_sendtime.dbl();
        case FIELD_srtt: return pp->srtt.dbl();
        case FIELD_rttvar: return pp->rttvar.dbl();
        case FIELD_numRtos: return (omnetpp::intval_t)(pp->numRtos);
        case FIELD_recover: return (omnetpp::intval_t)(pp->recover);
        case FIELD_firstPartialACK: return pp->firstPartialACK;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpBaseAlgStateVariables' as cValue -- field index out of range?", field);
    }
}

void TcpBaseAlgStateVariablesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpBaseAlgStateVariables'", field);
    }
}

const char *TcpBaseAlgStateVariablesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpBaseAlgStateVariablesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpBaseAlgStateVariablesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpBaseAlgStateVariables *pp = omnetpp::fromAnyPtr<TcpBaseAlgStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpBaseAlgStateVariables'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

template<> inet::tcp::TcpBaseAlgStateVariables *fromAnyPtr(any_ptr ptr) {
    if (ptr.contains<inet::tcp::TcpStateVariables>()) return static_cast<inet::tcp::TcpBaseAlgStateVariables*>(ptr.get<inet::tcp::TcpStateVariables>());
    if (ptr.contains<omnetpp::cObject>()) return static_cast<inet::tcp::TcpBaseAlgStateVariables*>(ptr.get<omnetpp::cObject>());
    throw cRuntimeError("Unable to obtain inet::tcp::TcpBaseAlgStateVariables* pointer from any_ptr(%s)", ptr.pointerTypeName());
}
}  // namespace omnetpp

