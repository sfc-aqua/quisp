//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee8021as/GptpPacket.msg.
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
#include "GptpPacket_m.h"

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

Register_Enum(inet::GptpNodeType, (inet::GptpNodeType::MASTER_NODE, inet::GptpNodeType::BRIDGE_NODE, inet::GptpNodeType::SLAVE_NODE));

Register_Enum(inet::GptpPortType, (inet::GptpPortType::MASTER_PORT, inet::GptpPortType::SLAVE_PORT, inet::GptpPortType::PASSIVE_PORT));

Register_Enum(inet::GptpMessageType, (inet::GptpMessageType::GPTPTYPE_SYNC, inet::GptpMessageType::GPTPTYPE_FOLLOW_UP, inet::GptpMessageType::GPTPTYPE_PDELAY_REQ, inet::GptpMessageType::GPTPTYPE_PDELAY_RESP, inet::GptpMessageType::GPTPTYPE_PDELAY_RESP_FOLLOW_UP));

Register_Enum(inet::GptpSelfMsgKind, (inet::GptpSelfMsgKind::GPTP_SELF_REQ_ANSWER_KIND, inet::GptpSelfMsgKind::GPTP_SELF_MSG_SYNC, inet::GptpSelfMsgKind::GPTP_REQUEST_TO_SEND_SYNC, inet::GptpSelfMsgKind::GPTP_SELF_MSG_PDELAY_REQ));

Register_Enum(inet::GptpFlags, (inet::GptpFlags::alternateMasterFlag, inet::GptpFlags::twoStepFlag));

Register_Enum(inet::GptpTlvType, (inet::GptpTlvType::GPTP_FOLLOW_UP_INFORMATION_TLV));

PortIdentity::PortIdentity()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const PortIdentity& a)
{
    doParsimPacking(b,a.clockIdentity);
    doParsimPacking(b,a.portNumber);
}

void __doUnpacking(omnetpp::cCommBuffer *b, PortIdentity& a)
{
    doParsimUnpacking(b,a.clockIdentity);
    doParsimUnpacking(b,a.portNumber);
}

class PortIdentityDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clockIdentity,
        FIELD_portNumber,
    };
  public:
    PortIdentityDescriptor();
    virtual ~PortIdentityDescriptor();

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

Register_ClassDescriptor(PortIdentityDescriptor)

PortIdentityDescriptor::PortIdentityDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PortIdentity)), "")
{
    propertyNames = nullptr;
}

PortIdentityDescriptor::~PortIdentityDescriptor()
{
    delete[] propertyNames;
}

bool PortIdentityDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PortIdentity *>(obj)!=nullptr;
}

const char **PortIdentityDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PortIdentityDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PortIdentityDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int PortIdentityDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clockIdentity
        FD_ISEDITABLE,    // FIELD_portNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *PortIdentityDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clockIdentity",
        "portNumber",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int PortIdentityDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clockIdentity") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "portNumber") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *PortIdentityDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint64_t",    // FIELD_clockIdentity
        "uint16_t",    // FIELD_portNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **PortIdentityDescriptor::getFieldPropertyNames(int field) const
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

const char *PortIdentityDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PortIdentityDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PortIdentityDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PortIdentity'", field);
    }
}

const char *PortIdentityDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PortIdentityDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        case FIELD_clockIdentity: return uint642string(pp->clockIdentity);
        case FIELD_portNumber: return ulong2string(pp->portNumber);
        default: return "";
    }
}

void PortIdentityDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        case FIELD_clockIdentity: pp->clockIdentity = string2uint64(value); break;
        case FIELD_portNumber: pp->portNumber = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PortIdentity'", field);
    }
}

omnetpp::cValue PortIdentityDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        case FIELD_clockIdentity: return (omnetpp::intval_t)(pp->clockIdentity);
        case FIELD_portNumber: return (omnetpp::intval_t)(pp->portNumber);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PortIdentity' as cValue -- field index out of range?", field);
    }
}

void PortIdentityDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        case FIELD_clockIdentity: pp->clockIdentity = omnetpp::checked_int_cast<uint64_t>(value.intValue()); break;
        case FIELD_portNumber: pp->portNumber = omnetpp::checked_int_cast<uint16_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PortIdentity'", field);
    }
}

const char *PortIdentityDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PortIdentityDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PortIdentityDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PortIdentity *pp = omnetpp::fromAnyPtr<PortIdentity>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PortIdentity'", field);
    }
}

Register_Class(GptpReqAnswerEvent)

GptpReqAnswerEvent::GptpReqAnswerEvent(const char *name, short kind) : ::inet::ClockEvent(name, kind)
{
}

GptpReqAnswerEvent::GptpReqAnswerEvent(const GptpReqAnswerEvent& other) : ::inet::ClockEvent(other)
{
    copy(other);
}

GptpReqAnswerEvent::~GptpReqAnswerEvent()
{
}

GptpReqAnswerEvent& GptpReqAnswerEvent::operator=(const GptpReqAnswerEvent& other)
{
    if (this == &other) return *this;
    ::inet::ClockEvent::operator=(other);
    copy(other);
    return *this;
}

void GptpReqAnswerEvent::copy(const GptpReqAnswerEvent& other)
{
    this->portId = other.portId;
    this->ingressTimestamp = other.ingressTimestamp;
    this->sourcePortIdentity = other.sourcePortIdentity;
    this->sequenceId = other.sequenceId;
}

void GptpReqAnswerEvent::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ClockEvent::parsimPack(b);
    doParsimPacking(b,this->portId);
    doParsimPacking(b,this->ingressTimestamp);
    doParsimPacking(b,this->sourcePortIdentity);
    doParsimPacking(b,this->sequenceId);
}

void GptpReqAnswerEvent::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ClockEvent::parsimUnpack(b);
    doParsimUnpacking(b,this->portId);
    doParsimUnpacking(b,this->ingressTimestamp);
    doParsimUnpacking(b,this->sourcePortIdentity);
    doParsimUnpacking(b,this->sequenceId);
}

int GptpReqAnswerEvent::getPortId() const
{
    return this->portId;
}

void GptpReqAnswerEvent::setPortId(int portId)
{
    this->portId = portId;
}

clocktime_t GptpReqAnswerEvent::getIngressTimestamp() const
{
    return this->ingressTimestamp;
}

void GptpReqAnswerEvent::setIngressTimestamp(clocktime_t ingressTimestamp)
{
    this->ingressTimestamp = ingressTimestamp;
}

const PortIdentity& GptpReqAnswerEvent::getSourcePortIdentity() const
{
    return this->sourcePortIdentity;
}

void GptpReqAnswerEvent::setSourcePortIdentity(const PortIdentity& sourcePortIdentity)
{
    this->sourcePortIdentity = sourcePortIdentity;
}

uint16_t GptpReqAnswerEvent::getSequenceId() const
{
    return this->sequenceId;
}

void GptpReqAnswerEvent::setSequenceId(uint16_t sequenceId)
{
    this->sequenceId = sequenceId;
}

class GptpReqAnswerEventDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_portId,
        FIELD_ingressTimestamp,
        FIELD_sourcePortIdentity,
        FIELD_sequenceId,
    };
  public:
    GptpReqAnswerEventDescriptor();
    virtual ~GptpReqAnswerEventDescriptor();

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

Register_ClassDescriptor(GptpReqAnswerEventDescriptor)

GptpReqAnswerEventDescriptor::GptpReqAnswerEventDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpReqAnswerEvent)), "inet::ClockEvent")
{
    propertyNames = nullptr;
}

GptpReqAnswerEventDescriptor::~GptpReqAnswerEventDescriptor()
{
    delete[] propertyNames;
}

bool GptpReqAnswerEventDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpReqAnswerEvent *>(obj)!=nullptr;
}

const char **GptpReqAnswerEventDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpReqAnswerEventDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpReqAnswerEventDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int GptpReqAnswerEventDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_portId
        0,    // FIELD_ingressTimestamp
        FD_ISCOMPOUND,    // FIELD_sourcePortIdentity
        FD_ISEDITABLE,    // FIELD_sequenceId
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *GptpReqAnswerEventDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "portId",
        "ingressTimestamp",
        "sourcePortIdentity",
        "sequenceId",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int GptpReqAnswerEventDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "portId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ingressTimestamp") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourcePortIdentity") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sequenceId") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpReqAnswerEventDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_portId
        "inet::clocktime_t",    // FIELD_ingressTimestamp
        "inet::PortIdentity",    // FIELD_sourcePortIdentity
        "uint16_t",    // FIELD_sequenceId
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpReqAnswerEventDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpReqAnswerEventDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpReqAnswerEventDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpReqAnswerEventDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpReqAnswerEvent'", field);
    }
}

const char *GptpReqAnswerEventDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpReqAnswerEventDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        case FIELD_portId: return long2string(pp->getPortId());
        case FIELD_ingressTimestamp: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getIngressTimestamp()));
        case FIELD_sourcePortIdentity: return "";
        case FIELD_sequenceId: return ulong2string(pp->getSequenceId());
        default: return "";
    }
}

void GptpReqAnswerEventDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        case FIELD_portId: pp->setPortId(string2long(value)); break;
        case FIELD_sequenceId: pp->setSequenceId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpReqAnswerEvent'", field);
    }
}

omnetpp::cValue GptpReqAnswerEventDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        case FIELD_portId: return pp->getPortId();
        case FIELD_ingressTimestamp: return cValue(pp->getIngressTimestamp().dbl(),"s");
        case FIELD_sourcePortIdentity: return omnetpp::toAnyPtr(&pp->getSourcePortIdentity()); break;
        case FIELD_sequenceId: return (omnetpp::intval_t)(pp->getSequenceId());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpReqAnswerEvent' as cValue -- field index out of range?", field);
    }
}

void GptpReqAnswerEventDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        case FIELD_portId: pp->setPortId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceId: pp->setSequenceId(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpReqAnswerEvent'", field);
    }
}

const char *GptpReqAnswerEventDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sourcePortIdentity: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

omnetpp::any_ptr GptpReqAnswerEventDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        case FIELD_sourcePortIdentity: return omnetpp::toAnyPtr(&pp->getSourcePortIdentity()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpReqAnswerEventDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpReqAnswerEvent *pp = omnetpp::fromAnyPtr<GptpReqAnswerEvent>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpReqAnswerEvent'", field);
    }
}

Register_Class(GptpBase)

GptpBase::GptpBase() : ::inet::FieldsChunk()
{
}

GptpBase::GptpBase(const GptpBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

GptpBase::~GptpBase()
{
}

GptpBase& GptpBase::operator=(const GptpBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void GptpBase::copy(const GptpBase& other)
{
    this->majorSdoId = other.majorSdoId;
    this->messageType = other.messageType;
    this->minorVersionPTP = other.minorVersionPTP;
    this->versionPTP = other.versionPTP;
    this->messageLengthField = other.messageLengthField;
    this->domainNumber = other.domainNumber;
    this->minorSdoId = other.minorSdoId;
    this->flags = other.flags;
    this->correctionField = other.correctionField;
    this->messageTypeSpecific = other.messageTypeSpecific;
    this->sourcePortIdentity = other.sourcePortIdentity;
    this->sequenceId = other.sequenceId;
    this->controlField = other.controlField;
    this->logMessageInterval = other.logMessageInterval;
}

void GptpBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->majorSdoId);
    doParsimPacking(b,this->messageType);
    doParsimPacking(b,this->minorVersionPTP);
    doParsimPacking(b,this->versionPTP);
    doParsimPacking(b,this->messageLengthField);
    doParsimPacking(b,this->domainNumber);
    doParsimPacking(b,this->minorSdoId);
    doParsimPacking(b,this->flags);
    doParsimPacking(b,this->correctionField);
    doParsimPacking(b,this->messageTypeSpecific);
    doParsimPacking(b,this->sourcePortIdentity);
    doParsimPacking(b,this->sequenceId);
    doParsimPacking(b,this->controlField);
    doParsimPacking(b,this->logMessageInterval);
}

void GptpBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->majorSdoId);
    doParsimUnpacking(b,this->messageType);
    doParsimUnpacking(b,this->minorVersionPTP);
    doParsimUnpacking(b,this->versionPTP);
    doParsimUnpacking(b,this->messageLengthField);
    doParsimUnpacking(b,this->domainNumber);
    doParsimUnpacking(b,this->minorSdoId);
    doParsimUnpacking(b,this->flags);
    doParsimUnpacking(b,this->correctionField);
    doParsimUnpacking(b,this->messageTypeSpecific);
    doParsimUnpacking(b,this->sourcePortIdentity);
    doParsimUnpacking(b,this->sequenceId);
    doParsimUnpacking(b,this->controlField);
    doParsimUnpacking(b,this->logMessageInterval);
}

uint8_t GptpBase::getMajorSdoId() const
{
    return this->majorSdoId;
}

void GptpBase::setMajorSdoId(uint8_t majorSdoId)
{
    handleChange();
    this->majorSdoId = majorSdoId;
}

GptpMessageType GptpBase::getMessageType() const
{
    return this->messageType;
}

void GptpBase::setMessageType(GptpMessageType messageType)
{
    handleChange();
    this->messageType = messageType;
}

uint8_t GptpBase::getMinorVersionPTP() const
{
    return this->minorVersionPTP;
}

void GptpBase::setMinorVersionPTP(uint8_t minorVersionPTP)
{
    handleChange();
    this->minorVersionPTP = minorVersionPTP;
}

uint8_t GptpBase::getVersionPTP() const
{
    return this->versionPTP;
}

void GptpBase::setVersionPTP(uint8_t versionPTP)
{
    handleChange();
    this->versionPTP = versionPTP;
}

uint16_t GptpBase::getMessageLengthField() const
{
    return this->messageLengthField;
}

void GptpBase::setMessageLengthField(uint16_t messageLengthField)
{
    handleChange();
    this->messageLengthField = messageLengthField;
}

uint8_t GptpBase::getDomainNumber() const
{
    return this->domainNumber;
}

void GptpBase::setDomainNumber(uint8_t domainNumber)
{
    handleChange();
    this->domainNumber = domainNumber;
}

uint8_t GptpBase::getMinorSdoId() const
{
    return this->minorSdoId;
}

void GptpBase::setMinorSdoId(uint8_t minorSdoId)
{
    handleChange();
    this->minorSdoId = minorSdoId;
}

uint16_t GptpBase::getFlags() const
{
    return this->flags;
}

void GptpBase::setFlags(uint16_t flags)
{
    handleChange();
    this->flags = flags;
}

clocktime_t GptpBase::getCorrectionField() const
{
    return this->correctionField;
}

void GptpBase::setCorrectionField(clocktime_t correctionField)
{
    handleChange();
    this->correctionField = correctionField;
}

uint32_t GptpBase::getMessageTypeSpecific() const
{
    return this->messageTypeSpecific;
}

void GptpBase::setMessageTypeSpecific(uint32_t messageTypeSpecific)
{
    handleChange();
    this->messageTypeSpecific = messageTypeSpecific;
}

const PortIdentity& GptpBase::getSourcePortIdentity() const
{
    return this->sourcePortIdentity;
}

void GptpBase::setSourcePortIdentity(const PortIdentity& sourcePortIdentity)
{
    handleChange();
    this->sourcePortIdentity = sourcePortIdentity;
}

uint16_t GptpBase::getSequenceId() const
{
    return this->sequenceId;
}

void GptpBase::setSequenceId(uint16_t sequenceId)
{
    handleChange();
    this->sequenceId = sequenceId;
}

uint8_t GptpBase::getControlField() const
{
    return this->controlField;
}

void GptpBase::setControlField(uint8_t controlField)
{
    handleChange();
    this->controlField = controlField;
}

uint8_t GptpBase::getLogMessageInterval() const
{
    return this->logMessageInterval;
}

void GptpBase::setLogMessageInterval(uint8_t logMessageInterval)
{
    handleChange();
    this->logMessageInterval = logMessageInterval;
}

class GptpBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_majorSdoId,
        FIELD_messageType,
        FIELD_minorVersionPTP,
        FIELD_versionPTP,
        FIELD_messageLengthField,
        FIELD_domainNumber,
        FIELD_minorSdoId,
        FIELD_flags,
        FIELD_correctionField,
        FIELD_messageTypeSpecific,
        FIELD_sourcePortIdentity,
        FIELD_sequenceId,
        FIELD_controlField,
        FIELD_logMessageInterval,
    };
  public:
    GptpBaseDescriptor();
    virtual ~GptpBaseDescriptor();

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

Register_ClassDescriptor(GptpBaseDescriptor)

GptpBaseDescriptor::GptpBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpBase)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

GptpBaseDescriptor::~GptpBaseDescriptor()
{
    delete[] propertyNames;
}

bool GptpBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpBase *>(obj)!=nullptr;
}

const char **GptpBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 14+base->getFieldCount() : 14;
}

unsigned int GptpBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_majorSdoId
        0,    // FIELD_messageType
        FD_ISEDITABLE,    // FIELD_minorVersionPTP
        FD_ISEDITABLE,    // FIELD_versionPTP
        FD_ISEDITABLE,    // FIELD_messageLengthField
        FD_ISEDITABLE,    // FIELD_domainNumber
        FD_ISEDITABLE,    // FIELD_minorSdoId
        FD_ISEDITABLE,    // FIELD_flags
        0,    // FIELD_correctionField
        FD_ISEDITABLE,    // FIELD_messageTypeSpecific
        FD_ISCOMPOUND,    // FIELD_sourcePortIdentity
        FD_ISEDITABLE,    // FIELD_sequenceId
        FD_ISEDITABLE,    // FIELD_controlField
        FD_ISEDITABLE,    // FIELD_logMessageInterval
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *GptpBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "majorSdoId",
        "messageType",
        "minorVersionPTP",
        "versionPTP",
        "messageLengthField",
        "domainNumber",
        "minorSdoId",
        "flags",
        "correctionField",
        "messageTypeSpecific",
        "sourcePortIdentity",
        "sequenceId",
        "controlField",
        "logMessageInterval",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int GptpBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "majorSdoId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "messageType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "minorVersionPTP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "versionPTP") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "messageLengthField") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "domainNumber") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "minorSdoId") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "flags") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "correctionField") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "messageTypeSpecific") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "sourcePortIdentity") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "sequenceId") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "controlField") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "logMessageInterval") == 0) return baseIndex + 13;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_majorSdoId
        "inet::GptpMessageType",    // FIELD_messageType
        "uint8_t",    // FIELD_minorVersionPTP
        "uint8_t",    // FIELD_versionPTP
        "uint16_t",    // FIELD_messageLengthField
        "uint8_t",    // FIELD_domainNumber
        "uint8_t",    // FIELD_minorSdoId
        "uint16_t",    // FIELD_flags
        "inet::clocktime_t",    // FIELD_correctionField
        "uint32_t",    // FIELD_messageTypeSpecific
        "inet::PortIdentity",    // FIELD_sourcePortIdentity
        "uint16_t",    // FIELD_sequenceId
        "uint8_t",    // FIELD_controlField
        "uint8_t",    // FIELD_logMessageInterval
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_majorSdoId: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_messageType: {
            static const char *names[] = { "bit", "enum",  nullptr };
            return names;
        }
        case FIELD_minorVersionPTP: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_versionPTP: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_messageLengthField: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_domainNumber: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_minorSdoId: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_flags: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_correctionField: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_messageTypeSpecific: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_sourcePortIdentity: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_sequenceId: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_controlField: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_logMessageInterval: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *GptpBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_majorSdoId:
            if (!strcmp(propertyName, "bit")) return "4";
            return nullptr;
        case FIELD_messageType:
            if (!strcmp(propertyName, "bit")) return "4";
            if (!strcmp(propertyName, "enum")) return "inet::GptpMessageType";
            return nullptr;
        case FIELD_minorVersionPTP:
            if (!strcmp(propertyName, "bit")) return "4";
            return nullptr;
        case FIELD_versionPTP:
            if (!strcmp(propertyName, "bit")) return "4";
            return nullptr;
        case FIELD_messageLengthField:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        case FIELD_domainNumber:
            if (!strcmp(propertyName, "bit")) return "8";
            return nullptr;
        case FIELD_minorSdoId:
            if (!strcmp(propertyName, "bit")) return "8";
            return nullptr;
        case FIELD_flags:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        case FIELD_correctionField:
            if (!strcmp(propertyName, "bit")) return "64";
            return nullptr;
        case FIELD_messageTypeSpecific:
            if (!strcmp(propertyName, "bit")) return "32";
            return nullptr;
        case FIELD_sourcePortIdentity:
            if (!strcmp(propertyName, "bit")) return "80";
            return nullptr;
        case FIELD_sequenceId:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        case FIELD_controlField:
            if (!strcmp(propertyName, "bit")) return "8";
            return nullptr;
        case FIELD_logMessageInterval:
            if (!strcmp(propertyName, "bit")) return "8";
            return nullptr;
        default: return nullptr;
    }
}

int GptpBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpBase'", field);
    }
}

const char *GptpBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        case FIELD_majorSdoId: return ulong2string(pp->getMajorSdoId());
        case FIELD_messageType: return enum2string(pp->getMessageType(), "inet::GptpMessageType");
        case FIELD_minorVersionPTP: return ulong2string(pp->getMinorVersionPTP());
        case FIELD_versionPTP: return ulong2string(pp->getVersionPTP());
        case FIELD_messageLengthField: return ulong2string(pp->getMessageLengthField());
        case FIELD_domainNumber: return ulong2string(pp->getDomainNumber());
        case FIELD_minorSdoId: return ulong2string(pp->getMinorSdoId());
        case FIELD_flags: return ulong2string(pp->getFlags());
        case FIELD_correctionField: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getCorrectionField()));
        case FIELD_messageTypeSpecific: return ulong2string(pp->getMessageTypeSpecific());
        case FIELD_sourcePortIdentity: return "";
        case FIELD_sequenceId: return ulong2string(pp->getSequenceId());
        case FIELD_controlField: return ulong2string(pp->getControlField());
        case FIELD_logMessageInterval: return ulong2string(pp->getLogMessageInterval());
        default: return "";
    }
}

void GptpBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        case FIELD_majorSdoId: pp->setMajorSdoId(string2ulong(value)); break;
        case FIELD_minorVersionPTP: pp->setMinorVersionPTP(string2ulong(value)); break;
        case FIELD_versionPTP: pp->setVersionPTP(string2ulong(value)); break;
        case FIELD_messageLengthField: pp->setMessageLengthField(string2ulong(value)); break;
        case FIELD_domainNumber: pp->setDomainNumber(string2ulong(value)); break;
        case FIELD_minorSdoId: pp->setMinorSdoId(string2ulong(value)); break;
        case FIELD_flags: pp->setFlags(string2ulong(value)); break;
        case FIELD_messageTypeSpecific: pp->setMessageTypeSpecific(string2ulong(value)); break;
        case FIELD_sequenceId: pp->setSequenceId(string2ulong(value)); break;
        case FIELD_controlField: pp->setControlField(string2ulong(value)); break;
        case FIELD_logMessageInterval: pp->setLogMessageInterval(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpBase'", field);
    }
}

omnetpp::cValue GptpBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        case FIELD_majorSdoId: return (omnetpp::intval_t)(pp->getMajorSdoId());
        case FIELD_messageType: return static_cast<int>(pp->getMessageType());
        case FIELD_minorVersionPTP: return (omnetpp::intval_t)(pp->getMinorVersionPTP());
        case FIELD_versionPTP: return (omnetpp::intval_t)(pp->getVersionPTP());
        case FIELD_messageLengthField: return (omnetpp::intval_t)(pp->getMessageLengthField());
        case FIELD_domainNumber: return (omnetpp::intval_t)(pp->getDomainNumber());
        case FIELD_minorSdoId: return (omnetpp::intval_t)(pp->getMinorSdoId());
        case FIELD_flags: return (omnetpp::intval_t)(pp->getFlags());
        case FIELD_correctionField: return cValue(pp->getCorrectionField().dbl(),"s");
        case FIELD_messageTypeSpecific: return (omnetpp::intval_t)(pp->getMessageTypeSpecific());
        case FIELD_sourcePortIdentity: return omnetpp::toAnyPtr(&pp->getSourcePortIdentity()); break;
        case FIELD_sequenceId: return (omnetpp::intval_t)(pp->getSequenceId());
        case FIELD_controlField: return (omnetpp::intval_t)(pp->getControlField());
        case FIELD_logMessageInterval: return (omnetpp::intval_t)(pp->getLogMessageInterval());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpBase' as cValue -- field index out of range?", field);
    }
}

void GptpBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        case FIELD_majorSdoId: pp->setMajorSdoId(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_minorVersionPTP: pp->setMinorVersionPTP(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_versionPTP: pp->setVersionPTP(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_messageLengthField: pp->setMessageLengthField(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_domainNumber: pp->setDomainNumber(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_minorSdoId: pp->setMinorSdoId(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_flags: pp->setFlags(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_messageTypeSpecific: pp->setMessageTypeSpecific(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sequenceId: pp->setSequenceId(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_controlField: pp->setControlField(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_logMessageInterval: pp->setLogMessageInterval(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpBase'", field);
    }
}

const char *GptpBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sourcePortIdentity: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

omnetpp::any_ptr GptpBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        case FIELD_sourcePortIdentity: return omnetpp::toAnyPtr(&pp->getSourcePortIdentity()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpBase *pp = omnetpp::fromAnyPtr<GptpBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpBase'", field);
    }
}

GptpTlv::GptpTlv()
{
}

GptpTlv::GptpTlv(const GptpTlv& other)
{
    copy(other);
}

GptpTlv::~GptpTlv()
{
}

GptpTlv& GptpTlv::operator=(const GptpTlv& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void GptpTlv::copy(const GptpTlv& other)
{
    this->tlvType = other.tlvType;
    this->lengthField = other.lengthField;
}

void GptpTlv::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->tlvType);
    doParsimPacking(b,this->lengthField);
}

void GptpTlv::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->tlvType);
    doParsimUnpacking(b,this->lengthField);
}

GptpTlvType GptpTlv::getTlvType() const
{
    return this->tlvType;
}

void GptpTlv::setTlvType(GptpTlvType tlvType)
{
    this->tlvType = tlvType;
}

uint16_t GptpTlv::getLengthField() const
{
    return this->lengthField;
}

void GptpTlv::setLengthField(uint16_t lengthField)
{
    this->lengthField = lengthField;
}

class GptpTlvDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tlvType,
        FIELD_lengthField,
    };
  public:
    GptpTlvDescriptor();
    virtual ~GptpTlvDescriptor();

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

Register_ClassDescriptor(GptpTlvDescriptor)

GptpTlvDescriptor::GptpTlvDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpTlv)), "")
{
    propertyNames = nullptr;
}

GptpTlvDescriptor::~GptpTlvDescriptor()
{
    delete[] propertyNames;
}

bool GptpTlvDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpTlv *>(obj)!=nullptr;
}

const char **GptpTlvDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpTlvDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpTlvDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GptpTlvDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_tlvType
        FD_ISEDITABLE,    // FIELD_lengthField
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GptpTlvDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tlvType",
        "lengthField",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GptpTlvDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tlvType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "lengthField") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpTlvDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::GptpTlvType",    // FIELD_tlvType
        "uint16_t",    // FIELD_lengthField
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpTlvDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvType: {
            static const char *names[] = { "bit", "enum",  nullptr };
            return names;
        }
        case FIELD_lengthField: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *GptpTlvDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvType:
            if (!strcmp(propertyName, "bit")) return "16";
            if (!strcmp(propertyName, "enum")) return "inet::GptpTlvType";
            return nullptr;
        case FIELD_lengthField:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        default: return nullptr;
    }
}

int GptpTlvDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpTlvDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpTlv'", field);
    }
}

const char *GptpTlvDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpTlvDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        case FIELD_tlvType: return enum2string(pp->getTlvType(), "inet::GptpTlvType");
        case FIELD_lengthField: return ulong2string(pp->getLengthField());
        default: return "";
    }
}

void GptpTlvDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpTlv'", field);
    }
}

omnetpp::cValue GptpTlvDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        case FIELD_tlvType: return static_cast<int>(pp->getTlvType());
        case FIELD_lengthField: return (omnetpp::intval_t)(pp->getLengthField());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpTlv' as cValue -- field index out of range?", field);
    }
}

void GptpTlvDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpTlv'", field);
    }
}

const char *GptpTlvDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GptpTlvDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpTlvDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpTlv *pp = omnetpp::fromAnyPtr<GptpTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpTlv'", field);
    }
}

GptpFollowUpInformationTlv::GptpFollowUpInformationTlv() : ::inet::GptpTlv()
{
    this->setTlvType(GPTP_FOLLOW_UP_INFORMATION_TLV);

}

GptpFollowUpInformationTlv::GptpFollowUpInformationTlv(const GptpFollowUpInformationTlv& other) : ::inet::GptpTlv(other)
{
    copy(other);
}

GptpFollowUpInformationTlv::~GptpFollowUpInformationTlv()
{
}

GptpFollowUpInformationTlv& GptpFollowUpInformationTlv::operator=(const GptpFollowUpInformationTlv& other)
{
    if (this == &other) return *this;
    ::inet::GptpTlv::operator=(other);
    copy(other);
    return *this;
}

void GptpFollowUpInformationTlv::copy(const GptpFollowUpInformationTlv& other)
{
    this->lengthField = other.lengthField;
    this->organizationId = other.organizationId;
    this->organizationSubType = other.organizationSubType;
    this->rateRatio = other.rateRatio;
    this->gmTimeBaseIndicator = other.gmTimeBaseIndicator;
    this->lastGmPhaseChange = other.lastGmPhaseChange;
    this->scaledLastGmFreqChange = other.scaledLastGmFreqChange;
}

void GptpFollowUpInformationTlv::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::inet::GptpTlv&)*this);
    doParsimPacking(b,this->lengthField);
    doParsimPacking(b,this->organizationId);
    doParsimPacking(b,this->organizationSubType);
    doParsimPacking(b,this->rateRatio);
    doParsimPacking(b,this->gmTimeBaseIndicator);
    doParsimPacking(b,this->lastGmPhaseChange);
    doParsimPacking(b,this->scaledLastGmFreqChange);
}

void GptpFollowUpInformationTlv::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::inet::GptpTlv&)*this);
    doParsimUnpacking(b,this->lengthField);
    doParsimUnpacking(b,this->organizationId);
    doParsimUnpacking(b,this->organizationSubType);
    doParsimUnpacking(b,this->rateRatio);
    doParsimUnpacking(b,this->gmTimeBaseIndicator);
    doParsimUnpacking(b,this->lastGmPhaseChange);
    doParsimUnpacking(b,this->scaledLastGmFreqChange);
}

uint16_t GptpFollowUpInformationTlv::getLengthField() const
{
    return this->lengthField;
}

void GptpFollowUpInformationTlv::setLengthField(uint16_t lengthField)
{
    this->lengthField = lengthField;
}

uint32_t GptpFollowUpInformationTlv::getOrganizationId() const
{
    return this->organizationId;
}

void GptpFollowUpInformationTlv::setOrganizationId(uint32_t organizationId)
{
    this->organizationId = organizationId;
}

uint32_t GptpFollowUpInformationTlv::getOrganizationSubType() const
{
    return this->organizationSubType;
}

void GptpFollowUpInformationTlv::setOrganizationSubType(uint32_t organizationSubType)
{
    this->organizationSubType = organizationSubType;
}

double GptpFollowUpInformationTlv::getRateRatio() const
{
    return this->rateRatio;
}

void GptpFollowUpInformationTlv::setRateRatio(double rateRatio)
{
    this->rateRatio = rateRatio;
}

uint16_t GptpFollowUpInformationTlv::getGmTimeBaseIndicator() const
{
    return this->gmTimeBaseIndicator;
}

void GptpFollowUpInformationTlv::setGmTimeBaseIndicator(uint16_t gmTimeBaseIndicator)
{
    this->gmTimeBaseIndicator = gmTimeBaseIndicator;
}

clocktime_t GptpFollowUpInformationTlv::getLastGmPhaseChange() const
{
    return this->lastGmPhaseChange;
}

void GptpFollowUpInformationTlv::setLastGmPhaseChange(clocktime_t lastGmPhaseChange)
{
    this->lastGmPhaseChange = lastGmPhaseChange;
}

int32_t GptpFollowUpInformationTlv::getScaledLastGmFreqChange() const
{
    return this->scaledLastGmFreqChange;
}

void GptpFollowUpInformationTlv::setScaledLastGmFreqChange(int32_t scaledLastGmFreqChange)
{
    this->scaledLastGmFreqChange = scaledLastGmFreqChange;
}

class GptpFollowUpInformationTlvDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lengthField,
        FIELD_organizationId,
        FIELD_organizationSubType,
        FIELD_rateRatio,
        FIELD_gmTimeBaseIndicator,
        FIELD_lastGmPhaseChange,
        FIELD_scaledLastGmFreqChange,
    };
  public:
    GptpFollowUpInformationTlvDescriptor();
    virtual ~GptpFollowUpInformationTlvDescriptor();

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

Register_ClassDescriptor(GptpFollowUpInformationTlvDescriptor)

GptpFollowUpInformationTlvDescriptor::GptpFollowUpInformationTlvDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpFollowUpInformationTlv)), "inet::GptpTlv")
{
    propertyNames = nullptr;
}

GptpFollowUpInformationTlvDescriptor::~GptpFollowUpInformationTlvDescriptor()
{
    delete[] propertyNames;
}

bool GptpFollowUpInformationTlvDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpFollowUpInformationTlv *>(obj)!=nullptr;
}

const char **GptpFollowUpInformationTlvDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpFollowUpInformationTlvDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpFollowUpInformationTlvDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int GptpFollowUpInformationTlvDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lengthField
        FD_ISEDITABLE,    // FIELD_organizationId
        FD_ISEDITABLE,    // FIELD_organizationSubType
        FD_ISEDITABLE,    // FIELD_rateRatio
        FD_ISEDITABLE,    // FIELD_gmTimeBaseIndicator
        0,    // FIELD_lastGmPhaseChange
        FD_ISEDITABLE,    // FIELD_scaledLastGmFreqChange
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *GptpFollowUpInformationTlvDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lengthField",
        "organizationId",
        "organizationSubType",
        "rateRatio",
        "gmTimeBaseIndicator",
        "lastGmPhaseChange",
        "scaledLastGmFreqChange",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int GptpFollowUpInformationTlvDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lengthField") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "organizationId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "organizationSubType") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "rateRatio") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "gmTimeBaseIndicator") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "lastGmPhaseChange") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "scaledLastGmFreqChange") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpFollowUpInformationTlvDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_lengthField
        "uint32_t",    // FIELD_organizationId
        "uint32_t",    // FIELD_organizationSubType
        "double",    // FIELD_rateRatio
        "uint16_t",    // FIELD_gmTimeBaseIndicator
        "inet::clocktime_t",    // FIELD_lastGmPhaseChange
        "int32_t",    // FIELD_scaledLastGmFreqChange
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpFollowUpInformationTlvDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lengthField: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_organizationId: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_organizationSubType: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_rateRatio: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_gmTimeBaseIndicator: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_lastGmPhaseChange: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        case FIELD_scaledLastGmFreqChange: {
            static const char *names[] = { "bit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *GptpFollowUpInformationTlvDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lengthField:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        case FIELD_organizationId:
            if (!strcmp(propertyName, "bit")) return "24";
            return nullptr;
        case FIELD_organizationSubType:
            if (!strcmp(propertyName, "bit")) return "24";
            return nullptr;
        case FIELD_rateRatio:
            if (!strcmp(propertyName, "bit")) return "32";
            return nullptr;
        case FIELD_gmTimeBaseIndicator:
            if (!strcmp(propertyName, "bit")) return "16";
            return nullptr;
        case FIELD_lastGmPhaseChange:
            if (!strcmp(propertyName, "bit")) return "96";
            return nullptr;
        case FIELD_scaledLastGmFreqChange:
            if (!strcmp(propertyName, "bit")) return "32";
            return nullptr;
        default: return nullptr;
    }
}

int GptpFollowUpInformationTlvDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpFollowUpInformationTlvDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpFollowUpInformationTlv'", field);
    }
}

const char *GptpFollowUpInformationTlvDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpFollowUpInformationTlvDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: return ulong2string(pp->getLengthField());
        case FIELD_organizationId: return ulong2string(pp->getOrganizationId());
        case FIELD_organizationSubType: return ulong2string(pp->getOrganizationSubType());
        case FIELD_rateRatio: return double2string(pp->getRateRatio());
        case FIELD_gmTimeBaseIndicator: return ulong2string(pp->getGmTimeBaseIndicator());
        case FIELD_lastGmPhaseChange: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getLastGmPhaseChange()));
        case FIELD_scaledLastGmFreqChange: return long2string(pp->getScaledLastGmFreqChange());
        default: return "";
    }
}

void GptpFollowUpInformationTlvDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(string2ulong(value)); break;
        case FIELD_organizationId: pp->setOrganizationId(string2ulong(value)); break;
        case FIELD_organizationSubType: pp->setOrganizationSubType(string2ulong(value)); break;
        case FIELD_rateRatio: pp->setRateRatio(string2double(value)); break;
        case FIELD_gmTimeBaseIndicator: pp->setGmTimeBaseIndicator(string2ulong(value)); break;
        case FIELD_scaledLastGmFreqChange: pp->setScaledLastGmFreqChange(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUpInformationTlv'", field);
    }
}

omnetpp::cValue GptpFollowUpInformationTlvDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: return (omnetpp::intval_t)(pp->getLengthField());
        case FIELD_organizationId: return (omnetpp::intval_t)(pp->getOrganizationId());
        case FIELD_organizationSubType: return (omnetpp::intval_t)(pp->getOrganizationSubType());
        case FIELD_rateRatio: return pp->getRateRatio();
        case FIELD_gmTimeBaseIndicator: return (omnetpp::intval_t)(pp->getGmTimeBaseIndicator());
        case FIELD_lastGmPhaseChange: return cValue(pp->getLastGmPhaseChange().dbl(),"s");
        case FIELD_scaledLastGmFreqChange: return pp->getScaledLastGmFreqChange();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpFollowUpInformationTlv' as cValue -- field index out of range?", field);
    }
}

void GptpFollowUpInformationTlvDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_organizationId: pp->setOrganizationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_organizationSubType: pp->setOrganizationSubType(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_rateRatio: pp->setRateRatio(value.doubleValue()); break;
        case FIELD_gmTimeBaseIndicator: pp->setGmTimeBaseIndicator(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_scaledLastGmFreqChange: pp->setScaledLastGmFreqChange(omnetpp::checked_int_cast<int32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUpInformationTlv'", field);
    }
}

const char *GptpFollowUpInformationTlvDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GptpFollowUpInformationTlvDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpFollowUpInformationTlvDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUpInformationTlv *pp = omnetpp::fromAnyPtr<GptpFollowUpInformationTlv>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUpInformationTlv'", field);
    }
}

Register_Class(GptpSync)

GptpSync::GptpSync() : ::inet::GptpBase()
{
    this->setMessageType(GPTPTYPE_SYNC);
    this->setFlags(twoStepFlag);
    this->setChunkLength(GPTP_SYNC_2STEP_PACKET_SIZE);
    this->setMessageLengthField(B(GPTP_SYNC_2STEP_PACKET_SIZE).get());
}

GptpSync::GptpSync(const GptpSync& other) : ::inet::GptpBase(other)
{
    copy(other);
}

GptpSync::~GptpSync()
{
}

GptpSync& GptpSync::operator=(const GptpSync& other)
{
    if (this == &other) return *this;
    ::inet::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpSync::copy(const GptpSync& other)
{
}

void GptpSync::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::GptpBase::parsimPack(b);
}

void GptpSync::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::GptpBase::parsimUnpack(b);
}

class GptpSyncDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    GptpSyncDescriptor();
    virtual ~GptpSyncDescriptor();

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

Register_ClassDescriptor(GptpSyncDescriptor)

GptpSyncDescriptor::GptpSyncDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpSync)), "inet::GptpBase")
{
    propertyNames = nullptr;
}

GptpSyncDescriptor::~GptpSyncDescriptor()
{
    delete[] propertyNames;
}

bool GptpSyncDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpSync *>(obj)!=nullptr;
}

const char **GptpSyncDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpSyncDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpSyncDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int GptpSyncDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *GptpSyncDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int GptpSyncDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *GptpSyncDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **GptpSyncDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpSyncDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpSyncDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpSyncDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpSync'", field);
    }
}

const char *GptpSyncDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpSyncDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void GptpSyncDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpSync'", field);
    }
}

omnetpp::cValue GptpSyncDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpSync' as cValue -- field index out of range?", field);
    }
}

void GptpSyncDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpSync'", field);
    }
}

const char *GptpSyncDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr GptpSyncDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpSyncDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpSync *pp = omnetpp::fromAnyPtr<GptpSync>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpSync'", field);
    }
}

Register_Class(GptpFollowUp)

GptpFollowUp::GptpFollowUp() : ::inet::GptpBase()
{
    this->setMessageType(GPTPTYPE_FOLLOW_UP);
    this->setChunkLength(GPTP_FOLLOW_UP_PACKET_SIZE);
    this->setMessageLengthField(B(GPTP_FOLLOW_UP_PACKET_SIZE).get());

}

GptpFollowUp::GptpFollowUp(const GptpFollowUp& other) : ::inet::GptpBase(other)
{
    copy(other);
}

GptpFollowUp::~GptpFollowUp()
{
}

GptpFollowUp& GptpFollowUp::operator=(const GptpFollowUp& other)
{
    if (this == &other) return *this;
    ::inet::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpFollowUp::copy(const GptpFollowUp& other)
{
    this->preciseOriginTimestamp = other.preciseOriginTimestamp;
    this->followUpInformationTLV = other.followUpInformationTLV;
}

void GptpFollowUp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::GptpBase::parsimPack(b);
    doParsimPacking(b,this->preciseOriginTimestamp);
    doParsimPacking(b,this->followUpInformationTLV);
}

void GptpFollowUp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::GptpBase::parsimUnpack(b);
    doParsimUnpacking(b,this->preciseOriginTimestamp);
    doParsimUnpacking(b,this->followUpInformationTLV);
}

clocktime_t GptpFollowUp::getPreciseOriginTimestamp() const
{
    return this->preciseOriginTimestamp;
}

void GptpFollowUp::setPreciseOriginTimestamp(clocktime_t preciseOriginTimestamp)
{
    handleChange();
    this->preciseOriginTimestamp = preciseOriginTimestamp;
}

const GptpFollowUpInformationTlv& GptpFollowUp::getFollowUpInformationTLV() const
{
    return this->followUpInformationTLV;
}

void GptpFollowUp::setFollowUpInformationTLV(const GptpFollowUpInformationTlv& followUpInformationTLV)
{
    handleChange();
    this->followUpInformationTLV = followUpInformationTLV;
}

class GptpFollowUpDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_preciseOriginTimestamp,
        FIELD_followUpInformationTLV,
    };
  public:
    GptpFollowUpDescriptor();
    virtual ~GptpFollowUpDescriptor();

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

Register_ClassDescriptor(GptpFollowUpDescriptor)

GptpFollowUpDescriptor::GptpFollowUpDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpFollowUp)), "inet::GptpBase")
{
    propertyNames = nullptr;
}

GptpFollowUpDescriptor::~GptpFollowUpDescriptor()
{
    delete[] propertyNames;
}

bool GptpFollowUpDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpFollowUp *>(obj)!=nullptr;
}

const char **GptpFollowUpDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpFollowUpDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpFollowUpDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GptpFollowUpDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_preciseOriginTimestamp
        FD_ISCOMPOUND,    // FIELD_followUpInformationTLV
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GptpFollowUpDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "preciseOriginTimestamp",
        "followUpInformationTLV",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GptpFollowUpDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "preciseOriginTimestamp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "followUpInformationTLV") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpFollowUpDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::clocktime_t",    // FIELD_preciseOriginTimestamp
        "inet::GptpFollowUpInformationTlv",    // FIELD_followUpInformationTLV
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpFollowUpDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpFollowUpDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpFollowUpDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpFollowUpDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpFollowUp'", field);
    }
}

const char *GptpFollowUpDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpFollowUpDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_preciseOriginTimestamp: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getPreciseOriginTimestamp()));
        case FIELD_followUpInformationTLV: return "";
        default: return "";
    }
}

void GptpFollowUpDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUp'", field);
    }
}

omnetpp::cValue GptpFollowUpDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_preciseOriginTimestamp: return cValue(pp->getPreciseOriginTimestamp().dbl(),"s");
        case FIELD_followUpInformationTLV: return omnetpp::toAnyPtr(&pp->getFollowUpInformationTLV()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpFollowUp' as cValue -- field index out of range?", field);
    }
}

void GptpFollowUpDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUp'", field);
    }
}

const char *GptpFollowUpDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_followUpInformationTLV: return omnetpp::opp_typename(typeid(GptpFollowUpInformationTlv));
        default: return nullptr;
    };
}

omnetpp::any_ptr GptpFollowUpDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_followUpInformationTLV: return omnetpp::toAnyPtr(&pp->getFollowUpInformationTLV()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpFollowUpDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpFollowUp *pp = omnetpp::fromAnyPtr<GptpFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpFollowUp'", field);
    }
}

Register_Class(GptpPdelayReq)

GptpPdelayReq::GptpPdelayReq() : ::inet::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_REQ);
    this->setChunkLength(GPTP_PDELAY_REQ_PACKET_SIZE);
    this->setMessageLengthField(B(GPTP_PDELAY_REQ_PACKET_SIZE).get());

}

GptpPdelayReq::GptpPdelayReq(const GptpPdelayReq& other) : ::inet::GptpBase(other)
{
    copy(other);
}

GptpPdelayReq::~GptpPdelayReq()
{
}

GptpPdelayReq& GptpPdelayReq::operator=(const GptpPdelayReq& other)
{
    if (this == &other) return *this;
    ::inet::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayReq::copy(const GptpPdelayReq& other)
{
    this->reserved1 = other.reserved1;
    this->reserved2 = other.reserved2;
}

void GptpPdelayReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::GptpBase::parsimPack(b);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->reserved2);
}

void GptpPdelayReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::GptpBase::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->reserved2);
}

clocktime_t GptpPdelayReq::getReserved1() const
{
    return this->reserved1;
}

void GptpPdelayReq::setReserved1(clocktime_t reserved1)
{
    handleChange();
    this->reserved1 = reserved1;
}

clocktime_t GptpPdelayReq::getReserved2() const
{
    return this->reserved2;
}

void GptpPdelayReq::setReserved2(clocktime_t reserved2)
{
    handleChange();
    this->reserved2 = reserved2;
}

class GptpPdelayReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved1,
        FIELD_reserved2,
    };
  public:
    GptpPdelayReqDescriptor();
    virtual ~GptpPdelayReqDescriptor();

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

Register_ClassDescriptor(GptpPdelayReqDescriptor)

GptpPdelayReqDescriptor::GptpPdelayReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpPdelayReq)), "inet::GptpBase")
{
    propertyNames = nullptr;
}

GptpPdelayReqDescriptor::~GptpPdelayReqDescriptor()
{
    delete[] propertyNames;
}

bool GptpPdelayReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayReq *>(obj)!=nullptr;
}

const char **GptpPdelayReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpPdelayReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpPdelayReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GptpPdelayReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_reserved1
        0,    // FIELD_reserved2
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved1",
        "reserved2",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GptpPdelayReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpPdelayReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::clocktime_t",    // FIELD_reserved1
        "inet::clocktime_t",    // FIELD_reserved2
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayReqDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpPdelayReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpPdelayReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpPdelayReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpPdelayReq'", field);
    }
}

const char *GptpPdelayReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getReserved1()));
        case FIELD_reserved2: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getReserved2()));
        default: return "";
    }
}

void GptpPdelayReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayReq'", field);
    }
}

omnetpp::cValue GptpPdelayReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        case FIELD_reserved1: return cValue(pp->getReserved1().dbl(),"s");
        case FIELD_reserved2: return cValue(pp->getReserved2().dbl(),"s");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpPdelayReq' as cValue -- field index out of range?", field);
    }
}

void GptpPdelayReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayReq'", field);
    }
}

const char *GptpPdelayReqDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GptpPdelayReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpPdelayReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayReq *pp = omnetpp::fromAnyPtr<GptpPdelayReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayReq'", field);
    }
}

Register_Class(GptpPdelayResp)

GptpPdelayResp::GptpPdelayResp() : ::inet::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_RESP);
    this->setChunkLength(GPTP_PDELAY_RESP_PACKET_SIZE);
    this->setMessageLengthField(B(GPTP_PDELAY_RESP_PACKET_SIZE).get());

}

GptpPdelayResp::GptpPdelayResp(const GptpPdelayResp& other) : ::inet::GptpBase(other)
{
    copy(other);
}

GptpPdelayResp::~GptpPdelayResp()
{
}

GptpPdelayResp& GptpPdelayResp::operator=(const GptpPdelayResp& other)
{
    if (this == &other) return *this;
    ::inet::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayResp::copy(const GptpPdelayResp& other)
{
    this->requestReceiptTimestamp = other.requestReceiptTimestamp;
    this->requestingPortIdentity = other.requestingPortIdentity;
}

void GptpPdelayResp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::GptpBase::parsimPack(b);
    doParsimPacking(b,this->requestReceiptTimestamp);
    doParsimPacking(b,this->requestingPortIdentity);
}

void GptpPdelayResp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::GptpBase::parsimUnpack(b);
    doParsimUnpacking(b,this->requestReceiptTimestamp);
    doParsimUnpacking(b,this->requestingPortIdentity);
}

clocktime_t GptpPdelayResp::getRequestReceiptTimestamp() const
{
    return this->requestReceiptTimestamp;
}

void GptpPdelayResp::setRequestReceiptTimestamp(clocktime_t requestReceiptTimestamp)
{
    handleChange();
    this->requestReceiptTimestamp = requestReceiptTimestamp;
}

const PortIdentity& GptpPdelayResp::getRequestingPortIdentity() const
{
    return this->requestingPortIdentity;
}

void GptpPdelayResp::setRequestingPortIdentity(const PortIdentity& requestingPortIdentity)
{
    handleChange();
    this->requestingPortIdentity = requestingPortIdentity;
}

class GptpPdelayRespDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestReceiptTimestamp,
        FIELD_requestingPortIdentity,
    };
  public:
    GptpPdelayRespDescriptor();
    virtual ~GptpPdelayRespDescriptor();

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

Register_ClassDescriptor(GptpPdelayRespDescriptor)

GptpPdelayRespDescriptor::GptpPdelayRespDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpPdelayResp)), "inet::GptpBase")
{
    propertyNames = nullptr;
}

GptpPdelayRespDescriptor::~GptpPdelayRespDescriptor()
{
    delete[] propertyNames;
}

bool GptpPdelayRespDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayResp *>(obj)!=nullptr;
}

const char **GptpPdelayRespDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpPdelayRespDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpPdelayRespDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GptpPdelayRespDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_requestReceiptTimestamp
        FD_ISCOMPOUND,    // FIELD_requestingPortIdentity
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayRespDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestReceiptTimestamp",
        "requestingPortIdentity",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GptpPdelayRespDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestReceiptTimestamp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "requestingPortIdentity") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpPdelayRespDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::clocktime_t",    // FIELD_requestReceiptTimestamp
        "inet::PortIdentity",    // FIELD_requestingPortIdentity
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayRespDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpPdelayRespDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpPdelayRespDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpPdelayRespDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpPdelayResp'", field);
    }
}

const char *GptpPdelayRespDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayRespDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        case FIELD_requestReceiptTimestamp: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getRequestReceiptTimestamp()));
        case FIELD_requestingPortIdentity: return "";
        default: return "";
    }
}

void GptpPdelayRespDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayResp'", field);
    }
}

omnetpp::cValue GptpPdelayRespDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        case FIELD_requestReceiptTimestamp: return cValue(pp->getRequestReceiptTimestamp().dbl(),"s");
        case FIELD_requestingPortIdentity: return omnetpp::toAnyPtr(&pp->getRequestingPortIdentity()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpPdelayResp' as cValue -- field index out of range?", field);
    }
}

void GptpPdelayRespDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayResp'", field);
    }
}

const char *GptpPdelayRespDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_requestingPortIdentity: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

omnetpp::any_ptr GptpPdelayRespDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        case FIELD_requestingPortIdentity: return omnetpp::toAnyPtr(&pp->getRequestingPortIdentity()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpPdelayRespDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayResp *pp = omnetpp::fromAnyPtr<GptpPdelayResp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayResp'", field);
    }
}

Register_Class(GptpPdelayRespFollowUp)

GptpPdelayRespFollowUp::GptpPdelayRespFollowUp() : ::inet::GptpBase()
{
    this->setMessageType(GPTPTYPE_PDELAY_RESP_FOLLOW_UP);
    this->setChunkLength(GPTP_PDELAY_RESP_FOLLOW_UP_PACKET_SIZE);
    this->setMessageLengthField(B(GPTP_PDELAY_RESP_FOLLOW_UP_PACKET_SIZE).get());

}

GptpPdelayRespFollowUp::GptpPdelayRespFollowUp(const GptpPdelayRespFollowUp& other) : ::inet::GptpBase(other)
{
    copy(other);
}

GptpPdelayRespFollowUp::~GptpPdelayRespFollowUp()
{
}

GptpPdelayRespFollowUp& GptpPdelayRespFollowUp::operator=(const GptpPdelayRespFollowUp& other)
{
    if (this == &other) return *this;
    ::inet::GptpBase::operator=(other);
    copy(other);
    return *this;
}

void GptpPdelayRespFollowUp::copy(const GptpPdelayRespFollowUp& other)
{
    this->responseOriginTimestamp = other.responseOriginTimestamp;
    this->requestingPortIdentity = other.requestingPortIdentity;
}

void GptpPdelayRespFollowUp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::GptpBase::parsimPack(b);
    doParsimPacking(b,this->responseOriginTimestamp);
    doParsimPacking(b,this->requestingPortIdentity);
}

void GptpPdelayRespFollowUp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::GptpBase::parsimUnpack(b);
    doParsimUnpacking(b,this->responseOriginTimestamp);
    doParsimUnpacking(b,this->requestingPortIdentity);
}

clocktime_t GptpPdelayRespFollowUp::getResponseOriginTimestamp() const
{
    return this->responseOriginTimestamp;
}

void GptpPdelayRespFollowUp::setResponseOriginTimestamp(clocktime_t responseOriginTimestamp)
{
    handleChange();
    this->responseOriginTimestamp = responseOriginTimestamp;
}

const PortIdentity& GptpPdelayRespFollowUp::getRequestingPortIdentity() const
{
    return this->requestingPortIdentity;
}

void GptpPdelayRespFollowUp::setRequestingPortIdentity(const PortIdentity& requestingPortIdentity)
{
    handleChange();
    this->requestingPortIdentity = requestingPortIdentity;
}

class GptpPdelayRespFollowUpDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_responseOriginTimestamp,
        FIELD_requestingPortIdentity,
    };
  public:
    GptpPdelayRespFollowUpDescriptor();
    virtual ~GptpPdelayRespFollowUpDescriptor();

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

Register_ClassDescriptor(GptpPdelayRespFollowUpDescriptor)

GptpPdelayRespFollowUpDescriptor::GptpPdelayRespFollowUpDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpPdelayRespFollowUp)), "inet::GptpBase")
{
    propertyNames = nullptr;
}

GptpPdelayRespFollowUpDescriptor::~GptpPdelayRespFollowUpDescriptor()
{
    delete[] propertyNames;
}

bool GptpPdelayRespFollowUpDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpPdelayRespFollowUp *>(obj)!=nullptr;
}

const char **GptpPdelayRespFollowUpDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpPdelayRespFollowUpDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpPdelayRespFollowUpDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GptpPdelayRespFollowUpDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_responseOriginTimestamp
        FD_ISCOMPOUND,    // FIELD_requestingPortIdentity
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "responseOriginTimestamp",
        "requestingPortIdentity",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GptpPdelayRespFollowUpDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "responseOriginTimestamp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "requestingPortIdentity") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::clocktime_t",    // FIELD_responseOriginTimestamp
        "inet::PortIdentity",    // FIELD_requestingPortIdentity
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpPdelayRespFollowUpDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpPdelayRespFollowUpDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpPdelayRespFollowUpDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpPdelayRespFollowUpDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpPdelayRespFollowUp'", field);
    }
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpPdelayRespFollowUpDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_responseOriginTimestamp: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getResponseOriginTimestamp()));
        case FIELD_requestingPortIdentity: return "";
        default: return "";
    }
}

void GptpPdelayRespFollowUpDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayRespFollowUp'", field);
    }
}

omnetpp::cValue GptpPdelayRespFollowUpDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_responseOriginTimestamp: return cValue(pp->getResponseOriginTimestamp().dbl(),"s");
        case FIELD_requestingPortIdentity: return omnetpp::toAnyPtr(&pp->getRequestingPortIdentity()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpPdelayRespFollowUp' as cValue -- field index out of range?", field);
    }
}

void GptpPdelayRespFollowUpDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayRespFollowUp'", field);
    }
}

const char *GptpPdelayRespFollowUpDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_requestingPortIdentity: return omnetpp::opp_typename(typeid(PortIdentity));
        default: return nullptr;
    };
}

omnetpp::any_ptr GptpPdelayRespFollowUpDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        case FIELD_requestingPortIdentity: return omnetpp::toAnyPtr(&pp->getRequestingPortIdentity()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpPdelayRespFollowUpDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpPdelayRespFollowUp *pp = omnetpp::fromAnyPtr<GptpPdelayRespFollowUp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpPdelayRespFollowUp'", field);
    }
}

Register_Class(GptpIngressTimeInd)

GptpIngressTimeInd::GptpIngressTimeInd() : ::inet::TagBase()
{
}

GptpIngressTimeInd::GptpIngressTimeInd(const GptpIngressTimeInd& other) : ::inet::TagBase(other)
{
    copy(other);
}

GptpIngressTimeInd::~GptpIngressTimeInd()
{
}

GptpIngressTimeInd& GptpIngressTimeInd::operator=(const GptpIngressTimeInd& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void GptpIngressTimeInd::copy(const GptpIngressTimeInd& other)
{
    this->arrivalClockTime = other.arrivalClockTime;
}

void GptpIngressTimeInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->arrivalClockTime);
}

void GptpIngressTimeInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->arrivalClockTime);
}

clocktime_t GptpIngressTimeInd::getArrivalClockTime() const
{
    return this->arrivalClockTime;
}

void GptpIngressTimeInd::setArrivalClockTime(clocktime_t arrivalClockTime)
{
    this->arrivalClockTime = arrivalClockTime;
}

class GptpIngressTimeIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_arrivalClockTime,
    };
  public:
    GptpIngressTimeIndDescriptor();
    virtual ~GptpIngressTimeIndDescriptor();

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

Register_ClassDescriptor(GptpIngressTimeIndDescriptor)

GptpIngressTimeIndDescriptor::GptpIngressTimeIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GptpIngressTimeInd)), "inet::TagBase")
{
    propertyNames = nullptr;
}

GptpIngressTimeIndDescriptor::~GptpIngressTimeIndDescriptor()
{
    delete[] propertyNames;
}

bool GptpIngressTimeIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GptpIngressTimeInd *>(obj)!=nullptr;
}

const char **GptpIngressTimeIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GptpIngressTimeIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GptpIngressTimeIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int GptpIngressTimeIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_arrivalClockTime
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *GptpIngressTimeIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "arrivalClockTime",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int GptpIngressTimeIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "arrivalClockTime") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *GptpIngressTimeIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::clocktime_t",    // FIELD_arrivalClockTime
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **GptpIngressTimeIndDescriptor::getFieldPropertyNames(int field) const
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

const char *GptpIngressTimeIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GptpIngressTimeIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GptpIngressTimeIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GptpIngressTimeInd'", field);
    }
}

const char *GptpIngressTimeIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GptpIngressTimeIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_arrivalClockTime: return simtime2string(CLOCKTIME_AS_SIMTIME(pp->getArrivalClockTime()));
        default: return "";
    }
}

void GptpIngressTimeIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpIngressTimeInd'", field);
    }
}

omnetpp::cValue GptpIngressTimeIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_arrivalClockTime: return cValue(pp->getArrivalClockTime().dbl(),"s");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GptpIngressTimeInd' as cValue -- field index out of range?", field);
    }
}

void GptpIngressTimeIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpIngressTimeInd'", field);
    }
}

const char *GptpIngressTimeIndDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GptpIngressTimeIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GptpIngressTimeIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GptpIngressTimeInd *pp = omnetpp::fromAnyPtr<GptpIngressTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GptpIngressTimeInd'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

