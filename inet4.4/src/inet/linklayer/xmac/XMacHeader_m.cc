//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/xmac/XMacHeader.msg.
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
#include "XMacHeader_m.h"

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

Register_Enum(inet::XMacTypes, (inet::XMacTypes::XMAC_PREAMBLE, inet::XMacTypes::XMAC_DATA, inet::XMacTypes::XMAC_ACK, inet::XMacTypes::XMAC_RESEND_DATA, inet::XMacTypes::XMAC_ACK_TIMEOUT, inet::XMacTypes::XMAC_START_XMAC, inet::XMacTypes::XMAC_WAKE_UP, inet::XMacTypes::XMAC_SEND_ACK, inet::XMacTypes::XMAC_CCA_TIMEOUT, inet::XMacTypes::XMAC_ACK_TX_OVER, inet::XMacTypes::XMAC_SEND_PREAMBLE, inet::XMacTypes::XMAC_STOP_PREAMBLES, inet::XMacTypes::XMAC_DATA_TX_OVER, inet::XMacTypes::XMAC_DATA_TIMEOUT, inet::XMacTypes::SWITCH_PREAMBLE_PHASE, inet::XMacTypes::DELAY_FOR_ACK_WITHIN_REMOTE_RX, inet::XMacTypes::XMAC_SWITCHING_FINISHED));

Register_Class(XMacHeaderBase)

XMacHeaderBase::XMacHeaderBase() : ::inet::FieldsChunk()
{
}

XMacHeaderBase::XMacHeaderBase(const XMacHeaderBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

XMacHeaderBase::~XMacHeaderBase()
{
}

XMacHeaderBase& XMacHeaderBase::operator=(const XMacHeaderBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void XMacHeaderBase::copy(const XMacHeaderBase& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->type = other.type;
}

void XMacHeaderBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->type);
}

void XMacHeaderBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->type);
}

const MacAddress& XMacHeaderBase::getSrcAddr() const
{
    return this->srcAddr;
}

void XMacHeaderBase::setSrcAddr(const MacAddress& srcAddr)
{
    handleChange();
    this->srcAddr = srcAddr;
}

const MacAddress& XMacHeaderBase::getDestAddr() const
{
    return this->destAddr;
}

void XMacHeaderBase::setDestAddr(const MacAddress& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

XMacTypes XMacHeaderBase::getType() const
{
    return this->type;
}

void XMacHeaderBase::setType(XMacTypes type)
{
    handleChange();
    this->type = type;
}

class XMacHeaderBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_type,
    };
  public:
    XMacHeaderBaseDescriptor();
    virtual ~XMacHeaderBaseDescriptor();

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

Register_ClassDescriptor(XMacHeaderBaseDescriptor)

XMacHeaderBaseDescriptor::XMacHeaderBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::XMacHeaderBase)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

XMacHeaderBaseDescriptor::~XMacHeaderBaseDescriptor()
{
    delete[] propertyNames;
}

bool XMacHeaderBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<XMacHeaderBase *>(obj)!=nullptr;
}

const char **XMacHeaderBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *XMacHeaderBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int XMacHeaderBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int XMacHeaderBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddr
        0,    // FIELD_destAddr
        0,    // FIELD_type
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *XMacHeaderBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "type",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int XMacHeaderBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *XMacHeaderBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_srcAddr
        "inet::MacAddress",    // FIELD_destAddr
        "inet::XMacTypes",    // FIELD_type
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **XMacHeaderBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *XMacHeaderBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::XMacTypes";
            return nullptr;
        default: return nullptr;
    }
}

int XMacHeaderBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void XMacHeaderBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'XMacHeaderBase'", field);
    }
}

const char *XMacHeaderBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string XMacHeaderBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr().str();
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_type: return enum2string(pp->getType(), "inet::XMacTypes");
        default: return "";
    }
}

void XMacHeaderBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacHeaderBase'", field);
    }
}

omnetpp::cValue XMacHeaderBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        case FIELD_type: return static_cast<int>(pp->getType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'XMacHeaderBase' as cValue -- field index out of range?", field);
    }
}

void XMacHeaderBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacHeaderBase'", field);
    }
}

const char *XMacHeaderBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr XMacHeaderBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return omnetpp::toAnyPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return omnetpp::toAnyPtr(&pp->getDestAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void XMacHeaderBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacHeaderBase *pp = omnetpp::fromAnyPtr<XMacHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacHeaderBase'", field);
    }
}

Register_Class(XMacControlFrame)

XMacControlFrame::XMacControlFrame() : ::inet::XMacHeaderBase()
{
}

XMacControlFrame::XMacControlFrame(const XMacControlFrame& other) : ::inet::XMacHeaderBase(other)
{
    copy(other);
}

XMacControlFrame::~XMacControlFrame()
{
}

XMacControlFrame& XMacControlFrame::operator=(const XMacControlFrame& other)
{
    if (this == &other) return *this;
    ::inet::XMacHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void XMacControlFrame::copy(const XMacControlFrame& other)
{
}

void XMacControlFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::XMacHeaderBase::parsimPack(b);
}

void XMacControlFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::XMacHeaderBase::parsimUnpack(b);
}

class XMacControlFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    XMacControlFrameDescriptor();
    virtual ~XMacControlFrameDescriptor();

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

Register_ClassDescriptor(XMacControlFrameDescriptor)

XMacControlFrameDescriptor::XMacControlFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::XMacControlFrame)), "inet::XMacHeaderBase")
{
    propertyNames = nullptr;
}

XMacControlFrameDescriptor::~XMacControlFrameDescriptor()
{
    delete[] propertyNames;
}

bool XMacControlFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<XMacControlFrame *>(obj)!=nullptr;
}

const char **XMacControlFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *XMacControlFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int XMacControlFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int XMacControlFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *XMacControlFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int XMacControlFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *XMacControlFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **XMacControlFrameDescriptor::getFieldPropertyNames(int field) const
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

const char *XMacControlFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int XMacControlFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void XMacControlFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'XMacControlFrame'", field);
    }
}

const char *XMacControlFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string XMacControlFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void XMacControlFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacControlFrame'", field);
    }
}

omnetpp::cValue XMacControlFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'XMacControlFrame' as cValue -- field index out of range?", field);
    }
}

void XMacControlFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacControlFrame'", field);
    }
}

const char *XMacControlFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr XMacControlFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void XMacControlFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacControlFrame *pp = omnetpp::fromAnyPtr<XMacControlFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacControlFrame'", field);
    }
}

Register_Class(XMacDataFrameHeader)

XMacDataFrameHeader::XMacDataFrameHeader() : ::inet::XMacHeaderBase()
{
}

XMacDataFrameHeader::XMacDataFrameHeader(const XMacDataFrameHeader& other) : ::inet::XMacHeaderBase(other)
{
    copy(other);
}

XMacDataFrameHeader::~XMacDataFrameHeader()
{
}

XMacDataFrameHeader& XMacDataFrameHeader::operator=(const XMacDataFrameHeader& other)
{
    if (this == &other) return *this;
    ::inet::XMacHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void XMacDataFrameHeader::copy(const XMacDataFrameHeader& other)
{
    this->sequenceId = other.sequenceId;
    this->networkProtocol = other.networkProtocol;
}

void XMacDataFrameHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::XMacHeaderBase::parsimPack(b);
    doParsimPacking(b,this->sequenceId);
    doParsimPacking(b,this->networkProtocol);
}

void XMacDataFrameHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::XMacHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceId);
    doParsimUnpacking(b,this->networkProtocol);
}

long XMacDataFrameHeader::getSequenceId() const
{
    return this->sequenceId;
}

void XMacDataFrameHeader::setSequenceId(long sequenceId)
{
    handleChange();
    this->sequenceId = sequenceId;
}

int XMacDataFrameHeader::getNetworkProtocol() const
{
    return this->networkProtocol;
}

void XMacDataFrameHeader::setNetworkProtocol(int networkProtocol)
{
    handleChange();
    this->networkProtocol = networkProtocol;
}

class XMacDataFrameHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sequenceId,
        FIELD_networkProtocol,
    };
  public:
    XMacDataFrameHeaderDescriptor();
    virtual ~XMacDataFrameHeaderDescriptor();

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

Register_ClassDescriptor(XMacDataFrameHeaderDescriptor)

XMacDataFrameHeaderDescriptor::XMacDataFrameHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::XMacDataFrameHeader)), "inet::XMacHeaderBase")
{
    propertyNames = nullptr;
}

XMacDataFrameHeaderDescriptor::~XMacDataFrameHeaderDescriptor()
{
    delete[] propertyNames;
}

bool XMacDataFrameHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<XMacDataFrameHeader *>(obj)!=nullptr;
}

const char **XMacDataFrameHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *XMacDataFrameHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int XMacDataFrameHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int XMacDataFrameHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceId
        FD_ISEDITABLE,    // FIELD_networkProtocol
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *XMacDataFrameHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceId",
        "networkProtocol",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int XMacDataFrameHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sequenceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "networkProtocol") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *XMacDataFrameHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "long",    // FIELD_sequenceId
        "int",    // FIELD_networkProtocol
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **XMacDataFrameHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *XMacDataFrameHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int XMacDataFrameHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void XMacDataFrameHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'XMacDataFrameHeader'", field);
    }
}

const char *XMacDataFrameHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string XMacDataFrameHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceId: return long2string(pp->getSequenceId());
        case FIELD_networkProtocol: return long2string(pp->getNetworkProtocol());
        default: return "";
    }
}

void XMacDataFrameHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceId: pp->setSequenceId(string2long(value)); break;
        case FIELD_networkProtocol: pp->setNetworkProtocol(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacDataFrameHeader'", field);
    }
}

omnetpp::cValue XMacDataFrameHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceId: return (omnetpp::intval_t)(pp->getSequenceId());
        case FIELD_networkProtocol: return pp->getNetworkProtocol();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'XMacDataFrameHeader' as cValue -- field index out of range?", field);
    }
}

void XMacDataFrameHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceId: pp->setSequenceId(omnetpp::checked_int_cast<long>(value.intValue())); break;
        case FIELD_networkProtocol: pp->setNetworkProtocol(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacDataFrameHeader'", field);
    }
}

const char *XMacDataFrameHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr XMacDataFrameHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void XMacDataFrameHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    XMacDataFrameHeader *pp = omnetpp::fromAnyPtr<XMacDataFrameHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'XMacDataFrameHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

