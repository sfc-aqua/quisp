//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee80211/mac/Ieee80211Frame.msg.
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
#include "Ieee80211Frame_m.h"

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

}  // namespace inet

namespace inet {
namespace ieee80211 {

Register_Enum(inet::ieee80211::Ieee80211FrameType, (inet::ieee80211::Ieee80211FrameType::ST_ASSOCIATIONREQUEST, inet::ieee80211::Ieee80211FrameType::ST_ASSOCIATIONRESPONSE, inet::ieee80211::Ieee80211FrameType::ST_REASSOCIATIONREQUEST, inet::ieee80211::Ieee80211FrameType::ST_REASSOCIATIONRESPONSE, inet::ieee80211::Ieee80211FrameType::ST_PROBEREQUEST, inet::ieee80211::Ieee80211FrameType::ST_PROBERESPONSE, inet::ieee80211::Ieee80211FrameType::ST_BEACON, inet::ieee80211::Ieee80211FrameType::ST_ATIM, inet::ieee80211::Ieee80211FrameType::ST_DISASSOCIATION, inet::ieee80211::Ieee80211FrameType::ST_AUTHENTICATION, inet::ieee80211::Ieee80211FrameType::ST_DEAUTHENTICATION, inet::ieee80211::Ieee80211FrameType::ST_ACTION, inet::ieee80211::Ieee80211FrameType::ST_NOACKACTION, inet::ieee80211::Ieee80211FrameType::ST_PSPOLL, inet::ieee80211::Ieee80211FrameType::ST_RTS, inet::ieee80211::Ieee80211FrameType::ST_CTS, inet::ieee80211::Ieee80211FrameType::ST_ACK, inet::ieee80211::Ieee80211FrameType::ST_BLOCKACK_REQ, inet::ieee80211::Ieee80211FrameType::ST_BLOCKACK, inet::ieee80211::Ieee80211FrameType::ST_DATA, inet::ieee80211::Ieee80211FrameType::ST_DATA_WITH_QOS, inet::ieee80211::Ieee80211FrameType::ST_LBMS_REQUEST, inet::ieee80211::Ieee80211FrameType::ST_LBMS_REPORT));

Register_Enum(inet::ieee80211::AckPolicy, (inet::ieee80211::AckPolicy::NORMAL_ACK, inet::ieee80211::AckPolicy::NO_ACK, inet::ieee80211::AckPolicy::NO_EXPLICIT_ACK, inet::ieee80211::AckPolicy::BLOCK_ACK));

Register_Class(Ieee80211MacTrailer)

Ieee80211MacTrailer::Ieee80211MacTrailer() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

Ieee80211MacTrailer::Ieee80211MacTrailer(const Ieee80211MacTrailer& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211MacTrailer::~Ieee80211MacTrailer()
{
}

Ieee80211MacTrailer& Ieee80211MacTrailer::operator=(const Ieee80211MacTrailer& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MacTrailer::copy(const Ieee80211MacTrailer& other)
{
    this->fcs = other.fcs;
    this->fcsMode = other.fcsMode;
}

void Ieee80211MacTrailer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->fcs);
    doParsimPacking(b,this->fcsMode);
}

void Ieee80211MacTrailer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->fcs);
    doParsimUnpacking(b,this->fcsMode);
}

uint32_t Ieee80211MacTrailer::getFcs() const
{
    return this->fcs;
}

void Ieee80211MacTrailer::setFcs(uint32_t fcs)
{
    handleChange();
    this->fcs = fcs;
}

::inet::FcsMode Ieee80211MacTrailer::getFcsMode() const
{
    return this->fcsMode;
}

void Ieee80211MacTrailer::setFcsMode(::inet::FcsMode fcsMode)
{
    handleChange();
    this->fcsMode = fcsMode;
}

class Ieee80211MacTrailerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fcs,
        FIELD_fcsMode,
    };
  public:
    Ieee80211MacTrailerDescriptor();
    virtual ~Ieee80211MacTrailerDescriptor();

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

Register_ClassDescriptor(Ieee80211MacTrailerDescriptor)

Ieee80211MacTrailerDescriptor::Ieee80211MacTrailerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MacTrailer)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211MacTrailerDescriptor::~Ieee80211MacTrailerDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MacTrailerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MacTrailer *>(obj)!=nullptr;
}

const char **Ieee80211MacTrailerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MacTrailerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MacTrailerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211MacTrailerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fcs
        FD_ISEDITABLE,    // FIELD_fcsMode
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211MacTrailerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fcs",
        "fcsMode",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211MacTrailerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fcs") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fcsMode") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MacTrailerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_fcs
        "inet::FcsMode",    // FIELD_fcsMode
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211MacTrailerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fcsMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211MacTrailerDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fcsMode:
            if (!strcmp(propertyName, "enum")) return "inet::FcsMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211MacTrailerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MacTrailerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MacTrailer'", field);
    }
}

const char *Ieee80211MacTrailerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MacTrailerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return ulong2string(pp->getFcs());
        case FIELD_fcsMode: return enum2string(pp->getFcsMode(), "inet::FcsMode");
        default: return "";
    }
}

void Ieee80211MacTrailerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(string2ulong(value)); break;
        case FIELD_fcsMode: pp->setFcsMode((inet::FcsMode)string2enum(value, "inet::FcsMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacTrailer'", field);
    }
}

omnetpp::cValue Ieee80211MacTrailerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return (omnetpp::intval_t)(pp->getFcs());
        case FIELD_fcsMode: return static_cast<int>(pp->getFcsMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MacTrailer' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MacTrailerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_fcsMode: pp->setFcsMode(static_cast<inet::FcsMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacTrailer'", field);
    }
}

const char *Ieee80211MacTrailerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211MacTrailerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MacTrailerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacTrailer *pp = omnetpp::fromAnyPtr<Ieee80211MacTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacTrailer'", field);
    }
}

Register_Class(Ieee80211MacHeader)

Ieee80211MacHeader::Ieee80211MacHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(LENGTH_ACK - B(4));

}

Ieee80211MacHeader::Ieee80211MacHeader(const Ieee80211MacHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211MacHeader::~Ieee80211MacHeader()
{
}

Ieee80211MacHeader& Ieee80211MacHeader::operator=(const Ieee80211MacHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MacHeader::copy(const Ieee80211MacHeader& other)
{
    this->type = other.type;
    this->toDS = other.toDS;
    this->fromDS = other.fromDS;
    this->moreFragments = other.moreFragments;
    this->retry = other.retry;
    this->powerMgmt = other.powerMgmt;
    this->moreData = other.moreData;
    this->protectedFrame = other.protectedFrame;
    this->order = other.order;
    this->durationField = other.durationField;
    this->AID = other.AID;
    this->receiverAddress = other.receiverAddress;
    this->MACArrive = other.MACArrive;
}

void Ieee80211MacHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->toDS);
    doParsimPacking(b,this->fromDS);
    doParsimPacking(b,this->moreFragments);
    doParsimPacking(b,this->retry);
    doParsimPacking(b,this->powerMgmt);
    doParsimPacking(b,this->moreData);
    doParsimPacking(b,this->protectedFrame);
    doParsimPacking(b,this->order);
    doParsimPacking(b,this->durationField);
    doParsimPacking(b,this->AID);
    doParsimPacking(b,this->receiverAddress);
    doParsimPacking(b,this->MACArrive);
}

void Ieee80211MacHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->toDS);
    doParsimUnpacking(b,this->fromDS);
    doParsimUnpacking(b,this->moreFragments);
    doParsimUnpacking(b,this->retry);
    doParsimUnpacking(b,this->powerMgmt);
    doParsimUnpacking(b,this->moreData);
    doParsimUnpacking(b,this->protectedFrame);
    doParsimUnpacking(b,this->order);
    doParsimUnpacking(b,this->durationField);
    doParsimUnpacking(b,this->AID);
    doParsimUnpacking(b,this->receiverAddress);
    doParsimUnpacking(b,this->MACArrive);
}

Ieee80211FrameType Ieee80211MacHeader::getType() const
{
    return this->type;
}

void Ieee80211MacHeader::setType(Ieee80211FrameType type)
{
    handleChange();
    this->type = type;
}

bool Ieee80211MacHeader::getToDS() const
{
    return this->toDS;
}

void Ieee80211MacHeader::setToDS(bool toDS)
{
    handleChange();
    this->toDS = toDS;
}

bool Ieee80211MacHeader::getFromDS() const
{
    return this->fromDS;
}

void Ieee80211MacHeader::setFromDS(bool fromDS)
{
    handleChange();
    this->fromDS = fromDS;
}

bool Ieee80211MacHeader::getMoreFragments() const
{
    return this->moreFragments;
}

void Ieee80211MacHeader::setMoreFragments(bool moreFragments)
{
    handleChange();
    this->moreFragments = moreFragments;
}

bool Ieee80211MacHeader::getRetry() const
{
    return this->retry;
}

void Ieee80211MacHeader::setRetry(bool retry)
{
    handleChange();
    this->retry = retry;
}

bool Ieee80211MacHeader::getPowerMgmt() const
{
    return this->powerMgmt;
}

void Ieee80211MacHeader::setPowerMgmt(bool powerMgmt)
{
    handleChange();
    this->powerMgmt = powerMgmt;
}

bool Ieee80211MacHeader::getMoreData() const
{
    return this->moreData;
}

void Ieee80211MacHeader::setMoreData(bool moreData)
{
    handleChange();
    this->moreData = moreData;
}

bool Ieee80211MacHeader::getProtectedFrame() const
{
    return this->protectedFrame;
}

void Ieee80211MacHeader::setProtectedFrame(bool protectedFrame)
{
    handleChange();
    this->protectedFrame = protectedFrame;
}

bool Ieee80211MacHeader::getOrder() const
{
    return this->order;
}

void Ieee80211MacHeader::setOrder(bool order)
{
    handleChange();
    this->order = order;
}

::omnetpp::simtime_t Ieee80211MacHeader::getDurationField() const
{
    return this->durationField;
}

void Ieee80211MacHeader::setDurationField(::omnetpp::simtime_t durationField)
{
    handleChange();
    this->durationField = durationField;
}

short Ieee80211MacHeader::getAID() const
{
    return this->AID;
}

void Ieee80211MacHeader::setAID(short AID)
{
    handleChange();
    this->AID = AID;
}

const ::inet::MacAddress& Ieee80211MacHeader::getReceiverAddress() const
{
    return this->receiverAddress;
}

void Ieee80211MacHeader::setReceiverAddress(const ::inet::MacAddress& receiverAddress)
{
    handleChange();
    this->receiverAddress = receiverAddress;
}

::omnetpp::simtime_t Ieee80211MacHeader::getMACArrive() const
{
    return this->MACArrive;
}

void Ieee80211MacHeader::setMACArrive(::omnetpp::simtime_t MACArrive)
{
    handleChange();
    this->MACArrive = MACArrive;
}

class Ieee80211MacHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_toDS,
        FIELD_fromDS,
        FIELD_moreFragments,
        FIELD_retry,
        FIELD_powerMgmt,
        FIELD_moreData,
        FIELD_protectedFrame,
        FIELD_order,
        FIELD_durationField,
        FIELD_AID,
        FIELD_receiverAddress,
        FIELD_MACArrive,
    };
  public:
    Ieee80211MacHeaderDescriptor();
    virtual ~Ieee80211MacHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211MacHeaderDescriptor)

Ieee80211MacHeaderDescriptor::Ieee80211MacHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MacHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211MacHeaderDescriptor::~Ieee80211MacHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MacHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MacHeader *>(obj)!=nullptr;
}

const char **Ieee80211MacHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MacHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MacHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 13+base->getFieldCount() : 13;
}

unsigned int Ieee80211MacHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_toDS
        FD_ISEDITABLE,    // FIELD_fromDS
        FD_ISEDITABLE,    // FIELD_moreFragments
        FD_ISEDITABLE,    // FIELD_retry
        FD_ISEDITABLE,    // FIELD_powerMgmt
        FD_ISEDITABLE,    // FIELD_moreData
        FD_ISEDITABLE,    // FIELD_protectedFrame
        FD_ISEDITABLE,    // FIELD_order
        FD_ISEDITABLE,    // FIELD_durationField
        FD_ISEDITABLE,    // FIELD_AID
        0,    // FIELD_receiverAddress
        FD_ISEDITABLE,    // FIELD_MACArrive
    };
    return (field >= 0 && field < 13) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211MacHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "toDS",
        "fromDS",
        "moreFragments",
        "retry",
        "powerMgmt",
        "moreData",
        "protectedFrame",
        "order",
        "durationField",
        "AID",
        "receiverAddress",
        "MACArrive",
    };
    return (field >= 0 && field < 13) ? fieldNames[field] : nullptr;
}

int Ieee80211MacHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "toDS") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fromDS") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "moreFragments") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "retry") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "powerMgmt") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "moreData") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "protectedFrame") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "order") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "durationField") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "AID") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "receiverAddress") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "MACArrive") == 0) return baseIndex + 12;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MacHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211FrameType",    // FIELD_type
        "bool",    // FIELD_toDS
        "bool",    // FIELD_fromDS
        "bool",    // FIELD_moreFragments
        "bool",    // FIELD_retry
        "bool",    // FIELD_powerMgmt
        "bool",    // FIELD_moreData
        "bool",    // FIELD_protectedFrame
        "bool",    // FIELD_order
        "omnetpp::simtime_t",    // FIELD_durationField
        "short",    // FIELD_AID
        "inet::MacAddress",    // FIELD_receiverAddress
        "omnetpp::simtime_t",    // FIELD_MACArrive
    };
    return (field >= 0 && field < 13) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211MacHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MacHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211FrameType";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211MacHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MacHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MacHeader'", field);
    }
}

const char *Ieee80211MacHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MacHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::ieee80211::Ieee80211FrameType");
        case FIELD_toDS: return bool2string(pp->getToDS());
        case FIELD_fromDS: return bool2string(pp->getFromDS());
        case FIELD_moreFragments: return bool2string(pp->getMoreFragments());
        case FIELD_retry: return bool2string(pp->getRetry());
        case FIELD_powerMgmt: return bool2string(pp->getPowerMgmt());
        case FIELD_moreData: return bool2string(pp->getMoreData());
        case FIELD_protectedFrame: return bool2string(pp->getProtectedFrame());
        case FIELD_order: return bool2string(pp->getOrder());
        case FIELD_durationField: return simtime2string(pp->getDurationField());
        case FIELD_AID: return long2string(pp->getAID());
        case FIELD_receiverAddress: return pp->getReceiverAddress().str();
        case FIELD_MACArrive: return simtime2string(pp->getMACArrive());
        default: return "";
    }
}

void Ieee80211MacHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_toDS: pp->setToDS(string2bool(value)); break;
        case FIELD_fromDS: pp->setFromDS(string2bool(value)); break;
        case FIELD_moreFragments: pp->setMoreFragments(string2bool(value)); break;
        case FIELD_retry: pp->setRetry(string2bool(value)); break;
        case FIELD_powerMgmt: pp->setPowerMgmt(string2bool(value)); break;
        case FIELD_moreData: pp->setMoreData(string2bool(value)); break;
        case FIELD_protectedFrame: pp->setProtectedFrame(string2bool(value)); break;
        case FIELD_order: pp->setOrder(string2bool(value)); break;
        case FIELD_durationField: pp->setDurationField(string2simtime(value)); break;
        case FIELD_AID: pp->setAID(string2long(value)); break;
        case FIELD_MACArrive: pp->setMACArrive(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacHeader'", field);
    }
}

omnetpp::cValue Ieee80211MacHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_toDS: return pp->getToDS();
        case FIELD_fromDS: return pp->getFromDS();
        case FIELD_moreFragments: return pp->getMoreFragments();
        case FIELD_retry: return pp->getRetry();
        case FIELD_powerMgmt: return pp->getPowerMgmt();
        case FIELD_moreData: return pp->getMoreData();
        case FIELD_protectedFrame: return pp->getProtectedFrame();
        case FIELD_order: return pp->getOrder();
        case FIELD_durationField: return pp->getDurationField().dbl();
        case FIELD_AID: return pp->getAID();
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        case FIELD_MACArrive: return pp->getMACArrive().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MacHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MacHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_toDS: pp->setToDS(value.boolValue()); break;
        case FIELD_fromDS: pp->setFromDS(value.boolValue()); break;
        case FIELD_moreFragments: pp->setMoreFragments(value.boolValue()); break;
        case FIELD_retry: pp->setRetry(value.boolValue()); break;
        case FIELD_powerMgmt: pp->setPowerMgmt(value.boolValue()); break;
        case FIELD_moreData: pp->setMoreData(value.boolValue()); break;
        case FIELD_protectedFrame: pp->setProtectedFrame(value.boolValue()); break;
        case FIELD_order: pp->setOrder(value.boolValue()); break;
        case FIELD_durationField: pp->setDurationField(value.doubleValue()); break;
        case FIELD_AID: pp->setAID(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_MACArrive: pp->setMACArrive(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacHeader'", field);
    }
}

const char *Ieee80211MacHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211MacHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MacHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MacHeader *pp = omnetpp::fromAnyPtr<Ieee80211MacHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MacHeader'", field);
    }
}

Register_Class(Ieee80211OneAddressHeader)

Ieee80211OneAddressHeader::Ieee80211OneAddressHeader() : ::inet::ieee80211::Ieee80211MacHeader()
{
}

Ieee80211OneAddressHeader::Ieee80211OneAddressHeader(const Ieee80211OneAddressHeader& other) : ::inet::ieee80211::Ieee80211MacHeader(other)
{
    copy(other);
}

Ieee80211OneAddressHeader::~Ieee80211OneAddressHeader()
{
}

Ieee80211OneAddressHeader& Ieee80211OneAddressHeader::operator=(const Ieee80211OneAddressHeader& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MacHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211OneAddressHeader::copy(const Ieee80211OneAddressHeader& other)
{
}

void Ieee80211OneAddressHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MacHeader::parsimPack(b);
}

void Ieee80211OneAddressHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MacHeader::parsimUnpack(b);
}

class Ieee80211OneAddressHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211OneAddressHeaderDescriptor();
    virtual ~Ieee80211OneAddressHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211OneAddressHeaderDescriptor)

Ieee80211OneAddressHeaderDescriptor::Ieee80211OneAddressHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211OneAddressHeader)), "inet::ieee80211::Ieee80211MacHeader")
{
    propertyNames = nullptr;
}

Ieee80211OneAddressHeaderDescriptor::~Ieee80211OneAddressHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211OneAddressHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211OneAddressHeader *>(obj)!=nullptr;
}

const char **Ieee80211OneAddressHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211OneAddressHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211OneAddressHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211OneAddressHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211OneAddressHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211OneAddressHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211OneAddressHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211OneAddressHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211OneAddressHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211OneAddressHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211OneAddressHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211OneAddressHeader'", field);
    }
}

const char *Ieee80211OneAddressHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211OneAddressHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211OneAddressHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OneAddressHeader'", field);
    }
}

omnetpp::cValue Ieee80211OneAddressHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211OneAddressHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211OneAddressHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OneAddressHeader'", field);
    }
}

const char *Ieee80211OneAddressHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211OneAddressHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211OneAddressHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OneAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211OneAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OneAddressHeader'", field);
    }
}

Register_Class(Ieee80211AckFrame)

Ieee80211AckFrame::Ieee80211AckFrame() : ::inet::ieee80211::Ieee80211OneAddressHeader()
{
    this->setChunkLength(LENGTH_ACK - B(4));
    this->setType(ST_ACK);
}

Ieee80211AckFrame::Ieee80211AckFrame(const Ieee80211AckFrame& other) : ::inet::ieee80211::Ieee80211OneAddressHeader(other)
{
    copy(other);
}

Ieee80211AckFrame::~Ieee80211AckFrame()
{
}

Ieee80211AckFrame& Ieee80211AckFrame::operator=(const Ieee80211AckFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211OneAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AckFrame::copy(const Ieee80211AckFrame& other)
{
}

void Ieee80211AckFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimPack(b);
}

void Ieee80211AckFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimUnpack(b);
}

class Ieee80211AckFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211AckFrameDescriptor();
    virtual ~Ieee80211AckFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211AckFrameDescriptor)

Ieee80211AckFrameDescriptor::Ieee80211AckFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AckFrame)), "inet::ieee80211::Ieee80211OneAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211AckFrameDescriptor::~Ieee80211AckFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AckFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AckFrame *>(obj)!=nullptr;
}

const char **Ieee80211AckFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AckFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AckFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211AckFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211AckFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211AckFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AckFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211AckFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211AckFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211AckFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AckFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AckFrame'", field);
    }
}

const char *Ieee80211AckFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AckFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211AckFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AckFrame'", field);
    }
}

omnetpp::cValue Ieee80211AckFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AckFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AckFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AckFrame'", field);
    }
}

const char *Ieee80211AckFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211AckFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AckFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AckFrame *pp = omnetpp::fromAnyPtr<Ieee80211AckFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AckFrame'", field);
    }
}

Register_Class(Ieee80211TwoAddressHeader)

Ieee80211TwoAddressHeader::Ieee80211TwoAddressHeader() : ::inet::ieee80211::Ieee80211OneAddressHeader()
{
    this->setChunkLength(LENGTH_RTS - B(4));

}

Ieee80211TwoAddressHeader::Ieee80211TwoAddressHeader(const Ieee80211TwoAddressHeader& other) : ::inet::ieee80211::Ieee80211OneAddressHeader(other)
{
    copy(other);
}

Ieee80211TwoAddressHeader::~Ieee80211TwoAddressHeader()
{
}

Ieee80211TwoAddressHeader& Ieee80211TwoAddressHeader::operator=(const Ieee80211TwoAddressHeader& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211OneAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211TwoAddressHeader::copy(const Ieee80211TwoAddressHeader& other)
{
    this->transmitterAddress = other.transmitterAddress;
}

void Ieee80211TwoAddressHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimPack(b);
    doParsimPacking(b,this->transmitterAddress);
}

void Ieee80211TwoAddressHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->transmitterAddress);
}

const ::inet::MacAddress& Ieee80211TwoAddressHeader::getTransmitterAddress() const
{
    return this->transmitterAddress;
}

void Ieee80211TwoAddressHeader::setTransmitterAddress(const ::inet::MacAddress& transmitterAddress)
{
    handleChange();
    this->transmitterAddress = transmitterAddress;
}

class Ieee80211TwoAddressHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_transmitterAddress,
    };
  public:
    Ieee80211TwoAddressHeaderDescriptor();
    virtual ~Ieee80211TwoAddressHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211TwoAddressHeaderDescriptor)

Ieee80211TwoAddressHeaderDescriptor::Ieee80211TwoAddressHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211TwoAddressHeader)), "inet::ieee80211::Ieee80211OneAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211TwoAddressHeaderDescriptor::~Ieee80211TwoAddressHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211TwoAddressHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211TwoAddressHeader *>(obj)!=nullptr;
}

const char **Ieee80211TwoAddressHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211TwoAddressHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211TwoAddressHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211TwoAddressHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_transmitterAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211TwoAddressHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "transmitterAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211TwoAddressHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "transmitterAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211TwoAddressHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_transmitterAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211TwoAddressHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211TwoAddressHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211TwoAddressHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211TwoAddressHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211TwoAddressHeader'", field);
    }
}

const char *Ieee80211TwoAddressHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211TwoAddressHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        case FIELD_transmitterAddress: return pp->getTransmitterAddress().str();
        default: return "";
    }
}

void Ieee80211TwoAddressHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211TwoAddressHeader'", field);
    }
}

omnetpp::cValue Ieee80211TwoAddressHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        case FIELD_transmitterAddress: return omnetpp::toAnyPtr(&pp->getTransmitterAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211TwoAddressHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211TwoAddressHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211TwoAddressHeader'", field);
    }
}

const char *Ieee80211TwoAddressHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211TwoAddressHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        case FIELD_transmitterAddress: return omnetpp::toAnyPtr(&pp->getTransmitterAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211TwoAddressHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211TwoAddressHeader *pp = omnetpp::fromAnyPtr<Ieee80211TwoAddressHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211TwoAddressHeader'", field);
    }
}

Register_Class(Ieee80211RtsFrame)

Ieee80211RtsFrame::Ieee80211RtsFrame() : ::inet::ieee80211::Ieee80211TwoAddressHeader()
{
    this->setChunkLength(LENGTH_RTS - B(4));
    this->setType(ST_RTS);
}

Ieee80211RtsFrame::Ieee80211RtsFrame(const Ieee80211RtsFrame& other) : ::inet::ieee80211::Ieee80211TwoAddressHeader(other)
{
    copy(other);
}

Ieee80211RtsFrame::~Ieee80211RtsFrame()
{
}

Ieee80211RtsFrame& Ieee80211RtsFrame::operator=(const Ieee80211RtsFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211TwoAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211RtsFrame::copy(const Ieee80211RtsFrame& other)
{
}

void Ieee80211RtsFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimPack(b);
}

void Ieee80211RtsFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimUnpack(b);
}

class Ieee80211RtsFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211RtsFrameDescriptor();
    virtual ~Ieee80211RtsFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211RtsFrameDescriptor)

Ieee80211RtsFrameDescriptor::Ieee80211RtsFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211RtsFrame)), "inet::ieee80211::Ieee80211TwoAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211RtsFrameDescriptor::~Ieee80211RtsFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211RtsFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211RtsFrame *>(obj)!=nullptr;
}

const char **Ieee80211RtsFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211RtsFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211RtsFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211RtsFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211RtsFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211RtsFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211RtsFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211RtsFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211RtsFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211RtsFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211RtsFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211RtsFrame'", field);
    }
}

const char *Ieee80211RtsFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211RtsFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211RtsFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211RtsFrame'", field);
    }
}

omnetpp::cValue Ieee80211RtsFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211RtsFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211RtsFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211RtsFrame'", field);
    }
}

const char *Ieee80211RtsFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211RtsFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211RtsFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211RtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211RtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211RtsFrame'", field);
    }
}

Register_Class(Ieee80211CtsFrame)

Ieee80211CtsFrame::Ieee80211CtsFrame() : ::inet::ieee80211::Ieee80211OneAddressHeader()
{
    this->setChunkLength(LENGTH_CTS - B(4));
    this->setType(ST_CTS);
}

Ieee80211CtsFrame::Ieee80211CtsFrame(const Ieee80211CtsFrame& other) : ::inet::ieee80211::Ieee80211OneAddressHeader(other)
{
    copy(other);
}

Ieee80211CtsFrame::~Ieee80211CtsFrame()
{
}

Ieee80211CtsFrame& Ieee80211CtsFrame::operator=(const Ieee80211CtsFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211OneAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211CtsFrame::copy(const Ieee80211CtsFrame& other)
{
}

void Ieee80211CtsFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimPack(b);
}

void Ieee80211CtsFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211OneAddressHeader::parsimUnpack(b);
}

class Ieee80211CtsFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211CtsFrameDescriptor();
    virtual ~Ieee80211CtsFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211CtsFrameDescriptor)

Ieee80211CtsFrameDescriptor::Ieee80211CtsFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211CtsFrame)), "inet::ieee80211::Ieee80211OneAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211CtsFrameDescriptor::~Ieee80211CtsFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211CtsFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211CtsFrame *>(obj)!=nullptr;
}

const char **Ieee80211CtsFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211CtsFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211CtsFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211CtsFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211CtsFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211CtsFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211CtsFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211CtsFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211CtsFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211CtsFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211CtsFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211CtsFrame'", field);
    }
}

const char *Ieee80211CtsFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211CtsFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211CtsFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CtsFrame'", field);
    }
}

omnetpp::cValue Ieee80211CtsFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211CtsFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211CtsFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CtsFrame'", field);
    }
}

const char *Ieee80211CtsFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211CtsFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211CtsFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CtsFrame *pp = omnetpp::fromAnyPtr<Ieee80211CtsFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CtsFrame'", field);
    }
}

Register_Class(Ieee80211DataOrMgmtHeader)

Ieee80211DataOrMgmtHeader::Ieee80211DataOrMgmtHeader() : ::inet::ieee80211::Ieee80211TwoAddressHeader()
{
    this->setChunkLength(LENGTH_MGMT - B(4));

}

Ieee80211DataOrMgmtHeader::Ieee80211DataOrMgmtHeader(const Ieee80211DataOrMgmtHeader& other) : ::inet::ieee80211::Ieee80211TwoAddressHeader(other)
{
    copy(other);
}

Ieee80211DataOrMgmtHeader::~Ieee80211DataOrMgmtHeader()
{
}

Ieee80211DataOrMgmtHeader& Ieee80211DataOrMgmtHeader::operator=(const Ieee80211DataOrMgmtHeader& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211TwoAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DataOrMgmtHeader::copy(const Ieee80211DataOrMgmtHeader& other)
{
    this->address3 = other.address3;
    this->fragmentNumber = other.fragmentNumber;
    this->sequenceNumber = other.sequenceNumber;
}

void Ieee80211DataOrMgmtHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimPack(b);
    doParsimPacking(b,this->address3);
    doParsimPacking(b,this->fragmentNumber);
    doParsimPacking(b,this->sequenceNumber);
}

void Ieee80211DataOrMgmtHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->address3);
    doParsimUnpacking(b,this->fragmentNumber);
    doParsimUnpacking(b,this->sequenceNumber);
}

const ::inet::MacAddress& Ieee80211DataOrMgmtHeader::getAddress3() const
{
    return this->address3;
}

void Ieee80211DataOrMgmtHeader::setAddress3(const ::inet::MacAddress& address3)
{
    handleChange();
    this->address3 = address3;
}

short Ieee80211DataOrMgmtHeader::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void Ieee80211DataOrMgmtHeader::setFragmentNumber(short fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211DataOrMgmtHeader::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void Ieee80211DataOrMgmtHeader::setSequenceNumber(const SequenceNumberCyclic& sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class Ieee80211DataOrMgmtHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address3,
        FIELD_fragmentNumber,
        FIELD_sequenceNumber,
    };
  public:
    Ieee80211DataOrMgmtHeaderDescriptor();
    virtual ~Ieee80211DataOrMgmtHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211DataOrMgmtHeaderDescriptor)

Ieee80211DataOrMgmtHeaderDescriptor::Ieee80211DataOrMgmtHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211DataOrMgmtHeader)), "inet::ieee80211::Ieee80211TwoAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211DataOrMgmtHeaderDescriptor::~Ieee80211DataOrMgmtHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DataOrMgmtHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DataOrMgmtHeader *>(obj)!=nullptr;
}

const char **Ieee80211DataOrMgmtHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DataOrMgmtHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DataOrMgmtHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211DataOrMgmtHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address3
        FD_ISEDITABLE,    // FIELD_fragmentNumber
        0,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DataOrMgmtHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address3",
        "fragmentNumber",
        "sequenceNumber",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211DataOrMgmtHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address3") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DataOrMgmtHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address3
        "short",    // FIELD_fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DataOrMgmtHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211DataOrMgmtHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211DataOrMgmtHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DataOrMgmtHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DataOrMgmtHeader'", field);
    }
}

const char *Ieee80211DataOrMgmtHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DataOrMgmtHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address3: return pp->getAddress3().str();
        case FIELD_fragmentNumber: return long2string(pp->getFragmentNumber());
        case FIELD_sequenceNumber: return "";
        default: return "";
    }
}

void Ieee80211DataOrMgmtHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataOrMgmtHeader'", field);
    }
}

omnetpp::cValue Ieee80211DataOrMgmtHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address3: return omnetpp::toAnyPtr(&pp->getAddress3()); break;
        case FIELD_fragmentNumber: return pp->getFragmentNumber();
        case FIELD_sequenceNumber: return omnetpp::toAnyPtr(&pp->getSequenceNumber()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DataOrMgmtHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DataOrMgmtHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataOrMgmtHeader'", field);
    }
}

const char *Ieee80211DataOrMgmtHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DataOrMgmtHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address3: return omnetpp::toAnyPtr(&pp->getAddress3()); break;
        case FIELD_sequenceNumber: return omnetpp::toAnyPtr(&pp->getSequenceNumber()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DataOrMgmtHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataOrMgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataOrMgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataOrMgmtHeader'", field);
    }
}

Register_Class(Ieee80211DataHeader)

Ieee80211DataHeader::Ieee80211DataHeader() : ::inet::ieee80211::Ieee80211DataOrMgmtHeader()
{
    this->setChunkLength(DATAFRAME_HEADER_MINLENGTH);
    this->setType(ST_DATA);

}

Ieee80211DataHeader::Ieee80211DataHeader(const Ieee80211DataHeader& other) : ::inet::ieee80211::Ieee80211DataOrMgmtHeader(other)
{
    copy(other);
}

Ieee80211DataHeader::~Ieee80211DataHeader()
{
}

Ieee80211DataHeader& Ieee80211DataHeader::operator=(const Ieee80211DataHeader& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DataHeader::copy(const Ieee80211DataHeader& other)
{
    this->address4 = other.address4;
    this->ackPolicy = other.ackPolicy;
    this->tid = other.tid;
    this->aMsduPresent = other.aMsduPresent;
}

void Ieee80211DataHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::parsimPack(b);
    doParsimPacking(b,this->address4);
    doParsimPacking(b,this->ackPolicy);
    doParsimPacking(b,this->tid);
    doParsimPacking(b,this->aMsduPresent);
}

void Ieee80211DataHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->address4);
    doParsimUnpacking(b,this->ackPolicy);
    doParsimUnpacking(b,this->tid);
    doParsimUnpacking(b,this->aMsduPresent);
}

const ::inet::MacAddress& Ieee80211DataHeader::getAddress4() const
{
    return this->address4;
}

void Ieee80211DataHeader::setAddress4(const ::inet::MacAddress& address4)
{
    handleChange();
    this->address4 = address4;
}

AckPolicy Ieee80211DataHeader::getAckPolicy() const
{
    return this->ackPolicy;
}

void Ieee80211DataHeader::setAckPolicy(AckPolicy ackPolicy)
{
    handleChange();
    this->ackPolicy = ackPolicy;
}

uint8_t Ieee80211DataHeader::getTid() const
{
    return this->tid;
}

void Ieee80211DataHeader::setTid(uint8_t tid)
{
    handleChange();
    this->tid = tid;
}

bool Ieee80211DataHeader::getAMsduPresent() const
{
    return this->aMsduPresent;
}

void Ieee80211DataHeader::setAMsduPresent(bool aMsduPresent)
{
    handleChange();
    this->aMsduPresent = aMsduPresent;
}

class Ieee80211DataHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address4,
        FIELD_ackPolicy,
        FIELD_tid,
        FIELD_aMsduPresent,
    };
  public:
    Ieee80211DataHeaderDescriptor();
    virtual ~Ieee80211DataHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211DataHeaderDescriptor)

Ieee80211DataHeaderDescriptor::Ieee80211DataHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211DataHeader)), "inet::ieee80211::Ieee80211DataOrMgmtHeader")
{
    propertyNames = nullptr;
}

Ieee80211DataHeaderDescriptor::~Ieee80211DataHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DataHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DataHeader *>(obj)!=nullptr;
}

const char **Ieee80211DataHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DataHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DataHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211DataHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address4
        0,    // FIELD_ackPolicy
        FD_ISEDITABLE,    // FIELD_tid
        FD_ISEDITABLE,    // FIELD_aMsduPresent
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DataHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address4",
        "ackPolicy",
        "tid",
        "aMsduPresent",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211DataHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address4") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ackPolicy") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "aMsduPresent") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DataHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address4
        "inet::ieee80211::AckPolicy",    // FIELD_ackPolicy
        "uint8_t",    // FIELD_tid
        "bool",    // FIELD_aMsduPresent
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DataHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ackPolicy: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211DataHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ackPolicy:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::AckPolicy";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211DataHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DataHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DataHeader'", field);
    }
}

const char *Ieee80211DataHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DataHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address4: return pp->getAddress4().str();
        case FIELD_ackPolicy: return enum2string(pp->getAckPolicy(), "inet::ieee80211::AckPolicy");
        case FIELD_tid: return ulong2string(pp->getTid());
        case FIELD_aMsduPresent: return bool2string(pp->getAMsduPresent());
        default: return "";
    }
}

void Ieee80211DataHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tid: pp->setTid(string2ulong(value)); break;
        case FIELD_aMsduPresent: pp->setAMsduPresent(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataHeader'", field);
    }
}

omnetpp::cValue Ieee80211DataHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address4: return omnetpp::toAnyPtr(&pp->getAddress4()); break;
        case FIELD_ackPolicy: return static_cast<int>(pp->getAckPolicy());
        case FIELD_tid: return (omnetpp::intval_t)(pp->getTid());
        case FIELD_aMsduPresent: return pp->getAMsduPresent();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DataHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DataHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tid: pp->setTid(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_aMsduPresent: pp->setAMsduPresent(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataHeader'", field);
    }
}

const char *Ieee80211DataHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DataHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address4: return omnetpp::toAnyPtr(&pp->getAddress4()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DataHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DataHeader *pp = omnetpp::fromAnyPtr<Ieee80211DataHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DataHeader'", field);
    }
}

Register_Class(Ieee80211MgmtHeader)

Ieee80211MgmtHeader::Ieee80211MgmtHeader() : ::inet::ieee80211::Ieee80211DataOrMgmtHeader()
{
}

Ieee80211MgmtHeader::Ieee80211MgmtHeader(const Ieee80211MgmtHeader& other) : ::inet::ieee80211::Ieee80211DataOrMgmtHeader(other)
{
    copy(other);
}

Ieee80211MgmtHeader::~Ieee80211MgmtHeader()
{
}

Ieee80211MgmtHeader& Ieee80211MgmtHeader::operator=(const Ieee80211MgmtHeader& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MgmtHeader::copy(const Ieee80211MgmtHeader& other)
{
}

void Ieee80211MgmtHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::parsimPack(b);
}

void Ieee80211MgmtHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211DataOrMgmtHeader::parsimUnpack(b);
}

class Ieee80211MgmtHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211MgmtHeaderDescriptor();
    virtual ~Ieee80211MgmtHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211MgmtHeaderDescriptor)

Ieee80211MgmtHeaderDescriptor::Ieee80211MgmtHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MgmtHeader)), "inet::ieee80211::Ieee80211DataOrMgmtHeader")
{
    propertyNames = nullptr;
}

Ieee80211MgmtHeaderDescriptor::~Ieee80211MgmtHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MgmtHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MgmtHeader *>(obj)!=nullptr;
}

const char **Ieee80211MgmtHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MgmtHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MgmtHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211MgmtHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211MgmtHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211MgmtHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MgmtHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211MgmtHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MgmtHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MgmtHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MgmtHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MgmtHeader'", field);
    }
}

const char *Ieee80211MgmtHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MgmtHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211MgmtHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtHeader'", field);
    }
}

omnetpp::cValue Ieee80211MgmtHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MgmtHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MgmtHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtHeader'", field);
    }
}

const char *Ieee80211MgmtHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211MgmtHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MgmtHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MgmtHeader *pp = omnetpp::fromAnyPtr<Ieee80211MgmtHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MgmtHeader'", field);
    }
}

Register_Class(Ieee80211ActionFrame)

Ieee80211ActionFrame::Ieee80211ActionFrame() : ::inet::ieee80211::Ieee80211MgmtHeader()
{
    this->setType(ST_ACTION);

}

Ieee80211ActionFrame::Ieee80211ActionFrame(const Ieee80211ActionFrame& other) : ::inet::ieee80211::Ieee80211MgmtHeader(other)
{
    copy(other);
}

Ieee80211ActionFrame::~Ieee80211ActionFrame()
{
}

Ieee80211ActionFrame& Ieee80211ActionFrame::operator=(const Ieee80211ActionFrame& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211MgmtHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ActionFrame::copy(const Ieee80211ActionFrame& other)
{
    this->category = other.category;
    this->blockAckAction = other.blockAckAction;
}

void Ieee80211ActionFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211MgmtHeader::parsimPack(b);
    doParsimPacking(b,this->category);
    doParsimPacking(b,this->blockAckAction);
}

void Ieee80211ActionFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211MgmtHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->category);
    doParsimUnpacking(b,this->blockAckAction);
}

short Ieee80211ActionFrame::getCategory() const
{
    return this->category;
}

void Ieee80211ActionFrame::setCategory(short category)
{
    handleChange();
    this->category = category;
}

uint8_t Ieee80211ActionFrame::getBlockAckAction() const
{
    return this->blockAckAction;
}

void Ieee80211ActionFrame::setBlockAckAction(uint8_t blockAckAction)
{
    handleChange();
    this->blockAckAction = blockAckAction;
}

class Ieee80211ActionFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_category,
        FIELD_blockAckAction,
    };
  public:
    Ieee80211ActionFrameDescriptor();
    virtual ~Ieee80211ActionFrameDescriptor();

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

Register_ClassDescriptor(Ieee80211ActionFrameDescriptor)

Ieee80211ActionFrameDescriptor::Ieee80211ActionFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211ActionFrame)), "inet::ieee80211::Ieee80211MgmtHeader")
{
    propertyNames = nullptr;
}

Ieee80211ActionFrameDescriptor::~Ieee80211ActionFrameDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ActionFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ActionFrame *>(obj)!=nullptr;
}

const char **Ieee80211ActionFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ActionFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ActionFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211ActionFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_category
        FD_ISEDITABLE,    // FIELD_blockAckAction
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211ActionFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "category",
        "blockAckAction",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211ActionFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "category") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "blockAckAction") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ActionFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_category
        "uint8_t",    // FIELD_blockAckAction
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211ActionFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ActionFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ActionFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ActionFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ActionFrame'", field);
    }
}

const char *Ieee80211ActionFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ActionFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        case FIELD_category: return long2string(pp->getCategory());
        case FIELD_blockAckAction: return ulong2string(pp->getBlockAckAction());
        default: return "";
    }
}

void Ieee80211ActionFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        case FIELD_category: pp->setCategory(string2long(value)); break;
        case FIELD_blockAckAction: pp->setBlockAckAction(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ActionFrame'", field);
    }
}

omnetpp::cValue Ieee80211ActionFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        case FIELD_category: return pp->getCategory();
        case FIELD_blockAckAction: return (omnetpp::intval_t)(pp->getBlockAckAction());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ActionFrame' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ActionFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        case FIELD_category: pp->setCategory(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_blockAckAction: pp->setBlockAckAction(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ActionFrame'", field);
    }
}

const char *Ieee80211ActionFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211ActionFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ActionFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ActionFrame *pp = omnetpp::fromAnyPtr<Ieee80211ActionFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ActionFrame'", field);
    }
}

Register_Class(Ieee80211MsduSubframeHeader)

Ieee80211MsduSubframeHeader::Ieee80211MsduSubframeHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(LENGTH_A_MSDU_SUBFRAME_HEADER);

}

Ieee80211MsduSubframeHeader::Ieee80211MsduSubframeHeader(const Ieee80211MsduSubframeHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211MsduSubframeHeader::~Ieee80211MsduSubframeHeader()
{
}

Ieee80211MsduSubframeHeader& Ieee80211MsduSubframeHeader::operator=(const Ieee80211MsduSubframeHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MsduSubframeHeader::copy(const Ieee80211MsduSubframeHeader& other)
{
    this->sa = other.sa;
    this->da = other.da;
    this->length = other.length;
}

void Ieee80211MsduSubframeHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sa);
    doParsimPacking(b,this->da);
    doParsimPacking(b,this->length);
}

void Ieee80211MsduSubframeHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sa);
    doParsimUnpacking(b,this->da);
    doParsimUnpacking(b,this->length);
}

const ::inet::MacAddress& Ieee80211MsduSubframeHeader::getSa() const
{
    return this->sa;
}

void Ieee80211MsduSubframeHeader::setSa(const ::inet::MacAddress& sa)
{
    handleChange();
    this->sa = sa;
}

const ::inet::MacAddress& Ieee80211MsduSubframeHeader::getDa() const
{
    return this->da;
}

void Ieee80211MsduSubframeHeader::setDa(const ::inet::MacAddress& da)
{
    handleChange();
    this->da = da;
}

int Ieee80211MsduSubframeHeader::getLength() const
{
    return this->length;
}

void Ieee80211MsduSubframeHeader::setLength(int length)
{
    handleChange();
    this->length = length;
}

class Ieee80211MsduSubframeHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sa,
        FIELD_da,
        FIELD_length,
    };
  public:
    Ieee80211MsduSubframeHeaderDescriptor();
    virtual ~Ieee80211MsduSubframeHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211MsduSubframeHeaderDescriptor)

Ieee80211MsduSubframeHeaderDescriptor::Ieee80211MsduSubframeHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MsduSubframeHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211MsduSubframeHeaderDescriptor::~Ieee80211MsduSubframeHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MsduSubframeHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MsduSubframeHeader *>(obj)!=nullptr;
}

const char **Ieee80211MsduSubframeHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MsduSubframeHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MsduSubframeHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211MsduSubframeHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_sa
        0,    // FIELD_da
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211MsduSubframeHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sa",
        "da",
        "length",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211MsduSubframeHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sa") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "da") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MsduSubframeHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_sa
        "inet::MacAddress",    // FIELD_da
        "int",    // FIELD_length
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211MsduSubframeHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MsduSubframeHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MsduSubframeHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MsduSubframeHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MsduSubframeHeader'", field);
    }
}

const char *Ieee80211MsduSubframeHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MsduSubframeHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sa: return pp->getSa().str();
        case FIELD_da: return pp->getDa().str();
        case FIELD_length: return long2string(pp->getLength());
        default: return "";
    }
}

void Ieee80211MsduSubframeHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MsduSubframeHeader'", field);
    }
}

omnetpp::cValue Ieee80211MsduSubframeHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sa: return omnetpp::toAnyPtr(&pp->getSa()); break;
        case FIELD_da: return omnetpp::toAnyPtr(&pp->getDa()); break;
        case FIELD_length: return pp->getLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MsduSubframeHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MsduSubframeHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MsduSubframeHeader'", field);
    }
}

const char *Ieee80211MsduSubframeHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211MsduSubframeHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sa: return omnetpp::toAnyPtr(&pp->getSa()); break;
        case FIELD_da: return omnetpp::toAnyPtr(&pp->getDa()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MsduSubframeHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MsduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MsduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MsduSubframeHeader'", field);
    }
}

Register_Class(Ieee80211MpduSubframeHeader)

Ieee80211MpduSubframeHeader::Ieee80211MpduSubframeHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(LENGTH_A_MPDU_SUBFRAME_HEADER);

}

Ieee80211MpduSubframeHeader::Ieee80211MpduSubframeHeader(const Ieee80211MpduSubframeHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211MpduSubframeHeader::~Ieee80211MpduSubframeHeader()
{
}

Ieee80211MpduSubframeHeader& Ieee80211MpduSubframeHeader::operator=(const Ieee80211MpduSubframeHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MpduSubframeHeader::copy(const Ieee80211MpduSubframeHeader& other)
{
    this->length = other.length;
}

void Ieee80211MpduSubframeHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->length);
}

void Ieee80211MpduSubframeHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->length);
}

int Ieee80211MpduSubframeHeader::getLength() const
{
    return this->length;
}

void Ieee80211MpduSubframeHeader::setLength(int length)
{
    handleChange();
    this->length = length;
}

class Ieee80211MpduSubframeHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_length,
    };
  public:
    Ieee80211MpduSubframeHeaderDescriptor();
    virtual ~Ieee80211MpduSubframeHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211MpduSubframeHeaderDescriptor)

Ieee80211MpduSubframeHeaderDescriptor::Ieee80211MpduSubframeHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MpduSubframeHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211MpduSubframeHeaderDescriptor::~Ieee80211MpduSubframeHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MpduSubframeHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MpduSubframeHeader *>(obj)!=nullptr;
}

const char **Ieee80211MpduSubframeHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MpduSubframeHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MpduSubframeHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211MpduSubframeHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211MpduSubframeHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "length",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211MpduSubframeHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MpduSubframeHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_length
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211MpduSubframeHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MpduSubframeHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MpduSubframeHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MpduSubframeHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MpduSubframeHeader'", field);
    }
}

const char *Ieee80211MpduSubframeHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MpduSubframeHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: return long2string(pp->getLength());
        default: return "";
    }
}

void Ieee80211MpduSubframeHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MpduSubframeHeader'", field);
    }
}

omnetpp::cValue Ieee80211MpduSubframeHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: return pp->getLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MpduSubframeHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MpduSubframeHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MpduSubframeHeader'", field);
    }
}

const char *Ieee80211MpduSubframeHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211MpduSubframeHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MpduSubframeHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MpduSubframeHeader *pp = omnetpp::fromAnyPtr<Ieee80211MpduSubframeHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MpduSubframeHeader'", field);
    }
}

Register_Class(Ieee80211AddbaRequest)

Ieee80211AddbaRequest::Ieee80211AddbaRequest() : ::inet::ieee80211::Ieee80211ActionFrame()
{
    this->setChunkLength(LENGTH_ADDBAREQ - B(4));
    this->setCategory(3);
    this->setBlockAckAction(0);

}

Ieee80211AddbaRequest::Ieee80211AddbaRequest(const Ieee80211AddbaRequest& other) : ::inet::ieee80211::Ieee80211ActionFrame(other)
{
    copy(other);
}

Ieee80211AddbaRequest::~Ieee80211AddbaRequest()
{
}

Ieee80211AddbaRequest& Ieee80211AddbaRequest::operator=(const Ieee80211AddbaRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211ActionFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AddbaRequest::copy(const Ieee80211AddbaRequest& other)
{
    this->dialogToken = other.dialogToken;
    this->aMsduSupported = other.aMsduSupported;
    this->blockAckPolicy = other.blockAckPolicy;
    this->tid = other.tid;
    this->bufferSize = other.bufferSize;
    this->blockAckTimeoutValue = other.blockAckTimeoutValue;
    this->_fragmentNumber = other._fragmentNumber;
    this->startingSequenceNumber = other.startingSequenceNumber;
}

void Ieee80211AddbaRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimPack(b);
    doParsimPacking(b,this->dialogToken);
    doParsimPacking(b,this->aMsduSupported);
    doParsimPacking(b,this->blockAckPolicy);
    doParsimPacking(b,this->tid);
    doParsimPacking(b,this->bufferSize);
    doParsimPacking(b,this->blockAckTimeoutValue);
    doParsimPacking(b,this->_fragmentNumber);
    doParsimPacking(b,this->startingSequenceNumber);
}

void Ieee80211AddbaRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->dialogToken);
    doParsimUnpacking(b,this->aMsduSupported);
    doParsimUnpacking(b,this->blockAckPolicy);
    doParsimUnpacking(b,this->tid);
    doParsimUnpacking(b,this->bufferSize);
    doParsimUnpacking(b,this->blockAckTimeoutValue);
    doParsimUnpacking(b,this->_fragmentNumber);
    doParsimUnpacking(b,this->startingSequenceNumber);
}

uint8_t Ieee80211AddbaRequest::getDialogToken() const
{
    return this->dialogToken;
}

void Ieee80211AddbaRequest::setDialogToken(uint8_t dialogToken)
{
    handleChange();
    this->dialogToken = dialogToken;
}

bool Ieee80211AddbaRequest::getAMsduSupported() const
{
    return this->aMsduSupported;
}

void Ieee80211AddbaRequest::setAMsduSupported(bool aMsduSupported)
{
    handleChange();
    this->aMsduSupported = aMsduSupported;
}

bool Ieee80211AddbaRequest::getBlockAckPolicy() const
{
    return this->blockAckPolicy;
}

void Ieee80211AddbaRequest::setBlockAckPolicy(bool blockAckPolicy)
{
    handleChange();
    this->blockAckPolicy = blockAckPolicy;
}

uint8_t Ieee80211AddbaRequest::getTid() const
{
    return this->tid;
}

void Ieee80211AddbaRequest::setTid(uint8_t tid)
{
    handleChange();
    this->tid = tid;
}

uint16_t Ieee80211AddbaRequest::getBufferSize() const
{
    return this->bufferSize;
}

void Ieee80211AddbaRequest::setBufferSize(uint16_t bufferSize)
{
    handleChange();
    this->bufferSize = bufferSize;
}

::omnetpp::simtime_t Ieee80211AddbaRequest::getBlockAckTimeoutValue() const
{
    return this->blockAckTimeoutValue;
}

void Ieee80211AddbaRequest::setBlockAckTimeoutValue(::omnetpp::simtime_t blockAckTimeoutValue)
{
    handleChange();
    this->blockAckTimeoutValue = blockAckTimeoutValue;
}

uint8_t Ieee80211AddbaRequest::get_fragmentNumber() const
{
    return this->_fragmentNumber;
}

void Ieee80211AddbaRequest::set_fragmentNumber(uint8_t _fragmentNumber)
{
    handleChange();
    this->_fragmentNumber = _fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211AddbaRequest::getStartingSequenceNumber() const
{
    return this->startingSequenceNumber;
}

void Ieee80211AddbaRequest::setStartingSequenceNumber(const SequenceNumberCyclic& startingSequenceNumber)
{
    handleChange();
    this->startingSequenceNumber = startingSequenceNumber;
}

class Ieee80211AddbaRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dialogToken,
        FIELD_aMsduSupported,
        FIELD_blockAckPolicy,
        FIELD_tid,
        FIELD_bufferSize,
        FIELD_blockAckTimeoutValue,
        FIELD__fragmentNumber,
        FIELD_startingSequenceNumber,
    };
  public:
    Ieee80211AddbaRequestDescriptor();
    virtual ~Ieee80211AddbaRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211AddbaRequestDescriptor)

Ieee80211AddbaRequestDescriptor::Ieee80211AddbaRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AddbaRequest)), "inet::ieee80211::Ieee80211ActionFrame")
{
    propertyNames = nullptr;
}

Ieee80211AddbaRequestDescriptor::~Ieee80211AddbaRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AddbaRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AddbaRequest *>(obj)!=nullptr;
}

const char **Ieee80211AddbaRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AddbaRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AddbaRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ieee80211AddbaRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dialogToken
        FD_ISEDITABLE,    // FIELD_aMsduSupported
        FD_ISEDITABLE,    // FIELD_blockAckPolicy
        FD_ISEDITABLE,    // FIELD_tid
        FD_ISEDITABLE,    // FIELD_bufferSize
        FD_ISEDITABLE,    // FIELD_blockAckTimeoutValue
        FD_ISEDITABLE,    // FIELD__fragmentNumber
        0,    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211AddbaRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dialogToken",
        "aMsduSupported",
        "blockAckPolicy",
        "tid",
        "bufferSize",
        "blockAckTimeoutValue",
        "_fragmentNumber",
        "startingSequenceNumber",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ieee80211AddbaRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dialogToken") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "aMsduSupported") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "blockAckPolicy") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "tid") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "bufferSize") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "blockAckTimeoutValue") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "_fragmentNumber") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "startingSequenceNumber") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AddbaRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_dialogToken
        "bool",    // FIELD_aMsduSupported
        "bool",    // FIELD_blockAckPolicy
        "uint8_t",    // FIELD_tid
        "uint16_t",    // FIELD_bufferSize
        "omnetpp::simtime_t",    // FIELD_blockAckTimeoutValue
        "uint8_t",    // FIELD__fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211AddbaRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211AddbaRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211AddbaRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AddbaRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AddbaRequest'", field);
    }
}

const char *Ieee80211AddbaRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AddbaRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: return ulong2string(pp->getDialogToken());
        case FIELD_aMsduSupported: return bool2string(pp->getAMsduSupported());
        case FIELD_blockAckPolicy: return bool2string(pp->getBlockAckPolicy());
        case FIELD_tid: return ulong2string(pp->getTid());
        case FIELD_bufferSize: return ulong2string(pp->getBufferSize());
        case FIELD_blockAckTimeoutValue: return simtime2string(pp->getBlockAckTimeoutValue());
        case FIELD__fragmentNumber: return ulong2string(pp->get_fragmentNumber());
        case FIELD_startingSequenceNumber: return "";
        default: return "";
    }
}

void Ieee80211AddbaRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: pp->setDialogToken(string2ulong(value)); break;
        case FIELD_aMsduSupported: pp->setAMsduSupported(string2bool(value)); break;
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(string2bool(value)); break;
        case FIELD_tid: pp->setTid(string2ulong(value)); break;
        case FIELD_bufferSize: pp->setBufferSize(string2ulong(value)); break;
        case FIELD_blockAckTimeoutValue: pp->setBlockAckTimeoutValue(string2simtime(value)); break;
        case FIELD__fragmentNumber: pp->set_fragmentNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaRequest'", field);
    }
}

omnetpp::cValue Ieee80211AddbaRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: return (omnetpp::intval_t)(pp->getDialogToken());
        case FIELD_aMsduSupported: return pp->getAMsduSupported();
        case FIELD_blockAckPolicy: return pp->getBlockAckPolicy();
        case FIELD_tid: return (omnetpp::intval_t)(pp->getTid());
        case FIELD_bufferSize: return (omnetpp::intval_t)(pp->getBufferSize());
        case FIELD_blockAckTimeoutValue: return pp->getBlockAckTimeoutValue().dbl();
        case FIELD__fragmentNumber: return (omnetpp::intval_t)(pp->get_fragmentNumber());
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AddbaRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AddbaRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: pp->setDialogToken(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_aMsduSupported: pp->setAMsduSupported(value.boolValue()); break;
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(value.boolValue()); break;
        case FIELD_tid: pp->setTid(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_bufferSize: pp->setBufferSize(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_blockAckTimeoutValue: pp->setBlockAckTimeoutValue(value.doubleValue()); break;
        case FIELD__fragmentNumber: pp->set_fragmentNumber(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaRequest'", field);
    }
}

const char *Ieee80211AddbaRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211AddbaRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AddbaRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaRequest *pp = omnetpp::fromAnyPtr<Ieee80211AddbaRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaRequest'", field);
    }
}

Register_Class(Ieee80211AddbaResponse)

Ieee80211AddbaResponse::Ieee80211AddbaResponse() : ::inet::ieee80211::Ieee80211ActionFrame()
{
    this->setChunkLength(LENGTH_ADDBARESP - B(4));
    this->setCategory(3);
    this->setBlockAckAction(1);

}

Ieee80211AddbaResponse::Ieee80211AddbaResponse(const Ieee80211AddbaResponse& other) : ::inet::ieee80211::Ieee80211ActionFrame(other)
{
    copy(other);
}

Ieee80211AddbaResponse::~Ieee80211AddbaResponse()
{
}

Ieee80211AddbaResponse& Ieee80211AddbaResponse::operator=(const Ieee80211AddbaResponse& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211ActionFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211AddbaResponse::copy(const Ieee80211AddbaResponse& other)
{
    this->dialogToken = other.dialogToken;
    this->statusCode = other.statusCode;
    this->aMsduSupported = other.aMsduSupported;
    this->blockAckPolicy = other.blockAckPolicy;
    this->tid = other.tid;
    this->bufferSize = other.bufferSize;
    this->blockAckTimeoutValue = other.blockAckTimeoutValue;
}

void Ieee80211AddbaResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimPack(b);
    doParsimPacking(b,this->dialogToken);
    doParsimPacking(b,this->statusCode);
    doParsimPacking(b,this->aMsduSupported);
    doParsimPacking(b,this->blockAckPolicy);
    doParsimPacking(b,this->tid);
    doParsimPacking(b,this->bufferSize);
    doParsimPacking(b,this->blockAckTimeoutValue);
}

void Ieee80211AddbaResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->dialogToken);
    doParsimUnpacking(b,this->statusCode);
    doParsimUnpacking(b,this->aMsduSupported);
    doParsimUnpacking(b,this->blockAckPolicy);
    doParsimUnpacking(b,this->tid);
    doParsimUnpacking(b,this->bufferSize);
    doParsimUnpacking(b,this->blockAckTimeoutValue);
}

uint8_t Ieee80211AddbaResponse::getDialogToken() const
{
    return this->dialogToken;
}

void Ieee80211AddbaResponse::setDialogToken(uint8_t dialogToken)
{
    handleChange();
    this->dialogToken = dialogToken;
}

uint16_t Ieee80211AddbaResponse::getStatusCode() const
{
    return this->statusCode;
}

void Ieee80211AddbaResponse::setStatusCode(uint16_t statusCode)
{
    handleChange();
    this->statusCode = statusCode;
}

bool Ieee80211AddbaResponse::getAMsduSupported() const
{
    return this->aMsduSupported;
}

void Ieee80211AddbaResponse::setAMsduSupported(bool aMsduSupported)
{
    handleChange();
    this->aMsduSupported = aMsduSupported;
}

bool Ieee80211AddbaResponse::getBlockAckPolicy() const
{
    return this->blockAckPolicy;
}

void Ieee80211AddbaResponse::setBlockAckPolicy(bool blockAckPolicy)
{
    handleChange();
    this->blockAckPolicy = blockAckPolicy;
}

uint8_t Ieee80211AddbaResponse::getTid() const
{
    return this->tid;
}

void Ieee80211AddbaResponse::setTid(uint8_t tid)
{
    handleChange();
    this->tid = tid;
}

uint16_t Ieee80211AddbaResponse::getBufferSize() const
{
    return this->bufferSize;
}

void Ieee80211AddbaResponse::setBufferSize(uint16_t bufferSize)
{
    handleChange();
    this->bufferSize = bufferSize;
}

::omnetpp::simtime_t Ieee80211AddbaResponse::getBlockAckTimeoutValue() const
{
    return this->blockAckTimeoutValue;
}

void Ieee80211AddbaResponse::setBlockAckTimeoutValue(::omnetpp::simtime_t blockAckTimeoutValue)
{
    handleChange();
    this->blockAckTimeoutValue = blockAckTimeoutValue;
}

class Ieee80211AddbaResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dialogToken,
        FIELD_statusCode,
        FIELD_aMsduSupported,
        FIELD_blockAckPolicy,
        FIELD_tid,
        FIELD_bufferSize,
        FIELD_blockAckTimeoutValue,
    };
  public:
    Ieee80211AddbaResponseDescriptor();
    virtual ~Ieee80211AddbaResponseDescriptor();

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

Register_ClassDescriptor(Ieee80211AddbaResponseDescriptor)

Ieee80211AddbaResponseDescriptor::Ieee80211AddbaResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211AddbaResponse)), "inet::ieee80211::Ieee80211ActionFrame")
{
    propertyNames = nullptr;
}

Ieee80211AddbaResponseDescriptor::~Ieee80211AddbaResponseDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211AddbaResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211AddbaResponse *>(obj)!=nullptr;
}

const char **Ieee80211AddbaResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211AddbaResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211AddbaResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int Ieee80211AddbaResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dialogToken
        FD_ISEDITABLE,    // FIELD_statusCode
        FD_ISEDITABLE,    // FIELD_aMsduSupported
        FD_ISEDITABLE,    // FIELD_blockAckPolicy
        FD_ISEDITABLE,    // FIELD_tid
        FD_ISEDITABLE,    // FIELD_bufferSize
        FD_ISEDITABLE,    // FIELD_blockAckTimeoutValue
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211AddbaResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dialogToken",
        "statusCode",
        "aMsduSupported",
        "blockAckPolicy",
        "tid",
        "bufferSize",
        "blockAckTimeoutValue",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ieee80211AddbaResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dialogToken") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "statusCode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "aMsduSupported") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "blockAckPolicy") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "tid") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "bufferSize") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "blockAckTimeoutValue") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211AddbaResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_dialogToken
        "uint16_t",    // FIELD_statusCode
        "bool",    // FIELD_aMsduSupported
        "bool",    // FIELD_blockAckPolicy
        "uint8_t",    // FIELD_tid
        "uint16_t",    // FIELD_bufferSize
        "omnetpp::simtime_t",    // FIELD_blockAckTimeoutValue
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211AddbaResponseDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211AddbaResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211AddbaResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211AddbaResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211AddbaResponse'", field);
    }
}

const char *Ieee80211AddbaResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211AddbaResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: return ulong2string(pp->getDialogToken());
        case FIELD_statusCode: return ulong2string(pp->getStatusCode());
        case FIELD_aMsduSupported: return bool2string(pp->getAMsduSupported());
        case FIELD_blockAckPolicy: return bool2string(pp->getBlockAckPolicy());
        case FIELD_tid: return ulong2string(pp->getTid());
        case FIELD_bufferSize: return ulong2string(pp->getBufferSize());
        case FIELD_blockAckTimeoutValue: return simtime2string(pp->getBlockAckTimeoutValue());
        default: return "";
    }
}

void Ieee80211AddbaResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: pp->setDialogToken(string2ulong(value)); break;
        case FIELD_statusCode: pp->setStatusCode(string2ulong(value)); break;
        case FIELD_aMsduSupported: pp->setAMsduSupported(string2bool(value)); break;
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(string2bool(value)); break;
        case FIELD_tid: pp->setTid(string2ulong(value)); break;
        case FIELD_bufferSize: pp->setBufferSize(string2ulong(value)); break;
        case FIELD_blockAckTimeoutValue: pp->setBlockAckTimeoutValue(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaResponse'", field);
    }
}

omnetpp::cValue Ieee80211AddbaResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: return (omnetpp::intval_t)(pp->getDialogToken());
        case FIELD_statusCode: return (omnetpp::intval_t)(pp->getStatusCode());
        case FIELD_aMsduSupported: return pp->getAMsduSupported();
        case FIELD_blockAckPolicy: return pp->getBlockAckPolicy();
        case FIELD_tid: return (omnetpp::intval_t)(pp->getTid());
        case FIELD_bufferSize: return (omnetpp::intval_t)(pp->getBufferSize());
        case FIELD_blockAckTimeoutValue: return pp->getBlockAckTimeoutValue().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211AddbaResponse' as cValue -- field index out of range?", field);
    }
}

void Ieee80211AddbaResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        case FIELD_dialogToken: pp->setDialogToken(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_statusCode: pp->setStatusCode(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_aMsduSupported: pp->setAMsduSupported(value.boolValue()); break;
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(value.boolValue()); break;
        case FIELD_tid: pp->setTid(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_bufferSize: pp->setBufferSize(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_blockAckTimeoutValue: pp->setBlockAckTimeoutValue(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaResponse'", field);
    }
}

const char *Ieee80211AddbaResponseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211AddbaResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211AddbaResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211AddbaResponse *pp = omnetpp::fromAnyPtr<Ieee80211AddbaResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211AddbaResponse'", field);
    }
}

Register_Class(Ieee80211Delba)

Ieee80211Delba::Ieee80211Delba() : ::inet::ieee80211::Ieee80211ActionFrame()
{
    this->setChunkLength(LENGTH_DELBA);
    this->setCategory(3);
    this->setBlockAckAction(2);

}

Ieee80211Delba::Ieee80211Delba(const Ieee80211Delba& other) : ::inet::ieee80211::Ieee80211ActionFrame(other)
{
    copy(other);
}

Ieee80211Delba::~Ieee80211Delba()
{
}

Ieee80211Delba& Ieee80211Delba::operator=(const Ieee80211Delba& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211ActionFrame::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Delba::copy(const Ieee80211Delba& other)
{
    this->reserved = other.reserved;
    this->initiator = other.initiator;
    this->tid = other.tid;
    this->reasonCode = other.reasonCode;
}

void Ieee80211Delba::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->initiator);
    doParsimPacking(b,this->tid);
    doParsimPacking(b,this->reasonCode);
}

void Ieee80211Delba::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211ActionFrame::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->initiator);
    doParsimUnpacking(b,this->tid);
    doParsimUnpacking(b,this->reasonCode);
}

uint16_t Ieee80211Delba::getReserved() const
{
    return this->reserved;
}

void Ieee80211Delba::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

bool Ieee80211Delba::getInitiator() const
{
    return this->initiator;
}

void Ieee80211Delba::setInitiator(bool initiator)
{
    handleChange();
    this->initiator = initiator;
}

uint8_t Ieee80211Delba::getTid() const
{
    return this->tid;
}

void Ieee80211Delba::setTid(uint8_t tid)
{
    handleChange();
    this->tid = tid;
}

uint16_t Ieee80211Delba::getReasonCode() const
{
    return this->reasonCode;
}

void Ieee80211Delba::setReasonCode(uint16_t reasonCode)
{
    handleChange();
    this->reasonCode = reasonCode;
}

class Ieee80211DelbaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_initiator,
        FIELD_tid,
        FIELD_reasonCode,
    };
  public:
    Ieee80211DelbaDescriptor();
    virtual ~Ieee80211DelbaDescriptor();

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

Register_ClassDescriptor(Ieee80211DelbaDescriptor)

Ieee80211DelbaDescriptor::Ieee80211DelbaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Delba)), "inet::ieee80211::Ieee80211ActionFrame")
{
    propertyNames = nullptr;
}

Ieee80211DelbaDescriptor::~Ieee80211DelbaDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DelbaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Delba *>(obj)!=nullptr;
}

const char **Ieee80211DelbaDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DelbaDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DelbaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211DelbaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_initiator
        FD_ISEDITABLE,    // FIELD_tid
        FD_ISEDITABLE,    // FIELD_reasonCode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DelbaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "initiator",
        "tid",
        "reasonCode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211DelbaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "initiator") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "tid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "reasonCode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DelbaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "bool",    // FIELD_initiator
        "uint8_t",    // FIELD_tid
        "uint16_t",    // FIELD_reasonCode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DelbaDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211DelbaDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211DelbaDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DelbaDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Delba'", field);
    }
}

const char *Ieee80211DelbaDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DelbaDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_initiator: return bool2string(pp->getInitiator());
        case FIELD_tid: return ulong2string(pp->getTid());
        case FIELD_reasonCode: return ulong2string(pp->getReasonCode());
        default: return "";
    }
}

void Ieee80211DelbaDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_initiator: pp->setInitiator(string2bool(value)); break;
        case FIELD_tid: pp->setTid(string2ulong(value)); break;
        case FIELD_reasonCode: pp->setReasonCode(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Delba'", field);
    }
}

omnetpp::cValue Ieee80211DelbaDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_initiator: return pp->getInitiator();
        case FIELD_tid: return (omnetpp::intval_t)(pp->getTid());
        case FIELD_reasonCode: return (omnetpp::intval_t)(pp->getReasonCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Delba' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DelbaDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_initiator: pp->setInitiator(value.boolValue()); break;
        case FIELD_tid: pp->setTid(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_reasonCode: pp->setReasonCode(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Delba'", field);
    }
}

const char *Ieee80211DelbaDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DelbaDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DelbaDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Delba *pp = omnetpp::fromAnyPtr<Ieee80211Delba>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Delba'", field);
    }
}

Register_Class(Ieee80211BlockAckReq)

Ieee80211BlockAckReq::Ieee80211BlockAckReq() : ::inet::ieee80211::Ieee80211TwoAddressHeader()
{
    this->setType(ST_BLOCKACK_REQ);

}

Ieee80211BlockAckReq::Ieee80211BlockAckReq(const Ieee80211BlockAckReq& other) : ::inet::ieee80211::Ieee80211TwoAddressHeader(other)
{
    copy(other);
}

Ieee80211BlockAckReq::~Ieee80211BlockAckReq()
{
}

Ieee80211BlockAckReq& Ieee80211BlockAckReq::operator=(const Ieee80211BlockAckReq& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211TwoAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211BlockAckReq::copy(const Ieee80211BlockAckReq& other)
{
    this->multiTid = other.multiTid;
    this->compressedBitmap = other.compressedBitmap;
    this->barAckPolicy = other.barAckPolicy;
    this->reserved = other.reserved;
}

void Ieee80211BlockAckReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimPack(b);
    doParsimPacking(b,this->multiTid);
    doParsimPacking(b,this->compressedBitmap);
    doParsimPacking(b,this->barAckPolicy);
    doParsimPacking(b,this->reserved);
}

void Ieee80211BlockAckReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->multiTid);
    doParsimUnpacking(b,this->compressedBitmap);
    doParsimUnpacking(b,this->barAckPolicy);
    doParsimUnpacking(b,this->reserved);
}

bool Ieee80211BlockAckReq::getMultiTid() const
{
    return this->multiTid;
}

void Ieee80211BlockAckReq::setMultiTid(bool multiTid)
{
    handleChange();
    this->multiTid = multiTid;
}

bool Ieee80211BlockAckReq::getCompressedBitmap() const
{
    return this->compressedBitmap;
}

void Ieee80211BlockAckReq::setCompressedBitmap(bool compressedBitmap)
{
    handleChange();
    this->compressedBitmap = compressedBitmap;
}

bool Ieee80211BlockAckReq::getBarAckPolicy() const
{
    return this->barAckPolicy;
}

void Ieee80211BlockAckReq::setBarAckPolicy(bool barAckPolicy)
{
    handleChange();
    this->barAckPolicy = barAckPolicy;
}

uint16_t Ieee80211BlockAckReq::getReserved() const
{
    return this->reserved;
}

void Ieee80211BlockAckReq::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

class Ieee80211BlockAckReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_multiTid,
        FIELD_compressedBitmap,
        FIELD_barAckPolicy,
        FIELD_reserved,
    };
  public:
    Ieee80211BlockAckReqDescriptor();
    virtual ~Ieee80211BlockAckReqDescriptor();

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

Register_ClassDescriptor(Ieee80211BlockAckReqDescriptor)

Ieee80211BlockAckReqDescriptor::Ieee80211BlockAckReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211BlockAckReq)), "inet::ieee80211::Ieee80211TwoAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211BlockAckReqDescriptor::~Ieee80211BlockAckReqDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211BlockAckReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211BlockAckReq *>(obj)!=nullptr;
}

const char **Ieee80211BlockAckReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211BlockAckReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211BlockAckReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211BlockAckReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_multiTid
        FD_ISEDITABLE,    // FIELD_compressedBitmap
        FD_ISEDITABLE,    // FIELD_barAckPolicy
        FD_ISEDITABLE,    // FIELD_reserved
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211BlockAckReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "multiTid",
        "compressedBitmap",
        "barAckPolicy",
        "reserved",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211BlockAckReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "multiTid") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "compressedBitmap") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "barAckPolicy") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211BlockAckReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_multiTid
        "bool",    // FIELD_compressedBitmap
        "bool",    // FIELD_barAckPolicy
        "uint16_t",    // FIELD_reserved
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211BlockAckReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211BlockAckReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211BlockAckReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211BlockAckReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211BlockAckReq'", field);
    }
}

const char *Ieee80211BlockAckReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211BlockAckReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_multiTid: return bool2string(pp->getMultiTid());
        case FIELD_compressedBitmap: return bool2string(pp->getCompressedBitmap());
        case FIELD_barAckPolicy: return bool2string(pp->getBarAckPolicy());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        default: return "";
    }
}

void Ieee80211BlockAckReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_multiTid: pp->setMultiTid(string2bool(value)); break;
        case FIELD_compressedBitmap: pp->setCompressedBitmap(string2bool(value)); break;
        case FIELD_barAckPolicy: pp->setBarAckPolicy(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAckReq'", field);
    }
}

omnetpp::cValue Ieee80211BlockAckReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_multiTid: return pp->getMultiTid();
        case FIELD_compressedBitmap: return pp->getCompressedBitmap();
        case FIELD_barAckPolicy: return pp->getBarAckPolicy();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211BlockAckReq' as cValue -- field index out of range?", field);
    }
}

void Ieee80211BlockAckReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_multiTid: pp->setMultiTid(value.boolValue()); break;
        case FIELD_compressedBitmap: pp->setCompressedBitmap(value.boolValue()); break;
        case FIELD_barAckPolicy: pp->setBarAckPolicy(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAckReq'", field);
    }
}

const char *Ieee80211BlockAckReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211BlockAckReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211BlockAckReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAckReq'", field);
    }
}

Register_Class(Ieee80211BasicBlockAckReq)

Ieee80211BasicBlockAckReq::Ieee80211BasicBlockAckReq() : ::inet::ieee80211::Ieee80211BlockAckReq()
{
    this->setChunkLength(B(38));
    this->setMultiTid(0);
    this->setCompressedBitmap(0);

}

Ieee80211BasicBlockAckReq::Ieee80211BasicBlockAckReq(const Ieee80211BasicBlockAckReq& other) : ::inet::ieee80211::Ieee80211BlockAckReq(other)
{
    copy(other);
}

Ieee80211BasicBlockAckReq::~Ieee80211BasicBlockAckReq()
{
}

Ieee80211BasicBlockAckReq& Ieee80211BasicBlockAckReq::operator=(const Ieee80211BasicBlockAckReq& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAckReq::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211BasicBlockAckReq::copy(const Ieee80211BasicBlockAckReq& other)
{
    this->tidInfo = other.tidInfo;
    this->fragmentNumber = other.fragmentNumber;
    this->startingSequenceNumber = other.startingSequenceNumber;
}

void Ieee80211BasicBlockAckReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimPack(b);
    doParsimPacking(b,this->tidInfo);
    doParsimPacking(b,this->fragmentNumber);
    doParsimPacking(b,this->startingSequenceNumber);
}

void Ieee80211BasicBlockAckReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimUnpack(b);
    doParsimUnpacking(b,this->tidInfo);
    doParsimUnpacking(b,this->fragmentNumber);
    doParsimUnpacking(b,this->startingSequenceNumber);
}

int Ieee80211BasicBlockAckReq::getTidInfo() const
{
    return this->tidInfo;
}

void Ieee80211BasicBlockAckReq::setTidInfo(int tidInfo)
{
    handleChange();
    this->tidInfo = tidInfo;
}

int Ieee80211BasicBlockAckReq::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void Ieee80211BasicBlockAckReq::setFragmentNumber(int fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211BasicBlockAckReq::getStartingSequenceNumber() const
{
    return this->startingSequenceNumber;
}

void Ieee80211BasicBlockAckReq::setStartingSequenceNumber(const SequenceNumberCyclic& startingSequenceNumber)
{
    handleChange();
    this->startingSequenceNumber = startingSequenceNumber;
}

class Ieee80211BasicBlockAckReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tidInfo,
        FIELD_fragmentNumber,
        FIELD_startingSequenceNumber,
    };
  public:
    Ieee80211BasicBlockAckReqDescriptor();
    virtual ~Ieee80211BasicBlockAckReqDescriptor();

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

Register_ClassDescriptor(Ieee80211BasicBlockAckReqDescriptor)

Ieee80211BasicBlockAckReqDescriptor::Ieee80211BasicBlockAckReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211BasicBlockAckReq)), "inet::ieee80211::Ieee80211BlockAckReq")
{
    propertyNames = nullptr;
}

Ieee80211BasicBlockAckReqDescriptor::~Ieee80211BasicBlockAckReqDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211BasicBlockAckReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211BasicBlockAckReq *>(obj)!=nullptr;
}

const char **Ieee80211BasicBlockAckReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211BasicBlockAckReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211BasicBlockAckReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211BasicBlockAckReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tidInfo
        FD_ISEDITABLE,    // FIELD_fragmentNumber
        0,    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211BasicBlockAckReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tidInfo",
        "fragmentNumber",
        "startingSequenceNumber",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211BasicBlockAckReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tidInfo") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "startingSequenceNumber") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211BasicBlockAckReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_tidInfo
        "int",    // FIELD_fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211BasicBlockAckReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211BasicBlockAckReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211BasicBlockAckReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211BasicBlockAckReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211BasicBlockAckReq'", field);
    }
}

const char *Ieee80211BasicBlockAckReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211BasicBlockAckReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: return long2string(pp->getTidInfo());
        case FIELD_fragmentNumber: return long2string(pp->getFragmentNumber());
        case FIELD_startingSequenceNumber: return "";
        default: return "";
    }
}

void Ieee80211BasicBlockAckReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: pp->setTidInfo(string2long(value)); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAckReq'", field);
    }
}

omnetpp::cValue Ieee80211BasicBlockAckReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: return pp->getTidInfo();
        case FIELD_fragmentNumber: return pp->getFragmentNumber();
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211BasicBlockAckReq' as cValue -- field index out of range?", field);
    }
}

void Ieee80211BasicBlockAckReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: pp->setTidInfo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAckReq'", field);
    }
}

const char *Ieee80211BasicBlockAckReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211BasicBlockAckReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211BasicBlockAckReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAckReq'", field);
    }
}

Register_Class(Ieee80211CompressedBlockAckReq)

Ieee80211CompressedBlockAckReq::Ieee80211CompressedBlockAckReq() : ::inet::ieee80211::Ieee80211BlockAckReq()
{
    this->setChunkLength(B(38));
    this->setMultiTid(0);
    this->setCompressedBitmap(1);

}

Ieee80211CompressedBlockAckReq::Ieee80211CompressedBlockAckReq(const Ieee80211CompressedBlockAckReq& other) : ::inet::ieee80211::Ieee80211BlockAckReq(other)
{
    copy(other);
}

Ieee80211CompressedBlockAckReq::~Ieee80211CompressedBlockAckReq()
{
}

Ieee80211CompressedBlockAckReq& Ieee80211CompressedBlockAckReq::operator=(const Ieee80211CompressedBlockAckReq& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAckReq::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211CompressedBlockAckReq::copy(const Ieee80211CompressedBlockAckReq& other)
{
    this->tidInfo = other.tidInfo;
    this->fragmentNumber = other.fragmentNumber;
    this->startingSequenceNumber = other.startingSequenceNumber;
}

void Ieee80211CompressedBlockAckReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimPack(b);
    doParsimPacking(b,this->tidInfo);
    doParsimPacking(b,this->fragmentNumber);
    doParsimPacking(b,this->startingSequenceNumber);
}

void Ieee80211CompressedBlockAckReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimUnpack(b);
    doParsimUnpacking(b,this->tidInfo);
    doParsimUnpacking(b,this->fragmentNumber);
    doParsimUnpacking(b,this->startingSequenceNumber);
}

int Ieee80211CompressedBlockAckReq::getTidInfo() const
{
    return this->tidInfo;
}

void Ieee80211CompressedBlockAckReq::setTidInfo(int tidInfo)
{
    handleChange();
    this->tidInfo = tidInfo;
}

int Ieee80211CompressedBlockAckReq::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void Ieee80211CompressedBlockAckReq::setFragmentNumber(int fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211CompressedBlockAckReq::getStartingSequenceNumber() const
{
    return this->startingSequenceNumber;
}

void Ieee80211CompressedBlockAckReq::setStartingSequenceNumber(const SequenceNumberCyclic& startingSequenceNumber)
{
    handleChange();
    this->startingSequenceNumber = startingSequenceNumber;
}

class Ieee80211CompressedBlockAckReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tidInfo,
        FIELD_fragmentNumber,
        FIELD_startingSequenceNumber,
    };
  public:
    Ieee80211CompressedBlockAckReqDescriptor();
    virtual ~Ieee80211CompressedBlockAckReqDescriptor();

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

Register_ClassDescriptor(Ieee80211CompressedBlockAckReqDescriptor)

Ieee80211CompressedBlockAckReqDescriptor::Ieee80211CompressedBlockAckReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211CompressedBlockAckReq)), "inet::ieee80211::Ieee80211BlockAckReq")
{
    propertyNames = nullptr;
}

Ieee80211CompressedBlockAckReqDescriptor::~Ieee80211CompressedBlockAckReqDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211CompressedBlockAckReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211CompressedBlockAckReq *>(obj)!=nullptr;
}

const char **Ieee80211CompressedBlockAckReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211CompressedBlockAckReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211CompressedBlockAckReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ieee80211CompressedBlockAckReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tidInfo
        FD_ISEDITABLE,    // FIELD_fragmentNumber
        0,    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211CompressedBlockAckReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tidInfo",
        "fragmentNumber",
        "startingSequenceNumber",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ieee80211CompressedBlockAckReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tidInfo") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "startingSequenceNumber") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211CompressedBlockAckReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_tidInfo
        "int",    // FIELD_fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_startingSequenceNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211CompressedBlockAckReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211CompressedBlockAckReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211CompressedBlockAckReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211CompressedBlockAckReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211CompressedBlockAckReq'", field);
    }
}

const char *Ieee80211CompressedBlockAckReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211CompressedBlockAckReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: return long2string(pp->getTidInfo());
        case FIELD_fragmentNumber: return long2string(pp->getFragmentNumber());
        case FIELD_startingSequenceNumber: return "";
        default: return "";
    }
}

void Ieee80211CompressedBlockAckReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: pp->setTidInfo(string2long(value)); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAckReq'", field);
    }
}

omnetpp::cValue Ieee80211CompressedBlockAckReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: return pp->getTidInfo();
        case FIELD_fragmentNumber: return pp->getFragmentNumber();
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211CompressedBlockAckReq' as cValue -- field index out of range?", field);
    }
}

void Ieee80211CompressedBlockAckReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_tidInfo: pp->setTidInfo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAckReq'", field);
    }
}

const char *Ieee80211CompressedBlockAckReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211CompressedBlockAckReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211CompressedBlockAckReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAckReq'", field);
    }
}

Register_Class(Ieee80211MultiTidBlockAckReq)

Ieee80211MultiTidBlockAckReq::Ieee80211MultiTidBlockAckReq() : ::inet::ieee80211::Ieee80211BlockAckReq()
{
    this->setMultiTid(1);
    this->setCompressedBitmap(1);
}

Ieee80211MultiTidBlockAckReq::Ieee80211MultiTidBlockAckReq(const Ieee80211MultiTidBlockAckReq& other) : ::inet::ieee80211::Ieee80211BlockAckReq(other)
{
    copy(other);
}

Ieee80211MultiTidBlockAckReq::~Ieee80211MultiTidBlockAckReq()
{
}

Ieee80211MultiTidBlockAckReq& Ieee80211MultiTidBlockAckReq::operator=(const Ieee80211MultiTidBlockAckReq& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAckReq::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MultiTidBlockAckReq::copy(const Ieee80211MultiTidBlockAckReq& other)
{
}

void Ieee80211MultiTidBlockAckReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimPack(b);
}

void Ieee80211MultiTidBlockAckReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAckReq::parsimUnpack(b);
}

class Ieee80211MultiTidBlockAckReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211MultiTidBlockAckReqDescriptor();
    virtual ~Ieee80211MultiTidBlockAckReqDescriptor();

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

Register_ClassDescriptor(Ieee80211MultiTidBlockAckReqDescriptor)

Ieee80211MultiTidBlockAckReqDescriptor::Ieee80211MultiTidBlockAckReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MultiTidBlockAckReq)), "inet::ieee80211::Ieee80211BlockAckReq")
{
    propertyNames = nullptr;
}

Ieee80211MultiTidBlockAckReqDescriptor::~Ieee80211MultiTidBlockAckReqDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MultiTidBlockAckReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MultiTidBlockAckReq *>(obj)!=nullptr;
}

const char **Ieee80211MultiTidBlockAckReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MultiTidBlockAckReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MultiTidBlockAckReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211MultiTidBlockAckReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211MultiTidBlockAckReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211MultiTidBlockAckReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MultiTidBlockAckReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211MultiTidBlockAckReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MultiTidBlockAckReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MultiTidBlockAckReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MultiTidBlockAckReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MultiTidBlockAckReq'", field);
    }
}

const char *Ieee80211MultiTidBlockAckReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MultiTidBlockAckReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211MultiTidBlockAckReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAckReq'", field);
    }
}

omnetpp::cValue Ieee80211MultiTidBlockAckReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MultiTidBlockAckReq' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MultiTidBlockAckReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAckReq'", field);
    }
}

const char *Ieee80211MultiTidBlockAckReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211MultiTidBlockAckReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MultiTidBlockAckReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAckReq *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAckReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAckReq'", field);
    }
}

Register_Class(Ieee80211BlockAck)

Ieee80211BlockAck::Ieee80211BlockAck() : ::inet::ieee80211::Ieee80211TwoAddressHeader()
{
    this->setType(ST_BLOCKACK);

}

Ieee80211BlockAck::Ieee80211BlockAck(const Ieee80211BlockAck& other) : ::inet::ieee80211::Ieee80211TwoAddressHeader(other)
{
    copy(other);
}

Ieee80211BlockAck::~Ieee80211BlockAck()
{
}

Ieee80211BlockAck& Ieee80211BlockAck::operator=(const Ieee80211BlockAck& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211TwoAddressHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211BlockAck::copy(const Ieee80211BlockAck& other)
{
    this->blockAckPolicy = other.blockAckPolicy;
    this->multiTid = other.multiTid;
    this->compressedBitmap = other.compressedBitmap;
    this->reserved = other.reserved;
}

void Ieee80211BlockAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimPack(b);
    doParsimPacking(b,this->blockAckPolicy);
    doParsimPacking(b,this->multiTid);
    doParsimPacking(b,this->compressedBitmap);
    doParsimPacking(b,this->reserved);
}

void Ieee80211BlockAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211TwoAddressHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->blockAckPolicy);
    doParsimUnpacking(b,this->multiTid);
    doParsimUnpacking(b,this->compressedBitmap);
    doParsimUnpacking(b,this->reserved);
}

bool Ieee80211BlockAck::getBlockAckPolicy() const
{
    return this->blockAckPolicy;
}

void Ieee80211BlockAck::setBlockAckPolicy(bool blockAckPolicy)
{
    handleChange();
    this->blockAckPolicy = blockAckPolicy;
}

bool Ieee80211BlockAck::getMultiTid() const
{
    return this->multiTid;
}

void Ieee80211BlockAck::setMultiTid(bool multiTid)
{
    handleChange();
    this->multiTid = multiTid;
}

bool Ieee80211BlockAck::getCompressedBitmap() const
{
    return this->compressedBitmap;
}

void Ieee80211BlockAck::setCompressedBitmap(bool compressedBitmap)
{
    handleChange();
    this->compressedBitmap = compressedBitmap;
}

uint16_t Ieee80211BlockAck::getReserved() const
{
    return this->reserved;
}

void Ieee80211BlockAck::setReserved(uint16_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

class Ieee80211BlockAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_blockAckPolicy,
        FIELD_multiTid,
        FIELD_compressedBitmap,
        FIELD_reserved,
    };
  public:
    Ieee80211BlockAckDescriptor();
    virtual ~Ieee80211BlockAckDescriptor();

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

Register_ClassDescriptor(Ieee80211BlockAckDescriptor)

Ieee80211BlockAckDescriptor::Ieee80211BlockAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211BlockAck)), "inet::ieee80211::Ieee80211TwoAddressHeader")
{
    propertyNames = nullptr;
}

Ieee80211BlockAckDescriptor::~Ieee80211BlockAckDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211BlockAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211BlockAck *>(obj)!=nullptr;
}

const char **Ieee80211BlockAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211BlockAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211BlockAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211BlockAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_blockAckPolicy
        FD_ISEDITABLE,    // FIELD_multiTid
        FD_ISEDITABLE,    // FIELD_compressedBitmap
        FD_ISEDITABLE,    // FIELD_reserved
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211BlockAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "blockAckPolicy",
        "multiTid",
        "compressedBitmap",
        "reserved",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211BlockAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "blockAckPolicy") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "multiTid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "compressedBitmap") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211BlockAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_blockAckPolicy
        "bool",    // FIELD_multiTid
        "bool",    // FIELD_compressedBitmap
        "uint16_t",    // FIELD_reserved
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211BlockAckDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211BlockAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211BlockAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211BlockAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211BlockAck'", field);
    }
}

const char *Ieee80211BlockAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211BlockAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_blockAckPolicy: return bool2string(pp->getBlockAckPolicy());
        case FIELD_multiTid: return bool2string(pp->getMultiTid());
        case FIELD_compressedBitmap: return bool2string(pp->getCompressedBitmap());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        default: return "";
    }
}

void Ieee80211BlockAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(string2bool(value)); break;
        case FIELD_multiTid: pp->setMultiTid(string2bool(value)); break;
        case FIELD_compressedBitmap: pp->setCompressedBitmap(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAck'", field);
    }
}

omnetpp::cValue Ieee80211BlockAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_blockAckPolicy: return pp->getBlockAckPolicy();
        case FIELD_multiTid: return pp->getMultiTid();
        case FIELD_compressedBitmap: return pp->getCompressedBitmap();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211BlockAck' as cValue -- field index out of range?", field);
    }
}

void Ieee80211BlockAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_blockAckPolicy: pp->setBlockAckPolicy(value.boolValue()); break;
        case FIELD_multiTid: pp->setMultiTid(value.boolValue()); break;
        case FIELD_compressedBitmap: pp->setCompressedBitmap(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAck'", field);
    }
}

const char *Ieee80211BlockAckDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211BlockAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211BlockAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BlockAck'", field);
    }
}

Register_Class(Ieee80211BasicBlockAck)

Ieee80211BasicBlockAck::Ieee80211BasicBlockAck() : ::inet::ieee80211::Ieee80211BlockAck()
{
    this->setChunkLength(LENGTH_BASIC_BLOCKACK - B(4));
    this->setMultiTid(0);
    this->setCompressedBitmap(0);

}

Ieee80211BasicBlockAck::Ieee80211BasicBlockAck(const Ieee80211BasicBlockAck& other) : ::inet::ieee80211::Ieee80211BlockAck(other)
{
    copy(other);
}

Ieee80211BasicBlockAck::~Ieee80211BasicBlockAck()
{
}

Ieee80211BasicBlockAck& Ieee80211BasicBlockAck::operator=(const Ieee80211BasicBlockAck& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAck::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211BasicBlockAck::copy(const Ieee80211BasicBlockAck& other)
{
    this->fragmentNumber = other.fragmentNumber;
    this->startingSequenceNumber = other.startingSequenceNumber;
    for (size_t i = 0; i < 64; i++) {
        this->blockAckBitmap[i] = other.blockAckBitmap[i];
    }
    this->tidInfo = other.tidInfo;
}

void Ieee80211BasicBlockAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimPack(b);
    doParsimPacking(b,this->fragmentNumber);
    doParsimPacking(b,this->startingSequenceNumber);
    doParsimArrayPacking(b,this->blockAckBitmap,64);
    doParsimPacking(b,this->tidInfo);
}

void Ieee80211BasicBlockAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimUnpack(b);
    doParsimUnpacking(b,this->fragmentNumber);
    doParsimUnpacking(b,this->startingSequenceNumber);
    doParsimArrayUnpacking(b,this->blockAckBitmap,64);
    doParsimUnpacking(b,this->tidInfo);
}

int Ieee80211BasicBlockAck::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void Ieee80211BasicBlockAck::setFragmentNumber(int fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211BasicBlockAck::getStartingSequenceNumber() const
{
    return this->startingSequenceNumber;
}

void Ieee80211BasicBlockAck::setStartingSequenceNumber(const SequenceNumberCyclic& startingSequenceNumber)
{
    handleChange();
    this->startingSequenceNumber = startingSequenceNumber;
}

size_t Ieee80211BasicBlockAck::getBlockAckBitmapArraySize() const
{
    return 64;
}

const ::inet::BitVector& Ieee80211BasicBlockAck::getBlockAckBitmap(size_t k) const
{
    if (k >= 64) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)64, (unsigned long)k);
    return this->blockAckBitmap[k];
}

void Ieee80211BasicBlockAck::setBlockAckBitmap(size_t k, const ::inet::BitVector& blockAckBitmap)
{
    if (k >= 64) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)64, (unsigned long)k);
    handleChange();
    this->blockAckBitmap[k] = blockAckBitmap;
}

int Ieee80211BasicBlockAck::getTidInfo() const
{
    return this->tidInfo;
}

void Ieee80211BasicBlockAck::setTidInfo(int tidInfo)
{
    handleChange();
    this->tidInfo = tidInfo;
}

class Ieee80211BasicBlockAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fragmentNumber,
        FIELD_startingSequenceNumber,
        FIELD_blockAckBitmap,
        FIELD_tidInfo,
    };
  public:
    Ieee80211BasicBlockAckDescriptor();
    virtual ~Ieee80211BasicBlockAckDescriptor();

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

Register_ClassDescriptor(Ieee80211BasicBlockAckDescriptor)

Ieee80211BasicBlockAckDescriptor::Ieee80211BasicBlockAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211BasicBlockAck)), "inet::ieee80211::Ieee80211BlockAck")
{
    propertyNames = nullptr;
}

Ieee80211BasicBlockAckDescriptor::~Ieee80211BasicBlockAckDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211BasicBlockAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211BasicBlockAck *>(obj)!=nullptr;
}

const char **Ieee80211BasicBlockAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211BasicBlockAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211BasicBlockAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211BasicBlockAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fragmentNumber
        0,    // FIELD_startingSequenceNumber
        FD_ISARRAY,    // FIELD_blockAckBitmap
        FD_ISEDITABLE,    // FIELD_tidInfo
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211BasicBlockAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fragmentNumber",
        "startingSequenceNumber",
        "blockAckBitmap",
        "tidInfo",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211BasicBlockAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "startingSequenceNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "blockAckBitmap") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "tidInfo") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211BasicBlockAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_startingSequenceNumber
        "inet::BitVector",    // FIELD_blockAckBitmap
        "int",    // FIELD_tidInfo
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211BasicBlockAckDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211BasicBlockAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211BasicBlockAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_blockAckBitmap: return 64;
        default: return 0;
    }
}

void Ieee80211BasicBlockAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211BasicBlockAck'", field);
    }
}

const char *Ieee80211BasicBlockAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211BasicBlockAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: return long2string(pp->getFragmentNumber());
        case FIELD_startingSequenceNumber: return "";
        case FIELD_blockAckBitmap: return pp->getBlockAckBitmap(i).toString();
        case FIELD_tidInfo: return long2string(pp->getTidInfo());
        default: return "";
    }
}

void Ieee80211BasicBlockAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2long(value)); break;
        case FIELD_tidInfo: pp->setTidInfo(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAck'", field);
    }
}

omnetpp::cValue Ieee80211BasicBlockAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: return pp->getFragmentNumber();
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        case FIELD_blockAckBitmap: return omnetpp::toAnyPtr(&pp->getBlockAckBitmap(i)); break;
        case FIELD_tidInfo: return pp->getTidInfo();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211BasicBlockAck' as cValue -- field index out of range?", field);
    }
}

void Ieee80211BasicBlockAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tidInfo: pp->setTidInfo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAck'", field);
    }
}

const char *Ieee80211BasicBlockAckDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211BasicBlockAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        case FIELD_blockAckBitmap: return omnetpp::toAnyPtr(&pp->getBlockAckBitmap(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211BasicBlockAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211BasicBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211BasicBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211BasicBlockAck'", field);
    }
}

Register_Class(Ieee80211CompressedBlockAck)

Ieee80211CompressedBlockAck::Ieee80211CompressedBlockAck() : ::inet::ieee80211::Ieee80211BlockAck()
{
    this->setMultiTid(0);
    this->setCompressedBitmap(1);

}

Ieee80211CompressedBlockAck::Ieee80211CompressedBlockAck(const Ieee80211CompressedBlockAck& other) : ::inet::ieee80211::Ieee80211BlockAck(other)
{
    copy(other);
}

Ieee80211CompressedBlockAck::~Ieee80211CompressedBlockAck()
{
}

Ieee80211CompressedBlockAck& Ieee80211CompressedBlockAck::operator=(const Ieee80211CompressedBlockAck& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAck::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211CompressedBlockAck::copy(const Ieee80211CompressedBlockAck& other)
{
    this->fragmentNumber = other.fragmentNumber;
    this->startingSequenceNumber = other.startingSequenceNumber;
    this->blockAckBitmap = other.blockAckBitmap;
    this->tidInfo = other.tidInfo;
}

void Ieee80211CompressedBlockAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimPack(b);
    doParsimPacking(b,this->fragmentNumber);
    doParsimPacking(b,this->startingSequenceNumber);
    doParsimPacking(b,this->blockAckBitmap);
    doParsimPacking(b,this->tidInfo);
}

void Ieee80211CompressedBlockAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimUnpack(b);
    doParsimUnpacking(b,this->fragmentNumber);
    doParsimUnpacking(b,this->startingSequenceNumber);
    doParsimUnpacking(b,this->blockAckBitmap);
    doParsimUnpacking(b,this->tidInfo);
}

int Ieee80211CompressedBlockAck::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void Ieee80211CompressedBlockAck::setFragmentNumber(int fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

const SequenceNumberCyclic& Ieee80211CompressedBlockAck::getStartingSequenceNumber() const
{
    return this->startingSequenceNumber;
}

void Ieee80211CompressedBlockAck::setStartingSequenceNumber(const SequenceNumberCyclic& startingSequenceNumber)
{
    handleChange();
    this->startingSequenceNumber = startingSequenceNumber;
}

const ::inet::BitVector& Ieee80211CompressedBlockAck::getBlockAckBitmap() const
{
    return this->blockAckBitmap;
}

void Ieee80211CompressedBlockAck::setBlockAckBitmap(const ::inet::BitVector& blockAckBitmap)
{
    handleChange();
    this->blockAckBitmap = blockAckBitmap;
}

int Ieee80211CompressedBlockAck::getTidInfo() const
{
    return this->tidInfo;
}

void Ieee80211CompressedBlockAck::setTidInfo(int tidInfo)
{
    handleChange();
    this->tidInfo = tidInfo;
}

class Ieee80211CompressedBlockAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fragmentNumber,
        FIELD_startingSequenceNumber,
        FIELD_blockAckBitmap,
        FIELD_tidInfo,
    };
  public:
    Ieee80211CompressedBlockAckDescriptor();
    virtual ~Ieee80211CompressedBlockAckDescriptor();

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

Register_ClassDescriptor(Ieee80211CompressedBlockAckDescriptor)

Ieee80211CompressedBlockAckDescriptor::Ieee80211CompressedBlockAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211CompressedBlockAck)), "inet::ieee80211::Ieee80211BlockAck")
{
    propertyNames = nullptr;
}

Ieee80211CompressedBlockAckDescriptor::~Ieee80211CompressedBlockAckDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211CompressedBlockAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211CompressedBlockAck *>(obj)!=nullptr;
}

const char **Ieee80211CompressedBlockAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211CompressedBlockAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211CompressedBlockAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211CompressedBlockAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fragmentNumber
        0,    // FIELD_startingSequenceNumber
        0,    // FIELD_blockAckBitmap
        FD_ISEDITABLE,    // FIELD_tidInfo
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211CompressedBlockAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fragmentNumber",
        "startingSequenceNumber",
        "blockAckBitmap",
        "tidInfo",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211CompressedBlockAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "startingSequenceNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "blockAckBitmap") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "tidInfo") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211CompressedBlockAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_fragmentNumber
        "inet::ieee80211::SequenceNumberCyclic",    // FIELD_startingSequenceNumber
        "inet::BitVector",    // FIELD_blockAckBitmap
        "int",    // FIELD_tidInfo
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211CompressedBlockAckDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211CompressedBlockAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211CompressedBlockAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211CompressedBlockAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211CompressedBlockAck'", field);
    }
}

const char *Ieee80211CompressedBlockAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211CompressedBlockAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: return long2string(pp->getFragmentNumber());
        case FIELD_startingSequenceNumber: return "";
        case FIELD_blockAckBitmap: return pp->getBlockAckBitmap().toString();
        case FIELD_tidInfo: return long2string(pp->getTidInfo());
        default: return "";
    }
}

void Ieee80211CompressedBlockAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2long(value)); break;
        case FIELD_tidInfo: pp->setTidInfo(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAck'", field);
    }
}

omnetpp::cValue Ieee80211CompressedBlockAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: return pp->getFragmentNumber();
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        case FIELD_blockAckBitmap: return omnetpp::toAnyPtr(&pp->getBlockAckBitmap()); break;
        case FIELD_tidInfo: return pp->getTidInfo();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211CompressedBlockAck' as cValue -- field index out of range?", field);
    }
}

void Ieee80211CompressedBlockAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_tidInfo: pp->setTidInfo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAck'", field);
    }
}

const char *Ieee80211CompressedBlockAckDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211CompressedBlockAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        case FIELD_startingSequenceNumber: return omnetpp::toAnyPtr(&pp->getStartingSequenceNumber()); break;
        case FIELD_blockAckBitmap: return omnetpp::toAnyPtr(&pp->getBlockAckBitmap()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211CompressedBlockAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211CompressedBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211CompressedBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211CompressedBlockAck'", field);
    }
}

Register_Class(Ieee80211MultiTidBlockAck)

Ieee80211MultiTidBlockAck::Ieee80211MultiTidBlockAck() : ::inet::ieee80211::Ieee80211BlockAck()
{
    this->setMultiTid(1);
    this->setCompressedBitmap(1);
}

Ieee80211MultiTidBlockAck::Ieee80211MultiTidBlockAck(const Ieee80211MultiTidBlockAck& other) : ::inet::ieee80211::Ieee80211BlockAck(other)
{
    copy(other);
}

Ieee80211MultiTidBlockAck::~Ieee80211MultiTidBlockAck()
{
}

Ieee80211MultiTidBlockAck& Ieee80211MultiTidBlockAck::operator=(const Ieee80211MultiTidBlockAck& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211BlockAck::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211MultiTidBlockAck::copy(const Ieee80211MultiTidBlockAck& other)
{
}

void Ieee80211MultiTidBlockAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimPack(b);
}

void Ieee80211MultiTidBlockAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211BlockAck::parsimUnpack(b);
}

class Ieee80211MultiTidBlockAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211MultiTidBlockAckDescriptor();
    virtual ~Ieee80211MultiTidBlockAckDescriptor();

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

Register_ClassDescriptor(Ieee80211MultiTidBlockAckDescriptor)

Ieee80211MultiTidBlockAckDescriptor::Ieee80211MultiTidBlockAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211MultiTidBlockAck)), "inet::ieee80211::Ieee80211BlockAck")
{
    propertyNames = nullptr;
}

Ieee80211MultiTidBlockAckDescriptor::~Ieee80211MultiTidBlockAckDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211MultiTidBlockAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211MultiTidBlockAck *>(obj)!=nullptr;
}

const char **Ieee80211MultiTidBlockAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211MultiTidBlockAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211MultiTidBlockAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211MultiTidBlockAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211MultiTidBlockAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211MultiTidBlockAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211MultiTidBlockAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211MultiTidBlockAckDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211MultiTidBlockAckDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211MultiTidBlockAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211MultiTidBlockAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211MultiTidBlockAck'", field);
    }
}

const char *Ieee80211MultiTidBlockAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211MultiTidBlockAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211MultiTidBlockAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAck'", field);
    }
}

omnetpp::cValue Ieee80211MultiTidBlockAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211MultiTidBlockAck' as cValue -- field index out of range?", field);
    }
}

void Ieee80211MultiTidBlockAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAck'", field);
    }
}

const char *Ieee80211MultiTidBlockAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211MultiTidBlockAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211MultiTidBlockAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211MultiTidBlockAck *pp = omnetpp::fromAnyPtr<Ieee80211MultiTidBlockAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211MultiTidBlockAck'", field);
    }
}

}  // namespace ieee80211
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

