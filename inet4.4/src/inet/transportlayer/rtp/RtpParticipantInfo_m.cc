//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtpParticipantInfo.msg.
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
#include "RtpParticipantInfo_m.h"

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

RtpParticipantInfo_Base::RtpParticipantInfo_Base(const char *name) : ::omnetpp::cNamedObject(name)
{
}

RtpParticipantInfo_Base::RtpParticipantInfo_Base(const RtpParticipantInfo_Base& other) : ::omnetpp::cNamedObject(other)
{
    copy(other);
}

RtpParticipantInfo_Base::~RtpParticipantInfo_Base()
{
}

RtpParticipantInfo_Base& RtpParticipantInfo_Base::operator=(const RtpParticipantInfo_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cNamedObject::operator=(other);
    copy(other);
    return *this;
}

void RtpParticipantInfo_Base::copy(const RtpParticipantInfo_Base& other)
{
    this->address = other.address;
    this->RTPPort = other.RTPPort;
    this->RTCPPort = other.RTCPPort;
}

void RtpParticipantInfo_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cNamedObject::parsimPack(b);
    // field ssrc is abstract or custom -- please do packing in customized class
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->RTPPort);
    doParsimPacking(b,this->RTCPPort);
}

void RtpParticipantInfo_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cNamedObject::parsimUnpack(b);
    // field ssrc is abstract or custom -- please do unpacking in customized class
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->RTPPort);
    doParsimUnpacking(b,this->RTCPPort);
}

const ::inet::Ipv4Address& RtpParticipantInfo_Base::getAddress() const
{
    return this->address;
}

void RtpParticipantInfo_Base::setAddress(const ::inet::Ipv4Address& address)
{
    this->address = address;
}

int RtpParticipantInfo_Base::getRTPPort() const
{
    return this->RTPPort;
}

void RtpParticipantInfo_Base::setRTPPort(int RTPPort)
{
    this->RTPPort = RTPPort;
}

int RtpParticipantInfo_Base::getRTCPPort() const
{
    return this->RTCPPort;
}

void RtpParticipantInfo_Base::setRTCPPort(int RTCPPort)
{
    this->RTCPPort = RTCPPort;
}

class RtpParticipantInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssrc,
        FIELD_address,
        FIELD_RTPPort,
        FIELD_RTCPPort,
    };
  public:
    RtpParticipantInfoDescriptor();
    virtual ~RtpParticipantInfoDescriptor();

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

Register_ClassDescriptor(RtpParticipantInfoDescriptor)

RtpParticipantInfoDescriptor::RtpParticipantInfoDescriptor() : omnetpp::cClassDescriptor("inet::rtp::RtpParticipantInfo", "omnetpp::cNamedObject")
{
    propertyNames = nullptr;
}

RtpParticipantInfoDescriptor::~RtpParticipantInfoDescriptor()
{
    delete[] propertyNames;
}

bool RtpParticipantInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpParticipantInfo_Base *>(obj)!=nullptr;
}

const char **RtpParticipantInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpParticipantInfoDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpParticipantInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int RtpParticipantInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ssrc
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_RTPPort
        FD_ISEDITABLE,    // FIELD_RTCPPort
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *RtpParticipantInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ssrc",
        "address",
        "RTPPort",
        "RTCPPort",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int RtpParticipantInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "RTPPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "RTCPPort") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpParticipantInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_ssrc
        "inet::Ipv4Address",    // FIELD_address
        "int",    // FIELD_RTPPort
        "int",    // FIELD_RTCPPort
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpParticipantInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpParticipantInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpParticipantInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpParticipantInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpParticipantInfo_Base'", field);
    }
}

const char *RtpParticipantInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpParticipantInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        case FIELD_address: return pp->getAddress().str();
        case FIELD_RTPPort: return long2string(pp->getRTPPort());
        case FIELD_RTCPPort: return long2string(pp->getRTCPPort());
        default: return "";
    }
}

void RtpParticipantInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        case FIELD_RTPPort: pp->setRTPPort(string2long(value)); break;
        case FIELD_RTCPPort: pp->setRTCPPort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpParticipantInfo_Base'", field);
    }
}

omnetpp::cValue RtpParticipantInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_RTPPort: return pp->getRTPPort();
        case FIELD_RTCPPort: return pp->getRTCPPort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpParticipantInfo_Base' as cValue -- field index out of range?", field);
    }
}

void RtpParticipantInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_RTPPort: pp->setRTPPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_RTCPPort: pp->setRTCPPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpParticipantInfo_Base'", field);
    }
}

const char *RtpParticipantInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpParticipantInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpParticipantInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpParticipantInfo_Base *pp = omnetpp::fromAnyPtr<RtpParticipantInfo_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpParticipantInfo_Base'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

