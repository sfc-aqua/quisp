//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/applications/tcpapp/GenericAppMsg.msg.
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
#include "GenericAppMsg_m.h"

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

Register_Class(GenericAppMsg)

GenericAppMsg::GenericAppMsg() : ::inet::FieldsChunk()
{
}

GenericAppMsg::GenericAppMsg(const GenericAppMsg& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

GenericAppMsg::~GenericAppMsg()
{
}

GenericAppMsg& GenericAppMsg::operator=(const GenericAppMsg& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void GenericAppMsg::copy(const GenericAppMsg& other)
{
    this->expectedReplyLength = other.expectedReplyLength;
    this->replyDelay = other.replyDelay;
    this->serverClose = other.serverClose;
}

void GenericAppMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->expectedReplyLength);
    doParsimPacking(b,this->replyDelay);
    doParsimPacking(b,this->serverClose);
}

void GenericAppMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->expectedReplyLength);
    doParsimUnpacking(b,this->replyDelay);
    doParsimUnpacking(b,this->serverClose);
}

B GenericAppMsg::getExpectedReplyLength() const
{
    return this->expectedReplyLength;
}

void GenericAppMsg::setExpectedReplyLength(B expectedReplyLength)
{
    handleChange();
    this->expectedReplyLength = expectedReplyLength;
}

double GenericAppMsg::getReplyDelay() const
{
    return this->replyDelay;
}

void GenericAppMsg::setReplyDelay(double replyDelay)
{
    handleChange();
    this->replyDelay = replyDelay;
}

bool GenericAppMsg::getServerClose() const
{
    return this->serverClose;
}

void GenericAppMsg::setServerClose(bool serverClose)
{
    handleChange();
    this->serverClose = serverClose;
}

class GenericAppMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_expectedReplyLength,
        FIELD_replyDelay,
        FIELD_serverClose,
    };
  public:
    GenericAppMsgDescriptor();
    virtual ~GenericAppMsgDescriptor();

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

Register_ClassDescriptor(GenericAppMsgDescriptor)

GenericAppMsgDescriptor::GenericAppMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GenericAppMsg)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

GenericAppMsgDescriptor::~GenericAppMsgDescriptor()
{
    delete[] propertyNames;
}

bool GenericAppMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GenericAppMsg *>(obj)!=nullptr;
}

const char **GenericAppMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GenericAppMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GenericAppMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int GenericAppMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_expectedReplyLength
        FD_ISEDITABLE,    // FIELD_replyDelay
        FD_ISEDITABLE,    // FIELD_serverClose
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *GenericAppMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "expectedReplyLength",
        "replyDelay",
        "serverClose",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int GenericAppMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "expectedReplyLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "replyDelay") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "serverClose") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *GenericAppMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::B",    // FIELD_expectedReplyLength
        "double",    // FIELD_replyDelay
        "bool",    // FIELD_serverClose
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **GenericAppMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *GenericAppMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GenericAppMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GenericAppMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GenericAppMsg'", field);
    }
}

const char *GenericAppMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GenericAppMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        case FIELD_expectedReplyLength: return unit2string(pp->getExpectedReplyLength());
        case FIELD_replyDelay: return double2string(pp->getReplyDelay());
        case FIELD_serverClose: return bool2string(pp->getServerClose());
        default: return "";
    }
}

void GenericAppMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        case FIELD_expectedReplyLength: pp->setExpectedReplyLength(B(string2long(value))); break;
        case FIELD_replyDelay: pp->setReplyDelay(string2double(value)); break;
        case FIELD_serverClose: pp->setServerClose(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenericAppMsg'", field);
    }
}

omnetpp::cValue GenericAppMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        case FIELD_expectedReplyLength: return cValue(pp->getExpectedReplyLength().get(),"B");
        case FIELD_replyDelay: return pp->getReplyDelay();
        case FIELD_serverClose: return pp->getServerClose();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GenericAppMsg' as cValue -- field index out of range?", field);
    }
}

void GenericAppMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        case FIELD_expectedReplyLength: pp->setExpectedReplyLength(B(value.intValueInUnit("B"))); break;
        case FIELD_replyDelay: pp->setReplyDelay(value.doubleValue()); break;
        case FIELD_serverClose: pp->setServerClose(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenericAppMsg'", field);
    }
}

const char *GenericAppMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GenericAppMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GenericAppMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GenericAppMsg *pp = omnetpp::fromAnyPtr<GenericAppMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GenericAppMsg'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

