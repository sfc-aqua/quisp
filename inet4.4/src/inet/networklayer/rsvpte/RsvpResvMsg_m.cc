//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/RsvpResvMsg.msg.
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
#include "RsvpResvMsg_m.h"

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

Register_Class(RsvpResvMsg)

RsvpResvMsg::RsvpResvMsg() : ::inet::RsvpPacket()
{
    this->setRsvpKind(RESV_MESSAGE);

}

RsvpResvMsg::RsvpResvMsg(const RsvpResvMsg& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpResvMsg::~RsvpResvMsg()
{
}

RsvpResvMsg& RsvpResvMsg::operator=(const RsvpResvMsg& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpResvMsg::copy(const RsvpResvMsg& other)
{
    this->hop = other.hop;
    this->flowDescriptor = other.flowDescriptor;
}

void RsvpResvMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->flowDescriptor);
}

void RsvpResvMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->flowDescriptor);
}

const RsvpHopObj& RsvpResvMsg::getHop() const
{
    return this->hop;
}

void RsvpResvMsg::setHop(const RsvpHopObj& hop)
{
    handleChange();
    this->hop = hop;
}

const FlowDescriptorVector& RsvpResvMsg::getFlowDescriptor() const
{
    return this->flowDescriptor;
}

void RsvpResvMsg::setFlowDescriptor(const FlowDescriptorVector& flowDescriptor)
{
    handleChange();
    this->flowDescriptor = flowDescriptor;
}

class RsvpResvMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hop,
        FIELD_flowDescriptor,
    };
  public:
    RsvpResvMsgDescriptor();
    virtual ~RsvpResvMsgDescriptor();

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

Register_ClassDescriptor(RsvpResvMsgDescriptor)

RsvpResvMsgDescriptor::RsvpResvMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpResvMsg)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpResvMsgDescriptor::~RsvpResvMsgDescriptor()
{
    delete[] propertyNames;
}

bool RsvpResvMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpResvMsg *>(obj)!=nullptr;
}

const char **RsvpResvMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpResvMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpResvMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RsvpResvMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_hop
        FD_ISCOMPOUND,    // FIELD_flowDescriptor
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RsvpResvMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hop",
        "flowDescriptor",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RsvpResvMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "flowDescriptor") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpResvMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RsvpHopObj",    // FIELD_hop
        "inet::FlowDescriptorVector",    // FIELD_flowDescriptor
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpResvMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpResvMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpResvMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpResvMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpResvMsg'", field);
    }
}

const char *RsvpResvMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpResvMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return "";
        case FIELD_flowDescriptor: return "";
        default: return "";
    }
}

void RsvpResvMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvMsg'", field);
    }
}

omnetpp::cValue RsvpResvMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_flowDescriptor: return omnetpp::toAnyPtr(&pp->getFlowDescriptor()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpResvMsg' as cValue -- field index out of range?", field);
    }
}

void RsvpResvMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvMsg'", field);
    }
}

const char *RsvpResvMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hop: return omnetpp::opp_typename(typeid(RsvpHopObj));
        case FIELD_flowDescriptor: return omnetpp::opp_typename(typeid(FlowDescriptorVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpResvMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_flowDescriptor: return omnetpp::toAnyPtr(&pp->getFlowDescriptor()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpResvMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvMsg *pp = omnetpp::fromAnyPtr<RsvpResvMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvMsg'", field);
    }
}

Register_Class(RsvpResvTear)

RsvpResvTear::RsvpResvTear() : ::inet::RsvpPacket()
{
    this->setRsvpKind(RTEAR_MESSAGE);

}

RsvpResvTear::RsvpResvTear(const RsvpResvTear& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpResvTear::~RsvpResvTear()
{
}

RsvpResvTear& RsvpResvTear::operator=(const RsvpResvTear& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpResvTear::copy(const RsvpResvTear& other)
{
    this->hop = other.hop;
    this->flowDescriptor = other.flowDescriptor;
}

void RsvpResvTear::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->flowDescriptor);
}

void RsvpResvTear::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->flowDescriptor);
}

const RsvpHopObj& RsvpResvTear::getHop() const
{
    return this->hop;
}

void RsvpResvTear::setHop(const RsvpHopObj& hop)
{
    handleChange();
    this->hop = hop;
}

const FlowDescriptorVector& RsvpResvTear::getFlowDescriptor() const
{
    return this->flowDescriptor;
}

void RsvpResvTear::setFlowDescriptor(const FlowDescriptorVector& flowDescriptor)
{
    handleChange();
    this->flowDescriptor = flowDescriptor;
}

class RsvpResvTearDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hop,
        FIELD_flowDescriptor,
    };
  public:
    RsvpResvTearDescriptor();
    virtual ~RsvpResvTearDescriptor();

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

Register_ClassDescriptor(RsvpResvTearDescriptor)

RsvpResvTearDescriptor::RsvpResvTearDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpResvTear)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpResvTearDescriptor::~RsvpResvTearDescriptor()
{
    delete[] propertyNames;
}

bool RsvpResvTearDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpResvTear *>(obj)!=nullptr;
}

const char **RsvpResvTearDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpResvTearDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpResvTearDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RsvpResvTearDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_hop
        FD_ISCOMPOUND,    // FIELD_flowDescriptor
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RsvpResvTearDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hop",
        "flowDescriptor",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RsvpResvTearDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "flowDescriptor") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpResvTearDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RsvpHopObj",    // FIELD_hop
        "inet::FlowDescriptorVector",    // FIELD_flowDescriptor
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpResvTearDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpResvTearDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpResvTearDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpResvTearDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpResvTear'", field);
    }
}

const char *RsvpResvTearDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpResvTearDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return "";
        case FIELD_flowDescriptor: return "";
        default: return "";
    }
}

void RsvpResvTearDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvTear'", field);
    }
}

omnetpp::cValue RsvpResvTearDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_flowDescriptor: return omnetpp::toAnyPtr(&pp->getFlowDescriptor()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpResvTear' as cValue -- field index out of range?", field);
    }
}

void RsvpResvTearDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvTear'", field);
    }
}

const char *RsvpResvTearDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hop: return omnetpp::opp_typename(typeid(RsvpHopObj));
        case FIELD_flowDescriptor: return omnetpp::opp_typename(typeid(FlowDescriptorVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpResvTearDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_flowDescriptor: return omnetpp::toAnyPtr(&pp->getFlowDescriptor()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpResvTearDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvTear *pp = omnetpp::fromAnyPtr<RsvpResvTear>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvTear'", field);
    }
}

Register_Class(RsvpResvError)

RsvpResvError::RsvpResvError() : ::inet::RsvpPacket()
{
    this->setRsvpKind(RERROR_MESSAGE);

}

RsvpResvError::RsvpResvError(const RsvpResvError& other) : ::inet::RsvpPacket(other)
{
    copy(other);
}

RsvpResvError::~RsvpResvError()
{
}

RsvpResvError& RsvpResvError::operator=(const RsvpResvError& other)
{
    if (this == &other) return *this;
    ::inet::RsvpPacket::operator=(other);
    copy(other);
    return *this;
}

void RsvpResvError::copy(const RsvpResvError& other)
{
    this->hop = other.hop;
    this->errorNode = other.errorNode;
    this->errorCode = other.errorCode;
}

void RsvpResvError::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::RsvpPacket::parsimPack(b);
    doParsimPacking(b,this->hop);
    doParsimPacking(b,this->errorNode);
    doParsimPacking(b,this->errorCode);
}

void RsvpResvError::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::RsvpPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hop);
    doParsimUnpacking(b,this->errorNode);
    doParsimUnpacking(b,this->errorCode);
}

const RsvpHopObj& RsvpResvError::getHop() const
{
    return this->hop;
}

void RsvpResvError::setHop(const RsvpHopObj& hop)
{
    handleChange();
    this->hop = hop;
}

const Ipv4Address& RsvpResvError::getErrorNode() const
{
    return this->errorNode;
}

void RsvpResvError::setErrorNode(const Ipv4Address& errorNode)
{
    handleChange();
    this->errorNode = errorNode;
}

int RsvpResvError::getErrorCode() const
{
    return this->errorCode;
}

void RsvpResvError::setErrorCode(int errorCode)
{
    handleChange();
    this->errorCode = errorCode;
}

class RsvpResvErrorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hop,
        FIELD_errorNode,
        FIELD_errorCode,
    };
  public:
    RsvpResvErrorDescriptor();
    virtual ~RsvpResvErrorDescriptor();

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

Register_ClassDescriptor(RsvpResvErrorDescriptor)

RsvpResvErrorDescriptor::RsvpResvErrorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpResvError)), "inet::RsvpPacket")
{
    propertyNames = nullptr;
}

RsvpResvErrorDescriptor::~RsvpResvErrorDescriptor()
{
    delete[] propertyNames;
}

bool RsvpResvErrorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpResvError *>(obj)!=nullptr;
}

const char **RsvpResvErrorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpResvErrorDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpResvErrorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RsvpResvErrorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_hop
        0,    // FIELD_errorNode
        FD_ISEDITABLE,    // FIELD_errorCode
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RsvpResvErrorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hop",
        "errorNode",
        "errorCode",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RsvpResvErrorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "errorNode") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "errorCode") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpResvErrorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::RsvpHopObj",    // FIELD_hop
        "inet::Ipv4Address",    // FIELD_errorNode
        "int",    // FIELD_errorCode
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpResvErrorDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpResvErrorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpResvErrorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpResvErrorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpResvError'", field);
    }
}

const char *RsvpResvErrorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpResvErrorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return "";
        case FIELD_errorNode: return pp->getErrorNode().str();
        case FIELD_errorCode: return long2string(pp->getErrorCode());
        default: return "";
    }
}

void RsvpResvErrorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: pp->setErrorCode(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvError'", field);
    }
}

omnetpp::cValue RsvpResvErrorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_errorNode: return omnetpp::toAnyPtr(&pp->getErrorNode()); break;
        case FIELD_errorCode: return pp->getErrorCode();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpResvError' as cValue -- field index out of range?", field);
    }
}

void RsvpResvErrorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        case FIELD_errorCode: pp->setErrorCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvError'", field);
    }
}

const char *RsvpResvErrorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_hop: return omnetpp::opp_typename(typeid(RsvpHopObj));
        default: return nullptr;
    };
}

omnetpp::any_ptr RsvpResvErrorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        case FIELD_hop: return omnetpp::toAnyPtr(&pp->getHop()); break;
        case FIELD_errorNode: return omnetpp::toAnyPtr(&pp->getErrorNode()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpResvErrorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpResvError *pp = omnetpp::fromAnyPtr<RsvpResvError>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpResvError'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

