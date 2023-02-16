//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/profiles/avprofile/RtpMpegPacket.msg.
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
#include "RtpMpegPacket_m.h"

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

Register_Class(RtpMpegHeader)

RtpMpegHeader::RtpMpegHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

RtpMpegHeader::RtpMpegHeader(const RtpMpegHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

RtpMpegHeader::~RtpMpegHeader()
{
}

RtpMpegHeader& RtpMpegHeader::operator=(const RtpMpegHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void RtpMpegHeader::copy(const RtpMpegHeader& other)
{
    this->headerLength = other.headerLength;
    this->payloadLength = other.payloadLength;
    this->mbz = other.mbz;
    this->two = other.two;
    this->temporalReference = other.temporalReference;
    this->activeN = other.activeN;
    this->newPictureHeader = other.newPictureHeader;
    this->sequenceHeaderPresent = other.sequenceHeaderPresent;
    this->beginningOfSlice = other.beginningOfSlice;
    this->endOfSlice = other.endOfSlice;
    this->pictureType = other.pictureType;
    this->fbv = other.fbv;
    this->bfc = other.bfc;
    this->ffv = other.ffv;
    this->ffc = other.ffc;
}

void RtpMpegHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->payloadLength);
    doParsimPacking(b,this->mbz);
    doParsimPacking(b,this->two);
    doParsimPacking(b,this->temporalReference);
    doParsimPacking(b,this->activeN);
    doParsimPacking(b,this->newPictureHeader);
    doParsimPacking(b,this->sequenceHeaderPresent);
    doParsimPacking(b,this->beginningOfSlice);
    doParsimPacking(b,this->endOfSlice);
    doParsimPacking(b,this->pictureType);
    doParsimPacking(b,this->fbv);
    doParsimPacking(b,this->bfc);
    doParsimPacking(b,this->ffv);
    doParsimPacking(b,this->ffc);
}

void RtpMpegHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->payloadLength);
    doParsimUnpacking(b,this->mbz);
    doParsimUnpacking(b,this->two);
    doParsimUnpacking(b,this->temporalReference);
    doParsimUnpacking(b,this->activeN);
    doParsimUnpacking(b,this->newPictureHeader);
    doParsimUnpacking(b,this->sequenceHeaderPresent);
    doParsimUnpacking(b,this->beginningOfSlice);
    doParsimUnpacking(b,this->endOfSlice);
    doParsimUnpacking(b,this->pictureType);
    doParsimUnpacking(b,this->fbv);
    doParsimUnpacking(b,this->bfc);
    doParsimUnpacking(b,this->ffv);
    doParsimUnpacking(b,this->ffc);
}

int RtpMpegHeader::getHeaderLength() const
{
    return this->headerLength;
}

void RtpMpegHeader::setHeaderLength(int headerLength)
{
    handleChange();
    this->headerLength = headerLength;
}

int RtpMpegHeader::getPayloadLength() const
{
    return this->payloadLength;
}

void RtpMpegHeader::setPayloadLength(int payloadLength)
{
    handleChange();
    this->payloadLength = payloadLength;
}

uint8_t RtpMpegHeader::getMbz() const
{
    return this->mbz;
}

void RtpMpegHeader::setMbz(uint8_t mbz)
{
    handleChange();
    this->mbz = mbz;
}

bool RtpMpegHeader::getTwo() const
{
    return this->two;
}

void RtpMpegHeader::setTwo(bool two)
{
    handleChange();
    this->two = two;
}

uint16_t RtpMpegHeader::getTemporalReference() const
{
    return this->temporalReference;
}

void RtpMpegHeader::setTemporalReference(uint16_t temporalReference)
{
    handleChange();
    this->temporalReference = temporalReference;
}

bool RtpMpegHeader::getActiveN() const
{
    return this->activeN;
}

void RtpMpegHeader::setActiveN(bool activeN)
{
    handleChange();
    this->activeN = activeN;
}

bool RtpMpegHeader::getNewPictureHeader() const
{
    return this->newPictureHeader;
}

void RtpMpegHeader::setNewPictureHeader(bool newPictureHeader)
{
    handleChange();
    this->newPictureHeader = newPictureHeader;
}

bool RtpMpegHeader::getSequenceHeaderPresent() const
{
    return this->sequenceHeaderPresent;
}

void RtpMpegHeader::setSequenceHeaderPresent(bool sequenceHeaderPresent)
{
    handleChange();
    this->sequenceHeaderPresent = sequenceHeaderPresent;
}

bool RtpMpegHeader::getBeginningOfSlice() const
{
    return this->beginningOfSlice;
}

void RtpMpegHeader::setBeginningOfSlice(bool beginningOfSlice)
{
    handleChange();
    this->beginningOfSlice = beginningOfSlice;
}

bool RtpMpegHeader::getEndOfSlice() const
{
    return this->endOfSlice;
}

void RtpMpegHeader::setEndOfSlice(bool endOfSlice)
{
    handleChange();
    this->endOfSlice = endOfSlice;
}

uint8_t RtpMpegHeader::getPictureType() const
{
    return this->pictureType;
}

void RtpMpegHeader::setPictureType(uint8_t pictureType)
{
    handleChange();
    this->pictureType = pictureType;
}

bool RtpMpegHeader::getFbv() const
{
    return this->fbv;
}

void RtpMpegHeader::setFbv(bool fbv)
{
    handleChange();
    this->fbv = fbv;
}

uint8_t RtpMpegHeader::getBfc() const
{
    return this->bfc;
}

void RtpMpegHeader::setBfc(uint8_t bfc)
{
    handleChange();
    this->bfc = bfc;
}

bool RtpMpegHeader::getFfv() const
{
    return this->ffv;
}

void RtpMpegHeader::setFfv(bool ffv)
{
    handleChange();
    this->ffv = ffv;
}

uint8_t RtpMpegHeader::getFfc() const
{
    return this->ffc;
}

void RtpMpegHeader::setFfc(uint8_t ffc)
{
    handleChange();
    this->ffc = ffc;
}

class RtpMpegHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_headerLength,
        FIELD_payloadLength,
        FIELD_mbz,
        FIELD_two,
        FIELD_temporalReference,
        FIELD_activeN,
        FIELD_newPictureHeader,
        FIELD_sequenceHeaderPresent,
        FIELD_beginningOfSlice,
        FIELD_endOfSlice,
        FIELD_pictureType,
        FIELD_fbv,
        FIELD_bfc,
        FIELD_ffv,
        FIELD_ffc,
    };
  public:
    RtpMpegHeaderDescriptor();
    virtual ~RtpMpegHeaderDescriptor();

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

Register_ClassDescriptor(RtpMpegHeaderDescriptor)

RtpMpegHeaderDescriptor::RtpMpegHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::rtp::RtpMpegHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

RtpMpegHeaderDescriptor::~RtpMpegHeaderDescriptor()
{
    delete[] propertyNames;
}

bool RtpMpegHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RtpMpegHeader *>(obj)!=nullptr;
}

const char **RtpMpegHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RtpMpegHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RtpMpegHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 15+base->getFieldCount() : 15;
}

unsigned int RtpMpegHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_payloadLength
        FD_ISEDITABLE,    // FIELD_mbz
        FD_ISEDITABLE,    // FIELD_two
        FD_ISEDITABLE,    // FIELD_temporalReference
        FD_ISEDITABLE,    // FIELD_activeN
        FD_ISEDITABLE,    // FIELD_newPictureHeader
        FD_ISEDITABLE,    // FIELD_sequenceHeaderPresent
        FD_ISEDITABLE,    // FIELD_beginningOfSlice
        FD_ISEDITABLE,    // FIELD_endOfSlice
        FD_ISEDITABLE,    // FIELD_pictureType
        FD_ISEDITABLE,    // FIELD_fbv
        FD_ISEDITABLE,    // FIELD_bfc
        FD_ISEDITABLE,    // FIELD_ffv
        FD_ISEDITABLE,    // FIELD_ffc
    };
    return (field >= 0 && field < 15) ? fieldTypeFlags[field] : 0;
}

const char *RtpMpegHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "headerLength",
        "payloadLength",
        "mbz",
        "two",
        "temporalReference",
        "activeN",
        "newPictureHeader",
        "sequenceHeaderPresent",
        "beginningOfSlice",
        "endOfSlice",
        "pictureType",
        "fbv",
        "bfc",
        "ffv",
        "ffc",
    };
    return (field >= 0 && field < 15) ? fieldNames[field] : nullptr;
}

int RtpMpegHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "payloadLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "mbz") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "two") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "temporalReference") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "activeN") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "newPictureHeader") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sequenceHeaderPresent") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "beginningOfSlice") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "endOfSlice") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "pictureType") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "fbv") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "bfc") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "ffv") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "ffc") == 0) return baseIndex + 14;
    return base ? base->findField(fieldName) : -1;
}

const char *RtpMpegHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_headerLength
        "int",    // FIELD_payloadLength
        "uint8_t",    // FIELD_mbz
        "bool",    // FIELD_two
        "uint16_t",    // FIELD_temporalReference
        "bool",    // FIELD_activeN
        "bool",    // FIELD_newPictureHeader
        "bool",    // FIELD_sequenceHeaderPresent
        "bool",    // FIELD_beginningOfSlice
        "bool",    // FIELD_endOfSlice
        "uint8_t",    // FIELD_pictureType
        "bool",    // FIELD_fbv
        "uint8_t",    // FIELD_bfc
        "bool",    // FIELD_ffv
        "uint8_t",    // FIELD_ffc
    };
    return (field >= 0 && field < 15) ? fieldTypeStrings[field] : nullptr;
}

const char **RtpMpegHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *RtpMpegHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RtpMpegHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RtpMpegHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RtpMpegHeader'", field);
    }
}

const char *RtpMpegHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RtpMpegHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLength: return long2string(pp->getHeaderLength());
        case FIELD_payloadLength: return long2string(pp->getPayloadLength());
        case FIELD_mbz: return ulong2string(pp->getMbz());
        case FIELD_two: return bool2string(pp->getTwo());
        case FIELD_temporalReference: return ulong2string(pp->getTemporalReference());
        case FIELD_activeN: return bool2string(pp->getActiveN());
        case FIELD_newPictureHeader: return bool2string(pp->getNewPictureHeader());
        case FIELD_sequenceHeaderPresent: return bool2string(pp->getSequenceHeaderPresent());
        case FIELD_beginningOfSlice: return bool2string(pp->getBeginningOfSlice());
        case FIELD_endOfSlice: return bool2string(pp->getEndOfSlice());
        case FIELD_pictureType: return ulong2string(pp->getPictureType());
        case FIELD_fbv: return bool2string(pp->getFbv());
        case FIELD_bfc: return ulong2string(pp->getBfc());
        case FIELD_ffv: return bool2string(pp->getFfv());
        case FIELD_ffc: return ulong2string(pp->getFfc());
        default: return "";
    }
}

void RtpMpegHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLength: pp->setHeaderLength(string2long(value)); break;
        case FIELD_payloadLength: pp->setPayloadLength(string2long(value)); break;
        case FIELD_mbz: pp->setMbz(string2ulong(value)); break;
        case FIELD_two: pp->setTwo(string2bool(value)); break;
        case FIELD_temporalReference: pp->setTemporalReference(string2ulong(value)); break;
        case FIELD_activeN: pp->setActiveN(string2bool(value)); break;
        case FIELD_newPictureHeader: pp->setNewPictureHeader(string2bool(value)); break;
        case FIELD_sequenceHeaderPresent: pp->setSequenceHeaderPresent(string2bool(value)); break;
        case FIELD_beginningOfSlice: pp->setBeginningOfSlice(string2bool(value)); break;
        case FIELD_endOfSlice: pp->setEndOfSlice(string2bool(value)); break;
        case FIELD_pictureType: pp->setPictureType(string2ulong(value)); break;
        case FIELD_fbv: pp->setFbv(string2bool(value)); break;
        case FIELD_bfc: pp->setBfc(string2ulong(value)); break;
        case FIELD_ffv: pp->setFfv(string2bool(value)); break;
        case FIELD_ffc: pp->setFfc(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpMpegHeader'", field);
    }
}

omnetpp::cValue RtpMpegHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLength: return pp->getHeaderLength();
        case FIELD_payloadLength: return pp->getPayloadLength();
        case FIELD_mbz: return (omnetpp::intval_t)(pp->getMbz());
        case FIELD_two: return pp->getTwo();
        case FIELD_temporalReference: return (omnetpp::intval_t)(pp->getTemporalReference());
        case FIELD_activeN: return pp->getActiveN();
        case FIELD_newPictureHeader: return pp->getNewPictureHeader();
        case FIELD_sequenceHeaderPresent: return pp->getSequenceHeaderPresent();
        case FIELD_beginningOfSlice: return pp->getBeginningOfSlice();
        case FIELD_endOfSlice: return pp->getEndOfSlice();
        case FIELD_pictureType: return (omnetpp::intval_t)(pp->getPictureType());
        case FIELD_fbv: return pp->getFbv();
        case FIELD_bfc: return (omnetpp::intval_t)(pp->getBfc());
        case FIELD_ffv: return pp->getFfv();
        case FIELD_ffc: return (omnetpp::intval_t)(pp->getFfc());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RtpMpegHeader' as cValue -- field index out of range?", field);
    }
}

void RtpMpegHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLength: pp->setHeaderLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_payloadLength: pp->setPayloadLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_mbz: pp->setMbz(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_two: pp->setTwo(value.boolValue()); break;
        case FIELD_temporalReference: pp->setTemporalReference(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_activeN: pp->setActiveN(value.boolValue()); break;
        case FIELD_newPictureHeader: pp->setNewPictureHeader(value.boolValue()); break;
        case FIELD_sequenceHeaderPresent: pp->setSequenceHeaderPresent(value.boolValue()); break;
        case FIELD_beginningOfSlice: pp->setBeginningOfSlice(value.boolValue()); break;
        case FIELD_endOfSlice: pp->setEndOfSlice(value.boolValue()); break;
        case FIELD_pictureType: pp->setPictureType(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_fbv: pp->setFbv(value.boolValue()); break;
        case FIELD_bfc: pp->setBfc(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_ffv: pp->setFfv(value.boolValue()); break;
        case FIELD_ffc: pp->setFfc(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpMpegHeader'", field);
    }
}

const char *RtpMpegHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RtpMpegHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RtpMpegHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RtpMpegHeader *pp = omnetpp::fromAnyPtr<RtpMpegHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RtpMpegHeader'", field);
    }
}

}  // namespace rtp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

