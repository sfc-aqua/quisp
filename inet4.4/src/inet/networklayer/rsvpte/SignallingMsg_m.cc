//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/SignallingMsg.msg.
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
#include "SignallingMsg_m.h"

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

Register_Enum(inet::SignallingConstants, (inet::SignallingConstants::MSG_PSB_TIMER, inet::SignallingConstants::MSG_PSB_TIMEOUT, inet::SignallingConstants::MSG_RSB_REFRESH_TIMER, inet::SignallingConstants::MSG_RSB_COMMIT_TIMER, inet::SignallingConstants::MSG_RSB_TIMEOUT, inet::SignallingConstants::MSG_HELLO_TIMER, inet::SignallingConstants::MSG_HELLO_TIMEOUT, inet::SignallingConstants::MSG_PATH_NOTIFY, inet::SignallingConstants::PATH_CREATED, inet::SignallingConstants::PATH_UNFEASIBLE, inet::SignallingConstants::PATH_FAILED, inet::SignallingConstants::PATH_PREEMPTED, inet::SignallingConstants::PATH_RETRY));

Register_Class(SignallingMsg)

SignallingMsg::SignallingMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SignallingMsg::SignallingMsg(const SignallingMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SignallingMsg::~SignallingMsg()
{
}

SignallingMsg& SignallingMsg::operator=(const SignallingMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SignallingMsg::copy(const SignallingMsg& other)
{
    this->command = other.command;
}

void SignallingMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->command);
}

void SignallingMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
}

int SignallingMsg::getCommand() const
{
    return this->command;
}

void SignallingMsg::setCommand(int command)
{
    this->command = command;
}

class SignallingMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_command,
    };
  public:
    SignallingMsgDescriptor();
    virtual ~SignallingMsgDescriptor();

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

Register_ClassDescriptor(SignallingMsgDescriptor)

SignallingMsgDescriptor::SignallingMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignallingMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SignallingMsgDescriptor::~SignallingMsgDescriptor()
{
    delete[] propertyNames;
}

bool SignallingMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignallingMsg *>(obj)!=nullptr;
}

const char **SignallingMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignallingMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignallingMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SignallingMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_command
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SignallingMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "command",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SignallingMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "command") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SignallingMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_command
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SignallingMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *SignallingMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignallingMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignallingMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignallingMsg'", field);
    }
}

const char *SignallingMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignallingMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_command: return long2string(pp->getCommand());
        default: return "";
    }
}

void SignallingMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_command: pp->setCommand(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignallingMsg'", field);
    }
}

omnetpp::cValue SignallingMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_command: return pp->getCommand();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignallingMsg' as cValue -- field index out of range?", field);
    }
}

void SignallingMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        case FIELD_command: pp->setCommand(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignallingMsg'", field);
    }
}

const char *SignallingMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SignallingMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignallingMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignallingMsg *pp = omnetpp::fromAnyPtr<SignallingMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignallingMsg'", field);
    }
}

Register_Class(PsbTimerMsg)

PsbTimerMsg::PsbTimerMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_PSB_TIMER);

}

PsbTimerMsg::PsbTimerMsg(const PsbTimerMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

PsbTimerMsg::~PsbTimerMsg()
{
}

PsbTimerMsg& PsbTimerMsg::operator=(const PsbTimerMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void PsbTimerMsg::copy(const PsbTimerMsg& other)
{
    this->id = other.id;
}

void PsbTimerMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->id);
}

void PsbTimerMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
}

int PsbTimerMsg::getId() const
{
    return this->id;
}

void PsbTimerMsg::setId(int id)
{
    this->id = id;
}

class PsbTimerMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
    };
  public:
    PsbTimerMsgDescriptor();
    virtual ~PsbTimerMsgDescriptor();

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

Register_ClassDescriptor(PsbTimerMsgDescriptor)

PsbTimerMsgDescriptor::PsbTimerMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PsbTimerMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

PsbTimerMsgDescriptor::~PsbTimerMsgDescriptor()
{
    delete[] propertyNames;
}

bool PsbTimerMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PsbTimerMsg *>(obj)!=nullptr;
}

const char **PsbTimerMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PsbTimerMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PsbTimerMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int PsbTimerMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PsbTimerMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PsbTimerMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *PsbTimerMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PsbTimerMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *PsbTimerMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PsbTimerMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PsbTimerMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PsbTimerMsg'", field);
    }
}

const char *PsbTimerMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PsbTimerMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return long2string(pp->getId());
        default: return "";
    }
}

void PsbTimerMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimerMsg'", field);
    }
}

omnetpp::cValue PsbTimerMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return pp->getId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PsbTimerMsg' as cValue -- field index out of range?", field);
    }
}

void PsbTimerMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimerMsg'", field);
    }
}

const char *PsbTimerMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PsbTimerMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PsbTimerMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimerMsg *pp = omnetpp::fromAnyPtr<PsbTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimerMsg'", field);
    }
}

Register_Class(PsbTimeoutMsg)

PsbTimeoutMsg::PsbTimeoutMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_PSB_TIMEOUT);

}

PsbTimeoutMsg::PsbTimeoutMsg(const PsbTimeoutMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

PsbTimeoutMsg::~PsbTimeoutMsg()
{
}

PsbTimeoutMsg& PsbTimeoutMsg::operator=(const PsbTimeoutMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void PsbTimeoutMsg::copy(const PsbTimeoutMsg& other)
{
    this->id = other.id;
}

void PsbTimeoutMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->id);
}

void PsbTimeoutMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
}

int PsbTimeoutMsg::getId() const
{
    return this->id;
}

void PsbTimeoutMsg::setId(int id)
{
    this->id = id;
}

class PsbTimeoutMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
    };
  public:
    PsbTimeoutMsgDescriptor();
    virtual ~PsbTimeoutMsgDescriptor();

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

Register_ClassDescriptor(PsbTimeoutMsgDescriptor)

PsbTimeoutMsgDescriptor::PsbTimeoutMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PsbTimeoutMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

PsbTimeoutMsgDescriptor::~PsbTimeoutMsgDescriptor()
{
    delete[] propertyNames;
}

bool PsbTimeoutMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PsbTimeoutMsg *>(obj)!=nullptr;
}

const char **PsbTimeoutMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PsbTimeoutMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PsbTimeoutMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int PsbTimeoutMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *PsbTimeoutMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int PsbTimeoutMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *PsbTimeoutMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **PsbTimeoutMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *PsbTimeoutMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PsbTimeoutMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PsbTimeoutMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PsbTimeoutMsg'", field);
    }
}

const char *PsbTimeoutMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PsbTimeoutMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return long2string(pp->getId());
        default: return "";
    }
}

void PsbTimeoutMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimeoutMsg'", field);
    }
}

omnetpp::cValue PsbTimeoutMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return pp->getId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PsbTimeoutMsg' as cValue -- field index out of range?", field);
    }
}

void PsbTimeoutMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimeoutMsg'", field);
    }
}

const char *PsbTimeoutMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PsbTimeoutMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PsbTimeoutMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PsbTimeoutMsg *pp = omnetpp::fromAnyPtr<PsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PsbTimeoutMsg'", field);
    }
}

Register_Class(RsbRefreshTimerMsg)

RsbRefreshTimerMsg::RsbRefreshTimerMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_RSB_REFRESH_TIMER);

}

RsbRefreshTimerMsg::RsbRefreshTimerMsg(const RsbRefreshTimerMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

RsbRefreshTimerMsg::~RsbRefreshTimerMsg()
{
}

RsbRefreshTimerMsg& RsbRefreshTimerMsg::operator=(const RsbRefreshTimerMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void RsbRefreshTimerMsg::copy(const RsbRefreshTimerMsg& other)
{
    this->id = other.id;
}

void RsbRefreshTimerMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->id);
}

void RsbRefreshTimerMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
}

int RsbRefreshTimerMsg::getId() const
{
    return this->id;
}

void RsbRefreshTimerMsg::setId(int id)
{
    this->id = id;
}

class RsbRefreshTimerMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
    };
  public:
    RsbRefreshTimerMsgDescriptor();
    virtual ~RsbRefreshTimerMsgDescriptor();

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

Register_ClassDescriptor(RsbRefreshTimerMsgDescriptor)

RsbRefreshTimerMsgDescriptor::RsbRefreshTimerMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsbRefreshTimerMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

RsbRefreshTimerMsgDescriptor::~RsbRefreshTimerMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsbRefreshTimerMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsbRefreshTimerMsg *>(obj)!=nullptr;
}

const char **RsbRefreshTimerMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsbRefreshTimerMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsbRefreshTimerMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RsbRefreshTimerMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RsbRefreshTimerMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RsbRefreshTimerMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RsbRefreshTimerMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RsbRefreshTimerMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsbRefreshTimerMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsbRefreshTimerMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsbRefreshTimerMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsbRefreshTimerMsg'", field);
    }
}

const char *RsbRefreshTimerMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsbRefreshTimerMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return long2string(pp->getId());
        default: return "";
    }
}

void RsbRefreshTimerMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbRefreshTimerMsg'", field);
    }
}

omnetpp::cValue RsbRefreshTimerMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return pp->getId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsbRefreshTimerMsg' as cValue -- field index out of range?", field);
    }
}

void RsbRefreshTimerMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbRefreshTimerMsg'", field);
    }
}

const char *RsbRefreshTimerMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RsbRefreshTimerMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsbRefreshTimerMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbRefreshTimerMsg *pp = omnetpp::fromAnyPtr<RsbRefreshTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbRefreshTimerMsg'", field);
    }
}

Register_Class(RsbCommitTimerMsg)

RsbCommitTimerMsg::RsbCommitTimerMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_RSB_COMMIT_TIMER);

}

RsbCommitTimerMsg::RsbCommitTimerMsg(const RsbCommitTimerMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

RsbCommitTimerMsg::~RsbCommitTimerMsg()
{
}

RsbCommitTimerMsg& RsbCommitTimerMsg::operator=(const RsbCommitTimerMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void RsbCommitTimerMsg::copy(const RsbCommitTimerMsg& other)
{
    this->id = other.id;
}

void RsbCommitTimerMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->id);
}

void RsbCommitTimerMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
}

int RsbCommitTimerMsg::getId() const
{
    return this->id;
}

void RsbCommitTimerMsg::setId(int id)
{
    this->id = id;
}

class RsbCommitTimerMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
    };
  public:
    RsbCommitTimerMsgDescriptor();
    virtual ~RsbCommitTimerMsgDescriptor();

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

Register_ClassDescriptor(RsbCommitTimerMsgDescriptor)

RsbCommitTimerMsgDescriptor::RsbCommitTimerMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsbCommitTimerMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

RsbCommitTimerMsgDescriptor::~RsbCommitTimerMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsbCommitTimerMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsbCommitTimerMsg *>(obj)!=nullptr;
}

const char **RsbCommitTimerMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsbCommitTimerMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsbCommitTimerMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RsbCommitTimerMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RsbCommitTimerMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RsbCommitTimerMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RsbCommitTimerMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RsbCommitTimerMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsbCommitTimerMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsbCommitTimerMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsbCommitTimerMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsbCommitTimerMsg'", field);
    }
}

const char *RsbCommitTimerMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsbCommitTimerMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return long2string(pp->getId());
        default: return "";
    }
}

void RsbCommitTimerMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbCommitTimerMsg'", field);
    }
}

omnetpp::cValue RsbCommitTimerMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return pp->getId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsbCommitTimerMsg' as cValue -- field index out of range?", field);
    }
}

void RsbCommitTimerMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbCommitTimerMsg'", field);
    }
}

const char *RsbCommitTimerMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RsbCommitTimerMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsbCommitTimerMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbCommitTimerMsg *pp = omnetpp::fromAnyPtr<RsbCommitTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbCommitTimerMsg'", field);
    }
}

Register_Class(RsbTimeoutMsg)

RsbTimeoutMsg::RsbTimeoutMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_RSB_TIMEOUT);

}

RsbTimeoutMsg::RsbTimeoutMsg(const RsbTimeoutMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

RsbTimeoutMsg::~RsbTimeoutMsg()
{
}

RsbTimeoutMsg& RsbTimeoutMsg::operator=(const RsbTimeoutMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void RsbTimeoutMsg::copy(const RsbTimeoutMsg& other)
{
    this->id = other.id;
}

void RsbTimeoutMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->id);
}

void RsbTimeoutMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->id);
}

int RsbTimeoutMsg::getId() const
{
    return this->id;
}

void RsbTimeoutMsg::setId(int id)
{
    this->id = id;
}

class RsbTimeoutMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_id,
    };
  public:
    RsbTimeoutMsgDescriptor();
    virtual ~RsbTimeoutMsgDescriptor();

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

Register_ClassDescriptor(RsbTimeoutMsgDescriptor)

RsbTimeoutMsgDescriptor::RsbTimeoutMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsbTimeoutMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

RsbTimeoutMsgDescriptor::~RsbTimeoutMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsbTimeoutMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsbTimeoutMsg *>(obj)!=nullptr;
}

const char **RsbTimeoutMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsbTimeoutMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsbTimeoutMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int RsbTimeoutMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *RsbTimeoutMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "id",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int RsbTimeoutMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *RsbTimeoutMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_id
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **RsbTimeoutMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsbTimeoutMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsbTimeoutMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsbTimeoutMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsbTimeoutMsg'", field);
    }
}

const char *RsbTimeoutMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsbTimeoutMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return long2string(pp->getId());
        default: return "";
    }
}

void RsbTimeoutMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbTimeoutMsg'", field);
    }
}

omnetpp::cValue RsbTimeoutMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: return pp->getId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsbTimeoutMsg' as cValue -- field index out of range?", field);
    }
}

void RsbTimeoutMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbTimeoutMsg'", field);
    }
}

const char *RsbTimeoutMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RsbTimeoutMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsbTimeoutMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsbTimeoutMsg *pp = omnetpp::fromAnyPtr<RsbTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsbTimeoutMsg'", field);
    }
}

Register_Class(HelloTimerMsg)

HelloTimerMsg::HelloTimerMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_HELLO_TIMER);

}

HelloTimerMsg::HelloTimerMsg(const HelloTimerMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

HelloTimerMsg::~HelloTimerMsg()
{
}

HelloTimerMsg& HelloTimerMsg::operator=(const HelloTimerMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void HelloTimerMsg::copy(const HelloTimerMsg& other)
{
    this->peer = other.peer;
}

void HelloTimerMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->peer);
}

void HelloTimerMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->peer);
}

const Ipv4Address& HelloTimerMsg::getPeer() const
{
    return this->peer;
}

void HelloTimerMsg::setPeer(const Ipv4Address& peer)
{
    this->peer = peer;
}

class HelloTimerMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_peer,
    };
  public:
    HelloTimerMsgDescriptor();
    virtual ~HelloTimerMsgDescriptor();

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

Register_ClassDescriptor(HelloTimerMsgDescriptor)

HelloTimerMsgDescriptor::HelloTimerMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HelloTimerMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

HelloTimerMsgDescriptor::~HelloTimerMsgDescriptor()
{
    delete[] propertyNames;
}

bool HelloTimerMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HelloTimerMsg *>(obj)!=nullptr;
}

const char **HelloTimerMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HelloTimerMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HelloTimerMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HelloTimerMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_peer
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HelloTimerMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "peer",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HelloTimerMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "peer") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HelloTimerMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_peer
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloTimerMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *HelloTimerMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HelloTimerMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HelloTimerMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HelloTimerMsg'", field);
    }
}

const char *HelloTimerMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HelloTimerMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return pp->getPeer().str();
        default: return "";
    }
}

void HelloTimerMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimerMsg'", field);
    }
}

omnetpp::cValue HelloTimerMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return omnetpp::toAnyPtr(&pp->getPeer()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HelloTimerMsg' as cValue -- field index out of range?", field);
    }
}

void HelloTimerMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimerMsg'", field);
    }
}

const char *HelloTimerMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HelloTimerMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return omnetpp::toAnyPtr(&pp->getPeer()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HelloTimerMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimerMsg *pp = omnetpp::fromAnyPtr<HelloTimerMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimerMsg'", field);
    }
}

Register_Class(HelloTimeoutMsg)

HelloTimeoutMsg::HelloTimeoutMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_HELLO_TIMEOUT);

}

HelloTimeoutMsg::HelloTimeoutMsg(const HelloTimeoutMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

HelloTimeoutMsg::~HelloTimeoutMsg()
{
}

HelloTimeoutMsg& HelloTimeoutMsg::operator=(const HelloTimeoutMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void HelloTimeoutMsg::copy(const HelloTimeoutMsg& other)
{
    this->peer = other.peer;
}

void HelloTimeoutMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->peer);
}

void HelloTimeoutMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->peer);
}

const Ipv4Address& HelloTimeoutMsg::getPeer() const
{
    return this->peer;
}

void HelloTimeoutMsg::setPeer(const Ipv4Address& peer)
{
    this->peer = peer;
}

class HelloTimeoutMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_peer,
    };
  public:
    HelloTimeoutMsgDescriptor();
    virtual ~HelloTimeoutMsgDescriptor();

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

Register_ClassDescriptor(HelloTimeoutMsgDescriptor)

HelloTimeoutMsgDescriptor::HelloTimeoutMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::HelloTimeoutMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

HelloTimeoutMsgDescriptor::~HelloTimeoutMsgDescriptor()
{
    delete[] propertyNames;
}

bool HelloTimeoutMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HelloTimeoutMsg *>(obj)!=nullptr;
}

const char **HelloTimeoutMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HelloTimeoutMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HelloTimeoutMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HelloTimeoutMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_peer
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HelloTimeoutMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "peer",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HelloTimeoutMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "peer") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HelloTimeoutMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_peer
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HelloTimeoutMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *HelloTimeoutMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HelloTimeoutMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HelloTimeoutMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HelloTimeoutMsg'", field);
    }
}

const char *HelloTimeoutMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HelloTimeoutMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return pp->getPeer().str();
        default: return "";
    }
}

void HelloTimeoutMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimeoutMsg'", field);
    }
}

omnetpp::cValue HelloTimeoutMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return omnetpp::toAnyPtr(&pp->getPeer()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HelloTimeoutMsg' as cValue -- field index out of range?", field);
    }
}

void HelloTimeoutMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimeoutMsg'", field);
    }
}

const char *HelloTimeoutMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HelloTimeoutMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_peer: return omnetpp::toAnyPtr(&pp->getPeer()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HelloTimeoutMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HelloTimeoutMsg *pp = omnetpp::fromAnyPtr<HelloTimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HelloTimeoutMsg'", field);
    }
}

Register_Class(PathNotifyMsg)

PathNotifyMsg::PathNotifyMsg(const char *name, short kind) : ::inet::SignallingMsg(name, kind)
{
    this->setCommand(MSG_PATH_NOTIFY);

}

PathNotifyMsg::PathNotifyMsg(const PathNotifyMsg& other) : ::inet::SignallingMsg(other)
{
    copy(other);
}

PathNotifyMsg::~PathNotifyMsg()
{
}

PathNotifyMsg& PathNotifyMsg::operator=(const PathNotifyMsg& other)
{
    if (this == &other) return *this;
    ::inet::SignallingMsg::operator=(other);
    copy(other);
    return *this;
}

void PathNotifyMsg::copy(const PathNotifyMsg& other)
{
    this->session = other.session;
    this->sender = other.sender;
    this->status = other.status;
}

void PathNotifyMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignallingMsg::parsimPack(b);
    doParsimPacking(b,this->session);
    doParsimPacking(b,this->sender);
    doParsimPacking(b,this->status);
}

void PathNotifyMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignallingMsg::parsimUnpack(b);
    doParsimUnpacking(b,this->session);
    doParsimUnpacking(b,this->sender);
    doParsimUnpacking(b,this->status);
}

const SessionObj& PathNotifyMsg::getSession() const
{
    return this->session;
}

void PathNotifyMsg::setSession(const SessionObj& session)
{
    this->session = session;
}

const SenderTemplateObj& PathNotifyMsg::getSender() const
{
    return this->sender;
}

void PathNotifyMsg::setSender(const SenderTemplateObj& sender)
{
    this->sender = sender;
}

int PathNotifyMsg::getStatus() const
{
    return this->status;
}

void PathNotifyMsg::setStatus(int status)
{
    this->status = status;
}

class PathNotifyMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_session,
        FIELD_sender,
        FIELD_status,
    };
  public:
    PathNotifyMsgDescriptor();
    virtual ~PathNotifyMsgDescriptor();

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

Register_ClassDescriptor(PathNotifyMsgDescriptor)

PathNotifyMsgDescriptor::PathNotifyMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PathNotifyMsg)), "inet::SignallingMsg")
{
    propertyNames = nullptr;
}

PathNotifyMsgDescriptor::~PathNotifyMsgDescriptor()
{
    delete[] propertyNames;
}

bool PathNotifyMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PathNotifyMsg *>(obj)!=nullptr;
}

const char **PathNotifyMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PathNotifyMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PathNotifyMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int PathNotifyMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_session
        FD_ISCOMPOUND,    // FIELD_sender
        FD_ISEDITABLE,    // FIELD_status
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *PathNotifyMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "session",
        "sender",
        "status",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int PathNotifyMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "session") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sender") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "status") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *PathNotifyMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::SessionObj",    // FIELD_session
        "inet::SenderTemplateObj",    // FIELD_sender
        "int",    // FIELD_status
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **PathNotifyMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *PathNotifyMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PathNotifyMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PathNotifyMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PathNotifyMsg'", field);
    }
}

const char *PathNotifyMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PathNotifyMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_session: return "";
        case FIELD_sender: return "";
        case FIELD_status: return long2string(pp->getStatus());
        default: return "";
    }
}

void PathNotifyMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PathNotifyMsg'", field);
    }
}

omnetpp::cValue PathNotifyMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_session: return omnetpp::toAnyPtr(&pp->getSession()); break;
        case FIELD_sender: return omnetpp::toAnyPtr(&pp->getSender()); break;
        case FIELD_status: return pp->getStatus();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PathNotifyMsg' as cValue -- field index out of range?", field);
    }
}

void PathNotifyMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_status: pp->setStatus(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PathNotifyMsg'", field);
    }
}

const char *PathNotifyMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_session: return omnetpp::opp_typename(typeid(SessionObj));
        case FIELD_sender: return omnetpp::opp_typename(typeid(SenderTemplateObj));
        default: return nullptr;
    };
}

omnetpp::any_ptr PathNotifyMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_session: return omnetpp::toAnyPtr(&pp->getSession()); break;
        case FIELD_sender: return omnetpp::toAnyPtr(&pp->getSender()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PathNotifyMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PathNotifyMsg *pp = omnetpp::fromAnyPtr<PathNotifyMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PathNotifyMsg'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

