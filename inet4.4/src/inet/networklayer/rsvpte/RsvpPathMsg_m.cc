//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/RsvpPathMsg.msg.
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
#include "RsvpPathMsg_m.h"

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

Register_Class(RsvpPathMsg)

RsvpPathMsg::RsvpPathMsg() : ::inet::RsvpPacket()
{
    this->setRsvpKind(PATH_MESSAGE);

}

RsvpPathMsg::RsvpPathMsg(const RsvpPathMsg& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpPathMsg::~RsvpPathMsg()
{
}

RsvpPathMsg& RsvpPathMsg::operator=(const RsvpPathMsg& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpPathMsg::copy(const RsvpPathMsg& other)
{
    this->hop = other.hop;
    this->label_request = other.label_request;
    this->sender_descriptor = other.sender_descriptor;
    this->ERO = other.ERO;
    this->color = other.color;
}

void RsvpPathMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->label_request);
    doParsimPacking(b,this->sender_descriptor);
    doParsimPacking(b,this->ERO);
    doParsimPacking(b,this->color);
}

void RsvpPathMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->label_request);
    doParsimUnpacking(b,this->sender_descriptor);
    doParsimUnpacking(b,this->ERO);
    doParsimUnpacking(b,this->color);
}

const RsvpHopObj& RsvpPathMsg::getHop() const
{
    return this->hop;
}

void RsvpPathMsg::setHop(const RsvpHopObj& hop)
{
    handleChange();
    this->hop = hop;
}

const LabelRequestObj& RsvpPathMsg::getLabel_request() const
{
    return this->label_request;
}

void RsvpPathMsg::setLabel_request(const LabelRequestObj& label_request)
{
    handleChange();
    this->label_request = label_request;
}

const SenderDescriptor_t& RsvpPathMsg::getSender_descriptor() const
{
    return this->sender_descriptor;
}

void RsvpPathMsg::setSender_descriptor(const SenderDescriptor_t& sender_descriptor)
{
    handleChange();
    this->sender_descriptor = sender_descriptor;
}

const EroVector& RsvpPathMsg::getERO() const
{
    return this->ERO;
}

void RsvpPathMsg::setERO(const EroVector& ERO)
{
    handleChange();
    this->ERO = ERO;
}

int RsvpPathMsg::getColor() const
{
    return this->color;
}

void RsvpPathMsg::setColor(int color)
{
    handleChange();
    this->color = color;
}

class RsvpPathMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hop,
        FIELD_label_request,
        FIELD_sender_descriptor,
        FIELD_ERO,
        FIELD_color,
    };
  public:
    RsvpPathMsgDescriptor();
    virtual ~RsvpPathMsgDescriptor();

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

Register_ClassDescriptor(RsvpPathMsgDescriptor)

RsvpPathMsgDescriptor::RsvpPathMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpPathMsg)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpPathMsgDescriptor::~RsvpPathMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsvpPathMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpPathMsg *>(obj)!=nullptr;
}

const char **RsvpPathMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpPathMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpPathMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RsvpPathMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_hop
        FD_ISCOMPOUND,    // FIELD_label_request
        FD_ISCOMPOUND,    // FIELD_sender_descriptor
        FD_ISCOMPOUND,    // FIELD_ERO
        FD_ISEDITABLE,    // FIELD_color
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RsvpPathMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hop",
        "label_request",
        "sender_descriptor",
        "ERO",
        "color",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RsvpPathMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "label_request") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sender_descriptor") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ERO") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "color") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpPathMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RsvpHopObj",    // FIELD_hop
        "inet::LabelRequestObj",    // FIELD_label_request
        "inet::SenderDescriptor_t",    // FIELD_sender_descriptor
        "inet::EroVector",    // FIELD_ERO
        "int",    // FIELD_color
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpPathMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpPathMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpPathMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpPathMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpPathMsg'", field);
    }
}

const char *RsvpPathMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpPathMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return "";
        case FIELD_label_request: return "";
        case FIELD_sender_descriptor: return "";
        case FIELD_ERO: return "";
        case FIELD_color: return long2string(pp->getColor());
        default: return "";
    }
}

void RsvpPathMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        case FIELD_color: pp->setColor(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathMsg'", field);
    }
}

omnetpp::cValue RsvpPathMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_label_request: return omnetpp::toAnyPtr(&pp->getLabel_request()); break;
        case FIELD_sender_descriptor: return omnetpp::toAnyPtr(&pp->getSender_descriptor()); break;
        case FIELD_ERO: return omnetpp::toAnyPtr(&pp->getERO()); break;
        case FIELD_color: return pp->getColor();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpPathMsg' as cValue -- field index out of range?", field);
    }
}

void RsvpPathMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        case FIELD_color: pp->setColor(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathMsg'", field);
    }
}

const char *RsvpPathMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hop: return omnetpp::opp_typename(typeid(RsvpHopObj));
        case FIELD_label_request: return omnetpp::opp_typename(typeid(LabelRequestObj));
        case FIELD_sender_descriptor: return omnetpp::opp_typename(typeid(SenderDescriptor_t));
        case FIELD_ERO: return omnetpp::opp_typename(typeid(EroVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpPathMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_label_request: return omnetpp::toAnyPtr(&pp->getLabel_request()); break;
        case FIELD_sender_descriptor: return omnetpp::toAnyPtr(&pp->getSender_descriptor()); break;
        case FIELD_ERO: return omnetpp::toAnyPtr(&pp->getERO()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpPathMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathMsg *pp = omnetpp::fromAnyPtr<RsvpPathMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathMsg'", field);
    }
}

Register_Class(RsvpPathTear)

RsvpPathTear::RsvpPathTear() : ::inet::RsvpPacket()
{
    this->setRsvpKind(PTEAR_MESSAGE);

}

RsvpPathTear::RsvpPathTear(const RsvpPathTear& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpPathTear::~RsvpPathTear()
{
}

RsvpPathTear& RsvpPathTear::operator=(const RsvpPathTear& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpPathTear::copy(const RsvpPathTear& other)
{
    this->hop = other.hop;
    this->senderTemplate = other.senderTemplate;
    this->force = other.force;
}

void RsvpPathTear::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->senderTemplate);
    doParsimPacking(b,this->force);
}

void RsvpPathTear::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->senderTemplate);
    doParsimUnpacking(b,this->force);
}

const RsvpHopObj& RsvpPathTear::getHop() const
{
    return this->hop;
}

void RsvpPathTear::setHop(const RsvpHopObj& hop)
{
    handleChange();
    this->hop = hop;
}

const SenderTemplateObj& RsvpPathTear::getSenderTemplate() const
{
    return this->senderTemplate;
}

void RsvpPathTear::setSenderTemplate(const SenderTemplateObj& senderTemplate)
{
    handleChange();
    this->senderTemplate = senderTemplate;
}

bool RsvpPathTear::getForce() const
{
    return this->force;
}

void RsvpPathTear::setForce(bool force)
{
    handleChange();
    this->force = force;
}

class RsvpPathTearDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hop,
        FIELD_senderTemplate,
        FIELD_force,
    };
  public:
    RsvpPathTearDescriptor();
    virtual ~RsvpPathTearDescriptor();

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

Register_ClassDescriptor(RsvpPathTearDescriptor)

RsvpPathTearDescriptor::RsvpPathTearDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpPathTear)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpPathTearDescriptor::~RsvpPathTearDescriptor()
{
    delete[] propertyNames;
}

bool RsvpPathTearDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpPathTear *>(obj)!=nullptr;
}

const char **RsvpPathTearDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpPathTearDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpPathTearDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RsvpPathTearDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_hop
        FD_ISCOMPOUND,    // FIELD_senderTemplate
        FD_ISEDITABLE,    // FIELD_force
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RsvpPathTearDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hop",
        "senderTemplate",
        "force",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RsvpPathTearDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "senderTemplate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "force") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpPathTearDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RsvpHopObj",    // FIELD_hop
        "inet::SenderTemplateObj",    // FIELD_senderTemplate
        "bool",    // FIELD_force
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpPathTearDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpPathTearDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpPathTearDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpPathTearDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpPathTear'", field);
    }
}

const char *RsvpPathTearDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpPathTearDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return "";
        case FIELD_senderTemplate: return "";
        case FIELD_force: return bool2string(pp->getForce());
        default: return "";
    }
}

void RsvpPathTearDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        case FIELD_force: pp->setForce(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathTear'", field);
    }
}

omnetpp::cValue RsvpPathTearDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_senderTemplate: return omnetpp::toAnyPtr(&pp->getSenderTemplate()); break;
        case FIELD_force: return pp->getForce();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpPathTear' as cValue -- field index out of range?", field);
    }
}

void RsvpPathTearDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        case FIELD_force: pp->setForce(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathTear'", field);
    }
}

const char *RsvpPathTearDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hop: return omnetpp::opp_typename(typeid(RsvpHopObj));
        case FIELD_senderTemplate: return omnetpp::opp_typename(typeid(SenderTemplateObj));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpPathTearDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_senderTemplate: return omnetpp::toAnyPtr(&pp->getSenderTemplate()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpPathTearDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathTear *pp = omnetpp::fromAnyPtr<RsvpPathTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathTear'", field);
    }
}

Register_Class(RsvpPathError)

RsvpPathError::RsvpPathError() : ::inet::RsvpPacket()
{
    this->setRsvpKind(PERROR_MESSAGE);

}

RsvpPathError::RsvpPathError(const RsvpPathError& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpPathError::~RsvpPathError()
{
}

RsvpPathError& RsvpPathError::operator=(const RsvpPathError& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpPathError::copy(const RsvpPathError& other)
{
    this->errorNode = other.errorNode;
    this->errorCode = other.errorCode;
    this->sender_descriptor = other.sender_descriptor;
}

void RsvpPathError::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->errorNode);
    doParsimPacking(b,this->errorCode);
    doParsimPacking(b,this->sender_descriptor);
}

void RsvpPathError::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->errorNode);
    doParsimUnpacking(b,this->errorCode);
    doParsimUnpacking(b,this->sender_descriptor);
}

const Ipv4Address& RsvpPathError::getErrorNode() const
{
    return this->errorNode;
}

void RsvpPathError::setErrorNode(const Ipv4Address& errorNode)
{
    handleChange();
    this->errorNode = errorNode;
}

int RsvpPathError::getErrorCode() const
{
    return this->errorCode;
}

void RsvpPathError::setErrorCode(int errorCode)
{
    handleChange();
    this->errorCode = errorCode;
}

const SenderDescriptor_t& RsvpPathError::getSender_descriptor() const
{
    return this->sender_descriptor;
}

void RsvpPathError::setSender_descriptor(const SenderDescriptor_t& sender_descriptor)
{
    handleChange();
    this->sender_descriptor = sender_descriptor;
}

class RsvpPathErrorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_errorNode,
        FIELD_errorCode,
        FIELD_sender_descriptor,
    };
  public:
    RsvpPathErrorDescriptor();
    virtual ~RsvpPathErrorDescriptor();

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

Register_ClassDescriptor(RsvpPathErrorDescriptor)

RsvpPathErrorDescriptor::RsvpPathErrorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpPathError)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpPathErrorDescriptor::~RsvpPathErrorDescriptor()
{
    delete[] propertyNames;
}

bool RsvpPathErrorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpPathError *>(obj)!=nullptr;
}

const char **RsvpPathErrorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpPathErrorDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpPathErrorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RsvpPathErrorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_errorNode
        FD_ISEDITABLE,    // FIELD_errorCode
        FD_ISCOMPOUND,    // FIELD_sender_descriptor
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RsvpPathErrorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "errorNode",
        "errorCode",
        "sender_descriptor",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RsvpPathErrorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "errorNode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "errorCode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sender_descriptor") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpPathErrorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_errorNode
        "int",    // FIELD_errorCode
        "inet::SenderDescriptor_t",    // FIELD_sender_descriptor
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpPathErrorDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpPathErrorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpPathErrorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpPathErrorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpPathError'", field);
    }
}

const char *RsvpPathErrorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpPathErrorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        case FIELD_errorNode: return pp->getErrorNode().str();
        case FIELD_errorCode: return long2string(pp->getErrorCode());
        case FIELD_sender_descriptor: return "";
        default: return "";
    }
}

void RsvpPathErrorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: pp->setErrorCode(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathError'", field);
    }
}

omnetpp::cValue RsvpPathErrorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        case FIELD_errorNode: return omnetpp::toAnyPtr(&pp->getErrorNode()); break;
        case FIELD_errorCode: return pp->getErrorCode();
        case FIELD_sender_descriptor: return omnetpp::toAnyPtr(&pp->getSender_descriptor()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpPathError' as cValue -- field index out of range?", field);
    }
}

void RsvpPathErrorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: pp->setErrorCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathError'", field);
    }
}

const char *RsvpPathErrorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sender_descriptor: return omnetpp::opp_typename(typeid(SenderDescriptor_t));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpPathErrorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        case FIELD_errorNode: return omnetpp::toAnyPtr(&pp->getErrorNode()); break;
        case FIELD_sender_descriptor: return omnetpp::toAnyPtr(&pp->getSender_descriptor()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpPathErrorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpPathError *pp = omnetpp::fromAnyPtr<RsvpPathError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpPathError'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

