//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtpPacket.msg.
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
#include "RtpPacket_m.h"

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

Register_Class(RtpHeader)

RtpHeader::RtpHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(RTPPACKET_FIX_HEADERLENGTH);

}

RtpHeader::RtpHeader(const RtpHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

RtpHeader::~RtpHeader()
{
    delete [] this->csrc;
}

RtpHeader& RtpHeader::operator=(const RtpHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void RtpHeader::copy(const RtpHeader& other)
{
    this->version = other.version;
    this->paddingFlag = other.paddingFlag;
    this->extensionFlag = other.extensionFlag;
    this->marker = other.marker;
    this->payloadType = other.payloadType;
    this->sequenceNumber = other.sequenceNumber;
    this->timeStamp = other.timeStamp;
    this->ssrc = other.ssrc;
    delete [] this->csrc;
    this->csrc = (other.csrc_arraysize==0) ? nullptr : new uint32_t[other.csrc_arraysize];
    csrc_arraysize = other.csrc_arraysize;
    for (size_t i = 0; i < csrc_arraysize; i++) {
        this->csrc[i] = other.csrc[i];
    }
}

void RtpHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->paddingFlag);
    doParsimPacking(b,this->extensionFlag);
    doParsimPacking(b,this->marker);
    doParsimPacking(b,this->payloadType);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->timeStamp);
    doParsimPacking(b,this->ssrc);
    b->pack(csrc_arraysize);
    doParsimArrayPacking(b,this->csrc,csrc_arraysize);
}

void RtpHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->paddingFlag);
    doParsimUnpacking(b,this->extensionFlag);
    doParsimUnpacking(b,this->marker);
    doParsimUnpacking(b,this->payloadType);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->timeStamp);
    doParsimUnpacking(b,this->ssrc);
    delete [] this->csrc;
    b->unpack(csrc_arraysize);
    if (csrc_arraysize == 0) {
        this->csrc = nullptr;
    } else {
        this->csrc = new uint32_t[csrc_arraysize];
        doParsimArrayUnpacking(b,this->csrc,csrc_arraysize);
    }
}

uint8_t RtpHeader::getVersion() const
{
    return this->version;
}

void RtpHeader::setVersion(uint8_t version)
{
    handleChange();
    this->version = version;
}

bool RtpHeader::getPaddingFlag() const
{
    return this->paddingFlag;
}

void RtpHeader::setPaddingFlag(bool paddingFlag)
{
    handleChange();
    this->paddingFlag = paddingFlag;
}

bool RtpHeader::getExtensionFlag() const
{
    return this->extensionFlag;
}

void RtpHeader::setExtensionFlag(bool extensionFlag)
{
    handleChange();
    this->extensionFlag = extensionFlag;
}

bool RtpHeader::getMarker() const
{
    return this->marker;
}

void RtpHeader::setMarker(bool marker)
{
    handleChange();
    this->marker = marker;
}

int8_t RtpHeader::getPayloadType() const
{
    return this->payloadType;
}

void RtpHeader::setPayloadType(int8_t payloadType)
{
    handleChange();
    this->payloadType = payloadType;
}

uint16_t RtpHeader::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void RtpHeader::setSequenceNumber(uint16_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

uint32_t RtpHeader::getTimeStamp() const
{
    return this->timeStamp;
}

void RtpHeader::setTimeStamp(uint32_t timeStamp)
{
    handleChange();
    this->timeStamp = timeStamp;
}

uint32_t RtpHeader::getSsrc() const
{
    return this->ssrc;
}

void RtpHeader::setSsrc(uint32_t ssrc)
{
    handleChange();
    this->ssrc = ssrc;
}

size_t RtpHeader::getCsrcArraySize() const
{
    return csrc_arraysize;
}

uint32_t RtpHeader::getCsrc(size_t k) const
{
    if (k >= csrc_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)csrc_arraysize, (unsigned long)k);
    return this->csrc[k];
}

void RtpHeader::setCsrcArraySize(size_t newSize)
{
    handleChange();
    uint32_t *csrc2 = (newSize==0) ? nullptr : new uint32_t[newSize];
    size_t minSize = csrc_arraysize < newSize ? csrc_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        csrc2[i] = this->csrc[i];
    for (size_t i = minSize; i < newSize; i++)
        csrc2[i] = 0;
    delete [] this->csrc;
    this->csrc = csrc2;
    csrc_arraysize = newSize;
}

void RtpHeader::setCsrc(size_t k, uint32_t csrc)
{
    if (k >= csrc_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)csrc_arraysize, (unsigned long)k);
    handleChange();
    this->csrc[k] = csrc;
}

void RtpHeader::insertCsrc(size_t k, uint32_t csrc)
{
    if (k > csrc_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)csrc_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = csrc_arraysize + 1;
    uint32_t *csrc2 = new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        csrc2[i] = this->csrc[i];
    csrc2[k] = csrc;
    for (i = k + 1; i < newSize; i++)
        csrc2[i] = this->csrc[i-1];
    delete [] this->csrc;
    this->csrc = csrc2;
    csrc_arraysize = newSize;
}

void RtpHeader::appendCsrc(uint32_t csrc)
{
    insertCsrc(csrc_arraysize, csrc);
}

void RtpHeader::eraseCsrc(size_t k)
{
    if (k >= csrc_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)csrc_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = csrc_arraysize - 1;
    uint32_t *csrc2 = (newSize == 0) ? nullptr : new uint32_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        csrc2[i] = this->csrc[i];
    for (i = k; i < newSize; i++)
        csrc2[i] = this->csrc[i+1];
    delete [] this->csrc;
    this->csrc = csrc2;
    csrc_arraysize = newSize;
}

class RtpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_paddingFlag,
        FIELD_extensionFlag,
        FIELD_marker,
        FIELD_payloadType,
        FIELD_sequenceNumber,
        FIELD_timeStamp,
        FIELD_ssrc,
        FIELD_csrc,
    };
  public:
    RtpHeaderDescriptor();
    virtual ~RtpHeaderDescriptor();

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

Register_ClassDescriptor(RtpHeaderDescriptor)

RtpHeaderDescriptor::RtpHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

RtpHeaderDescriptor::~RtpHeaderDescriptor()
{
    delete[] propertyNames;
}

bool RtpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpHeader *>(obj)!=nullptr;
}

const char **RtpHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int RtpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        FD_ISEDITABLE,    // FIELD_paddingFlag
        FD_ISEDITABLE,    // FIELD_extensionFlag
        FD_ISEDITABLE,    // FIELD_marker
        FD_ISEDITABLE,    // FIELD_payloadType
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_timeStamp
        FD_ISEDITABLE,    // FIELD_ssrc
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_csrc
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *RtpHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "paddingFlag",
        "extensionFlag",
        "marker",
        "payloadType",
        "sequenceNumber",
        "timeStamp",
        "ssrc",
        "csrc",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int RtpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "paddingFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "extensionFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "marker") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "payloadType") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "timeStamp") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "ssrc") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "csrc") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_version
        "bool",    // FIELD_paddingFlag
        "bool",    // FIELD_extensionFlag
        "bool",    // FIELD_marker
        "int8_t",    // FIELD_payloadType
        "uint16_t",    // FIELD_sequenceNumber
        "uint32_t",    // FIELD_timeStamp
        "uint32_t",    // FIELD_ssrc
        "uint32_t",    // FIELD_csrc
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_csrc: return pp->getCsrcArraySize();
        default: return 0;
    }
}

void RtpHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_csrc: pp->setCsrcArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpHeader'", field);
    }
}

const char *RtpHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_version: return ulong2string(pp->getVersion());
        case FIELD_paddingFlag: return bool2string(pp->getPaddingFlag());
        case FIELD_extensionFlag: return bool2string(pp->getExtensionFlag());
        case FIELD_marker: return bool2string(pp->getMarker());
        case FIELD_payloadType: return long2string(pp->getPayloadType());
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_timeStamp: return ulong2string(pp->getTimeStamp());
        case FIELD_ssrc: return ulong2string(pp->getSsrc());
        case FIELD_csrc: return ulong2string(pp->getCsrc(i));
        default: return "";
    }
}

void RtpHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2ulong(value)); break;
        case FIELD_paddingFlag: pp->setPaddingFlag(string2bool(value)); break;
        case FIELD_extensionFlag: pp->setExtensionFlag(string2bool(value)); break;
        case FIELD_marker: pp->setMarker(string2bool(value)); break;
        case FIELD_payloadType: pp->setPayloadType(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); break;
        case FIELD_timeStamp: pp->setTimeStamp(string2ulong(value)); break;
        case FIELD_ssrc: pp->setSsrc(string2ulong(value)); break;
        case FIELD_csrc: pp->setCsrc(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpHeader'", field);
    }
}

omnetpp::cValue RtpHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_version: return (omnetpp::intval_t)(pp->getVersion());
        case FIELD_paddingFlag: return pp->getPaddingFlag();
        case FIELD_extensionFlag: return pp->getExtensionFlag();
        case FIELD_marker: return pp->getMarker();
        case FIELD_payloadType: return pp->getPayloadType();
        case FIELD_sequenceNumber: return (omnetpp::intval_t)(pp->getSequenceNumber());
        case FIELD_timeStamp: return (omnetpp::intval_t)(pp->getTimeStamp());
        case FIELD_ssrc: return (omnetpp::intval_t)(pp->getSsrc());
        case FIELD_csrc: return (omnetpp::intval_t)(pp->getCsrc(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpHeader' as cValue -- field index out of range?", field);
    }
}

void RtpHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_paddingFlag: pp->setPaddingFlag(value.boolValue()); break;
        case FIELD_extensionFlag: pp->setExtensionFlag(value.boolValue()); break;
        case FIELD_marker: pp->setMarker(value.boolValue()); break;
        case FIELD_payloadType: pp->setPayloadType(omnetpp::checked_int_cast<int8_t>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_timeStamp: pp->setTimeStamp(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_ssrc: pp->setSsrc(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_csrc: pp->setCsrc(i,omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpHeader'", field);
    }
}

const char *RtpHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpHeader *pp = omnetpp::fromAnyPtr<RtpHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpHeader'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

