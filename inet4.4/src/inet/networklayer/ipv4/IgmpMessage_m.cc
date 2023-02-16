//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/IgmpMessage.msg.
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
#include "IgmpMessage_m.h"

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

Register_Enum(inet::IgmpType, (inet::IgmpType::IGMP_MEMBERSHIP_QUERY, inet::IgmpType::IGMPV1_MEMBERSHIP_REPORT, inet::IgmpType::IGMPV2_MEMBERSHIP_REPORT, inet::IgmpType::IGMPV2_LEAVE_GROUP, inet::IgmpType::IGMPV3_MEMBERSHIP_REPORT));

Register_Class(IgmpMessage)

IgmpMessage::IgmpMessage() : ::inet::FieldsChunk()
{
}

IgmpMessage::IgmpMessage(const IgmpMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

IgmpMessage::~IgmpMessage()
{
}

IgmpMessage& IgmpMessage::operator=(const IgmpMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void IgmpMessage::copy(const IgmpMessage& other)
{
    this->type = other.type;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void IgmpMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void IgmpMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

IgmpType IgmpMessage::getType() const
{
    return this->type;
}

void IgmpMessage::setType(IgmpType type)
{
    handleChange();
    this->type = type;
}

uint16_t IgmpMessage::getCrc() const
{
    return this->crc;
}

void IgmpMessage::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

CrcMode IgmpMessage::getCrcMode() const
{
    return this->crcMode;
}

void IgmpMessage::setCrcMode(CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class IgmpMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    IgmpMessageDescriptor();
    virtual ~IgmpMessageDescriptor();

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

Register_ClassDescriptor(IgmpMessageDescriptor)

IgmpMessageDescriptor::IgmpMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IgmpMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

IgmpMessageDescriptor::~IgmpMessageDescriptor()
{
    delete[] propertyNames;
}

bool IgmpMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IgmpMessage *>(obj)!=nullptr;
}

const char **IgmpMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IgmpMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IgmpMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int IgmpMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *IgmpMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int IgmpMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *IgmpMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::IgmpType",    // FIELD_type
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **IgmpMessageDescriptor::getFieldPropertyNames(int field) const
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
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *IgmpMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::IgmpType";
            return nullptr;
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int IgmpMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IgmpMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IgmpMessage'", field);
    }
}

const char *IgmpMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IgmpMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::IgmpType");
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void IgmpMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpMessage'", field);
    }
}

omnetpp::cValue IgmpMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IgmpMessage' as cValue -- field index out of range?", field);
    }
}

void IgmpMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpMessage'", field);
    }
}

const char *IgmpMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IgmpMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IgmpMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpMessage *pp = omnetpp::fromAnyPtr<IgmpMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpMessage'", field);
    }
}

Register_Class(IgmpQuery)

IgmpQuery::IgmpQuery() : ::inet::IgmpMessage()
{
    this->setType(IGMP_MEMBERSHIP_QUERY);

}

IgmpQuery::IgmpQuery(const IgmpQuery& other) : ::inet::IgmpMessage(other)
{
    copy(other);
}

IgmpQuery::~IgmpQuery()
{
}

IgmpQuery& IgmpQuery::operator=(const IgmpQuery& other)
{
    if (this == &other) return *this;
    ::inet::IgmpMessage::operator=(other);
    copy(other);
    return *this;
}

void IgmpQuery::copy(const IgmpQuery& other)
{
    this->groupAddress = other.groupAddress;
}

void IgmpQuery::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpMessage::parsimPack(b);
    doParsimPacking(b,this->groupAddress);
}

void IgmpQuery::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->groupAddress);
}

const Ipv4Address& IgmpQuery::getGroupAddress() const
{
    return this->groupAddress;
}

void IgmpQuery::setGroupAddress(const Ipv4Address& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

class IgmpQueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_groupAddress,
    };
  public:
    IgmpQueryDescriptor();
    virtual ~IgmpQueryDescriptor();

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

Register_ClassDescriptor(IgmpQueryDescriptor)

IgmpQueryDescriptor::IgmpQueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::IgmpQuery)), "inet::IgmpMessage")
{
    propertyNames = nullptr;
}

IgmpQueryDescriptor::~IgmpQueryDescriptor()
{
    delete[] propertyNames;
}

bool IgmpQueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<IgmpQuery *>(obj)!=nullptr;
}

const char **IgmpQueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *IgmpQueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int IgmpQueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int IgmpQueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_groupAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *IgmpQueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "groupAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int IgmpQueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *IgmpQueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_groupAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **IgmpQueryDescriptor::getFieldPropertyNames(int field) const
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

const char *IgmpQueryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int IgmpQueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void IgmpQueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'IgmpQuery'", field);
    }
}

const char *IgmpQueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string IgmpQueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return pp->getGroupAddress().str();
        default: return "";
    }
}

void IgmpQueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpQuery'", field);
    }
}

omnetpp::cValue IgmpQueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'IgmpQuery' as cValue -- field index out of range?", field);
    }
}

void IgmpQueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpQuery'", field);
    }
}

const char *IgmpQueryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr IgmpQueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void IgmpQueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    IgmpQuery *pp = omnetpp::fromAnyPtr<IgmpQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'IgmpQuery'", field);
    }
}

Register_Class(Igmpv1Query)

Igmpv1Query::Igmpv1Query() : ::inet::IgmpQuery()
{
    this->setChunkLength(B(8));

}

Igmpv1Query::Igmpv1Query(const Igmpv1Query& other) : ::inet::IgmpQuery(other)
{
    copy(other);
}

Igmpv1Query::~Igmpv1Query()
{
}

Igmpv1Query& Igmpv1Query::operator=(const Igmpv1Query& other)
{
    if (this == &other) return *this;
    ::inet::IgmpQuery::operator=(other);
    copy(other);
    return *this;
}

void Igmpv1Query::copy(const Igmpv1Query& other)
{
    this->unused = other.unused;
}

void Igmpv1Query::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpQuery::parsimPack(b);
    doParsimPacking(b,this->unused);
}

void Igmpv1Query::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpQuery::parsimUnpack(b);
    doParsimUnpacking(b,this->unused);
}

uint8_t Igmpv1Query::getUnused() const
{
    return this->unused;
}

void Igmpv1Query::setUnused(uint8_t unused)
{
    handleChange();
    this->unused = unused;
}

class Igmpv1QueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unused,
    };
  public:
    Igmpv1QueryDescriptor();
    virtual ~Igmpv1QueryDescriptor();

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

Register_ClassDescriptor(Igmpv1QueryDescriptor)

Igmpv1QueryDescriptor::Igmpv1QueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv1Query)), "inet::IgmpQuery")
{
    propertyNames = nullptr;
}

Igmpv1QueryDescriptor::~Igmpv1QueryDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv1QueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv1Query *>(obj)!=nullptr;
}

const char **Igmpv1QueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv1QueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv1QueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Igmpv1QueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_unused
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv1QueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unused",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Igmpv1QueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unused") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv1QueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_unused
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv1QueryDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv1QueryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv1QueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv1QueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv1Query'", field);
    }
}

const char *Igmpv1QueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv1QueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return ulong2string(pp->getUnused());
        default: return "";
    }
}

void Igmpv1QueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Query'", field);
    }
}

omnetpp::cValue Igmpv1QueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return (omnetpp::intval_t)(pp->getUnused());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv1Query' as cValue -- field index out of range?", field);
    }
}

void Igmpv1QueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Query'", field);
    }
}

const char *Igmpv1QueryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Igmpv1QueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv1QueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Query *pp = omnetpp::fromAnyPtr<Igmpv1Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Query'", field);
    }
}

Register_Class(Igmpv1Report)

Igmpv1Report::Igmpv1Report() : ::inet::IgmpMessage()
{
    this->setChunkLength(B(8));
    this->setType(IGMPV1_MEMBERSHIP_REPORT);

}

Igmpv1Report::Igmpv1Report(const Igmpv1Report& other) : ::inet::IgmpMessage(other)
{
    copy(other);
}

Igmpv1Report::~Igmpv1Report()
{
}

Igmpv1Report& Igmpv1Report::operator=(const Igmpv1Report& other)
{
    if (this == &other) return *this;
    ::inet::IgmpMessage::operator=(other);
    copy(other);
    return *this;
}

void Igmpv1Report::copy(const Igmpv1Report& other)
{
    this->unused = other.unused;
    this->groupAddress = other.groupAddress;
}

void Igmpv1Report::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpMessage::parsimPack(b);
    doParsimPacking(b,this->unused);
    doParsimPacking(b,this->groupAddress);
}

void Igmpv1Report::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->unused);
    doParsimUnpacking(b,this->groupAddress);
}

uint8_t Igmpv1Report::getUnused() const
{
    return this->unused;
}

void Igmpv1Report::setUnused(uint8_t unused)
{
    handleChange();
    this->unused = unused;
}

const Ipv4Address& Igmpv1Report::getGroupAddress() const
{
    return this->groupAddress;
}

void Igmpv1Report::setGroupAddress(const Ipv4Address& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

class Igmpv1ReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_unused,
        FIELD_groupAddress,
    };
  public:
    Igmpv1ReportDescriptor();
    virtual ~Igmpv1ReportDescriptor();

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

Register_ClassDescriptor(Igmpv1ReportDescriptor)

Igmpv1ReportDescriptor::Igmpv1ReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv1Report)), "inet::IgmpMessage")
{
    propertyNames = nullptr;
}

Igmpv1ReportDescriptor::~Igmpv1ReportDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv1ReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv1Report *>(obj)!=nullptr;
}

const char **Igmpv1ReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv1ReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv1ReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Igmpv1ReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_unused
        0,    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv1ReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "unused",
        "groupAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Igmpv1ReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "unused") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv1ReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_unused
        "inet::Ipv4Address",    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv1ReportDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv1ReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv1ReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv1ReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv1Report'", field);
    }
}

const char *Igmpv1ReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv1ReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return ulong2string(pp->getUnused());
        case FIELD_groupAddress: return pp->getGroupAddress().str();
        default: return "";
    }
}

void Igmpv1ReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Report'", field);
    }
}

omnetpp::cValue Igmpv1ReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        case FIELD_unused: return (omnetpp::intval_t)(pp->getUnused());
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv1Report' as cValue -- field index out of range?", field);
    }
}

void Igmpv1ReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        case FIELD_unused: pp->setUnused(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Report'", field);
    }
}

const char *Igmpv1ReportDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Igmpv1ReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv1ReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv1Report *pp = omnetpp::fromAnyPtr<Igmpv1Report>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv1Report'", field);
    }
}

Register_Class(Igmpv2Query)

Igmpv2Query::Igmpv2Query() : ::inet::IgmpQuery()
{
    this->setChunkLength(B(8));

}

Igmpv2Query::Igmpv2Query(const Igmpv2Query& other) : ::inet::IgmpQuery(other)
{
    copy(other);
}

Igmpv2Query::~Igmpv2Query()
{
}

Igmpv2Query& Igmpv2Query::operator=(const Igmpv2Query& other)
{
    if (this == &other) return *this;
    ::inet::IgmpQuery::operator=(other);
    copy(other);
    return *this;
}

void Igmpv2Query::copy(const Igmpv2Query& other)
{
    this->maxRespTimeCode = other.maxRespTimeCode;
}

void Igmpv2Query::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpQuery::parsimPack(b);
    doParsimPacking(b,this->maxRespTimeCode);
}

void Igmpv2Query::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpQuery::parsimUnpack(b);
    doParsimUnpacking(b,this->maxRespTimeCode);
}

uint8_t Igmpv2Query::getMaxRespTimeCode() const
{
    return this->maxRespTimeCode;
}

void Igmpv2Query::setMaxRespTimeCode(uint8_t maxRespTimeCode)
{
    handleChange();
    this->maxRespTimeCode = maxRespTimeCode;
}

class Igmpv2QueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_maxRespTimeCode,
    };
  public:
    Igmpv2QueryDescriptor();
    virtual ~Igmpv2QueryDescriptor();

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

Register_ClassDescriptor(Igmpv2QueryDescriptor)

Igmpv2QueryDescriptor::Igmpv2QueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv2Query)), "inet::IgmpQuery")
{
    propertyNames = nullptr;
}

Igmpv2QueryDescriptor::~Igmpv2QueryDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv2QueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv2Query *>(obj)!=nullptr;
}

const char **Igmpv2QueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv2QueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv2QueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Igmpv2QueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_maxRespTimeCode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv2QueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "maxRespTimeCode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Igmpv2QueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "maxRespTimeCode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv2QueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_maxRespTimeCode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv2QueryDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv2QueryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv2QueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv2QueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv2Query'", field);
    }
}

const char *Igmpv2QueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv2QueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTimeCode: return ulong2string(pp->getMaxRespTimeCode());
        default: return "";
    }
}

void Igmpv2QueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTimeCode: pp->setMaxRespTimeCode(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Query'", field);
    }
}

omnetpp::cValue Igmpv2QueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTimeCode: return (omnetpp::intval_t)(pp->getMaxRespTimeCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv2Query' as cValue -- field index out of range?", field);
    }
}

void Igmpv2QueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTimeCode: pp->setMaxRespTimeCode(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Query'", field);
    }
}

const char *Igmpv2QueryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Igmpv2QueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv2QueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Query *pp = omnetpp::fromAnyPtr<Igmpv2Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Query'", field);
    }
}

Register_Class(Igmpv2Report)

Igmpv2Report::Igmpv2Report() : ::inet::IgmpMessage()
{
    this->setChunkLength(B(8));
    this->setType(IGMPV2_MEMBERSHIP_REPORT);

}

Igmpv2Report::Igmpv2Report(const Igmpv2Report& other) : ::inet::IgmpMessage(other)
{
    copy(other);
}

Igmpv2Report::~Igmpv2Report()
{
}

Igmpv2Report& Igmpv2Report::operator=(const Igmpv2Report& other)
{
    if (this == &other) return *this;
    ::inet::IgmpMessage::operator=(other);
    copy(other);
    return *this;
}

void Igmpv2Report::copy(const Igmpv2Report& other)
{
    this->maxRespTime = other.maxRespTime;
    this->groupAddress = other.groupAddress;
}

void Igmpv2Report::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpMessage::parsimPack(b);
    doParsimPacking(b,this->maxRespTime);
    doParsimPacking(b,this->groupAddress);
}

void Igmpv2Report::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->maxRespTime);
    doParsimUnpacking(b,this->groupAddress);
}

uint8_t Igmpv2Report::getMaxRespTime() const
{
    return this->maxRespTime;
}

void Igmpv2Report::setMaxRespTime(uint8_t maxRespTime)
{
    handleChange();
    this->maxRespTime = maxRespTime;
}

const Ipv4Address& Igmpv2Report::getGroupAddress() const
{
    return this->groupAddress;
}

void Igmpv2Report::setGroupAddress(const Ipv4Address& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

class Igmpv2ReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_maxRespTime,
        FIELD_groupAddress,
    };
  public:
    Igmpv2ReportDescriptor();
    virtual ~Igmpv2ReportDescriptor();

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

Register_ClassDescriptor(Igmpv2ReportDescriptor)

Igmpv2ReportDescriptor::Igmpv2ReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv2Report)), "inet::IgmpMessage")
{
    propertyNames = nullptr;
}

Igmpv2ReportDescriptor::~Igmpv2ReportDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv2ReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv2Report *>(obj)!=nullptr;
}

const char **Igmpv2ReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv2ReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv2ReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Igmpv2ReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_maxRespTime
        0,    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv2ReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "maxRespTime",
        "groupAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Igmpv2ReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "maxRespTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv2ReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_maxRespTime
        "inet::Ipv4Address",    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv2ReportDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv2ReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv2ReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv2ReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv2Report'", field);
    }
}

const char *Igmpv2ReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv2ReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: return ulong2string(pp->getMaxRespTime());
        case FIELD_groupAddress: return pp->getGroupAddress().str();
        default: return "";
    }
}

void Igmpv2ReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: pp->setMaxRespTime(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Report'", field);
    }
}

omnetpp::cValue Igmpv2ReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: return (omnetpp::intval_t)(pp->getMaxRespTime());
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv2Report' as cValue -- field index out of range?", field);
    }
}

void Igmpv2ReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: pp->setMaxRespTime(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Report'", field);
    }
}

const char *Igmpv2ReportDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Igmpv2ReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv2ReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Report *pp = omnetpp::fromAnyPtr<Igmpv2Report>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Report'", field);
    }
}

Register_Class(Igmpv2Leave)

Igmpv2Leave::Igmpv2Leave() : ::inet::IgmpMessage()
{
    this->setChunkLength(B(8));
    this->setType(IGMPV2_LEAVE_GROUP);

}

Igmpv2Leave::Igmpv2Leave(const Igmpv2Leave& other) : ::inet::IgmpMessage(other)
{
    copy(other);
}

Igmpv2Leave::~Igmpv2Leave()
{
}

Igmpv2Leave& Igmpv2Leave::operator=(const Igmpv2Leave& other)
{
    if (this == &other) return *this;
    ::inet::IgmpMessage::operator=(other);
    copy(other);
    return *this;
}

void Igmpv2Leave::copy(const Igmpv2Leave& other)
{
    this->maxRespTime = other.maxRespTime;
    this->groupAddress = other.groupAddress;
}

void Igmpv2Leave::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpMessage::parsimPack(b);
    doParsimPacking(b,this->maxRespTime);
    doParsimPacking(b,this->groupAddress);
}

void Igmpv2Leave::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->maxRespTime);
    doParsimUnpacking(b,this->groupAddress);
}

uint8_t Igmpv2Leave::getMaxRespTime() const
{
    return this->maxRespTime;
}

void Igmpv2Leave::setMaxRespTime(uint8_t maxRespTime)
{
    handleChange();
    this->maxRespTime = maxRespTime;
}

const Ipv4Address& Igmpv2Leave::getGroupAddress() const
{
    return this->groupAddress;
}

void Igmpv2Leave::setGroupAddress(const Ipv4Address& groupAddress)
{
    handleChange();
    this->groupAddress = groupAddress;
}

class Igmpv2LeaveDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_maxRespTime,
        FIELD_groupAddress,
    };
  public:
    Igmpv2LeaveDescriptor();
    virtual ~Igmpv2LeaveDescriptor();

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

Register_ClassDescriptor(Igmpv2LeaveDescriptor)

Igmpv2LeaveDescriptor::Igmpv2LeaveDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv2Leave)), "inet::IgmpMessage")
{
    propertyNames = nullptr;
}

Igmpv2LeaveDescriptor::~Igmpv2LeaveDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv2LeaveDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv2Leave *>(obj)!=nullptr;
}

const char **Igmpv2LeaveDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv2LeaveDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv2LeaveDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Igmpv2LeaveDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_maxRespTime
        0,    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv2LeaveDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "maxRespTime",
        "groupAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Igmpv2LeaveDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "maxRespTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv2LeaveDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_maxRespTime
        "inet::Ipv4Address",    // FIELD_groupAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv2LeaveDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv2LeaveDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv2LeaveDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv2LeaveDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv2Leave'", field);
    }
}

const char *Igmpv2LeaveDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv2LeaveDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: return ulong2string(pp->getMaxRespTime());
        case FIELD_groupAddress: return pp->getGroupAddress().str();
        default: return "";
    }
}

void Igmpv2LeaveDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: pp->setMaxRespTime(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Leave'", field);
    }
}

omnetpp::cValue Igmpv2LeaveDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: return (omnetpp::intval_t)(pp->getMaxRespTime());
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv2Leave' as cValue -- field index out of range?", field);
    }
}

void Igmpv2LeaveDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        case FIELD_maxRespTime: pp->setMaxRespTime(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Leave'", field);
    }
}

const char *Igmpv2LeaveDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Igmpv2LeaveDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv2LeaveDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv2Leave *pp = omnetpp::fromAnyPtr<Igmpv2Leave>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv2Leave'", field);
    }
}

Register_Class(Igmpv3Query)

Igmpv3Query::Igmpv3Query() : ::inet::Igmpv2Query()
{
    this->setChunkLength(B(12));

}

Igmpv3Query::Igmpv3Query(const Igmpv3Query& other) : ::inet::Igmpv2Query(other)
{
    copy(other);
}

Igmpv3Query::~Igmpv3Query()
{
}

Igmpv3Query& Igmpv3Query::operator=(const Igmpv3Query& other)
{
    if (this == &other) return *this;
    ::inet::Igmpv2Query::operator=(other);
    copy(other);
    return *this;
}

void Igmpv3Query::copy(const Igmpv3Query& other)
{
    this->resv = other.resv;
    this->suppressRouterProc = other.suppressRouterProc;
    this->robustnessVariable = other.robustnessVariable;
    this->queryIntervalCode = other.queryIntervalCode;
    this->sourceList = other.sourceList;
}

void Igmpv3Query::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Igmpv2Query::parsimPack(b);
    doParsimPacking(b,this->resv);
    doParsimPacking(b,this->suppressRouterProc);
    doParsimPacking(b,this->robustnessVariable);
    doParsimPacking(b,this->queryIntervalCode);
    doParsimPacking(b,this->sourceList);
}

void Igmpv3Query::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Igmpv2Query::parsimUnpack(b);
    doParsimUnpacking(b,this->resv);
    doParsimUnpacking(b,this->suppressRouterProc);
    doParsimUnpacking(b,this->robustnessVariable);
    doParsimUnpacking(b,this->queryIntervalCode);
    doParsimUnpacking(b,this->sourceList);
}

uint8_t Igmpv3Query::getResv() const
{
    return this->resv;
}

void Igmpv3Query::setResv(uint8_t resv)
{
    handleChange();
    this->resv = resv;
}

bool Igmpv3Query::getSuppressRouterProc() const
{
    return this->suppressRouterProc;
}

void Igmpv3Query::setSuppressRouterProc(bool suppressRouterProc)
{
    handleChange();
    this->suppressRouterProc = suppressRouterProc;
}

uint8_t Igmpv3Query::getRobustnessVariable() const
{
    return this->robustnessVariable;
}

void Igmpv3Query::setRobustnessVariable(uint8_t robustnessVariable)
{
    handleChange();
    this->robustnessVariable = robustnessVariable;
}

uint8_t Igmpv3Query::getQueryIntervalCode() const
{
    return this->queryIntervalCode;
}

void Igmpv3Query::setQueryIntervalCode(uint8_t queryIntervalCode)
{
    handleChange();
    this->queryIntervalCode = queryIntervalCode;
}

const Ipv4AddressVector& Igmpv3Query::getSourceList() const
{
    return this->sourceList;
}

void Igmpv3Query::setSourceList(const Ipv4AddressVector& sourceList)
{
    handleChange();
    this->sourceList = sourceList;
}

class Igmpv3QueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_resv,
        FIELD_suppressRouterProc,
        FIELD_robustnessVariable,
        FIELD_queryIntervalCode,
        FIELD_sourceList,
    };
  public:
    Igmpv3QueryDescriptor();
    virtual ~Igmpv3QueryDescriptor();

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

Register_ClassDescriptor(Igmpv3QueryDescriptor)

Igmpv3QueryDescriptor::Igmpv3QueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv3Query)), "inet::Igmpv2Query")
{
    propertyNames = nullptr;
}

Igmpv3QueryDescriptor::~Igmpv3QueryDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv3QueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv3Query *>(obj)!=nullptr;
}

const char **Igmpv3QueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv3QueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv3QueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Igmpv3QueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_resv
        FD_ISEDITABLE,    // FIELD_suppressRouterProc
        FD_ISEDITABLE,    // FIELD_robustnessVariable
        FD_ISEDITABLE,    // FIELD_queryIntervalCode
        FD_ISCOMPOUND,    // FIELD_sourceList
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv3QueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "resv",
        "suppressRouterProc",
        "robustnessVariable",
        "queryIntervalCode",
        "sourceList",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Igmpv3QueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "resv") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "suppressRouterProc") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "robustnessVariable") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "queryIntervalCode") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv3QueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_resv
        "bool",    // FIELD_suppressRouterProc
        "uint8_t",    // FIELD_robustnessVariable
        "uint8_t",    // FIELD_queryIntervalCode
        "inet::Ipv4AddressVector",    // FIELD_sourceList
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv3QueryDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv3QueryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv3QueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Igmpv3QueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv3Query'", field);
    }
}

const char *Igmpv3QueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv3QueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        case FIELD_resv: return ulong2string(pp->getResv());
        case FIELD_suppressRouterProc: return bool2string(pp->getSuppressRouterProc());
        case FIELD_robustnessVariable: return ulong2string(pp->getRobustnessVariable());
        case FIELD_queryIntervalCode: return ulong2string(pp->getQueryIntervalCode());
        case FIELD_sourceList: return "";
        default: return "";
    }
}

void Igmpv3QueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        case FIELD_resv: pp->setResv(string2ulong(value)); break;
        case FIELD_suppressRouterProc: pp->setSuppressRouterProc(string2bool(value)); break;
        case FIELD_robustnessVariable: pp->setRobustnessVariable(string2ulong(value)); break;
        case FIELD_queryIntervalCode: pp->setQueryIntervalCode(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Query'", field);
    }
}

omnetpp::cValue Igmpv3QueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        case FIELD_resv: return (omnetpp::intval_t)(pp->getResv());
        case FIELD_suppressRouterProc: return pp->getSuppressRouterProc();
        case FIELD_robustnessVariable: return (omnetpp::intval_t)(pp->getRobustnessVariable());
        case FIELD_queryIntervalCode: return (omnetpp::intval_t)(pp->getQueryIntervalCode());
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv3Query' as cValue -- field index out of range?", field);
    }
}

void Igmpv3QueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        case FIELD_resv: pp->setResv(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_suppressRouterProc: pp->setSuppressRouterProc(value.boolValue()); break;
        case FIELD_robustnessVariable: pp->setRobustnessVariable(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_queryIntervalCode: pp->setQueryIntervalCode(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Query'", field);
    }
}

const char *Igmpv3QueryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sourceList: return omnetpp::opp_typename(typeid(Ipv4AddressVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr Igmpv3QueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv3QueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Query *pp = omnetpp::fromAnyPtr<Igmpv3Query>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Query'", field);
    }
}

Register_Enum(inet::GroupRecordType, (inet::GroupRecordType::MODE_IS_INCLUDE, inet::GroupRecordType::MODE_IS_EXCLUDE, inet::GroupRecordType::CHANGE_TO_INCLUDE_MODE, inet::GroupRecordType::CHANGE_TO_EXCLUDE_MODE, inet::GroupRecordType::ALLOW_NEW_SOURCES, inet::GroupRecordType::BLOCK_OLD_SOURCE));

GroupRecord::GroupRecord()
{
}

GroupRecord::GroupRecord(const GroupRecord& other)
{
    copy(other);
}

GroupRecord::~GroupRecord()
{
    delete [] this->auxData;
}

GroupRecord& GroupRecord::operator=(const GroupRecord& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void GroupRecord::copy(const GroupRecord& other)
{
    this->recordType = other.recordType;
    this->groupAddress = other.groupAddress;
    this->sourceList = other.sourceList;
    delete [] this->auxData;
    this->auxData = (other.auxData_arraysize==0) ? nullptr : new uint32_t[other.auxData_arraysize];
    auxData_arraysize = other.auxData_arraysize;
    for (size_t i = 0; i < auxData_arraysize; i++) {
        this->auxData[i] = other.auxData[i];
    }
}

void GroupRecord::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->recordType);
    doParsimPacking(b,this->groupAddress);
    doParsimPacking(b,this->sourceList);
    b->pack(auxData_arraysize);
    doParsimArrayPacking(b,this->auxData,auxData_arraysize);
}

void GroupRecord::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->recordType);
    doParsimUnpacking(b,this->groupAddress);
    doParsimUnpacking(b,this->sourceList);
    delete [] this->auxData;
    b->unpack(auxData_arraysize);
    if (auxData_arraysize == 0) {
        this->auxData = nullptr;
    } else {
        this->auxData = new uint32_t[auxData_arraysize];
        doParsimArrayUnpacking(b,this->auxData,auxData_arraysize);
    }
}

int GroupRecord::getRecordType() const
{
    return this->recordType;
}

void GroupRecord::setRecordType(int recordType)
{
    this->recordType = recordType;
}

const Ipv4Address& GroupRecord::getGroupAddress() const
{
    return this->groupAddress;
}

void GroupRecord::setGroupAddress(const Ipv4Address& groupAddress)
{
    this->groupAddress = groupAddress;
}

const Ipv4AddressVector& GroupRecord::getSourceList() const
{
    return this->sourceList;
}

void GroupRecord::setSourceList(const Ipv4AddressVector& sourceList)
{
    this->sourceList = sourceList;
}

size_t GroupRecord::getAuxDataArraySize() const
{
    return auxData_arraysize;
}

uint32_t GroupRecord::getAuxData(size_t k) const
{
    if (k >= auxData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)auxData_arraysize, (unsigned long)k);
    return this->auxData[k];
}

void GroupRecord::setAuxDataArraySize(size_t newSize)
{
    uint32_t *auxData2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = auxData_arraysize < newSize ? auxData_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        auxData2[i] = this->auxData[i];
    for (size_t i = minSize; i < newSize; i++)
        auxData2[i] = 0;
    delete [] this->auxData;
    this->auxData = auxData2;
    auxData_arraysize = newSize;
}

void GroupRecord::setAuxData(size_t k, uint32_t auxData)
{
    if (k >= auxData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)auxData_arraysize, (unsigned long)k);
    this->auxData[k] = auxData;
}

void GroupRecord::insertAuxData(size_t k, uint32_t auxData)
{
    if (k > auxData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)auxData_arraysize, (unsigned long)k);
    size_t newSize = auxData_arraysize + 1;
    uint32_t *auxData2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        auxData2[i] = this->auxData[i];
    auxData2[k] = auxData;
    for (i = k + 1; i < newSize; i++)
        auxData2[i] = this->auxData[i-1];
    delete [] this->auxData;
    this->auxData = auxData2;
    auxData_arraysize = newSize;
}

void GroupRecord::appendAuxData(uint32_t auxData)
{
    insertAuxData(auxData_arraysize, auxData);
}

void GroupRecord::eraseAuxData(size_t k)
{
    if (k >= auxData_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)auxData_arraysize, (unsigned long)k);
    size_t newSize = auxData_arraysize - 1;
    uint32_t *auxData2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        auxData2[i] = this->auxData[i];
    for (i = k; i < newSize; i++)
        auxData2[i] = this->auxData[i+1];
    delete [] this->auxData;
    this->auxData = auxData2;
    auxData_arraysize = newSize;
}

class GroupRecordDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_recordType,
        FIELD_groupAddress,
        FIELD_sourceList,
        FIELD_auxData,
    };
  public:
    GroupRecordDescriptor();
    virtual ~GroupRecordDescriptor();

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

Register_ClassDescriptor(GroupRecordDescriptor)

GroupRecordDescriptor::GroupRecordDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::GroupRecord)), "")
{
    propertyNames = nullptr;
}

GroupRecordDescriptor::~GroupRecordDescriptor()
{
    delete[] propertyNames;
}

bool GroupRecordDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GroupRecord *>(obj)!=nullptr;
}

const char **GroupRecordDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GroupRecordDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GroupRecordDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int GroupRecordDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_recordType
        0,    // FIELD_groupAddress
        FD_ISCOMPOUND,    // FIELD_sourceList
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_auxData
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *GroupRecordDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "recordType",
        "groupAddress",
        "sourceList",
        "auxData",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int GroupRecordDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "recordType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "groupAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sourceList") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "auxData") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *GroupRecordDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_recordType
        "inet::Ipv4Address",    // FIELD_groupAddress
        "inet::Ipv4AddressVector",    // FIELD_sourceList
        "uint32_t",    // FIELD_auxData
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **GroupRecordDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_recordType: {
            static const char *names[] = { "enum", "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *GroupRecordDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_recordType:
            if (!strcmp(propertyName, "enum")) return "GroupRecordType";
            if (!strcmp(propertyName, "enum")) return "inet::GroupRecordType";
            return nullptr;
        default: return nullptr;
    }
}

int GroupRecordDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_auxData: return pp->getAuxDataArraySize();
        default: return 0;
    }
}

void GroupRecordDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_auxData: pp->setAuxDataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GroupRecord'", field);
    }
}

const char *GroupRecordDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GroupRecordDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_recordType: return enum2string(pp->getRecordType(), "inet::GroupRecordType");
        case FIELD_groupAddress: return pp->getGroupAddress().str();
        case FIELD_sourceList: return "";
        case FIELD_auxData: return ulong2string(pp->getAuxData(i));
        default: return "";
    }
}

void GroupRecordDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_recordType: pp->setRecordType((inet::GroupRecordType)string2enum(value, "inet::GroupRecordType")); break;
        case FIELD_auxData: pp->setAuxData(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GroupRecord'", field);
    }
}

omnetpp::cValue GroupRecordDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_recordType: return pp->getRecordType();
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList()); break;
        case FIELD_auxData: return (omnetpp::intval_t)(pp->getAuxData(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GroupRecord' as cValue -- field index out of range?", field);
    }
}

void GroupRecordDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_recordType: pp->setRecordType((inet::GroupRecordType)value.intValue()); break;
        case FIELD_auxData: pp->setAuxData(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GroupRecord'", field);
    }
}

const char *GroupRecordDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sourceList: return omnetpp::opp_typename(typeid(Ipv4AddressVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr GroupRecordDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        case FIELD_groupAddress: return omnetpp::toAnyPtr(&pp->getGroupAddress()); break;
        case FIELD_sourceList: return omnetpp::toAnyPtr(&pp->getSourceList()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GroupRecordDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GroupRecord *pp = omnetpp::fromAnyPtr<GroupRecord>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GroupRecord'", field);
    }
}

Register_Class(Igmpv3Report)

Igmpv3Report::Igmpv3Report() : ::inet::IgmpMessage()
{
    this->setType(IGMPV3_MEMBERSHIP_REPORT);

}

Igmpv3Report::Igmpv3Report(const Igmpv3Report& other) : ::inet::IgmpMessage(other)
{
    copy(other);
}

Igmpv3Report::~Igmpv3Report()
{
    delete [] this->groupRecord;
}

Igmpv3Report& Igmpv3Report::operator=(const Igmpv3Report& other)
{
    if (this == &other) return *this;
    ::inet::IgmpMessage::operator=(other);
    copy(other);
    return *this;
}

void Igmpv3Report::copy(const Igmpv3Report& other)
{
    this->resv1 = other.resv1;
    this->resv2 = other.resv2;
    delete [] this->groupRecord;
    this->groupRecord = (other.groupRecord_arraysize==0) ? nullptr : new GroupRecord[other.groupRecord_arraysize];
    groupRecord_arraysize = other.groupRecord_arraysize;
    for (size_t i = 0; i < groupRecord_arraysize; i++) {
        this->groupRecord[i] = other.groupRecord[i];
    }
}

void Igmpv3Report::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::IgmpMessage::parsimPack(b);
    doParsimPacking(b,this->resv1);
    doParsimPacking(b,this->resv2);
    b->pack(groupRecord_arraysize);
    doParsimArrayPacking(b,this->groupRecord,groupRecord_arraysize);
}

void Igmpv3Report::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::IgmpMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->resv1);
    doParsimUnpacking(b,this->resv2);
    delete [] this->groupRecord;
    b->unpack(groupRecord_arraysize);
    if (groupRecord_arraysize == 0) {
        this->groupRecord = nullptr;
    } else {
        this->groupRecord = new GroupRecord[groupRecord_arraysize];
        doParsimArrayUnpacking(b,this->groupRecord,groupRecord_arraysize);
    }
}

uint8_t Igmpv3Report::getResv1() const
{
    return this->resv1;
}

void Igmpv3Report::setResv1(uint8_t resv1)
{
    handleChange();
    this->resv1 = resv1;
}

uint16_t Igmpv3Report::getResv2() const
{
    return this->resv2;
}

void Igmpv3Report::setResv2(uint16_t resv2)
{
    handleChange();
    this->resv2 = resv2;
}

size_t Igmpv3Report::getGroupRecordArraySize() const
{
    return groupRecord_arraysize;
}

const GroupRecord& Igmpv3Report::getGroupRecord(size_t k) const
{
    if (k >= groupRecord_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)groupRecord_arraysize, (unsigned long)k);
    return this->groupRecord[k];
}

void Igmpv3Report::setGroupRecordArraySize(size_t newSize)
{
    handleChange();
    GroupRecord *groupRecord2 = (newSize==0) ? nullptr : new GroupRecord[newSize];
    size_t minSize = groupRecord_arraysize < newSize ? groupRecord_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        groupRecord2[i] = this->groupRecord[i];
    delete [] this->groupRecord;
    this->groupRecord = groupRecord2;
    groupRecord_arraysize = newSize;
}

void Igmpv3Report::setGroupRecord(size_t k, const GroupRecord& groupRecord)
{
    if (k >= groupRecord_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)groupRecord_arraysize, (unsigned long)k);
    handleChange();
    this->groupRecord[k] = groupRecord;
}

void Igmpv3Report::insertGroupRecord(size_t k, const GroupRecord& groupRecord)
{
    if (k > groupRecord_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)groupRecord_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = groupRecord_arraysize + 1;
    GroupRecord *groupRecord2 = new GroupRecord[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        groupRecord2[i] = this->groupRecord[i];
    groupRecord2[k] = groupRecord;
    for (i = k + 1; i < newSize; i++)
        groupRecord2[i] = this->groupRecord[i-1];
    delete [] this->groupRecord;
    this->groupRecord = groupRecord2;
    groupRecord_arraysize = newSize;
}

void Igmpv3Report::appendGroupRecord(const GroupRecord& groupRecord)
{
    insertGroupRecord(groupRecord_arraysize, groupRecord);
}

void Igmpv3Report::eraseGroupRecord(size_t k)
{
    if (k >= groupRecord_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)groupRecord_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = groupRecord_arraysize - 1;
    GroupRecord *groupRecord2 = (newSize == 0) ? nullptr : new GroupRecord[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        groupRecord2[i] = this->groupRecord[i];
    for (i = k; i < newSize; i++)
        groupRecord2[i] = this->groupRecord[i+1];
    delete [] this->groupRecord;
    this->groupRecord = groupRecord2;
    groupRecord_arraysize = newSize;
}

class Igmpv3ReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_resv1,
        FIELD_resv2,
        FIELD_groupRecord,
    };
  public:
    Igmpv3ReportDescriptor();
    virtual ~Igmpv3ReportDescriptor();

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

Register_ClassDescriptor(Igmpv3ReportDescriptor)

Igmpv3ReportDescriptor::Igmpv3ReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Igmpv3Report)), "inet::IgmpMessage")
{
    propertyNames = nullptr;
}

Igmpv3ReportDescriptor::~Igmpv3ReportDescriptor()
{
    delete[] propertyNames;
}

bool Igmpv3ReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Igmpv3Report *>(obj)!=nullptr;
}

const char **Igmpv3ReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Igmpv3ReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Igmpv3ReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Igmpv3ReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_resv1
        FD_ISEDITABLE,    // FIELD_resv2
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_groupRecord
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Igmpv3ReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "resv1",
        "resv2",
        "groupRecord",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Igmpv3ReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "resv1") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "resv2") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "groupRecord") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Igmpv3ReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_resv1
        "uint16_t",    // FIELD_resv2
        "inet::GroupRecord",    // FIELD_groupRecord
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Igmpv3ReportDescriptor::getFieldPropertyNames(int field) const
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

const char *Igmpv3ReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Igmpv3ReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_groupRecord: return pp->getGroupRecordArraySize();
        default: return 0;
    }
}

void Igmpv3ReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_groupRecord: pp->setGroupRecordArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Igmpv3Report'", field);
    }
}

const char *Igmpv3ReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Igmpv3ReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_resv1: return ulong2string(pp->getResv1());
        case FIELD_resv2: return ulong2string(pp->getResv2());
        case FIELD_groupRecord: return "";
        default: return "";
    }
}

void Igmpv3ReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_resv1: pp->setResv1(string2ulong(value)); break;
        case FIELD_resv2: pp->setResv2(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Report'", field);
    }
}

omnetpp::cValue Igmpv3ReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_resv1: return (omnetpp::intval_t)(pp->getResv1());
        case FIELD_resv2: return (omnetpp::intval_t)(pp->getResv2());
        case FIELD_groupRecord: return omnetpp::toAnyPtr(&pp->getGroupRecord(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Igmpv3Report' as cValue -- field index out of range?", field);
    }
}

void Igmpv3ReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_resv1: pp->setResv1(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_resv2: pp->setResv2(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Report'", field);
    }
}

const char *Igmpv3ReportDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_groupRecord: return omnetpp::opp_typename(typeid(GroupRecord));
        default: return nullptr;
    };
}

omnetpp::any_ptr Igmpv3ReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        case FIELD_groupRecord: return omnetpp::toAnyPtr(&pp->getGroupRecord(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Igmpv3ReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Igmpv3Report *pp = omnetpp::fromAnyPtr<Igmpv3Report>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Igmpv3Report'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

