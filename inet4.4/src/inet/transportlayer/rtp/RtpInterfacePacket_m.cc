//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtpInterfacePacket.msg.
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
#include "RtpInterfacePacket_m.h"

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

Register_Enum(inet::rtp::RtpIfpType, (inet::rtp::RtpIfpType::RTP_IFP_ENTER_SESSION, inet::rtp::RtpIfpType::RTP_IFP_SESSION_ENTERED, inet::rtp::RtpIfpType::RTP_IFP_CREATE_SENDER_MODULE, inet::rtp::RtpIfpType::RTP_IFP_SENDER_MODULE_CREATED, inet::rtp::RtpIfpType::RTP_IFP_DELETE_SENDER_MODULE, inet::rtp::RtpIfpType::RTP_IFP_SENDER_MODULE_DELETED, inet::rtp::RtpIfpType::RTP_IFP_SENDER_CONTROL, inet::rtp::RtpIfpType::RTP_IFP_SENDER_STATUS, inet::rtp::RtpIfpType::RTP_IFP_LEAVE_SESSION, inet::rtp::RtpIfpType::RTP_IFP_SESSION_LEFT));

Register_Class(RtpControlMsg)

RtpControlMsg::RtpControlMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RtpControlMsg::RtpControlMsg(const RtpControlMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RtpControlMsg::~RtpControlMsg()
{
}

RtpControlMsg& RtpControlMsg::operator=(const RtpControlMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RtpControlMsg::copy(const RtpControlMsg& other)
{
}

void RtpControlMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
}

void RtpControlMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
}

class RtpControlMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpControlMsgDescriptor();
    virtual ~RtpControlMsgDescriptor();

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

Register_ClassDescriptor(RtpControlMsgDescriptor)

RtpControlMsgDescriptor::RtpControlMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpControlMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RtpControlMsgDescriptor::~RtpControlMsgDescriptor()
{
    delete[] propertyNames;
}

bool RtpControlMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpControlMsg *>(obj)!=nullptr;
}

const char **RtpControlMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpControlMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpControlMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpControlMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpControlMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpControlMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpControlMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpControlMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpControlMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpControlMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpControlMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpControlMsg'", field);
    }
}

const char *RtpControlMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpControlMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpControlMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlMsg'", field);
    }
}

omnetpp::cValue RtpControlMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpControlMsg' as cValue -- field index out of range?", field);
    }
}

void RtpControlMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlMsg'", field);
    }
}

const char *RtpControlMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpControlMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpControlMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlMsg *pp = omnetpp::fromAnyPtr<RtpControlMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlMsg'", field);
    }
}

Register_Class(RtpControlInfo)

RtpControlInfo::RtpControlInfo() : ::omnetpp::cObject()
{
}

RtpControlInfo::RtpControlInfo(const RtpControlInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

RtpControlInfo::~RtpControlInfo()
{
}

RtpControlInfo& RtpControlInfo::operator=(const RtpControlInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void RtpControlInfo::copy(const RtpControlInfo& other)
{
    this->type = other.type;
}

void RtpControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
}

void RtpControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
}

RtpIfpType RtpControlInfo::getType() const
{
    return this->type;
}

void RtpControlInfo::setType(RtpIfpType type)
{
    this->type = type;
}

class RtpControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
    };
  public:
    RtpControlInfoDescriptor();
    virtual ~RtpControlInfoDescriptor();

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

Register_ClassDescriptor(RtpControlInfoDescriptor)

RtpControlInfoDescriptor::RtpControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpControlInfo)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

RtpControlInfoDescriptor::~RtpControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool RtpControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpControlInfo *>(obj)!=nullptr;
}

const char **RtpControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RtpControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RtpControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RtpControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::rtp::RtpIfpType",    // FIELD_type
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpControlInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::rtp::RtpIfpType";
            return nullptr;
        default: return nullptr;
    }
}

int RtpControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpControlInfo'", field);
    }
}

const char *RtpControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::rtp::RtpIfpType");
        default: return "";
    }
}

void RtpControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlInfo'", field);
    }
}

omnetpp::cValue RtpControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpControlInfo' as cValue -- field index out of range?", field);
    }
}

void RtpControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlInfo'", field);
    }
}

const char *RtpControlInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpControlInfo *pp = omnetpp::fromAnyPtr<RtpControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpControlInfo'", field);
    }
}

Register_Class(RtpSessionControlInfo)

RtpSessionControlInfo::RtpSessionControlInfo() : ::inet::rtp::RtpControlInfo()
{
}

RtpSessionControlInfo::RtpSessionControlInfo(const RtpSessionControlInfo& other) : ::inet::rtp::RtpControlInfo(other)
{
    copy(other);
}

RtpSessionControlInfo::~RtpSessionControlInfo()
{
}

RtpSessionControlInfo& RtpSessionControlInfo::operator=(const RtpSessionControlInfo& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpSessionControlInfo::copy(const RtpSessionControlInfo& other)
{
    this->ssrc = other.ssrc;
}

void RtpSessionControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpControlInfo::parsimPack(b);
    doParsimPacking(b,this->ssrc);
}

void RtpSessionControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->ssrc);
}

uint32_t RtpSessionControlInfo::getSsrc() const
{
    return this->ssrc;
}

void RtpSessionControlInfo::setSsrc(uint32_t ssrc)
{
    this->ssrc = ssrc;
}

class RtpSessionControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ssrc,
    };
  public:
    RtpSessionControlInfoDescriptor();
    virtual ~RtpSessionControlInfoDescriptor();

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

Register_ClassDescriptor(RtpSessionControlInfoDescriptor)

RtpSessionControlInfoDescriptor::RtpSessionControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpSessionControlInfo)), "inet::rtp::RtpControlInfo")
{
    propertyNames = nullptr;
}

RtpSessionControlInfoDescriptor::~RtpSessionControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool RtpSessionControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpSessionControlInfo *>(obj)!=nullptr;
}

const char **RtpSessionControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpSessionControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpSessionControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RtpSessionControlInfoDescriptor::getFieldTypeFlags(int field) const
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

const char *RtpSessionControlInfoDescriptor::getFieldName(int field) const
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

int RtpSessionControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpSessionControlInfoDescriptor::getFieldTypeString(int field) const
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

const char **RtpSessionControlInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpSessionControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpSessionControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpSessionControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpSessionControlInfo'", field);
    }
}

const char *RtpSessionControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpSessionControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        default: return "";
    }
}

void RtpSessionControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSessionControlInfo'", field);
    }
}

omnetpp::cValue RtpSessionControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpSessionControlInfo' as cValue -- field index out of range?", field);
    }
}

void RtpSessionControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSessionControlInfo'", field);
    }
}

const char *RtpSessionControlInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpSessionControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpSessionControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSessionControlInfo *pp = omnetpp::fromAnyPtr<RtpSessionControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSessionControlInfo'", field);
    }
}

Register_Class(RtpCiEnterSession)

RtpCiEnterSession::RtpCiEnterSession() : ::inet::rtp::RtpControlInfo()
{
    this->setType(RTP_IFP_ENTER_SESSION);

}

RtpCiEnterSession::RtpCiEnterSession(const RtpCiEnterSession& other) : ::inet::rtp::RtpControlInfo(other)
{
    copy(other);
}

RtpCiEnterSession::~RtpCiEnterSession()
{
}

RtpCiEnterSession& RtpCiEnterSession::operator=(const RtpCiEnterSession& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiEnterSession::copy(const RtpCiEnterSession& other)
{
    this->commonName = other.commonName;
    this->profileName = other.profileName;
    this->bandwidth = other.bandwidth;
    this->destinationAddress = other.destinationAddress;
    this->port = other.port;
}

void RtpCiEnterSession::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpControlInfo::parsimPack(b);
    doParsimPacking(b,this->commonName);
    doParsimPacking(b,this->profileName);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->port);
}

void RtpCiEnterSession::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->commonName);
    doParsimUnpacking(b,this->profileName);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->port);
}

const char * RtpCiEnterSession::getCommonName() const
{
    return this->commonName.c_str();
}

void RtpCiEnterSession::setCommonName(const char * commonName)
{
    this->commonName = commonName;
}

const char * RtpCiEnterSession::getProfileName() const
{
    return this->profileName.c_str();
}

void RtpCiEnterSession::setProfileName(const char * profileName)
{
    this->profileName = profileName;
}

int RtpCiEnterSession::getBandwidth() const
{
    return this->bandwidth;
}

void RtpCiEnterSession::setBandwidth(int bandwidth)
{
    this->bandwidth = bandwidth;
}

const ::inet::Ipv4Address& RtpCiEnterSession::getDestinationAddress() const
{
    return this->destinationAddress;
}

void RtpCiEnterSession::setDestinationAddress(const ::inet::Ipv4Address& destinationAddress)
{
    this->destinationAddress = destinationAddress;
}

int RtpCiEnterSession::getPort() const
{
    return this->port;
}

void RtpCiEnterSession::setPort(int port)
{
    this->port = port;
}

class RtpCiEnterSessionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_commonName,
        FIELD_profileName,
        FIELD_bandwidth,
        FIELD_destinationAddress,
        FIELD_port,
    };
  public:
    RtpCiEnterSessionDescriptor();
    virtual ~RtpCiEnterSessionDescriptor();

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

Register_ClassDescriptor(RtpCiEnterSessionDescriptor)

RtpCiEnterSessionDescriptor::RtpCiEnterSessionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiEnterSession)), "inet::rtp::RtpControlInfo")
{
    propertyNames = nullptr;
}

RtpCiEnterSessionDescriptor::~RtpCiEnterSessionDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiEnterSessionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiEnterSession *>(obj)!=nullptr;
}

const char **RtpCiEnterSessionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiEnterSessionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiEnterSessionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RtpCiEnterSessionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_commonName
        FD_ISEDITABLE,    // FIELD_profileName
        FD_ISEDITABLE,    // FIELD_bandwidth
        0,    // FIELD_destinationAddress
        FD_ISEDITABLE,    // FIELD_port
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RtpCiEnterSessionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "commonName",
        "profileName",
        "bandwidth",
        "destinationAddress",
        "port",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RtpCiEnterSessionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "commonName") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "profileName") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "destinationAddress") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "port") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiEnterSessionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_commonName
        "string",    // FIELD_profileName
        "int",    // FIELD_bandwidth
        "inet::Ipv4Address",    // FIELD_destinationAddress
        "int",    // FIELD_port
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpCiEnterSessionDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiEnterSessionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiEnterSessionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiEnterSessionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiEnterSession'", field);
    }
}

const char *RtpCiEnterSessionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiEnterSessionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: return oppstring2string(pp->getCommonName());
        case FIELD_profileName: return oppstring2string(pp->getProfileName());
        case FIELD_bandwidth: return long2string(pp->getBandwidth());
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_port: return long2string(pp->getPort());
        default: return "";
    }
}

void RtpCiEnterSessionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: pp->setCommonName((value)); break;
        case FIELD_profileName: pp->setProfileName((value)); break;
        case FIELD_bandwidth: pp->setBandwidth(string2long(value)); break;
        case FIELD_port: pp->setPort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiEnterSession'", field);
    }
}

omnetpp::cValue RtpCiEnterSessionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: return pp->getCommonName();
        case FIELD_profileName: return pp->getProfileName();
        case FIELD_bandwidth: return pp->getBandwidth();
        case FIELD_destinationAddress: return omnetpp::toAnyPtr(&pp->getDestinationAddress()); break;
        case FIELD_port: return pp->getPort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiEnterSession' as cValue -- field index out of range?", field);
    }
}

void RtpCiEnterSessionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        case FIELD_commonName: pp->setCommonName(value.stringValue()); break;
        case FIELD_profileName: pp->setProfileName(value.stringValue()); break;
        case FIELD_bandwidth: pp->setBandwidth(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_port: pp->setPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiEnterSession'", field);
    }
}

const char *RtpCiEnterSessionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpCiEnterSessionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        case FIELD_destinationAddress: return omnetpp::toAnyPtr(&pp->getDestinationAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiEnterSessionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiEnterSession *pp = omnetpp::fromAnyPtr<RtpCiEnterSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiEnterSession'", field);
    }
}

Register_Class(RtpCiSessionEntered)

RtpCiSessionEntered::RtpCiSessionEntered() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_SESSION_ENTERED);
}

RtpCiSessionEntered::RtpCiSessionEntered(const RtpCiSessionEntered& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiSessionEntered::~RtpCiSessionEntered()
{
}

RtpCiSessionEntered& RtpCiSessionEntered::operator=(const RtpCiSessionEntered& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSessionEntered::copy(const RtpCiSessionEntered& other)
{
}

void RtpCiSessionEntered::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
}

void RtpCiSessionEntered::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
}

class RtpCiSessionEnteredDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiSessionEnteredDescriptor();
    virtual ~RtpCiSessionEnteredDescriptor();

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

Register_ClassDescriptor(RtpCiSessionEnteredDescriptor)

RtpCiSessionEnteredDescriptor::RtpCiSessionEnteredDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSessionEntered)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSessionEnteredDescriptor::~RtpCiSessionEnteredDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSessionEnteredDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSessionEntered *>(obj)!=nullptr;
}

const char **RtpCiSessionEnteredDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSessionEnteredDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSessionEnteredDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiSessionEnteredDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiSessionEnteredDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiSessionEnteredDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSessionEnteredDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiSessionEnteredDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiSessionEnteredDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiSessionEnteredDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSessionEnteredDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSessionEntered'", field);
    }
}

const char *RtpCiSessionEnteredDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSessionEnteredDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiSessionEnteredDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionEntered'", field);
    }
}

omnetpp::cValue RtpCiSessionEnteredDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSessionEntered' as cValue -- field index out of range?", field);
    }
}

void RtpCiSessionEnteredDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionEntered'", field);
    }
}

const char *RtpCiSessionEnteredDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiSessionEnteredDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSessionEnteredDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionEntered *pp = omnetpp::fromAnyPtr<RtpCiSessionEntered>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionEntered'", field);
    }
}

Register_Class(RtpCiSenderControl)

RtpCiSenderControl::RtpCiSenderControl() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_SENDER_CONTROL);

}

RtpCiSenderControl::RtpCiSenderControl(const RtpCiSenderControl& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiSenderControl::~RtpCiSenderControl()
{
}

RtpCiSenderControl& RtpCiSenderControl::operator=(const RtpCiSenderControl& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSenderControl::copy(const RtpCiSenderControl& other)
{
    this->command = other.command;
    this->commandParameter1 = other.commandParameter1;
    this->commandParameter2 = other.commandParameter2;
}

void RtpCiSenderControl::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
    doParsimPacking(b,this->command);
    doParsimPacking(b,this->commandParameter1);
    doParsimPacking(b,this->commandParameter2);
}

void RtpCiSenderControl::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
    doParsimUnpacking(b,this->commandParameter1);
    doParsimUnpacking(b,this->commandParameter2);
}

RtpSenderControlMessageCommands RtpCiSenderControl::getCommand() const
{
    return this->command;
}

void RtpCiSenderControl::setCommand(RtpSenderControlMessageCommands command)
{
    this->command = command;
}

float RtpCiSenderControl::getCommandParameter1() const
{
    return this->commandParameter1;
}

void RtpCiSenderControl::setCommandParameter1(float commandParameter1)
{
    this->commandParameter1 = commandParameter1;
}

float RtpCiSenderControl::getCommandParameter2() const
{
    return this->commandParameter2;
}

void RtpCiSenderControl::setCommandParameter2(float commandParameter2)
{
    this->commandParameter2 = commandParameter2;
}

class RtpCiSenderControlDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_command,
        FIELD_commandParameter1,
        FIELD_commandParameter2,
    };
  public:
    RtpCiSenderControlDescriptor();
    virtual ~RtpCiSenderControlDescriptor();

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

Register_ClassDescriptor(RtpCiSenderControlDescriptor)

RtpCiSenderControlDescriptor::RtpCiSenderControlDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSenderControl)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSenderControlDescriptor::~RtpCiSenderControlDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSenderControlDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSenderControl *>(obj)!=nullptr;
}

const char **RtpCiSenderControlDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSenderControlDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSenderControlDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RtpCiSenderControlDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_command
        FD_ISEDITABLE,    // FIELD_commandParameter1
        FD_ISEDITABLE,    // FIELD_commandParameter2
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RtpCiSenderControlDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "command",
        "commandParameter1",
        "commandParameter2",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RtpCiSenderControlDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "command") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "commandParameter1") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "commandParameter2") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSenderControlDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::rtp::RtpSenderControlMessageCommands",    // FIELD_command
        "float",    // FIELD_commandParameter1
        "float",    // FIELD_commandParameter2
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpCiSenderControlDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_command: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RtpCiSenderControlDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_command:
            if (!strcmp(propertyName, "enum")) return "inet::rtp::RtpSenderControlMessageCommands";
            return nullptr;
        default: return nullptr;
    }
}

int RtpCiSenderControlDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSenderControlDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSenderControl'", field);
    }
}

const char *RtpCiSenderControlDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSenderControlDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        case FIELD_command: return enum2string(pp->getCommand(), "inet::rtp::RtpSenderControlMessageCommands");
        case FIELD_commandParameter1: return double2string(pp->getCommandParameter1());
        case FIELD_commandParameter2: return double2string(pp->getCommandParameter2());
        default: return "";
    }
}

void RtpCiSenderControlDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        case FIELD_command: pp->setCommand((inet::rtp::RtpSenderControlMessageCommands)string2enum(value, "inet::rtp::RtpSenderControlMessageCommands")); break;
        case FIELD_commandParameter1: pp->setCommandParameter1(string2double(value)); break;
        case FIELD_commandParameter2: pp->setCommandParameter2(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderControl'", field);
    }
}

omnetpp::cValue RtpCiSenderControlDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        case FIELD_command: return static_cast<int>(pp->getCommand());
        case FIELD_commandParameter1: return (double)(pp->getCommandParameter1());
        case FIELD_commandParameter2: return (double)(pp->getCommandParameter2());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSenderControl' as cValue -- field index out of range?", field);
    }
}

void RtpCiSenderControlDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        case FIELD_command: pp->setCommand(static_cast<inet::rtp::RtpSenderControlMessageCommands>(value.intValue())); break;
        case FIELD_commandParameter1: pp->setCommandParameter1(static_cast<float>(value.doubleValue())); break;
        case FIELD_commandParameter2: pp->setCommandParameter2(static_cast<float>(value.doubleValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderControl'", field);
    }
}

const char *RtpCiSenderControlDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpCiSenderControlDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSenderControlDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderControl *pp = omnetpp::fromAnyPtr<RtpCiSenderControl>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderControl'", field);
    }
}

Register_Class(RtpCiSenderStatus)

RtpCiSenderStatus::RtpCiSenderStatus() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_SENDER_STATUS);

}

RtpCiSenderStatus::RtpCiSenderStatus(const RtpCiSenderStatus& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiSenderStatus::~RtpCiSenderStatus()
{
}

RtpCiSenderStatus& RtpCiSenderStatus::operator=(const RtpCiSenderStatus& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSenderStatus::copy(const RtpCiSenderStatus& other)
{
    this->status = other.status;
    this->timeStamp = other.timeStamp;
}

void RtpCiSenderStatus::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->timeStamp);
}

void RtpCiSenderStatus::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->timeStamp);
}

RtpSenderStatus RtpCiSenderStatus::getStatus() const
{
    return this->status;
}

void RtpCiSenderStatus::setStatus(RtpSenderStatus status)
{
    this->status = status;
}

uint32_t RtpCiSenderStatus::getTimeStamp() const
{
    return this->timeStamp;
}

void RtpCiSenderStatus::setTimeStamp(uint32_t timeStamp)
{
    this->timeStamp = timeStamp;
}

class RtpCiSenderStatusDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_status,
        FIELD_timeStamp,
    };
  public:
    RtpCiSenderStatusDescriptor();
    virtual ~RtpCiSenderStatusDescriptor();

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

Register_ClassDescriptor(RtpCiSenderStatusDescriptor)

RtpCiSenderStatusDescriptor::RtpCiSenderStatusDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSenderStatus)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSenderStatusDescriptor::~RtpCiSenderStatusDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSenderStatusDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSenderStatus *>(obj)!=nullptr;
}

const char **RtpCiSenderStatusDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSenderStatusDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSenderStatusDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RtpCiSenderStatusDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_timeStamp
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RtpCiSenderStatusDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "status",
        "timeStamp",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RtpCiSenderStatusDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timeStamp") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSenderStatusDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::rtp::RtpSenderStatus",    // FIELD_status
        "uint32_t",    // FIELD_timeStamp
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpCiSenderStatusDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RtpCiSenderStatusDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_status:
            if (!strcmp(propertyName, "enum")) return "inet::rtp::RtpSenderStatus";
            return nullptr;
        default: return nullptr;
    }
}

int RtpCiSenderStatusDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSenderStatusDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSenderStatus'", field);
    }
}

const char *RtpCiSenderStatusDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSenderStatusDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        case FIELD_status: return enum2string(pp->getStatus(), "inet::rtp::RtpSenderStatus");
        case FIELD_timeStamp: return ulong2string(pp->getTimeStamp());
        default: return "";
    }
}

void RtpCiSenderStatusDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus((inet::rtp::RtpSenderStatus)string2enum(value, "inet::rtp::RtpSenderStatus")); break;
        case FIELD_timeStamp: pp->setTimeStamp(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderStatus'", field);
    }
}

omnetpp::cValue RtpCiSenderStatusDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        case FIELD_status: return static_cast<int>(pp->getStatus());
        case FIELD_timeStamp: return (omnetpp::intval_t)(pp->getTimeStamp());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSenderStatus' as cValue -- field index out of range?", field);
    }
}

void RtpCiSenderStatusDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(static_cast<inet::rtp::RtpSenderStatus>(value.intValue())); break;
        case FIELD_timeStamp: pp->setTimeStamp(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderStatus'", field);
    }
}

const char *RtpCiSenderStatusDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpCiSenderStatusDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSenderStatusDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderStatus *pp = omnetpp::fromAnyPtr<RtpCiSenderStatus>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderStatus'", field);
    }
}

Register_Class(RtpCiLeaveSession)

RtpCiLeaveSession::RtpCiLeaveSession() : ::inet::rtp::RtpControlInfo()
{
    this->setType(RTP_IFP_LEAVE_SESSION);
}

RtpCiLeaveSession::RtpCiLeaveSession(const RtpCiLeaveSession& other) : ::inet::rtp::RtpControlInfo(other)
{
    copy(other);
}

RtpCiLeaveSession::~RtpCiLeaveSession()
{
}

RtpCiLeaveSession& RtpCiLeaveSession::operator=(const RtpCiLeaveSession& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiLeaveSession::copy(const RtpCiLeaveSession& other)
{
}

void RtpCiLeaveSession::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpControlInfo::parsimPack(b);
}

void RtpCiLeaveSession::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpControlInfo::parsimUnpack(b);
}

class RtpCiLeaveSessionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiLeaveSessionDescriptor();
    virtual ~RtpCiLeaveSessionDescriptor();

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

Register_ClassDescriptor(RtpCiLeaveSessionDescriptor)

RtpCiLeaveSessionDescriptor::RtpCiLeaveSessionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiLeaveSession)), "inet::rtp::RtpControlInfo")
{
    propertyNames = nullptr;
}

RtpCiLeaveSessionDescriptor::~RtpCiLeaveSessionDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiLeaveSessionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiLeaveSession *>(obj)!=nullptr;
}

const char **RtpCiLeaveSessionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiLeaveSessionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiLeaveSessionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiLeaveSessionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiLeaveSessionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiLeaveSessionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiLeaveSessionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiLeaveSessionDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiLeaveSessionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiLeaveSessionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiLeaveSessionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiLeaveSession'", field);
    }
}

const char *RtpCiLeaveSessionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiLeaveSessionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiLeaveSessionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiLeaveSession'", field);
    }
}

omnetpp::cValue RtpCiLeaveSessionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiLeaveSession' as cValue -- field index out of range?", field);
    }
}

void RtpCiLeaveSessionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiLeaveSession'", field);
    }
}

const char *RtpCiLeaveSessionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiLeaveSessionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiLeaveSessionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiLeaveSession *pp = omnetpp::fromAnyPtr<RtpCiLeaveSession>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiLeaveSession'", field);
    }
}

Register_Class(RtpCiSessionLeft)

RtpCiSessionLeft::RtpCiSessionLeft() : ::inet::rtp::RtpControlInfo()
{
    this->setType(RTP_IFP_SESSION_LEFT);
}

RtpCiSessionLeft::RtpCiSessionLeft(const RtpCiSessionLeft& other) : ::inet::rtp::RtpControlInfo(other)
{
    copy(other);
}

RtpCiSessionLeft::~RtpCiSessionLeft()
{
}

RtpCiSessionLeft& RtpCiSessionLeft::operator=(const RtpCiSessionLeft& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSessionLeft::copy(const RtpCiSessionLeft& other)
{
}

void RtpCiSessionLeft::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpControlInfo::parsimPack(b);
}

void RtpCiSessionLeft::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpControlInfo::parsimUnpack(b);
}

class RtpCiSessionLeftDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiSessionLeftDescriptor();
    virtual ~RtpCiSessionLeftDescriptor();

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

Register_ClassDescriptor(RtpCiSessionLeftDescriptor)

RtpCiSessionLeftDescriptor::RtpCiSessionLeftDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSessionLeft)), "inet::rtp::RtpControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSessionLeftDescriptor::~RtpCiSessionLeftDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSessionLeftDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSessionLeft *>(obj)!=nullptr;
}

const char **RtpCiSessionLeftDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSessionLeftDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSessionLeftDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiSessionLeftDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiSessionLeftDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiSessionLeftDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSessionLeftDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiSessionLeftDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiSessionLeftDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiSessionLeftDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSessionLeftDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSessionLeft'", field);
    }
}

const char *RtpCiSessionLeftDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSessionLeftDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiSessionLeftDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionLeft'", field);
    }
}

omnetpp::cValue RtpCiSessionLeftDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSessionLeft' as cValue -- field index out of range?", field);
    }
}

void RtpCiSessionLeftDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionLeft'", field);
    }
}

const char *RtpCiSessionLeftDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiSessionLeftDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSessionLeftDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSessionLeft *pp = omnetpp::fromAnyPtr<RtpCiSessionLeft>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSessionLeft'", field);
    }
}

Register_Class(RtpCiCreateSenderModule)

RtpCiCreateSenderModule::RtpCiCreateSenderModule() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_CREATE_SENDER_MODULE);

}

RtpCiCreateSenderModule::RtpCiCreateSenderModule(const RtpCiCreateSenderModule& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiCreateSenderModule::~RtpCiCreateSenderModule()
{
}

RtpCiCreateSenderModule& RtpCiCreateSenderModule::operator=(const RtpCiCreateSenderModule& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiCreateSenderModule::copy(const RtpCiCreateSenderModule& other)
{
    this->payloadType = other.payloadType;
    this->fileName = other.fileName;
}

void RtpCiCreateSenderModule::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
    doParsimPacking(b,this->payloadType);
    doParsimPacking(b,this->fileName);
}

void RtpCiCreateSenderModule::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
    doParsimUnpacking(b,this->payloadType);
    doParsimUnpacking(b,this->fileName);
}

int RtpCiCreateSenderModule::getPayloadType() const
{
    return this->payloadType;
}

void RtpCiCreateSenderModule::setPayloadType(int payloadType)
{
    this->payloadType = payloadType;
}

const char * RtpCiCreateSenderModule::getFileName() const
{
    return this->fileName.c_str();
}

void RtpCiCreateSenderModule::setFileName(const char * fileName)
{
    this->fileName = fileName;
}

class RtpCiCreateSenderModuleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_payloadType,
        FIELD_fileName,
    };
  public:
    RtpCiCreateSenderModuleDescriptor();
    virtual ~RtpCiCreateSenderModuleDescriptor();

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

Register_ClassDescriptor(RtpCiCreateSenderModuleDescriptor)

RtpCiCreateSenderModuleDescriptor::RtpCiCreateSenderModuleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiCreateSenderModule)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiCreateSenderModuleDescriptor::~RtpCiCreateSenderModuleDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiCreateSenderModuleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiCreateSenderModule *>(obj)!=nullptr;
}

const char **RtpCiCreateSenderModuleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiCreateSenderModuleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiCreateSenderModuleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RtpCiCreateSenderModuleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_payloadType
        FD_ISEDITABLE,    // FIELD_fileName
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RtpCiCreateSenderModuleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "payloadType",
        "fileName",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RtpCiCreateSenderModuleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "payloadType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fileName") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiCreateSenderModuleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_payloadType
        "string",    // FIELD_fileName
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpCiCreateSenderModuleDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiCreateSenderModuleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiCreateSenderModuleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiCreateSenderModuleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiCreateSenderModule'", field);
    }
}

const char *RtpCiCreateSenderModuleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiCreateSenderModuleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        case FIELD_payloadType: return long2string(pp->getPayloadType());
        case FIELD_fileName: return oppstring2string(pp->getFileName());
        default: return "";
    }
}

void RtpCiCreateSenderModuleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        case FIELD_payloadType: pp->setPayloadType(string2long(value)); break;
        case FIELD_fileName: pp->setFileName((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiCreateSenderModule'", field);
    }
}

omnetpp::cValue RtpCiCreateSenderModuleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        case FIELD_payloadType: return pp->getPayloadType();
        case FIELD_fileName: return pp->getFileName();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiCreateSenderModule' as cValue -- field index out of range?", field);
    }
}

void RtpCiCreateSenderModuleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        case FIELD_payloadType: pp->setPayloadType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fileName: pp->setFileName(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiCreateSenderModule'", field);
    }
}

const char *RtpCiCreateSenderModuleDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpCiCreateSenderModuleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiCreateSenderModuleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiCreateSenderModule *pp = omnetpp::fromAnyPtr<RtpCiCreateSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiCreateSenderModule'", field);
    }
}

Register_Class(RtpCiSenderModuleCreated)

RtpCiSenderModuleCreated::RtpCiSenderModuleCreated() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_SENDER_MODULE_CREATED);
}

RtpCiSenderModuleCreated::RtpCiSenderModuleCreated(const RtpCiSenderModuleCreated& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiSenderModuleCreated::~RtpCiSenderModuleCreated()
{
}

RtpCiSenderModuleCreated& RtpCiSenderModuleCreated::operator=(const RtpCiSenderModuleCreated& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSenderModuleCreated::copy(const RtpCiSenderModuleCreated& other)
{
}

void RtpCiSenderModuleCreated::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
}

void RtpCiSenderModuleCreated::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
}

class RtpCiSenderModuleCreatedDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiSenderModuleCreatedDescriptor();
    virtual ~RtpCiSenderModuleCreatedDescriptor();

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

Register_ClassDescriptor(RtpCiSenderModuleCreatedDescriptor)

RtpCiSenderModuleCreatedDescriptor::RtpCiSenderModuleCreatedDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSenderModuleCreated)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSenderModuleCreatedDescriptor::~RtpCiSenderModuleCreatedDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSenderModuleCreatedDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSenderModuleCreated *>(obj)!=nullptr;
}

const char **RtpCiSenderModuleCreatedDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSenderModuleCreatedDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSenderModuleCreatedDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiSenderModuleCreatedDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiSenderModuleCreatedDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiSenderModuleCreatedDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSenderModuleCreatedDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiSenderModuleCreatedDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiSenderModuleCreatedDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiSenderModuleCreatedDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSenderModuleCreatedDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSenderModuleCreated'", field);
    }
}

const char *RtpCiSenderModuleCreatedDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSenderModuleCreatedDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiSenderModuleCreatedDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleCreated'", field);
    }
}

omnetpp::cValue RtpCiSenderModuleCreatedDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSenderModuleCreated' as cValue -- field index out of range?", field);
    }
}

void RtpCiSenderModuleCreatedDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleCreated'", field);
    }
}

const char *RtpCiSenderModuleCreatedDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiSenderModuleCreatedDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSenderModuleCreatedDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleCreated *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleCreated>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleCreated'", field);
    }
}

Register_Class(RtpCiDeleteSenderModule)

RtpCiDeleteSenderModule::RtpCiDeleteSenderModule() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_DELETE_SENDER_MODULE);
}

RtpCiDeleteSenderModule::RtpCiDeleteSenderModule(const RtpCiDeleteSenderModule& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiDeleteSenderModule::~RtpCiDeleteSenderModule()
{
}

RtpCiDeleteSenderModule& RtpCiDeleteSenderModule::operator=(const RtpCiDeleteSenderModule& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiDeleteSenderModule::copy(const RtpCiDeleteSenderModule& other)
{
}

void RtpCiDeleteSenderModule::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
}

void RtpCiDeleteSenderModule::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
}

class RtpCiDeleteSenderModuleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiDeleteSenderModuleDescriptor();
    virtual ~RtpCiDeleteSenderModuleDescriptor();

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

Register_ClassDescriptor(RtpCiDeleteSenderModuleDescriptor)

RtpCiDeleteSenderModuleDescriptor::RtpCiDeleteSenderModuleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiDeleteSenderModule)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiDeleteSenderModuleDescriptor::~RtpCiDeleteSenderModuleDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiDeleteSenderModuleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiDeleteSenderModule *>(obj)!=nullptr;
}

const char **RtpCiDeleteSenderModuleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiDeleteSenderModuleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiDeleteSenderModuleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiDeleteSenderModuleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiDeleteSenderModuleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiDeleteSenderModuleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiDeleteSenderModuleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiDeleteSenderModuleDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiDeleteSenderModuleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiDeleteSenderModuleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiDeleteSenderModuleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiDeleteSenderModule'", field);
    }
}

const char *RtpCiDeleteSenderModuleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiDeleteSenderModuleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiDeleteSenderModuleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiDeleteSenderModule'", field);
    }
}

omnetpp::cValue RtpCiDeleteSenderModuleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiDeleteSenderModule' as cValue -- field index out of range?", field);
    }
}

void RtpCiDeleteSenderModuleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiDeleteSenderModule'", field);
    }
}

const char *RtpCiDeleteSenderModuleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiDeleteSenderModuleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiDeleteSenderModuleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiDeleteSenderModule *pp = omnetpp::fromAnyPtr<RtpCiDeleteSenderModule>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiDeleteSenderModule'", field);
    }
}

Register_Class(RtpCiSenderModuleDeleted)

RtpCiSenderModuleDeleted::RtpCiSenderModuleDeleted() : ::inet::rtp::RtpSessionControlInfo()
{
    this->setType(RTP_IFP_SENDER_MODULE_DELETED);
}

RtpCiSenderModuleDeleted::RtpCiSenderModuleDeleted(const RtpCiSenderModuleDeleted& other) : ::inet::rtp::RtpSessionControlInfo(other)
{
    copy(other);
}

RtpCiSenderModuleDeleted::~RtpCiSenderModuleDeleted()
{
}

RtpCiSenderModuleDeleted& RtpCiSenderModuleDeleted::operator=(const RtpCiSenderModuleDeleted& other)
{
    if (this == &other) return *this;
    ::inet::rtp::RtpSessionControlInfo::operator=(other);
    copy(other);
    return *this;
}

void RtpCiSenderModuleDeleted::copy(const RtpCiSenderModuleDeleted& other)
{
}

void RtpCiSenderModuleDeleted::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::rtp::RtpSessionControlInfo::parsimPack(b);
}

void RtpCiSenderModuleDeleted::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::rtp::RtpSessionControlInfo::parsimUnpack(b);
}

class RtpCiSenderModuleDeletedDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    RtpCiSenderModuleDeletedDescriptor();
    virtual ~RtpCiSenderModuleDeletedDescriptor();

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

Register_ClassDescriptor(RtpCiSenderModuleDeletedDescriptor)

RtpCiSenderModuleDeletedDescriptor::RtpCiSenderModuleDeletedDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpCiSenderModuleDeleted)), "inet::rtp::RtpSessionControlInfo")
{
    propertyNames = nullptr;
}

RtpCiSenderModuleDeletedDescriptor::~RtpCiSenderModuleDeletedDescriptor()
{
    delete[] propertyNames;
}

bool RtpCiSenderModuleDeletedDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpCiSenderModuleDeleted *>(obj)!=nullptr;
}

const char **RtpCiSenderModuleDeletedDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpCiSenderModuleDeletedDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpCiSenderModuleDeletedDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int RtpCiSenderModuleDeletedDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *RtpCiSenderModuleDeletedDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int RtpCiSenderModuleDeletedDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *RtpCiSenderModuleDeletedDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **RtpCiSenderModuleDeletedDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpCiSenderModuleDeletedDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpCiSenderModuleDeletedDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpCiSenderModuleDeletedDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpCiSenderModuleDeleted'", field);
    }
}

const char *RtpCiSenderModuleDeletedDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpCiSenderModuleDeletedDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void RtpCiSenderModuleDeletedDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleDeleted'", field);
    }
}

omnetpp::cValue RtpCiSenderModuleDeletedDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpCiSenderModuleDeleted' as cValue -- field index out of range?", field);
    }
}

void RtpCiSenderModuleDeletedDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleDeleted'", field);
    }
}

const char *RtpCiSenderModuleDeletedDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr RtpCiSenderModuleDeletedDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpCiSenderModuleDeletedDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpCiSenderModuleDeleted *pp = omnetpp::fromAnyPtr<RtpCiSenderModuleDeleted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpCiSenderModuleDeleted'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

