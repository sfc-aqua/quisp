//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/RsvpHelloMsg.msg.
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
#include "RsvpHelloMsg_m.h"

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

Register_Class(RsvpHelloMsg)

RsvpHelloMsg::RsvpHelloMsg() : ::inet::RsvpMessage()
{
    this->setRsvpKind(HELLO_MESSAGE);

}

RsvpHelloMsg::RsvpHelloMsg(const RsvpHelloMsg& other) : ::inet::RsvpMessage(other)
{
    copy(other);
}

RsvpHelloMsg::~RsvpHelloMsg()
{
}

RsvpHelloMsg& RsvpHelloMsg::operator=(const RsvpHelloMsg& other)
{
    if (this == &other) return *this;
    ::inet::RsvpMessage::operator=(other);
    copy(other);
    return *this;
}

void RsvpHelloMsg::copy(const RsvpHelloMsg& other)
{
    this->request = other.request;
    this->ack = other.ack;
    this->srcInstance = other.srcInstance;
    this->dstInstance = other.dstInstance;
}

void RsvpHelloMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpMessage::parsimPack(b);
    doParsimPacking(b,this->request);
    doParsimPacking(b,this->ack);
    doParsimPacking(b,this->srcInstance);
    doParsimPacking(b,this->dstInstance);
}

void RsvpHelloMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->request);
    doParsimUnpacking(b,this->ack);
    doParsimUnpacking(b,this->srcInstance);
    doParsimUnpacking(b,this->dstInstance);
}

bool RsvpHelloMsg::getRequest() const
{
    return this->request;
}

void RsvpHelloMsg::setRequest(bool request)
{
    handleChange();
    this->request = request;
}

bool RsvpHelloMsg::getAck() const
{
    return this->ack;
}

void RsvpHelloMsg::setAck(bool ack)
{
    handleChange();
    this->ack = ack;
}

int RsvpHelloMsg::getSrcInstance() const
{
    return this->srcInstance;
}

void RsvpHelloMsg::setSrcInstance(int srcInstance)
{
    handleChange();
    this->srcInstance = srcInstance;
}

int RsvpHelloMsg::getDstInstance() const
{
    return this->dstInstance;
}

void RsvpHelloMsg::setDstInstance(int dstInstance)
{
    handleChange();
    this->dstInstance = dstInstance;
}

class RsvpHelloMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_request,
        FIELD_ack,
        FIELD_srcInstance,
        FIELD_dstInstance,
    };
  public:
    RsvpHelloMsgDescriptor();
    virtual ~RsvpHelloMsgDescriptor();

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

Register_ClassDescriptor(RsvpHelloMsgDescriptor)

RsvpHelloMsgDescriptor::RsvpHelloMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpHelloMsg)), "inet::RsvpMessage")
{
    propertyNames = nullptr;
}

RsvpHelloMsgDescriptor::~RsvpHelloMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsvpHelloMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpHelloMsg *>(obj)!=nullptr;
}

const char **RsvpHelloMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpHelloMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpHelloMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int RsvpHelloMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_request
        FD_ISEDITABLE,    // FIELD_ack
        FD_ISEDITABLE,    // FIELD_srcInstance
        FD_ISEDITABLE,    // FIELD_dstInstance
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *RsvpHelloMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "request",
        "ack",
        "srcInstance",
        "dstInstance",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int RsvpHelloMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "request") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "ack") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "srcInstance") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "dstInstance") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpHelloMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_request
        "bool",    // FIELD_ack
        "int",    // FIELD_srcInstance
        "int",    // FIELD_dstInstance
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpHelloMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpHelloMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpHelloMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpHelloMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpHelloMsg'", field);
    }
}

const char *RsvpHelloMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpHelloMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: return bool2string(pp->getRequest());
        case FIELD_ack: return bool2string(pp->getAck());
        case FIELD_srcInstance: return long2string(pp->getSrcInstance());
        case FIELD_dstInstance: return long2string(pp->getDstInstance());
        default: return "";
    }
}

void RsvpHelloMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->setRequest(string2bool(value)); break;
        case FIELD_ack: pp->setAck(string2bool(value)); break;
        case FIELD_srcInstance: pp->setSrcInstance(string2long(value)); break;
        case FIELD_dstInstance: pp->setDstInstance(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHelloMsg'", field);
    }
}

omnetpp::cValue RsvpHelloMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: return pp->getRequest();
        case FIELD_ack: return pp->getAck();
        case FIELD_srcInstance: return pp->getSrcInstance();
        case FIELD_dstInstance: return pp->getDstInstance();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpHelloMsg' as cValue -- field index out of range?", field);
    }
}

void RsvpHelloMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        case FIELD_request: pp->setRequest(value.boolValue()); break;
        case FIELD_ack: pp->setAck(value.boolValue()); break;
        case FIELD_srcInstance: pp->setSrcInstance(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dstInstance: pp->setDstInstance(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHelloMsg'", field);
    }
}

const char *RsvpHelloMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RsvpHelloMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpHelloMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHelloMsg *pp = omnetpp::fromAnyPtr<RsvpHelloMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHelloMsg'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

