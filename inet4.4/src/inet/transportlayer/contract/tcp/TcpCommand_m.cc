//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/contract/tcp/TcpCommand.msg.
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
#include "TcpCommand_m.h"

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

Register_Enum(inet::TcpCommandCode, (inet::TcpCommandCode::TCP_C_OPEN_ACTIVE, inet::TcpCommandCode::TCP_C_OPEN_PASSIVE, inet::TcpCommandCode::TCP_C_ACCEPT, inet::TcpCommandCode::TCP_C_SEND, inet::TcpCommandCode::TCP_C_CLOSE, inet::TcpCommandCode::TCP_C_ABORT, inet::TcpCommandCode::TCP_C_STATUS, inet::TcpCommandCode::TCP_C_QUEUE_BYTES_LIMIT, inet::TcpCommandCode::TCP_C_READ, inet::TcpCommandCode::TCP_C_DESTROY, inet::TcpCommandCode::TCP_C_SETOPTION));

Register_Enum(inet::TcpStatusInd, (inet::TcpStatusInd::TCP_I_DATA, inet::TcpStatusInd::TCP_I_URGENT_DATA, inet::TcpStatusInd::TCP_I_AVAILABLE, inet::TcpStatusInd::TCP_I_ESTABLISHED, inet::TcpStatusInd::TCP_I_PEER_CLOSED, inet::TcpStatusInd::TCP_I_CLOSED, inet::TcpStatusInd::TCP_I_CONNECTION_REFUSED, inet::TcpStatusInd::TCP_I_CONNECTION_RESET, inet::TcpStatusInd::TCP_I_TIMED_OUT, inet::TcpStatusInd::TCP_I_STATUS, inet::TcpStatusInd::TCP_I_SEND_MSG, inet::TcpStatusInd::TCP_I_DATA_NOTIFICATION));

Register_Enum(inet::TcpErrorCode, ());

Register_Class(TcpCommand)

TcpCommand::TcpCommand() : ::omnetpp::cObject()
{
}

TcpCommand::TcpCommand(const TcpCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

TcpCommand::~TcpCommand()
{
}

TcpCommand& TcpCommand::operator=(const TcpCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void TcpCommand::copy(const TcpCommand& other)
{
    this->userId = other.userId;
}

void TcpCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->userId);
}

void TcpCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->userId);
}

int TcpCommand::getUserId() const
{
    return this->userId;
}

void TcpCommand::setUserId(int userId)
{
    this->userId = userId;
}

class TcpCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_userId,
    };
  public:
    TcpCommandDescriptor();
    virtual ~TcpCommandDescriptor();

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

Register_ClassDescriptor(TcpCommandDescriptor)

TcpCommandDescriptor::TcpCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpCommand)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpCommandDescriptor::~TcpCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpCommand *>(obj)!=nullptr;
}

const char **TcpCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_userId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "userId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "userId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_userId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpCommand'", field);
    }
}

const char *TcpCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_userId: return long2string(pp->getUserId());
        default: return "";
    }
}

void TcpCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_userId: pp->setUserId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpCommand'", field);
    }
}

omnetpp::cValue TcpCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_userId: return pp->getUserId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpCommand' as cValue -- field index out of range?", field);
    }
}

void TcpCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_userId: pp->setUserId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpCommand'", field);
    }
}

const char *TcpCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpCommand *pp = omnetpp::fromAnyPtr<TcpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpCommand'", field);
    }
}

Register_Class(TcpErrorInfo)

TcpErrorInfo::TcpErrorInfo() : ::inet::TcpCommand()
{
}

TcpErrorInfo::TcpErrorInfo(const TcpErrorInfo& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpErrorInfo::~TcpErrorInfo()
{
}

TcpErrorInfo& TcpErrorInfo::operator=(const TcpErrorInfo& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpErrorInfo::copy(const TcpErrorInfo& other)
{
    this->errorCode = other.errorCode;
    this->messageText = other.messageText;
}

void TcpErrorInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
    doParsimPacking(b,this->errorCode);
    doParsimPacking(b,this->messageText);
}

void TcpErrorInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->errorCode);
    doParsimUnpacking(b,this->messageText);
}

TcpErrorCode TcpErrorInfo::getErrorCode() const
{
    return this->errorCode;
}

void TcpErrorInfo::setErrorCode(TcpErrorCode errorCode)
{
    this->errorCode = errorCode;
}

const char * TcpErrorInfo::getMessageText() const
{
    return this->messageText.c_str();
}

void TcpErrorInfo::setMessageText(const char * messageText)
{
    this->messageText = messageText;
}

class TcpErrorInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_errorCode,
        FIELD_messageText,
    };
  public:
    TcpErrorInfoDescriptor();
    virtual ~TcpErrorInfoDescriptor();

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

Register_ClassDescriptor(TcpErrorInfoDescriptor)

TcpErrorInfoDescriptor::TcpErrorInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpErrorInfo)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpErrorInfoDescriptor::~TcpErrorInfoDescriptor()
{
    delete[] propertyNames;
}

bool TcpErrorInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpErrorInfo *>(obj)!=nullptr;
}

const char **TcpErrorInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpErrorInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpErrorInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TcpErrorInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_errorCode
        FD_ISEDITABLE,    // FIELD_messageText
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TcpErrorInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "errorCode",
        "messageText",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TcpErrorInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "errorCode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "messageText") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpErrorInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TcpErrorCode",    // FIELD_errorCode
        "string",    // FIELD_messageText
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpErrorInfoDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_errorCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TcpErrorInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_errorCode:
            if (!strcmp(propertyName, "enum")) return "inet::TcpErrorCode";
            return nullptr;
        default: return nullptr;
    }
}

int TcpErrorInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpErrorInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpErrorInfo'", field);
    }
}

const char *TcpErrorInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpErrorInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: return enum2string(pp->getErrorCode(), "inet::TcpErrorCode");
        case FIELD_messageText: return oppstring2string(pp->getMessageText());
        default: return "";
    }
}

void TcpErrorInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        case FIELD_messageText: pp->setMessageText((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpErrorInfo'", field);
    }
}

omnetpp::cValue TcpErrorInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: return static_cast<int>(pp->getErrorCode());
        case FIELD_messageText: return pp->getMessageText();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpErrorInfo' as cValue -- field index out of range?", field);
    }
}

void TcpErrorInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        case FIELD_messageText: pp->setMessageText(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpErrorInfo'", field);
    }
}

const char *TcpErrorInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpErrorInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpErrorInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpErrorInfo *pp = omnetpp::fromAnyPtr<TcpErrorInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpErrorInfo'", field);
    }
}

Register_Class(TcpOpenCommand)

TcpOpenCommand::TcpOpenCommand() : ::inet::TcpCommand()
{
}

TcpOpenCommand::TcpOpenCommand(const TcpOpenCommand& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpOpenCommand::~TcpOpenCommand()
{
}

TcpOpenCommand& TcpOpenCommand::operator=(const TcpOpenCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpOpenCommand::copy(const TcpOpenCommand& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->fork = other.fork;
    this->tcpAlgorithmClass = other.tcpAlgorithmClass;
}

void TcpOpenCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->fork);
    doParsimPacking(b,this->tcpAlgorithmClass);
}

void TcpOpenCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->fork);
    doParsimUnpacking(b,this->tcpAlgorithmClass);
}

const L3Address& TcpOpenCommand::getLocalAddr() const
{
    return this->localAddr;
}

void TcpOpenCommand::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& TcpOpenCommand::getRemoteAddr() const
{
    return this->remoteAddr;
}

void TcpOpenCommand::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int TcpOpenCommand::getLocalPort() const
{
    return this->localPort;
}

void TcpOpenCommand::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int TcpOpenCommand::getRemotePort() const
{
    return this->remotePort;
}

void TcpOpenCommand::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

bool TcpOpenCommand::getFork() const
{
    return this->fork;
}

void TcpOpenCommand::setFork(bool fork)
{
    this->fork = fork;
}

const char * TcpOpenCommand::getTcpAlgorithmClass() const
{
    return this->tcpAlgorithmClass.c_str();
}

void TcpOpenCommand::setTcpAlgorithmClass(const char * tcpAlgorithmClass)
{
    this->tcpAlgorithmClass = tcpAlgorithmClass;
}

class TcpOpenCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_fork,
        FIELD_tcpAlgorithmClass,
    };
  public:
    TcpOpenCommandDescriptor();
    virtual ~TcpOpenCommandDescriptor();

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

Register_ClassDescriptor(TcpOpenCommandDescriptor)

TcpOpenCommandDescriptor::TcpOpenCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpOpenCommand)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpOpenCommandDescriptor::~TcpOpenCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpOpenCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOpenCommand *>(obj)!=nullptr;
}

const char **TcpOpenCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOpenCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOpenCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int TcpOpenCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_fork
        FD_ISEDITABLE,    // FIELD_tcpAlgorithmClass
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *TcpOpenCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "fork",
        "tcpAlgorithmClass",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int TcpOpenCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "fork") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "tcpAlgorithmClass") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOpenCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "bool",    // FIELD_fork
        "string",    // FIELD_tcpAlgorithmClass
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOpenCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOpenCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOpenCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOpenCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOpenCommand'", field);
    }
}

const char *TcpOpenCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOpenCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_fork: return bool2string(pp->getFork());
        case FIELD_tcpAlgorithmClass: return oppstring2string(pp->getTcpAlgorithmClass());
        default: return "";
    }
}

void TcpOpenCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        case FIELD_fork: pp->setFork(string2bool(value)); break;
        case FIELD_tcpAlgorithmClass: pp->setTcpAlgorithmClass((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOpenCommand'", field);
    }
}

omnetpp::cValue TcpOpenCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        case FIELD_fork: return pp->getFork();
        case FIELD_tcpAlgorithmClass: return pp->getTcpAlgorithmClass();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOpenCommand' as cValue -- field index out of range?", field);
    }
}

void TcpOpenCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fork: pp->setFork(value.boolValue()); break;
        case FIELD_tcpAlgorithmClass: pp->setTcpAlgorithmClass(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOpenCommand'", field);
    }
}

const char *TcpOpenCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOpenCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOpenCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOpenCommand *pp = omnetpp::fromAnyPtr<TcpOpenCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOpenCommand'", field);
    }
}

Register_Class(TcpAcceptCommand)

TcpAcceptCommand::TcpAcceptCommand() : ::inet::TcpCommand()
{
}

TcpAcceptCommand::TcpAcceptCommand(const TcpAcceptCommand& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpAcceptCommand::~TcpAcceptCommand()
{
}

TcpAcceptCommand& TcpAcceptCommand::operator=(const TcpAcceptCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpAcceptCommand::copy(const TcpAcceptCommand& other)
{
}

void TcpAcceptCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
}

void TcpAcceptCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
}

class TcpAcceptCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpAcceptCommandDescriptor();
    virtual ~TcpAcceptCommandDescriptor();

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

Register_ClassDescriptor(TcpAcceptCommandDescriptor)

TcpAcceptCommandDescriptor::TcpAcceptCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpAcceptCommand)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpAcceptCommandDescriptor::~TcpAcceptCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpAcceptCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpAcceptCommand *>(obj)!=nullptr;
}

const char **TcpAcceptCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpAcceptCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpAcceptCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpAcceptCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpAcceptCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpAcceptCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpAcceptCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpAcceptCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpAcceptCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpAcceptCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpAcceptCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpAcceptCommand'", field);
    }
}

const char *TcpAcceptCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpAcceptCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpAcceptCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAcceptCommand'", field);
    }
}

omnetpp::cValue TcpAcceptCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpAcceptCommand' as cValue -- field index out of range?", field);
    }
}

void TcpAcceptCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAcceptCommand'", field);
    }
}

const char *TcpAcceptCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpAcceptCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpAcceptCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAcceptCommand *pp = omnetpp::fromAnyPtr<TcpAcceptCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAcceptCommand'", field);
    }
}

Register_Class(TcpSetOptionCommand)

TcpSetOptionCommand::TcpSetOptionCommand() : ::inet::TcpCommand()
{
}

TcpSetOptionCommand::TcpSetOptionCommand(const TcpSetOptionCommand& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpSetOptionCommand::~TcpSetOptionCommand()
{
}

TcpSetOptionCommand& TcpSetOptionCommand::operator=(const TcpSetOptionCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpSetOptionCommand::copy(const TcpSetOptionCommand& other)
{
}

void TcpSetOptionCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
}

void TcpSetOptionCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
}

class TcpSetOptionCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpSetOptionCommandDescriptor();
    virtual ~TcpSetOptionCommandDescriptor();

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

Register_ClassDescriptor(TcpSetOptionCommandDescriptor)

TcpSetOptionCommandDescriptor::TcpSetOptionCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpSetOptionCommand)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpSetOptionCommandDescriptor::~TcpSetOptionCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpSetOptionCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSetOptionCommand *>(obj)!=nullptr;
}

const char **TcpSetOptionCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSetOptionCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSetOptionCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpSetOptionCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpSetOptionCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpSetOptionCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSetOptionCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpSetOptionCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSetOptionCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSetOptionCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSetOptionCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSetOptionCommand'", field);
    }
}

const char *TcpSetOptionCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSetOptionCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpSetOptionCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetOptionCommand'", field);
    }
}

omnetpp::cValue TcpSetOptionCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSetOptionCommand' as cValue -- field index out of range?", field);
    }
}

void TcpSetOptionCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetOptionCommand'", field);
    }
}

const char *TcpSetOptionCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpSetOptionCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSetOptionCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetOptionCommand *pp = omnetpp::fromAnyPtr<TcpSetOptionCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetOptionCommand'", field);
    }
}

Register_Class(TcpSetTimeToLiveCommand)

TcpSetTimeToLiveCommand::TcpSetTimeToLiveCommand() : ::inet::TcpSetOptionCommand()
{
}

TcpSetTimeToLiveCommand::TcpSetTimeToLiveCommand(const TcpSetTimeToLiveCommand& other) : ::inet::TcpSetOptionCommand(other)
{
    copy(other);
}

TcpSetTimeToLiveCommand::~TcpSetTimeToLiveCommand()
{
}

TcpSetTimeToLiveCommand& TcpSetTimeToLiveCommand::operator=(const TcpSetTimeToLiveCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpSetTimeToLiveCommand::copy(const TcpSetTimeToLiveCommand& other)
{
    this->ttl = other.ttl;
}

void TcpSetTimeToLiveCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->ttl);
}

void TcpSetTimeToLiveCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->ttl);
}

int TcpSetTimeToLiveCommand::getTtl() const
{
    return this->ttl;
}

void TcpSetTimeToLiveCommand::setTtl(int ttl)
{
    this->ttl = ttl;
}

class TcpSetTimeToLiveCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ttl,
    };
  public:
    TcpSetTimeToLiveCommandDescriptor();
    virtual ~TcpSetTimeToLiveCommandDescriptor();

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

Register_ClassDescriptor(TcpSetTimeToLiveCommandDescriptor)

TcpSetTimeToLiveCommandDescriptor::TcpSetTimeToLiveCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpSetTimeToLiveCommand)), "inet::TcpSetOptionCommand")
{
    propertyNames = nullptr;
}

TcpSetTimeToLiveCommandDescriptor::~TcpSetTimeToLiveCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpSetTimeToLiveCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSetTimeToLiveCommand *>(obj)!=nullptr;
}

const char **TcpSetTimeToLiveCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSetTimeToLiveCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSetTimeToLiveCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpSetTimeToLiveCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ttl
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpSetTimeToLiveCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ttl",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpSetTimeToLiveCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSetTimeToLiveCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_ttl
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpSetTimeToLiveCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSetTimeToLiveCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSetTimeToLiveCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSetTimeToLiveCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSetTimeToLiveCommand'", field);
    }
}

const char *TcpSetTimeToLiveCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSetTimeToLiveCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: return long2string(pp->getTtl());
        default: return "";
    }
}

void TcpSetTimeToLiveCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: pp->setTtl(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTimeToLiveCommand'", field);
    }
}

omnetpp::cValue TcpSetTimeToLiveCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: return pp->getTtl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSetTimeToLiveCommand' as cValue -- field index out of range?", field);
    }
}

void TcpSetTimeToLiveCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        case FIELD_ttl: pp->setTtl(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTimeToLiveCommand'", field);
    }
}

const char *TcpSetTimeToLiveCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpSetTimeToLiveCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSetTimeToLiveCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTimeToLiveCommand *pp = omnetpp::fromAnyPtr<TcpSetTimeToLiveCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTimeToLiveCommand'", field);
    }
}

Register_Class(TcpSetDscpCommand)

TcpSetDscpCommand::TcpSetDscpCommand() : ::inet::TcpSetOptionCommand()
{
}

TcpSetDscpCommand::TcpSetDscpCommand(const TcpSetDscpCommand& other) : ::inet::TcpSetOptionCommand(other)
{
    copy(other);
}

TcpSetDscpCommand::~TcpSetDscpCommand()
{
}

TcpSetDscpCommand& TcpSetDscpCommand::operator=(const TcpSetDscpCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpSetDscpCommand::copy(const TcpSetDscpCommand& other)
{
    this->dscp = other.dscp;
}

void TcpSetDscpCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->dscp);
}

void TcpSetDscpCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->dscp);
}

short TcpSetDscpCommand::getDscp() const
{
    return this->dscp;
}

void TcpSetDscpCommand::setDscp(short dscp)
{
    this->dscp = dscp;
}

class TcpSetDscpCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dscp,
    };
  public:
    TcpSetDscpCommandDescriptor();
    virtual ~TcpSetDscpCommandDescriptor();

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

Register_ClassDescriptor(TcpSetDscpCommandDescriptor)

TcpSetDscpCommandDescriptor::TcpSetDscpCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpSetDscpCommand)), "inet::TcpSetOptionCommand")
{
    propertyNames = nullptr;
}

TcpSetDscpCommandDescriptor::~TcpSetDscpCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpSetDscpCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSetDscpCommand *>(obj)!=nullptr;
}

const char **TcpSetDscpCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSetDscpCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSetDscpCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpSetDscpCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dscp
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpSetDscpCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dscp",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpSetDscpCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dscp") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSetDscpCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_dscp
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpSetDscpCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSetDscpCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSetDscpCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSetDscpCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSetDscpCommand'", field);
    }
}

const char *TcpSetDscpCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSetDscpCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: return long2string(pp->getDscp());
        default: return "";
    }
}

void TcpSetDscpCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: pp->setDscp(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetDscpCommand'", field);
    }
}

omnetpp::cValue TcpSetDscpCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: return pp->getDscp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSetDscpCommand' as cValue -- field index out of range?", field);
    }
}

void TcpSetDscpCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        case FIELD_dscp: pp->setDscp(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetDscpCommand'", field);
    }
}

const char *TcpSetDscpCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpSetDscpCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSetDscpCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetDscpCommand *pp = omnetpp::fromAnyPtr<TcpSetDscpCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetDscpCommand'", field);
    }
}

Register_Class(TcpSetTosCommand)

TcpSetTosCommand::TcpSetTosCommand() : ::inet::TcpSetOptionCommand()
{
}

TcpSetTosCommand::TcpSetTosCommand(const TcpSetTosCommand& other) : ::inet::TcpSetOptionCommand(other)
{
    copy(other);
}

TcpSetTosCommand::~TcpSetTosCommand()
{
}

TcpSetTosCommand& TcpSetTosCommand::operator=(const TcpSetTosCommand& other)
{
    if (this == &other) return *this;
    ::inet::TcpSetOptionCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpSetTosCommand::copy(const TcpSetTosCommand& other)
{
    this->tos = other.tos;
}

void TcpSetTosCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpSetOptionCommand::parsimPack(b);
    doParsimPacking(b,this->tos);
}

void TcpSetTosCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpSetOptionCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->tos);
}

short TcpSetTosCommand::getTos() const
{
    return this->tos;
}

void TcpSetTosCommand::setTos(short tos)
{
    this->tos = tos;
}

class TcpSetTosCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tos,
    };
  public:
    TcpSetTosCommandDescriptor();
    virtual ~TcpSetTosCommandDescriptor();

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

Register_ClassDescriptor(TcpSetTosCommandDescriptor)

TcpSetTosCommandDescriptor::TcpSetTosCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpSetTosCommand)), "inet::TcpSetOptionCommand")
{
    propertyNames = nullptr;
}

TcpSetTosCommandDescriptor::~TcpSetTosCommandDescriptor()
{
    delete[] propertyNames;
}

bool TcpSetTosCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSetTosCommand *>(obj)!=nullptr;
}

const char **TcpSetTosCommandDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSetTosCommandDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSetTosCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpSetTosCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_tos
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpSetTosCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tos",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpSetTosCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tos") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSetTosCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_tos
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpSetTosCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSetTosCommandDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSetTosCommandDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSetTosCommandDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSetTosCommand'", field);
    }
}

const char *TcpSetTosCommandDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSetTosCommandDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return long2string(pp->getTos());
        default: return "";
    }
}

void TcpSetTosCommandDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->setTos(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTosCommand'", field);
    }
}

omnetpp::cValue TcpSetTosCommandDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: return pp->getTos();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSetTosCommand' as cValue -- field index out of range?", field);
    }
}

void TcpSetTosCommandDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        case FIELD_tos: pp->setTos(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTosCommand'", field);
    }
}

const char *TcpSetTosCommandDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpSetTosCommandDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSetTosCommandDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSetTosCommand *pp = omnetpp::fromAnyPtr<TcpSetTosCommand>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSetTosCommand'", field);
    }
}

Register_Class(TcpAvailableInfo)

TcpAvailableInfo::TcpAvailableInfo() : ::inet::TcpCommand()
{
}

TcpAvailableInfo::TcpAvailableInfo(const TcpAvailableInfo& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpAvailableInfo::~TcpAvailableInfo()
{
}

TcpAvailableInfo& TcpAvailableInfo::operator=(const TcpAvailableInfo& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpAvailableInfo::copy(const TcpAvailableInfo& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->newSocketId = other.newSocketId;
}

void TcpAvailableInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->newSocketId);
}

void TcpAvailableInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->newSocketId);
}

const L3Address& TcpAvailableInfo::getLocalAddr() const
{
    return this->localAddr;
}

void TcpAvailableInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& TcpAvailableInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void TcpAvailableInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int TcpAvailableInfo::getLocalPort() const
{
    return this->localPort;
}

void TcpAvailableInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int TcpAvailableInfo::getRemotePort() const
{
    return this->remotePort;
}

void TcpAvailableInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

int TcpAvailableInfo::getNewSocketId() const
{
    return this->newSocketId;
}

void TcpAvailableInfo::setNewSocketId(int newSocketId)
{
    this->newSocketId = newSocketId;
}

class TcpAvailableInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_newSocketId,
    };
  public:
    TcpAvailableInfoDescriptor();
    virtual ~TcpAvailableInfoDescriptor();

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

Register_ClassDescriptor(TcpAvailableInfoDescriptor)

TcpAvailableInfoDescriptor::TcpAvailableInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpAvailableInfo)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpAvailableInfoDescriptor::~TcpAvailableInfoDescriptor()
{
    delete[] propertyNames;
}

bool TcpAvailableInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpAvailableInfo *>(obj)!=nullptr;
}

const char **TcpAvailableInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpAvailableInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpAvailableInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int TcpAvailableInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_newSocketId
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TcpAvailableInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "newSocketId",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TcpAvailableInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "newSocketId") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpAvailableInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "int",    // FIELD_newSocketId
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpAvailableInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpAvailableInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpAvailableInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpAvailableInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpAvailableInfo'", field);
    }
}

const char *TcpAvailableInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpAvailableInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_newSocketId: return long2string(pp->getNewSocketId());
        default: return "";
    }
}

void TcpAvailableInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        case FIELD_newSocketId: pp->setNewSocketId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAvailableInfo'", field);
    }
}

omnetpp::cValue TcpAvailableInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        case FIELD_newSocketId: return pp->getNewSocketId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpAvailableInfo' as cValue -- field index out of range?", field);
    }
}

void TcpAvailableInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_newSocketId: pp->setNewSocketId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAvailableInfo'", field);
    }
}

const char *TcpAvailableInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpAvailableInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpAvailableInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAvailableInfo *pp = omnetpp::fromAnyPtr<TcpAvailableInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAvailableInfo'", field);
    }
}

Register_Class(TcpConnectInfo)

TcpConnectInfo::TcpConnectInfo() : ::inet::TcpCommand()
{
}

TcpConnectInfo::TcpConnectInfo(const TcpConnectInfo& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpConnectInfo::~TcpConnectInfo()
{
}

TcpConnectInfo& TcpConnectInfo::operator=(const TcpConnectInfo& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpConnectInfo::copy(const TcpConnectInfo& other)
{
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
}

void TcpConnectInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
}

void TcpConnectInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
}

const L3Address& TcpConnectInfo::getLocalAddr() const
{
    return this->localAddr;
}

void TcpConnectInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& TcpConnectInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void TcpConnectInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int TcpConnectInfo::getLocalPort() const
{
    return this->localPort;
}

void TcpConnectInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int TcpConnectInfo::getRemotePort() const
{
    return this->remotePort;
}

void TcpConnectInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

class TcpConnectInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
    };
  public:
    TcpConnectInfoDescriptor();
    virtual ~TcpConnectInfoDescriptor();

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

Register_ClassDescriptor(TcpConnectInfoDescriptor)

TcpConnectInfoDescriptor::TcpConnectInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpConnectInfo)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpConnectInfoDescriptor::~TcpConnectInfoDescriptor()
{
    delete[] propertyNames;
}

bool TcpConnectInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpConnectInfo *>(obj)!=nullptr;
}

const char **TcpConnectInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpConnectInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpConnectInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int TcpConnectInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *TcpConnectInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int TcpConnectInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpConnectInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpConnectInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpConnectInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpConnectInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpConnectInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpConnectInfo'", field);
    }
}

const char *TcpConnectInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpConnectInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        default: return "";
    }
}

void TcpConnectInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnectInfo'", field);
    }
}

omnetpp::cValue TcpConnectInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpConnectInfo' as cValue -- field index out of range?", field);
    }
}

void TcpConnectInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnectInfo'", field);
    }
}

const char *TcpConnectInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpConnectInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpConnectInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnectInfo *pp = omnetpp::fromAnyPtr<TcpConnectInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnectInfo'", field);
    }
}

Register_Class(TcpStatusInfo)

TcpStatusInfo::TcpStatusInfo() : ::inet::TcpCommand()
{
}

TcpStatusInfo::TcpStatusInfo(const TcpStatusInfo& other) : ::inet::TcpCommand(other)
{
    copy(other);
}

TcpStatusInfo::~TcpStatusInfo()
{
}

TcpStatusInfo& TcpStatusInfo::operator=(const TcpStatusInfo& other)
{
    if (this == &other) return *this;
    ::inet::TcpCommand::operator=(other);
    copy(other);
    return *this;
}

void TcpStatusInfo::copy(const TcpStatusInfo& other)
{
    this->state = other.state;
    this->stateName = other.stateName;
    this->localAddr = other.localAddr;
    this->remoteAddr = other.remoteAddr;
    this->localPort = other.localPort;
    this->remotePort = other.remotePort;
    this->snd_mss = other.snd_mss;
    this->snd_una = other.snd_una;
    this->snd_nxt = other.snd_nxt;
    this->snd_max = other.snd_max;
    this->snd_wnd = other.snd_wnd;
    this->snd_up = other.snd_up;
    this->snd_wl1 = other.snd_wl1;
    this->snd_wl2 = other.snd_wl2;
    this->iss = other.iss;
    this->rcv_nxt = other.rcv_nxt;
    this->rcv_wnd = other.rcv_wnd;
    this->rcv_up = other.rcv_up;
    this->irs = other.irs;
    this->fin_ack_rcvd = other.fin_ack_rcvd;
}

void TcpStatusInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TcpCommand::parsimPack(b);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->stateName);
    doParsimPacking(b,this->localAddr);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->remotePort);
    doParsimPacking(b,this->snd_mss);
    doParsimPacking(b,this->snd_una);
    doParsimPacking(b,this->snd_nxt);
    doParsimPacking(b,this->snd_max);
    doParsimPacking(b,this->snd_wnd);
    doParsimPacking(b,this->snd_up);
    doParsimPacking(b,this->snd_wl1);
    doParsimPacking(b,this->snd_wl2);
    doParsimPacking(b,this->iss);
    doParsimPacking(b,this->rcv_nxt);
    doParsimPacking(b,this->rcv_wnd);
    doParsimPacking(b,this->rcv_up);
    doParsimPacking(b,this->irs);
    doParsimPacking(b,this->fin_ack_rcvd);
}

void TcpStatusInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TcpCommand::parsimUnpack(b);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->stateName);
    doParsimUnpacking(b,this->localAddr);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->remotePort);
    doParsimUnpacking(b,this->snd_mss);
    doParsimUnpacking(b,this->snd_una);
    doParsimUnpacking(b,this->snd_nxt);
    doParsimUnpacking(b,this->snd_max);
    doParsimUnpacking(b,this->snd_wnd);
    doParsimUnpacking(b,this->snd_up);
    doParsimUnpacking(b,this->snd_wl1);
    doParsimUnpacking(b,this->snd_wl2);
    doParsimUnpacking(b,this->iss);
    doParsimUnpacking(b,this->rcv_nxt);
    doParsimUnpacking(b,this->rcv_wnd);
    doParsimUnpacking(b,this->rcv_up);
    doParsimUnpacking(b,this->irs);
    doParsimUnpacking(b,this->fin_ack_rcvd);
}

int TcpStatusInfo::getState() const
{
    return this->state;
}

void TcpStatusInfo::setState(int state)
{
    this->state = state;
}

const char * TcpStatusInfo::getStateName() const
{
    return this->stateName.c_str();
}

void TcpStatusInfo::setStateName(const char * stateName)
{
    this->stateName = stateName;
}

const L3Address& TcpStatusInfo::getLocalAddr() const
{
    return this->localAddr;
}

void TcpStatusInfo::setLocalAddr(const L3Address& localAddr)
{
    this->localAddr = localAddr;
}

const L3Address& TcpStatusInfo::getRemoteAddr() const
{
    return this->remoteAddr;
}

void TcpStatusInfo::setRemoteAddr(const L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

int TcpStatusInfo::getLocalPort() const
{
    return this->localPort;
}

void TcpStatusInfo::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

int TcpStatusInfo::getRemotePort() const
{
    return this->remotePort;
}

void TcpStatusInfo::setRemotePort(int remotePort)
{
    this->remotePort = remotePort;
}

unsigned int TcpStatusInfo::getSnd_mss() const
{
    return this->snd_mss;
}

void TcpStatusInfo::setSnd_mss(unsigned int snd_mss)
{
    this->snd_mss = snd_mss;
}

unsigned int TcpStatusInfo::getSnd_una() const
{
    return this->snd_una;
}

void TcpStatusInfo::setSnd_una(unsigned int snd_una)
{
    this->snd_una = snd_una;
}

unsigned int TcpStatusInfo::getSnd_nxt() const
{
    return this->snd_nxt;
}

void TcpStatusInfo::setSnd_nxt(unsigned int snd_nxt)
{
    this->snd_nxt = snd_nxt;
}

unsigned int TcpStatusInfo::getSnd_max() const
{
    return this->snd_max;
}

void TcpStatusInfo::setSnd_max(unsigned int snd_max)
{
    this->snd_max = snd_max;
}

unsigned int TcpStatusInfo::getSnd_wnd() const
{
    return this->snd_wnd;
}

void TcpStatusInfo::setSnd_wnd(unsigned int snd_wnd)
{
    this->snd_wnd = snd_wnd;
}

unsigned int TcpStatusInfo::getSnd_up() const
{
    return this->snd_up;
}

void TcpStatusInfo::setSnd_up(unsigned int snd_up)
{
    this->snd_up = snd_up;
}

unsigned int TcpStatusInfo::getSnd_wl1() const
{
    return this->snd_wl1;
}

void TcpStatusInfo::setSnd_wl1(unsigned int snd_wl1)
{
    this->snd_wl1 = snd_wl1;
}

unsigned int TcpStatusInfo::getSnd_wl2() const
{
    return this->snd_wl2;
}

void TcpStatusInfo::setSnd_wl2(unsigned int snd_wl2)
{
    this->snd_wl2 = snd_wl2;
}

unsigned int TcpStatusInfo::getIss() const
{
    return this->iss;
}

void TcpStatusInfo::setIss(unsigned int iss)
{
    this->iss = iss;
}

unsigned int TcpStatusInfo::getRcv_nxt() const
{
    return this->rcv_nxt;
}

void TcpStatusInfo::setRcv_nxt(unsigned int rcv_nxt)
{
    this->rcv_nxt = rcv_nxt;
}

unsigned int TcpStatusInfo::getRcv_wnd() const
{
    return this->rcv_wnd;
}

void TcpStatusInfo::setRcv_wnd(unsigned int rcv_wnd)
{
    this->rcv_wnd = rcv_wnd;
}

unsigned int TcpStatusInfo::getRcv_up() const
{
    return this->rcv_up;
}

void TcpStatusInfo::setRcv_up(unsigned int rcv_up)
{
    this->rcv_up = rcv_up;
}

unsigned int TcpStatusInfo::getIrs() const
{
    return this->irs;
}

void TcpStatusInfo::setIrs(unsigned int irs)
{
    this->irs = irs;
}

bool TcpStatusInfo::getFin_ack_rcvd() const
{
    return this->fin_ack_rcvd;
}

void TcpStatusInfo::setFin_ack_rcvd(bool fin_ack_rcvd)
{
    this->fin_ack_rcvd = fin_ack_rcvd;
}

class TcpStatusInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_state,
        FIELD_stateName,
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_snd_mss,
        FIELD_snd_una,
        FIELD_snd_nxt,
        FIELD_snd_max,
        FIELD_snd_wnd,
        FIELD_snd_up,
        FIELD_snd_wl1,
        FIELD_snd_wl2,
        FIELD_iss,
        FIELD_rcv_nxt,
        FIELD_rcv_wnd,
        FIELD_rcv_up,
        FIELD_irs,
        FIELD_fin_ack_rcvd,
    };
  public:
    TcpStatusInfoDescriptor();
    virtual ~TcpStatusInfoDescriptor();

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

Register_ClassDescriptor(TcpStatusInfoDescriptor)

TcpStatusInfoDescriptor::TcpStatusInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TcpStatusInfo)), "inet::TcpCommand")
{
    propertyNames = nullptr;
}

TcpStatusInfoDescriptor::~TcpStatusInfoDescriptor()
{
    delete[] propertyNames;
}

bool TcpStatusInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpStatusInfo *>(obj)!=nullptr;
}

const char **TcpStatusInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpStatusInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpStatusInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 20+base->getFieldCount() : 20;
}

unsigned int TcpStatusInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_state
        FD_ISEDITABLE,    // FIELD_stateName
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_remotePort
        FD_ISEDITABLE,    // FIELD_snd_mss
        FD_ISEDITABLE,    // FIELD_snd_una
        FD_ISEDITABLE,    // FIELD_snd_nxt
        FD_ISEDITABLE,    // FIELD_snd_max
        FD_ISEDITABLE,    // FIELD_snd_wnd
        FD_ISEDITABLE,    // FIELD_snd_up
        FD_ISEDITABLE,    // FIELD_snd_wl1
        FD_ISEDITABLE,    // FIELD_snd_wl2
        FD_ISEDITABLE,    // FIELD_iss
        FD_ISEDITABLE,    // FIELD_rcv_nxt
        FD_ISEDITABLE,    // FIELD_rcv_wnd
        FD_ISEDITABLE,    // FIELD_rcv_up
        FD_ISEDITABLE,    // FIELD_irs
        FD_ISEDITABLE,    // FIELD_fin_ack_rcvd
    };
    return (field >= 0 && field < 20) ? fieldTypeFlags[field] : 0;
}

const char *TcpStatusInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "state",
        "stateName",
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "snd_mss",
        "snd_una",
        "snd_nxt",
        "snd_max",
        "snd_wnd",
        "snd_up",
        "snd_wl1",
        "snd_wl2",
        "iss",
        "rcv_nxt",
        "rcv_wnd",
        "rcv_up",
        "irs",
        "fin_ack_rcvd",
    };
    return (field >= 0 && field < 20) ? fieldNames[field] : nullptr;
}

int TcpStatusInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "state") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "stateName") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "snd_mss") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "snd_una") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "snd_nxt") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "snd_max") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "snd_wnd") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "snd_up") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "snd_wl1") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "snd_wl2") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "iss") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "rcv_nxt") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "rcv_wnd") == 0) return baseIndex + 16;
    if (strcmp(fieldName, "rcv_up") == 0) return baseIndex + 17;
    if (strcmp(fieldName, "irs") == 0) return baseIndex + 18;
    if (strcmp(fieldName, "fin_ack_rcvd") == 0) return baseIndex + 19;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpStatusInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_state
        "string",    // FIELD_stateName
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "unsigned int",    // FIELD_snd_mss
        "unsigned int",    // FIELD_snd_una
        "unsigned int",    // FIELD_snd_nxt
        "unsigned int",    // FIELD_snd_max
        "unsigned int",    // FIELD_snd_wnd
        "unsigned int",    // FIELD_snd_up
        "unsigned int",    // FIELD_snd_wl1
        "unsigned int",    // FIELD_snd_wl2
        "unsigned int",    // FIELD_iss
        "unsigned int",    // FIELD_rcv_nxt
        "unsigned int",    // FIELD_rcv_wnd
        "unsigned int",    // FIELD_rcv_up
        "unsigned int",    // FIELD_irs
        "bool",    // FIELD_fin_ack_rcvd
    };
    return (field >= 0 && field < 20) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpStatusInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpStatusInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpStatusInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpStatusInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpStatusInfo'", field);
    }
}

const char *TcpStatusInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpStatusInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        case FIELD_state: return long2string(pp->getState());
        case FIELD_stateName: return oppstring2string(pp->getStateName());
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_snd_mss: return ulong2string(pp->getSnd_mss());
        case FIELD_snd_una: return ulong2string(pp->getSnd_una());
        case FIELD_snd_nxt: return ulong2string(pp->getSnd_nxt());
        case FIELD_snd_max: return ulong2string(pp->getSnd_max());
        case FIELD_snd_wnd: return ulong2string(pp->getSnd_wnd());
        case FIELD_snd_up: return ulong2string(pp->getSnd_up());
        case FIELD_snd_wl1: return ulong2string(pp->getSnd_wl1());
        case FIELD_snd_wl2: return ulong2string(pp->getSnd_wl2());
        case FIELD_iss: return ulong2string(pp->getIss());
        case FIELD_rcv_nxt: return ulong2string(pp->getRcv_nxt());
        case FIELD_rcv_wnd: return ulong2string(pp->getRcv_wnd());
        case FIELD_rcv_up: return ulong2string(pp->getRcv_up());
        case FIELD_irs: return ulong2string(pp->getIrs());
        case FIELD_fin_ack_rcvd: return bool2string(pp->getFin_ack_rcvd());
        default: return "";
    }
}

void TcpStatusInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        case FIELD_state: pp->setState(string2long(value)); break;
        case FIELD_stateName: pp->setStateName((value)); break;
        case FIELD_localPort: pp->setLocalPort(string2long(value)); break;
        case FIELD_remotePort: pp->setRemotePort(string2long(value)); break;
        case FIELD_snd_mss: pp->setSnd_mss(string2ulong(value)); break;
        case FIELD_snd_una: pp->setSnd_una(string2ulong(value)); break;
        case FIELD_snd_nxt: pp->setSnd_nxt(string2ulong(value)); break;
        case FIELD_snd_max: pp->setSnd_max(string2ulong(value)); break;
        case FIELD_snd_wnd: pp->setSnd_wnd(string2ulong(value)); break;
        case FIELD_snd_up: pp->setSnd_up(string2ulong(value)); break;
        case FIELD_snd_wl1: pp->setSnd_wl1(string2ulong(value)); break;
        case FIELD_snd_wl2: pp->setSnd_wl2(string2ulong(value)); break;
        case FIELD_iss: pp->setIss(string2ulong(value)); break;
        case FIELD_rcv_nxt: pp->setRcv_nxt(string2ulong(value)); break;
        case FIELD_rcv_wnd: pp->setRcv_wnd(string2ulong(value)); break;
        case FIELD_rcv_up: pp->setRcv_up(string2ulong(value)); break;
        case FIELD_irs: pp->setIrs(string2ulong(value)); break;
        case FIELD_fin_ack_rcvd: pp->setFin_ack_rcvd(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStatusInfo'", field);
    }
}

omnetpp::cValue TcpStatusInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        case FIELD_state: return pp->getState();
        case FIELD_stateName: return pp->getStateName();
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        case FIELD_snd_mss: return (omnetpp::intval_t)(pp->getSnd_mss());
        case FIELD_snd_una: return (omnetpp::intval_t)(pp->getSnd_una());
        case FIELD_snd_nxt: return (omnetpp::intval_t)(pp->getSnd_nxt());
        case FIELD_snd_max: return (omnetpp::intval_t)(pp->getSnd_max());
        case FIELD_snd_wnd: return (omnetpp::intval_t)(pp->getSnd_wnd());
        case FIELD_snd_up: return (omnetpp::intval_t)(pp->getSnd_up());
        case FIELD_snd_wl1: return (omnetpp::intval_t)(pp->getSnd_wl1());
        case FIELD_snd_wl2: return (omnetpp::intval_t)(pp->getSnd_wl2());
        case FIELD_iss: return (omnetpp::intval_t)(pp->getIss());
        case FIELD_rcv_nxt: return (omnetpp::intval_t)(pp->getRcv_nxt());
        case FIELD_rcv_wnd: return (omnetpp::intval_t)(pp->getRcv_wnd());
        case FIELD_rcv_up: return (omnetpp::intval_t)(pp->getRcv_up());
        case FIELD_irs: return (omnetpp::intval_t)(pp->getIrs());
        case FIELD_fin_ack_rcvd: return pp->getFin_ack_rcvd();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpStatusInfo' as cValue -- field index out of range?", field);
    }
}

void TcpStatusInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        case FIELD_state: pp->setState(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_stateName: pp->setStateName(value.stringValue()); break;
        case FIELD_localPort: pp->setLocalPort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_remotePort: pp->setRemotePort(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_snd_mss: pp->setSnd_mss(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_una: pp->setSnd_una(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_nxt: pp->setSnd_nxt(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_max: pp->setSnd_max(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_wnd: pp->setSnd_wnd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_up: pp->setSnd_up(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_wl1: pp->setSnd_wl1(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_snd_wl2: pp->setSnd_wl2(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_iss: pp->setIss(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_rcv_nxt: pp->setRcv_nxt(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_rcv_wnd: pp->setRcv_wnd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_rcv_up: pp->setRcv_up(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_irs: pp->setIrs(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_fin_ack_rcvd: pp->setFin_ack_rcvd(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStatusInfo'", field);
    }
}

const char *TcpStatusInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpStatusInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpStatusInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStatusInfo *pp = omnetpp::fromAnyPtr<TcpStatusInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStatusInfo'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

