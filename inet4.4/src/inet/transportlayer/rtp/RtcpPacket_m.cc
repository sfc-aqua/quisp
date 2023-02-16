//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtcpPacket.msg.
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
#include "RtcpPacket_m.h"

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
namespace rtp {

Register_Enum(inet::rtp::RtcpPacketType, (inet::rtp::RtcpPacketType::RTCP_PT_UNDEF, inet::rtp::RtcpPacketType::RTCP_PT_SR, inet::rtp::RtcpPacketType::RTCP_PT_RR, inet::rtp::RtcpPacketType::RTCP_PT_SDES, inet::rtp::RtcpPacketType::RTCP_PT_BYE));

Register_Class(RtcpPacket)

RtcpPacket::RtcpPacket() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

RtcpPacket::RtcpPacket(const RtcpPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

RtcpPacket::~RtcpPacket()
{
}

RtcpPacket& RtcpPacket::operator=(const RtcpPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void RtcpPacket::copy(const RtcpPacket& other)
{
    this->version = other.version;
    this->padding = other.padding;
    this->count = other.count;
    this->packetType = other.packetType;
    this->rtcpLength = other.rtcpLength;
}

void RtcpPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->padding);
    doParsimPacking(b,this->count);
    doParsimPacking(b,this->packetType);
    doParsimPacking(b,this->rtcpLength);
}

void RtcpPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->padding);
    doParsimUnpacking(b,this->count);
    doParsimUnpacking(b,this->packetType);
    doParsimUnpacking(b,this->rtcpLength);
}

int8_t RtcpPacket::getVersion() const
{
    return this->version;
}

void RtcpPacket::setVersion(int8_t version)
{
    handleChange();
    this->version = version;
}

bool RtcpPacket::getPadding() const
{
    return this->padding;
}

void RtcpPacket::setPadding(bool padding)
{
    handleChange();
    this->padding = padding;
}

short RtcpPacket::getCount() const
{
    return this->count;
}

void RtcpPacket::setCount(short count)
{
    handleChange();
    this->count = count;
}

RtcpPacketType RtcpPacket::getPacketType() const
{
    return this->packetType;
}

void RtcpPacket::setPacketType(RtcpPacketType packetType)
{
    handleChange();
    this->packetType = packetType;
}

int RtcpPacket::getRtcpLength() const
{
    return this->rtcpLength;
}

void RtcpPacket::setRtcpLength(int rtcpLength)
{
    handleChange();
    this->rtcpLength = rtcpLength;
}

class RtcpPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_padding,
        FIELD_count,
        FIELD_packetType,
        FIELD_rtcpLength,
    };
  public:
    RtcpPacketDescriptor();
    virtual ~RtcpPacketDescriptor();

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

Register_ClassDescriptor(RtcpPacketDescriptor)

RtcpPacketDescriptor::RtcpPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtcpPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

RtcpPacketDescriptor::~RtcpPacketDescriptor()
{
    delete[] propertyNames;
}

bool RtcpPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtcpPacket *>(obj)!=nullptr;
}

const char **RtcpPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtcpPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtcpPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RtcpPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        FD_ISEDITABLE,    // FIELD_padding
        FD_ISEDITABLE,    // FIELD_count
        0,    // FIELD_packetType
        FD_ISEDITABLE,    // FIELD_rtcpLength
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RtcpPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "padding",
        "count",
        "packetType",
        "rtcpLength",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RtcpPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "padding") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "count") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "packetType") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "rtcpLength") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RtcpPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int8_t",    // FIELD_version
        "bool",    // FIELD_padding
        "short",    // FIELD_count
        "inet::rtp::RtcpPacketType",    // FIELD_packetType
        "int",    // FIELD_rtcpLength
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RtcpPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RtcpPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_packetType:
            if (!strcmp(propertyName, "enum")) return "inet::rtp::RtcpPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int RtcpPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtcpPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtcpPacket'", field);
    }
}

const char *RtcpPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtcpPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: return long2string(pp->getVersion());
        case FIELD_padding: return bool2string(pp->getPadding());
        case FIELD_count: return long2string(pp->getCount());
        case FIELD_packetType: return enum2string(pp->getPacketType(), "inet::rtp::RtcpPacketType");
        case FIELD_rtcpLength: return long2string(pp->getRtcpLength());
        default: return "";
    }
}

void RtcpPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2long(value)); break;
        case FIELD_padding: pp->setPadding(string2bool(value)); break;
        case FIELD_count: pp->setCount(string2long(value)); break;
        case FIELD_rtcpLength: pp->setRtcpLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpPacket'", field);
    }
}

omnetpp::cValue RtcpPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: return pp->getVersion();
        case FIELD_padding: return pp->getPadding();
        case FIELD_count: return pp->getCount();
        case FIELD_packetType: return static_cast<int>(pp->getPacketType());
        case FIELD_rtcpLength: return pp->getRtcpLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtcpPacket' as cValue -- field index out of range?", field);
    }
}

void RtcpPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<int8_t>(value.intValue())); break;
        case FIELD_padding: pp->setPadding(value.boolValue()); break;
        case FIELD_count: pp->setCount(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_rtcpLength: pp->setRtcpLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpPacket'", field);
    }
}

const char *RtcpPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtcpPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtcpPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpPacket *pp = omnetpp::fromAnyPtr<RtcpPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpPacket'", field);
    }
}

Register_Class(RtcpReceiverReportPacket)

RtcpReceiverReportPacket::RtcpReceiverReportPacket() : ::inet::rtp::RtcpPacket()
{
    this->setPacketType(RTCP_PT_RR);
    this->setChunkLength(getChunkLength() + B(4));

    take(&this->receptionReports);
}

RtcpReceiverReportPacket::RtcpReceiverReportPacket(const RtcpReceiverReportPacket& other) : ::inet::rtp::RtcpPacket(other)
{
    take(&this->receptionReports);
    copy(other);
}

RtcpReceiverReportPacket::~RtcpReceiverReportPacket()
{
    drop(&this->receptionReports);
}

RtcpReceiverReportPacket& RtcpReceiverReportPacket::operator=(const RtcpReceiverReportPacket& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtcpPacket::operator=(other);
    copy(other);
    return *this;
}

void RtcpReceiverReportPacket::copy(const RtcpReceiverReportPacket& other)
{
    this->ssrc = other.ssrc;
    this->receptionReports = other.receptionReports;
    this->receptionReports.setName(other.receptionReports.getName());
}

void RtcpReceiverReportPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtcpPacket::parsimPack(b);
    doParsimPacking(b,this->ssrc);
    doParsimPacking(b,this->receptionReports);
}

void RtcpReceiverReportPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtcpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->ssrc);
    doParsimUnpacking(b,this->receptionReports);
}

uint32_t RtcpReceiverReportPacket::getSsrc() const
{
    return this->ssrc;
}

void RtcpReceiverReportPacket::setSsrc(uint32_t ssrc)
{
    handleChange();
    this->ssrc = ssrc;
}

const ::omnetpp::cArray& RtcpReceiverReportPacket::getReceptionReports() const
{
    return this->receptionReports;
}

void RtcpReceiverReportPacket::setReceptionReports(const ::omnetpp::cArray& receptionReports)
{
    handleChange();
    this->receptionReports = receptionReports;
}

class RtcpReceiverReportPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssrc,
        FIELD_receptionReports,
    };
  public:
    RtcpReceiverReportPacketDescriptor();
    virtual ~RtcpReceiverReportPacketDescriptor();

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

Register_ClassDescriptor(RtcpReceiverReportPacketDescriptor)

RtcpReceiverReportPacketDescriptor::RtcpReceiverReportPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtcpReceiverReportPacket)), "inet::rtp::RtcpPacket")
{
    propertyNames = nullptr;
}

RtcpReceiverReportPacketDescriptor::~RtcpReceiverReportPacketDescriptor()
{
    delete[] propertyNames;
}

bool RtcpReceiverReportPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtcpReceiverReportPacket *>(obj)!=nullptr;
}

const char **RtcpReceiverReportPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtcpReceiverReportPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtcpReceiverReportPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RtcpReceiverReportPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ssrc
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_receptionReports
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RtcpReceiverReportPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ssrc",
        "receptionReports",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RtcpReceiverReportPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "receptionReports") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RtcpReceiverReportPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ssrc
        "omnetpp::cArray",    // FIELD_receptionReports
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RtcpReceiverReportPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *RtcpReceiverReportPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtcpReceiverReportPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtcpReceiverReportPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtcpReceiverReportPacket'", field);
    }
}

const char *RtcpReceiverReportPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtcpReceiverReportPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        case FIELD_receptionReports: return pp->getReceptionReports().str();
        default: return "";
    }
}

void RtcpReceiverReportPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpReceiverReportPacket'", field);
    }
}

omnetpp::cValue RtcpReceiverReportPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        case FIELD_receptionReports: return omnetpp::toAnyPtr(&pp->getReceptionReports()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtcpReceiverReportPacket' as cValue -- field index out of range?", field);
    }
}

void RtcpReceiverReportPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpReceiverReportPacket'", field);
    }
}

const char *RtcpReceiverReportPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_receptionReports: return omnetpp::opp_typename(typeid(::omnetpp::cArray));
        default: return nullptr;
    };
}

omnetpp::any_ptr RtcpReceiverReportPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_receptionReports: return omnetpp::toAnyPtr(&pp->getReceptionReports()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtcpReceiverReportPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpReceiverReportPacket *pp = omnetpp::fromAnyPtr<RtcpReceiverReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpReceiverReportPacket'", field);
    }
}

Register_Class(RtcpSdesPacket)

RtcpSdesPacket::RtcpSdesPacket() : ::inet::rtp::RtcpPacket()
{
    this->setPacketType(RTCP_PT_SDES);

    take(&this->sdesChunks);
}

RtcpSdesPacket::RtcpSdesPacket(const RtcpSdesPacket& other) : ::inet::rtp::RtcpPacket(other)
{
    take(&this->sdesChunks);
    copy(other);
}

RtcpSdesPacket::~RtcpSdesPacket()
{
    drop(&this->sdesChunks);
}

RtcpSdesPacket& RtcpSdesPacket::operator=(const RtcpSdesPacket& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtcpPacket::operator=(other);
    copy(other);
    return *this;
}

void RtcpSdesPacket::copy(const RtcpSdesPacket& other)
{
    this->sdesChunks = other.sdesChunks;
    this->sdesChunks.setName(other.sdesChunks.getName());
}

void RtcpSdesPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtcpPacket::parsimPack(b);
    doParsimPacking(b,this->sdesChunks);
}

void RtcpSdesPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtcpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sdesChunks);
}

const ::omnetpp::cArray& RtcpSdesPacket::getSdesChunks() const
{
    return this->sdesChunks;
}

void RtcpSdesPacket::setSdesChunks(const ::omnetpp::cArray& sdesChunks)
{
    handleChange();
    this->sdesChunks = sdesChunks;
}

class RtcpSdesPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sdesChunks,
    };
  public:
    RtcpSdesPacketDescriptor();
    virtual ~RtcpSdesPacketDescriptor();

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

Register_ClassDescriptor(RtcpSdesPacketDescriptor)

RtcpSdesPacketDescriptor::RtcpSdesPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtcpSdesPacket)), "inet::rtp::RtcpPacket")
{
    propertyNames = nullptr;
}

RtcpSdesPacketDescriptor::~RtcpSdesPacketDescriptor()
{
    delete[] propertyNames;
}

bool RtcpSdesPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtcpSdesPacket *>(obj)!=nullptr;
}

const char **RtcpSdesPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtcpSdesPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtcpSdesPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RtcpSdesPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_sdesChunks
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RtcpSdesPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sdesChunks",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RtcpSdesPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sdesChunks") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RtcpSdesPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::cArray",    // FIELD_sdesChunks
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RtcpSdesPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *RtcpSdesPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtcpSdesPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtcpSdesPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtcpSdesPacket'", field);
    }
}

const char *RtcpSdesPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtcpSdesPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sdesChunks: return pp->getSdesChunks().str();
        default: return "";
    }
}

void RtcpSdesPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSdesPacket'", field);
    }
}

omnetpp::cValue RtcpSdesPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sdesChunks: return omnetpp::toAnyPtr(&pp->getSdesChunks()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtcpSdesPacket' as cValue -- field index out of range?", field);
    }
}

void RtcpSdesPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSdesPacket'", field);
    }
}

const char *RtcpSdesPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sdesChunks: return omnetpp::opp_typename(typeid(::omnetpp::cArray));
        default: return nullptr;
    };
}

omnetpp::any_ptr RtcpSdesPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sdesChunks: return omnetpp::toAnyPtr(&pp->getSdesChunks()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtcpSdesPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSdesPacket *pp = omnetpp::fromAnyPtr<RtcpSdesPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSdesPacket'", field);
    }
}

Register_Class(RtcpByePacket)

RtcpByePacket::RtcpByePacket() : ::inet::rtp::RtcpPacket()
{
    this->setPacketType(RTCP_PT_BYE);
    this->setChunkLength(getChunkLength() + B(4));
    this->setCount(1);

}

RtcpByePacket::RtcpByePacket(const RtcpByePacket& other) : ::inet::rtp::RtcpPacket(other)
{
    copy(other);
}

RtcpByePacket::~RtcpByePacket()
{
}

RtcpByePacket& RtcpByePacket::operator=(const RtcpByePacket& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtcpPacket::operator=(other);
    copy(other);
    return *this;
}

void RtcpByePacket::copy(const RtcpByePacket& other)
{
    this->ssrc = other.ssrc;
}

void RtcpByePacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtcpPacket::parsimPack(b);
    doParsimPacking(b,this->ssrc);
}

void RtcpByePacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtcpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->ssrc);
}

uint32_t RtcpByePacket::getSsrc() const
{
    return this->ssrc;
}

void RtcpByePacket::setSsrc(uint32_t ssrc)
{
    handleChange();
    this->ssrc = ssrc;
}

class RtcpByePacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssrc,
    };
  public:
    RtcpByePacketDescriptor();
    virtual ~RtcpByePacketDescriptor();

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

Register_ClassDescriptor(RtcpByePacketDescriptor)

RtcpByePacketDescriptor::RtcpByePacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtcpByePacket)), "inet::rtp::RtcpPacket")
{
    propertyNames = nullptr;
}

RtcpByePacketDescriptor::~RtcpByePacketDescriptor()
{
    delete[] propertyNames;
}

bool RtcpByePacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtcpByePacket *>(obj)!=nullptr;
}

const char **RtcpByePacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtcpByePacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtcpByePacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RtcpByePacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ssrc
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RtcpByePacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ssrc",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RtcpByePacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RtcpByePacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ssrc
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RtcpByePacketDescriptor::getFieldPropertyNames(int field) const
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

const char *RtcpByePacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtcpByePacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtcpByePacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtcpByePacket'", field);
    }
}

const char *RtcpByePacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtcpByePacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        default: return "";
    }
}

void RtcpByePacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpByePacket'", field);
    }
}

omnetpp::cValue RtcpByePacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtcpByePacket' as cValue -- field index out of range?", field);
    }
}

void RtcpByePacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpByePacket'", field);
    }
}

const char *RtcpByePacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtcpByePacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtcpByePacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpByePacket *pp = omnetpp::fromAnyPtr<RtcpByePacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpByePacket'", field);
    }
}

Register_Class(RtcpSenderReportPacket)

RtcpSenderReportPacket::RtcpSenderReportPacket() : ::inet::rtp::RtcpReceiverReportPacket()
{
    this->setPacketType(RTCP_PT_SR);
    this->setChunkLength(getChunkLength() + B(20));

}

RtcpSenderReportPacket::RtcpSenderReportPacket(const RtcpSenderReportPacket& other) : ::inet::rtp::RtcpReceiverReportPacket(other)
{
    copy(other);
}

RtcpSenderReportPacket::~RtcpSenderReportPacket()
{
}

RtcpSenderReportPacket& RtcpSenderReportPacket::operator=(const RtcpSenderReportPacket& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtcpReceiverReportPacket::operator=(other);
    copy(other);
    return *this;
}

void RtcpSenderReportPacket::copy(const RtcpSenderReportPacket& other)
{
    this->senderReport = other.senderReport;
}

void RtcpSenderReportPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtcpReceiverReportPacket::parsimPack(b);
    doParsimPacking(b,this->senderReport);
}

void RtcpSenderReportPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtcpReceiverReportPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->senderReport);
}

const SenderReport& RtcpSenderReportPacket::getSenderReport() const
{
    return this->senderReport;
}

void RtcpSenderReportPacket::setSenderReport(const SenderReport& senderReport)
{
    handleChange();
    this->senderReport = senderReport;
}

class RtcpSenderReportPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderReport,
    };
  public:
    RtcpSenderReportPacketDescriptor();
    virtual ~RtcpSenderReportPacketDescriptor();

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

Register_ClassDescriptor(RtcpSenderReportPacketDescriptor)

RtcpSenderReportPacketDescriptor::RtcpSenderReportPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtcpSenderReportPacket)), "inet::rtp::RtcpReceiverReportPacket")
{
    propertyNames = nullptr;
}

RtcpSenderReportPacketDescriptor::~RtcpSenderReportPacketDescriptor()
{
    delete[] propertyNames;
}

bool RtcpSenderReportPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtcpSenderReportPacket *>(obj)!=nullptr;
}

const char **RtcpSenderReportPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtcpSenderReportPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtcpSenderReportPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RtcpSenderReportPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_senderReport
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RtcpSenderReportPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderReport",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RtcpSenderReportPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderReport") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RtcpSenderReportPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::rtp::SenderReport",    // FIELD_senderReport
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RtcpSenderReportPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *RtcpSenderReportPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtcpSenderReportPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtcpSenderReportPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtcpSenderReportPacket'", field);
    }
}

const char *RtcpSenderReportPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtcpSenderReportPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_senderReport: return pp->getSenderReport().str();
        default: return "";
    }
}

void RtcpSenderReportPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSenderReportPacket'", field);
    }
}

omnetpp::cValue RtcpSenderReportPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_senderReport: return omnetpp::toAnyPtr(&pp->getSenderReport()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtcpSenderReportPacket' as cValue -- field index out of range?", field);
    }
}

void RtcpSenderReportPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSenderReportPacket'", field);
    }
}

const char *RtcpSenderReportPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_senderReport: return omnetpp::opp_typename(typeid(SenderReport));
        default: return nullptr;
    };
}

omnetpp::any_ptr RtcpSenderReportPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        case FIELD_senderReport: return omnetpp::toAnyPtr(&pp->getSenderReport()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtcpSenderReportPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtcpSenderReportPacket *pp = omnetpp::fromAnyPtr<RtcpSenderReportPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtcpSenderReportPacket'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

