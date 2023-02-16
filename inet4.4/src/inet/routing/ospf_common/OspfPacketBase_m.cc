//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/ospf_common/OspfPacketBase.msg.
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
#include "OspfPacketBase_m.h"

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
namespace ospf {

Register_Enum(inet::ospf::OspfPacketType, (inet::ospf::OspfPacketType::HELLO_PACKET, inet::ospf::OspfPacketType::DATABASE_DESCRIPTION_PACKET, inet::ospf::OspfPacketType::LINKSTATE_REQUEST_PACKET, inet::ospf::OspfPacketType::LINKSTATE_UPDATE_PACKET, inet::ospf::OspfPacketType::LINKSTATE_ACKNOWLEDGEMENT_PACKET));

Register_Class(OspfPacketBase)

OspfPacketBase::OspfPacketBase() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(14));

}

OspfPacketBase::OspfPacketBase(const OspfPacketBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

OspfPacketBase::~OspfPacketBase()
{
}

OspfPacketBase& OspfPacketBase::operator=(const OspfPacketBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void OspfPacketBase::copy(const OspfPacketBase& other)
{
    this->version = other.version;
    this->type = other.type;
    this->packetLengthField = other.packetLengthField;
    this->routerID = other.routerID;
    this->areaID = other.areaID;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void OspfPacketBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->packetLengthField);
    doParsimPacking(b,this->routerID);
    doParsimPacking(b,this->areaID);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void OspfPacketBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->packetLengthField);
    doParsimUnpacking(b,this->routerID);
    doParsimUnpacking(b,this->areaID);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

short OspfPacketBase::getVersion() const
{
    return this->version;
}

void OspfPacketBase::setVersion(short version)
{
    handleChange();
    this->version = version;
}

OspfPacketType OspfPacketBase::getType() const
{
    return this->type;
}

void OspfPacketBase::setType(OspfPacketType type)
{
    handleChange();
    this->type = type;
}

int OspfPacketBase::getPacketLengthField() const
{
    return this->packetLengthField;
}

void OspfPacketBase::setPacketLengthField(int packetLengthField)
{
    handleChange();
    this->packetLengthField = packetLengthField;
}

const ::inet::Ipv4Address& OspfPacketBase::getRouterID() const
{
    return this->routerID;
}

void OspfPacketBase::setRouterID(const ::inet::Ipv4Address& routerID)
{
    handleChange();
    this->routerID = routerID;
}

const ::inet::Ipv4Address& OspfPacketBase::getAreaID() const
{
    return this->areaID;
}

void OspfPacketBase::setAreaID(const ::inet::Ipv4Address& areaID)
{
    handleChange();
    this->areaID = areaID;
}

uint16_t OspfPacketBase::getCrc() const
{
    return this->crc;
}

void OspfPacketBase::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode OspfPacketBase::getCrcMode() const
{
    return this->crcMode;
}

void OspfPacketBase::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class OspfPacketBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_type,
        FIELD_packetLengthField,
        FIELD_routerID,
        FIELD_areaID,
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    OspfPacketBaseDescriptor();
    virtual ~OspfPacketBaseDescriptor();

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

Register_ClassDescriptor(OspfPacketBaseDescriptor)

OspfPacketBaseDescriptor::OspfPacketBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ospf::OspfPacketBase)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

OspfPacketBaseDescriptor::~OspfPacketBaseDescriptor()
{
    delete[] propertyNames;
}

bool OspfPacketBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OspfPacketBase *>(obj)!=nullptr;
}

const char **OspfPacketBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *OspfPacketBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int OspfPacketBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int OspfPacketBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_packetLengthField
        0,    // FIELD_routerID
        0,    // FIELD_areaID
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *OspfPacketBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "type",
        "packetLengthField",
        "routerID",
        "areaID",
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int OspfPacketBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "packetLengthField") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "routerID") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "areaID") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *OspfPacketBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_version
        "inet::ospf::OspfPacketType",    // FIELD_type
        "int",    // FIELD_packetLengthField
        "inet::Ipv4Address",    // FIELD_routerID
        "inet::Ipv4Address",    // FIELD_areaID
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **OspfPacketBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *OspfPacketBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::ospf::OspfPacketType";
            return nullptr;
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int OspfPacketBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void OspfPacketBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'OspfPacketBase'", field);
    }
}

const char *OspfPacketBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OspfPacketBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        case FIELD_version: return long2string(pp->getVersion());
        case FIELD_type: return enum2string(pp->getType(), "inet::ospf::OspfPacketType");
        case FIELD_packetLengthField: return long2string(pp->getPacketLengthField());
        case FIELD_routerID: return pp->getRouterID().str();
        case FIELD_areaID: return pp->getAreaID().str();
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void OspfPacketBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2long(value)); break;
        case FIELD_packetLengthField: pp->setPacketLengthField(string2long(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacketBase'", field);
    }
}

omnetpp::cValue OspfPacketBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        case FIELD_version: return pp->getVersion();
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_packetLengthField: return pp->getPacketLengthField();
        case FIELD_routerID: return omnetpp::toAnyPtr(&pp->getRouterID()); break;
        case FIELD_areaID: return omnetpp::toAnyPtr(&pp->getAreaID()); break;
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'OspfPacketBase' as cValue -- field index out of range?", field);
    }
}

void OspfPacketBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_packetLengthField: pp->setPacketLengthField(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacketBase'", field);
    }
}

const char *OspfPacketBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr OspfPacketBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        case FIELD_routerID: return omnetpp::toAnyPtr(&pp->getRouterID()); break;
        case FIELD_areaID: return omnetpp::toAnyPtr(&pp->getAreaID()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void OspfPacketBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacketBase *pp = omnetpp::fromAnyPtr<OspfPacketBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacketBase'", field);
    }
}

}  // namespace ospf
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

