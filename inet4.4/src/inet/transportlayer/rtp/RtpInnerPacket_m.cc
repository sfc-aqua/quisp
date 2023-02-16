//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtpInnerPacket.msg.
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
#include "RtpInnerPacket_m.h"

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

Register_Enum(inet::rtp::RtpInpType, (inet::rtp::RtpInpType::RTP_INP_UNDEF, inet::rtp::RtpInpType::RTP_INP_INITIALIZE_PROFILE, inet::rtp::RtpInpType::RTP_INP_PROFILE_INITIALIZED, inet::rtp::RtpInpType::RTP_INP_INITIALIZE_RTCP, inet::rtp::RtpInpType::RTP_INP_RTCP_INITIALIZED, inet::rtp::RtpInpType::RTP_INP_CREATE_SENDER_MODULE, inet::rtp::RtpInpType::RTP_INP_SENDER_MODULE_CREATED, inet::rtp::RtpInpType::RTP_INP_DELETE_SENDER_MODULE, inet::rtp::RtpInpType::RTP_INP_SENDER_MODULE_DELETED, inet::rtp::RtpInpType::RTP_INP_INITIALIZE_SENDER_MODULE, inet::rtp::RtpInpType::RTP_INP_SENDER_MODULE_INITIALIZED, inet::rtp::RtpInpType::RTP_INP_SENDER_MODULE_CONTROL, inet::rtp::RtpInpType::RTP_INP_SENDER_MODULE_STATUS, inet::rtp::RtpInpType::RTP_INP_LEAVE_SESSION, inet::rtp::RtpInpType::RTP_INP_SESSION_LEFT, inet::rtp::RtpInpType::RTP_INP_DATA_OUT, inet::rtp::RtpInpType::RTP_INP_DATA_IN));

Register_Class(RtpInnerPacket)

RtpInnerPacket::RtpInnerPacket(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

RtpInnerPacket::RtpInnerPacket(const RtpInnerPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RtpInnerPacket::~RtpInnerPacket()
{
}

RtpInnerPacket& RtpInnerPacket::operator=(const RtpInnerPacket& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RtpInnerPacket::copy(const RtpInnerPacket& other)
{
    this->type = other.type;
    this->commonName = other.commonName;
    this->mtu = other.mtu;
    this->bandwidth = other.bandwidth;
    this->rtcpPercentage = other.rtcpPercentage;
    this->address = other.address;
    this->port = other.port;
    this->ssrc = other.ssrc;
    this->payloadType = other.payloadType;
    this->fileName = other.fileName;
    this->clockRate = other.clockRate;
    this->timeStampBase = other.timeStampBase;
    this->sequenceNumberBase = other.sequenceNumberBase;
}

void RtpInnerPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->commonName);
    doParsimPacking(b,this->mtu);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->rtcpPercentage);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->port);
    doParsimPacking(b,this->ssrc);
    doParsimPacking(b,this->payloadType);
    doParsimPacking(b,this->fileName);
    doParsimPacking(b,this->clockRate);
    doParsimPacking(b,this->timeStampBase);
    doParsimPacking(b,this->sequenceNumberBase);
}

void RtpInnerPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->commonName);
    doParsimUnpacking(b,this->mtu);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->rtcpPercentage);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->port);
    doParsimUnpacking(b,this->ssrc);
    doParsimUnpacking(b,this->payloadType);
    doParsimUnpacking(b,this->fileName);
    doParsimUnpacking(b,this->clockRate);
    doParsimUnpacking(b,this->timeStampBase);
    doParsimUnpacking(b,this->sequenceNumberBase);
}

RtpInpType RtpInnerPacket::getType() const
{
    return this->type;
}

void RtpInnerPacket::setType(RtpInpType type)
{
    this->type = type;
}

const char * RtpInnerPacket::getCommonName() const
{
    return this->commonName.c_str();
}

void RtpInnerPacket::setCommonName(const char * commonName)
{
    this->commonName = commonName;
}

int RtpInnerPacket::getMtu() const
{
    return this->mtu;
}

void RtpInnerPacket::setMtu(int mtu)
{
    this->mtu = mtu;
}

int RtpInnerPacket::getBandwidth() const
{
    return this->bandwidth;
}

void RtpInnerPacket::setBandwidth(int bandwidth)
{
    this->bandwidth = bandwidth;
}

int RtpInnerPacket::getRtcpPercentage() const
{
    return this->rtcpPercentage;
}

void RtpInnerPacket::setRtcpPercentage(int rtcpPercentage)
{
    this->rtcpPercentage = rtcpPercentage;
}

const ::inet::Ipv4Address& RtpInnerPacket::getAddress() const
{
    return this->address;
}

void RtpInnerPacket::setAddress(const ::inet::Ipv4Address& address)
{
    this->address = address;
}

int RtpInnerPacket::getPort() const
{
    return this->port;
}

void RtpInnerPacket::setPort(int port)
{
    this->port = port;
}

uint32_t RtpInnerPacket::getSsrc() const
{
    return this->ssrc;
}

void RtpInnerPacket::setSsrc(uint32_t ssrc)
{
    this->ssrc = ssrc;
}

int RtpInnerPacket::getPayloadType() const
{
    return this->payloadType;
}

void RtpInnerPacket::setPayloadType(int payloadType)
{
    this->payloadType = payloadType;
}

const char * RtpInnerPacket::getFileName() const
{
    return this->fileName.c_str();
}

void RtpInnerPacket::setFileName(const char * fileName)
{
    this->fileName = fileName;
}

int RtpInnerPacket::getClockRate() const
{
    return this->clockRate;
}

void RtpInnerPacket::setClockRate(int clockRate)
{
    this->clockRate = clockRate;
}

int RtpInnerPacket::getTimeStampBase() const
{
    return this->timeStampBase;
}

void RtpInnerPacket::setTimeStampBase(int timeStampBase)
{
    this->timeStampBase = timeStampBase;
}

int RtpInnerPacket::getSequenceNumberBase() const
{
    return this->sequenceNumberBase;
}

void RtpInnerPacket::setSequenceNumberBase(int sequenceNumberBase)
{
    this->sequenceNumberBase = sequenceNumberBase;
}

class RtpInnerPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_commonName,
        FIELD_mtu,
        FIELD_bandwidth,
        FIELD_rtcpPercentage,
        FIELD_address,
        FIELD_port,
        FIELD_ssrc,
        FIELD_payloadType,
        FIELD_fileName,
        FIELD_clockRate,
        FIELD_timeStampBase,
        FIELD_sequenceNumberBase,
    };
  public:
    RtpInnerPacketDescriptor();
    virtual ~RtpInnerPacketDescriptor();

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

Register_ClassDescriptor(RtpInnerPacketDescriptor)

RtpInnerPacketDescriptor::RtpInnerPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpInnerPacket)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

RtpInnerPacketDescriptor::~RtpInnerPacketDescriptor()
{
    delete[] propertyNames;
}

bool RtpInnerPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpInnerPacket *>(obj)!=nullptr;
}

const char **RtpInnerPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpInnerPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpInnerPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 13+base->getFieldCount() : 13;
}

unsigned int RtpInnerPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_commonName
        FD_ISEDITABLE,    // FIELD_mtu
        FD_ISEDITABLE,    // FIELD_bandwidth
        FD_ISEDITABLE,    // FIELD_rtcpPercentage
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_port
        FD_ISEDITABLE,    // FIELD_ssrc
        FD_ISEDITABLE,    // FIELD_payloadType
        FD_ISEDITABLE,    // FIELD_fileName
        FD_ISEDITABLE,    // FIELD_clockRate
        FD_ISEDITABLE,    // FIELD_timeStampBase
        FD_ISEDITABLE,    // FIELD_sequenceNumberBase
    };
    return (field >= 0 && field < 13) ? fieldTypeFlags[field] : 0;
}

const char *RtpInnerPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "commonName",
        "mtu",
        "bandwidth",
        "rtcpPercentage",
        "address",
        "port",
        "ssrc",
        "payloadType",
        "fileName",
        "clockRate",
        "timeStampBase",
        "sequenceNumberBase",
    };
    return (field >= 0 && field < 13) ? fieldNames[field] : nullptr;
}

int RtpInnerPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "commonName") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "mtu") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "rtcpPercentage") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "port") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "payloadType") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "fileName") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "clockRate") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "timeStampBase") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "sequenceNumberBase") == 0) return baseIndex + 12;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpInnerPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::rtp::RtpInpType",    // FIELD_type
        "string",    // FIELD_commonName
        "int",    // FIELD_mtu
        "int",    // FIELD_bandwidth
        "int",    // FIELD_rtcpPercentage
        "inet::Ipv4Address",    // FIELD_address
        "int",    // FIELD_port
        "uint32_t",    // FIELD_ssrc
        "int",    // FIELD_payloadType
        "string",    // FIELD_fileName
        "int",    // FIELD_clockRate
        "int",    // FIELD_timeStampBase
        "int",    // FIELD_sequenceNumberBase
    };
    return (field >= 0 && field < 13) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpInnerPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpInnerPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::rtp::RtpInpType";
            return nullptr;
        default: return nullptr;
    }
}

int RtpInnerPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpInnerPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpInnerPacket'", field);
    }
}

const char *RtpInnerPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpInnerPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::rtp::RtpInpType");
        case FIELD_commonName: return oppstring2string(pp->getCommonName());
        case FIELD_mtu: return long2string(pp->getMtu());
        case FIELD_bandwidth: return long2string(pp->getBandwidth());
        case FIELD_rtcpPercentage: return long2string(pp->getRtcpPercentage());
        case FIELD_address: return pp->getAddress().str();
        case FIELD_port: return long2string(pp->getPort());
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        case FIELD_payloadType: return long2string(pp->getPayloadType());
        case FIELD_fileName: return oppstring2string(pp->getFileName());
        case FIELD_clockRate: return long2string(pp->getClockRate());
        case FIELD_timeStampBase: return long2string(pp->getTimeStampBase());
        case FIELD_sequenceNumberBase: return long2string(pp->getSequenceNumberBase());
        default: return "";
    }
}

void RtpInnerPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: pp->setCommonName((value)); break;
        case FIELD_mtu: pp->setMtu(string2long(value)); break;
        case FIELD_bandwidth: pp->setBandwidth(string2long(value)); break;
        case FIELD_rtcpPercentage: pp->setRtcpPercentage(string2long(value)); break;
        case FIELD_port: pp->setPort(string2long(value)); break;
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        case FIELD_payloadType: pp->setPayloadType(string2long(value)); break;
        case FIELD_fileName: pp->setFileName((value)); break;
        case FIELD_clockRate: pp->setClockRate(string2long(value)); break;
        case FIELD_timeStampBase: pp->setTimeStampBase(string2long(value)); break;
        case FIELD_sequenceNumberBase: pp->setSequenceNumberBase(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpInnerPacket'", field);
    }
}

omnetpp::cValue RtpInnerPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_commonName: return pp->getCommonName();
        case FIELD_mtu: return pp->getMtu();
        case FIELD_bandwidth: return pp->getBandwidth();
        case FIELD_rtcpPercentage: return pp->getRtcpPercentage();
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_port: return pp->getPort();
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        case FIELD_payloadType: return pp->getPayloadType();
        case FIELD_fileName: return pp->getFileName();
        case FIELD_clockRate: return pp->getClockRate();
        case FIELD_timeStampBase: return pp->getTimeStampBase();
        case FIELD_sequenceNumberBase: return pp->getSequenceNumberBase();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpInnerPacket' as cValue -- field index out of range?", field);
    }
}

void RtpInnerPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: pp->setCommonName(value.stringValue()); break;
        case FIELD_mtu: pp->setMtu(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_bandwidth: pp->setBandwidth(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_rtcpPercentage: pp->setRtcpPercentage(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_port: pp->setPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_payloadType: pp->setPayloadType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fileName: pp->setFileName(value.stringValue()); break;
        case FIELD_clockRate: pp->setClockRate(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timeStampBase: pp->setTimeStampBase(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumberBase: pp->setSequenceNumberBase(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpInnerPacket'", field);
    }
}

const char *RtpInnerPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpInnerPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpInnerPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpInnerPacket *pp = omnetpp::fromAnyPtr<RtpInnerPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpInnerPacket'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

