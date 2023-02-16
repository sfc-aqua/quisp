//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/sctp/SctpHeader.msg.
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
#include "SctpHeader_m.h"

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
namespace sctp {

SctpHeader_Base::SctpHeader_Base() : ::inet::TransportHeaderBase()
{
}

SctpHeader_Base::SctpHeader_Base(const SctpHeader_Base& other) : ::inet::TransportHeaderBase(other)
{
    copy(other);
}

SctpHeader_Base::~SctpHeader_Base()
{
}

SctpHeader_Base& SctpHeader_Base::operator=(const SctpHeader_Base& other)
{
    if (this == &other) return *this;
    ::inet::TransportHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void SctpHeader_Base::copy(const SctpHeader_Base& other)
{
    this->srcPort = other.srcPort;
    this->destPort = other.destPort;
    this->vTag = other.vTag;
    this->checksumOk = other.checksumOk;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
    this->headerLength = other.headerLength;
}

void SctpHeader_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TransportHeaderBase::parsimPack(b);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->destPort);
    doParsimPacking(b,this->vTag);
    doParsimPacking(b,this->checksumOk);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
    doParsimPacking(b,this->headerLength);
    // field sctpChunks is abstract or custom -- please do packing in customized class
}

void SctpHeader_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TransportHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->destPort);
    doParsimUnpacking(b,this->vTag);
    doParsimUnpacking(b,this->checksumOk);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
    doParsimUnpacking(b,this->headerLength);
    // field sctpChunks is abstract or custom -- please do unpacking in customized class
}

uint16_t SctpHeader_Base::getSrcPort() const
{
    return this->srcPort;
}

void SctpHeader_Base::setSrcPort(uint16_t srcPort)
{
    handleChange();
    this->srcPort = srcPort;
}

uint16_t SctpHeader_Base::getDestPort() const
{
    return this->destPort;
}

void SctpHeader_Base::setDestPort(uint16_t destPort)
{
    handleChange();
    this->destPort = destPort;
}

uint32_t SctpHeader_Base::getVTag() const
{
    return this->vTag;
}

void SctpHeader_Base::setVTag(uint32_t vTag)
{
    handleChange();
    this->vTag = vTag;
}

bool SctpHeader_Base::getChecksumOk() const
{
    return this->checksumOk;
}

void SctpHeader_Base::setChecksumOk(bool checksumOk)
{
    handleChange();
    this->checksumOk = checksumOk;
}

uint32_t SctpHeader_Base::getCrc() const
{
    return this->crc;
}

void SctpHeader_Base::setCrc(uint32_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode SctpHeader_Base::getCrcMode() const
{
    return this->crcMode;
}

void SctpHeader_Base::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

unsigned short SctpHeader_Base::getHeaderLength() const
{
    return this->headerLength;
}

void SctpHeader_Base::setHeaderLength(unsigned short headerLength)
{
    handleChange();
    this->headerLength = headerLength;
}

class SctpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcPort,
        FIELD_destPort,
        FIELD_vTag,
        FIELD_checksumOk,
        FIELD_crc,
        FIELD_crcMode,
        FIELD_headerLength,
        FIELD_sctpChunks,
    };
  public:
    SctpHeaderDescriptor();
    virtual ~SctpHeaderDescriptor();

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

Register_ClassDescriptor(SctpHeaderDescriptor)

SctpHeaderDescriptor::SctpHeaderDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpHeader", "inet::TransportHeaderBase")
{
    propertyNames = nullptr;
}

SctpHeaderDescriptor::~SctpHeaderDescriptor()
{
    delete[] propertyNames;
}

bool SctpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpHeader_Base *>(obj)!=nullptr;
}

const char **SctpHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpHeaderDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int SctpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISEDITABLE,    // FIELD_destPort
        FD_ISEDITABLE,    // FIELD_vTag
        FD_ISEDITABLE,    // FIELD_checksumOk
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_sctpChunks
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *SctpHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcPort",
        "destPort",
        "vTag",
        "checksumOk",
        "crc",
        "crcMode",
        "headerLength",
        "sctpChunks",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int SctpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destPort") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "vTag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "checksumOk") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sctpChunks") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_srcPort
        "uint16_t",    // FIELD_destPort
        "uint32_t",    // FIELD_vTag
        "bool",    // FIELD_checksumOk
        "uint32_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
        "unsigned short",    // FIELD_headerLength
        "inet::sctp::SctpChunk",    // FIELD_sctpChunks
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SctpHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int SctpHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunks: return pp->getSctpChunksArraySize();
        default: return 0;
    }
}

void SctpHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunks: pp->setSctpChunksArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpHeader_Base'", field);
    }
}

const char *SctpHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunks: { const SctpChunk * value = pp->getSctpChunks(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: return ulong2string(pp->getSrcPort());
        case FIELD_destPort: return ulong2string(pp->getDestPort());
        case FIELD_vTag: return ulong2string(pp->getVTag());
        case FIELD_checksumOk: return bool2string(pp->getChecksumOk());
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        case FIELD_headerLength: return ulong2string(pp->getHeaderLength());
        case FIELD_sctpChunks: { auto obj = pp->getSctpChunks(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void SctpHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(string2ulong(value)); break;
        case FIELD_destPort: pp->setDestPort(string2ulong(value)); break;
        case FIELD_vTag: pp->setVTag(string2ulong(value)); break;
        case FIELD_checksumOk: pp->setChecksumOk(string2bool(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        case FIELD_headerLength: pp->setHeaderLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeader_Base'", field);
    }
}

omnetpp::cValue SctpHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: return (omnetpp::intval_t)(pp->getSrcPort());
        case FIELD_destPort: return (omnetpp::intval_t)(pp->getDestPort());
        case FIELD_vTag: return (omnetpp::intval_t)(pp->getVTag());
        case FIELD_checksumOk: return pp->getChecksumOk();
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        case FIELD_headerLength: return (omnetpp::intval_t)(pp->getHeaderLength());
        case FIELD_sctpChunks: return omnetpp::toAnyPtr(pp->getSctpChunks(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpHeader_Base' as cValue -- field index out of range?", field);
    }
}

void SctpHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_destPort: pp->setDestPort(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_vTag: pp->setVTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_checksumOk: pp->setChecksumOk(value.boolValue()); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_sctpChunks: pp->setSctpChunks(i,omnetpp::fromAnyPtr<SctpChunk>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeader_Base'", field);
    }
}

const char *SctpHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sctpChunks: return omnetpp::opp_typename(typeid(SctpChunk));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunks: return omnetpp::toAnyPtr(pp->getSctpChunks(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeader_Base *pp = omnetpp::fromAnyPtr<SctpHeader_Base>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunks: pp->setSctpChunks(i,omnetpp::fromAnyPtr<SctpChunk>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeader_Base'", field);
    }
}

Register_Class(SctpChunk)

SctpChunk::SctpChunk(const char *name) : ::omnetpp::cPacket(name)
{
}

SctpChunk::SctpChunk(const SctpChunk& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SctpChunk::~SctpChunk()
{
    delete [] this->chunkName;
}

SctpChunk& SctpChunk::operator=(const SctpChunk& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SctpChunk::copy(const SctpChunk& other)
{
    this->sctpChunkType = other.sctpChunkType;
    this->flags = other.flags;
    this->length = other.length;
    delete [] this->chunkName;
    this->chunkName = (other.chunkName_arraysize==0) ? nullptr : new char[other.chunkName_arraysize];
    chunkName_arraysize = other.chunkName_arraysize;
    for (size_t i = 0; i < chunkName_arraysize; i++) {
        this->chunkName[i] = other.chunkName[i];
    }
}

void SctpChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sctpChunkType);
    doParsimPacking(b,this->flags);
    doParsimPacking(b,this->length);
    b->pack(chunkName_arraysize);
    doParsimArrayPacking(b,this->chunkName,chunkName_arraysize);
}

void SctpChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sctpChunkType);
    doParsimUnpacking(b,this->flags);
    doParsimUnpacking(b,this->length);
    delete [] this->chunkName;
    b->unpack(chunkName_arraysize);
    if (chunkName_arraysize == 0) {
        this->chunkName = nullptr;
    } else {
        this->chunkName = new char[chunkName_arraysize];
        doParsimArrayUnpacking(b,this->chunkName,chunkName_arraysize);
    }
}

uint8_t SctpChunk::getSctpChunkType() const
{
    return this->sctpChunkType;
}

void SctpChunk::setSctpChunkType(uint8_t sctpChunkType)
{
    this->sctpChunkType = sctpChunkType;
}

uint32_t SctpChunk::getFlags() const
{
    return this->flags;
}

void SctpChunk::setFlags(uint32_t flags)
{
    this->flags = flags;
}

unsigned short SctpChunk::getLength() const
{
    return this->length;
}

void SctpChunk::setLength(unsigned short length)
{
    this->length = length;
}

size_t SctpChunk::getChunkNameArraySize() const
{
    return chunkName_arraysize;
}

char SctpChunk::getChunkName(size_t k) const
{
    if (k >= chunkName_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkName_arraysize, (unsigned long)k);
    return this->chunkName[k];
}

void SctpChunk::setChunkNameArraySize(size_t newSize)
{
    char *chunkName2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = chunkName_arraysize < newSize ? chunkName_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        chunkName2[i] = this->chunkName[i];
    for (size_t i = minSize; i < newSize; i++)
        chunkName2[i] = 0;
    delete [] this->chunkName;
    this->chunkName = chunkName2;
    chunkName_arraysize = newSize;
}

void SctpChunk::setChunkName(size_t k, char chunkName)
{
    if (k >= chunkName_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkName_arraysize, (unsigned long)k);
    this->chunkName[k] = chunkName;
}

void SctpChunk::insertChunkName(size_t k, char chunkName)
{
    if (k > chunkName_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkName_arraysize, (unsigned long)k);
    size_t newSize = chunkName_arraysize + 1;
    char *chunkName2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        chunkName2[i] = this->chunkName[i];
    chunkName2[k] = chunkName;
    for (i = k + 1; i < newSize; i++)
        chunkName2[i] = this->chunkName[i-1];
    delete [] this->chunkName;
    this->chunkName = chunkName2;
    chunkName_arraysize = newSize;
}

void SctpChunk::appendChunkName(char chunkName)
{
    insertChunkName(chunkName_arraysize, chunkName);
}

void SctpChunk::eraseChunkName(size_t k)
{
    if (k >= chunkName_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)chunkName_arraysize, (unsigned long)k);
    size_t newSize = chunkName_arraysize - 1;
    char *chunkName2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        chunkName2[i] = this->chunkName[i];
    for (i = k; i < newSize; i++)
        chunkName2[i] = this->chunkName[i+1];
    delete [] this->chunkName;
    this->chunkName = chunkName2;
    chunkName_arraysize = newSize;
}

class SctpChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sctpChunkType,
        FIELD_flags,
        FIELD_length,
        FIELD_chunkName,
    };
  public:
    SctpChunkDescriptor();
    virtual ~SctpChunkDescriptor();

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

Register_ClassDescriptor(SctpChunkDescriptor)

SctpChunkDescriptor::SctpChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpChunk)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SctpChunkDescriptor::~SctpChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpChunk *>(obj)!=nullptr;
}

const char **SctpChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpChunkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sctpChunkType
        FD_ISEDITABLE,    // FIELD_flags
        FD_ISEDITABLE,    // FIELD_length
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_chunkName
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sctpChunkType",
        "flags",
        "length",
        "chunkName",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sctpChunkType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "flags") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "chunkName") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_sctpChunkType
        "uint32_t",    // FIELD_flags
        "unsigned short",    // FIELD_length
        "char",    // FIELD_chunkName
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_chunkName: return pp->getChunkNameArraySize();
        default: return 0;
    }
}

void SctpChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_chunkName: pp->setChunkNameArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpChunk'", field);
    }
}

const char *SctpChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkType: return ulong2string(pp->getSctpChunkType());
        case FIELD_flags: return ulong2string(pp->getFlags());
        case FIELD_length: return ulong2string(pp->getLength());
        case FIELD_chunkName: return long2string(pp->getChunkName(i));
        default: return "";
    }
}

void SctpChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkType: pp->setSctpChunkType(string2ulong(value)); break;
        case FIELD_flags: pp->setFlags(string2ulong(value)); break;
        case FIELD_length: pp->setLength(string2ulong(value)); break;
        case FIELD_chunkName: pp->setChunkName(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpChunk'", field);
    }
}

omnetpp::cValue SctpChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkType: return (omnetpp::intval_t)(pp->getSctpChunkType());
        case FIELD_flags: return (omnetpp::intval_t)(pp->getFlags());
        case FIELD_length: return (omnetpp::intval_t)(pp->getLength());
        case FIELD_chunkName: return pp->getChunkName(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpChunk' as cValue -- field index out of range?", field);
    }
}

void SctpChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkType: pp->setSctpChunkType(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_flags: pp->setFlags(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_chunkName: pp->setChunkName(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpChunk'", field);
    }
}

const char *SctpChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpChunk *pp = omnetpp::fromAnyPtr<SctpChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpChunk'", field);
    }
}

Register_Class(SctpInitChunk)

SctpInitChunk::SctpInitChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpInitChunk::SctpInitChunk(const SctpInitChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpInitChunk::~SctpInitChunk()
{
    delete [] this->addresses;
    delete [] this->unrecognizedParameters;
    delete [] this->sctpChunkTypes;
    delete [] this->sepChunks;
    delete [] this->hmacTypes;
    delete [] this->random;
}

SctpInitChunk& SctpInitChunk::operator=(const SctpInitChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpInitChunk::copy(const SctpInitChunk& other)
{
    this->initTag = other.initTag;
    this->a_rwnd = other.a_rwnd;
    this->noOutStreams = other.noOutStreams;
    this->noInStreams = other.noInStreams;
    this->initTsn = other.initTsn;
    this->forwardTsn = other.forwardTsn;
    this->ipv4Supported = other.ipv4Supported;
    this->ipv6Supported = other.ipv6Supported;
    delete [] this->addresses;
    this->addresses = (other.addresses_arraysize==0) ? nullptr : new ::inet::L3Address[other.addresses_arraysize];
    addresses_arraysize = other.addresses_arraysize;
    for (size_t i = 0; i < addresses_arraysize; i++) {
        this->addresses[i] = other.addresses[i];
    }
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = (other.unrecognizedParameters_arraysize==0) ? nullptr : new uint8_t[other.unrecognizedParameters_arraysize];
    unrecognizedParameters_arraysize = other.unrecognizedParameters_arraysize;
    for (size_t i = 0; i < unrecognizedParameters_arraysize; i++) {
        this->unrecognizedParameters[i] = other.unrecognizedParameters[i];
    }
    this->msg_rwnd = other.msg_rwnd;
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = (other.sctpChunkTypes_arraysize==0) ? nullptr : new uint16_t[other.sctpChunkTypes_arraysize];
    sctpChunkTypes_arraysize = other.sctpChunkTypes_arraysize;
    for (size_t i = 0; i < sctpChunkTypes_arraysize; i++) {
        this->sctpChunkTypes[i] = other.sctpChunkTypes[i];
    }
    delete [] this->sepChunks;
    this->sepChunks = (other.sepChunks_arraysize==0) ? nullptr : new uint16_t[other.sepChunks_arraysize];
    sepChunks_arraysize = other.sepChunks_arraysize;
    for (size_t i = 0; i < sepChunks_arraysize; i++) {
        this->sepChunks[i] = other.sepChunks[i];
    }
    delete [] this->hmacTypes;
    this->hmacTypes = (other.hmacTypes_arraysize==0) ? nullptr : new uint16_t[other.hmacTypes_arraysize];
    hmacTypes_arraysize = other.hmacTypes_arraysize;
    for (size_t i = 0; i < hmacTypes_arraysize; i++) {
        this->hmacTypes[i] = other.hmacTypes[i];
    }
    delete [] this->random;
    this->random = (other.random_arraysize==0) ? nullptr : new uint8_t[other.random_arraysize];
    random_arraysize = other.random_arraysize;
    for (size_t i = 0; i < random_arraysize; i++) {
        this->random[i] = other.random[i];
    }
}

void SctpInitChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->initTag);
    doParsimPacking(b,this->a_rwnd);
    doParsimPacking(b,this->noOutStreams);
    doParsimPacking(b,this->noInStreams);
    doParsimPacking(b,this->initTsn);
    doParsimPacking(b,this->forwardTsn);
    doParsimPacking(b,this->ipv4Supported);
    doParsimPacking(b,this->ipv6Supported);
    b->pack(addresses_arraysize);
    doParsimArrayPacking(b,this->addresses,addresses_arraysize);
    b->pack(unrecognizedParameters_arraysize);
    doParsimArrayPacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
    doParsimPacking(b,this->msg_rwnd);
    b->pack(sctpChunkTypes_arraysize);
    doParsimArrayPacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
    b->pack(sepChunks_arraysize);
    doParsimArrayPacking(b,this->sepChunks,sepChunks_arraysize);
    b->pack(hmacTypes_arraysize);
    doParsimArrayPacking(b,this->hmacTypes,hmacTypes_arraysize);
    b->pack(random_arraysize);
    doParsimArrayPacking(b,this->random,random_arraysize);
}

void SctpInitChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->initTag);
    doParsimUnpacking(b,this->a_rwnd);
    doParsimUnpacking(b,this->noOutStreams);
    doParsimUnpacking(b,this->noInStreams);
    doParsimUnpacking(b,this->initTsn);
    doParsimUnpacking(b,this->forwardTsn);
    doParsimUnpacking(b,this->ipv4Supported);
    doParsimUnpacking(b,this->ipv6Supported);
    delete [] this->addresses;
    b->unpack(addresses_arraysize);
    if (addresses_arraysize == 0) {
        this->addresses = nullptr;
    } else {
        this->addresses = new ::inet::L3Address[addresses_arraysize];
        doParsimArrayUnpacking(b,this->addresses,addresses_arraysize);
    }
    delete [] this->unrecognizedParameters;
    b->unpack(unrecognizedParameters_arraysize);
    if (unrecognizedParameters_arraysize == 0) {
        this->unrecognizedParameters = nullptr;
    } else {
        this->unrecognizedParameters = new uint8_t[unrecognizedParameters_arraysize];
        doParsimArrayUnpacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
    }
    doParsimUnpacking(b,this->msg_rwnd);
    delete [] this->sctpChunkTypes;
    b->unpack(sctpChunkTypes_arraysize);
    if (sctpChunkTypes_arraysize == 0) {
        this->sctpChunkTypes = nullptr;
    } else {
        this->sctpChunkTypes = new uint16_t[sctpChunkTypes_arraysize];
        doParsimArrayUnpacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
    }
    delete [] this->sepChunks;
    b->unpack(sepChunks_arraysize);
    if (sepChunks_arraysize == 0) {
        this->sepChunks = nullptr;
    } else {
        this->sepChunks = new uint16_t[sepChunks_arraysize];
        doParsimArrayUnpacking(b,this->sepChunks,sepChunks_arraysize);
    }
    delete [] this->hmacTypes;
    b->unpack(hmacTypes_arraysize);
    if (hmacTypes_arraysize == 0) {
        this->hmacTypes = nullptr;
    } else {
        this->hmacTypes = new uint16_t[hmacTypes_arraysize];
        doParsimArrayUnpacking(b,this->hmacTypes,hmacTypes_arraysize);
    }
    delete [] this->random;
    b->unpack(random_arraysize);
    if (random_arraysize == 0) {
        this->random = nullptr;
    } else {
        this->random = new uint8_t[random_arraysize];
        doParsimArrayUnpacking(b,this->random,random_arraysize);
    }
}

uint32_t SctpInitChunk::getInitTag() const
{
    return this->initTag;
}

void SctpInitChunk::setInitTag(uint32_t initTag)
{
    this->initTag = initTag;
}

uint32_t SctpInitChunk::getA_rwnd() const
{
    return this->a_rwnd;
}

void SctpInitChunk::setA_rwnd(uint32_t a_rwnd)
{
    this->a_rwnd = a_rwnd;
}

uint16_t SctpInitChunk::getNoOutStreams() const
{
    return this->noOutStreams;
}

void SctpInitChunk::setNoOutStreams(uint16_t noOutStreams)
{
    this->noOutStreams = noOutStreams;
}

uint16_t SctpInitChunk::getNoInStreams() const
{
    return this->noInStreams;
}

void SctpInitChunk::setNoInStreams(uint16_t noInStreams)
{
    this->noInStreams = noInStreams;
}

uint32_t SctpInitChunk::getInitTsn() const
{
    return this->initTsn;
}

void SctpInitChunk::setInitTsn(uint32_t initTsn)
{
    this->initTsn = initTsn;
}

bool SctpInitChunk::getForwardTsn() const
{
    return this->forwardTsn;
}

void SctpInitChunk::setForwardTsn(bool forwardTsn)
{
    this->forwardTsn = forwardTsn;
}

bool SctpInitChunk::getIpv4Supported() const
{
    return this->ipv4Supported;
}

void SctpInitChunk::setIpv4Supported(bool ipv4Supported)
{
    this->ipv4Supported = ipv4Supported;
}

bool SctpInitChunk::getIpv6Supported() const
{
    return this->ipv6Supported;
}

void SctpInitChunk::setIpv6Supported(bool ipv6Supported)
{
    this->ipv6Supported = ipv6Supported;
}

size_t SctpInitChunk::getAddressesArraySize() const
{
    return addresses_arraysize;
}

const ::inet::L3Address& SctpInitChunk::getAddresses(size_t k) const
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    return this->addresses[k];
}

void SctpInitChunk::setAddressesArraySize(size_t newSize)
{
    ::inet::L3Address *addresses2 = (newSize==0) ? nullptr : new ::inet::L3Address[newSize];
    size_t minSize = addresses_arraysize < newSize ? addresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        addresses2[i] = this->addresses[i];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void SctpInitChunk::setAddresses(size_t k, const ::inet::L3Address& addresses)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    this->addresses[k] = addresses;
}

void SctpInitChunk::insertAddresses(size_t k, const ::inet::L3Address& addresses)
{
    if (k > addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    size_t newSize = addresses_arraysize + 1;
    ::inet::L3Address *addresses2 = new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    addresses2[k] = addresses;
    for (i = k + 1; i < newSize; i++)
        addresses2[i] = this->addresses[i-1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void SctpInitChunk::appendAddresses(const ::inet::L3Address& addresses)
{
    insertAddresses(addresses_arraysize, addresses);
}

void SctpInitChunk::eraseAddresses(size_t k)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    size_t newSize = addresses_arraysize - 1;
    ::inet::L3Address *addresses2 = (newSize == 0) ? nullptr : new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    for (i = k; i < newSize; i++)
        addresses2[i] = this->addresses[i+1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

size_t SctpInitChunk::getUnrecognizedParametersArraySize() const
{
    return unrecognizedParameters_arraysize;
}

uint8_t SctpInitChunk::getUnrecognizedParameters(size_t k) const
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    return this->unrecognizedParameters[k];
}

void SctpInitChunk::setUnrecognizedParametersArraySize(size_t newSize)
{
    uint8_t *unrecognizedParameters2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = unrecognizedParameters_arraysize < newSize ? unrecognizedParameters_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (size_t i = minSize; i < newSize; i++)
        unrecognizedParameters2[i] = 0;
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpInitChunk::setUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    this->unrecognizedParameters[k] = unrecognizedParameters;
}

void SctpInitChunk::insertUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k > unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize + 1;
    uint8_t *unrecognizedParameters2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    unrecognizedParameters2[k] = unrecognizedParameters;
    for (i = k + 1; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i-1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpInitChunk::appendUnrecognizedParameters(uint8_t unrecognizedParameters)
{
    insertUnrecognizedParameters(unrecognizedParameters_arraysize, unrecognizedParameters);
}

void SctpInitChunk::eraseUnrecognizedParameters(size_t k)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize - 1;
    uint8_t *unrecognizedParameters2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (i = k; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i+1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

uint32_t SctpInitChunk::getMsg_rwnd() const
{
    return this->msg_rwnd;
}

void SctpInitChunk::setMsg_rwnd(uint32_t msg_rwnd)
{
    this->msg_rwnd = msg_rwnd;
}

size_t SctpInitChunk::getSctpChunkTypesArraySize() const
{
    return sctpChunkTypes_arraysize;
}

uint16_t SctpInitChunk::getSctpChunkTypes(size_t k) const
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    return this->sctpChunkTypes[k];
}

void SctpInitChunk::setSctpChunkTypesArraySize(size_t newSize)
{
    uint16_t *sctpChunkTypes2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sctpChunkTypes_arraysize < newSize ? sctpChunkTypes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (size_t i = minSize; i < newSize; i++)
        sctpChunkTypes2[i] = 0;
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpInitChunk::setSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    this->sctpChunkTypes[k] = sctpChunkTypes;
}

void SctpInitChunk::insertSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k > sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize + 1;
    uint16_t *sctpChunkTypes2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    sctpChunkTypes2[k] = sctpChunkTypes;
    for (i = k + 1; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i-1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpInitChunk::appendSctpChunkTypes(uint16_t sctpChunkTypes)
{
    insertSctpChunkTypes(sctpChunkTypes_arraysize, sctpChunkTypes);
}

void SctpInitChunk::eraseSctpChunkTypes(size_t k)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize - 1;
    uint16_t *sctpChunkTypes2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (i = k; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i+1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

size_t SctpInitChunk::getSepChunksArraySize() const
{
    return sepChunks_arraysize;
}

uint16_t SctpInitChunk::getSepChunks(size_t k) const
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    return this->sepChunks[k];
}

void SctpInitChunk::setSepChunksArraySize(size_t newSize)
{
    uint16_t *sepChunks2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sepChunks_arraysize < newSize ? sepChunks_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sepChunks2[i] = this->sepChunks[i];
    for (size_t i = minSize; i < newSize; i++)
        sepChunks2[i] = 0;
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

void SctpInitChunk::setSepChunks(size_t k, uint16_t sepChunks)
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    this->sepChunks[k] = sepChunks;
}

void SctpInitChunk::insertSepChunks(size_t k, uint16_t sepChunks)
{
    if (k > sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    size_t newSize = sepChunks_arraysize + 1;
    uint16_t *sepChunks2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sepChunks2[i] = this->sepChunks[i];
    sepChunks2[k] = sepChunks;
    for (i = k + 1; i < newSize; i++)
        sepChunks2[i] = this->sepChunks[i-1];
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

void SctpInitChunk::appendSepChunks(uint16_t sepChunks)
{
    insertSepChunks(sepChunks_arraysize, sepChunks);
}

void SctpInitChunk::eraseSepChunks(size_t k)
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    size_t newSize = sepChunks_arraysize - 1;
    uint16_t *sepChunks2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sepChunks2[i] = this->sepChunks[i];
    for (i = k; i < newSize; i++)
        sepChunks2[i] = this->sepChunks[i+1];
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

size_t SctpInitChunk::getHmacTypesArraySize() const
{
    return hmacTypes_arraysize;
}

uint16_t SctpInitChunk::getHmacTypes(size_t k) const
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    return this->hmacTypes[k];
}

void SctpInitChunk::setHmacTypesArraySize(size_t newSize)
{
    uint16_t *hmacTypes2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = hmacTypes_arraysize < newSize ? hmacTypes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    for (size_t i = minSize; i < newSize; i++)
        hmacTypes2[i] = 0;
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

void SctpInitChunk::setHmacTypes(size_t k, uint16_t hmacTypes)
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    this->hmacTypes[k] = hmacTypes;
}

void SctpInitChunk::insertHmacTypes(size_t k, uint16_t hmacTypes)
{
    if (k > hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    size_t newSize = hmacTypes_arraysize + 1;
    uint16_t *hmacTypes2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    hmacTypes2[k] = hmacTypes;
    for (i = k + 1; i < newSize; i++)
        hmacTypes2[i] = this->hmacTypes[i-1];
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

void SctpInitChunk::appendHmacTypes(uint16_t hmacTypes)
{
    insertHmacTypes(hmacTypes_arraysize, hmacTypes);
}

void SctpInitChunk::eraseHmacTypes(size_t k)
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    size_t newSize = hmacTypes_arraysize - 1;
    uint16_t *hmacTypes2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    for (i = k; i < newSize; i++)
        hmacTypes2[i] = this->hmacTypes[i+1];
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

size_t SctpInitChunk::getRandomArraySize() const
{
    return random_arraysize;
}

uint8_t SctpInitChunk::getRandom(size_t k) const
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    return this->random[k];
}

void SctpInitChunk::setRandomArraySize(size_t newSize)
{
    uint8_t *random2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = random_arraysize < newSize ? random_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        random2[i] = this->random[i];
    for (size_t i = minSize; i < newSize; i++)
        random2[i] = 0;
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

void SctpInitChunk::setRandom(size_t k, uint8_t random)
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    this->random[k] = random;
}

void SctpInitChunk::insertRandom(size_t k, uint8_t random)
{
    if (k > random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    size_t newSize = random_arraysize + 1;
    uint8_t *random2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        random2[i] = this->random[i];
    random2[k] = random;
    for (i = k + 1; i < newSize; i++)
        random2[i] = this->random[i-1];
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

void SctpInitChunk::appendRandom(uint8_t random)
{
    insertRandom(random_arraysize, random);
}

void SctpInitChunk::eraseRandom(size_t k)
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    size_t newSize = random_arraysize - 1;
    uint8_t *random2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        random2[i] = this->random[i];
    for (i = k; i < newSize; i++)
        random2[i] = this->random[i+1];
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

class SctpInitChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_initTag,
        FIELD_a_rwnd,
        FIELD_noOutStreams,
        FIELD_noInStreams,
        FIELD_initTsn,
        FIELD_forwardTsn,
        FIELD_ipv4Supported,
        FIELD_ipv6Supported,
        FIELD_addresses,
        FIELD_unrecognizedParameters,
        FIELD_msg_rwnd,
        FIELD_sctpChunkTypes,
        FIELD_sepChunks,
        FIELD_hmacTypes,
        FIELD_random,
    };
  public:
    SctpInitChunkDescriptor();
    virtual ~SctpInitChunkDescriptor();

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

Register_ClassDescriptor(SctpInitChunkDescriptor)

SctpInitChunkDescriptor::SctpInitChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpInitChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpInitChunkDescriptor::~SctpInitChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpInitChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpInitChunk *>(obj)!=nullptr;
}

const char **SctpInitChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpInitChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpInitChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 15+base->getFieldCount() : 15;
}

unsigned int SctpInitChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_initTag
        FD_ISEDITABLE,    // FIELD_a_rwnd
        FD_ISEDITABLE,    // FIELD_noOutStreams
        FD_ISEDITABLE,    // FIELD_noInStreams
        FD_ISEDITABLE,    // FIELD_initTsn
        FD_ISEDITABLE,    // FIELD_forwardTsn
        FD_ISEDITABLE,    // FIELD_ipv4Supported
        FD_ISEDITABLE,    // FIELD_ipv6Supported
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_addresses
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_unrecognizedParameters
        FD_ISEDITABLE,    // FIELD_msg_rwnd
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sctpChunkTypes
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sepChunks
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_hmacTypes
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_random
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
}

const char *SctpInitChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "initTag",
        "a_rwnd",
        "noOutStreams",
        "noInStreams",
        "initTsn",
        "forwardTsn",
        "ipv4Supported",
        "ipv6Supported",
        "addresses",
        "unrecognizedParameters",
        "msg_rwnd",
        "sctpChunkTypes",
        "sepChunks",
        "hmacTypes",
        "random",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int SctpInitChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "initTag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "a_rwnd") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "noOutStreams") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "noInStreams") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "initTsn") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "forwardTsn") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "ipv4Supported") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ipv6Supported") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "addresses") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "unrecognizedParameters") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "msg_rwnd") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "sctpChunkTypes") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "sepChunks") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "hmacTypes") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "random") == 0) return baseIndex + 14;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpInitChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_initTag
        "uint32_t",    // FIELD_a_rwnd
        "uint16_t",    // FIELD_noOutStreams
        "uint16_t",    // FIELD_noInStreams
        "uint32_t",    // FIELD_initTsn
        "bool",    // FIELD_forwardTsn
        "bool",    // FIELD_ipv4Supported
        "bool",    // FIELD_ipv6Supported
        "inet::L3Address",    // FIELD_addresses
        "uint8_t",    // FIELD_unrecognizedParameters
        "uint32_t",    // FIELD_msg_rwnd
        "uint16_t",    // FIELD_sctpChunkTypes
        "uint16_t",    // FIELD_sepChunks
        "uint16_t",    // FIELD_hmacTypes
        "uint8_t",    // FIELD_random
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpInitChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpInitChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpInitChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: return pp->getAddressesArraySize();
        case FIELD_unrecognizedParameters: return pp->getUnrecognizedParametersArraySize();
        case FIELD_sctpChunkTypes: return pp->getSctpChunkTypesArraySize();
        case FIELD_sepChunks: return pp->getSepChunksArraySize();
        case FIELD_hmacTypes: return pp->getHmacTypesArraySize();
        case FIELD_random: return pp->getRandomArraySize();
        default: return 0;
    }
}

void SctpInitChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: pp->setAddressesArraySize(size); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParametersArraySize(size); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypesArraySize(size); break;
        case FIELD_sepChunks: pp->setSepChunksArraySize(size); break;
        case FIELD_hmacTypes: pp->setHmacTypesArraySize(size); break;
        case FIELD_random: pp->setRandomArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpInitChunk'", field);
    }
}

const char *SctpInitChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpInitChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: return ulong2string(pp->getInitTag());
        case FIELD_a_rwnd: return ulong2string(pp->getA_rwnd());
        case FIELD_noOutStreams: return ulong2string(pp->getNoOutStreams());
        case FIELD_noInStreams: return ulong2string(pp->getNoInStreams());
        case FIELD_initTsn: return ulong2string(pp->getInitTsn());
        case FIELD_forwardTsn: return bool2string(pp->getForwardTsn());
        case FIELD_ipv4Supported: return bool2string(pp->getIpv4Supported());
        case FIELD_ipv6Supported: return bool2string(pp->getIpv6Supported());
        case FIELD_addresses: return pp->getAddresses(i).str();
        case FIELD_unrecognizedParameters: return ulong2string(pp->getUnrecognizedParameters(i));
        case FIELD_msg_rwnd: return ulong2string(pp->getMsg_rwnd());
        case FIELD_sctpChunkTypes: return ulong2string(pp->getSctpChunkTypes(i));
        case FIELD_sepChunks: return ulong2string(pp->getSepChunks(i));
        case FIELD_hmacTypes: return ulong2string(pp->getHmacTypes(i));
        case FIELD_random: return ulong2string(pp->getRandom(i));
        default: return "";
    }
}

void SctpInitChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: pp->setInitTag(string2ulong(value)); break;
        case FIELD_a_rwnd: pp->setA_rwnd(string2ulong(value)); break;
        case FIELD_noOutStreams: pp->setNoOutStreams(string2ulong(value)); break;
        case FIELD_noInStreams: pp->setNoInStreams(string2ulong(value)); break;
        case FIELD_initTsn: pp->setInitTsn(string2ulong(value)); break;
        case FIELD_forwardTsn: pp->setForwardTsn(string2bool(value)); break;
        case FIELD_ipv4Supported: pp->setIpv4Supported(string2bool(value)); break;
        case FIELD_ipv6Supported: pp->setIpv6Supported(string2bool(value)); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,string2ulong(value)); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(string2ulong(value)); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,string2ulong(value)); break;
        case FIELD_sepChunks: pp->setSepChunks(i,string2ulong(value)); break;
        case FIELD_hmacTypes: pp->setHmacTypes(i,string2ulong(value)); break;
        case FIELD_random: pp->setRandom(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitChunk'", field);
    }
}

omnetpp::cValue SctpInitChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: return (omnetpp::intval_t)(pp->getInitTag());
        case FIELD_a_rwnd: return (omnetpp::intval_t)(pp->getA_rwnd());
        case FIELD_noOutStreams: return (omnetpp::intval_t)(pp->getNoOutStreams());
        case FIELD_noInStreams: return (omnetpp::intval_t)(pp->getNoInStreams());
        case FIELD_initTsn: return (omnetpp::intval_t)(pp->getInitTsn());
        case FIELD_forwardTsn: return pp->getForwardTsn();
        case FIELD_ipv4Supported: return pp->getIpv4Supported();
        case FIELD_ipv6Supported: return pp->getIpv6Supported();
        case FIELD_addresses: return omnetpp::toAnyPtr(&pp->getAddresses(i)); break;
        case FIELD_unrecognizedParameters: return (omnetpp::intval_t)(pp->getUnrecognizedParameters(i));
        case FIELD_msg_rwnd: return (omnetpp::intval_t)(pp->getMsg_rwnd());
        case FIELD_sctpChunkTypes: return (omnetpp::intval_t)(pp->getSctpChunkTypes(i));
        case FIELD_sepChunks: return (omnetpp::intval_t)(pp->getSepChunks(i));
        case FIELD_hmacTypes: return (omnetpp::intval_t)(pp->getHmacTypes(i));
        case FIELD_random: return (omnetpp::intval_t)(pp->getRandom(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpInitChunk' as cValue -- field index out of range?", field);
    }
}

void SctpInitChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: pp->setInitTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_a_rwnd: pp->setA_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_noOutStreams: pp->setNoOutStreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_noInStreams: pp->setNoInStreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_initTsn: pp->setInitTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_forwardTsn: pp->setForwardTsn(value.boolValue()); break;
        case FIELD_ipv4Supported: pp->setIpv4Supported(value.boolValue()); break;
        case FIELD_ipv6Supported: pp->setIpv6Supported(value.boolValue()); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_sepChunks: pp->setSepChunks(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_hmacTypes: pp->setHmacTypes(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_random: pp->setRandom(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitChunk'", field);
    }
}

const char *SctpInitChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpInitChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: return omnetpp::toAnyPtr(&pp->getAddresses(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpInitChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitChunk *pp = omnetpp::fromAnyPtr<SctpInitChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitChunk'", field);
    }
}

Register_Class(SctpInitAckChunk)

SctpInitAckChunk::SctpInitAckChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpInitAckChunk::SctpInitAckChunk(const SctpInitAckChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpInitAckChunk::~SctpInitAckChunk()
{
    delete [] this->addresses;
    delete [] this->cookie;
    delete [] this->unrecognizedParameters;
    delete [] this->random;
    delete [] this->sctpChunkTypes;
    delete [] this->sepChunks;
    delete [] this->hmacTypes;
}

SctpInitAckChunk& SctpInitAckChunk::operator=(const SctpInitAckChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpInitAckChunk::copy(const SctpInitAckChunk& other)
{
    this->initTag = other.initTag;
    this->a_rwnd = other.a_rwnd;
    this->noOutStreams = other.noOutStreams;
    this->noInStreams = other.noInStreams;
    this->initTsn = other.initTsn;
    this->forwardTsn = other.forwardTsn;
    this->ipv4Supported = other.ipv4Supported;
    this->ipv6Supported = other.ipv6Supported;
    delete [] this->addresses;
    this->addresses = (other.addresses_arraysize==0) ? nullptr : new ::inet::L3Address[other.addresses_arraysize];
    addresses_arraysize = other.addresses_arraysize;
    for (size_t i = 0; i < addresses_arraysize; i++) {
        this->addresses[i] = other.addresses[i];
    }
    delete [] this->cookie;
    this->cookie = (other.cookie_arraysize==0) ? nullptr : new char[other.cookie_arraysize];
    cookie_arraysize = other.cookie_arraysize;
    for (size_t i = 0; i < cookie_arraysize; i++) {
        this->cookie[i] = other.cookie[i];
    }
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = (other.unrecognizedParameters_arraysize==0) ? nullptr : new uint8_t[other.unrecognizedParameters_arraysize];
    unrecognizedParameters_arraysize = other.unrecognizedParameters_arraysize;
    for (size_t i = 0; i < unrecognizedParameters_arraysize; i++) {
        this->unrecognizedParameters[i] = other.unrecognizedParameters[i];
    }
    this->stateCookie = other.stateCookie;
    this->msg_rwnd = other.msg_rwnd;
    delete [] this->random;
    this->random = (other.random_arraysize==0) ? nullptr : new uint8_t[other.random_arraysize];
    random_arraysize = other.random_arraysize;
    for (size_t i = 0; i < random_arraysize; i++) {
        this->random[i] = other.random[i];
    }
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = (other.sctpChunkTypes_arraysize==0) ? nullptr : new uint16_t[other.sctpChunkTypes_arraysize];
    sctpChunkTypes_arraysize = other.sctpChunkTypes_arraysize;
    for (size_t i = 0; i < sctpChunkTypes_arraysize; i++) {
        this->sctpChunkTypes[i] = other.sctpChunkTypes[i];
    }
    delete [] this->sepChunks;
    this->sepChunks = (other.sepChunks_arraysize==0) ? nullptr : new uint16_t[other.sepChunks_arraysize];
    sepChunks_arraysize = other.sepChunks_arraysize;
    for (size_t i = 0; i < sepChunks_arraysize; i++) {
        this->sepChunks[i] = other.sepChunks[i];
    }
    delete [] this->hmacTypes;
    this->hmacTypes = (other.hmacTypes_arraysize==0) ? nullptr : new uint16_t[other.hmacTypes_arraysize];
    hmacTypes_arraysize = other.hmacTypes_arraysize;
    for (size_t i = 0; i < hmacTypes_arraysize; i++) {
        this->hmacTypes[i] = other.hmacTypes[i];
    }
}

void SctpInitAckChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->initTag);
    doParsimPacking(b,this->a_rwnd);
    doParsimPacking(b,this->noOutStreams);
    doParsimPacking(b,this->noInStreams);
    doParsimPacking(b,this->initTsn);
    doParsimPacking(b,this->forwardTsn);
    doParsimPacking(b,this->ipv4Supported);
    doParsimPacking(b,this->ipv6Supported);
    b->pack(addresses_arraysize);
    doParsimArrayPacking(b,this->addresses,addresses_arraysize);
    b->pack(cookie_arraysize);
    doParsimArrayPacking(b,this->cookie,cookie_arraysize);
    b->pack(unrecognizedParameters_arraysize);
    doParsimArrayPacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
    doParsimPacking(b,this->stateCookie);
    doParsimPacking(b,this->msg_rwnd);
    b->pack(random_arraysize);
    doParsimArrayPacking(b,this->random,random_arraysize);
    b->pack(sctpChunkTypes_arraysize);
    doParsimArrayPacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
    b->pack(sepChunks_arraysize);
    doParsimArrayPacking(b,this->sepChunks,sepChunks_arraysize);
    b->pack(hmacTypes_arraysize);
    doParsimArrayPacking(b,this->hmacTypes,hmacTypes_arraysize);
}

void SctpInitAckChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->initTag);
    doParsimUnpacking(b,this->a_rwnd);
    doParsimUnpacking(b,this->noOutStreams);
    doParsimUnpacking(b,this->noInStreams);
    doParsimUnpacking(b,this->initTsn);
    doParsimUnpacking(b,this->forwardTsn);
    doParsimUnpacking(b,this->ipv4Supported);
    doParsimUnpacking(b,this->ipv6Supported);
    delete [] this->addresses;
    b->unpack(addresses_arraysize);
    if (addresses_arraysize == 0) {
        this->addresses = nullptr;
    } else {
        this->addresses = new ::inet::L3Address[addresses_arraysize];
        doParsimArrayUnpacking(b,this->addresses,addresses_arraysize);
    }
    delete [] this->cookie;
    b->unpack(cookie_arraysize);
    if (cookie_arraysize == 0) {
        this->cookie = nullptr;
    } else {
        this->cookie = new char[cookie_arraysize];
        doParsimArrayUnpacking(b,this->cookie,cookie_arraysize);
    }
    delete [] this->unrecognizedParameters;
    b->unpack(unrecognizedParameters_arraysize);
    if (unrecognizedParameters_arraysize == 0) {
        this->unrecognizedParameters = nullptr;
    } else {
        this->unrecognizedParameters = new uint8_t[unrecognizedParameters_arraysize];
        doParsimArrayUnpacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
    }
    doParsimUnpacking(b,this->stateCookie);
    doParsimUnpacking(b,this->msg_rwnd);
    delete [] this->random;
    b->unpack(random_arraysize);
    if (random_arraysize == 0) {
        this->random = nullptr;
    } else {
        this->random = new uint8_t[random_arraysize];
        doParsimArrayUnpacking(b,this->random,random_arraysize);
    }
    delete [] this->sctpChunkTypes;
    b->unpack(sctpChunkTypes_arraysize);
    if (sctpChunkTypes_arraysize == 0) {
        this->sctpChunkTypes = nullptr;
    } else {
        this->sctpChunkTypes = new uint16_t[sctpChunkTypes_arraysize];
        doParsimArrayUnpacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
    }
    delete [] this->sepChunks;
    b->unpack(sepChunks_arraysize);
    if (sepChunks_arraysize == 0) {
        this->sepChunks = nullptr;
    } else {
        this->sepChunks = new uint16_t[sepChunks_arraysize];
        doParsimArrayUnpacking(b,this->sepChunks,sepChunks_arraysize);
    }
    delete [] this->hmacTypes;
    b->unpack(hmacTypes_arraysize);
    if (hmacTypes_arraysize == 0) {
        this->hmacTypes = nullptr;
    } else {
        this->hmacTypes = new uint16_t[hmacTypes_arraysize];
        doParsimArrayUnpacking(b,this->hmacTypes,hmacTypes_arraysize);
    }
}

uint32_t SctpInitAckChunk::getInitTag() const
{
    return this->initTag;
}

void SctpInitAckChunk::setInitTag(uint32_t initTag)
{
    this->initTag = initTag;
}

uint32_t SctpInitAckChunk::getA_rwnd() const
{
    return this->a_rwnd;
}

void SctpInitAckChunk::setA_rwnd(uint32_t a_rwnd)
{
    this->a_rwnd = a_rwnd;
}

uint16_t SctpInitAckChunk::getNoOutStreams() const
{
    return this->noOutStreams;
}

void SctpInitAckChunk::setNoOutStreams(uint16_t noOutStreams)
{
    this->noOutStreams = noOutStreams;
}

uint16_t SctpInitAckChunk::getNoInStreams() const
{
    return this->noInStreams;
}

void SctpInitAckChunk::setNoInStreams(uint16_t noInStreams)
{
    this->noInStreams = noInStreams;
}

uint32_t SctpInitAckChunk::getInitTsn() const
{
    return this->initTsn;
}

void SctpInitAckChunk::setInitTsn(uint32_t initTsn)
{
    this->initTsn = initTsn;
}

bool SctpInitAckChunk::getForwardTsn() const
{
    return this->forwardTsn;
}

void SctpInitAckChunk::setForwardTsn(bool forwardTsn)
{
    this->forwardTsn = forwardTsn;
}

bool SctpInitAckChunk::getIpv4Supported() const
{
    return this->ipv4Supported;
}

void SctpInitAckChunk::setIpv4Supported(bool ipv4Supported)
{
    this->ipv4Supported = ipv4Supported;
}

bool SctpInitAckChunk::getIpv6Supported() const
{
    return this->ipv6Supported;
}

void SctpInitAckChunk::setIpv6Supported(bool ipv6Supported)
{
    this->ipv6Supported = ipv6Supported;
}

size_t SctpInitAckChunk::getAddressesArraySize() const
{
    return addresses_arraysize;
}

const ::inet::L3Address& SctpInitAckChunk::getAddresses(size_t k) const
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    return this->addresses[k];
}

void SctpInitAckChunk::setAddressesArraySize(size_t newSize)
{
    ::inet::L3Address *addresses2 = (newSize==0) ? nullptr : new ::inet::L3Address[newSize];
    size_t minSize = addresses_arraysize < newSize ? addresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        addresses2[i] = this->addresses[i];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void SctpInitAckChunk::setAddresses(size_t k, const ::inet::L3Address& addresses)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    this->addresses[k] = addresses;
}

void SctpInitAckChunk::insertAddresses(size_t k, const ::inet::L3Address& addresses)
{
    if (k > addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    size_t newSize = addresses_arraysize + 1;
    ::inet::L3Address *addresses2 = new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    addresses2[k] = addresses;
    for (i = k + 1; i < newSize; i++)
        addresses2[i] = this->addresses[i-1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

void SctpInitAckChunk::appendAddresses(const ::inet::L3Address& addresses)
{
    insertAddresses(addresses_arraysize, addresses);
}

void SctpInitAckChunk::eraseAddresses(size_t k)
{
    if (k >= addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)addresses_arraysize, (unsigned long)k);
    size_t newSize = addresses_arraysize - 1;
    ::inet::L3Address *addresses2 = (newSize == 0) ? nullptr : new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        addresses2[i] = this->addresses[i];
    for (i = k; i < newSize; i++)
        addresses2[i] = this->addresses[i+1];
    delete [] this->addresses;
    this->addresses = addresses2;
    addresses_arraysize = newSize;
}

size_t SctpInitAckChunk::getCookieArraySize() const
{
    return cookie_arraysize;
}

char SctpInitAckChunk::getCookie(size_t k) const
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    return this->cookie[k];
}

void SctpInitAckChunk::setCookieArraySize(size_t newSize)
{
    char *cookie2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = cookie_arraysize < newSize ? cookie_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        cookie2[i] = this->cookie[i];
    for (size_t i = minSize; i < newSize; i++)
        cookie2[i] = 0;
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

void SctpInitAckChunk::setCookie(size_t k, char cookie)
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    this->cookie[k] = cookie;
}

void SctpInitAckChunk::insertCookie(size_t k, char cookie)
{
    if (k > cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    size_t newSize = cookie_arraysize + 1;
    char *cookie2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        cookie2[i] = this->cookie[i];
    cookie2[k] = cookie;
    for (i = k + 1; i < newSize; i++)
        cookie2[i] = this->cookie[i-1];
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

void SctpInitAckChunk::appendCookie(char cookie)
{
    insertCookie(cookie_arraysize, cookie);
}

void SctpInitAckChunk::eraseCookie(size_t k)
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    size_t newSize = cookie_arraysize - 1;
    char *cookie2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        cookie2[i] = this->cookie[i];
    for (i = k; i < newSize; i++)
        cookie2[i] = this->cookie[i+1];
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

size_t SctpInitAckChunk::getUnrecognizedParametersArraySize() const
{
    return unrecognizedParameters_arraysize;
}

uint8_t SctpInitAckChunk::getUnrecognizedParameters(size_t k) const
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    return this->unrecognizedParameters[k];
}

void SctpInitAckChunk::setUnrecognizedParametersArraySize(size_t newSize)
{
    uint8_t *unrecognizedParameters2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = unrecognizedParameters_arraysize < newSize ? unrecognizedParameters_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (size_t i = minSize; i < newSize; i++)
        unrecognizedParameters2[i] = 0;
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpInitAckChunk::setUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    this->unrecognizedParameters[k] = unrecognizedParameters;
}

void SctpInitAckChunk::insertUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k > unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize + 1;
    uint8_t *unrecognizedParameters2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    unrecognizedParameters2[k] = unrecognizedParameters;
    for (i = k + 1; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i-1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpInitAckChunk::appendUnrecognizedParameters(uint8_t unrecognizedParameters)
{
    insertUnrecognizedParameters(unrecognizedParameters_arraysize, unrecognizedParameters);
}

void SctpInitAckChunk::eraseUnrecognizedParameters(size_t k)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize - 1;
    uint8_t *unrecognizedParameters2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (i = k; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i+1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

const SctpCookie * SctpInitAckChunk::getStateCookie() const
{
    return this->stateCookie;
}

void SctpInitAckChunk::setStateCookie(SctpCookie * stateCookie)
{
    this->stateCookie = stateCookie;
}

uint32_t SctpInitAckChunk::getMsg_rwnd() const
{
    return this->msg_rwnd;
}

void SctpInitAckChunk::setMsg_rwnd(uint32_t msg_rwnd)
{
    this->msg_rwnd = msg_rwnd;
}

size_t SctpInitAckChunk::getRandomArraySize() const
{
    return random_arraysize;
}

uint8_t SctpInitAckChunk::getRandom(size_t k) const
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    return this->random[k];
}

void SctpInitAckChunk::setRandomArraySize(size_t newSize)
{
    uint8_t *random2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = random_arraysize < newSize ? random_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        random2[i] = this->random[i];
    for (size_t i = minSize; i < newSize; i++)
        random2[i] = 0;
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

void SctpInitAckChunk::setRandom(size_t k, uint8_t random)
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    this->random[k] = random;
}

void SctpInitAckChunk::insertRandom(size_t k, uint8_t random)
{
    if (k > random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    size_t newSize = random_arraysize + 1;
    uint8_t *random2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        random2[i] = this->random[i];
    random2[k] = random;
    for (i = k + 1; i < newSize; i++)
        random2[i] = this->random[i-1];
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

void SctpInitAckChunk::appendRandom(uint8_t random)
{
    insertRandom(random_arraysize, random);
}

void SctpInitAckChunk::eraseRandom(size_t k)
{
    if (k >= random_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)random_arraysize, (unsigned long)k);
    size_t newSize = random_arraysize - 1;
    uint8_t *random2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        random2[i] = this->random[i];
    for (i = k; i < newSize; i++)
        random2[i] = this->random[i+1];
    delete [] this->random;
    this->random = random2;
    random_arraysize = newSize;
}

size_t SctpInitAckChunk::getSctpChunkTypesArraySize() const
{
    return sctpChunkTypes_arraysize;
}

uint16_t SctpInitAckChunk::getSctpChunkTypes(size_t k) const
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    return this->sctpChunkTypes[k];
}

void SctpInitAckChunk::setSctpChunkTypesArraySize(size_t newSize)
{
    uint16_t *sctpChunkTypes2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sctpChunkTypes_arraysize < newSize ? sctpChunkTypes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (size_t i = minSize; i < newSize; i++)
        sctpChunkTypes2[i] = 0;
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpInitAckChunk::setSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    this->sctpChunkTypes[k] = sctpChunkTypes;
}

void SctpInitAckChunk::insertSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k > sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize + 1;
    uint16_t *sctpChunkTypes2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    sctpChunkTypes2[k] = sctpChunkTypes;
    for (i = k + 1; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i-1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpInitAckChunk::appendSctpChunkTypes(uint16_t sctpChunkTypes)
{
    insertSctpChunkTypes(sctpChunkTypes_arraysize, sctpChunkTypes);
}

void SctpInitAckChunk::eraseSctpChunkTypes(size_t k)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize - 1;
    uint16_t *sctpChunkTypes2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (i = k; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i+1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

size_t SctpInitAckChunk::getSepChunksArraySize() const
{
    return sepChunks_arraysize;
}

uint16_t SctpInitAckChunk::getSepChunks(size_t k) const
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    return this->sepChunks[k];
}

void SctpInitAckChunk::setSepChunksArraySize(size_t newSize)
{
    uint16_t *sepChunks2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sepChunks_arraysize < newSize ? sepChunks_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sepChunks2[i] = this->sepChunks[i];
    for (size_t i = minSize; i < newSize; i++)
        sepChunks2[i] = 0;
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

void SctpInitAckChunk::setSepChunks(size_t k, uint16_t sepChunks)
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    this->sepChunks[k] = sepChunks;
}

void SctpInitAckChunk::insertSepChunks(size_t k, uint16_t sepChunks)
{
    if (k > sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    size_t newSize = sepChunks_arraysize + 1;
    uint16_t *sepChunks2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sepChunks2[i] = this->sepChunks[i];
    sepChunks2[k] = sepChunks;
    for (i = k + 1; i < newSize; i++)
        sepChunks2[i] = this->sepChunks[i-1];
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

void SctpInitAckChunk::appendSepChunks(uint16_t sepChunks)
{
    insertSepChunks(sepChunks_arraysize, sepChunks);
}

void SctpInitAckChunk::eraseSepChunks(size_t k)
{
    if (k >= sepChunks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sepChunks_arraysize, (unsigned long)k);
    size_t newSize = sepChunks_arraysize - 1;
    uint16_t *sepChunks2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sepChunks2[i] = this->sepChunks[i];
    for (i = k; i < newSize; i++)
        sepChunks2[i] = this->sepChunks[i+1];
    delete [] this->sepChunks;
    this->sepChunks = sepChunks2;
    sepChunks_arraysize = newSize;
}

size_t SctpInitAckChunk::getHmacTypesArraySize() const
{
    return hmacTypes_arraysize;
}

uint16_t SctpInitAckChunk::getHmacTypes(size_t k) const
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    return this->hmacTypes[k];
}

void SctpInitAckChunk::setHmacTypesArraySize(size_t newSize)
{
    uint16_t *hmacTypes2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = hmacTypes_arraysize < newSize ? hmacTypes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    for (size_t i = minSize; i < newSize; i++)
        hmacTypes2[i] = 0;
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

void SctpInitAckChunk::setHmacTypes(size_t k, uint16_t hmacTypes)
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    this->hmacTypes[k] = hmacTypes;
}

void SctpInitAckChunk::insertHmacTypes(size_t k, uint16_t hmacTypes)
{
    if (k > hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    size_t newSize = hmacTypes_arraysize + 1;
    uint16_t *hmacTypes2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    hmacTypes2[k] = hmacTypes;
    for (i = k + 1; i < newSize; i++)
        hmacTypes2[i] = this->hmacTypes[i-1];
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

void SctpInitAckChunk::appendHmacTypes(uint16_t hmacTypes)
{
    insertHmacTypes(hmacTypes_arraysize, hmacTypes);
}

void SctpInitAckChunk::eraseHmacTypes(size_t k)
{
    if (k >= hmacTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hmacTypes_arraysize, (unsigned long)k);
    size_t newSize = hmacTypes_arraysize - 1;
    uint16_t *hmacTypes2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hmacTypes2[i] = this->hmacTypes[i];
    for (i = k; i < newSize; i++)
        hmacTypes2[i] = this->hmacTypes[i+1];
    delete [] this->hmacTypes;
    this->hmacTypes = hmacTypes2;
    hmacTypes_arraysize = newSize;
}

class SctpInitAckChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_initTag,
        FIELD_a_rwnd,
        FIELD_noOutStreams,
        FIELD_noInStreams,
        FIELD_initTsn,
        FIELD_forwardTsn,
        FIELD_ipv4Supported,
        FIELD_ipv6Supported,
        FIELD_addresses,
        FIELD_cookie,
        FIELD_unrecognizedParameters,
        FIELD_stateCookie,
        FIELD_msg_rwnd,
        FIELD_random,
        FIELD_sctpChunkTypes,
        FIELD_sepChunks,
        FIELD_hmacTypes,
    };
  public:
    SctpInitAckChunkDescriptor();
    virtual ~SctpInitAckChunkDescriptor();

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

Register_ClassDescriptor(SctpInitAckChunkDescriptor)

SctpInitAckChunkDescriptor::SctpInitAckChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpInitAckChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpInitAckChunkDescriptor::~SctpInitAckChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpInitAckChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpInitAckChunk *>(obj)!=nullptr;
}

const char **SctpInitAckChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpInitAckChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpInitAckChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 17+base->getFieldCount() : 17;
}

unsigned int SctpInitAckChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_initTag
        FD_ISEDITABLE,    // FIELD_a_rwnd
        FD_ISEDITABLE,    // FIELD_noOutStreams
        FD_ISEDITABLE,    // FIELD_noInStreams
        FD_ISEDITABLE,    // FIELD_initTsn
        FD_ISEDITABLE,    // FIELD_forwardTsn
        FD_ISEDITABLE,    // FIELD_ipv4Supported
        FD_ISEDITABLE,    // FIELD_ipv6Supported
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_addresses
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_cookie
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_unrecognizedParameters
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE,    // FIELD_stateCookie
        FD_ISEDITABLE,    // FIELD_msg_rwnd
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_random
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sctpChunkTypes
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sepChunks
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_hmacTypes
    };
    return (field >= 0 && field < 17) ? fieldTypeFlags[field] : 0;
}

const char *SctpInitAckChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "initTag",
        "a_rwnd",
        "noOutStreams",
        "noInStreams",
        "initTsn",
        "forwardTsn",
        "ipv4Supported",
        "ipv6Supported",
        "addresses",
        "cookie",
        "unrecognizedParameters",
        "stateCookie",
        "msg_rwnd",
        "random",
        "sctpChunkTypes",
        "sepChunks",
        "hmacTypes",
    };
    return (field >= 0 && field < 17) ? fieldNames[field] : nullptr;
}

int SctpInitAckChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "initTag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "a_rwnd") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "noOutStreams") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "noInStreams") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "initTsn") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "forwardTsn") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "ipv4Supported") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ipv6Supported") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "addresses") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "cookie") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "unrecognizedParameters") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "stateCookie") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "msg_rwnd") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "random") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "sctpChunkTypes") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "sepChunks") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "hmacTypes") == 0) return baseIndex + 16;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpInitAckChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_initTag
        "uint32_t",    // FIELD_a_rwnd
        "uint16_t",    // FIELD_noOutStreams
        "uint16_t",    // FIELD_noInStreams
        "uint32_t",    // FIELD_initTsn
        "bool",    // FIELD_forwardTsn
        "bool",    // FIELD_ipv4Supported
        "bool",    // FIELD_ipv6Supported
        "inet::L3Address",    // FIELD_addresses
        "char",    // FIELD_cookie
        "uint8_t",    // FIELD_unrecognizedParameters
        "inet::sctp::SctpCookie",    // FIELD_stateCookie
        "uint32_t",    // FIELD_msg_rwnd
        "uint8_t",    // FIELD_random
        "uint16_t",    // FIELD_sctpChunkTypes
        "uint16_t",    // FIELD_sepChunks
        "uint16_t",    // FIELD_hmacTypes
    };
    return (field >= 0 && field < 17) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpInitAckChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpInitAckChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpInitAckChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: return pp->getAddressesArraySize();
        case FIELD_cookie: return pp->getCookieArraySize();
        case FIELD_unrecognizedParameters: return pp->getUnrecognizedParametersArraySize();
        case FIELD_random: return pp->getRandomArraySize();
        case FIELD_sctpChunkTypes: return pp->getSctpChunkTypesArraySize();
        case FIELD_sepChunks: return pp->getSepChunksArraySize();
        case FIELD_hmacTypes: return pp->getHmacTypesArraySize();
        default: return 0;
    }
}

void SctpInitAckChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: pp->setAddressesArraySize(size); break;
        case FIELD_cookie: pp->setCookieArraySize(size); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParametersArraySize(size); break;
        case FIELD_random: pp->setRandomArraySize(size); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypesArraySize(size); break;
        case FIELD_sepChunks: pp->setSepChunksArraySize(size); break;
        case FIELD_hmacTypes: pp->setHmacTypesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpInitAckChunk'", field);
    }
}

const char *SctpInitAckChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_stateCookie: { const SctpCookie * value = pp->getStateCookie(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpInitAckChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: return ulong2string(pp->getInitTag());
        case FIELD_a_rwnd: return ulong2string(pp->getA_rwnd());
        case FIELD_noOutStreams: return ulong2string(pp->getNoOutStreams());
        case FIELD_noInStreams: return ulong2string(pp->getNoInStreams());
        case FIELD_initTsn: return ulong2string(pp->getInitTsn());
        case FIELD_forwardTsn: return bool2string(pp->getForwardTsn());
        case FIELD_ipv4Supported: return bool2string(pp->getIpv4Supported());
        case FIELD_ipv6Supported: return bool2string(pp->getIpv6Supported());
        case FIELD_addresses: return pp->getAddresses(i).str();
        case FIELD_cookie: return long2string(pp->getCookie(i));
        case FIELD_unrecognizedParameters: return ulong2string(pp->getUnrecognizedParameters(i));
        case FIELD_stateCookie: { auto obj = pp->getStateCookie(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_msg_rwnd: return ulong2string(pp->getMsg_rwnd());
        case FIELD_random: return ulong2string(pp->getRandom(i));
        case FIELD_sctpChunkTypes: return ulong2string(pp->getSctpChunkTypes(i));
        case FIELD_sepChunks: return ulong2string(pp->getSepChunks(i));
        case FIELD_hmacTypes: return ulong2string(pp->getHmacTypes(i));
        default: return "";
    }
}

void SctpInitAckChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: pp->setInitTag(string2ulong(value)); break;
        case FIELD_a_rwnd: pp->setA_rwnd(string2ulong(value)); break;
        case FIELD_noOutStreams: pp->setNoOutStreams(string2ulong(value)); break;
        case FIELD_noInStreams: pp->setNoInStreams(string2ulong(value)); break;
        case FIELD_initTsn: pp->setInitTsn(string2ulong(value)); break;
        case FIELD_forwardTsn: pp->setForwardTsn(string2bool(value)); break;
        case FIELD_ipv4Supported: pp->setIpv4Supported(string2bool(value)); break;
        case FIELD_ipv6Supported: pp->setIpv6Supported(string2bool(value)); break;
        case FIELD_cookie: pp->setCookie(i,string2long(value)); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,string2ulong(value)); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(string2ulong(value)); break;
        case FIELD_random: pp->setRandom(i,string2ulong(value)); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,string2ulong(value)); break;
        case FIELD_sepChunks: pp->setSepChunks(i,string2ulong(value)); break;
        case FIELD_hmacTypes: pp->setHmacTypes(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitAckChunk'", field);
    }
}

omnetpp::cValue SctpInitAckChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: return (omnetpp::intval_t)(pp->getInitTag());
        case FIELD_a_rwnd: return (omnetpp::intval_t)(pp->getA_rwnd());
        case FIELD_noOutStreams: return (omnetpp::intval_t)(pp->getNoOutStreams());
        case FIELD_noInStreams: return (omnetpp::intval_t)(pp->getNoInStreams());
        case FIELD_initTsn: return (omnetpp::intval_t)(pp->getInitTsn());
        case FIELD_forwardTsn: return pp->getForwardTsn();
        case FIELD_ipv4Supported: return pp->getIpv4Supported();
        case FIELD_ipv6Supported: return pp->getIpv6Supported();
        case FIELD_addresses: return omnetpp::toAnyPtr(&pp->getAddresses(i)); break;
        case FIELD_cookie: return pp->getCookie(i);
        case FIELD_unrecognizedParameters: return (omnetpp::intval_t)(pp->getUnrecognizedParameters(i));
        case FIELD_stateCookie: return omnetpp::toAnyPtr(pp->getStateCookie()); break;
        case FIELD_msg_rwnd: return (omnetpp::intval_t)(pp->getMsg_rwnd());
        case FIELD_random: return (omnetpp::intval_t)(pp->getRandom(i));
        case FIELD_sctpChunkTypes: return (omnetpp::intval_t)(pp->getSctpChunkTypes(i));
        case FIELD_sepChunks: return (omnetpp::intval_t)(pp->getSepChunks(i));
        case FIELD_hmacTypes: return (omnetpp::intval_t)(pp->getHmacTypes(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpInitAckChunk' as cValue -- field index out of range?", field);
    }
}

void SctpInitAckChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_initTag: pp->setInitTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_a_rwnd: pp->setA_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_noOutStreams: pp->setNoOutStreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_noInStreams: pp->setNoInStreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_initTsn: pp->setInitTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_forwardTsn: pp->setForwardTsn(value.boolValue()); break;
        case FIELD_ipv4Supported: pp->setIpv4Supported(value.boolValue()); break;
        case FIELD_ipv6Supported: pp->setIpv6Supported(value.boolValue()); break;
        case FIELD_cookie: pp->setCookie(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_stateCookie: pp->setStateCookie(omnetpp::fromAnyPtr<SctpCookie>(value.pointerValue())); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_random: pp->setRandom(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_sepChunks: pp->setSepChunks(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_hmacTypes: pp->setHmacTypes(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitAckChunk'", field);
    }
}

const char *SctpInitAckChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_stateCookie: return omnetpp::opp_typename(typeid(SctpCookie));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpInitAckChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_addresses: return omnetpp::toAnyPtr(&pp->getAddresses(i)); break;
        case FIELD_stateCookie: return omnetpp::toAnyPtr(pp->getStateCookie()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpInitAckChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpInitAckChunk *pp = omnetpp::fromAnyPtr<SctpInitAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_stateCookie: pp->setStateCookie(omnetpp::fromAnyPtr<SctpCookie>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpInitAckChunk'", field);
    }
}

Register_Class(SctpCookieEchoChunk)

SctpCookieEchoChunk::SctpCookieEchoChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpCookieEchoChunk::SctpCookieEchoChunk(const SctpCookieEchoChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpCookieEchoChunk::~SctpCookieEchoChunk()
{
    delete [] this->cookie;
    delete [] this->unrecognizedParameters;
}

SctpCookieEchoChunk& SctpCookieEchoChunk::operator=(const SctpCookieEchoChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpCookieEchoChunk::copy(const SctpCookieEchoChunk& other)
{
    delete [] this->cookie;
    this->cookie = (other.cookie_arraysize==0) ? nullptr : new char[other.cookie_arraysize];
    cookie_arraysize = other.cookie_arraysize;
    for (size_t i = 0; i < cookie_arraysize; i++) {
        this->cookie[i] = other.cookie[i];
    }
    this->stateCookie = other.stateCookie;
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = (other.unrecognizedParameters_arraysize==0) ? nullptr : new uint8_t[other.unrecognizedParameters_arraysize];
    unrecognizedParameters_arraysize = other.unrecognizedParameters_arraysize;
    for (size_t i = 0; i < unrecognizedParameters_arraysize; i++) {
        this->unrecognizedParameters[i] = other.unrecognizedParameters[i];
    }
}

void SctpCookieEchoChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    b->pack(cookie_arraysize);
    doParsimArrayPacking(b,this->cookie,cookie_arraysize);
    doParsimPacking(b,this->stateCookie);
    b->pack(unrecognizedParameters_arraysize);
    doParsimArrayPacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
}

void SctpCookieEchoChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    delete [] this->cookie;
    b->unpack(cookie_arraysize);
    if (cookie_arraysize == 0) {
        this->cookie = nullptr;
    } else {
        this->cookie = new char[cookie_arraysize];
        doParsimArrayUnpacking(b,this->cookie,cookie_arraysize);
    }
    doParsimUnpacking(b,this->stateCookie);
    delete [] this->unrecognizedParameters;
    b->unpack(unrecognizedParameters_arraysize);
    if (unrecognizedParameters_arraysize == 0) {
        this->unrecognizedParameters = nullptr;
    } else {
        this->unrecognizedParameters = new uint8_t[unrecognizedParameters_arraysize];
        doParsimArrayUnpacking(b,this->unrecognizedParameters,unrecognizedParameters_arraysize);
    }
}

size_t SctpCookieEchoChunk::getCookieArraySize() const
{
    return cookie_arraysize;
}

char SctpCookieEchoChunk::getCookie(size_t k) const
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    return this->cookie[k];
}

void SctpCookieEchoChunk::setCookieArraySize(size_t newSize)
{
    char *cookie2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = cookie_arraysize < newSize ? cookie_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        cookie2[i] = this->cookie[i];
    for (size_t i = minSize; i < newSize; i++)
        cookie2[i] = 0;
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

void SctpCookieEchoChunk::setCookie(size_t k, char cookie)
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    this->cookie[k] = cookie;
}

void SctpCookieEchoChunk::insertCookie(size_t k, char cookie)
{
    if (k > cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    size_t newSize = cookie_arraysize + 1;
    char *cookie2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        cookie2[i] = this->cookie[i];
    cookie2[k] = cookie;
    for (i = k + 1; i < newSize; i++)
        cookie2[i] = this->cookie[i-1];
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

void SctpCookieEchoChunk::appendCookie(char cookie)
{
    insertCookie(cookie_arraysize, cookie);
}

void SctpCookieEchoChunk::eraseCookie(size_t k)
{
    if (k >= cookie_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)cookie_arraysize, (unsigned long)k);
    size_t newSize = cookie_arraysize - 1;
    char *cookie2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        cookie2[i] = this->cookie[i];
    for (i = k; i < newSize; i++)
        cookie2[i] = this->cookie[i+1];
    delete [] this->cookie;
    this->cookie = cookie2;
    cookie_arraysize = newSize;
}

const SctpCookie * SctpCookieEchoChunk::getStateCookie() const
{
    return this->stateCookie;
}

void SctpCookieEchoChunk::setStateCookie(SctpCookie * stateCookie)
{
    this->stateCookie = stateCookie;
}

size_t SctpCookieEchoChunk::getUnrecognizedParametersArraySize() const
{
    return unrecognizedParameters_arraysize;
}

uint8_t SctpCookieEchoChunk::getUnrecognizedParameters(size_t k) const
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    return this->unrecognizedParameters[k];
}

void SctpCookieEchoChunk::setUnrecognizedParametersArraySize(size_t newSize)
{
    uint8_t *unrecognizedParameters2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = unrecognizedParameters_arraysize < newSize ? unrecognizedParameters_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (size_t i = minSize; i < newSize; i++)
        unrecognizedParameters2[i] = 0;
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpCookieEchoChunk::setUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    this->unrecognizedParameters[k] = unrecognizedParameters;
}

void SctpCookieEchoChunk::insertUnrecognizedParameters(size_t k, uint8_t unrecognizedParameters)
{
    if (k > unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize + 1;
    uint8_t *unrecognizedParameters2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    unrecognizedParameters2[k] = unrecognizedParameters;
    for (i = k + 1; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i-1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

void SctpCookieEchoChunk::appendUnrecognizedParameters(uint8_t unrecognizedParameters)
{
    insertUnrecognizedParameters(unrecognizedParameters_arraysize, unrecognizedParameters);
}

void SctpCookieEchoChunk::eraseUnrecognizedParameters(size_t k)
{
    if (k >= unrecognizedParameters_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)unrecognizedParameters_arraysize, (unsigned long)k);
    size_t newSize = unrecognizedParameters_arraysize - 1;
    uint8_t *unrecognizedParameters2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i];
    for (i = k; i < newSize; i++)
        unrecognizedParameters2[i] = this->unrecognizedParameters[i+1];
    delete [] this->unrecognizedParameters;
    this->unrecognizedParameters = unrecognizedParameters2;
    unrecognizedParameters_arraysize = newSize;
}

class SctpCookieEchoChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cookie,
        FIELD_stateCookie,
        FIELD_unrecognizedParameters,
    };
  public:
    SctpCookieEchoChunkDescriptor();
    virtual ~SctpCookieEchoChunkDescriptor();

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

Register_ClassDescriptor(SctpCookieEchoChunkDescriptor)

SctpCookieEchoChunkDescriptor::SctpCookieEchoChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpCookieEchoChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpCookieEchoChunkDescriptor::~SctpCookieEchoChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpCookieEchoChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpCookieEchoChunk *>(obj)!=nullptr;
}

const char **SctpCookieEchoChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpCookieEchoChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpCookieEchoChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpCookieEchoChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_cookie
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE,    // FIELD_stateCookie
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_unrecognizedParameters
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpCookieEchoChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cookie",
        "stateCookie",
        "unrecognizedParameters",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpCookieEchoChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cookie") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "stateCookie") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "unrecognizedParameters") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpCookieEchoChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "char",    // FIELD_cookie
        "inet::sctp::SctpCookie",    // FIELD_stateCookie
        "uint8_t",    // FIELD_unrecognizedParameters
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpCookieEchoChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpCookieEchoChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpCookieEchoChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: return pp->getCookieArraySize();
        case FIELD_unrecognizedParameters: return pp->getUnrecognizedParametersArraySize();
        default: return 0;
    }
}

void SctpCookieEchoChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: pp->setCookieArraySize(size); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParametersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpCookieEchoChunk'", field);
    }
}

const char *SctpCookieEchoChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_stateCookie: { const SctpCookie * value = pp->getStateCookie(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpCookieEchoChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: return long2string(pp->getCookie(i));
        case FIELD_stateCookie: { auto obj = pp->getStateCookie(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_unrecognizedParameters: return ulong2string(pp->getUnrecognizedParameters(i));
        default: return "";
    }
}

void SctpCookieEchoChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: pp->setCookie(i,string2long(value)); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieEchoChunk'", field);
    }
}

omnetpp::cValue SctpCookieEchoChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: return pp->getCookie(i);
        case FIELD_stateCookie: return omnetpp::toAnyPtr(pp->getStateCookie()); break;
        case FIELD_unrecognizedParameters: return (omnetpp::intval_t)(pp->getUnrecognizedParameters(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpCookieEchoChunk' as cValue -- field index out of range?", field);
    }
}

void SctpCookieEchoChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cookie: pp->setCookie(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        case FIELD_stateCookie: pp->setStateCookie(omnetpp::fromAnyPtr<SctpCookie>(value.pointerValue())); break;
        case FIELD_unrecognizedParameters: pp->setUnrecognizedParameters(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieEchoChunk'", field);
    }
}

const char *SctpCookieEchoChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_stateCookie: return omnetpp::opp_typename(typeid(SctpCookie));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpCookieEchoChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_stateCookie: return omnetpp::toAnyPtr(pp->getStateCookie()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpCookieEchoChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieEchoChunk *pp = omnetpp::fromAnyPtr<SctpCookieEchoChunk>(object); (void)pp;
    switch (field) {
        case FIELD_stateCookie: pp->setStateCookie(omnetpp::fromAnyPtr<SctpCookie>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieEchoChunk'", field);
    }
}

Register_Class(SctpCookie)

SctpCookie::SctpCookie(const char *name) : ::omnetpp::cNamedObject(name)
{
}

SctpCookie::SctpCookie(const SctpCookie& other) : ::omnetpp::cNamedObject(other)
{
    copy(other);
}

SctpCookie::~SctpCookie()
{
    delete [] this->localTieTag;
    delete [] this->peerTieTag;
}

SctpCookie& SctpCookie::operator=(const SctpCookie& other)
{
    if (this == &other) return *this;
    ::omnetpp::cNamedObject::operator=(other);
    copy(other);
    return *this;
}

void SctpCookie::copy(const SctpCookie& other)
{
    this->creationTime = other.creationTime;
    this->localTag = other.localTag;
    this->peerTag = other.peerTag;
    delete [] this->localTieTag;
    this->localTieTag = (other.localTieTag_arraysize==0) ? nullptr : new uint8_t[other.localTieTag_arraysize];
    localTieTag_arraysize = other.localTieTag_arraysize;
    for (size_t i = 0; i < localTieTag_arraysize; i++) {
        this->localTieTag[i] = other.localTieTag[i];
    }
    delete [] this->peerTieTag;
    this->peerTieTag = (other.peerTieTag_arraysize==0) ? nullptr : new uint8_t[other.peerTieTag_arraysize];
    peerTieTag_arraysize = other.peerTieTag_arraysize;
    for (size_t i = 0; i < peerTieTag_arraysize; i++) {
        this->peerTieTag[i] = other.peerTieTag[i];
    }
    this->length = other.length;
}

void SctpCookie::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cNamedObject::parsimPack(b);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->localTag);
    doParsimPacking(b,this->peerTag);
    b->pack(localTieTag_arraysize);
    doParsimArrayPacking(b,this->localTieTag,localTieTag_arraysize);
    b->pack(peerTieTag_arraysize);
    doParsimArrayPacking(b,this->peerTieTag,peerTieTag_arraysize);
    doParsimPacking(b,this->length);
}

void SctpCookie::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cNamedObject::parsimUnpack(b);
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->localTag);
    doParsimUnpacking(b,this->peerTag);
    delete [] this->localTieTag;
    b->unpack(localTieTag_arraysize);
    if (localTieTag_arraysize == 0) {
        this->localTieTag = nullptr;
    } else {
        this->localTieTag = new uint8_t[localTieTag_arraysize];
        doParsimArrayUnpacking(b,this->localTieTag,localTieTag_arraysize);
    }
    delete [] this->peerTieTag;
    b->unpack(peerTieTag_arraysize);
    if (peerTieTag_arraysize == 0) {
        this->peerTieTag = nullptr;
    } else {
        this->peerTieTag = new uint8_t[peerTieTag_arraysize];
        doParsimArrayUnpacking(b,this->peerTieTag,peerTieTag_arraysize);
    }
    doParsimUnpacking(b,this->length);
}

::omnetpp::simtime_t SctpCookie::getCreationTime() const
{
    return this->creationTime;
}

void SctpCookie::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

uint32_t SctpCookie::getLocalTag() const
{
    return this->localTag;
}

void SctpCookie::setLocalTag(uint32_t localTag)
{
    this->localTag = localTag;
}

uint32_t SctpCookie::getPeerTag() const
{
    return this->peerTag;
}

void SctpCookie::setPeerTag(uint32_t peerTag)
{
    this->peerTag = peerTag;
}

size_t SctpCookie::getLocalTieTagArraySize() const
{
    return localTieTag_arraysize;
}

uint8_t SctpCookie::getLocalTieTag(size_t k) const
{
    if (k >= localTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)localTieTag_arraysize, (unsigned long)k);
    return this->localTieTag[k];
}

void SctpCookie::setLocalTieTagArraySize(size_t newSize)
{
    uint8_t *localTieTag2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = localTieTag_arraysize < newSize ? localTieTag_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        localTieTag2[i] = this->localTieTag[i];
    for (size_t i = minSize; i < newSize; i++)
        localTieTag2[i] = 0;
    delete [] this->localTieTag;
    this->localTieTag = localTieTag2;
    localTieTag_arraysize = newSize;
}

void SctpCookie::setLocalTieTag(size_t k, uint8_t localTieTag)
{
    if (k >= localTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)localTieTag_arraysize, (unsigned long)k);
    this->localTieTag[k] = localTieTag;
}

void SctpCookie::insertLocalTieTag(size_t k, uint8_t localTieTag)
{
    if (k > localTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)localTieTag_arraysize, (unsigned long)k);
    size_t newSize = localTieTag_arraysize + 1;
    uint8_t *localTieTag2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        localTieTag2[i] = this->localTieTag[i];
    localTieTag2[k] = localTieTag;
    for (i = k + 1; i < newSize; i++)
        localTieTag2[i] = this->localTieTag[i-1];
    delete [] this->localTieTag;
    this->localTieTag = localTieTag2;
    localTieTag_arraysize = newSize;
}

void SctpCookie::appendLocalTieTag(uint8_t localTieTag)
{
    insertLocalTieTag(localTieTag_arraysize, localTieTag);
}

void SctpCookie::eraseLocalTieTag(size_t k)
{
    if (k >= localTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)localTieTag_arraysize, (unsigned long)k);
    size_t newSize = localTieTag_arraysize - 1;
    uint8_t *localTieTag2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        localTieTag2[i] = this->localTieTag[i];
    for (i = k; i < newSize; i++)
        localTieTag2[i] = this->localTieTag[i+1];
    delete [] this->localTieTag;
    this->localTieTag = localTieTag2;
    localTieTag_arraysize = newSize;
}

size_t SctpCookie::getPeerTieTagArraySize() const
{
    return peerTieTag_arraysize;
}

uint8_t SctpCookie::getPeerTieTag(size_t k) const
{
    if (k >= peerTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peerTieTag_arraysize, (unsigned long)k);
    return this->peerTieTag[k];
}

void SctpCookie::setPeerTieTagArraySize(size_t newSize)
{
    uint8_t *peerTieTag2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = peerTieTag_arraysize < newSize ? peerTieTag_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        peerTieTag2[i] = this->peerTieTag[i];
    for (size_t i = minSize; i < newSize; i++)
        peerTieTag2[i] = 0;
    delete [] this->peerTieTag;
    this->peerTieTag = peerTieTag2;
    peerTieTag_arraysize = newSize;
}

void SctpCookie::setPeerTieTag(size_t k, uint8_t peerTieTag)
{
    if (k >= peerTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peerTieTag_arraysize, (unsigned long)k);
    this->peerTieTag[k] = peerTieTag;
}

void SctpCookie::insertPeerTieTag(size_t k, uint8_t peerTieTag)
{
    if (k > peerTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peerTieTag_arraysize, (unsigned long)k);
    size_t newSize = peerTieTag_arraysize + 1;
    uint8_t *peerTieTag2 = new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peerTieTag2[i] = this->peerTieTag[i];
    peerTieTag2[k] = peerTieTag;
    for (i = k + 1; i < newSize; i++)
        peerTieTag2[i] = this->peerTieTag[i-1];
    delete [] this->peerTieTag;
    this->peerTieTag = peerTieTag2;
    peerTieTag_arraysize = newSize;
}

void SctpCookie::appendPeerTieTag(uint8_t peerTieTag)
{
    insertPeerTieTag(peerTieTag_arraysize, peerTieTag);
}

void SctpCookie::erasePeerTieTag(size_t k)
{
    if (k >= peerTieTag_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peerTieTag_arraysize, (unsigned long)k);
    size_t newSize = peerTieTag_arraysize - 1;
    uint8_t *peerTieTag2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peerTieTag2[i] = this->peerTieTag[i];
    for (i = k; i < newSize; i++)
        peerTieTag2[i] = this->peerTieTag[i+1];
    delete [] this->peerTieTag;
    this->peerTieTag = peerTieTag2;
    peerTieTag_arraysize = newSize;
}

uint32_t SctpCookie::getLength() const
{
    return this->length;
}

void SctpCookie::setLength(uint32_t length)
{
    this->length = length;
}

class SctpCookieDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_creationTime,
        FIELD_localTag,
        FIELD_peerTag,
        FIELD_localTieTag,
        FIELD_peerTieTag,
        FIELD_length,
    };
  public:
    SctpCookieDescriptor();
    virtual ~SctpCookieDescriptor();

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

Register_ClassDescriptor(SctpCookieDescriptor)

SctpCookieDescriptor::SctpCookieDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpCookie)), "omnetpp::cNamedObject")
{
    propertyNames = nullptr;
}

SctpCookieDescriptor::~SctpCookieDescriptor()
{
    delete[] propertyNames;
}

bool SctpCookieDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpCookie *>(obj)!=nullptr;
}

const char **SctpCookieDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpCookieDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpCookieDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int SctpCookieDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_creationTime
        FD_ISEDITABLE,    // FIELD_localTag
        FD_ISEDITABLE,    // FIELD_peerTag
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_localTieTag
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_peerTieTag
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *SctpCookieDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "creationTime",
        "localTag",
        "peerTag",
        "localTieTag",
        "peerTieTag",
        "length",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int SctpCookieDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "creationTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "localTag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "peerTag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "localTieTag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "peerTieTag") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpCookieDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_creationTime
        "uint32_t",    // FIELD_localTag
        "uint32_t",    // FIELD_peerTag
        "uint8_t",    // FIELD_localTieTag
        "uint8_t",    // FIELD_peerTieTag
        "uint32_t",    // FIELD_length
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpCookieDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpCookieDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpCookieDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_localTieTag: return pp->getLocalTieTagArraySize();
        case FIELD_peerTieTag: return pp->getPeerTieTagArraySize();
        default: return 0;
    }
}

void SctpCookieDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_localTieTag: pp->setLocalTieTagArraySize(size); break;
        case FIELD_peerTieTag: pp->setPeerTieTagArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpCookie'", field);
    }
}

const char *SctpCookieDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpCookieDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return simtime2string(pp->getCreationTime());
        case FIELD_localTag: return ulong2string(pp->getLocalTag());
        case FIELD_peerTag: return ulong2string(pp->getPeerTag());
        case FIELD_localTieTag: return ulong2string(pp->getLocalTieTag(i));
        case FIELD_peerTieTag: return ulong2string(pp->getPeerTieTag(i));
        case FIELD_length: return ulong2string(pp->getLength());
        default: return "";
    }
}

void SctpCookieDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(string2simtime(value)); break;
        case FIELD_localTag: pp->setLocalTag(string2ulong(value)); break;
        case FIELD_peerTag: pp->setPeerTag(string2ulong(value)); break;
        case FIELD_localTieTag: pp->setLocalTieTag(i,string2ulong(value)); break;
        case FIELD_peerTieTag: pp->setPeerTieTag(i,string2ulong(value)); break;
        case FIELD_length: pp->setLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookie'", field);
    }
}

omnetpp::cValue SctpCookieDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return pp->getCreationTime().dbl();
        case FIELD_localTag: return (omnetpp::intval_t)(pp->getLocalTag());
        case FIELD_peerTag: return (omnetpp::intval_t)(pp->getPeerTag());
        case FIELD_localTieTag: return (omnetpp::intval_t)(pp->getLocalTieTag(i));
        case FIELD_peerTieTag: return (omnetpp::intval_t)(pp->getPeerTieTag(i));
        case FIELD_length: return (omnetpp::intval_t)(pp->getLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpCookie' as cValue -- field index out of range?", field);
    }
}

void SctpCookieDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(value.doubleValue()); break;
        case FIELD_localTag: pp->setLocalTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_peerTag: pp->setPeerTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_localTieTag: pp->setLocalTieTag(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_peerTieTag: pp->setPeerTieTag(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookie'", field);
    }
}

const char *SctpCookieDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpCookieDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpCookieDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookie *pp = omnetpp::fromAnyPtr<SctpCookie>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookie'", field);
    }
}

Register_Class(SctpCookieAckChunk)

SctpCookieAckChunk::SctpCookieAckChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpCookieAckChunk::SctpCookieAckChunk(const SctpCookieAckChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpCookieAckChunk::~SctpCookieAckChunk()
{
}

SctpCookieAckChunk& SctpCookieAckChunk::operator=(const SctpCookieAckChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpCookieAckChunk::copy(const SctpCookieAckChunk& other)
{
}

void SctpCookieAckChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
}

void SctpCookieAckChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
}

class SctpCookieAckChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SctpCookieAckChunkDescriptor();
    virtual ~SctpCookieAckChunkDescriptor();

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

Register_ClassDescriptor(SctpCookieAckChunkDescriptor)

SctpCookieAckChunkDescriptor::SctpCookieAckChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpCookieAckChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpCookieAckChunkDescriptor::~SctpCookieAckChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpCookieAckChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpCookieAckChunk *>(obj)!=nullptr;
}

const char **SctpCookieAckChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpCookieAckChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpCookieAckChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SctpCookieAckChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SctpCookieAckChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SctpCookieAckChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SctpCookieAckChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SctpCookieAckChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpCookieAckChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpCookieAckChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpCookieAckChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpCookieAckChunk'", field);
    }
}

const char *SctpCookieAckChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpCookieAckChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SctpCookieAckChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieAckChunk'", field);
    }
}

omnetpp::cValue SctpCookieAckChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpCookieAckChunk' as cValue -- field index out of range?", field);
    }
}

void SctpCookieAckChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieAckChunk'", field);
    }
}

const char *SctpCookieAckChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SctpCookieAckChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpCookieAckChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpCookieAckChunk *pp = omnetpp::fromAnyPtr<SctpCookieAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpCookieAckChunk'", field);
    }
}

Register_Class(SctpDataMsg)

SctpDataMsg::SctpDataMsg(const char *name) : ::omnetpp::cPacket(name)
{
}

SctpDataMsg::SctpDataMsg(const SctpDataMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SctpDataMsg::~SctpDataMsg()
{
}

SctpDataMsg& SctpDataMsg::operator=(const SctpDataMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SctpDataMsg::copy(const SctpDataMsg& other)
{
    this->eBit = other.eBit;
    this->bBit = other.bBit;
    this->enqueuingTime = other.enqueuingTime;
    this->expiryTime = other.expiryTime;
    this->ppid = other.ppid;
    this->initialDestination = other.initialDestination;
    this->msgNum = other.msgNum;
    this->sid = other.sid;
    this->ordered = other.ordered;
    this->booksize = other.booksize;
    this->rtx = other.rtx;
    this->fragment = other.fragment;
    this->prMethod = other.prMethod;
    this->priority = other.priority;
    this->strReset = other.strReset;
    this->sackNow = other.sackNow;
}

void SctpDataMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->eBit);
    doParsimPacking(b,this->bBit);
    doParsimPacking(b,this->enqueuingTime);
    doParsimPacking(b,this->expiryTime);
    doParsimPacking(b,this->ppid);
    doParsimPacking(b,this->initialDestination);
    doParsimPacking(b,this->msgNum);
    doParsimPacking(b,this->sid);
    doParsimPacking(b,this->ordered);
    doParsimPacking(b,this->booksize);
    doParsimPacking(b,this->rtx);
    doParsimPacking(b,this->fragment);
    doParsimPacking(b,this->prMethod);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->strReset);
    doParsimPacking(b,this->sackNow);
}

void SctpDataMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->eBit);
    doParsimUnpacking(b,this->bBit);
    doParsimUnpacking(b,this->enqueuingTime);
    doParsimUnpacking(b,this->expiryTime);
    doParsimUnpacking(b,this->ppid);
    doParsimUnpacking(b,this->initialDestination);
    doParsimUnpacking(b,this->msgNum);
    doParsimUnpacking(b,this->sid);
    doParsimUnpacking(b,this->ordered);
    doParsimUnpacking(b,this->booksize);
    doParsimUnpacking(b,this->rtx);
    doParsimUnpacking(b,this->fragment);
    doParsimUnpacking(b,this->prMethod);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->strReset);
    doParsimUnpacking(b,this->sackNow);
}

bool SctpDataMsg::getEBit() const
{
    return this->eBit;
}

void SctpDataMsg::setEBit(bool eBit)
{
    this->eBit = eBit;
}

bool SctpDataMsg::getBBit() const
{
    return this->bBit;
}

void SctpDataMsg::setBBit(bool bBit)
{
    this->bBit = bBit;
}

::omnetpp::simtime_t SctpDataMsg::getEnqueuingTime() const
{
    return this->enqueuingTime;
}

void SctpDataMsg::setEnqueuingTime(::omnetpp::simtime_t enqueuingTime)
{
    this->enqueuingTime = enqueuingTime;
}

::omnetpp::simtime_t SctpDataMsg::getExpiryTime() const
{
    return this->expiryTime;
}

void SctpDataMsg::setExpiryTime(::omnetpp::simtime_t expiryTime)
{
    this->expiryTime = expiryTime;
}

uint32_t SctpDataMsg::getPpid() const
{
    return this->ppid;
}

void SctpDataMsg::setPpid(uint32_t ppid)
{
    this->ppid = ppid;
}

const ::inet::L3Address& SctpDataMsg::getInitialDestination() const
{
    return this->initialDestination;
}

void SctpDataMsg::setInitialDestination(const ::inet::L3Address& initialDestination)
{
    this->initialDestination = initialDestination;
}

uint32_t SctpDataMsg::getMsgNum() const
{
    return this->msgNum;
}

void SctpDataMsg::setMsgNum(uint32_t msgNum)
{
    this->msgNum = msgNum;
}

uint16_t SctpDataMsg::getSid() const
{
    return this->sid;
}

void SctpDataMsg::setSid(uint16_t sid)
{
    this->sid = sid;
}

bool SctpDataMsg::getOrdered() const
{
    return this->ordered;
}

void SctpDataMsg::setOrdered(bool ordered)
{
    this->ordered = ordered;
}

uint32_t SctpDataMsg::getBooksize() const
{
    return this->booksize;
}

void SctpDataMsg::setBooksize(uint32_t booksize)
{
    this->booksize = booksize;
}

uint32_t SctpDataMsg::getRtx() const
{
    return this->rtx;
}

void SctpDataMsg::setRtx(uint32_t rtx)
{
    this->rtx = rtx;
}

bool SctpDataMsg::getFragment() const
{
    return this->fragment;
}

void SctpDataMsg::setFragment(bool fragment)
{
    this->fragment = fragment;
}

uint32_t SctpDataMsg::getPrMethod() const
{
    return this->prMethod;
}

void SctpDataMsg::setPrMethod(uint32_t prMethod)
{
    this->prMethod = prMethod;
}

uint32_t SctpDataMsg::getPriority() const
{
    return this->priority;
}

void SctpDataMsg::setPriority(uint32_t priority)
{
    this->priority = priority;
}

bool SctpDataMsg::getStrReset() const
{
    return this->strReset;
}

void SctpDataMsg::setStrReset(bool strReset)
{
    this->strReset = strReset;
}

bool SctpDataMsg::getSackNow() const
{
    return this->sackNow;
}

void SctpDataMsg::setSackNow(bool sackNow)
{
    this->sackNow = sackNow;
}

class SctpDataMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_eBit,
        FIELD_bBit,
        FIELD_enqueuingTime,
        FIELD_expiryTime,
        FIELD_ppid,
        FIELD_initialDestination,
        FIELD_msgNum,
        FIELD_sid,
        FIELD_ordered,
        FIELD_booksize,
        FIELD_rtx,
        FIELD_fragment,
        FIELD_prMethod,
        FIELD_priority,
        FIELD_strReset,
        FIELD_sackNow,
    };
  public:
    SctpDataMsgDescriptor();
    virtual ~SctpDataMsgDescriptor();

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

Register_ClassDescriptor(SctpDataMsgDescriptor)

SctpDataMsgDescriptor::SctpDataMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpDataMsg)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SctpDataMsgDescriptor::~SctpDataMsgDescriptor()
{
    delete[] propertyNames;
}

bool SctpDataMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpDataMsg *>(obj)!=nullptr;
}

const char **SctpDataMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpDataMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpDataMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 16+base->getFieldCount() : 16;
}

unsigned int SctpDataMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_bBit
        FD_ISEDITABLE,    // FIELD_enqueuingTime
        FD_ISEDITABLE,    // FIELD_expiryTime
        FD_ISEDITABLE,    // FIELD_ppid
        0,    // FIELD_initialDestination
        FD_ISEDITABLE,    // FIELD_msgNum
        FD_ISEDITABLE,    // FIELD_sid
        FD_ISEDITABLE,    // FIELD_ordered
        FD_ISEDITABLE,    // FIELD_booksize
        FD_ISEDITABLE,    // FIELD_rtx
        FD_ISEDITABLE,    // FIELD_fragment
        FD_ISEDITABLE,    // FIELD_prMethod
        FD_ISEDITABLE,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_strReset
        FD_ISEDITABLE,    // FIELD_sackNow
    };
    return (field >= 0 && field < 16) ? fieldTypeFlags[field] : 0;
}

const char *SctpDataMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "eBit",
        "bBit",
        "enqueuingTime",
        "expiryTime",
        "ppid",
        "initialDestination",
        "msgNum",
        "sid",
        "ordered",
        "booksize",
        "rtx",
        "fragment",
        "prMethod",
        "priority",
        "strReset",
        "sackNow",
    };
    return (field >= 0 && field < 16) ? fieldNames[field] : nullptr;
}

int SctpDataMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "enqueuingTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "expiryTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "ppid") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "initialDestination") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "msgNum") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sid") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "ordered") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "booksize") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "rtx") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "fragment") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "prMethod") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "strReset") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "sackNow") == 0) return baseIndex + 15;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpDataMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_eBit
        "bool",    // FIELD_bBit
        "omnetpp::simtime_t",    // FIELD_enqueuingTime
        "omnetpp::simtime_t",    // FIELD_expiryTime
        "uint32_t",    // FIELD_ppid
        "inet::L3Address",    // FIELD_initialDestination
        "uint32_t",    // FIELD_msgNum
        "uint16_t",    // FIELD_sid
        "bool",    // FIELD_ordered
        "uint32_t",    // FIELD_booksize
        "uint32_t",    // FIELD_rtx
        "bool",    // FIELD_fragment
        "uint32_t",    // FIELD_prMethod
        "uint32_t",    // FIELD_priority
        "bool",    // FIELD_strReset
        "bool",    // FIELD_sackNow
    };
    return (field >= 0 && field < 16) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpDataMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpDataMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpDataMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpDataMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpDataMsg'", field);
    }
}

const char *SctpDataMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpDataMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return bool2string(pp->getEBit());
        case FIELD_bBit: return bool2string(pp->getBBit());
        case FIELD_enqueuingTime: return simtime2string(pp->getEnqueuingTime());
        case FIELD_expiryTime: return simtime2string(pp->getExpiryTime());
        case FIELD_ppid: return ulong2string(pp->getPpid());
        case FIELD_initialDestination: return pp->getInitialDestination().str();
        case FIELD_msgNum: return ulong2string(pp->getMsgNum());
        case FIELD_sid: return ulong2string(pp->getSid());
        case FIELD_ordered: return bool2string(pp->getOrdered());
        case FIELD_booksize: return ulong2string(pp->getBooksize());
        case FIELD_rtx: return ulong2string(pp->getRtx());
        case FIELD_fragment: return bool2string(pp->getFragment());
        case FIELD_prMethod: return ulong2string(pp->getPrMethod());
        case FIELD_priority: return ulong2string(pp->getPriority());
        case FIELD_strReset: return bool2string(pp->getStrReset());
        case FIELD_sackNow: return bool2string(pp->getSackNow());
        default: return "";
    }
}

void SctpDataMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(string2bool(value)); break;
        case FIELD_bBit: pp->setBBit(string2bool(value)); break;
        case FIELD_enqueuingTime: pp->setEnqueuingTime(string2simtime(value)); break;
        case FIELD_expiryTime: pp->setExpiryTime(string2simtime(value)); break;
        case FIELD_ppid: pp->setPpid(string2ulong(value)); break;
        case FIELD_msgNum: pp->setMsgNum(string2ulong(value)); break;
        case FIELD_sid: pp->setSid(string2ulong(value)); break;
        case FIELD_ordered: pp->setOrdered(string2bool(value)); break;
        case FIELD_booksize: pp->setBooksize(string2ulong(value)); break;
        case FIELD_rtx: pp->setRtx(string2ulong(value)); break;
        case FIELD_fragment: pp->setFragment(string2bool(value)); break;
        case FIELD_prMethod: pp->setPrMethod(string2ulong(value)); break;
        case FIELD_priority: pp->setPriority(string2ulong(value)); break;
        case FIELD_strReset: pp->setStrReset(string2bool(value)); break;
        case FIELD_sackNow: pp->setSackNow(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataMsg'", field);
    }
}

omnetpp::cValue SctpDataMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return pp->getEBit();
        case FIELD_bBit: return pp->getBBit();
        case FIELD_enqueuingTime: return pp->getEnqueuingTime().dbl();
        case FIELD_expiryTime: return pp->getExpiryTime().dbl();
        case FIELD_ppid: return (omnetpp::intval_t)(pp->getPpid());
        case FIELD_initialDestination: return omnetpp::toAnyPtr(&pp->getInitialDestination()); break;
        case FIELD_msgNum: return (omnetpp::intval_t)(pp->getMsgNum());
        case FIELD_sid: return (omnetpp::intval_t)(pp->getSid());
        case FIELD_ordered: return pp->getOrdered();
        case FIELD_booksize: return (omnetpp::intval_t)(pp->getBooksize());
        case FIELD_rtx: return (omnetpp::intval_t)(pp->getRtx());
        case FIELD_fragment: return pp->getFragment();
        case FIELD_prMethod: return (omnetpp::intval_t)(pp->getPrMethod());
        case FIELD_priority: return (omnetpp::intval_t)(pp->getPriority());
        case FIELD_strReset: return pp->getStrReset();
        case FIELD_sackNow: return pp->getSackNow();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpDataMsg' as cValue -- field index out of range?", field);
    }
}

void SctpDataMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(value.boolValue()); break;
        case FIELD_bBit: pp->setBBit(value.boolValue()); break;
        case FIELD_enqueuingTime: pp->setEnqueuingTime(value.doubleValue()); break;
        case FIELD_expiryTime: pp->setExpiryTime(value.doubleValue()); break;
        case FIELD_ppid: pp->setPpid(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_msgNum: pp->setMsgNum(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sid: pp->setSid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_ordered: pp->setOrdered(value.boolValue()); break;
        case FIELD_booksize: pp->setBooksize(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_rtx: pp->setRtx(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_fragment: pp->setFragment(value.boolValue()); break;
        case FIELD_prMethod: pp->setPrMethod(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_strReset: pp->setStrReset(value.boolValue()); break;
        case FIELD_sackNow: pp->setSackNow(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataMsg'", field);
    }
}

const char *SctpDataMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpDataMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        case FIELD_initialDestination: return omnetpp::toAnyPtr(&pp->getInitialDestination()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpDataMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataMsg *pp = omnetpp::fromAnyPtr<SctpDataMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataMsg'", field);
    }
}

Register_Class(SctpDataChunk)

SctpDataChunk::SctpDataChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpDataChunk::SctpDataChunk(const SctpDataChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpDataChunk::~SctpDataChunk()
{
}

SctpDataChunk& SctpDataChunk::operator=(const SctpDataChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpDataChunk::copy(const SctpDataChunk& other)
{
    this->eBit = other.eBit;
    this->bBit = other.bBit;
    this->uBit = other.uBit;
    this->iBit = other.iBit;
    this->tsn = other.tsn;
    this->sid = other.sid;
    this->ssn = other.ssn;
    this->ppid = other.ppid;
    this->enqueuingTime = other.enqueuingTime;
    this->firstSendTime = other.firstSendTime;
}

void SctpDataChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->eBit);
    doParsimPacking(b,this->bBit);
    doParsimPacking(b,this->uBit);
    doParsimPacking(b,this->iBit);
    doParsimPacking(b,this->tsn);
    doParsimPacking(b,this->sid);
    doParsimPacking(b,this->ssn);
    doParsimPacking(b,this->ppid);
    doParsimPacking(b,this->enqueuingTime);
    doParsimPacking(b,this->firstSendTime);
}

void SctpDataChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->eBit);
    doParsimUnpacking(b,this->bBit);
    doParsimUnpacking(b,this->uBit);
    doParsimUnpacking(b,this->iBit);
    doParsimUnpacking(b,this->tsn);
    doParsimUnpacking(b,this->sid);
    doParsimUnpacking(b,this->ssn);
    doParsimUnpacking(b,this->ppid);
    doParsimUnpacking(b,this->enqueuingTime);
    doParsimUnpacking(b,this->firstSendTime);
}

bool SctpDataChunk::getEBit() const
{
    return this->eBit;
}

void SctpDataChunk::setEBit(bool eBit)
{
    this->eBit = eBit;
}

bool SctpDataChunk::getBBit() const
{
    return this->bBit;
}

void SctpDataChunk::setBBit(bool bBit)
{
    this->bBit = bBit;
}

bool SctpDataChunk::getUBit() const
{
    return this->uBit;
}

void SctpDataChunk::setUBit(bool uBit)
{
    this->uBit = uBit;
}

bool SctpDataChunk::getIBit() const
{
    return this->iBit;
}

void SctpDataChunk::setIBit(bool iBit)
{
    this->iBit = iBit;
}

uint32_t SctpDataChunk::getTsn() const
{
    return this->tsn;
}

void SctpDataChunk::setTsn(uint32_t tsn)
{
    this->tsn = tsn;
}

uint16_t SctpDataChunk::getSid() const
{
    return this->sid;
}

void SctpDataChunk::setSid(uint16_t sid)
{
    this->sid = sid;
}

uint16_t SctpDataChunk::getSsn() const
{
    return this->ssn;
}

void SctpDataChunk::setSsn(uint16_t ssn)
{
    this->ssn = ssn;
}

uint32_t SctpDataChunk::getPpid() const
{
    return this->ppid;
}

void SctpDataChunk::setPpid(uint32_t ppid)
{
    this->ppid = ppid;
}

::omnetpp::simtime_t SctpDataChunk::getEnqueuingTime() const
{
    return this->enqueuingTime;
}

void SctpDataChunk::setEnqueuingTime(::omnetpp::simtime_t enqueuingTime)
{
    this->enqueuingTime = enqueuingTime;
}

::omnetpp::simtime_t SctpDataChunk::getFirstSendTime() const
{
    return this->firstSendTime;
}

void SctpDataChunk::setFirstSendTime(::omnetpp::simtime_t firstSendTime)
{
    this->firstSendTime = firstSendTime;
}

class SctpDataChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_eBit,
        FIELD_bBit,
        FIELD_uBit,
        FIELD_iBit,
        FIELD_tsn,
        FIELD_sid,
        FIELD_ssn,
        FIELD_ppid,
        FIELD_enqueuingTime,
        FIELD_firstSendTime,
    };
  public:
    SctpDataChunkDescriptor();
    virtual ~SctpDataChunkDescriptor();

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

Register_ClassDescriptor(SctpDataChunkDescriptor)

SctpDataChunkDescriptor::SctpDataChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpDataChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpDataChunkDescriptor::~SctpDataChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpDataChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpDataChunk *>(obj)!=nullptr;
}

const char **SctpDataChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpDataChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpDataChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int SctpDataChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_eBit
        FD_ISEDITABLE,    // FIELD_bBit
        FD_ISEDITABLE,    // FIELD_uBit
        FD_ISEDITABLE,    // FIELD_iBit
        FD_ISEDITABLE,    // FIELD_tsn
        FD_ISEDITABLE,    // FIELD_sid
        FD_ISEDITABLE,    // FIELD_ssn
        FD_ISEDITABLE,    // FIELD_ppid
        FD_ISEDITABLE,    // FIELD_enqueuingTime
        FD_ISEDITABLE,    // FIELD_firstSendTime
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *SctpDataChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "eBit",
        "bBit",
        "uBit",
        "iBit",
        "tsn",
        "sid",
        "ssn",
        "ppid",
        "enqueuingTime",
        "firstSendTime",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int SctpDataChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "eBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "uBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "iBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "tsn") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "sid") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "ssn") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ppid") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "enqueuingTime") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "firstSendTime") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpDataChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_eBit
        "bool",    // FIELD_bBit
        "bool",    // FIELD_uBit
        "bool",    // FIELD_iBit
        "uint32_t",    // FIELD_tsn
        "uint16_t",    // FIELD_sid
        "uint16_t",    // FIELD_ssn
        "uint32_t",    // FIELD_ppid
        "omnetpp::simtime_t",    // FIELD_enqueuingTime
        "omnetpp::simtime_t",    // FIELD_firstSendTime
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpDataChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpDataChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpDataChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpDataChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpDataChunk'", field);
    }
}

const char *SctpDataChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpDataChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return bool2string(pp->getEBit());
        case FIELD_bBit: return bool2string(pp->getBBit());
        case FIELD_uBit: return bool2string(pp->getUBit());
        case FIELD_iBit: return bool2string(pp->getIBit());
        case FIELD_tsn: return ulong2string(pp->getTsn());
        case FIELD_sid: return ulong2string(pp->getSid());
        case FIELD_ssn: return ulong2string(pp->getSsn());
        case FIELD_ppid: return ulong2string(pp->getPpid());
        case FIELD_enqueuingTime: return simtime2string(pp->getEnqueuingTime());
        case FIELD_firstSendTime: return simtime2string(pp->getFirstSendTime());
        default: return "";
    }
}

void SctpDataChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(string2bool(value)); break;
        case FIELD_bBit: pp->setBBit(string2bool(value)); break;
        case FIELD_uBit: pp->setUBit(string2bool(value)); break;
        case FIELD_iBit: pp->setIBit(string2bool(value)); break;
        case FIELD_tsn: pp->setTsn(string2ulong(value)); break;
        case FIELD_sid: pp->setSid(string2ulong(value)); break;
        case FIELD_ssn: pp->setSsn(string2ulong(value)); break;
        case FIELD_ppid: pp->setPpid(string2ulong(value)); break;
        case FIELD_enqueuingTime: pp->setEnqueuingTime(string2simtime(value)); break;
        case FIELD_firstSendTime: pp->setFirstSendTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataChunk'", field);
    }
}

omnetpp::cValue SctpDataChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: return pp->getEBit();
        case FIELD_bBit: return pp->getBBit();
        case FIELD_uBit: return pp->getUBit();
        case FIELD_iBit: return pp->getIBit();
        case FIELD_tsn: return (omnetpp::intval_t)(pp->getTsn());
        case FIELD_sid: return (omnetpp::intval_t)(pp->getSid());
        case FIELD_ssn: return (omnetpp::intval_t)(pp->getSsn());
        case FIELD_ppid: return (omnetpp::intval_t)(pp->getPpid());
        case FIELD_enqueuingTime: return pp->getEnqueuingTime().dbl();
        case FIELD_firstSendTime: return pp->getFirstSendTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpDataChunk' as cValue -- field index out of range?", field);
    }
}

void SctpDataChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        case FIELD_eBit: pp->setEBit(value.boolValue()); break;
        case FIELD_bBit: pp->setBBit(value.boolValue()); break;
        case FIELD_uBit: pp->setUBit(value.boolValue()); break;
        case FIELD_iBit: pp->setIBit(value.boolValue()); break;
        case FIELD_tsn: pp->setTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sid: pp->setSid(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_ssn: pp->setSsn(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_ppid: pp->setPpid(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_enqueuingTime: pp->setEnqueuingTime(value.doubleValue()); break;
        case FIELD_firstSendTime: pp->setFirstSendTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataChunk'", field);
    }
}

const char *SctpDataChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpDataChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpDataChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDataChunk *pp = omnetpp::fromAnyPtr<SctpDataChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDataChunk'", field);
    }
}

Register_Class(SctpForwardTsnChunk)

SctpForwardTsnChunk::SctpForwardTsnChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpForwardTsnChunk::SctpForwardTsnChunk(const SctpForwardTsnChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpForwardTsnChunk::~SctpForwardTsnChunk()
{
    delete [] this->sid;
    delete [] this->ssn;
}

SctpForwardTsnChunk& SctpForwardTsnChunk::operator=(const SctpForwardTsnChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpForwardTsnChunk::copy(const SctpForwardTsnChunk& other)
{
    this->newCumTsn = other.newCumTsn;
    delete [] this->sid;
    this->sid = (other.sid_arraysize==0) ? nullptr : new uint16_t[other.sid_arraysize];
    sid_arraysize = other.sid_arraysize;
    for (size_t i = 0; i < sid_arraysize; i++) {
        this->sid[i] = other.sid[i];
    }
    delete [] this->ssn;
    this->ssn = (other.ssn_arraysize==0) ? nullptr : new short[other.ssn_arraysize];
    ssn_arraysize = other.ssn_arraysize;
    for (size_t i = 0; i < ssn_arraysize; i++) {
        this->ssn[i] = other.ssn[i];
    }
}

void SctpForwardTsnChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->newCumTsn);
    b->pack(sid_arraysize);
    doParsimArrayPacking(b,this->sid,sid_arraysize);
    b->pack(ssn_arraysize);
    doParsimArrayPacking(b,this->ssn,ssn_arraysize);
}

void SctpForwardTsnChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->newCumTsn);
    delete [] this->sid;
    b->unpack(sid_arraysize);
    if (sid_arraysize == 0) {
        this->sid = nullptr;
    } else {
        this->sid = new uint16_t[sid_arraysize];
        doParsimArrayUnpacking(b,this->sid,sid_arraysize);
    }
    delete [] this->ssn;
    b->unpack(ssn_arraysize);
    if (ssn_arraysize == 0) {
        this->ssn = nullptr;
    } else {
        this->ssn = new short[ssn_arraysize];
        doParsimArrayUnpacking(b,this->ssn,ssn_arraysize);
    }
}

uint32_t SctpForwardTsnChunk::getNewCumTsn() const
{
    return this->newCumTsn;
}

void SctpForwardTsnChunk::setNewCumTsn(uint32_t newCumTsn)
{
    this->newCumTsn = newCumTsn;
}

size_t SctpForwardTsnChunk::getSidArraySize() const
{
    return sid_arraysize;
}

uint16_t SctpForwardTsnChunk::getSid(size_t k) const
{
    if (k >= sid_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sid_arraysize, (unsigned long)k);
    return this->sid[k];
}

void SctpForwardTsnChunk::setSidArraySize(size_t newSize)
{
    uint16_t *sid2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sid_arraysize < newSize ? sid_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sid2[i] = this->sid[i];
    for (size_t i = minSize; i < newSize; i++)
        sid2[i] = 0;
    delete [] this->sid;
    this->sid = sid2;
    sid_arraysize = newSize;
}

void SctpForwardTsnChunk::setSid(size_t k, uint16_t sid)
{
    if (k >= sid_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sid_arraysize, (unsigned long)k);
    this->sid[k] = sid;
}

void SctpForwardTsnChunk::insertSid(size_t k, uint16_t sid)
{
    if (k > sid_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sid_arraysize, (unsigned long)k);
    size_t newSize = sid_arraysize + 1;
    uint16_t *sid2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sid2[i] = this->sid[i];
    sid2[k] = sid;
    for (i = k + 1; i < newSize; i++)
        sid2[i] = this->sid[i-1];
    delete [] this->sid;
    this->sid = sid2;
    sid_arraysize = newSize;
}

void SctpForwardTsnChunk::appendSid(uint16_t sid)
{
    insertSid(sid_arraysize, sid);
}

void SctpForwardTsnChunk::eraseSid(size_t k)
{
    if (k >= sid_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sid_arraysize, (unsigned long)k);
    size_t newSize = sid_arraysize - 1;
    uint16_t *sid2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sid2[i] = this->sid[i];
    for (i = k; i < newSize; i++)
        sid2[i] = this->sid[i+1];
    delete [] this->sid;
    this->sid = sid2;
    sid_arraysize = newSize;
}

size_t SctpForwardTsnChunk::getSsnArraySize() const
{
    return ssn_arraysize;
}

short SctpForwardTsnChunk::getSsn(size_t k) const
{
    if (k >= ssn_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ssn_arraysize, (unsigned long)k);
    return this->ssn[k];
}

void SctpForwardTsnChunk::setSsnArraySize(size_t newSize)
{
    short *ssn2 = (newSize==0) ? nullptr : new short[newSize];
    size_t minSize = ssn_arraysize < newSize ? ssn_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        ssn2[i] = this->ssn[i];
    for (size_t i = minSize; i < newSize; i++)
        ssn2[i] = 0;
    delete [] this->ssn;
    this->ssn = ssn2;
    ssn_arraysize = newSize;
}

void SctpForwardTsnChunk::setSsn(size_t k, short ssn)
{
    if (k >= ssn_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ssn_arraysize, (unsigned long)k);
    this->ssn[k] = ssn;
}

void SctpForwardTsnChunk::insertSsn(size_t k, short ssn)
{
    if (k > ssn_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ssn_arraysize, (unsigned long)k);
    size_t newSize = ssn_arraysize + 1;
    short *ssn2 = new short[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ssn2[i] = this->ssn[i];
    ssn2[k] = ssn;
    for (i = k + 1; i < newSize; i++)
        ssn2[i] = this->ssn[i-1];
    delete [] this->ssn;
    this->ssn = ssn2;
    ssn_arraysize = newSize;
}

void SctpForwardTsnChunk::appendSsn(short ssn)
{
    insertSsn(ssn_arraysize, ssn);
}

void SctpForwardTsnChunk::eraseSsn(size_t k)
{
    if (k >= ssn_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)ssn_arraysize, (unsigned long)k);
    size_t newSize = ssn_arraysize - 1;
    short *ssn2 = (newSize == 0) ? nullptr : new short[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        ssn2[i] = this->ssn[i];
    for (i = k; i < newSize; i++)
        ssn2[i] = this->ssn[i+1];
    delete [] this->ssn;
    this->ssn = ssn2;
    ssn_arraysize = newSize;
}

class SctpForwardTsnChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_newCumTsn,
        FIELD_sid,
        FIELD_ssn,
    };
  public:
    SctpForwardTsnChunkDescriptor();
    virtual ~SctpForwardTsnChunkDescriptor();

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

Register_ClassDescriptor(SctpForwardTsnChunkDescriptor)

SctpForwardTsnChunkDescriptor::SctpForwardTsnChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpForwardTsnChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpForwardTsnChunkDescriptor::~SctpForwardTsnChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpForwardTsnChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpForwardTsnChunk *>(obj)!=nullptr;
}

const char **SctpForwardTsnChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpForwardTsnChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpForwardTsnChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpForwardTsnChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_newCumTsn
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sid
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_ssn
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpForwardTsnChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "newCumTsn",
        "sid",
        "ssn",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpForwardTsnChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "newCumTsn") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sid") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ssn") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpForwardTsnChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_newCumTsn
        "uint16_t",    // FIELD_sid
        "short",    // FIELD_ssn
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpForwardTsnChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpForwardTsnChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpForwardTsnChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sid: return pp->getSidArraySize();
        case FIELD_ssn: return pp->getSsnArraySize();
        default: return 0;
    }
}

void SctpForwardTsnChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sid: pp->setSidArraySize(size); break;
        case FIELD_ssn: pp->setSsnArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpForwardTsnChunk'", field);
    }
}

const char *SctpForwardTsnChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpForwardTsnChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_newCumTsn: return ulong2string(pp->getNewCumTsn());
        case FIELD_sid: return ulong2string(pp->getSid(i));
        case FIELD_ssn: return long2string(pp->getSsn(i));
        default: return "";
    }
}

void SctpForwardTsnChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_newCumTsn: pp->setNewCumTsn(string2ulong(value)); break;
        case FIELD_sid: pp->setSid(i,string2ulong(value)); break;
        case FIELD_ssn: pp->setSsn(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpForwardTsnChunk'", field);
    }
}

omnetpp::cValue SctpForwardTsnChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_newCumTsn: return (omnetpp::intval_t)(pp->getNewCumTsn());
        case FIELD_sid: return (omnetpp::intval_t)(pp->getSid(i));
        case FIELD_ssn: return pp->getSsn(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpForwardTsnChunk' as cValue -- field index out of range?", field);
    }
}

void SctpForwardTsnChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        case FIELD_newCumTsn: pp->setNewCumTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sid: pp->setSid(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_ssn: pp->setSsn(i,omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpForwardTsnChunk'", field);
    }
}

const char *SctpForwardTsnChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpForwardTsnChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpForwardTsnChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpForwardTsnChunk *pp = omnetpp::fromAnyPtr<SctpForwardTsnChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpForwardTsnChunk'", field);
    }
}

Register_Class(SctpSackChunk)

SctpSackChunk::SctpSackChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpSackChunk::SctpSackChunk(const SctpSackChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpSackChunk::~SctpSackChunk()
{
    delete [] this->gapStart;
    delete [] this->gapStop;
    delete [] this->dupTsns;
    delete [] this->nrGapStart;
    delete [] this->nrGapStop;
}

SctpSackChunk& SctpSackChunk::operator=(const SctpSackChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpSackChunk::copy(const SctpSackChunk& other)
{
    this->cumTsnAck = other.cumTsnAck;
    this->a_rwnd = other.a_rwnd;
    this->numGaps = other.numGaps;
    this->numNrGaps = other.numNrGaps;
    this->numDupTsns = other.numDupTsns;
    this->isNrSack_ = other.isNrSack_;
    delete [] this->gapStart;
    this->gapStart = (other.gapStart_arraysize==0) ? nullptr : new uint32_t[other.gapStart_arraysize];
    gapStart_arraysize = other.gapStart_arraysize;
    for (size_t i = 0; i < gapStart_arraysize; i++) {
        this->gapStart[i] = other.gapStart[i];
    }
    delete [] this->gapStop;
    this->gapStop = (other.gapStop_arraysize==0) ? nullptr : new uint32_t[other.gapStop_arraysize];
    gapStop_arraysize = other.gapStop_arraysize;
    for (size_t i = 0; i < gapStop_arraysize; i++) {
        this->gapStop[i] = other.gapStop[i];
    }
    delete [] this->dupTsns;
    this->dupTsns = (other.dupTsns_arraysize==0) ? nullptr : new uint32_t[other.dupTsns_arraysize];
    dupTsns_arraysize = other.dupTsns_arraysize;
    for (size_t i = 0; i < dupTsns_arraysize; i++) {
        this->dupTsns[i] = other.dupTsns[i];
    }
    this->sackSeqNum = other.sackSeqNum;
    delete [] this->nrGapStart;
    this->nrGapStart = (other.nrGapStart_arraysize==0) ? nullptr : new uint32_t[other.nrGapStart_arraysize];
    nrGapStart_arraysize = other.nrGapStart_arraysize;
    for (size_t i = 0; i < nrGapStart_arraysize; i++) {
        this->nrGapStart[i] = other.nrGapStart[i];
    }
    delete [] this->nrGapStop;
    this->nrGapStop = (other.nrGapStop_arraysize==0) ? nullptr : new uint32_t[other.nrGapStop_arraysize];
    nrGapStop_arraysize = other.nrGapStop_arraysize;
    for (size_t i = 0; i < nrGapStop_arraysize; i++) {
        this->nrGapStop[i] = other.nrGapStop[i];
    }
    this->msg_rwnd = other.msg_rwnd;
    this->dacPacketsRcvd = other.dacPacketsRcvd;
    this->nrSubtractRGaps = other.nrSubtractRGaps;
}

void SctpSackChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->cumTsnAck);
    doParsimPacking(b,this->a_rwnd);
    doParsimPacking(b,this->numGaps);
    doParsimPacking(b,this->numNrGaps);
    doParsimPacking(b,this->numDupTsns);
    doParsimPacking(b,this->isNrSack_);
    b->pack(gapStart_arraysize);
    doParsimArrayPacking(b,this->gapStart,gapStart_arraysize);
    b->pack(gapStop_arraysize);
    doParsimArrayPacking(b,this->gapStop,gapStop_arraysize);
    b->pack(dupTsns_arraysize);
    doParsimArrayPacking(b,this->dupTsns,dupTsns_arraysize);
    doParsimPacking(b,this->sackSeqNum);
    b->pack(nrGapStart_arraysize);
    doParsimArrayPacking(b,this->nrGapStart,nrGapStart_arraysize);
    b->pack(nrGapStop_arraysize);
    doParsimArrayPacking(b,this->nrGapStop,nrGapStop_arraysize);
    doParsimPacking(b,this->msg_rwnd);
    doParsimPacking(b,this->dacPacketsRcvd);
    doParsimPacking(b,this->nrSubtractRGaps);
}

void SctpSackChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->cumTsnAck);
    doParsimUnpacking(b,this->a_rwnd);
    doParsimUnpacking(b,this->numGaps);
    doParsimUnpacking(b,this->numNrGaps);
    doParsimUnpacking(b,this->numDupTsns);
    doParsimUnpacking(b,this->isNrSack_);
    delete [] this->gapStart;
    b->unpack(gapStart_arraysize);
    if (gapStart_arraysize == 0) {
        this->gapStart = nullptr;
    } else {
        this->gapStart = new uint32_t[gapStart_arraysize];
        doParsimArrayUnpacking(b,this->gapStart,gapStart_arraysize);
    }
    delete [] this->gapStop;
    b->unpack(gapStop_arraysize);
    if (gapStop_arraysize == 0) {
        this->gapStop = nullptr;
    } else {
        this->gapStop = new uint32_t[gapStop_arraysize];
        doParsimArrayUnpacking(b,this->gapStop,gapStop_arraysize);
    }
    delete [] this->dupTsns;
    b->unpack(dupTsns_arraysize);
    if (dupTsns_arraysize == 0) {
        this->dupTsns = nullptr;
    } else {
        this->dupTsns = new uint32_t[dupTsns_arraysize];
        doParsimArrayUnpacking(b,this->dupTsns,dupTsns_arraysize);
    }
    doParsimUnpacking(b,this->sackSeqNum);
    delete [] this->nrGapStart;
    b->unpack(nrGapStart_arraysize);
    if (nrGapStart_arraysize == 0) {
        this->nrGapStart = nullptr;
    } else {
        this->nrGapStart = new uint32_t[nrGapStart_arraysize];
        doParsimArrayUnpacking(b,this->nrGapStart,nrGapStart_arraysize);
    }
    delete [] this->nrGapStop;
    b->unpack(nrGapStop_arraysize);
    if (nrGapStop_arraysize == 0) {
        this->nrGapStop = nullptr;
    } else {
        this->nrGapStop = new uint32_t[nrGapStop_arraysize];
        doParsimArrayUnpacking(b,this->nrGapStop,nrGapStop_arraysize);
    }
    doParsimUnpacking(b,this->msg_rwnd);
    doParsimUnpacking(b,this->dacPacketsRcvd);
    doParsimUnpacking(b,this->nrSubtractRGaps);
}

uint32_t SctpSackChunk::getCumTsnAck() const
{
    return this->cumTsnAck;
}

void SctpSackChunk::setCumTsnAck(uint32_t cumTsnAck)
{
    this->cumTsnAck = cumTsnAck;
}

uint32_t SctpSackChunk::getA_rwnd() const
{
    return this->a_rwnd;
}

void SctpSackChunk::setA_rwnd(uint32_t a_rwnd)
{
    this->a_rwnd = a_rwnd;
}

uint16_t SctpSackChunk::getNumGaps() const
{
    return this->numGaps;
}

void SctpSackChunk::setNumGaps(uint16_t numGaps)
{
    this->numGaps = numGaps;
}

uint16_t SctpSackChunk::getNumNrGaps() const
{
    return this->numNrGaps;
}

void SctpSackChunk::setNumNrGaps(uint16_t numNrGaps)
{
    this->numNrGaps = numNrGaps;
}

uint16_t SctpSackChunk::getNumDupTsns() const
{
    return this->numDupTsns;
}

void SctpSackChunk::setNumDupTsns(uint16_t numDupTsns)
{
    this->numDupTsns = numDupTsns;
}

bool SctpSackChunk::isNrSack() const
{
    return this->isNrSack_;
}

void SctpSackChunk::setIsNrSack(bool isNrSack)
{
    this->isNrSack_ = isNrSack;
}

size_t SctpSackChunk::getGapStartArraySize() const
{
    return gapStart_arraysize;
}

uint32_t SctpSackChunk::getGapStart(size_t k) const
{
    if (k >= gapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStart_arraysize, (unsigned long)k);
    return this->gapStart[k];
}

void SctpSackChunk::setGapStartArraySize(size_t newSize)
{
    uint32_t *gapStart2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = gapStart_arraysize < newSize ? gapStart_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        gapStart2[i] = this->gapStart[i];
    for (size_t i = minSize; i < newSize; i++)
        gapStart2[i] = 0;
    delete [] this->gapStart;
    this->gapStart = gapStart2;
    gapStart_arraysize = newSize;
}

void SctpSackChunk::setGapStart(size_t k, uint32_t gapStart)
{
    if (k >= gapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStart_arraysize, (unsigned long)k);
    this->gapStart[k] = gapStart;
}

void SctpSackChunk::insertGapStart(size_t k, uint32_t gapStart)
{
    if (k > gapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStart_arraysize, (unsigned long)k);
    size_t newSize = gapStart_arraysize + 1;
    uint32_t *gapStart2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        gapStart2[i] = this->gapStart[i];
    gapStart2[k] = gapStart;
    for (i = k + 1; i < newSize; i++)
        gapStart2[i] = this->gapStart[i-1];
    delete [] this->gapStart;
    this->gapStart = gapStart2;
    gapStart_arraysize = newSize;
}

void SctpSackChunk::appendGapStart(uint32_t gapStart)
{
    insertGapStart(gapStart_arraysize, gapStart);
}

void SctpSackChunk::eraseGapStart(size_t k)
{
    if (k >= gapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStart_arraysize, (unsigned long)k);
    size_t newSize = gapStart_arraysize - 1;
    uint32_t *gapStart2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        gapStart2[i] = this->gapStart[i];
    for (i = k; i < newSize; i++)
        gapStart2[i] = this->gapStart[i+1];
    delete [] this->gapStart;
    this->gapStart = gapStart2;
    gapStart_arraysize = newSize;
}

size_t SctpSackChunk::getGapStopArraySize() const
{
    return gapStop_arraysize;
}

uint32_t SctpSackChunk::getGapStop(size_t k) const
{
    if (k >= gapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStop_arraysize, (unsigned long)k);
    return this->gapStop[k];
}

void SctpSackChunk::setGapStopArraySize(size_t newSize)
{
    uint32_t *gapStop2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = gapStop_arraysize < newSize ? gapStop_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        gapStop2[i] = this->gapStop[i];
    for (size_t i = minSize; i < newSize; i++)
        gapStop2[i] = 0;
    delete [] this->gapStop;
    this->gapStop = gapStop2;
    gapStop_arraysize = newSize;
}

void SctpSackChunk::setGapStop(size_t k, uint32_t gapStop)
{
    if (k >= gapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStop_arraysize, (unsigned long)k);
    this->gapStop[k] = gapStop;
}

void SctpSackChunk::insertGapStop(size_t k, uint32_t gapStop)
{
    if (k > gapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStop_arraysize, (unsigned long)k);
    size_t newSize = gapStop_arraysize + 1;
    uint32_t *gapStop2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        gapStop2[i] = this->gapStop[i];
    gapStop2[k] = gapStop;
    for (i = k + 1; i < newSize; i++)
        gapStop2[i] = this->gapStop[i-1];
    delete [] this->gapStop;
    this->gapStop = gapStop2;
    gapStop_arraysize = newSize;
}

void SctpSackChunk::appendGapStop(uint32_t gapStop)
{
    insertGapStop(gapStop_arraysize, gapStop);
}

void SctpSackChunk::eraseGapStop(size_t k)
{
    if (k >= gapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)gapStop_arraysize, (unsigned long)k);
    size_t newSize = gapStop_arraysize - 1;
    uint32_t *gapStop2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        gapStop2[i] = this->gapStop[i];
    for (i = k; i < newSize; i++)
        gapStop2[i] = this->gapStop[i+1];
    delete [] this->gapStop;
    this->gapStop = gapStop2;
    gapStop_arraysize = newSize;
}

size_t SctpSackChunk::getDupTsnsArraySize() const
{
    return dupTsns_arraysize;
}

uint32_t SctpSackChunk::getDupTsns(size_t k) const
{
    if (k >= dupTsns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dupTsns_arraysize, (unsigned long)k);
    return this->dupTsns[k];
}

void SctpSackChunk::setDupTsnsArraySize(size_t newSize)
{
    uint32_t *dupTsns2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = dupTsns_arraysize < newSize ? dupTsns_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        dupTsns2[i] = this->dupTsns[i];
    for (size_t i = minSize; i < newSize; i++)
        dupTsns2[i] = 0;
    delete [] this->dupTsns;
    this->dupTsns = dupTsns2;
    dupTsns_arraysize = newSize;
}

void SctpSackChunk::setDupTsns(size_t k, uint32_t dupTsns)
{
    if (k >= dupTsns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dupTsns_arraysize, (unsigned long)k);
    this->dupTsns[k] = dupTsns;
}

void SctpSackChunk::insertDupTsns(size_t k, uint32_t dupTsns)
{
    if (k > dupTsns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dupTsns_arraysize, (unsigned long)k);
    size_t newSize = dupTsns_arraysize + 1;
    uint32_t *dupTsns2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dupTsns2[i] = this->dupTsns[i];
    dupTsns2[k] = dupTsns;
    for (i = k + 1; i < newSize; i++)
        dupTsns2[i] = this->dupTsns[i-1];
    delete [] this->dupTsns;
    this->dupTsns = dupTsns2;
    dupTsns_arraysize = newSize;
}

void SctpSackChunk::appendDupTsns(uint32_t dupTsns)
{
    insertDupTsns(dupTsns_arraysize, dupTsns);
}

void SctpSackChunk::eraseDupTsns(size_t k)
{
    if (k >= dupTsns_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)dupTsns_arraysize, (unsigned long)k);
    size_t newSize = dupTsns_arraysize - 1;
    uint32_t *dupTsns2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        dupTsns2[i] = this->dupTsns[i];
    for (i = k; i < newSize; i++)
        dupTsns2[i] = this->dupTsns[i+1];
    delete [] this->dupTsns;
    this->dupTsns = dupTsns2;
    dupTsns_arraysize = newSize;
}

uint32_t SctpSackChunk::getSackSeqNum() const
{
    return this->sackSeqNum;
}

void SctpSackChunk::setSackSeqNum(uint32_t sackSeqNum)
{
    this->sackSeqNum = sackSeqNum;
}

size_t SctpSackChunk::getNrGapStartArraySize() const
{
    return nrGapStart_arraysize;
}

uint32_t SctpSackChunk::getNrGapStart(size_t k) const
{
    if (k >= nrGapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStart_arraysize, (unsigned long)k);
    return this->nrGapStart[k];
}

void SctpSackChunk::setNrGapStartArraySize(size_t newSize)
{
    uint32_t *nrGapStart2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = nrGapStart_arraysize < newSize ? nrGapStart_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        nrGapStart2[i] = this->nrGapStart[i];
    for (size_t i = minSize; i < newSize; i++)
        nrGapStart2[i] = 0;
    delete [] this->nrGapStart;
    this->nrGapStart = nrGapStart2;
    nrGapStart_arraysize = newSize;
}

void SctpSackChunk::setNrGapStart(size_t k, uint32_t nrGapStart)
{
    if (k >= nrGapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStart_arraysize, (unsigned long)k);
    this->nrGapStart[k] = nrGapStart;
}

void SctpSackChunk::insertNrGapStart(size_t k, uint32_t nrGapStart)
{
    if (k > nrGapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStart_arraysize, (unsigned long)k);
    size_t newSize = nrGapStart_arraysize + 1;
    uint32_t *nrGapStart2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nrGapStart2[i] = this->nrGapStart[i];
    nrGapStart2[k] = nrGapStart;
    for (i = k + 1; i < newSize; i++)
        nrGapStart2[i] = this->nrGapStart[i-1];
    delete [] this->nrGapStart;
    this->nrGapStart = nrGapStart2;
    nrGapStart_arraysize = newSize;
}

void SctpSackChunk::appendNrGapStart(uint32_t nrGapStart)
{
    insertNrGapStart(nrGapStart_arraysize, nrGapStart);
}

void SctpSackChunk::eraseNrGapStart(size_t k)
{
    if (k >= nrGapStart_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStart_arraysize, (unsigned long)k);
    size_t newSize = nrGapStart_arraysize - 1;
    uint32_t *nrGapStart2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nrGapStart2[i] = this->nrGapStart[i];
    for (i = k; i < newSize; i++)
        nrGapStart2[i] = this->nrGapStart[i+1];
    delete [] this->nrGapStart;
    this->nrGapStart = nrGapStart2;
    nrGapStart_arraysize = newSize;
}

size_t SctpSackChunk::getNrGapStopArraySize() const
{
    return nrGapStop_arraysize;
}

uint32_t SctpSackChunk::getNrGapStop(size_t k) const
{
    if (k >= nrGapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStop_arraysize, (unsigned long)k);
    return this->nrGapStop[k];
}

void SctpSackChunk::setNrGapStopArraySize(size_t newSize)
{
    uint32_t *nrGapStop2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = nrGapStop_arraysize < newSize ? nrGapStop_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        nrGapStop2[i] = this->nrGapStop[i];
    for (size_t i = minSize; i < newSize; i++)
        nrGapStop2[i] = 0;
    delete [] this->nrGapStop;
    this->nrGapStop = nrGapStop2;
    nrGapStop_arraysize = newSize;
}

void SctpSackChunk::setNrGapStop(size_t k, uint32_t nrGapStop)
{
    if (k >= nrGapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStop_arraysize, (unsigned long)k);
    this->nrGapStop[k] = nrGapStop;
}

void SctpSackChunk::insertNrGapStop(size_t k, uint32_t nrGapStop)
{
    if (k > nrGapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStop_arraysize, (unsigned long)k);
    size_t newSize = nrGapStop_arraysize + 1;
    uint32_t *nrGapStop2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nrGapStop2[i] = this->nrGapStop[i];
    nrGapStop2[k] = nrGapStop;
    for (i = k + 1; i < newSize; i++)
        nrGapStop2[i] = this->nrGapStop[i-1];
    delete [] this->nrGapStop;
    this->nrGapStop = nrGapStop2;
    nrGapStop_arraysize = newSize;
}

void SctpSackChunk::appendNrGapStop(uint32_t nrGapStop)
{
    insertNrGapStop(nrGapStop_arraysize, nrGapStop);
}

void SctpSackChunk::eraseNrGapStop(size_t k)
{
    if (k >= nrGapStop_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nrGapStop_arraysize, (unsigned long)k);
    size_t newSize = nrGapStop_arraysize - 1;
    uint32_t *nrGapStop2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nrGapStop2[i] = this->nrGapStop[i];
    for (i = k; i < newSize; i++)
        nrGapStop2[i] = this->nrGapStop[i+1];
    delete [] this->nrGapStop;
    this->nrGapStop = nrGapStop2;
    nrGapStop_arraysize = newSize;
}

uint32_t SctpSackChunk::getMsg_rwnd() const
{
    return this->msg_rwnd;
}

void SctpSackChunk::setMsg_rwnd(uint32_t msg_rwnd)
{
    this->msg_rwnd = msg_rwnd;
}

uint8_t SctpSackChunk::getDacPacketsRcvd() const
{
    return this->dacPacketsRcvd;
}

void SctpSackChunk::setDacPacketsRcvd(uint8_t dacPacketsRcvd)
{
    this->dacPacketsRcvd = dacPacketsRcvd;
}

bool SctpSackChunk::getNrSubtractRGaps() const
{
    return this->nrSubtractRGaps;
}

void SctpSackChunk::setNrSubtractRGaps(bool nrSubtractRGaps)
{
    this->nrSubtractRGaps = nrSubtractRGaps;
}

class SctpSackChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cumTsnAck,
        FIELD_a_rwnd,
        FIELD_numGaps,
        FIELD_numNrGaps,
        FIELD_numDupTsns,
        FIELD_isNrSack,
        FIELD_gapStart,
        FIELD_gapStop,
        FIELD_dupTsns,
        FIELD_sackSeqNum,
        FIELD_nrGapStart,
        FIELD_nrGapStop,
        FIELD_msg_rwnd,
        FIELD_dacPacketsRcvd,
        FIELD_nrSubtractRGaps,
    };
  public:
    SctpSackChunkDescriptor();
    virtual ~SctpSackChunkDescriptor();

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

Register_ClassDescriptor(SctpSackChunkDescriptor)

SctpSackChunkDescriptor::SctpSackChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSackChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpSackChunkDescriptor::~SctpSackChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpSackChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSackChunk *>(obj)!=nullptr;
}

const char **SctpSackChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSackChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSackChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 15+base->getFieldCount() : 15;
}

unsigned int SctpSackChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cumTsnAck
        FD_ISEDITABLE,    // FIELD_a_rwnd
        FD_ISEDITABLE,    // FIELD_numGaps
        FD_ISEDITABLE,    // FIELD_numNrGaps
        FD_ISEDITABLE,    // FIELD_numDupTsns
        FD_ISEDITABLE,    // FIELD_isNrSack
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_gapStart
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_gapStop
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_dupTsns
        FD_ISEDITABLE,    // FIELD_sackSeqNum
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_nrGapStart
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_nrGapStop
        FD_ISEDITABLE,    // FIELD_msg_rwnd
        FD_ISEDITABLE,    // FIELD_dacPacketsRcvd
        FD_ISEDITABLE,    // FIELD_nrSubtractRGaps
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
}

const char *SctpSackChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cumTsnAck",
        "a_rwnd",
        "numGaps",
        "numNrGaps",
        "numDupTsns",
        "isNrSack",
        "gapStart",
        "gapStop",
        "dupTsns",
        "sackSeqNum",
        "nrGapStart",
        "nrGapStop",
        "msg_rwnd",
        "dacPacketsRcvd",
        "nrSubtractRGaps",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int SctpSackChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cumTsnAck") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "a_rwnd") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "numGaps") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "numNrGaps") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "numDupTsns") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "isNrSack") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "gapStart") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "gapStop") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "dupTsns") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "sackSeqNum") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "nrGapStart") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "nrGapStop") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "msg_rwnd") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "dacPacketsRcvd") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "nrSubtractRGaps") == 0) return baseIndex + 14;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSackChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_cumTsnAck
        "uint32_t",    // FIELD_a_rwnd
        "uint16_t",    // FIELD_numGaps
        "uint16_t",    // FIELD_numNrGaps
        "uint16_t",    // FIELD_numDupTsns
        "bool",    // FIELD_isNrSack
        "uint32_t",    // FIELD_gapStart
        "uint32_t",    // FIELD_gapStop
        "uint32_t",    // FIELD_dupTsns
        "uint32_t",    // FIELD_sackSeqNum
        "uint32_t",    // FIELD_nrGapStart
        "uint32_t",    // FIELD_nrGapStop
        "uint32_t",    // FIELD_msg_rwnd
        "uint8_t",    // FIELD_dacPacketsRcvd
        "bool",    // FIELD_nrSubtractRGaps
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSackChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSackChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSackChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_gapStart: return pp->getGapStartArraySize();
        case FIELD_gapStop: return pp->getGapStopArraySize();
        case FIELD_dupTsns: return pp->getDupTsnsArraySize();
        case FIELD_nrGapStart: return pp->getNrGapStartArraySize();
        case FIELD_nrGapStop: return pp->getNrGapStopArraySize();
        default: return 0;
    }
}

void SctpSackChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_gapStart: pp->setGapStartArraySize(size); break;
        case FIELD_gapStop: pp->setGapStopArraySize(size); break;
        case FIELD_dupTsns: pp->setDupTsnsArraySize(size); break;
        case FIELD_nrGapStart: pp->setNrGapStartArraySize(size); break;
        case FIELD_nrGapStop: pp->setNrGapStopArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSackChunk'", field);
    }
}

const char *SctpSackChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSackChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: return ulong2string(pp->getCumTsnAck());
        case FIELD_a_rwnd: return ulong2string(pp->getA_rwnd());
        case FIELD_numGaps: return ulong2string(pp->getNumGaps());
        case FIELD_numNrGaps: return ulong2string(pp->getNumNrGaps());
        case FIELD_numDupTsns: return ulong2string(pp->getNumDupTsns());
        case FIELD_isNrSack: return bool2string(pp->isNrSack());
        case FIELD_gapStart: return ulong2string(pp->getGapStart(i));
        case FIELD_gapStop: return ulong2string(pp->getGapStop(i));
        case FIELD_dupTsns: return ulong2string(pp->getDupTsns(i));
        case FIELD_sackSeqNum: return ulong2string(pp->getSackSeqNum());
        case FIELD_nrGapStart: return ulong2string(pp->getNrGapStart(i));
        case FIELD_nrGapStop: return ulong2string(pp->getNrGapStop(i));
        case FIELD_msg_rwnd: return ulong2string(pp->getMsg_rwnd());
        case FIELD_dacPacketsRcvd: return ulong2string(pp->getDacPacketsRcvd());
        case FIELD_nrSubtractRGaps: return bool2string(pp->getNrSubtractRGaps());
        default: return "";
    }
}

void SctpSackChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: pp->setCumTsnAck(string2ulong(value)); break;
        case FIELD_a_rwnd: pp->setA_rwnd(string2ulong(value)); break;
        case FIELD_numGaps: pp->setNumGaps(string2ulong(value)); break;
        case FIELD_numNrGaps: pp->setNumNrGaps(string2ulong(value)); break;
        case FIELD_numDupTsns: pp->setNumDupTsns(string2ulong(value)); break;
        case FIELD_isNrSack: pp->setIsNrSack(string2bool(value)); break;
        case FIELD_gapStart: pp->setGapStart(i,string2ulong(value)); break;
        case FIELD_gapStop: pp->setGapStop(i,string2ulong(value)); break;
        case FIELD_dupTsns: pp->setDupTsns(i,string2ulong(value)); break;
        case FIELD_sackSeqNum: pp->setSackSeqNum(string2ulong(value)); break;
        case FIELD_nrGapStart: pp->setNrGapStart(i,string2ulong(value)); break;
        case FIELD_nrGapStop: pp->setNrGapStop(i,string2ulong(value)); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(string2ulong(value)); break;
        case FIELD_dacPacketsRcvd: pp->setDacPacketsRcvd(string2ulong(value)); break;
        case FIELD_nrSubtractRGaps: pp->setNrSubtractRGaps(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSackChunk'", field);
    }
}

omnetpp::cValue SctpSackChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: return (omnetpp::intval_t)(pp->getCumTsnAck());
        case FIELD_a_rwnd: return (omnetpp::intval_t)(pp->getA_rwnd());
        case FIELD_numGaps: return (omnetpp::intval_t)(pp->getNumGaps());
        case FIELD_numNrGaps: return (omnetpp::intval_t)(pp->getNumNrGaps());
        case FIELD_numDupTsns: return (omnetpp::intval_t)(pp->getNumDupTsns());
        case FIELD_isNrSack: return pp->isNrSack();
        case FIELD_gapStart: return (omnetpp::intval_t)(pp->getGapStart(i));
        case FIELD_gapStop: return (omnetpp::intval_t)(pp->getGapStop(i));
        case FIELD_dupTsns: return (omnetpp::intval_t)(pp->getDupTsns(i));
        case FIELD_sackSeqNum: return (omnetpp::intval_t)(pp->getSackSeqNum());
        case FIELD_nrGapStart: return (omnetpp::intval_t)(pp->getNrGapStart(i));
        case FIELD_nrGapStop: return (omnetpp::intval_t)(pp->getNrGapStop(i));
        case FIELD_msg_rwnd: return (omnetpp::intval_t)(pp->getMsg_rwnd());
        case FIELD_dacPacketsRcvd: return (omnetpp::intval_t)(pp->getDacPacketsRcvd());
        case FIELD_nrSubtractRGaps: return pp->getNrSubtractRGaps();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSackChunk' as cValue -- field index out of range?", field);
    }
}

void SctpSackChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: pp->setCumTsnAck(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_a_rwnd: pp->setA_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_numGaps: pp->setNumGaps(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_numNrGaps: pp->setNumNrGaps(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_numDupTsns: pp->setNumDupTsns(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_isNrSack: pp->setIsNrSack(value.boolValue()); break;
        case FIELD_gapStart: pp->setGapStart(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_gapStop: pp->setGapStop(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dupTsns: pp->setDupTsns(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sackSeqNum: pp->setSackSeqNum(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_nrGapStart: pp->setNrGapStart(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_nrGapStop: pp->setNrGapStop(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_msg_rwnd: pp->setMsg_rwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_dacPacketsRcvd: pp->setDacPacketsRcvd(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_nrSubtractRGaps: pp->setNrSubtractRGaps(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSackChunk'", field);
    }
}

const char *SctpSackChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSackChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSackChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSackChunk *pp = omnetpp::fromAnyPtr<SctpSackChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSackChunk'", field);
    }
}

Register_Class(SctpAbortChunk)

SctpAbortChunk::SctpAbortChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpAbortChunk::SctpAbortChunk(const SctpAbortChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpAbortChunk::~SctpAbortChunk()
{
}

SctpAbortChunk& SctpAbortChunk::operator=(const SctpAbortChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpAbortChunk::copy(const SctpAbortChunk& other)
{
    this->T_Bit = other.T_Bit;
}

void SctpAbortChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->T_Bit);
}

void SctpAbortChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->T_Bit);
}

bool SctpAbortChunk::getT_Bit() const
{
    return this->T_Bit;
}

void SctpAbortChunk::setT_Bit(bool T_Bit)
{
    this->T_Bit = T_Bit;
}

class SctpAbortChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_T_Bit,
    };
  public:
    SctpAbortChunkDescriptor();
    virtual ~SctpAbortChunkDescriptor();

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

Register_ClassDescriptor(SctpAbortChunkDescriptor)

SctpAbortChunkDescriptor::SctpAbortChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpAbortChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpAbortChunkDescriptor::~SctpAbortChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpAbortChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAbortChunk *>(obj)!=nullptr;
}

const char **SctpAbortChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAbortChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAbortChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpAbortChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_T_Bit
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpAbortChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "T_Bit",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpAbortChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "T_Bit") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAbortChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_T_Bit
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAbortChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAbortChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAbortChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpAbortChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAbortChunk'", field);
    }
}

const char *SctpAbortChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpAbortChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        case FIELD_T_Bit: return bool2string(pp->getT_Bit());
        default: return "";
    }
}

void SctpAbortChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        case FIELD_T_Bit: pp->setT_Bit(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAbortChunk'", field);
    }
}

omnetpp::cValue SctpAbortChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        case FIELD_T_Bit: return pp->getT_Bit();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAbortChunk' as cValue -- field index out of range?", field);
    }
}

void SctpAbortChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        case FIELD_T_Bit: pp->setT_Bit(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAbortChunk'", field);
    }
}

const char *SctpAbortChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpAbortChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAbortChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAbortChunk *pp = omnetpp::fromAnyPtr<SctpAbortChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAbortChunk'", field);
    }
}

Register_Class(SctpHeartbeatChunk)

SctpHeartbeatChunk::SctpHeartbeatChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpHeartbeatChunk::SctpHeartbeatChunk(const SctpHeartbeatChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpHeartbeatChunk::~SctpHeartbeatChunk()
{
    delete [] this->info;
}

SctpHeartbeatChunk& SctpHeartbeatChunk::operator=(const SctpHeartbeatChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpHeartbeatChunk::copy(const SctpHeartbeatChunk& other)
{
    this->remoteAddr = other.remoteAddr;
    this->timeField = other.timeField;
    delete [] this->info;
    this->info = (other.info_arraysize==0) ? nullptr : new char[other.info_arraysize];
    info_arraysize = other.info_arraysize;
    for (size_t i = 0; i < info_arraysize; i++) {
        this->info[i] = other.info[i];
    }
}

void SctpHeartbeatChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->timeField);
    b->pack(info_arraysize);
    doParsimArrayPacking(b,this->info,info_arraysize);
}

void SctpHeartbeatChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->timeField);
    delete [] this->info;
    b->unpack(info_arraysize);
    if (info_arraysize == 0) {
        this->info = nullptr;
    } else {
        this->info = new char[info_arraysize];
        doParsimArrayUnpacking(b,this->info,info_arraysize);
    }
}

const ::inet::L3Address& SctpHeartbeatChunk::getRemoteAddr() const
{
    return this->remoteAddr;
}

void SctpHeartbeatChunk::setRemoteAddr(const ::inet::L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

::omnetpp::simtime_t SctpHeartbeatChunk::getTimeField() const
{
    return this->timeField;
}

void SctpHeartbeatChunk::setTimeField(::omnetpp::simtime_t timeField)
{
    this->timeField = timeField;
}

size_t SctpHeartbeatChunk::getInfoArraySize() const
{
    return info_arraysize;
}

char SctpHeartbeatChunk::getInfo(size_t k) const
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    return this->info[k];
}

void SctpHeartbeatChunk::setInfoArraySize(size_t newSize)
{
    char *info2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = info_arraysize < newSize ? info_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        info2[i] = this->info[i];
    for (size_t i = minSize; i < newSize; i++)
        info2[i] = 0;
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

void SctpHeartbeatChunk::setInfo(size_t k, char info)
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    this->info[k] = info;
}

void SctpHeartbeatChunk::insertInfo(size_t k, char info)
{
    if (k > info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    size_t newSize = info_arraysize + 1;
    char *info2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        info2[i] = this->info[i];
    info2[k] = info;
    for (i = k + 1; i < newSize; i++)
        info2[i] = this->info[i-1];
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

void SctpHeartbeatChunk::appendInfo(char info)
{
    insertInfo(info_arraysize, info);
}

void SctpHeartbeatChunk::eraseInfo(size_t k)
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    size_t newSize = info_arraysize - 1;
    char *info2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        info2[i] = this->info[i];
    for (i = k; i < newSize; i++)
        info2[i] = this->info[i+1];
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

class SctpHeartbeatChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddr,
        FIELD_timeField,
        FIELD_info,
    };
  public:
    SctpHeartbeatChunkDescriptor();
    virtual ~SctpHeartbeatChunkDescriptor();

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

Register_ClassDescriptor(SctpHeartbeatChunkDescriptor)

SctpHeartbeatChunkDescriptor::SctpHeartbeatChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpHeartbeatChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpHeartbeatChunkDescriptor::~SctpHeartbeatChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpHeartbeatChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpHeartbeatChunk *>(obj)!=nullptr;
}

const char **SctpHeartbeatChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpHeartbeatChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpHeartbeatChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpHeartbeatChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_timeField
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_info
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpHeartbeatChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddr",
        "timeField",
        "info",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpHeartbeatChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timeField") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "info") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpHeartbeatChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_remoteAddr
        "omnetpp::simtime_t",    // FIELD_timeField
        "char",    // FIELD_info
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpHeartbeatChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpHeartbeatChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpHeartbeatChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_info: return pp->getInfoArraySize();
        default: return 0;
    }
}

void SctpHeartbeatChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_info: pp->setInfoArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpHeartbeatChunk'", field);
    }
}

const char *SctpHeartbeatChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpHeartbeatChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_timeField: return simtime2string(pp->getTimeField());
        case FIELD_info: return long2string(pp->getInfo(i));
        default: return "";
    }
}

void SctpHeartbeatChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_timeField: pp->setTimeField(string2simtime(value)); break;
        case FIELD_info: pp->setInfo(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatChunk'", field);
    }
}

omnetpp::cValue SctpHeartbeatChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_timeField: return pp->getTimeField().dbl();
        case FIELD_info: return pp->getInfo(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpHeartbeatChunk' as cValue -- field index out of range?", field);
    }
}

void SctpHeartbeatChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_timeField: pp->setTimeField(value.doubleValue()); break;
        case FIELD_info: pp->setInfo(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatChunk'", field);
    }
}

const char *SctpHeartbeatChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpHeartbeatChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpHeartbeatChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatChunk'", field);
    }
}

Register_Class(SctpHeartbeatAckChunk)

SctpHeartbeatAckChunk::SctpHeartbeatAckChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpHeartbeatAckChunk::SctpHeartbeatAckChunk(const SctpHeartbeatAckChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpHeartbeatAckChunk::~SctpHeartbeatAckChunk()
{
    delete [] this->info;
}

SctpHeartbeatAckChunk& SctpHeartbeatAckChunk::operator=(const SctpHeartbeatAckChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpHeartbeatAckChunk::copy(const SctpHeartbeatAckChunk& other)
{
    this->remoteAddr = other.remoteAddr;
    this->timeField = other.timeField;
    delete [] this->info;
    this->info = (other.info_arraysize==0) ? nullptr : new char[other.info_arraysize];
    info_arraysize = other.info_arraysize;
    for (size_t i = 0; i < info_arraysize; i++) {
        this->info[i] = other.info[i];
    }
}

void SctpHeartbeatAckChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->remoteAddr);
    doParsimPacking(b,this->timeField);
    b->pack(info_arraysize);
    doParsimArrayPacking(b,this->info,info_arraysize);
}

void SctpHeartbeatAckChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->remoteAddr);
    doParsimUnpacking(b,this->timeField);
    delete [] this->info;
    b->unpack(info_arraysize);
    if (info_arraysize == 0) {
        this->info = nullptr;
    } else {
        this->info = new char[info_arraysize];
        doParsimArrayUnpacking(b,this->info,info_arraysize);
    }
}

const ::inet::L3Address& SctpHeartbeatAckChunk::getRemoteAddr() const
{
    return this->remoteAddr;
}

void SctpHeartbeatAckChunk::setRemoteAddr(const ::inet::L3Address& remoteAddr)
{
    this->remoteAddr = remoteAddr;
}

::omnetpp::simtime_t SctpHeartbeatAckChunk::getTimeField() const
{
    return this->timeField;
}

void SctpHeartbeatAckChunk::setTimeField(::omnetpp::simtime_t timeField)
{
    this->timeField = timeField;
}

size_t SctpHeartbeatAckChunk::getInfoArraySize() const
{
    return info_arraysize;
}

char SctpHeartbeatAckChunk::getInfo(size_t k) const
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    return this->info[k];
}

void SctpHeartbeatAckChunk::setInfoArraySize(size_t newSize)
{
    char *info2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = info_arraysize < newSize ? info_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        info2[i] = this->info[i];
    for (size_t i = minSize; i < newSize; i++)
        info2[i] = 0;
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

void SctpHeartbeatAckChunk::setInfo(size_t k, char info)
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    this->info[k] = info;
}

void SctpHeartbeatAckChunk::insertInfo(size_t k, char info)
{
    if (k > info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    size_t newSize = info_arraysize + 1;
    char *info2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        info2[i] = this->info[i];
    info2[k] = info;
    for (i = k + 1; i < newSize; i++)
        info2[i] = this->info[i-1];
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

void SctpHeartbeatAckChunk::appendInfo(char info)
{
    insertInfo(info_arraysize, info);
}

void SctpHeartbeatAckChunk::eraseInfo(size_t k)
{
    if (k >= info_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)info_arraysize, (unsigned long)k);
    size_t newSize = info_arraysize - 1;
    char *info2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        info2[i] = this->info[i];
    for (i = k; i < newSize; i++)
        info2[i] = this->info[i+1];
    delete [] this->info;
    this->info = info2;
    info_arraysize = newSize;
}

class SctpHeartbeatAckChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_remoteAddr,
        FIELD_timeField,
        FIELD_info,
    };
  public:
    SctpHeartbeatAckChunkDescriptor();
    virtual ~SctpHeartbeatAckChunkDescriptor();

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

Register_ClassDescriptor(SctpHeartbeatAckChunkDescriptor)

SctpHeartbeatAckChunkDescriptor::SctpHeartbeatAckChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpHeartbeatAckChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpHeartbeatAckChunkDescriptor::~SctpHeartbeatAckChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpHeartbeatAckChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpHeartbeatAckChunk *>(obj)!=nullptr;
}

const char **SctpHeartbeatAckChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpHeartbeatAckChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpHeartbeatAckChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpHeartbeatAckChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_remoteAddr
        FD_ISEDITABLE,    // FIELD_timeField
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_info
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpHeartbeatAckChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "remoteAddr",
        "timeField",
        "info",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpHeartbeatAckChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timeField") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "info") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpHeartbeatAckChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_remoteAddr
        "omnetpp::simtime_t",    // FIELD_timeField
        "char",    // FIELD_info
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpHeartbeatAckChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpHeartbeatAckChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpHeartbeatAckChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_info: return pp->getInfoArraySize();
        default: return 0;
    }
}

void SctpHeartbeatAckChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_info: pp->setInfoArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpHeartbeatAckChunk'", field);
    }
}

const char *SctpHeartbeatAckChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpHeartbeatAckChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_timeField: return simtime2string(pp->getTimeField());
        case FIELD_info: return long2string(pp->getInfo(i));
        default: return "";
    }
}

void SctpHeartbeatAckChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_timeField: pp->setTimeField(string2simtime(value)); break;
        case FIELD_info: pp->setInfo(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatAckChunk'", field);
    }
}

omnetpp::cValue SctpHeartbeatAckChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_timeField: return pp->getTimeField().dbl();
        case FIELD_info: return pp->getInfo(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpHeartbeatAckChunk' as cValue -- field index out of range?", field);
    }
}

void SctpHeartbeatAckChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_timeField: pp->setTimeField(value.doubleValue()); break;
        case FIELD_info: pp->setInfo(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatAckChunk'", field);
    }
}

const char *SctpHeartbeatAckChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpHeartbeatAckChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpHeartbeatAckChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpHeartbeatAckChunk *pp = omnetpp::fromAnyPtr<SctpHeartbeatAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpHeartbeatAckChunk'", field);
    }
}

Register_Class(SctpShutdownChunk)

SctpShutdownChunk::SctpShutdownChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpShutdownChunk::SctpShutdownChunk(const SctpShutdownChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpShutdownChunk::~SctpShutdownChunk()
{
}

SctpShutdownChunk& SctpShutdownChunk::operator=(const SctpShutdownChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpShutdownChunk::copy(const SctpShutdownChunk& other)
{
    this->cumTsnAck = other.cumTsnAck;
}

void SctpShutdownChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->cumTsnAck);
}

void SctpShutdownChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->cumTsnAck);
}

uint32_t SctpShutdownChunk::getCumTsnAck() const
{
    return this->cumTsnAck;
}

void SctpShutdownChunk::setCumTsnAck(uint32_t cumTsnAck)
{
    this->cumTsnAck = cumTsnAck;
}

class SctpShutdownChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cumTsnAck,
    };
  public:
    SctpShutdownChunkDescriptor();
    virtual ~SctpShutdownChunkDescriptor();

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

Register_ClassDescriptor(SctpShutdownChunkDescriptor)

SctpShutdownChunkDescriptor::SctpShutdownChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpShutdownChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpShutdownChunkDescriptor::~SctpShutdownChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpShutdownChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpShutdownChunk *>(obj)!=nullptr;
}

const char **SctpShutdownChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpShutdownChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpShutdownChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpShutdownChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cumTsnAck
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpShutdownChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cumTsnAck",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpShutdownChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cumTsnAck") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpShutdownChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_cumTsnAck
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpShutdownChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpShutdownChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpShutdownChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpShutdownChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpShutdownChunk'", field);
    }
}

const char *SctpShutdownChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpShutdownChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: return ulong2string(pp->getCumTsnAck());
        default: return "";
    }
}

void SctpShutdownChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: pp->setCumTsnAck(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownChunk'", field);
    }
}

omnetpp::cValue SctpShutdownChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: return (omnetpp::intval_t)(pp->getCumTsnAck());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpShutdownChunk' as cValue -- field index out of range?", field);
    }
}

void SctpShutdownChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cumTsnAck: pp->setCumTsnAck(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownChunk'", field);
    }
}

const char *SctpShutdownChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpShutdownChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpShutdownChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownChunk *pp = omnetpp::fromAnyPtr<SctpShutdownChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownChunk'", field);
    }
}

Register_Class(SctpShutdownAckChunk)

SctpShutdownAckChunk::SctpShutdownAckChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpShutdownAckChunk::SctpShutdownAckChunk(const SctpShutdownAckChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpShutdownAckChunk::~SctpShutdownAckChunk()
{
}

SctpShutdownAckChunk& SctpShutdownAckChunk::operator=(const SctpShutdownAckChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpShutdownAckChunk::copy(const SctpShutdownAckChunk& other)
{
}

void SctpShutdownAckChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
}

void SctpShutdownAckChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
}

class SctpShutdownAckChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SctpShutdownAckChunkDescriptor();
    virtual ~SctpShutdownAckChunkDescriptor();

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

Register_ClassDescriptor(SctpShutdownAckChunkDescriptor)

SctpShutdownAckChunkDescriptor::SctpShutdownAckChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpShutdownAckChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpShutdownAckChunkDescriptor::~SctpShutdownAckChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpShutdownAckChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpShutdownAckChunk *>(obj)!=nullptr;
}

const char **SctpShutdownAckChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpShutdownAckChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpShutdownAckChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SctpShutdownAckChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SctpShutdownAckChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SctpShutdownAckChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SctpShutdownAckChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SctpShutdownAckChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpShutdownAckChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpShutdownAckChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpShutdownAckChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpShutdownAckChunk'", field);
    }
}

const char *SctpShutdownAckChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpShutdownAckChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SctpShutdownAckChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownAckChunk'", field);
    }
}

omnetpp::cValue SctpShutdownAckChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpShutdownAckChunk' as cValue -- field index out of range?", field);
    }
}

void SctpShutdownAckChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownAckChunk'", field);
    }
}

const char *SctpShutdownAckChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SctpShutdownAckChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpShutdownAckChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownAckChunk *pp = omnetpp::fromAnyPtr<SctpShutdownAckChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownAckChunk'", field);
    }
}

Register_Class(SctpShutdownCompleteChunk)

SctpShutdownCompleteChunk::SctpShutdownCompleteChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpShutdownCompleteChunk::SctpShutdownCompleteChunk(const SctpShutdownCompleteChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpShutdownCompleteChunk::~SctpShutdownCompleteChunk()
{
}

SctpShutdownCompleteChunk& SctpShutdownCompleteChunk::operator=(const SctpShutdownCompleteChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpShutdownCompleteChunk::copy(const SctpShutdownCompleteChunk& other)
{
    this->TBit = other.TBit;
}

void SctpShutdownCompleteChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->TBit);
}

void SctpShutdownCompleteChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->TBit);
}

bool SctpShutdownCompleteChunk::getTBit() const
{
    return this->TBit;
}

void SctpShutdownCompleteChunk::setTBit(bool TBit)
{
    this->TBit = TBit;
}

class SctpShutdownCompleteChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_TBit,
    };
  public:
    SctpShutdownCompleteChunkDescriptor();
    virtual ~SctpShutdownCompleteChunkDescriptor();

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

Register_ClassDescriptor(SctpShutdownCompleteChunkDescriptor)

SctpShutdownCompleteChunkDescriptor::SctpShutdownCompleteChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpShutdownCompleteChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpShutdownCompleteChunkDescriptor::~SctpShutdownCompleteChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpShutdownCompleteChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpShutdownCompleteChunk *>(obj)!=nullptr;
}

const char **SctpShutdownCompleteChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpShutdownCompleteChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpShutdownCompleteChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpShutdownCompleteChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_TBit
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpShutdownCompleteChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "TBit",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpShutdownCompleteChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "TBit") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpShutdownCompleteChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_TBit
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpShutdownCompleteChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpShutdownCompleteChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpShutdownCompleteChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpShutdownCompleteChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpShutdownCompleteChunk'", field);
    }
}

const char *SctpShutdownCompleteChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpShutdownCompleteChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: return bool2string(pp->getTBit());
        default: return "";
    }
}

void SctpShutdownCompleteChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: pp->setTBit(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownCompleteChunk'", field);
    }
}

omnetpp::cValue SctpShutdownCompleteChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: return pp->getTBit();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpShutdownCompleteChunk' as cValue -- field index out of range?", field);
    }
}

void SctpShutdownCompleteChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: pp->setTBit(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownCompleteChunk'", field);
    }
}

const char *SctpShutdownCompleteChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpShutdownCompleteChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpShutdownCompleteChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpShutdownCompleteChunk *pp = omnetpp::fromAnyPtr<SctpShutdownCompleteChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpShutdownCompleteChunk'", field);
    }
}

SctpErrorChunk_Base::SctpErrorChunk_Base(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpErrorChunk_Base::SctpErrorChunk_Base(const SctpErrorChunk_Base& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpErrorChunk_Base::~SctpErrorChunk_Base()
{
}

SctpErrorChunk_Base& SctpErrorChunk_Base::operator=(const SctpErrorChunk_Base& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpErrorChunk_Base::copy(const SctpErrorChunk_Base& other)
{
    this->TBit = other.TBit;
    this->MBit = other.MBit;
}

void SctpErrorChunk_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->TBit);
    doParsimPacking(b,this->MBit);
    // field parameters is abstract or custom -- please do packing in customized class
}

void SctpErrorChunk_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->TBit);
    doParsimUnpacking(b,this->MBit);
    // field parameters is abstract or custom -- please do unpacking in customized class
}

bool SctpErrorChunk_Base::getTBit() const
{
    return this->TBit;
}

void SctpErrorChunk_Base::setTBit(bool TBit)
{
    this->TBit = TBit;
}

bool SctpErrorChunk_Base::getMBit() const
{
    return this->MBit;
}

void SctpErrorChunk_Base::setMBit(bool MBit)
{
    this->MBit = MBit;
}

class SctpErrorChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_TBit,
        FIELD_MBit,
        FIELD_parameters,
    };
  public:
    SctpErrorChunkDescriptor();
    virtual ~SctpErrorChunkDescriptor();

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

Register_ClassDescriptor(SctpErrorChunkDescriptor)

SctpErrorChunkDescriptor::SctpErrorChunkDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpErrorChunk", "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpErrorChunkDescriptor::~SctpErrorChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpErrorChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpErrorChunk_Base *>(obj)!=nullptr;
}

const char **SctpErrorChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpErrorChunkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpErrorChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpErrorChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_TBit
        FD_ISEDITABLE,    // FIELD_MBit
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_parameters
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpErrorChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "TBit",
        "MBit",
        "parameters",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpErrorChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "TBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "MBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "parameters") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpErrorChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_TBit
        "bool",    // FIELD_MBit
        "inet::sctp::SctpParameter",    // FIELD_parameters
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpErrorChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpErrorChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpErrorChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: return pp->getParametersArraySize();
        default: return 0;
    }
}

void SctpErrorChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: pp->setParametersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpErrorChunk_Base'", field);
    }
}

const char *SctpErrorChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: { const SctpParameter * value = pp->getParameters(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpErrorChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: return bool2string(pp->getTBit());
        case FIELD_MBit: return bool2string(pp->getMBit());
        case FIELD_parameters: { auto obj = pp->getParameters(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void SctpErrorChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: pp->setTBit(string2bool(value)); break;
        case FIELD_MBit: pp->setMBit(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorChunk_Base'", field);
    }
}

omnetpp::cValue SctpErrorChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: return pp->getTBit();
        case FIELD_MBit: return pp->getMBit();
        case FIELD_parameters: return omnetpp::toAnyPtr(pp->getParameters(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpErrorChunk_Base' as cValue -- field index out of range?", field);
    }
}

void SctpErrorChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_TBit: pp->setTBit(value.boolValue()); break;
        case FIELD_MBit: pp->setMBit(value.boolValue()); break;
        case FIELD_parameters: pp->setParameters(i,omnetpp::fromAnyPtr<SctpParameter>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorChunk_Base'", field);
    }
}

const char *SctpErrorChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_parameters: return omnetpp::opp_typename(typeid(SctpParameter));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpErrorChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: return omnetpp::toAnyPtr(pp->getParameters(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpErrorChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorChunk_Base *pp = omnetpp::fromAnyPtr<SctpErrorChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: pp->setParameters(i,omnetpp::fromAnyPtr<SctpParameter>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorChunk_Base'", field);
    }
}

Register_Class(SctpParameter)

SctpParameter::SctpParameter(const char *name) : ::omnetpp::cPacket(name)
{
}

SctpParameter::SctpParameter(const SctpParameter& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SctpParameter::~SctpParameter()
{
}

SctpParameter& SctpParameter::operator=(const SctpParameter& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SctpParameter::copy(const SctpParameter& other)
{
    this->parameterType = other.parameterType;
}

void SctpParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->parameterType);
}

void SctpParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->parameterType);
}

uint16_t SctpParameter::getParameterType() const
{
    return this->parameterType;
}

void SctpParameter::setParameterType(uint16_t parameterType)
{
    this->parameterType = parameterType;
}

class SctpParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_parameterType,
    };
  public:
    SctpParameterDescriptor();
    virtual ~SctpParameterDescriptor();

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

Register_ClassDescriptor(SctpParameterDescriptor)

SctpParameterDescriptor::SctpParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpParameter)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SctpParameterDescriptor::~SctpParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpParameter *>(obj)!=nullptr;
}

const char **SctpParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpParameterDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_parameterType
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "parameterType",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "parameterType") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_parameterType
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpParameter'", field);
    }
}

const char *SctpParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: return ulong2string(pp->getParameterType());
        default: return "";
    }
}

void SctpParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: pp->setParameterType(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpParameter'", field);
    }
}

omnetpp::cValue SctpParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: return (omnetpp::intval_t)(pp->getParameterType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpParameter' as cValue -- field index out of range?", field);
    }
}

void SctpParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: pp->setParameterType(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpParameter'", field);
    }
}

const char *SctpParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpParameter *pp = omnetpp::fromAnyPtr<SctpParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpParameter'", field);
    }
}

Register_Class(SctpPacketDropChunk)

SctpPacketDropChunk::SctpPacketDropChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpPacketDropChunk::SctpPacketDropChunk(const SctpPacketDropChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpPacketDropChunk::~SctpPacketDropChunk()
{
}

SctpPacketDropChunk& SctpPacketDropChunk::operator=(const SctpPacketDropChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpPacketDropChunk::copy(const SctpPacketDropChunk& other)
{
    this->cFlag = other.cFlag;
    this->tFlag = other.tFlag;
    this->bFlag = other.bFlag;
    this->mFlag = other.mFlag;
    this->maxRwnd = other.maxRwnd;
    this->queuedData = other.queuedData;
    this->truncLength = other.truncLength;
}

void SctpPacketDropChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->cFlag);
    doParsimPacking(b,this->tFlag);
    doParsimPacking(b,this->bFlag);
    doParsimPacking(b,this->mFlag);
    doParsimPacking(b,this->maxRwnd);
    doParsimPacking(b,this->queuedData);
    doParsimPacking(b,this->truncLength);
}

void SctpPacketDropChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->cFlag);
    doParsimUnpacking(b,this->tFlag);
    doParsimUnpacking(b,this->bFlag);
    doParsimUnpacking(b,this->mFlag);
    doParsimUnpacking(b,this->maxRwnd);
    doParsimUnpacking(b,this->queuedData);
    doParsimUnpacking(b,this->truncLength);
}

bool SctpPacketDropChunk::getCFlag() const
{
    return this->cFlag;
}

void SctpPacketDropChunk::setCFlag(bool cFlag)
{
    this->cFlag = cFlag;
}

bool SctpPacketDropChunk::getTFlag() const
{
    return this->tFlag;
}

void SctpPacketDropChunk::setTFlag(bool tFlag)
{
    this->tFlag = tFlag;
}

bool SctpPacketDropChunk::getBFlag() const
{
    return this->bFlag;
}

void SctpPacketDropChunk::setBFlag(bool bFlag)
{
    this->bFlag = bFlag;
}

bool SctpPacketDropChunk::getMFlag() const
{
    return this->mFlag;
}

void SctpPacketDropChunk::setMFlag(bool mFlag)
{
    this->mFlag = mFlag;
}

uint32_t SctpPacketDropChunk::getMaxRwnd() const
{
    return this->maxRwnd;
}

void SctpPacketDropChunk::setMaxRwnd(uint32_t maxRwnd)
{
    this->maxRwnd = maxRwnd;
}

uint32_t SctpPacketDropChunk::getQueuedData() const
{
    return this->queuedData;
}

void SctpPacketDropChunk::setQueuedData(uint32_t queuedData)
{
    this->queuedData = queuedData;
}

uint16_t SctpPacketDropChunk::getTruncLength() const
{
    return this->truncLength;
}

void SctpPacketDropChunk::setTruncLength(uint16_t truncLength)
{
    this->truncLength = truncLength;
}

class SctpPacketDropChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cFlag,
        FIELD_tFlag,
        FIELD_bFlag,
        FIELD_mFlag,
        FIELD_maxRwnd,
        FIELD_queuedData,
        FIELD_truncLength,
    };
  public:
    SctpPacketDropChunkDescriptor();
    virtual ~SctpPacketDropChunkDescriptor();

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

Register_ClassDescriptor(SctpPacketDropChunkDescriptor)

SctpPacketDropChunkDescriptor::SctpPacketDropChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpPacketDropChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpPacketDropChunkDescriptor::~SctpPacketDropChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpPacketDropChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpPacketDropChunk *>(obj)!=nullptr;
}

const char **SctpPacketDropChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpPacketDropChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpPacketDropChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int SctpPacketDropChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cFlag
        FD_ISEDITABLE,    // FIELD_tFlag
        FD_ISEDITABLE,    // FIELD_bFlag
        FD_ISEDITABLE,    // FIELD_mFlag
        FD_ISEDITABLE,    // FIELD_maxRwnd
        FD_ISEDITABLE,    // FIELD_queuedData
        FD_ISEDITABLE,    // FIELD_truncLength
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *SctpPacketDropChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cFlag",
        "tFlag",
        "bFlag",
        "mFlag",
        "maxRwnd",
        "queuedData",
        "truncLength",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int SctpPacketDropChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cFlag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "tFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "bFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "mFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "maxRwnd") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "queuedData") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "truncLength") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpPacketDropChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_cFlag
        "bool",    // FIELD_tFlag
        "bool",    // FIELD_bFlag
        "bool",    // FIELD_mFlag
        "uint32_t",    // FIELD_maxRwnd
        "uint32_t",    // FIELD_queuedData
        "uint16_t",    // FIELD_truncLength
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpPacketDropChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpPacketDropChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpPacketDropChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpPacketDropChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpPacketDropChunk'", field);
    }
}

const char *SctpPacketDropChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpPacketDropChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cFlag: return bool2string(pp->getCFlag());
        case FIELD_tFlag: return bool2string(pp->getTFlag());
        case FIELD_bFlag: return bool2string(pp->getBFlag());
        case FIELD_mFlag: return bool2string(pp->getMFlag());
        case FIELD_maxRwnd: return ulong2string(pp->getMaxRwnd());
        case FIELD_queuedData: return ulong2string(pp->getQueuedData());
        case FIELD_truncLength: return ulong2string(pp->getTruncLength());
        default: return "";
    }
}

void SctpPacketDropChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cFlag: pp->setCFlag(string2bool(value)); break;
        case FIELD_tFlag: pp->setTFlag(string2bool(value)); break;
        case FIELD_bFlag: pp->setBFlag(string2bool(value)); break;
        case FIELD_mFlag: pp->setMFlag(string2bool(value)); break;
        case FIELD_maxRwnd: pp->setMaxRwnd(string2ulong(value)); break;
        case FIELD_queuedData: pp->setQueuedData(string2ulong(value)); break;
        case FIELD_truncLength: pp->setTruncLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPacketDropChunk'", field);
    }
}

omnetpp::cValue SctpPacketDropChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cFlag: return pp->getCFlag();
        case FIELD_tFlag: return pp->getTFlag();
        case FIELD_bFlag: return pp->getBFlag();
        case FIELD_mFlag: return pp->getMFlag();
        case FIELD_maxRwnd: return (omnetpp::intval_t)(pp->getMaxRwnd());
        case FIELD_queuedData: return (omnetpp::intval_t)(pp->getQueuedData());
        case FIELD_truncLength: return (omnetpp::intval_t)(pp->getTruncLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpPacketDropChunk' as cValue -- field index out of range?", field);
    }
}

void SctpPacketDropChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        case FIELD_cFlag: pp->setCFlag(value.boolValue()); break;
        case FIELD_tFlag: pp->setTFlag(value.boolValue()); break;
        case FIELD_bFlag: pp->setBFlag(value.boolValue()); break;
        case FIELD_mFlag: pp->setMFlag(value.boolValue()); break;
        case FIELD_maxRwnd: pp->setMaxRwnd(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_queuedData: pp->setQueuedData(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_truncLength: pp->setTruncLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPacketDropChunk'", field);
    }
}

const char *SctpPacketDropChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpPacketDropChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpPacketDropChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpPacketDropChunk *pp = omnetpp::fromAnyPtr<SctpPacketDropChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpPacketDropChunk'", field);
    }
}

SctpStreamResetChunk_Base::SctpStreamResetChunk_Base(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpStreamResetChunk_Base::SctpStreamResetChunk_Base(const SctpStreamResetChunk_Base& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpStreamResetChunk_Base::~SctpStreamResetChunk_Base()
{
}

SctpStreamResetChunk_Base& SctpStreamResetChunk_Base::operator=(const SctpStreamResetChunk_Base& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpStreamResetChunk_Base::copy(const SctpStreamResetChunk_Base& other)
{
}

void SctpStreamResetChunk_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    // field parameters is abstract or custom -- please do packing in customized class
}

void SctpStreamResetChunk_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    // field parameters is abstract or custom -- please do unpacking in customized class
}

class SctpStreamResetChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_parameters,
    };
  public:
    SctpStreamResetChunkDescriptor();
    virtual ~SctpStreamResetChunkDescriptor();

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

Register_ClassDescriptor(SctpStreamResetChunkDescriptor)

SctpStreamResetChunkDescriptor::SctpStreamResetChunkDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpStreamResetChunk", "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpStreamResetChunkDescriptor::~SctpStreamResetChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpStreamResetChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpStreamResetChunk_Base *>(obj)!=nullptr;
}

const char **SctpStreamResetChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpStreamResetChunkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpStreamResetChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpStreamResetChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_parameters
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpStreamResetChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "parameters",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpStreamResetChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "parameters") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpStreamResetChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::sctp::SctpParameter",    // FIELD_parameters
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpStreamResetChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpStreamResetChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpStreamResetChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: return pp->getParametersArraySize();
        default: return 0;
    }
}

void SctpStreamResetChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: pp->setParametersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpStreamResetChunk_Base'", field);
    }
}

const char *SctpStreamResetChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: { const SctpParameter * value = pp->getParameters(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpStreamResetChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: { auto obj = pp->getParameters(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void SctpStreamResetChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetChunk_Base'", field);
    }
}

omnetpp::cValue SctpStreamResetChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: return omnetpp::toAnyPtr(pp->getParameters(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpStreamResetChunk_Base' as cValue -- field index out of range?", field);
    }
}

void SctpStreamResetChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: pp->setParameters(i,omnetpp::fromAnyPtr<SctpParameter>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetChunk_Base'", field);
    }
}

const char *SctpStreamResetChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_parameters: return omnetpp::opp_typename(typeid(SctpParameter));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpStreamResetChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: return omnetpp::toAnyPtr(pp->getParameters(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpStreamResetChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetChunk_Base *pp = omnetpp::fromAnyPtr<SctpStreamResetChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_parameters: pp->setParameters(i,omnetpp::fromAnyPtr<SctpParameter>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetChunk_Base'", field);
    }
}

Register_Class(SctpOutgoingSsnResetRequestParameter)

SctpOutgoingSsnResetRequestParameter::SctpOutgoingSsnResetRequestParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpOutgoingSsnResetRequestParameter::SctpOutgoingSsnResetRequestParameter(const SctpOutgoingSsnResetRequestParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpOutgoingSsnResetRequestParameter::~SctpOutgoingSsnResetRequestParameter()
{
    delete [] this->streamNumbers;
}

SctpOutgoingSsnResetRequestParameter& SctpOutgoingSsnResetRequestParameter::operator=(const SctpOutgoingSsnResetRequestParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpOutgoingSsnResetRequestParameter::copy(const SctpOutgoingSsnResetRequestParameter& other)
{
    this->srReqSn = other.srReqSn;
    this->srResSn = other.srResSn;
    this->lastTsn = other.lastTsn;
    delete [] this->streamNumbers;
    this->streamNumbers = (other.streamNumbers_arraysize==0) ? nullptr : new uint16_t[other.streamNumbers_arraysize];
    streamNumbers_arraysize = other.streamNumbers_arraysize;
    for (size_t i = 0; i < streamNumbers_arraysize; i++) {
        this->streamNumbers[i] = other.streamNumbers[i];
    }
}

void SctpOutgoingSsnResetRequestParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->srReqSn);
    doParsimPacking(b,this->srResSn);
    doParsimPacking(b,this->lastTsn);
    b->pack(streamNumbers_arraysize);
    doParsimArrayPacking(b,this->streamNumbers,streamNumbers_arraysize);
}

void SctpOutgoingSsnResetRequestParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->srReqSn);
    doParsimUnpacking(b,this->srResSn);
    doParsimUnpacking(b,this->lastTsn);
    delete [] this->streamNumbers;
    b->unpack(streamNumbers_arraysize);
    if (streamNumbers_arraysize == 0) {
        this->streamNumbers = nullptr;
    } else {
        this->streamNumbers = new uint16_t[streamNumbers_arraysize];
        doParsimArrayUnpacking(b,this->streamNumbers,streamNumbers_arraysize);
    }
}

uint32_t SctpOutgoingSsnResetRequestParameter::getSrReqSn() const
{
    return this->srReqSn;
}

void SctpOutgoingSsnResetRequestParameter::setSrReqSn(uint32_t srReqSn)
{
    this->srReqSn = srReqSn;
}

uint32_t SctpOutgoingSsnResetRequestParameter::getSrResSn() const
{
    return this->srResSn;
}

void SctpOutgoingSsnResetRequestParameter::setSrResSn(uint32_t srResSn)
{
    this->srResSn = srResSn;
}

uint32_t SctpOutgoingSsnResetRequestParameter::getLastTsn() const
{
    return this->lastTsn;
}

void SctpOutgoingSsnResetRequestParameter::setLastTsn(uint32_t lastTsn)
{
    this->lastTsn = lastTsn;
}

size_t SctpOutgoingSsnResetRequestParameter::getStreamNumbersArraySize() const
{
    return streamNumbers_arraysize;
}

uint16_t SctpOutgoingSsnResetRequestParameter::getStreamNumbers(size_t k) const
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    return this->streamNumbers[k];
}

void SctpOutgoingSsnResetRequestParameter::setStreamNumbersArraySize(size_t newSize)
{
    uint16_t *streamNumbers2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = streamNumbers_arraysize < newSize ? streamNumbers_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    for (size_t i = minSize; i < newSize; i++)
        streamNumbers2[i] = 0;
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

void SctpOutgoingSsnResetRequestParameter::setStreamNumbers(size_t k, uint16_t streamNumbers)
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    this->streamNumbers[k] = streamNumbers;
}

void SctpOutgoingSsnResetRequestParameter::insertStreamNumbers(size_t k, uint16_t streamNumbers)
{
    if (k > streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    size_t newSize = streamNumbers_arraysize + 1;
    uint16_t *streamNumbers2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    streamNumbers2[k] = streamNumbers;
    for (i = k + 1; i < newSize; i++)
        streamNumbers2[i] = this->streamNumbers[i-1];
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

void SctpOutgoingSsnResetRequestParameter::appendStreamNumbers(uint16_t streamNumbers)
{
    insertStreamNumbers(streamNumbers_arraysize, streamNumbers);
}

void SctpOutgoingSsnResetRequestParameter::eraseStreamNumbers(size_t k)
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    size_t newSize = streamNumbers_arraysize - 1;
    uint16_t *streamNumbers2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    for (i = k; i < newSize; i++)
        streamNumbers2[i] = this->streamNumbers[i+1];
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

class SctpOutgoingSsnResetRequestParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srReqSn,
        FIELD_srResSn,
        FIELD_lastTsn,
        FIELD_streamNumbers,
    };
  public:
    SctpOutgoingSsnResetRequestParameterDescriptor();
    virtual ~SctpOutgoingSsnResetRequestParameterDescriptor();

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

Register_ClassDescriptor(SctpOutgoingSsnResetRequestParameterDescriptor)

SctpOutgoingSsnResetRequestParameterDescriptor::SctpOutgoingSsnResetRequestParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpOutgoingSsnResetRequestParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpOutgoingSsnResetRequestParameterDescriptor::~SctpOutgoingSsnResetRequestParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpOutgoingSsnResetRequestParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpOutgoingSsnResetRequestParameter *>(obj)!=nullptr;
}

const char **SctpOutgoingSsnResetRequestParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpOutgoingSsnResetRequestParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpOutgoingSsnResetRequestParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srReqSn
        FD_ISEDITABLE,    // FIELD_srResSn
        FD_ISEDITABLE,    // FIELD_lastTsn
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_streamNumbers
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srReqSn",
        "srResSn",
        "lastTsn",
        "streamNumbers",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpOutgoingSsnResetRequestParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srReqSn") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "srResSn") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "lastTsn") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "streamNumbers") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_srReqSn
        "uint32_t",    // FIELD_srResSn
        "uint32_t",    // FIELD_lastTsn
        "uint16_t",    // FIELD_streamNumbers
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpOutgoingSsnResetRequestParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpOutgoingSsnResetRequestParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_streamNumbers: return pp->getStreamNumbersArraySize();
        default: return 0;
    }
}

void SctpOutgoingSsnResetRequestParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_streamNumbers: pp->setStreamNumbersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpOutgoingSsnResetRequestParameter'", field);
    }
}

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpOutgoingSsnResetRequestParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return ulong2string(pp->getSrReqSn());
        case FIELD_srResSn: return ulong2string(pp->getSrResSn());
        case FIELD_lastTsn: return ulong2string(pp->getLastTsn());
        case FIELD_streamNumbers: return ulong2string(pp->getStreamNumbers(i));
        default: return "";
    }
}

void SctpOutgoingSsnResetRequestParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(string2ulong(value)); break;
        case FIELD_srResSn: pp->setSrResSn(string2ulong(value)); break;
        case FIELD_lastTsn: pp->setLastTsn(string2ulong(value)); break;
        case FIELD_streamNumbers: pp->setStreamNumbers(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOutgoingSsnResetRequestParameter'", field);
    }
}

omnetpp::cValue SctpOutgoingSsnResetRequestParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return (omnetpp::intval_t)(pp->getSrReqSn());
        case FIELD_srResSn: return (omnetpp::intval_t)(pp->getSrResSn());
        case FIELD_lastTsn: return (omnetpp::intval_t)(pp->getLastTsn());
        case FIELD_streamNumbers: return (omnetpp::intval_t)(pp->getStreamNumbers(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpOutgoingSsnResetRequestParameter' as cValue -- field index out of range?", field);
    }
}

void SctpOutgoingSsnResetRequestParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_srResSn: pp->setSrResSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_lastTsn: pp->setLastTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_streamNumbers: pp->setStreamNumbers(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOutgoingSsnResetRequestParameter'", field);
    }
}

const char *SctpOutgoingSsnResetRequestParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpOutgoingSsnResetRequestParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpOutgoingSsnResetRequestParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpOutgoingSsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpOutgoingSsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpOutgoingSsnResetRequestParameter'", field);
    }
}

SctpIncomingSsnResetRequestParameter_Base::SctpIncomingSsnResetRequestParameter_Base(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpIncomingSsnResetRequestParameter_Base::SctpIncomingSsnResetRequestParameter_Base(const SctpIncomingSsnResetRequestParameter_Base& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpIncomingSsnResetRequestParameter_Base::~SctpIncomingSsnResetRequestParameter_Base()
{
    delete [] this->streamNumbers;
}

SctpIncomingSsnResetRequestParameter_Base& SctpIncomingSsnResetRequestParameter_Base::operator=(const SctpIncomingSsnResetRequestParameter_Base& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpIncomingSsnResetRequestParameter_Base::copy(const SctpIncomingSsnResetRequestParameter_Base& other)
{
    this->srReqSn = other.srReqSn;
    delete [] this->streamNumbers;
    this->streamNumbers = (other.streamNumbers_arraysize==0) ? nullptr : new uint16_t[other.streamNumbers_arraysize];
    streamNumbers_arraysize = other.streamNumbers_arraysize;
    for (size_t i = 0; i < streamNumbers_arraysize; i++) {
        this->streamNumbers[i] = other.streamNumbers[i];
    }
}

void SctpIncomingSsnResetRequestParameter_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->srReqSn);
    b->pack(streamNumbers_arraysize);
    doParsimArrayPacking(b,this->streamNumbers,streamNumbers_arraysize);
}

void SctpIncomingSsnResetRequestParameter_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->srReqSn);
    delete [] this->streamNumbers;
    b->unpack(streamNumbers_arraysize);
    if (streamNumbers_arraysize == 0) {
        this->streamNumbers = nullptr;
    } else {
        this->streamNumbers = new uint16_t[streamNumbers_arraysize];
        doParsimArrayUnpacking(b,this->streamNumbers,streamNumbers_arraysize);
    }
}

uint32_t SctpIncomingSsnResetRequestParameter_Base::getSrReqSn() const
{
    return this->srReqSn;
}

void SctpIncomingSsnResetRequestParameter_Base::setSrReqSn(uint32_t srReqSn)
{
    this->srReqSn = srReqSn;
}

size_t SctpIncomingSsnResetRequestParameter_Base::getStreamNumbersArraySize() const
{
    return streamNumbers_arraysize;
}

uint16_t SctpIncomingSsnResetRequestParameter_Base::getStreamNumbers(size_t k) const
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    return this->streamNumbers[k];
}

void SctpIncomingSsnResetRequestParameter_Base::setStreamNumbersArraySize(size_t newSize)
{
    uint16_t *streamNumbers2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = streamNumbers_arraysize < newSize ? streamNumbers_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    for (size_t i = minSize; i < newSize; i++)
        streamNumbers2[i] = 0;
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

void SctpIncomingSsnResetRequestParameter_Base::setStreamNumbers(size_t k, uint16_t streamNumbers)
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    this->streamNumbers[k] = streamNumbers;
}

void SctpIncomingSsnResetRequestParameter_Base::insertStreamNumbers(size_t k, uint16_t streamNumbers)
{
    if (k > streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    size_t newSize = streamNumbers_arraysize + 1;
    uint16_t *streamNumbers2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    streamNumbers2[k] = streamNumbers;
    for (i = k + 1; i < newSize; i++)
        streamNumbers2[i] = this->streamNumbers[i-1];
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

void SctpIncomingSsnResetRequestParameter_Base::appendStreamNumbers(uint16_t streamNumbers)
{
    insertStreamNumbers(streamNumbers_arraysize, streamNumbers);
}

void SctpIncomingSsnResetRequestParameter_Base::eraseStreamNumbers(size_t k)
{
    if (k >= streamNumbers_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)streamNumbers_arraysize, (unsigned long)k);
    size_t newSize = streamNumbers_arraysize - 1;
    uint16_t *streamNumbers2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        streamNumbers2[i] = this->streamNumbers[i];
    for (i = k; i < newSize; i++)
        streamNumbers2[i] = this->streamNumbers[i+1];
    delete [] this->streamNumbers;
    this->streamNumbers = streamNumbers2;
    streamNumbers_arraysize = newSize;
}

class SctpIncomingSsnResetRequestParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srReqSn,
        FIELD_streamNumbers,
    };
  public:
    SctpIncomingSsnResetRequestParameterDescriptor();
    virtual ~SctpIncomingSsnResetRequestParameterDescriptor();

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

Register_ClassDescriptor(SctpIncomingSsnResetRequestParameterDescriptor)

SctpIncomingSsnResetRequestParameterDescriptor::SctpIncomingSsnResetRequestParameterDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpIncomingSsnResetRequestParameter", "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpIncomingSsnResetRequestParameterDescriptor::~SctpIncomingSsnResetRequestParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpIncomingSsnResetRequestParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpIncomingSsnResetRequestParameter_Base *>(obj)!=nullptr;
}

const char **SctpIncomingSsnResetRequestParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpIncomingSsnResetRequestParameterDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpIncomingSsnResetRequestParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpIncomingSsnResetRequestParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srReqSn
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_streamNumbers
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpIncomingSsnResetRequestParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srReqSn",
        "streamNumbers",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpIncomingSsnResetRequestParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srReqSn") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "streamNumbers") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpIncomingSsnResetRequestParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_srReqSn
        "uint16_t",    // FIELD_streamNumbers
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpIncomingSsnResetRequestParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpIncomingSsnResetRequestParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpIncomingSsnResetRequestParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_streamNumbers: return pp->getStreamNumbersArraySize();
        default: return 0;
    }
}

void SctpIncomingSsnResetRequestParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_streamNumbers: pp->setStreamNumbersArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpIncomingSsnResetRequestParameter_Base'", field);
    }
}

const char *SctpIncomingSsnResetRequestParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpIncomingSsnResetRequestParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return ulong2string(pp->getSrReqSn());
        case FIELD_streamNumbers: return ulong2string(pp->getStreamNumbers(i));
        default: return "";
    }
}

void SctpIncomingSsnResetRequestParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(string2ulong(value)); break;
        case FIELD_streamNumbers: pp->setStreamNumbers(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpIncomingSsnResetRequestParameter_Base'", field);
    }
}

omnetpp::cValue SctpIncomingSsnResetRequestParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return (omnetpp::intval_t)(pp->getSrReqSn());
        case FIELD_streamNumbers: return (omnetpp::intval_t)(pp->getStreamNumbers(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpIncomingSsnResetRequestParameter_Base' as cValue -- field index out of range?", field);
    }
}

void SctpIncomingSsnResetRequestParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_streamNumbers: pp->setStreamNumbers(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpIncomingSsnResetRequestParameter_Base'", field);
    }
}

const char *SctpIncomingSsnResetRequestParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpIncomingSsnResetRequestParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpIncomingSsnResetRequestParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpIncomingSsnResetRequestParameter_Base *pp = omnetpp::fromAnyPtr<SctpIncomingSsnResetRequestParameter_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpIncomingSsnResetRequestParameter_Base'", field);
    }
}

Register_Class(SctpSsnTsnResetRequestParameter)

SctpSsnTsnResetRequestParameter::SctpSsnTsnResetRequestParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpSsnTsnResetRequestParameter::SctpSsnTsnResetRequestParameter(const SctpSsnTsnResetRequestParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpSsnTsnResetRequestParameter::~SctpSsnTsnResetRequestParameter()
{
}

SctpSsnTsnResetRequestParameter& SctpSsnTsnResetRequestParameter::operator=(const SctpSsnTsnResetRequestParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpSsnTsnResetRequestParameter::copy(const SctpSsnTsnResetRequestParameter& other)
{
    this->srReqSn = other.srReqSn;
}

void SctpSsnTsnResetRequestParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->srReqSn);
}

void SctpSsnTsnResetRequestParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->srReqSn);
}

uint32_t SctpSsnTsnResetRequestParameter::getSrReqSn() const
{
    return this->srReqSn;
}

void SctpSsnTsnResetRequestParameter::setSrReqSn(uint32_t srReqSn)
{
    this->srReqSn = srReqSn;
}

class SctpSsnTsnResetRequestParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srReqSn,
    };
  public:
    SctpSsnTsnResetRequestParameterDescriptor();
    virtual ~SctpSsnTsnResetRequestParameterDescriptor();

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

Register_ClassDescriptor(SctpSsnTsnResetRequestParameterDescriptor)

SctpSsnTsnResetRequestParameterDescriptor::SctpSsnTsnResetRequestParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSsnTsnResetRequestParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpSsnTsnResetRequestParameterDescriptor::~SctpSsnTsnResetRequestParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpSsnTsnResetRequestParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSsnTsnResetRequestParameter *>(obj)!=nullptr;
}

const char **SctpSsnTsnResetRequestParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSsnTsnResetRequestParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSsnTsnResetRequestParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpSsnTsnResetRequestParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srReqSn
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpSsnTsnResetRequestParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srReqSn",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpSsnTsnResetRequestParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srReqSn") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSsnTsnResetRequestParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_srReqSn
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSsnTsnResetRequestParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSsnTsnResetRequestParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSsnTsnResetRequestParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpSsnTsnResetRequestParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSsnTsnResetRequestParameter'", field);
    }
}

const char *SctpSsnTsnResetRequestParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSsnTsnResetRequestParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return ulong2string(pp->getSrReqSn());
        default: return "";
    }
}

void SctpSsnTsnResetRequestParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSsnTsnResetRequestParameter'", field);
    }
}

omnetpp::cValue SctpSsnTsnResetRequestParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return (omnetpp::intval_t)(pp->getSrReqSn());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSsnTsnResetRequestParameter' as cValue -- field index out of range?", field);
    }
}

void SctpSsnTsnResetRequestParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSsnTsnResetRequestParameter'", field);
    }
}

const char *SctpSsnTsnResetRequestParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSsnTsnResetRequestParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSsnTsnResetRequestParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSsnTsnResetRequestParameter *pp = omnetpp::fromAnyPtr<SctpSsnTsnResetRequestParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSsnTsnResetRequestParameter'", field);
    }
}

Register_Class(SctpStreamResetResponseParameter)

SctpStreamResetResponseParameter::SctpStreamResetResponseParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpStreamResetResponseParameter::SctpStreamResetResponseParameter(const SctpStreamResetResponseParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpStreamResetResponseParameter::~SctpStreamResetResponseParameter()
{
}

SctpStreamResetResponseParameter& SctpStreamResetResponseParameter::operator=(const SctpStreamResetResponseParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpStreamResetResponseParameter::copy(const SctpStreamResetResponseParameter& other)
{
    this->srResSn = other.srResSn;
    this->result = other.result;
    this->sendersNextTsn = other.sendersNextTsn;
    this->receiversNextTsn = other.receiversNextTsn;
}

void SctpStreamResetResponseParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->srResSn);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->sendersNextTsn);
    doParsimPacking(b,this->receiversNextTsn);
}

void SctpStreamResetResponseParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->srResSn);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->sendersNextTsn);
    doParsimUnpacking(b,this->receiversNextTsn);
}

uint32_t SctpStreamResetResponseParameter::getSrResSn() const
{
    return this->srResSn;
}

void SctpStreamResetResponseParameter::setSrResSn(uint32_t srResSn)
{
    this->srResSn = srResSn;
}

uint32_t SctpStreamResetResponseParameter::getResult() const
{
    return this->result;
}

void SctpStreamResetResponseParameter::setResult(uint32_t result)
{
    this->result = result;
}

uint32_t SctpStreamResetResponseParameter::getSendersNextTsn() const
{
    return this->sendersNextTsn;
}

void SctpStreamResetResponseParameter::setSendersNextTsn(uint32_t sendersNextTsn)
{
    this->sendersNextTsn = sendersNextTsn;
}

uint32_t SctpStreamResetResponseParameter::getReceiversNextTsn() const
{
    return this->receiversNextTsn;
}

void SctpStreamResetResponseParameter::setReceiversNextTsn(uint32_t receiversNextTsn)
{
    this->receiversNextTsn = receiversNextTsn;
}

class SctpStreamResetResponseParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srResSn,
        FIELD_result,
        FIELD_sendersNextTsn,
        FIELD_receiversNextTsn,
    };
  public:
    SctpStreamResetResponseParameterDescriptor();
    virtual ~SctpStreamResetResponseParameterDescriptor();

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

Register_ClassDescriptor(SctpStreamResetResponseParameterDescriptor)

SctpStreamResetResponseParameterDescriptor::SctpStreamResetResponseParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpStreamResetResponseParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpStreamResetResponseParameterDescriptor::~SctpStreamResetResponseParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpStreamResetResponseParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpStreamResetResponseParameter *>(obj)!=nullptr;
}

const char **SctpStreamResetResponseParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpStreamResetResponseParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpStreamResetResponseParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpStreamResetResponseParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srResSn
        FD_ISEDITABLE,    // FIELD_result
        FD_ISEDITABLE,    // FIELD_sendersNextTsn
        FD_ISEDITABLE,    // FIELD_receiversNextTsn
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpStreamResetResponseParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srResSn",
        "result",
        "sendersNextTsn",
        "receiversNextTsn",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpStreamResetResponseParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srResSn") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "result") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sendersNextTsn") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "receiversNextTsn") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpStreamResetResponseParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_srResSn
        "uint32_t",    // FIELD_result
        "uint32_t",    // FIELD_sendersNextTsn
        "uint32_t",    // FIELD_receiversNextTsn
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpStreamResetResponseParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpStreamResetResponseParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpStreamResetResponseParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpStreamResetResponseParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpStreamResetResponseParameter'", field);
    }
}

const char *SctpStreamResetResponseParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpStreamResetResponseParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srResSn: return ulong2string(pp->getSrResSn());
        case FIELD_result: return ulong2string(pp->getResult());
        case FIELD_sendersNextTsn: return ulong2string(pp->getSendersNextTsn());
        case FIELD_receiversNextTsn: return ulong2string(pp->getReceiversNextTsn());
        default: return "";
    }
}

void SctpStreamResetResponseParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srResSn: pp->setSrResSn(string2ulong(value)); break;
        case FIELD_result: pp->setResult(string2ulong(value)); break;
        case FIELD_sendersNextTsn: pp->setSendersNextTsn(string2ulong(value)); break;
        case FIELD_receiversNextTsn: pp->setReceiversNextTsn(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetResponseParameter'", field);
    }
}

omnetpp::cValue SctpStreamResetResponseParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srResSn: return (omnetpp::intval_t)(pp->getSrResSn());
        case FIELD_result: return (omnetpp::intval_t)(pp->getResult());
        case FIELD_sendersNextTsn: return (omnetpp::intval_t)(pp->getSendersNextTsn());
        case FIELD_receiversNextTsn: return (omnetpp::intval_t)(pp->getReceiversNextTsn());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpStreamResetResponseParameter' as cValue -- field index out of range?", field);
    }
}

void SctpStreamResetResponseParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srResSn: pp->setSrResSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_result: pp->setResult(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_sendersNextTsn: pp->setSendersNextTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_receiversNextTsn: pp->setReceiversNextTsn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetResponseParameter'", field);
    }
}

const char *SctpStreamResetResponseParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpStreamResetResponseParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpStreamResetResponseParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpStreamResetResponseParameter *pp = omnetpp::fromAnyPtr<SctpStreamResetResponseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpStreamResetResponseParameter'", field);
    }
}

Register_Class(SctpAddStreamsRequestParameter)

SctpAddStreamsRequestParameter::SctpAddStreamsRequestParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpAddStreamsRequestParameter::SctpAddStreamsRequestParameter(const SctpAddStreamsRequestParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpAddStreamsRequestParameter::~SctpAddStreamsRequestParameter()
{
}

SctpAddStreamsRequestParameter& SctpAddStreamsRequestParameter::operator=(const SctpAddStreamsRequestParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpAddStreamsRequestParameter::copy(const SctpAddStreamsRequestParameter& other)
{
    this->srReqSn = other.srReqSn;
    this->numberOfStreams = other.numberOfStreams;
    this->reserved = other.reserved;
}

void SctpAddStreamsRequestParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->srReqSn);
    doParsimPacking(b,this->numberOfStreams);
    doParsimPacking(b,this->reserved);
}

void SctpAddStreamsRequestParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->srReqSn);
    doParsimUnpacking(b,this->numberOfStreams);
    doParsimUnpacking(b,this->reserved);
}

uint32_t SctpAddStreamsRequestParameter::getSrReqSn() const
{
    return this->srReqSn;
}

void SctpAddStreamsRequestParameter::setSrReqSn(uint32_t srReqSn)
{
    this->srReqSn = srReqSn;
}

uint16_t SctpAddStreamsRequestParameter::getNumberOfStreams() const
{
    return this->numberOfStreams;
}

void SctpAddStreamsRequestParameter::setNumberOfStreams(uint16_t numberOfStreams)
{
    this->numberOfStreams = numberOfStreams;
}

uint16_t SctpAddStreamsRequestParameter::getReserved() const
{
    return this->reserved;
}

void SctpAddStreamsRequestParameter::setReserved(uint16_t reserved)
{
    this->reserved = reserved;
}

class SctpAddStreamsRequestParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srReqSn,
        FIELD_numberOfStreams,
        FIELD_reserved,
    };
  public:
    SctpAddStreamsRequestParameterDescriptor();
    virtual ~SctpAddStreamsRequestParameterDescriptor();

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

Register_ClassDescriptor(SctpAddStreamsRequestParameterDescriptor)

SctpAddStreamsRequestParameterDescriptor::SctpAddStreamsRequestParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpAddStreamsRequestParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpAddStreamsRequestParameterDescriptor::~SctpAddStreamsRequestParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpAddStreamsRequestParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAddStreamsRequestParameter *>(obj)!=nullptr;
}

const char **SctpAddStreamsRequestParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAddStreamsRequestParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAddStreamsRequestParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SctpAddStreamsRequestParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srReqSn
        FD_ISEDITABLE,    // FIELD_numberOfStreams
        FD_ISEDITABLE,    // FIELD_reserved
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SctpAddStreamsRequestParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srReqSn",
        "numberOfStreams",
        "reserved",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SctpAddStreamsRequestParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srReqSn") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "numberOfStreams") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAddStreamsRequestParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_srReqSn
        "uint16_t",    // FIELD_numberOfStreams
        "uint16_t",    // FIELD_reserved
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAddStreamsRequestParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAddStreamsRequestParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAddStreamsRequestParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpAddStreamsRequestParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAddStreamsRequestParameter'", field);
    }
}

const char *SctpAddStreamsRequestParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpAddStreamsRequestParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return ulong2string(pp->getSrReqSn());
        case FIELD_numberOfStreams: return ulong2string(pp->getNumberOfStreams());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        default: return "";
    }
}

void SctpAddStreamsRequestParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(string2ulong(value)); break;
        case FIELD_numberOfStreams: pp->setNumberOfStreams(string2ulong(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddStreamsRequestParameter'", field);
    }
}

omnetpp::cValue SctpAddStreamsRequestParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: return (omnetpp::intval_t)(pp->getSrReqSn());
        case FIELD_numberOfStreams: return (omnetpp::intval_t)(pp->getNumberOfStreams());
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAddStreamsRequestParameter' as cValue -- field index out of range?", field);
    }
}

void SctpAddStreamsRequestParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        case FIELD_srReqSn: pp->setSrReqSn(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_numberOfStreams: pp->setNumberOfStreams(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddStreamsRequestParameter'", field);
    }
}

const char *SctpAddStreamsRequestParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpAddStreamsRequestParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAddStreamsRequestParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddStreamsRequestParameter *pp = omnetpp::fromAnyPtr<SctpAddStreamsRequestParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddStreamsRequestParameter'", field);
    }
}

Register_Class(SctpResetTimer)

SctpResetTimer::SctpResetTimer(const char *name) : ::omnetpp::cPacket(name)
{
}

SctpResetTimer::SctpResetTimer(const SctpResetTimer& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

SctpResetTimer::~SctpResetTimer()
{
}

SctpResetTimer& SctpResetTimer::operator=(const SctpResetTimer& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void SctpResetTimer::copy(const SctpResetTimer& other)
{
    this->inSN = other.inSN;
    this->inAcked = other.inAcked;
    this->outSN = other.outSN;
    this->outAcked = other.outAcked;
}

void SctpResetTimer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->inSN);
    doParsimPacking(b,this->inAcked);
    doParsimPacking(b,this->outSN);
    doParsimPacking(b,this->outAcked);
}

void SctpResetTimer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->inSN);
    doParsimUnpacking(b,this->inAcked);
    doParsimUnpacking(b,this->outSN);
    doParsimUnpacking(b,this->outAcked);
}

uint32_t SctpResetTimer::getInSN() const
{
    return this->inSN;
}

void SctpResetTimer::setInSN(uint32_t inSN)
{
    this->inSN = inSN;
}

bool SctpResetTimer::getInAcked() const
{
    return this->inAcked;
}

void SctpResetTimer::setInAcked(bool inAcked)
{
    this->inAcked = inAcked;
}

uint32_t SctpResetTimer::getOutSN() const
{
    return this->outSN;
}

void SctpResetTimer::setOutSN(uint32_t outSN)
{
    this->outSN = outSN;
}

bool SctpResetTimer::getOutAcked() const
{
    return this->outAcked;
}

void SctpResetTimer::setOutAcked(bool outAcked)
{
    this->outAcked = outAcked;
}

class SctpResetTimerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_inSN,
        FIELD_inAcked,
        FIELD_outSN,
        FIELD_outAcked,
    };
  public:
    SctpResetTimerDescriptor();
    virtual ~SctpResetTimerDescriptor();

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

Register_ClassDescriptor(SctpResetTimerDescriptor)

SctpResetTimerDescriptor::SctpResetTimerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpResetTimer)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

SctpResetTimerDescriptor::~SctpResetTimerDescriptor()
{
    delete[] propertyNames;
}

bool SctpResetTimerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpResetTimer *>(obj)!=nullptr;
}

const char **SctpResetTimerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpResetTimerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpResetTimerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpResetTimerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_inSN
        FD_ISEDITABLE,    // FIELD_inAcked
        FD_ISEDITABLE,    // FIELD_outSN
        FD_ISEDITABLE,    // FIELD_outAcked
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpResetTimerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "inSN",
        "inAcked",
        "outSN",
        "outAcked",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpResetTimerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "inSN") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "inAcked") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "outSN") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "outAcked") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpResetTimerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_inSN
        "bool",    // FIELD_inAcked
        "uint32_t",    // FIELD_outSN
        "bool",    // FIELD_outAcked
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpResetTimerDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpResetTimerDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpResetTimerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpResetTimerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpResetTimer'", field);
    }
}

const char *SctpResetTimerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpResetTimerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        case FIELD_inSN: return ulong2string(pp->getInSN());
        case FIELD_inAcked: return bool2string(pp->getInAcked());
        case FIELD_outSN: return ulong2string(pp->getOutSN());
        case FIELD_outAcked: return bool2string(pp->getOutAcked());
        default: return "";
    }
}

void SctpResetTimerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        case FIELD_inSN: pp->setInSN(string2ulong(value)); break;
        case FIELD_inAcked: pp->setInAcked(string2bool(value)); break;
        case FIELD_outSN: pp->setOutSN(string2ulong(value)); break;
        case FIELD_outAcked: pp->setOutAcked(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetTimer'", field);
    }
}

omnetpp::cValue SctpResetTimerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        case FIELD_inSN: return (omnetpp::intval_t)(pp->getInSN());
        case FIELD_inAcked: return pp->getInAcked();
        case FIELD_outSN: return (omnetpp::intval_t)(pp->getOutSN());
        case FIELD_outAcked: return pp->getOutAcked();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpResetTimer' as cValue -- field index out of range?", field);
    }
}

void SctpResetTimerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        case FIELD_inSN: pp->setInSN(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_inAcked: pp->setInAcked(value.boolValue()); break;
        case FIELD_outSN: pp->setOutSN(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_outAcked: pp->setOutAcked(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetTimer'", field);
    }
}

const char *SctpResetTimerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpResetTimerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpResetTimerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpResetTimer *pp = omnetpp::fromAnyPtr<SctpResetTimer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpResetTimer'", field);
    }
}

Register_Class(SctpAuthenticationChunk)

SctpAuthenticationChunk::SctpAuthenticationChunk(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpAuthenticationChunk::SctpAuthenticationChunk(const SctpAuthenticationChunk& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpAuthenticationChunk::~SctpAuthenticationChunk()
{
    delete [] this->HMAC;
}

SctpAuthenticationChunk& SctpAuthenticationChunk::operator=(const SctpAuthenticationChunk& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpAuthenticationChunk::copy(const SctpAuthenticationChunk& other)
{
    this->sharedKey = other.sharedKey;
    this->hMacIdentifier = other.hMacIdentifier;
    this->hMacOk = other.hMacOk;
    delete [] this->HMAC;
    this->HMAC = (other.HMAC_arraysize==0) ? nullptr : new uint32_t[other.HMAC_arraysize];
    HMAC_arraysize = other.HMAC_arraysize;
    for (size_t i = 0; i < HMAC_arraysize; i++) {
        this->HMAC[i] = other.HMAC[i];
    }
}

void SctpAuthenticationChunk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->sharedKey);
    doParsimPacking(b,this->hMacIdentifier);
    doParsimPacking(b,this->hMacOk);
    b->pack(HMAC_arraysize);
    doParsimArrayPacking(b,this->HMAC,HMAC_arraysize);
}

void SctpAuthenticationChunk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sharedKey);
    doParsimUnpacking(b,this->hMacIdentifier);
    doParsimUnpacking(b,this->hMacOk);
    delete [] this->HMAC;
    b->unpack(HMAC_arraysize);
    if (HMAC_arraysize == 0) {
        this->HMAC = nullptr;
    } else {
        this->HMAC = new uint32_t[HMAC_arraysize];
        doParsimArrayUnpacking(b,this->HMAC,HMAC_arraysize);
    }
}

uint16_t SctpAuthenticationChunk::getSharedKey() const
{
    return this->sharedKey;
}

void SctpAuthenticationChunk::setSharedKey(uint16_t sharedKey)
{
    this->sharedKey = sharedKey;
}

uint16_t SctpAuthenticationChunk::getHMacIdentifier() const
{
    return this->hMacIdentifier;
}

void SctpAuthenticationChunk::setHMacIdentifier(uint16_t hMacIdentifier)
{
    this->hMacIdentifier = hMacIdentifier;
}

bool SctpAuthenticationChunk::getHMacOk() const
{
    return this->hMacOk;
}

void SctpAuthenticationChunk::setHMacOk(bool hMacOk)
{
    this->hMacOk = hMacOk;
}

size_t SctpAuthenticationChunk::getHMACArraySize() const
{
    return HMAC_arraysize;
}

uint32_t SctpAuthenticationChunk::getHMAC(size_t k) const
{
    if (k >= HMAC_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)HMAC_arraysize, (unsigned long)k);
    return this->HMAC[k];
}

void SctpAuthenticationChunk::setHMACArraySize(size_t newSize)
{
    uint32_t *HMAC2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = HMAC_arraysize < newSize ? HMAC_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        HMAC2[i] = this->HMAC[i];
    for (size_t i = minSize; i < newSize; i++)
        HMAC2[i] = 0;
    delete [] this->HMAC;
    this->HMAC = HMAC2;
    HMAC_arraysize = newSize;
}

void SctpAuthenticationChunk::setHMAC(size_t k, uint32_t HMAC)
{
    if (k >= HMAC_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)HMAC_arraysize, (unsigned long)k);
    this->HMAC[k] = HMAC;
}

void SctpAuthenticationChunk::insertHMAC(size_t k, uint32_t HMAC)
{
    if (k > HMAC_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)HMAC_arraysize, (unsigned long)k);
    size_t newSize = HMAC_arraysize + 1;
    uint32_t *HMAC2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        HMAC2[i] = this->HMAC[i];
    HMAC2[k] = HMAC;
    for (i = k + 1; i < newSize; i++)
        HMAC2[i] = this->HMAC[i-1];
    delete [] this->HMAC;
    this->HMAC = HMAC2;
    HMAC_arraysize = newSize;
}

void SctpAuthenticationChunk::appendHMAC(uint32_t HMAC)
{
    insertHMAC(HMAC_arraysize, HMAC);
}

void SctpAuthenticationChunk::eraseHMAC(size_t k)
{
    if (k >= HMAC_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)HMAC_arraysize, (unsigned long)k);
    size_t newSize = HMAC_arraysize - 1;
    uint32_t *HMAC2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        HMAC2[i] = this->HMAC[i];
    for (i = k; i < newSize; i++)
        HMAC2[i] = this->HMAC[i+1];
    delete [] this->HMAC;
    this->HMAC = HMAC2;
    HMAC_arraysize = newSize;
}

class SctpAuthenticationChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sharedKey,
        FIELD_hMacIdentifier,
        FIELD_hMacOk,
        FIELD_HMAC,
    };
  public:
    SctpAuthenticationChunkDescriptor();
    virtual ~SctpAuthenticationChunkDescriptor();

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

Register_ClassDescriptor(SctpAuthenticationChunkDescriptor)

SctpAuthenticationChunkDescriptor::SctpAuthenticationChunkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpAuthenticationChunk)), "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpAuthenticationChunkDescriptor::~SctpAuthenticationChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpAuthenticationChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAuthenticationChunk *>(obj)!=nullptr;
}

const char **SctpAuthenticationChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAuthenticationChunkDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAuthenticationChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpAuthenticationChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sharedKey
        FD_ISEDITABLE,    // FIELD_hMacIdentifier
        FD_ISEDITABLE,    // FIELD_hMacOk
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_HMAC
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpAuthenticationChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sharedKey",
        "hMacIdentifier",
        "hMacOk",
        "HMAC",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpAuthenticationChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sharedKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hMacIdentifier") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hMacOk") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "HMAC") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAuthenticationChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_sharedKey
        "uint16_t",    // FIELD_hMacIdentifier
        "bool",    // FIELD_hMacOk
        "uint32_t",    // FIELD_HMAC
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAuthenticationChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAuthenticationChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAuthenticationChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_HMAC: return pp->getHMACArraySize();
        default: return 0;
    }
}

void SctpAuthenticationChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_HMAC: pp->setHMACArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAuthenticationChunk'", field);
    }
}

const char *SctpAuthenticationChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpAuthenticationChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sharedKey: return ulong2string(pp->getSharedKey());
        case FIELD_hMacIdentifier: return ulong2string(pp->getHMacIdentifier());
        case FIELD_hMacOk: return bool2string(pp->getHMacOk());
        case FIELD_HMAC: return ulong2string(pp->getHMAC(i));
        default: return "";
    }
}

void SctpAuthenticationChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sharedKey: pp->setSharedKey(string2ulong(value)); break;
        case FIELD_hMacIdentifier: pp->setHMacIdentifier(string2ulong(value)); break;
        case FIELD_hMacOk: pp->setHMacOk(string2bool(value)); break;
        case FIELD_HMAC: pp->setHMAC(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAuthenticationChunk'", field);
    }
}

omnetpp::cValue SctpAuthenticationChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sharedKey: return (omnetpp::intval_t)(pp->getSharedKey());
        case FIELD_hMacIdentifier: return (omnetpp::intval_t)(pp->getHMacIdentifier());
        case FIELD_hMacOk: return pp->getHMacOk();
        case FIELD_HMAC: return (omnetpp::intval_t)(pp->getHMAC(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAuthenticationChunk' as cValue -- field index out of range?", field);
    }
}

void SctpAuthenticationChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        case FIELD_sharedKey: pp->setSharedKey(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_hMacIdentifier: pp->setHMacIdentifier(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_hMacOk: pp->setHMacOk(value.boolValue()); break;
        case FIELD_HMAC: pp->setHMAC(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAuthenticationChunk'", field);
    }
}

const char *SctpAuthenticationChunkDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpAuthenticationChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAuthenticationChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAuthenticationChunk *pp = omnetpp::fromAnyPtr<SctpAuthenticationChunk>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAuthenticationChunk'", field);
    }
}

SctpAsconfChunk_Base::SctpAsconfChunk_Base(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpAsconfChunk_Base::SctpAsconfChunk_Base(const SctpAsconfChunk_Base& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpAsconfChunk_Base::~SctpAsconfChunk_Base()
{
}

SctpAsconfChunk_Base& SctpAsconfChunk_Base::operator=(const SctpAsconfChunk_Base& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpAsconfChunk_Base::copy(const SctpAsconfChunk_Base& other)
{
    this->serialNumber = other.serialNumber;
    this->addressParam = other.addressParam;
    this->peerVTag = other.peerVTag;
}

void SctpAsconfChunk_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->serialNumber);
    doParsimPacking(b,this->addressParam);
    doParsimPacking(b,this->peerVTag);
    // field asconfParams is abstract or custom -- please do packing in customized class
}

void SctpAsconfChunk_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->serialNumber);
    doParsimUnpacking(b,this->addressParam);
    doParsimUnpacking(b,this->peerVTag);
    // field asconfParams is abstract or custom -- please do unpacking in customized class
}

uint32_t SctpAsconfChunk_Base::getSerialNumber() const
{
    return this->serialNumber;
}

void SctpAsconfChunk_Base::setSerialNumber(uint32_t serialNumber)
{
    this->serialNumber = serialNumber;
}

const ::inet::L3Address& SctpAsconfChunk_Base::getAddressParam() const
{
    return this->addressParam;
}

void SctpAsconfChunk_Base::setAddressParam(const ::inet::L3Address& addressParam)
{
    this->addressParam = addressParam;
}

uint32_t SctpAsconfChunk_Base::getPeerVTag() const
{
    return this->peerVTag;
}

void SctpAsconfChunk_Base::setPeerVTag(uint32_t peerVTag)
{
    this->peerVTag = peerVTag;
}

class SctpAsconfChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_serialNumber,
        FIELD_addressParam,
        FIELD_peerVTag,
        FIELD_asconfParams,
    };
  public:
    SctpAsconfChunkDescriptor();
    virtual ~SctpAsconfChunkDescriptor();

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

Register_ClassDescriptor(SctpAsconfChunkDescriptor)

SctpAsconfChunkDescriptor::SctpAsconfChunkDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpAsconfChunk", "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpAsconfChunkDescriptor::~SctpAsconfChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpAsconfChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAsconfChunk_Base *>(obj)!=nullptr;
}

const char **SctpAsconfChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAsconfChunkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAsconfChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SctpAsconfChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_serialNumber
        0,    // FIELD_addressParam
        FD_ISEDITABLE,    // FIELD_peerVTag
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_asconfParams
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SctpAsconfChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "serialNumber",
        "addressParam",
        "peerVTag",
        "asconfParams",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SctpAsconfChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "serialNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "addressParam") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "peerVTag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "asconfParams") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAsconfChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_serialNumber
        "inet::L3Address",    // FIELD_addressParam
        "uint32_t",    // FIELD_peerVTag
        "inet::sctp::SctpParameter",    // FIELD_asconfParams
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAsconfChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAsconfChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAsconfChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfParams: return pp->getAsconfParamsArraySize();
        default: return 0;
    }
}

void SctpAsconfChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfParams: pp->setAsconfParamsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAsconfChunk_Base'", field);
    }
}

const char *SctpAsconfChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfParams: { const SctpParameter * value = pp->getAsconfParams(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpAsconfChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: return ulong2string(pp->getSerialNumber());
        case FIELD_addressParam: return pp->getAddressParam().str();
        case FIELD_peerVTag: return ulong2string(pp->getPeerVTag());
        case FIELD_asconfParams: { auto obj = pp->getAsconfParams(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void SctpAsconfChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: pp->setSerialNumber(string2ulong(value)); break;
        case FIELD_peerVTag: pp->setPeerVTag(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfChunk_Base'", field);
    }
}

omnetpp::cValue SctpAsconfChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: return (omnetpp::intval_t)(pp->getSerialNumber());
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        case FIELD_peerVTag: return (omnetpp::intval_t)(pp->getPeerVTag());
        case FIELD_asconfParams: return omnetpp::toAnyPtr(pp->getAsconfParams(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAsconfChunk_Base' as cValue -- field index out of range?", field);
    }
}

void SctpAsconfChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: pp->setSerialNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_peerVTag: pp->setPeerVTag(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_asconfParams: pp->setAsconfParams(i,omnetpp::fromAnyPtr<SctpParameter>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfChunk_Base'", field);
    }
}

const char *SctpAsconfChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_asconfParams: return omnetpp::opp_typename(typeid(SctpParameter));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpAsconfChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        case FIELD_asconfParams: return omnetpp::toAnyPtr(pp->getAsconfParams(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAsconfChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfParams: pp->setAsconfParams(i,omnetpp::fromAnyPtr<SctpParameter>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfChunk_Base'", field);
    }
}

SctpAsconfAckChunk_Base::SctpAsconfAckChunk_Base(const char *name) : ::inet::sctp::SctpChunk(name)
{
}

SctpAsconfAckChunk_Base::SctpAsconfAckChunk_Base(const SctpAsconfAckChunk_Base& other) : ::inet::sctp::SctpChunk(other)
{
    copy(other);
}

SctpAsconfAckChunk_Base::~SctpAsconfAckChunk_Base()
{
}

SctpAsconfAckChunk_Base& SctpAsconfAckChunk_Base::operator=(const SctpAsconfAckChunk_Base& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpChunk::operator=(other);
    copy(other);
    return *this;
}

void SctpAsconfAckChunk_Base::copy(const SctpAsconfAckChunk_Base& other)
{
    this->serialNumber = other.serialNumber;
}

void SctpAsconfAckChunk_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpChunk::parsimPack(b);
    doParsimPacking(b,this->serialNumber);
    // field asconfResponse is abstract or custom -- please do packing in customized class
}

void SctpAsconfAckChunk_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->serialNumber);
    // field asconfResponse is abstract or custom -- please do unpacking in customized class
}

uint32_t SctpAsconfAckChunk_Base::getSerialNumber() const
{
    return this->serialNumber;
}

void SctpAsconfAckChunk_Base::setSerialNumber(uint32_t serialNumber)
{
    this->serialNumber = serialNumber;
}

class SctpAsconfAckChunkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_serialNumber,
        FIELD_asconfResponse,
    };
  public:
    SctpAsconfAckChunkDescriptor();
    virtual ~SctpAsconfAckChunkDescriptor();

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

Register_ClassDescriptor(SctpAsconfAckChunkDescriptor)

SctpAsconfAckChunkDescriptor::SctpAsconfAckChunkDescriptor() : omnetpp::cClassDescriptor("inet::sctp::SctpAsconfAckChunk", "inet::sctp::SctpChunk")
{
    propertyNames = nullptr;
}

SctpAsconfAckChunkDescriptor::~SctpAsconfAckChunkDescriptor()
{
    delete[] propertyNames;
}

bool SctpAsconfAckChunkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAsconfAckChunk_Base *>(obj)!=nullptr;
}

const char **SctpAsconfAckChunkDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAsconfAckChunkDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAsconfAckChunkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpAsconfAckChunkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_serialNumber
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_asconfResponse
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpAsconfAckChunkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "serialNumber",
        "asconfResponse",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpAsconfAckChunkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "serialNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "asconfResponse") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAsconfAckChunkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_serialNumber
        "inet::sctp::SctpParameter",    // FIELD_asconfResponse
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAsconfAckChunkDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAsconfAckChunkDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAsconfAckChunkDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfResponse: return pp->getAsconfResponseArraySize();
        default: return 0;
    }
}

void SctpAsconfAckChunkDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfResponse: pp->setAsconfResponseArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAsconfAckChunk_Base'", field);
    }
}

const char *SctpAsconfAckChunkDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfResponse: { const SctpParameter * value = pp->getAsconfResponse(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string SctpAsconfAckChunkDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: return ulong2string(pp->getSerialNumber());
        case FIELD_asconfResponse: { auto obj = pp->getAsconfResponse(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void SctpAsconfAckChunkDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: pp->setSerialNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfAckChunk_Base'", field);
    }
}

omnetpp::cValue SctpAsconfAckChunkDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: return (omnetpp::intval_t)(pp->getSerialNumber());
        case FIELD_asconfResponse: return omnetpp::toAnyPtr(pp->getAsconfResponse(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAsconfAckChunk_Base' as cValue -- field index out of range?", field);
    }
}

void SctpAsconfAckChunkDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_serialNumber: pp->setSerialNumber(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_asconfResponse: pp->setAsconfResponse(i,omnetpp::fromAnyPtr<SctpParameter>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfAckChunk_Base'", field);
    }
}

const char *SctpAsconfAckChunkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_asconfResponse: return omnetpp::opp_typename(typeid(SctpParameter));
        default: return nullptr;
    };
}

omnetpp::any_ptr SctpAsconfAckChunkDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfResponse: return omnetpp::toAnyPtr(pp->getAsconfResponse(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAsconfAckChunkDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAsconfAckChunk_Base *pp = omnetpp::fromAnyPtr<SctpAsconfAckChunk_Base>(object); (void)pp;
    switch (field) {
        case FIELD_asconfResponse: pp->setAsconfResponse(i,omnetpp::fromAnyPtr<SctpParameter>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAsconfAckChunk_Base'", field);
    }
}

Register_Class(SctpAddIPParameter)

SctpAddIPParameter::SctpAddIPParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpAddIPParameter::SctpAddIPParameter(const SctpAddIPParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpAddIPParameter::~SctpAddIPParameter()
{
}

SctpAddIPParameter& SctpAddIPParameter::operator=(const SctpAddIPParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpAddIPParameter::copy(const SctpAddIPParameter& other)
{
    this->requestCorrelationId = other.requestCorrelationId;
    this->addressParam = other.addressParam;
}

void SctpAddIPParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->requestCorrelationId);
    doParsimPacking(b,this->addressParam);
}

void SctpAddIPParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->requestCorrelationId);
    doParsimUnpacking(b,this->addressParam);
}

uint32_t SctpAddIPParameter::getRequestCorrelationId() const
{
    return this->requestCorrelationId;
}

void SctpAddIPParameter::setRequestCorrelationId(uint32_t requestCorrelationId)
{
    this->requestCorrelationId = requestCorrelationId;
}

const ::inet::L3Address& SctpAddIPParameter::getAddressParam() const
{
    return this->addressParam;
}

void SctpAddIPParameter::setAddressParam(const ::inet::L3Address& addressParam)
{
    this->addressParam = addressParam;
}

class SctpAddIPParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestCorrelationId,
        FIELD_addressParam,
    };
  public:
    SctpAddIPParameterDescriptor();
    virtual ~SctpAddIPParameterDescriptor();

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

Register_ClassDescriptor(SctpAddIPParameterDescriptor)

SctpAddIPParameterDescriptor::SctpAddIPParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpAddIPParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpAddIPParameterDescriptor::~SctpAddIPParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpAddIPParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpAddIPParameter *>(obj)!=nullptr;
}

const char **SctpAddIPParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpAddIPParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpAddIPParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpAddIPParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestCorrelationId
        0,    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpAddIPParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestCorrelationId",
        "addressParam",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpAddIPParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestCorrelationId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "addressParam") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpAddIPParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_requestCorrelationId
        "inet::L3Address",    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpAddIPParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpAddIPParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpAddIPParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpAddIPParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpAddIPParameter'", field);
    }
}

const char *SctpAddIPParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpAddIPParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return ulong2string(pp->getRequestCorrelationId());
        case FIELD_addressParam: return pp->getAddressParam().str();
        default: return "";
    }
}

void SctpAddIPParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddIPParameter'", field);
    }
}

omnetpp::cValue SctpAddIPParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return (omnetpp::intval_t)(pp->getRequestCorrelationId());
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpAddIPParameter' as cValue -- field index out of range?", field);
    }
}

void SctpAddIPParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddIPParameter'", field);
    }
}

const char *SctpAddIPParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpAddIPParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpAddIPParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpAddIPParameter *pp = omnetpp::fromAnyPtr<SctpAddIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpAddIPParameter'", field);
    }
}

Register_Class(SctpDeleteIPParameter)

SctpDeleteIPParameter::SctpDeleteIPParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpDeleteIPParameter::SctpDeleteIPParameter(const SctpDeleteIPParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpDeleteIPParameter::~SctpDeleteIPParameter()
{
}

SctpDeleteIPParameter& SctpDeleteIPParameter::operator=(const SctpDeleteIPParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpDeleteIPParameter::copy(const SctpDeleteIPParameter& other)
{
    this->requestCorrelationId = other.requestCorrelationId;
    this->addressParam = other.addressParam;
}

void SctpDeleteIPParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->requestCorrelationId);
    doParsimPacking(b,this->addressParam);
}

void SctpDeleteIPParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->requestCorrelationId);
    doParsimUnpacking(b,this->addressParam);
}

uint32_t SctpDeleteIPParameter::getRequestCorrelationId() const
{
    return this->requestCorrelationId;
}

void SctpDeleteIPParameter::setRequestCorrelationId(uint32_t requestCorrelationId)
{
    this->requestCorrelationId = requestCorrelationId;
}

const ::inet::L3Address& SctpDeleteIPParameter::getAddressParam() const
{
    return this->addressParam;
}

void SctpDeleteIPParameter::setAddressParam(const ::inet::L3Address& addressParam)
{
    this->addressParam = addressParam;
}

class SctpDeleteIPParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestCorrelationId,
        FIELD_addressParam,
    };
  public:
    SctpDeleteIPParameterDescriptor();
    virtual ~SctpDeleteIPParameterDescriptor();

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

Register_ClassDescriptor(SctpDeleteIPParameterDescriptor)

SctpDeleteIPParameterDescriptor::SctpDeleteIPParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpDeleteIPParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpDeleteIPParameterDescriptor::~SctpDeleteIPParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpDeleteIPParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpDeleteIPParameter *>(obj)!=nullptr;
}

const char **SctpDeleteIPParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpDeleteIPParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpDeleteIPParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpDeleteIPParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestCorrelationId
        0,    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpDeleteIPParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestCorrelationId",
        "addressParam",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpDeleteIPParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestCorrelationId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "addressParam") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpDeleteIPParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_requestCorrelationId
        "inet::L3Address",    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpDeleteIPParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpDeleteIPParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpDeleteIPParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpDeleteIPParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpDeleteIPParameter'", field);
    }
}

const char *SctpDeleteIPParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpDeleteIPParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return ulong2string(pp->getRequestCorrelationId());
        case FIELD_addressParam: return pp->getAddressParam().str();
        default: return "";
    }
}

void SctpDeleteIPParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDeleteIPParameter'", field);
    }
}

omnetpp::cValue SctpDeleteIPParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return (omnetpp::intval_t)(pp->getRequestCorrelationId());
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpDeleteIPParameter' as cValue -- field index out of range?", field);
    }
}

void SctpDeleteIPParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDeleteIPParameter'", field);
    }
}

const char *SctpDeleteIPParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpDeleteIPParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpDeleteIPParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpDeleteIPParameter *pp = omnetpp::fromAnyPtr<SctpDeleteIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpDeleteIPParameter'", field);
    }
}

Register_Class(SctpSetPrimaryIPParameter)

SctpSetPrimaryIPParameter::SctpSetPrimaryIPParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpSetPrimaryIPParameter::SctpSetPrimaryIPParameter(const SctpSetPrimaryIPParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpSetPrimaryIPParameter::~SctpSetPrimaryIPParameter()
{
}

SctpSetPrimaryIPParameter& SctpSetPrimaryIPParameter::operator=(const SctpSetPrimaryIPParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpSetPrimaryIPParameter::copy(const SctpSetPrimaryIPParameter& other)
{
    this->requestCorrelationId = other.requestCorrelationId;
    this->addressParam = other.addressParam;
}

void SctpSetPrimaryIPParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->requestCorrelationId);
    doParsimPacking(b,this->addressParam);
}

void SctpSetPrimaryIPParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->requestCorrelationId);
    doParsimUnpacking(b,this->addressParam);
}

uint32_t SctpSetPrimaryIPParameter::getRequestCorrelationId() const
{
    return this->requestCorrelationId;
}

void SctpSetPrimaryIPParameter::setRequestCorrelationId(uint32_t requestCorrelationId)
{
    this->requestCorrelationId = requestCorrelationId;
}

const ::inet::L3Address& SctpSetPrimaryIPParameter::getAddressParam() const
{
    return this->addressParam;
}

void SctpSetPrimaryIPParameter::setAddressParam(const ::inet::L3Address& addressParam)
{
    this->addressParam = addressParam;
}

class SctpSetPrimaryIPParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_requestCorrelationId,
        FIELD_addressParam,
    };
  public:
    SctpSetPrimaryIPParameterDescriptor();
    virtual ~SctpSetPrimaryIPParameterDescriptor();

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

Register_ClassDescriptor(SctpSetPrimaryIPParameterDescriptor)

SctpSetPrimaryIPParameterDescriptor::SctpSetPrimaryIPParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSetPrimaryIPParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpSetPrimaryIPParameterDescriptor::~SctpSetPrimaryIPParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpSetPrimaryIPParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSetPrimaryIPParameter *>(obj)!=nullptr;
}

const char **SctpSetPrimaryIPParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSetPrimaryIPParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSetPrimaryIPParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpSetPrimaryIPParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_requestCorrelationId
        0,    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpSetPrimaryIPParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requestCorrelationId",
        "addressParam",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpSetPrimaryIPParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "requestCorrelationId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "addressParam") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSetPrimaryIPParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_requestCorrelationId
        "inet::L3Address",    // FIELD_addressParam
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSetPrimaryIPParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSetPrimaryIPParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSetPrimaryIPParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpSetPrimaryIPParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSetPrimaryIPParameter'", field);
    }
}

const char *SctpSetPrimaryIPParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSetPrimaryIPParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return ulong2string(pp->getRequestCorrelationId());
        case FIELD_addressParam: return pp->getAddressParam().str();
        default: return "";
    }
}

void SctpSetPrimaryIPParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSetPrimaryIPParameter'", field);
    }
}

omnetpp::cValue SctpSetPrimaryIPParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: return (omnetpp::intval_t)(pp->getRequestCorrelationId());
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSetPrimaryIPParameter' as cValue -- field index out of range?", field);
    }
}

void SctpSetPrimaryIPParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_requestCorrelationId: pp->setRequestCorrelationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSetPrimaryIPParameter'", field);
    }
}

const char *SctpSetPrimaryIPParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSetPrimaryIPParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        case FIELD_addressParam: return omnetpp::toAnyPtr(&pp->getAddressParam()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSetPrimaryIPParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSetPrimaryIPParameter *pp = omnetpp::fromAnyPtr<SctpSetPrimaryIPParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSetPrimaryIPParameter'", field);
    }
}

Register_Class(SctpSupportedExtensionsParameter)

SctpSupportedExtensionsParameter::SctpSupportedExtensionsParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpSupportedExtensionsParameter::SctpSupportedExtensionsParameter(const SctpSupportedExtensionsParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpSupportedExtensionsParameter::~SctpSupportedExtensionsParameter()
{
    delete [] this->sctpChunkTypes;
}

SctpSupportedExtensionsParameter& SctpSupportedExtensionsParameter::operator=(const SctpSupportedExtensionsParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpSupportedExtensionsParameter::copy(const SctpSupportedExtensionsParameter& other)
{
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = (other.sctpChunkTypes_arraysize==0) ? nullptr : new uint16_t[other.sctpChunkTypes_arraysize];
    sctpChunkTypes_arraysize = other.sctpChunkTypes_arraysize;
    for (size_t i = 0; i < sctpChunkTypes_arraysize; i++) {
        this->sctpChunkTypes[i] = other.sctpChunkTypes[i];
    }
}

void SctpSupportedExtensionsParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    b->pack(sctpChunkTypes_arraysize);
    doParsimArrayPacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
}

void SctpSupportedExtensionsParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    delete [] this->sctpChunkTypes;
    b->unpack(sctpChunkTypes_arraysize);
    if (sctpChunkTypes_arraysize == 0) {
        this->sctpChunkTypes = nullptr;
    } else {
        this->sctpChunkTypes = new uint16_t[sctpChunkTypes_arraysize];
        doParsimArrayUnpacking(b,this->sctpChunkTypes,sctpChunkTypes_arraysize);
    }
}

size_t SctpSupportedExtensionsParameter::getSctpChunkTypesArraySize() const
{
    return sctpChunkTypes_arraysize;
}

uint16_t SctpSupportedExtensionsParameter::getSctpChunkTypes(size_t k) const
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    return this->sctpChunkTypes[k];
}

void SctpSupportedExtensionsParameter::setSctpChunkTypesArraySize(size_t newSize)
{
    uint16_t *sctpChunkTypes2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = sctpChunkTypes_arraysize < newSize ? sctpChunkTypes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (size_t i = minSize; i < newSize; i++)
        sctpChunkTypes2[i] = 0;
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpSupportedExtensionsParameter::setSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    this->sctpChunkTypes[k] = sctpChunkTypes;
}

void SctpSupportedExtensionsParameter::insertSctpChunkTypes(size_t k, uint16_t sctpChunkTypes)
{
    if (k > sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize + 1;
    uint16_t *sctpChunkTypes2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    sctpChunkTypes2[k] = sctpChunkTypes;
    for (i = k + 1; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i-1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

void SctpSupportedExtensionsParameter::appendSctpChunkTypes(uint16_t sctpChunkTypes)
{
    insertSctpChunkTypes(sctpChunkTypes_arraysize, sctpChunkTypes);
}

void SctpSupportedExtensionsParameter::eraseSctpChunkTypes(size_t k)
{
    if (k >= sctpChunkTypes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sctpChunkTypes_arraysize, (unsigned long)k);
    size_t newSize = sctpChunkTypes_arraysize - 1;
    uint16_t *sctpChunkTypes2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i];
    for (i = k; i < newSize; i++)
        sctpChunkTypes2[i] = this->sctpChunkTypes[i+1];
    delete [] this->sctpChunkTypes;
    this->sctpChunkTypes = sctpChunkTypes2;
    sctpChunkTypes_arraysize = newSize;
}

class SctpSupportedExtensionsParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sctpChunkTypes,
    };
  public:
    SctpSupportedExtensionsParameterDescriptor();
    virtual ~SctpSupportedExtensionsParameterDescriptor();

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

Register_ClassDescriptor(SctpSupportedExtensionsParameterDescriptor)

SctpSupportedExtensionsParameterDescriptor::SctpSupportedExtensionsParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSupportedExtensionsParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpSupportedExtensionsParameterDescriptor::~SctpSupportedExtensionsParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpSupportedExtensionsParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSupportedExtensionsParameter *>(obj)!=nullptr;
}

const char **SctpSupportedExtensionsParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSupportedExtensionsParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSupportedExtensionsParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpSupportedExtensionsParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sctpChunkTypes
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpSupportedExtensionsParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sctpChunkTypes",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpSupportedExtensionsParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sctpChunkTypes") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSupportedExtensionsParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_sctpChunkTypes
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSupportedExtensionsParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSupportedExtensionsParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSupportedExtensionsParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: return pp->getSctpChunkTypesArraySize();
        default: return 0;
    }
}

void SctpSupportedExtensionsParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSupportedExtensionsParameter'", field);
    }
}

const char *SctpSupportedExtensionsParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSupportedExtensionsParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: return ulong2string(pp->getSctpChunkTypes(i));
        default: return "";
    }
}

void SctpSupportedExtensionsParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSupportedExtensionsParameter'", field);
    }
}

omnetpp::cValue SctpSupportedExtensionsParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: return (omnetpp::intval_t)(pp->getSctpChunkTypes(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSupportedExtensionsParameter' as cValue -- field index out of range?", field);
    }
}

void SctpSupportedExtensionsParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        case FIELD_sctpChunkTypes: pp->setSctpChunkTypes(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSupportedExtensionsParameter'", field);
    }
}

const char *SctpSupportedExtensionsParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSupportedExtensionsParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSupportedExtensionsParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSupportedExtensionsParameter *pp = omnetpp::fromAnyPtr<SctpSupportedExtensionsParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSupportedExtensionsParameter'", field);
    }
}

Register_Class(SctpErrorCauseParameter)

SctpErrorCauseParameter::SctpErrorCauseParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpErrorCauseParameter::SctpErrorCauseParameter(const SctpErrorCauseParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpErrorCauseParameter::~SctpErrorCauseParameter()
{
}

SctpErrorCauseParameter& SctpErrorCauseParameter::operator=(const SctpErrorCauseParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpErrorCauseParameter::copy(const SctpErrorCauseParameter& other)
{
    this->responseCorrelationId = other.responseCorrelationId;
    this->errorCauseType = other.errorCauseType;
}

void SctpErrorCauseParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->responseCorrelationId);
    doParsimPacking(b,this->errorCauseType);
}

void SctpErrorCauseParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->responseCorrelationId);
    doParsimUnpacking(b,this->errorCauseType);
}

uint32_t SctpErrorCauseParameter::getResponseCorrelationId() const
{
    return this->responseCorrelationId;
}

void SctpErrorCauseParameter::setResponseCorrelationId(uint32_t responseCorrelationId)
{
    this->responseCorrelationId = responseCorrelationId;
}

uint32_t SctpErrorCauseParameter::getErrorCauseType() const
{
    return this->errorCauseType;
}

void SctpErrorCauseParameter::setErrorCauseType(uint32_t errorCauseType)
{
    this->errorCauseType = errorCauseType;
}

class SctpErrorCauseParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_responseCorrelationId,
        FIELD_errorCauseType,
    };
  public:
    SctpErrorCauseParameterDescriptor();
    virtual ~SctpErrorCauseParameterDescriptor();

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

Register_ClassDescriptor(SctpErrorCauseParameterDescriptor)

SctpErrorCauseParameterDescriptor::SctpErrorCauseParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpErrorCauseParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpErrorCauseParameterDescriptor::~SctpErrorCauseParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpErrorCauseParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpErrorCauseParameter *>(obj)!=nullptr;
}

const char **SctpErrorCauseParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpErrorCauseParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpErrorCauseParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SctpErrorCauseParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_responseCorrelationId
        FD_ISEDITABLE,    // FIELD_errorCauseType
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SctpErrorCauseParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "responseCorrelationId",
        "errorCauseType",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SctpErrorCauseParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "responseCorrelationId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "errorCauseType") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpErrorCauseParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_responseCorrelationId
        "uint32_t",    // FIELD_errorCauseType
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpErrorCauseParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpErrorCauseParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpErrorCauseParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpErrorCauseParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpErrorCauseParameter'", field);
    }
}

const char *SctpErrorCauseParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpErrorCauseParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: return ulong2string(pp->getResponseCorrelationId());
        case FIELD_errorCauseType: return ulong2string(pp->getErrorCauseType());
        default: return "";
    }
}

void SctpErrorCauseParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: pp->setResponseCorrelationId(string2ulong(value)); break;
        case FIELD_errorCauseType: pp->setErrorCauseType(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorCauseParameter'", field);
    }
}

omnetpp::cValue SctpErrorCauseParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: return (omnetpp::intval_t)(pp->getResponseCorrelationId());
        case FIELD_errorCauseType: return (omnetpp::intval_t)(pp->getErrorCauseType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpErrorCauseParameter' as cValue -- field index out of range?", field);
    }
}

void SctpErrorCauseParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: pp->setResponseCorrelationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_errorCauseType: pp->setErrorCauseType(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorCauseParameter'", field);
    }
}

const char *SctpErrorCauseParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpErrorCauseParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpErrorCauseParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpErrorCauseParameter'", field);
    }
}

Register_Class(SctpSimpleErrorCauseParameter)

SctpSimpleErrorCauseParameter::SctpSimpleErrorCauseParameter(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpSimpleErrorCauseParameter::SctpSimpleErrorCauseParameter(const SctpSimpleErrorCauseParameter& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpSimpleErrorCauseParameter::~SctpSimpleErrorCauseParameter()
{
}

SctpSimpleErrorCauseParameter& SctpSimpleErrorCauseParameter::operator=(const SctpSimpleErrorCauseParameter& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpSimpleErrorCauseParameter::copy(const SctpSimpleErrorCauseParameter& other)
{
    this->value = other.value;
}

void SctpSimpleErrorCauseParameter::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->value);
}

void SctpSimpleErrorCauseParameter::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
}

uint16_t SctpSimpleErrorCauseParameter::getValue() const
{
    return this->value;
}

void SctpSimpleErrorCauseParameter::setValue(uint16_t value)
{
    this->value = value;
}

class SctpSimpleErrorCauseParameterDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    SctpSimpleErrorCauseParameterDescriptor();
    virtual ~SctpSimpleErrorCauseParameterDescriptor();

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

Register_ClassDescriptor(SctpSimpleErrorCauseParameterDescriptor)

SctpSimpleErrorCauseParameterDescriptor::SctpSimpleErrorCauseParameterDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSimpleErrorCauseParameter)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpSimpleErrorCauseParameterDescriptor::~SctpSimpleErrorCauseParameterDescriptor()
{
    delete[] propertyNames;
}

bool SctpSimpleErrorCauseParameterDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSimpleErrorCauseParameter *>(obj)!=nullptr;
}

const char **SctpSimpleErrorCauseParameterDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSimpleErrorCauseParameterDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSimpleErrorCauseParameterDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpSimpleErrorCauseParameterDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpSimpleErrorCauseParameterDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "value",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpSimpleErrorCauseParameterDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSimpleErrorCauseParameterDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSimpleErrorCauseParameterDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSimpleErrorCauseParameterDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSimpleErrorCauseParameterDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpSimpleErrorCauseParameterDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSimpleErrorCauseParameter'", field);
    }
}

const char *SctpSimpleErrorCauseParameterDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSimpleErrorCauseParameterDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_value: return ulong2string(pp->getValue());
        default: return "";
    }
}

void SctpSimpleErrorCauseParameterDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleErrorCauseParameter'", field);
    }
}

omnetpp::cValue SctpSimpleErrorCauseParameterDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_value: return (omnetpp::intval_t)(pp->getValue());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSimpleErrorCauseParameter' as cValue -- field index out of range?", field);
    }
}

void SctpSimpleErrorCauseParameterDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleErrorCauseParameter'", field);
    }
}

const char *SctpSimpleErrorCauseParameterDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSimpleErrorCauseParameterDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSimpleErrorCauseParameterDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSimpleErrorCauseParameter *pp = omnetpp::fromAnyPtr<SctpSimpleErrorCauseParameter>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSimpleErrorCauseParameter'", field);
    }
}

Register_Class(SctpSuccessIndication)

SctpSuccessIndication::SctpSuccessIndication(const char *name) : ::inet::sctp::SctpParameter(name)
{
}

SctpSuccessIndication::SctpSuccessIndication(const SctpSuccessIndication& other) : ::inet::sctp::SctpParameter(other)
{
    copy(other);
}

SctpSuccessIndication::~SctpSuccessIndication()
{
}

SctpSuccessIndication& SctpSuccessIndication::operator=(const SctpSuccessIndication& other)
{
    if (this == &other) return *this;
    ::inet::sctp::SctpParameter::operator=(other);
    copy(other);
    return *this;
}

void SctpSuccessIndication::copy(const SctpSuccessIndication& other)
{
    this->responseCorrelationId = other.responseCorrelationId;
}

void SctpSuccessIndication::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::sctp::SctpParameter::parsimPack(b);
    doParsimPacking(b,this->responseCorrelationId);
}

void SctpSuccessIndication::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::sctp::SctpParameter::parsimUnpack(b);
    doParsimUnpacking(b,this->responseCorrelationId);
}

uint32_t SctpSuccessIndication::getResponseCorrelationId() const
{
    return this->responseCorrelationId;
}

void SctpSuccessIndication::setResponseCorrelationId(uint32_t responseCorrelationId)
{
    this->responseCorrelationId = responseCorrelationId;
}

class SctpSuccessIndicationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_responseCorrelationId,
    };
  public:
    SctpSuccessIndicationDescriptor();
    virtual ~SctpSuccessIndicationDescriptor();

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

Register_ClassDescriptor(SctpSuccessIndicationDescriptor)

SctpSuccessIndicationDescriptor::SctpSuccessIndicationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::SctpSuccessIndication)), "inet::sctp::SctpParameter")
{
    propertyNames = nullptr;
}

SctpSuccessIndicationDescriptor::~SctpSuccessIndicationDescriptor()
{
    delete[] propertyNames;
}

bool SctpSuccessIndicationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SctpSuccessIndication *>(obj)!=nullptr;
}

const char **SctpSuccessIndicationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SctpSuccessIndicationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SctpSuccessIndicationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SctpSuccessIndicationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_responseCorrelationId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SctpSuccessIndicationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "responseCorrelationId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SctpSuccessIndicationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "responseCorrelationId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SctpSuccessIndicationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_responseCorrelationId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SctpSuccessIndicationDescriptor::getFieldPropertyNames(int field) const
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

const char *SctpSuccessIndicationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SctpSuccessIndicationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SctpSuccessIndicationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SctpSuccessIndication'", field);
    }
}

const char *SctpSuccessIndicationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SctpSuccessIndicationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: return ulong2string(pp->getResponseCorrelationId());
        default: return "";
    }
}

void SctpSuccessIndicationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: pp->setResponseCorrelationId(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSuccessIndication'", field);
    }
}

omnetpp::cValue SctpSuccessIndicationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: return (omnetpp::intval_t)(pp->getResponseCorrelationId());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SctpSuccessIndication' as cValue -- field index out of range?", field);
    }
}

void SctpSuccessIndicationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        case FIELD_responseCorrelationId: pp->setResponseCorrelationId(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSuccessIndication'", field);
    }
}

const char *SctpSuccessIndicationDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SctpSuccessIndicationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SctpSuccessIndicationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SctpSuccessIndication *pp = omnetpp::fromAnyPtr<SctpSuccessIndication>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SctpSuccessIndication'", field);
    }
}

Register_Class(NatMessage)

NatMessage::NatMessage(const char *name) : ::omnetpp::cMessage(name)
{
}

NatMessage::NatMessage(const NatMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NatMessage::~NatMessage()
{
    delete [] this->peer1Addresses;
    delete [] this->peer2Addresses;
}

NatMessage& NatMessage::operator=(const NatMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NatMessage::copy(const NatMessage& other)
{
    this->multi = other.multi;
    this->peer1 = other.peer1;
    delete [] this->peer1Addresses;
    this->peer1Addresses = (other.peer1Addresses_arraysize==0) ? nullptr : new ::inet::L3Address[other.peer1Addresses_arraysize];
    peer1Addresses_arraysize = other.peer1Addresses_arraysize;
    for (size_t i = 0; i < peer1Addresses_arraysize; i++) {
        this->peer1Addresses[i] = other.peer1Addresses[i];
    }
    this->portPeer1 = other.portPeer1;
    this->peer2 = other.peer2;
    delete [] this->peer2Addresses;
    this->peer2Addresses = (other.peer2Addresses_arraysize==0) ? nullptr : new ::inet::L3Address[other.peer2Addresses_arraysize];
    peer2Addresses_arraysize = other.peer2Addresses_arraysize;
    for (size_t i = 0; i < peer2Addresses_arraysize; i++) {
        this->peer2Addresses[i] = other.peer2Addresses[i];
    }
    this->portPeer2 = other.portPeer2;
}

void NatMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->multi);
    doParsimPacking(b,this->peer1);
    b->pack(peer1Addresses_arraysize);
    doParsimArrayPacking(b,this->peer1Addresses,peer1Addresses_arraysize);
    doParsimPacking(b,this->portPeer1);
    doParsimPacking(b,this->peer2);
    b->pack(peer2Addresses_arraysize);
    doParsimArrayPacking(b,this->peer2Addresses,peer2Addresses_arraysize);
    doParsimPacking(b,this->portPeer2);
}

void NatMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->multi);
    doParsimUnpacking(b,this->peer1);
    delete [] this->peer1Addresses;
    b->unpack(peer1Addresses_arraysize);
    if (peer1Addresses_arraysize == 0) {
        this->peer1Addresses = nullptr;
    } else {
        this->peer1Addresses = new ::inet::L3Address[peer1Addresses_arraysize];
        doParsimArrayUnpacking(b,this->peer1Addresses,peer1Addresses_arraysize);
    }
    doParsimUnpacking(b,this->portPeer1);
    doParsimUnpacking(b,this->peer2);
    delete [] this->peer2Addresses;
    b->unpack(peer2Addresses_arraysize);
    if (peer2Addresses_arraysize == 0) {
        this->peer2Addresses = nullptr;
    } else {
        this->peer2Addresses = new ::inet::L3Address[peer2Addresses_arraysize];
        doParsimArrayUnpacking(b,this->peer2Addresses,peer2Addresses_arraysize);
    }
    doParsimUnpacking(b,this->portPeer2);
}

bool NatMessage::getMulti() const
{
    return this->multi;
}

void NatMessage::setMulti(bool multi)
{
    this->multi = multi;
}

uint16_t NatMessage::getPeer1() const
{
    return this->peer1;
}

void NatMessage::setPeer1(uint16_t peer1)
{
    this->peer1 = peer1;
}

size_t NatMessage::getPeer1AddressesArraySize() const
{
    return peer1Addresses_arraysize;
}

const ::inet::L3Address& NatMessage::getPeer1Addresses(size_t k) const
{
    if (k >= peer1Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer1Addresses_arraysize, (unsigned long)k);
    return this->peer1Addresses[k];
}

void NatMessage::setPeer1AddressesArraySize(size_t newSize)
{
    ::inet::L3Address *peer1Addresses2 = (newSize==0) ? nullptr : new ::inet::L3Address[newSize];
    size_t minSize = peer1Addresses_arraysize < newSize ? peer1Addresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        peer1Addresses2[i] = this->peer1Addresses[i];
    delete [] this->peer1Addresses;
    this->peer1Addresses = peer1Addresses2;
    peer1Addresses_arraysize = newSize;
}

void NatMessage::setPeer1Addresses(size_t k, const ::inet::L3Address& peer1Addresses)
{
    if (k >= peer1Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer1Addresses_arraysize, (unsigned long)k);
    this->peer1Addresses[k] = peer1Addresses;
}

void NatMessage::insertPeer1Addresses(size_t k, const ::inet::L3Address& peer1Addresses)
{
    if (k > peer1Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer1Addresses_arraysize, (unsigned long)k);
    size_t newSize = peer1Addresses_arraysize + 1;
    ::inet::L3Address *peer1Addresses2 = new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peer1Addresses2[i] = this->peer1Addresses[i];
    peer1Addresses2[k] = peer1Addresses;
    for (i = k + 1; i < newSize; i++)
        peer1Addresses2[i] = this->peer1Addresses[i-1];
    delete [] this->peer1Addresses;
    this->peer1Addresses = peer1Addresses2;
    peer1Addresses_arraysize = newSize;
}

void NatMessage::appendPeer1Addresses(const ::inet::L3Address& peer1Addresses)
{
    insertPeer1Addresses(peer1Addresses_arraysize, peer1Addresses);
}

void NatMessage::erasePeer1Addresses(size_t k)
{
    if (k >= peer1Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer1Addresses_arraysize, (unsigned long)k);
    size_t newSize = peer1Addresses_arraysize - 1;
    ::inet::L3Address *peer1Addresses2 = (newSize == 0) ? nullptr : new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peer1Addresses2[i] = this->peer1Addresses[i];
    for (i = k; i < newSize; i++)
        peer1Addresses2[i] = this->peer1Addresses[i+1];
    delete [] this->peer1Addresses;
    this->peer1Addresses = peer1Addresses2;
    peer1Addresses_arraysize = newSize;
}

uint32_t NatMessage::getPortPeer1() const
{
    return this->portPeer1;
}

void NatMessage::setPortPeer1(uint32_t portPeer1)
{
    this->portPeer1 = portPeer1;
}

uint16_t NatMessage::getPeer2() const
{
    return this->peer2;
}

void NatMessage::setPeer2(uint16_t peer2)
{
    this->peer2 = peer2;
}

size_t NatMessage::getPeer2AddressesArraySize() const
{
    return peer2Addresses_arraysize;
}

const ::inet::L3Address& NatMessage::getPeer2Addresses(size_t k) const
{
    if (k >= peer2Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer2Addresses_arraysize, (unsigned long)k);
    return this->peer2Addresses[k];
}

void NatMessage::setPeer2AddressesArraySize(size_t newSize)
{
    ::inet::L3Address *peer2Addresses2 = (newSize==0) ? nullptr : new ::inet::L3Address[newSize];
    size_t minSize = peer2Addresses_arraysize < newSize ? peer2Addresses_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        peer2Addresses2[i] = this->peer2Addresses[i];
    delete [] this->peer2Addresses;
    this->peer2Addresses = peer2Addresses2;
    peer2Addresses_arraysize = newSize;
}

void NatMessage::setPeer2Addresses(size_t k, const ::inet::L3Address& peer2Addresses)
{
    if (k >= peer2Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer2Addresses_arraysize, (unsigned long)k);
    this->peer2Addresses[k] = peer2Addresses;
}

void NatMessage::insertPeer2Addresses(size_t k, const ::inet::L3Address& peer2Addresses)
{
    if (k > peer2Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer2Addresses_arraysize, (unsigned long)k);
    size_t newSize = peer2Addresses_arraysize + 1;
    ::inet::L3Address *peer2Addresses2 = new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peer2Addresses2[i] = this->peer2Addresses[i];
    peer2Addresses2[k] = peer2Addresses;
    for (i = k + 1; i < newSize; i++)
        peer2Addresses2[i] = this->peer2Addresses[i-1];
    delete [] this->peer2Addresses;
    this->peer2Addresses = peer2Addresses2;
    peer2Addresses_arraysize = newSize;
}

void NatMessage::appendPeer2Addresses(const ::inet::L3Address& peer2Addresses)
{
    insertPeer2Addresses(peer2Addresses_arraysize, peer2Addresses);
}

void NatMessage::erasePeer2Addresses(size_t k)
{
    if (k >= peer2Addresses_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)peer2Addresses_arraysize, (unsigned long)k);
    size_t newSize = peer2Addresses_arraysize - 1;
    ::inet::L3Address *peer2Addresses2 = (newSize == 0) ? nullptr : new ::inet::L3Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        peer2Addresses2[i] = this->peer2Addresses[i];
    for (i = k; i < newSize; i++)
        peer2Addresses2[i] = this->peer2Addresses[i+1];
    delete [] this->peer2Addresses;
    this->peer2Addresses = peer2Addresses2;
    peer2Addresses_arraysize = newSize;
}

uint32_t NatMessage::getPortPeer2() const
{
    return this->portPeer2;
}

void NatMessage::setPortPeer2(uint32_t portPeer2)
{
    this->portPeer2 = portPeer2;
}

class NatMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_multi,
        FIELD_peer1,
        FIELD_peer1Addresses,
        FIELD_portPeer1,
        FIELD_peer2,
        FIELD_peer2Addresses,
        FIELD_portPeer2,
    };
  public:
    NatMessageDescriptor();
    virtual ~NatMessageDescriptor();

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

Register_ClassDescriptor(NatMessageDescriptor)

NatMessageDescriptor::NatMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::sctp::NatMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

NatMessageDescriptor::~NatMessageDescriptor()
{
    delete[] propertyNames;
}

bool NatMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NatMessage *>(obj)!=nullptr;
}

const char **NatMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NatMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NatMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int NatMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_multi
        FD_ISEDITABLE,    // FIELD_peer1
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_peer1Addresses
        FD_ISEDITABLE,    // FIELD_portPeer1
        FD_ISEDITABLE,    // FIELD_peer2
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_peer2Addresses
        FD_ISEDITABLE,    // FIELD_portPeer2
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *NatMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "multi",
        "peer1",
        "peer1Addresses",
        "portPeer1",
        "peer2",
        "peer2Addresses",
        "portPeer2",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int NatMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "multi") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "peer1") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "peer1Addresses") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "portPeer1") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "peer2") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "peer2Addresses") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "portPeer2") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *NatMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_multi
        "uint16_t",    // FIELD_peer1
        "inet::L3Address",    // FIELD_peer1Addresses
        "uint32_t",    // FIELD_portPeer1
        "uint16_t",    // FIELD_peer2
        "inet::L3Address",    // FIELD_peer2Addresses
        "uint32_t",    // FIELD_portPeer2
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **NatMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *NatMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int NatMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_peer1Addresses: return pp->getPeer1AddressesArraySize();
        case FIELD_peer2Addresses: return pp->getPeer2AddressesArraySize();
        default: return 0;
    }
}

void NatMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_peer1Addresses: pp->setPeer1AddressesArraySize(size); break;
        case FIELD_peer2Addresses: pp->setPeer2AddressesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NatMessage'", field);
    }
}

const char *NatMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NatMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_multi: return bool2string(pp->getMulti());
        case FIELD_peer1: return ulong2string(pp->getPeer1());
        case FIELD_peer1Addresses: return pp->getPeer1Addresses(i).str();
        case FIELD_portPeer1: return ulong2string(pp->getPortPeer1());
        case FIELD_peer2: return ulong2string(pp->getPeer2());
        case FIELD_peer2Addresses: return pp->getPeer2Addresses(i).str();
        case FIELD_portPeer2: return ulong2string(pp->getPortPeer2());
        default: return "";
    }
}

void NatMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_multi: pp->setMulti(string2bool(value)); break;
        case FIELD_peer1: pp->setPeer1(string2ulong(value)); break;
        case FIELD_portPeer1: pp->setPortPeer1(string2ulong(value)); break;
        case FIELD_peer2: pp->setPeer2(string2ulong(value)); break;
        case FIELD_portPeer2: pp->setPortPeer2(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NatMessage'", field);
    }
}

omnetpp::cValue NatMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_multi: return pp->getMulti();
        case FIELD_peer1: return (omnetpp::intval_t)(pp->getPeer1());
        case FIELD_peer1Addresses: return omnetpp::toAnyPtr(&pp->getPeer1Addresses(i)); break;
        case FIELD_portPeer1: return (omnetpp::intval_t)(pp->getPortPeer1());
        case FIELD_peer2: return (omnetpp::intval_t)(pp->getPeer2());
        case FIELD_peer2Addresses: return omnetpp::toAnyPtr(&pp->getPeer2Addresses(i)); break;
        case FIELD_portPeer2: return (omnetpp::intval_t)(pp->getPortPeer2());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NatMessage' as cValue -- field index out of range?", field);
    }
}

void NatMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_multi: pp->setMulti(value.boolValue()); break;
        case FIELD_peer1: pp->setPeer1(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_portPeer1: pp->setPortPeer1(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_peer2: pp->setPeer2(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_portPeer2: pp->setPortPeer2(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NatMessage'", field);
    }
}

const char *NatMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr NatMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        case FIELD_peer1Addresses: return omnetpp::toAnyPtr(&pp->getPeer1Addresses(i)); break;
        case FIELD_peer2Addresses: return omnetpp::toAnyPtr(&pp->getPeer2Addresses(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NatMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NatMessage *pp = omnetpp::fromAnyPtr<NatMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NatMessage'", field);
    }
}

}  // namespace sctp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

