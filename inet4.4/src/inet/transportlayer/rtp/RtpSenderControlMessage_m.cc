//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtpSenderControlMessage.msg.
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
#include "RtpSenderControlMessage_m.h"

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

Register_Enum(inet::rtp::RtpSenderControlMessageCommands, (inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_PLAY, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_PLAY_UNTIL_TIME, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_PLAY_UNTIL_BYTE, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_PAUSE, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_STOP, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_SEEK_TIME, inet::rtp::RtpSenderControlMessageCommands::RTP_CONTROL_SEEK_BYTE));

Register_Class(RtpSenderControlMessage)

RtpSenderControlMessage::RtpSenderControlMessage(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

RtpSenderControlMessage::RtpSenderControlMessage(const RtpSenderControlMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RtpSenderControlMessage::~RtpSenderControlMessage()
{
}

RtpSenderControlMessage& RtpSenderControlMessage::operator=(const RtpSenderControlMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RtpSenderControlMessage::copy(const RtpSenderControlMessage& other)
{
    this->command = other.command;
    this->commandParameter1 = other.commandParameter1;
    this->commandParameter2 = other.commandParameter2;
}

void RtpSenderControlMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->command);
    doParsimPacking(b,this->commandParameter1);
    doParsimPacking(b,this->commandParameter2);
}

void RtpSenderControlMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->command);
    doParsimUnpacking(b,this->commandParameter1);
    doParsimUnpacking(b,this->commandParameter2);
}

RtpSenderControlMessageCommands RtpSenderControlMessage::getCommand() const
{
    return this->command;
}

void RtpSenderControlMessage::setCommand(RtpSenderControlMessageCommands command)
{
    this->command = command;
}

float RtpSenderControlMessage::getCommandParameter1() const
{
    return this->commandParameter1;
}

void RtpSenderControlMessage::setCommandParameter1(float commandParameter1)
{
    this->commandParameter1 = commandParameter1;
}

float RtpSenderControlMessage::getCommandParameter2() const
{
    return this->commandParameter2;
}

void RtpSenderControlMessage::setCommandParameter2(float commandParameter2)
{
    this->commandParameter2 = commandParameter2;
}

class RtpSenderControlMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_command,
        FIELD_commandParameter1,
        FIELD_commandParameter2,
    };
  public:
    RtpSenderControlMessageDescriptor();
    virtual ~RtpSenderControlMessageDescriptor();

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

Register_ClassDescriptor(RtpSenderControlMessageDescriptor)

RtpSenderControlMessageDescriptor::RtpSenderControlMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpSenderControlMessage)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

RtpSenderControlMessageDescriptor::~RtpSenderControlMessageDescriptor()
{
    delete[] propertyNames;
}

bool RtpSenderControlMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpSenderControlMessage *>(obj)!=nullptr;
}

const char **RtpSenderControlMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpSenderControlMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpSenderControlMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RtpSenderControlMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_command
        FD_ISEDITABLE,    // FIELD_commandParameter1
        FD_ISEDITABLE,    // FIELD_commandParameter2
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RtpSenderControlMessageDescriptor::getFieldName(int field) const
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

int RtpSenderControlMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "command") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "commandParameter1") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "commandParameter2") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpSenderControlMessageDescriptor::getFieldTypeString(int field) const
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

const char **RtpSenderControlMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpSenderControlMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpSenderControlMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpSenderControlMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpSenderControlMessage'", field);
    }
}

const char *RtpSenderControlMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpSenderControlMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        case FIELD_command: return enum2string(pp->getCommand(), "inet::rtp::RtpSenderControlMessageCommands");
        case FIELD_commandParameter1: return double2string(pp->getCommandParameter1());
        case FIELD_commandParameter2: return double2string(pp->getCommandParameter2());
        default: return "";
    }
}

void RtpSenderControlMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        case FIELD_commandParameter1: pp->setCommandParameter1(string2double(value)); break;
        case FIELD_commandParameter2: pp->setCommandParameter2(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSenderControlMessage'", field);
    }
}

omnetpp::cValue RtpSenderControlMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        case FIELD_command: return static_cast<int>(pp->getCommand());
        case FIELD_commandParameter1: return (double)(pp->getCommandParameter1());
        case FIELD_commandParameter2: return (double)(pp->getCommandParameter2());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpSenderControlMessage' as cValue -- field index out of range?", field);
    }
}

void RtpSenderControlMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        case FIELD_commandParameter1: pp->setCommandParameter1(static_cast<float>(value.doubleValue())); break;
        case FIELD_commandParameter2: pp->setCommandParameter2(static_cast<float>(value.doubleValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSenderControlMessage'", field);
    }
}

const char *RtpSenderControlMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpSenderControlMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpSenderControlMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpSenderControlMessage *pp = omnetpp::fromAnyPtr<RtpSenderControlMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpSenderControlMessage'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

