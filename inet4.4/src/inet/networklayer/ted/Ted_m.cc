//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ted/Ted.msg.
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
#include "Ted_m.h"

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

TeLinkStateInfo::TeLinkStateInfo()
{
    for (size_t i = 0; i < 8; i++)
        this->UnResvBandwidth[i] = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const TeLinkStateInfo& a)
{
    doParsimPacking(b,a.advrouter);
    doParsimPacking(b,a.linkid);
    doParsimPacking(b,a.local);
    doParsimPacking(b,a.remote);
    doParsimPacking(b,a.metric);
    doParsimPacking(b,a.MaxBandwidth);
    doParsimArrayPacking(b,a.UnResvBandwidth,8);
    doParsimPacking(b,a.timestamp);
    doParsimPacking(b,a.sourceId);
    doParsimPacking(b,a.messageId);
    doParsimPacking(b,a.state);
}

void __doUnpacking(omnetpp::cCommBuffer *b, TeLinkStateInfo& a)
{
    doParsimUnpacking(b,a.advrouter);
    doParsimUnpacking(b,a.linkid);
    doParsimUnpacking(b,a.local);
    doParsimUnpacking(b,a.remote);
    doParsimUnpacking(b,a.metric);
    doParsimUnpacking(b,a.MaxBandwidth);
    doParsimArrayUnpacking(b,a.UnResvBandwidth,8);
    doParsimUnpacking(b,a.timestamp);
    doParsimUnpacking(b,a.sourceId);
    doParsimUnpacking(b,a.messageId);
    doParsimUnpacking(b,a.state);
}

class TeLinkStateInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_advrouter,
        FIELD_linkid,
        FIELD_local,
        FIELD_remote,
        FIELD_metric,
        FIELD_MaxBandwidth,
        FIELD_UnResvBandwidth,
        FIELD_timestamp,
        FIELD_sourceId,
        FIELD_messageId,
        FIELD_state,
    };
  public:
    TeLinkStateInfoDescriptor();
    virtual ~TeLinkStateInfoDescriptor();

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

Register_ClassDescriptor(TeLinkStateInfoDescriptor)

TeLinkStateInfoDescriptor::TeLinkStateInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TeLinkStateInfo)), "")
{
    propertyNames = nullptr;
}

TeLinkStateInfoDescriptor::~TeLinkStateInfoDescriptor()
{
    delete[] propertyNames;
}

bool TeLinkStateInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TeLinkStateInfo *>(obj)!=nullptr;
}

const char **TeLinkStateInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TeLinkStateInfoDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TeLinkStateInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int TeLinkStateInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_advrouter
        0,    // FIELD_linkid
        0,    // FIELD_local
        0,    // FIELD_remote
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_MaxBandwidth
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_UnResvBandwidth
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_messageId
        FD_ISEDITABLE,    // FIELD_state
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *TeLinkStateInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "advrouter",
        "linkid",
        "local",
        "remote",
        "metric",
        "MaxBandwidth",
        "UnResvBandwidth",
        "timestamp",
        "sourceId",
        "messageId",
        "state",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int TeLinkStateInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "advrouter") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "linkid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "local") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remote") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "MaxBandwidth") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "UnResvBandwidth") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "messageId") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "state") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *TeLinkStateInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_advrouter
        "inet::Ipv4Address",    // FIELD_linkid
        "inet::Ipv4Address",    // FIELD_local
        "inet::Ipv4Address",    // FIELD_remote
        "double",    // FIELD_metric
        "double",    // FIELD_MaxBandwidth
        "double",    // FIELD_UnResvBandwidth
        "omnetpp::simtime_t",    // FIELD_timestamp
        "unsigned int",    // FIELD_sourceId
        "unsigned int",    // FIELD_messageId
        "bool",    // FIELD_state
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **TeLinkStateInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *TeLinkStateInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TeLinkStateInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_UnResvBandwidth: return 8;
        default: return 0;
    }
}

void TeLinkStateInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TeLinkStateInfo'", field);
    }
}

const char *TeLinkStateInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TeLinkStateInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_advrouter: return pp->advrouter.str();
        case FIELD_linkid: return pp->linkid.str();
        case FIELD_local: return pp->local.str();
        case FIELD_remote: return pp->remote.str();
        case FIELD_metric: return double2string(pp->metric);
        case FIELD_MaxBandwidth: return double2string(pp->MaxBandwidth);
        case FIELD_UnResvBandwidth: if (i >= 8) return "";
                return double2string(pp->UnResvBandwidth[i]);
        case FIELD_timestamp: return simtime2string(pp->timestamp);
        case FIELD_sourceId: return ulong2string(pp->sourceId);
        case FIELD_messageId: return ulong2string(pp->messageId);
        case FIELD_state: return bool2string(pp->state);
        default: return "";
    }
}

void TeLinkStateInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_metric: pp->metric = string2double(value); break;
        case FIELD_MaxBandwidth: pp->MaxBandwidth = string2double(value); break;
        case FIELD_UnResvBandwidth: if (i < 0 || i >= 8) throw omnetpp::cRuntimeError("Array index %d out of bounds for field %d of class 'TeLinkStateInfo'", i, field);
                pp->UnResvBandwidth[i] = string2double(value); break;
        case FIELD_timestamp: pp->timestamp = string2simtime(value); break;
        case FIELD_sourceId: pp->sourceId = string2ulong(value); break;
        case FIELD_messageId: pp->messageId = string2ulong(value); break;
        case FIELD_state: pp->state = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TeLinkStateInfo'", field);
    }
}

omnetpp::cValue TeLinkStateInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_advrouter: return omnetpp::toAnyPtr(&pp->advrouter); break;
        case FIELD_linkid: return omnetpp::toAnyPtr(&pp->linkid); break;
        case FIELD_local: return omnetpp::toAnyPtr(&pp->local); break;
        case FIELD_remote: return omnetpp::toAnyPtr(&pp->remote); break;
        case FIELD_metric: return pp->metric;
        case FIELD_MaxBandwidth: return pp->MaxBandwidth;
        case FIELD_UnResvBandwidth: if (i >= 8) return omnetpp::cValue();
                return pp->UnResvBandwidth[i];
        case FIELD_timestamp: return pp->timestamp.dbl();
        case FIELD_sourceId: return (omnetpp::intval_t)(pp->sourceId);
        case FIELD_messageId: return (omnetpp::intval_t)(pp->messageId);
        case FIELD_state: return pp->state;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TeLinkStateInfo' as cValue -- field index out of range?", field);
    }
}

void TeLinkStateInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_metric: pp->metric = value.doubleValue(); break;
        case FIELD_MaxBandwidth: pp->MaxBandwidth = value.doubleValue(); break;
        case FIELD_UnResvBandwidth: if (i < 0 || i >= 8) throw omnetpp::cRuntimeError("Array index %d out of bounds for field %d of class 'TeLinkStateInfo'", i, field);
                pp->UnResvBandwidth[i] = value.doubleValue(); break;
        case FIELD_timestamp: pp->timestamp = value.doubleValue(); break;
        case FIELD_sourceId: pp->sourceId = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_messageId: pp->messageId = omnetpp::checked_int_cast<unsigned int>(value.intValue()); break;
        case FIELD_state: pp->state = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TeLinkStateInfo'", field);
    }
}

const char *TeLinkStateInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TeLinkStateInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        case FIELD_advrouter: return omnetpp::toAnyPtr(&pp->advrouter); break;
        case FIELD_linkid: return omnetpp::toAnyPtr(&pp->linkid); break;
        case FIELD_local: return omnetpp::toAnyPtr(&pp->local); break;
        case FIELD_remote: return omnetpp::toAnyPtr(&pp->remote); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TeLinkStateInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TeLinkStateInfo *pp = omnetpp::fromAnyPtr<TeLinkStateInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TeLinkStateInfo'", field);
    }
}

Register_Class(TedChangeInfo)

TedChangeInfo::TedChangeInfo() : ::omnetpp::cObject()
{
}

TedChangeInfo::TedChangeInfo(const TedChangeInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

TedChangeInfo::~TedChangeInfo()
{
    delete [] this->tedLinkIndices;
}

TedChangeInfo& TedChangeInfo::operator=(const TedChangeInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void TedChangeInfo::copy(const TedChangeInfo& other)
{
    delete [] this->tedLinkIndices;
    this->tedLinkIndices = (other.tedLinkIndices_arraysize==0) ? nullptr : new int[other.tedLinkIndices_arraysize];
    tedLinkIndices_arraysize = other.tedLinkIndices_arraysize;
    for (size_t i = 0; i < tedLinkIndices_arraysize; i++) {
        this->tedLinkIndices[i] = other.tedLinkIndices[i];
    }
}

void TedChangeInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    b->pack(tedLinkIndices_arraysize);
    doParsimArrayPacking(b,this->tedLinkIndices,tedLinkIndices_arraysize);
}

void TedChangeInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    delete [] this->tedLinkIndices;
    b->unpack(tedLinkIndices_arraysize);
    if (tedLinkIndices_arraysize == 0) {
        this->tedLinkIndices = nullptr;
    } else {
        this->tedLinkIndices = new int[tedLinkIndices_arraysize];
        doParsimArrayUnpacking(b,this->tedLinkIndices,tedLinkIndices_arraysize);
    }
}

size_t TedChangeInfo::getTedLinkIndicesArraySize() const
{
    return tedLinkIndices_arraysize;
}

int TedChangeInfo::getTedLinkIndices(size_t k) const
{
    if (k >= tedLinkIndices_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tedLinkIndices_arraysize, (unsigned long)k);
    return this->tedLinkIndices[k];
}

void TedChangeInfo::setTedLinkIndicesArraySize(size_t newSize)
{
    int *tedLinkIndices2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = tedLinkIndices_arraysize < newSize ? tedLinkIndices_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        tedLinkIndices2[i] = this->tedLinkIndices[i];
    for (size_t i = minSize; i < newSize; i++)
        tedLinkIndices2[i] = 0;
    delete [] this->tedLinkIndices;
    this->tedLinkIndices = tedLinkIndices2;
    tedLinkIndices_arraysize = newSize;
}

void TedChangeInfo::setTedLinkIndices(size_t k, int tedLinkIndices)
{
    if (k >= tedLinkIndices_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tedLinkIndices_arraysize, (unsigned long)k);
    this->tedLinkIndices[k] = tedLinkIndices;
}

void TedChangeInfo::insertTedLinkIndices(size_t k, int tedLinkIndices)
{
    if (k > tedLinkIndices_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tedLinkIndices_arraysize, (unsigned long)k);
    size_t newSize = tedLinkIndices_arraysize + 1;
    int *tedLinkIndices2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tedLinkIndices2[i] = this->tedLinkIndices[i];
    tedLinkIndices2[k] = tedLinkIndices;
    for (i = k + 1; i < newSize; i++)
        tedLinkIndices2[i] = this->tedLinkIndices[i-1];
    delete [] this->tedLinkIndices;
    this->tedLinkIndices = tedLinkIndices2;
    tedLinkIndices_arraysize = newSize;
}

void TedChangeInfo::appendTedLinkIndices(int tedLinkIndices)
{
    insertTedLinkIndices(tedLinkIndices_arraysize, tedLinkIndices);
}

void TedChangeInfo::eraseTedLinkIndices(size_t k)
{
    if (k >= tedLinkIndices_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tedLinkIndices_arraysize, (unsigned long)k);
    size_t newSize = tedLinkIndices_arraysize - 1;
    int *tedLinkIndices2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tedLinkIndices2[i] = this->tedLinkIndices[i];
    for (i = k; i < newSize; i++)
        tedLinkIndices2[i] = this->tedLinkIndices[i+1];
    delete [] this->tedLinkIndices;
    this->tedLinkIndices = tedLinkIndices2;
    tedLinkIndices_arraysize = newSize;
}

class TedChangeInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tedLinkIndices,
    };
  public:
    TedChangeInfoDescriptor();
    virtual ~TedChangeInfoDescriptor();

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

Register_ClassDescriptor(TedChangeInfoDescriptor)

TedChangeInfoDescriptor::TedChangeInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TedChangeInfo)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TedChangeInfoDescriptor::~TedChangeInfoDescriptor()
{
    delete[] propertyNames;
}

bool TedChangeInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TedChangeInfo *>(obj)!=nullptr;
}

const char **TedChangeInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TedChangeInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TedChangeInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TedChangeInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_tedLinkIndices
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TedChangeInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tedLinkIndices",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TedChangeInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tedLinkIndices") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TedChangeInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_tedLinkIndices
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TedChangeInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *TedChangeInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TedChangeInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: return pp->getTedLinkIndicesArraySize();
        default: return 0;
    }
}

void TedChangeInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: pp->setTedLinkIndicesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TedChangeInfo'", field);
    }
}

const char *TedChangeInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TedChangeInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: return long2string(pp->getTedLinkIndices(i));
        default: return "";
    }
}

void TedChangeInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: pp->setTedLinkIndices(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TedChangeInfo'", field);
    }
}

omnetpp::cValue TedChangeInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: return pp->getTedLinkIndices(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TedChangeInfo' as cValue -- field index out of range?", field);
    }
}

void TedChangeInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        case FIELD_tedLinkIndices: pp->setTedLinkIndices(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TedChangeInfo'", field);
    }
}

const char *TedChangeInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TedChangeInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TedChangeInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TedChangeInfo *pp = omnetpp::fromAnyPtr<TedChangeInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TedChangeInfo'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

