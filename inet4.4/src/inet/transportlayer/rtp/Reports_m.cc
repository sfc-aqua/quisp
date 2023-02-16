//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/Reports.msg.
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
#include "Reports_m.h"

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
namespace rtp {

Register_Class(SenderReport)

SenderReport::SenderReport() : ::omnetpp::cObject()
{
}

SenderReport::SenderReport(const SenderReport& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

SenderReport::~SenderReport()
{
}

SenderReport& SenderReport::operator=(const SenderReport& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void SenderReport::copy(const SenderReport& other)
{
    this->NTPTimeStamp = other.NTPTimeStamp;
    this->RTPTimeStamp = other.RTPTimeStamp;
    this->packetCount = other.packetCount;
    this->byteCount = other.byteCount;
}

void SenderReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->NTPTimeStamp);
    doParsimPacking(b,this->RTPTimeStamp);
    doParsimPacking(b,this->packetCount);
    doParsimPacking(b,this->byteCount);
}

void SenderReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->NTPTimeStamp);
    doParsimUnpacking(b,this->RTPTimeStamp);
    doParsimUnpacking(b,this->packetCount);
    doParsimUnpacking(b,this->byteCount);
}

uint64_t SenderReport::getNTPTimeStamp() const
{
    return this->NTPTimeStamp;
}

void SenderReport::setNTPTimeStamp(uint64_t NTPTimeStamp)
{
    this->NTPTimeStamp = NTPTimeStamp;
}

uint32_t SenderReport::getRTPTimeStamp() const
{
    return this->RTPTimeStamp;
}

void SenderReport::setRTPTimeStamp(uint32_t RTPTimeStamp)
{
    this->RTPTimeStamp = RTPTimeStamp;
}

uint32_t SenderReport::getPacketCount() const
{
    return this->packetCount;
}

void SenderReport::setPacketCount(uint32_t packetCount)
{
    this->packetCount = packetCount;
}

uint32_t SenderReport::getByteCount() const
{
    return this->byteCount;
}

void SenderReport::setByteCount(uint32_t byteCount)
{
    this->byteCount = byteCount;
}

class SenderReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_NTPTimeStamp,
        FIELD_RTPTimeStamp,
        FIELD_packetCount,
        FIELD_byteCount,
    };
  public:
    SenderReportDescriptor();
    virtual ~SenderReportDescriptor();

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

Register_ClassDescriptor(SenderReportDescriptor)

SenderReportDescriptor::SenderReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::SenderReport)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

SenderReportDescriptor::~SenderReportDescriptor()
{
    delete[] propertyNames;
}

bool SenderReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SenderReport *>(obj)!=nullptr;
}

const char **SenderReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SenderReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SenderReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SenderReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_NTPTimeStamp
        FD_ISEDITABLE,    // FIELD_RTPTimeStamp
        FD_ISEDITABLE,    // FIELD_packetCount
        FD_ISEDITABLE,    // FIELD_byteCount
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SenderReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "NTPTimeStamp",
        "RTPTimeStamp",
        "packetCount",
        "byteCount",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SenderReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "NTPTimeStamp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "RTPTimeStamp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "packetCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "byteCount") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SenderReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_NTPTimeStamp
        "uint32_t",    // FIELD_RTPTimeStamp
        "uint32_t",    // FIELD_packetCount
        "uint32_t",    // FIELD_byteCount
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SenderReportDescriptor::getFieldPropertyNames(int field) const
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

const char *SenderReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SenderReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SenderReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SenderReport'", field);
    }
}

const char *SenderReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SenderReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        case FIELD_NTPTimeStamp: return uint642string(pp->getNTPTimeStamp());
        case FIELD_RTPTimeStamp: return ulong2string(pp->getRTPTimeStamp());
        case FIELD_packetCount: return ulong2string(pp->getPacketCount());
        case FIELD_byteCount: return ulong2string(pp->getByteCount());
        default: return "";
    }
}

void SenderReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        case FIELD_NTPTimeStamp: pp->setNTPTimeStamp(string2uint64(value)); break;
        case FIELD_RTPTimeStamp: pp->setRTPTimeStamp(string2ulong(value)); break;
        case FIELD_packetCount: pp->setPacketCount(string2ulong(value)); break;
        case FIELD_byteCount: pp->setByteCount(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderReport'", field);
    }
}

omnetpp::cValue SenderReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        case FIELD_NTPTimeStamp: return (omnetpp::intval_t)(pp->getNTPTimeStamp());
        case FIELD_RTPTimeStamp: return (omnetpp::intval_t)(pp->getRTPTimeStamp());
        case FIELD_packetCount: return (omnetpp::intval_t)(pp->getPacketCount());
        case FIELD_byteCount: return (omnetpp::intval_t)(pp->getByteCount());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SenderReport' as cValue -- field index out of range?", field);
    }
}

void SenderReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        case FIELD_NTPTimeStamp: pp->setNTPTimeStamp(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_RTPTimeStamp: pp->setRTPTimeStamp(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_packetCount: pp->setPacketCount(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_byteCount: pp->setByteCount(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderReport'", field);
    }
}

const char *SenderReportDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SenderReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SenderReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderReport *pp = omnetpp::fromAnyPtr<SenderReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderReport'", field);
    }
}

Register_Class(ReceptionReport)

ReceptionReport::ReceptionReport() : ::omnetpp::cObject()
{
}

ReceptionReport::ReceptionReport(const ReceptionReport& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

ReceptionReport::~ReceptionReport()
{
}

ReceptionReport& ReceptionReport::operator=(const ReceptionReport& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void ReceptionReport::copy(const ReceptionReport& other)
{
    this->ssrc = other.ssrc;
    this->fractionLost = other.fractionLost;
    this->packetsLostCumulative = other.packetsLostCumulative;
    this->sequenceNumber = other.sequenceNumber;
    this->jitter = other.jitter;
    this->lastSR = other.lastSR;
    this->delaySinceLastSR = other.delaySinceLastSR;
}

void ReceptionReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->ssrc);
    doParsimPacking(b,this->fractionLost);
    doParsimPacking(b,this->packetsLostCumulative);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->jitter);
    doParsimPacking(b,this->lastSR);
    doParsimPacking(b,this->delaySinceLastSR);
}

void ReceptionReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->ssrc);
    doParsimUnpacking(b,this->fractionLost);
    doParsimUnpacking(b,this->packetsLostCumulative);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->jitter);
    doParsimUnpacking(b,this->lastSR);
    doParsimUnpacking(b,this->delaySinceLastSR);
}

uint32_t ReceptionReport::getSsrc() const
{
    return this->ssrc;
}

void ReceptionReport::setSsrc(uint32_t ssrc)
{
    this->ssrc = ssrc;
}

uint8_t ReceptionReport::getFractionLost() const
{
    return this->fractionLost;
}

void ReceptionReport::setFractionLost(uint8_t fractionLost)
{
    this->fractionLost = fractionLost;
}

int ReceptionReport::getPacketsLostCumulative() const
{
    return this->packetsLostCumulative;
}

void ReceptionReport::setPacketsLostCumulative(int packetsLostCumulative)
{
    this->packetsLostCumulative = packetsLostCumulative;
}

uint32_t ReceptionReport::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void ReceptionReport::setSequenceNumber(uint32_t sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int ReceptionReport::getJitter() const
{
    return this->jitter;
}

void ReceptionReport::setJitter(int jitter)
{
    this->jitter = jitter;
}

int ReceptionReport::getLastSR() const
{
    return this->lastSR;
}

void ReceptionReport::setLastSR(int lastSR)
{
    this->lastSR = lastSR;
}

int ReceptionReport::getDelaySinceLastSR() const
{
    return this->delaySinceLastSR;
}

void ReceptionReport::setDelaySinceLastSR(int delaySinceLastSR)
{
    this->delaySinceLastSR = delaySinceLastSR;
}

class ReceptionReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssrc,
        FIELD_fractionLost,
        FIELD_packetsLostCumulative,
        FIELD_sequenceNumber,
        FIELD_jitter,
        FIELD_lastSR,
        FIELD_delaySinceLastSR,
    };
  public:
    ReceptionReportDescriptor();
    virtual ~ReceptionReportDescriptor();

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

Register_ClassDescriptor(ReceptionReportDescriptor)

ReceptionReportDescriptor::ReceptionReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::ReceptionReport)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

ReceptionReportDescriptor::~ReceptionReportDescriptor()
{
    delete[] propertyNames;
}

bool ReceptionReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ReceptionReport *>(obj)!=nullptr;
}

const char **ReceptionReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ReceptionReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ReceptionReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int ReceptionReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ssrc
        FD_ISEDITABLE,    // FIELD_fractionLost
        FD_ISEDITABLE,    // FIELD_packetsLostCumulative
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_jitter
        FD_ISEDITABLE,    // FIELD_lastSR
        FD_ISEDITABLE,    // FIELD_delaySinceLastSR
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ReceptionReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ssrc",
        "fractionLost",
        "packetsLostCumulative",
        "sequenceNumber",
        "jitter",
        "lastSR",
        "delaySinceLastSR",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ReceptionReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fractionLost") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "packetsLostCumulative") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "jitter") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lastSR") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "delaySinceLastSR") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *ReceptionReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ssrc
        "uint8_t",    // FIELD_fractionLost
        "int",    // FIELD_packetsLostCumulative
        "uint32_t",    // FIELD_sequenceNumber
        "int",    // FIELD_jitter
        "int",    // FIELD_lastSR
        "int",    // FIELD_delaySinceLastSR
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ReceptionReportDescriptor::getFieldPropertyNames(int field) const
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

const char *ReceptionReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ReceptionReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ReceptionReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ReceptionReport'", field);
    }
}

const char *ReceptionReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ReceptionReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        case FIELD_fractionLost: return ulong2string(pp->getFractionLost());
        case FIELD_packetsLostCumulative: return long2string(pp->getPacketsLostCumulative());
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_jitter: return long2string(pp->getJitter());
        case FIELD_lastSR: return long2string(pp->getLastSR());
        case FIELD_delaySinceLastSR: return long2string(pp->getDelaySinceLastSR());
        default: return "";
    }
}

void ReceptionReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        case FIELD_fractionLost: pp->setFractionLost(string2ulong(value)); break;
        case FIELD_packetsLostCumulative: pp->setPacketsLostCumulative(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        case FIELD_jitter: pp->setJitter(string2long(value)); break;
        case FIELD_lastSR: pp->setLastSR(string2long(value)); break;
        case FIELD_delaySinceLastSR: pp->setDelaySinceLastSR(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionReport'", field);
    }
}

omnetpp::cValue ReceptionReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        case FIELD_fractionLost: return (omnetpp::intval_t)(pp->getFractionLost());
        case FIELD_packetsLostCumulative: return pp->getPacketsLostCumulative();
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_jitter: return pp->getJitter();
        case FIELD_lastSR: return pp->getLastSR();
        case FIELD_delaySinceLastSR: return pp->getDelaySinceLastSR();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ReceptionReport' as cValue -- field index out of range?", field);
    }
}

void ReceptionReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_fractionLost: pp->setFractionLost(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_packetsLostCumulative: pp->setPacketsLostCumulative(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_jitter: pp->setJitter(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_lastSR: pp->setLastSR(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_delaySinceLastSR: pp->setDelaySinceLastSR(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionReport'", field);
    }
}

const char *ReceptionReportDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ReceptionReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ReceptionReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ReceptionReport *pp = omnetpp::fromAnyPtr<ReceptionReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ReceptionReport'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

