//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/bgpv4/bgpmessage/BgpHeader.msg.
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
#include "BgpHeader_m.h"

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
namespace bgp {

Register_Class(BgpAsPathSegment)

BgpAsPathSegment::BgpAsPathSegment() : ::omnetpp::cObject()
{
}

BgpAsPathSegment::BgpAsPathSegment(const BgpAsPathSegment& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

BgpAsPathSegment::~BgpAsPathSegment()
{
    delete [] this->asValue;
}

BgpAsPathSegment& BgpAsPathSegment::operator=(const BgpAsPathSegment& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void BgpAsPathSegment::copy(const BgpAsPathSegment& other)
{
    this->type = other.type;
    this->length = other.length;
    delete [] this->asValue;
    this->asValue = (other.asValue_arraysize==0) ? nullptr : new uint16_t[other.asValue_arraysize];
    asValue_arraysize = other.asValue_arraysize;
    for (size_t i = 0; i < asValue_arraysize; i++) {
        this->asValue[i] = other.asValue[i];
    }
}

void BgpAsPathSegment::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->length);
    b->pack(asValue_arraysize);
    doParsimArrayPacking(b,this->asValue,asValue_arraysize);
}

void BgpAsPathSegment::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->length);
    delete [] this->asValue;
    b->unpack(asValue_arraysize);
    if (asValue_arraysize == 0) {
        this->asValue = nullptr;
    } else {
        this->asValue = new uint16_t[asValue_arraysize];
        doParsimArrayUnpacking(b,this->asValue,asValue_arraysize);
    }
}

BgpPathSegmentType BgpAsPathSegment::getType() const
{
    return this->type;
}

void BgpAsPathSegment::setType(BgpPathSegmentType type)
{
    this->type = type;
}

uint8_t BgpAsPathSegment::getLength() const
{
    return this->length;
}

void BgpAsPathSegment::setLength(uint8_t length)
{
    this->length = length;
}

size_t BgpAsPathSegment::getAsValueArraySize() const
{
    return asValue_arraysize;
}

uint16_t BgpAsPathSegment::getAsValue(size_t k) const
{
    if (k >= asValue_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)asValue_arraysize, (unsigned long)k);
    return this->asValue[k];
}

void BgpAsPathSegment::setAsValueArraySize(size_t newSize)
{
    uint16_t *asValue2 = (newSize==0) ? nullptr : new uint16_t[newSize];
    size_t minSize = asValue_arraysize < newSize ? asValue_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        asValue2[i] = this->asValue[i];
    for (size_t i = minSize; i < newSize; i++)
        asValue2[i] = 0;
    delete [] this->asValue;
    this->asValue = asValue2;
    asValue_arraysize = newSize;
}

void BgpAsPathSegment::setAsValue(size_t k, uint16_t asValue)
{
    if (k >= asValue_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)asValue_arraysize, (unsigned long)k);
    this->asValue[k] = asValue;
}

void BgpAsPathSegment::insertAsValue(size_t k, uint16_t asValue)
{
    if (k > asValue_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)asValue_arraysize, (unsigned long)k);
    size_t newSize = asValue_arraysize + 1;
    uint16_t *asValue2 = new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        asValue2[i] = this->asValue[i];
    asValue2[k] = asValue;
    for (i = k + 1; i < newSize; i++)
        asValue2[i] = this->asValue[i-1];
    delete [] this->asValue;
    this->asValue = asValue2;
    asValue_arraysize = newSize;
}

void BgpAsPathSegment::appendAsValue(uint16_t asValue)
{
    insertAsValue(asValue_arraysize, asValue);
}

void BgpAsPathSegment::eraseAsValue(size_t k)
{
    if (k >= asValue_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)asValue_arraysize, (unsigned long)k);
    size_t newSize = asValue_arraysize - 1;
    uint16_t *asValue2 = (newSize == 0) ? nullptr : new uint16_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        asValue2[i] = this->asValue[i];
    for (i = k; i < newSize; i++)
        asValue2[i] = this->asValue[i+1];
    delete [] this->asValue;
    this->asValue = asValue2;
    asValue_arraysize = newSize;
}

class BgpAsPathSegmentDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_length,
        FIELD_asValue,
    };
  public:
    BgpAsPathSegmentDescriptor();
    virtual ~BgpAsPathSegmentDescriptor();

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

Register_ClassDescriptor(BgpAsPathSegmentDescriptor)

BgpAsPathSegmentDescriptor::BgpAsPathSegmentDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpAsPathSegment)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

BgpAsPathSegmentDescriptor::~BgpAsPathSegmentDescriptor()
{
    delete[] propertyNames;
}

bool BgpAsPathSegmentDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpAsPathSegment *>(obj)!=nullptr;
}

const char **BgpAsPathSegmentDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpAsPathSegmentDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpAsPathSegmentDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int BgpAsPathSegmentDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_length
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_asValue
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *BgpAsPathSegmentDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "length",
        "asValue",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int BgpAsPathSegmentDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "asValue") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpAsPathSegmentDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bgp::BgpPathSegmentType",    // FIELD_type
        "uint8_t",    // FIELD_length
        "uint16_t",    // FIELD_asValue
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpAsPathSegmentDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpAsPathSegmentDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::bgp::BgpPathSegmentType";
            return nullptr;
        default: return nullptr;
    }
}

int BgpAsPathSegmentDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_asValue: return pp->getAsValueArraySize();
        default: return 0;
    }
}

void BgpAsPathSegmentDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_asValue: pp->setAsValueArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpAsPathSegment'", field);
    }
}

const char *BgpAsPathSegmentDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpAsPathSegmentDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::bgp::BgpPathSegmentType");
        case FIELD_length: return ulong2string(pp->getLength());
        case FIELD_asValue: return ulong2string(pp->getAsValue(i));
        default: return "";
    }
}

void BgpAsPathSegmentDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType((inet::bgp::BgpPathSegmentType)string2enum(value, "inet::bgp::BgpPathSegmentType")); break;
        case FIELD_length: pp->setLength(string2ulong(value)); break;
        case FIELD_asValue: pp->setAsValue(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpAsPathSegment'", field);
    }
}

omnetpp::cValue BgpAsPathSegmentDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_length: return (omnetpp::intval_t)(pp->getLength());
        case FIELD_asValue: return (omnetpp::intval_t)(pp->getAsValue(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpAsPathSegment' as cValue -- field index out of range?", field);
    }
}

void BgpAsPathSegmentDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(static_cast<inet::bgp::BgpPathSegmentType>(value.intValue())); break;
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_asValue: pp->setAsValue(i,omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpAsPathSegment'", field);
    }
}

const char *BgpAsPathSegmentDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpAsPathSegmentDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpAsPathSegmentDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpAsPathSegment *pp = omnetpp::fromAnyPtr<BgpAsPathSegment>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpAsPathSegment'", field);
    }
}

Register_Enum(inet::bgp::BgpType, (inet::bgp::BgpType::BGP_OPEN, inet::bgp::BgpType::BGP_UPDATE, inet::bgp::BgpType::BGP_NOTIFICATION, inet::bgp::BgpType::BGP_KEEPALIVE));

Register_Class(BgpHeader)

BgpHeader::BgpHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(BGP_HEADER_OCTETS);

    std::fill(this->marker, this->marker + 16, 0xFF);
}

BgpHeader::BgpHeader(const BgpHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

BgpHeader::~BgpHeader()
{
}

BgpHeader& BgpHeader::operator=(const BgpHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void BgpHeader::copy(const BgpHeader& other)
{
    for (size_t i = 0; i < 16; i++) {
        this->marker[i] = other.marker[i];
    }
    this->totalLength = other.totalLength;
    this->type = other.type;
}

void BgpHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimArrayPacking(b,this->marker,16);
    doParsimPacking(b,this->totalLength);
    doParsimPacking(b,this->type);
}

void BgpHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimArrayUnpacking(b,this->marker,16);
    doParsimUnpacking(b,this->totalLength);
    doParsimUnpacking(b,this->type);
}

size_t BgpHeader::getMarkerArraySize() const
{
    return 16;
}

uint8_t BgpHeader::getMarker(size_t k) const
{
    if (k >= 16) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)16, (unsigned long)k);
    return this->marker[k];
}

void BgpHeader::setMarker(size_t k, uint8_t marker)
{
    if (k >= 16) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)16, (unsigned long)k);
    handleChange();
    this->marker[k] = marker;
}

uint16_t BgpHeader::getTotalLength() const
{
    return this->totalLength;
}

void BgpHeader::setTotalLength(uint16_t totalLength)
{
    handleChange();
    this->totalLength = totalLength;
}

BgpType BgpHeader::getType() const
{
    return this->type;
}

void BgpHeader::setType(BgpType type)
{
    handleChange();
    this->type = type;
}

class BgpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_marker,
        FIELD_totalLength,
        FIELD_type,
    };
  public:
    BgpHeaderDescriptor();
    virtual ~BgpHeaderDescriptor();

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

Register_ClassDescriptor(BgpHeaderDescriptor)

BgpHeaderDescriptor::BgpHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

BgpHeaderDescriptor::~BgpHeaderDescriptor()
{
    delete[] propertyNames;
}

bool BgpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpHeader *>(obj)!=nullptr;
}

const char **BgpHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int BgpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,    // FIELD_marker
        FD_ISEDITABLE,    // FIELD_totalLength
        0,    // FIELD_type
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *BgpHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "marker",
        "totalLength",
        "type",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int BgpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "marker") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "totalLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_marker
        "uint16_t",    // FIELD_totalLength
        "inet::bgp::BgpType",    // FIELD_type
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::bgp::BgpType";
            return nullptr;
        default: return nullptr;
    }
}

int BgpHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_marker: return 16;
        default: return 0;
    }
}

void BgpHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpHeader'", field);
    }
}

const char *BgpHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_marker: return ulong2string(pp->getMarker(i));
        case FIELD_totalLength: return ulong2string(pp->getTotalLength());
        case FIELD_type: return enum2string(pp->getType(), "inet::bgp::BgpType");
        default: return "";
    }
}

void BgpHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_marker: pp->setMarker(i,string2ulong(value)); break;
        case FIELD_totalLength: pp->setTotalLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpHeader'", field);
    }
}

omnetpp::cValue BgpHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_marker: return (omnetpp::intval_t)(pp->getMarker(i));
        case FIELD_totalLength: return (omnetpp::intval_t)(pp->getTotalLength());
        case FIELD_type: return static_cast<int>(pp->getType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpHeader' as cValue -- field index out of range?", field);
    }
}

void BgpHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_marker: pp->setMarker(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_totalLength: pp->setTotalLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpHeader'", field);
    }
}

const char *BgpHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpHeader *pp = omnetpp::fromAnyPtr<BgpHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpHeader'", field);
    }
}

Register_Class(BgpKeepAliveMessage)

BgpKeepAliveMessage::BgpKeepAliveMessage() : ::inet::bgp::BgpHeader()
{
    this->setType(BGP_KEEPALIVE);
}

BgpKeepAliveMessage::BgpKeepAliveMessage(const BgpKeepAliveMessage& other) : ::inet::bgp::BgpHeader(other)
{
    copy(other);
}

BgpKeepAliveMessage::~BgpKeepAliveMessage()
{
}

BgpKeepAliveMessage& BgpKeepAliveMessage::operator=(const BgpKeepAliveMessage& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpHeader::operator=(other);
    copy(other);
    return *this;
}

void BgpKeepAliveMessage::copy(const BgpKeepAliveMessage& other)
{
}

void BgpKeepAliveMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpHeader::parsimPack(b);
}

void BgpKeepAliveMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpHeader::parsimUnpack(b);
}

class BgpKeepAliveMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    BgpKeepAliveMessageDescriptor();
    virtual ~BgpKeepAliveMessageDescriptor();

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

Register_ClassDescriptor(BgpKeepAliveMessageDescriptor)

BgpKeepAliveMessageDescriptor::BgpKeepAliveMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpKeepAliveMessage)), "inet::bgp::BgpHeader")
{
    propertyNames = nullptr;
}

BgpKeepAliveMessageDescriptor::~BgpKeepAliveMessageDescriptor()
{
    delete[] propertyNames;
}

bool BgpKeepAliveMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpKeepAliveMessage *>(obj)!=nullptr;
}

const char **BgpKeepAliveMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpKeepAliveMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpKeepAliveMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int BgpKeepAliveMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *BgpKeepAliveMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int BgpKeepAliveMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *BgpKeepAliveMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **BgpKeepAliveMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpKeepAliveMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpKeepAliveMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpKeepAliveMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpKeepAliveMessage'", field);
    }
}

const char *BgpKeepAliveMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpKeepAliveMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void BgpKeepAliveMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpKeepAliveMessage'", field);
    }
}

omnetpp::cValue BgpKeepAliveMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpKeepAliveMessage' as cValue -- field index out of range?", field);
    }
}

void BgpKeepAliveMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpKeepAliveMessage'", field);
    }
}

const char *BgpKeepAliveMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr BgpKeepAliveMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpKeepAliveMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpKeepAliveMessage *pp = omnetpp::fromAnyPtr<BgpKeepAliveMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpKeepAliveMessage'", field);
    }
}

BgpOptionalParameterBase::BgpOptionalParameterBase()
{
}

BgpOptionalParameterBase::BgpOptionalParameterBase(const BgpOptionalParameterBase& other)
{
    copy(other);
}

BgpOptionalParameterBase::~BgpOptionalParameterBase()
{
}

BgpOptionalParameterBase& BgpOptionalParameterBase::operator=(const BgpOptionalParameterBase& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void BgpOptionalParameterBase::copy(const BgpOptionalParameterBase& other)
{
    this->parameterType = other.parameterType;
    this->parameterValueLength = other.parameterValueLength;
}

void BgpOptionalParameterBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->parameterType);
    doParsimPacking(b,this->parameterValueLength);
}

void BgpOptionalParameterBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->parameterType);
    doParsimUnpacking(b,this->parameterValueLength);
}

short BgpOptionalParameterBase::getParameterType() const
{
    return this->parameterType;
}

void BgpOptionalParameterBase::setParameterType(short parameterType)
{
    this->parameterType = parameterType;
}

unsigned short BgpOptionalParameterBase::getParameterValueLength() const
{
    return this->parameterValueLength;
}

void BgpOptionalParameterBase::setParameterValueLength(unsigned short parameterValueLength)
{
    this->parameterValueLength = parameterValueLength;
}

class BgpOptionalParameterBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_parameterType,
        FIELD_parameterValueLength,
    };
  public:
    BgpOptionalParameterBaseDescriptor();
    virtual ~BgpOptionalParameterBaseDescriptor();

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

Register_ClassDescriptor(BgpOptionalParameterBaseDescriptor)

BgpOptionalParameterBaseDescriptor::BgpOptionalParameterBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpOptionalParameterBase)), "")
{
    propertyNames = nullptr;
}

BgpOptionalParameterBaseDescriptor::~BgpOptionalParameterBaseDescriptor()
{
    delete[] propertyNames;
}

bool BgpOptionalParameterBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpOptionalParameterBase *>(obj)!=nullptr;
}

const char **BgpOptionalParameterBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpOptionalParameterBaseDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpOptionalParameterBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int BgpOptionalParameterBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_parameterType
        FD_ISEDITABLE,    // FIELD_parameterValueLength
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *BgpOptionalParameterBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "parameterType",
        "parameterValueLength",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int BgpOptionalParameterBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "parameterType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "parameterValueLength") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpOptionalParameterBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_parameterType
        "unsigned short",    // FIELD_parameterValueLength
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpOptionalParameterBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpOptionalParameterBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpOptionalParameterBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpOptionalParameterBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpOptionalParameterBase'", field);
    }
}

const char *BgpOptionalParameterBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpOptionalParameterBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: return long2string(pp->getParameterType());
        case FIELD_parameterValueLength: return ulong2string(pp->getParameterValueLength());
        default: return "";
    }
}

void BgpOptionalParameterBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: pp->setParameterType(string2long(value)); break;
        case FIELD_parameterValueLength: pp->setParameterValueLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterBase'", field);
    }
}

omnetpp::cValue BgpOptionalParameterBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: return pp->getParameterType();
        case FIELD_parameterValueLength: return (omnetpp::intval_t)(pp->getParameterValueLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpOptionalParameterBase' as cValue -- field index out of range?", field);
    }
}

void BgpOptionalParameterBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        case FIELD_parameterType: pp->setParameterType(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_parameterValueLength: pp->setParameterValueLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterBase'", field);
    }
}

const char *BgpOptionalParameterBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpOptionalParameterBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpOptionalParameterBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterBase *pp = omnetpp::fromAnyPtr<BgpOptionalParameterBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterBase'", field);
    }
}

BgpOptionalParameterRaw::BgpOptionalParameterRaw() : ::inet::bgp::BgpOptionalParameterBase()
{
}

BgpOptionalParameterRaw::BgpOptionalParameterRaw(const BgpOptionalParameterRaw& other) : ::inet::bgp::BgpOptionalParameterBase(other)
{
    copy(other);
}

BgpOptionalParameterRaw::~BgpOptionalParameterRaw()
{
    delete [] this->value;
}

BgpOptionalParameterRaw& BgpOptionalParameterRaw::operator=(const BgpOptionalParameterRaw& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpOptionalParameterBase::operator=(other);
    copy(other);
    return *this;
}

void BgpOptionalParameterRaw::copy(const BgpOptionalParameterRaw& other)
{
    delete [] this->value;
    this->value = (other.value_arraysize==0) ? nullptr : new char[other.value_arraysize];
    value_arraysize = other.value_arraysize;
    for (size_t i = 0; i < value_arraysize; i++) {
        this->value[i] = other.value[i];
    }
}

void BgpOptionalParameterRaw::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,(::inet::bgp::BgpOptionalParameterBase&)*this);
    b->pack(value_arraysize);
    doParsimArrayPacking(b,this->value,value_arraysize);
}

void BgpOptionalParameterRaw::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,(::inet::bgp::BgpOptionalParameterBase&)*this);
    delete [] this->value;
    b->unpack(value_arraysize);
    if (value_arraysize == 0) {
        this->value = nullptr;
    } else {
        this->value = new char[value_arraysize];
        doParsimArrayUnpacking(b,this->value,value_arraysize);
    }
}

size_t BgpOptionalParameterRaw::getValueArraySize() const
{
    return value_arraysize;
}

char BgpOptionalParameterRaw::getValue(size_t k) const
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    return this->value[k];
}

void BgpOptionalParameterRaw::setValueArraySize(size_t newSize)
{
    char *value2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = value_arraysize < newSize ? value_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        value2[i] = this->value[i];
    for (size_t i = minSize; i < newSize; i++)
        value2[i] = 0;
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

void BgpOptionalParameterRaw::setValue(size_t k, char value)
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    this->value[k] = value;
}

void BgpOptionalParameterRaw::insertValue(size_t k, char value)
{
    if (k > value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    size_t newSize = value_arraysize + 1;
    char *value2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        value2[i] = this->value[i];
    value2[k] = value;
    for (i = k + 1; i < newSize; i++)
        value2[i] = this->value[i-1];
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

void BgpOptionalParameterRaw::appendValue(char value)
{
    insertValue(value_arraysize, value);
}

void BgpOptionalParameterRaw::eraseValue(size_t k)
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    size_t newSize = value_arraysize - 1;
    char *value2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        value2[i] = this->value[i];
    for (i = k; i < newSize; i++)
        value2[i] = this->value[i+1];
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

class BgpOptionalParameterRawDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpOptionalParameterRawDescriptor();
    virtual ~BgpOptionalParameterRawDescriptor();

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

Register_ClassDescriptor(BgpOptionalParameterRawDescriptor)

BgpOptionalParameterRawDescriptor::BgpOptionalParameterRawDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpOptionalParameterRaw)), "inet::bgp::BgpOptionalParameterBase")
{
    propertyNames = nullptr;
}

BgpOptionalParameterRawDescriptor::~BgpOptionalParameterRawDescriptor()
{
    delete[] propertyNames;
}

bool BgpOptionalParameterRawDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpOptionalParameterRaw *>(obj)!=nullptr;
}

const char **BgpOptionalParameterRawDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpOptionalParameterRawDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpOptionalParameterRawDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpOptionalParameterRawDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *BgpOptionalParameterRawDescriptor::getFieldName(int field) const
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

int BgpOptionalParameterRawDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpOptionalParameterRawDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "char",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpOptionalParameterRawDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpOptionalParameterRawDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpOptionalParameterRawDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: return pp->getValueArraySize();
        default: return 0;
    }
}

void BgpOptionalParameterRawDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValueArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpOptionalParameterRaw'", field);
    }
}

const char *BgpOptionalParameterRawDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpOptionalParameterRawDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: return long2string(pp->getValue(i));
        default: return "";
    }
}

void BgpOptionalParameterRawDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterRaw'", field);
    }
}

omnetpp::cValue BgpOptionalParameterRawDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: return pp->getValue(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpOptionalParameterRaw' as cValue -- field index out of range?", field);
    }
}

void BgpOptionalParameterRawDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterRaw'", field);
    }
}

const char *BgpOptionalParameterRawDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpOptionalParameterRawDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpOptionalParameterRawDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOptionalParameterRaw *pp = omnetpp::fromAnyPtr<BgpOptionalParameterRaw>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOptionalParameterRaw'", field);
    }
}

Register_Class(BgpOpenMessage)

BgpOpenMessage::BgpOpenMessage() : ::inet::bgp::BgpHeader()
{
    this->setType(BGP_OPEN);
    this->setChunkLength(BGP_HEADER_OCTETS + BGP_OPEN_OCTETS);
    this->setTotalLength(B(BGP_HEADER_OCTETS + BGP_OPEN_OCTETS).get());

}

BgpOpenMessage::BgpOpenMessage(const BgpOpenMessage& other) : ::inet::bgp::BgpHeader(other)
{
    copy(other);
}

BgpOpenMessage::~BgpOpenMessage()
{
    for (size_t i = 0; i < optionalParameter_arraysize; i++)
        delete this->optionalParameter[i];
    delete [] this->optionalParameter;
}

BgpOpenMessage& BgpOpenMessage::operator=(const BgpOpenMessage& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpHeader::operator=(other);
    copy(other);
    return *this;
}

void BgpOpenMessage::copy(const BgpOpenMessage& other)
{
    this->version = other.version;
    this->myAS = other.myAS;
    this->holdTime = other.holdTime;
    this->BGPIdentifier = other.BGPIdentifier;
    this->optionalParametersLength = other.optionalParametersLength;
    for (size_t i = 0; i < optionalParameter_arraysize; i++)
        delete this->optionalParameter[i];
    delete [] this->optionalParameter;
    this->optionalParameter = (other.optionalParameter_arraysize==0) ? nullptr : new BgpOptionalParameterBase *[other.optionalParameter_arraysize];
    optionalParameter_arraysize = other.optionalParameter_arraysize;
    for (size_t i = 0; i < optionalParameter_arraysize; i++) {
        this->optionalParameter[i] = other.optionalParameter[i];
        if (this->optionalParameter[i] != nullptr) {
            this->optionalParameter[i] = new BgpOptionalParameterBase(*this->optionalParameter[i]);
        }
    }
}

void BgpOpenMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpHeader::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->myAS);
    doParsimPacking(b,this->holdTime);
    doParsimPacking(b,this->BGPIdentifier);
    doParsimPacking(b,this->optionalParametersLength);
    b->pack(optionalParameter_arraysize);
    doParsimArrayPacking(b,this->optionalParameter,optionalParameter_arraysize);
}

void BgpOpenMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->myAS);
    doParsimUnpacking(b,this->holdTime);
    doParsimUnpacking(b,this->BGPIdentifier);
    doParsimUnpacking(b,this->optionalParametersLength);
    delete [] this->optionalParameter;
    b->unpack(optionalParameter_arraysize);
    if (optionalParameter_arraysize == 0) {
        this->optionalParameter = nullptr;
    } else {
        this->optionalParameter = new BgpOptionalParameterBase *[optionalParameter_arraysize];
        doParsimArrayUnpacking(b,this->optionalParameter,optionalParameter_arraysize);
    }
}

uint8_t BgpOpenMessage::getVersion() const
{
    return this->version;
}

void BgpOpenMessage::setVersion(uint8_t version)
{
    handleChange();
    this->version = version;
}

uint16_t BgpOpenMessage::getMyAS() const
{
    return this->myAS;
}

void BgpOpenMessage::setMyAS(uint16_t myAS)
{
    handleChange();
    this->myAS = myAS;
}

::omnetpp::simtime_t BgpOpenMessage::getHoldTime() const
{
    return this->holdTime;
}

void BgpOpenMessage::setHoldTime(::omnetpp::simtime_t holdTime)
{
    handleChange();
    this->holdTime = holdTime;
}

const ::inet::Ipv4Address& BgpOpenMessage::getBGPIdentifier() const
{
    return this->BGPIdentifier;
}

void BgpOpenMessage::setBGPIdentifier(const ::inet::Ipv4Address& BGPIdentifier)
{
    handleChange();
    this->BGPIdentifier = BGPIdentifier;
}

unsigned short BgpOpenMessage::getOptionalParametersLength() const
{
    return this->optionalParametersLength;
}

void BgpOpenMessage::setOptionalParametersLength(unsigned short optionalParametersLength)
{
    handleChange();
    this->optionalParametersLength = optionalParametersLength;
}

size_t BgpOpenMessage::getOptionalParameterArraySize() const
{
    return optionalParameter_arraysize;
}

const BgpOptionalParameterBase * BgpOpenMessage::getOptionalParameter(size_t k) const
{
    if (k >= optionalParameter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)optionalParameter_arraysize, (unsigned long)k);
    return this->optionalParameter[k];
}

void BgpOpenMessage::setOptionalParameterArraySize(size_t newSize)
{
    handleChange();
    BgpOptionalParameterBase * *optionalParameter2 = (newSize==0) ? nullptr : new BgpOptionalParameterBase *[newSize];
    size_t minSize = optionalParameter_arraysize < newSize ? optionalParameter_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        optionalParameter2[i] = this->optionalParameter[i];
    for (size_t i = minSize; i < newSize; i++)
        optionalParameter2[i] = nullptr;
    for (size_t i = newSize; i < optionalParameter_arraysize; i++)
        delete optionalParameter[i];
    delete [] this->optionalParameter;
    this->optionalParameter = optionalParameter2;
    optionalParameter_arraysize = newSize;
}

void BgpOpenMessage::setOptionalParameter(size_t k, BgpOptionalParameterBase * optionalParameter)
{
    if (k >= optionalParameter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)optionalParameter_arraysize, (unsigned long)k);
    handleChange();
    if (this->optionalParameter[k] != nullptr) throw omnetpp::cRuntimeError("setOptionalParameter(): a value is already set, remove it first with removeOptionalParameter()");
    this->optionalParameter[k] = optionalParameter;
}

BgpOptionalParameterBase * BgpOpenMessage::removeOptionalParameter(size_t k)
{
    if (k >= optionalParameter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)optionalParameter_arraysize, (unsigned long)k);
    handleChange();
    BgpOptionalParameterBase * retval = this->optionalParameter[k];
    this->optionalParameter[k] = nullptr;
    return retval;
}

void BgpOpenMessage::insertOptionalParameter(size_t k, BgpOptionalParameterBase * optionalParameter)
{
    if (k > optionalParameter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)optionalParameter_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = optionalParameter_arraysize + 1;
    BgpOptionalParameterBase * *optionalParameter2 = new BgpOptionalParameterBase *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        optionalParameter2[i] = this->optionalParameter[i];
    optionalParameter2[k] = optionalParameter;
    for (i = k + 1; i < newSize; i++)
        optionalParameter2[i] = this->optionalParameter[i-1];
    delete [] this->optionalParameter;
    this->optionalParameter = optionalParameter2;
    optionalParameter_arraysize = newSize;
}

void BgpOpenMessage::appendOptionalParameter(BgpOptionalParameterBase * optionalParameter)
{
    insertOptionalParameter(optionalParameter_arraysize, optionalParameter);
}

void BgpOpenMessage::eraseOptionalParameter(size_t k)
{
    if (k >= optionalParameter_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)optionalParameter_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = optionalParameter_arraysize - 1;
    BgpOptionalParameterBase * *optionalParameter2 = (newSize == 0) ? nullptr : new BgpOptionalParameterBase *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        optionalParameter2[i] = this->optionalParameter[i];
    for (i = k; i < newSize; i++)
        optionalParameter2[i] = this->optionalParameter[i+1];
    delete this->optionalParameter[k];
    delete [] this->optionalParameter;
    this->optionalParameter = optionalParameter2;
    optionalParameter_arraysize = newSize;
}

class BgpOpenMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_myAS,
        FIELD_holdTime,
        FIELD_BGPIdentifier,
        FIELD_optionalParametersLength,
        FIELD_optionalParameter,
    };
  public:
    BgpOpenMessageDescriptor();
    virtual ~BgpOpenMessageDescriptor();

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

Register_ClassDescriptor(BgpOpenMessageDescriptor)

BgpOpenMessageDescriptor::BgpOpenMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpOpenMessage)), "inet::bgp::BgpHeader")
{
    propertyNames = nullptr;
}

BgpOpenMessageDescriptor::~BgpOpenMessageDescriptor()
{
    delete[] propertyNames;
}

bool BgpOpenMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpOpenMessage *>(obj)!=nullptr;
}

const char **BgpOpenMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpOpenMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpOpenMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int BgpOpenMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        FD_ISEDITABLE,    // FIELD_myAS
        FD_ISEDITABLE,    // FIELD_holdTime
        0,    // FIELD_BGPIdentifier
        FD_ISEDITABLE,    // FIELD_optionalParametersLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_optionalParameter
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *BgpOpenMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "myAS",
        "holdTime",
        "BGPIdentifier",
        "optionalParametersLength",
        "optionalParameter",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int BgpOpenMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "myAS") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "holdTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "BGPIdentifier") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "optionalParametersLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "optionalParameter") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpOpenMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_version
        "uint16_t",    // FIELD_myAS
        "omnetpp::simtime_t",    // FIELD_holdTime
        "inet::Ipv4Address",    // FIELD_BGPIdentifier
        "unsigned short",    // FIELD_optionalParametersLength
        "inet::bgp::BgpOptionalParameterBase",    // FIELD_optionalParameter
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpOpenMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_optionalParameter: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BgpOpenMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_optionalParameter:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int BgpOpenMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_optionalParameter: return pp->getOptionalParameterArraySize();
        default: return 0;
    }
}

void BgpOpenMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_optionalParameter: pp->setOptionalParameterArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpOpenMessage'", field);
    }
}

const char *BgpOpenMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_optionalParameter: { const BgpOptionalParameterBase * value = pp->getOptionalParameter(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string BgpOpenMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_version: return ulong2string(pp->getVersion());
        case FIELD_myAS: return ulong2string(pp->getMyAS());
        case FIELD_holdTime: return simtime2string(pp->getHoldTime());
        case FIELD_BGPIdentifier: return pp->getBGPIdentifier().str();
        case FIELD_optionalParametersLength: return ulong2string(pp->getOptionalParametersLength());
        case FIELD_optionalParameter: return "";
        default: return "";
    }
}

void BgpOpenMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2ulong(value)); break;
        case FIELD_myAS: pp->setMyAS(string2ulong(value)); break;
        case FIELD_holdTime: pp->setHoldTime(string2simtime(value)); break;
        case FIELD_optionalParametersLength: pp->setOptionalParametersLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOpenMessage'", field);
    }
}

omnetpp::cValue BgpOpenMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_version: return (omnetpp::intval_t)(pp->getVersion());
        case FIELD_myAS: return (omnetpp::intval_t)(pp->getMyAS());
        case FIELD_holdTime: return pp->getHoldTime().dbl();
        case FIELD_BGPIdentifier: return omnetpp::toAnyPtr(&pp->getBGPIdentifier()); break;
        case FIELD_optionalParametersLength: return (omnetpp::intval_t)(pp->getOptionalParametersLength());
        case FIELD_optionalParameter: return omnetpp::toAnyPtr(pp->getOptionalParameter(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpOpenMessage' as cValue -- field index out of range?", field);
    }
}

void BgpOpenMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_myAS: pp->setMyAS(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_holdTime: pp->setHoldTime(value.doubleValue()); break;
        case FIELD_optionalParametersLength: pp->setOptionalParametersLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_optionalParameter: pp->setOptionalParameter(i,omnetpp::fromAnyPtr<BgpOptionalParameterBase>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOpenMessage'", field);
    }
}

const char *BgpOpenMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_optionalParameter: return omnetpp::opp_typename(typeid(BgpOptionalParameterBase));
        default: return nullptr;
    };
}

omnetpp::any_ptr BgpOpenMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_BGPIdentifier: return omnetpp::toAnyPtr(&pp->getBGPIdentifier()); break;
        case FIELD_optionalParameter: return omnetpp::toAnyPtr(pp->getOptionalParameter(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpOpenMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpOpenMessage *pp = omnetpp::fromAnyPtr<BgpOpenMessage>(object); (void)pp;
    switch (field) {
        case FIELD_optionalParameter: pp->setOptionalParameter(i,omnetpp::fromAnyPtr<BgpOptionalParameterBase>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpOpenMessage'", field);
    }
}

Register_Enum(inet::bgp::BgpUpdateAttributeTypeCode, (inet::bgp::BgpUpdateAttributeTypeCode::ORIGIN, inet::bgp::BgpUpdateAttributeTypeCode::AS_PATH, inet::bgp::BgpUpdateAttributeTypeCode::NEXT_HOP, inet::bgp::BgpUpdateAttributeTypeCode::MULTI_EXIT_DISC, inet::bgp::BgpUpdateAttributeTypeCode::LOCAL_PREF, inet::bgp::BgpUpdateAttributeTypeCode::ATOMIC_AGGREGATE, inet::bgp::BgpUpdateAttributeTypeCode::AGGREGATOR));

Register_Class(BgpUpdatePathAttributes)

BgpUpdatePathAttributes::BgpUpdatePathAttributes() : ::omnetpp::cObject()
{
}

BgpUpdatePathAttributes::BgpUpdatePathAttributes(const BgpUpdatePathAttributes& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

BgpUpdatePathAttributes::~BgpUpdatePathAttributes()
{
}

BgpUpdatePathAttributes& BgpUpdatePathAttributes::operator=(const BgpUpdatePathAttributes& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributes::copy(const BgpUpdatePathAttributes& other)
{
    this->optionalBit = other.optionalBit;
    this->transitiveBit = other.transitiveBit;
    this->partialBit = other.partialBit;
    this->extendedLengthBit = other.extendedLengthBit;
    this->reserved = other.reserved;
    this->typeCode = other.typeCode;
    this->length = other.length;
}

void BgpUpdatePathAttributes::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->optionalBit);
    doParsimPacking(b,this->transitiveBit);
    doParsimPacking(b,this->partialBit);
    doParsimPacking(b,this->extendedLengthBit);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->typeCode);
    doParsimPacking(b,this->length);
}

void BgpUpdatePathAttributes::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->optionalBit);
    doParsimUnpacking(b,this->transitiveBit);
    doParsimUnpacking(b,this->partialBit);
    doParsimUnpacking(b,this->extendedLengthBit);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->typeCode);
    doParsimUnpacking(b,this->length);
}

bool BgpUpdatePathAttributes::getOptionalBit() const
{
    return this->optionalBit;
}

void BgpUpdatePathAttributes::setOptionalBit(bool optionalBit)
{
    this->optionalBit = optionalBit;
}

bool BgpUpdatePathAttributes::getTransitiveBit() const
{
    return this->transitiveBit;
}

void BgpUpdatePathAttributes::setTransitiveBit(bool transitiveBit)
{
    this->transitiveBit = transitiveBit;
}

bool BgpUpdatePathAttributes::getPartialBit() const
{
    return this->partialBit;
}

void BgpUpdatePathAttributes::setPartialBit(bool partialBit)
{
    this->partialBit = partialBit;
}

bool BgpUpdatePathAttributes::getExtendedLengthBit() const
{
    return this->extendedLengthBit;
}

void BgpUpdatePathAttributes::setExtendedLengthBit(bool extendedLengthBit)
{
    this->extendedLengthBit = extendedLengthBit;
}

unsigned short BgpUpdatePathAttributes::getReserved() const
{
    return this->reserved;
}

void BgpUpdatePathAttributes::setReserved(unsigned short reserved)
{
    this->reserved = reserved;
}

BgpUpdateAttributeTypeCode BgpUpdatePathAttributes::getTypeCode() const
{
    return this->typeCode;
}

void BgpUpdatePathAttributes::setTypeCode(BgpUpdateAttributeTypeCode typeCode)
{
    this->typeCode = typeCode;
}

unsigned short BgpUpdatePathAttributes::getLength() const
{
    return this->length;
}

void BgpUpdatePathAttributes::setLength(unsigned short length)
{
    this->length = length;
}

class BgpUpdatePathAttributesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_optionalBit,
        FIELD_transitiveBit,
        FIELD_partialBit,
        FIELD_extendedLengthBit,
        FIELD_reserved,
        FIELD_typeCode,
        FIELD_length,
    };
  public:
    BgpUpdatePathAttributesDescriptor();
    virtual ~BgpUpdatePathAttributesDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesDescriptor)

BgpUpdatePathAttributesDescriptor::BgpUpdatePathAttributesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributes)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesDescriptor::~BgpUpdatePathAttributesDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributes *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int BgpUpdatePathAttributesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_optionalBit
        FD_ISEDITABLE,    // FIELD_transitiveBit
        FD_ISEDITABLE,    // FIELD_partialBit
        FD_ISEDITABLE,    // FIELD_extendedLengthBit
        FD_ISEDITABLE,    // FIELD_reserved
        0,    // FIELD_typeCode
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdatePathAttributesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "optionalBit",
        "transitiveBit",
        "partialBit",
        "extendedLengthBit",
        "reserved",
        "typeCode",
        "length",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int BgpUpdatePathAttributesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "optionalBit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "transitiveBit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "partialBit") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "extendedLengthBit") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "typeCode") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_optionalBit
        "bool",    // FIELD_transitiveBit
        "bool",    // FIELD_partialBit
        "bool",    // FIELD_extendedLengthBit
        "unsigned short",    // FIELD_reserved
        "inet::bgp::BgpUpdateAttributeTypeCode",    // FIELD_typeCode
        "unsigned short",    // FIELD_length
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_typeCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BgpUpdatePathAttributesDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_typeCode:
            if (!strcmp(propertyName, "enum")) return "inet::bgp::BgpUpdateAttributeTypeCode";
            return nullptr;
        default: return nullptr;
    }
}

int BgpUpdatePathAttributesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributes'", field);
    }
}

const char *BgpUpdatePathAttributesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        case FIELD_optionalBit: return bool2string(pp->getOptionalBit());
        case FIELD_transitiveBit: return bool2string(pp->getTransitiveBit());
        case FIELD_partialBit: return bool2string(pp->getPartialBit());
        case FIELD_extendedLengthBit: return bool2string(pp->getExtendedLengthBit());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_typeCode: return enum2string(pp->getTypeCode(), "inet::bgp::BgpUpdateAttributeTypeCode");
        case FIELD_length: return ulong2string(pp->getLength());
        default: return "";
    }
}

void BgpUpdatePathAttributesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        case FIELD_optionalBit: pp->setOptionalBit(string2bool(value)); break;
        case FIELD_transitiveBit: pp->setTransitiveBit(string2bool(value)); break;
        case FIELD_partialBit: pp->setPartialBit(string2bool(value)); break;
        case FIELD_extendedLengthBit: pp->setExtendedLengthBit(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_length: pp->setLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributes'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        case FIELD_optionalBit: return pp->getOptionalBit();
        case FIELD_transitiveBit: return pp->getTransitiveBit();
        case FIELD_partialBit: return pp->getPartialBit();
        case FIELD_extendedLengthBit: return pp->getExtendedLengthBit();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_typeCode: return static_cast<int>(pp->getTypeCode());
        case FIELD_length: return (omnetpp::intval_t)(pp->getLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributes' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        case FIELD_optionalBit: pp->setOptionalBit(value.boolValue()); break;
        case FIELD_transitiveBit: pp->setTransitiveBit(value.boolValue()); break;
        case FIELD_partialBit: pp->setPartialBit(value.boolValue()); break;
        case FIELD_extendedLengthBit: pp->setExtendedLengthBit(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributes'", field);
    }
}

const char *BgpUpdatePathAttributesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributes *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributes'", field);
    }
}

Register_Class(BgpUpdatePathAttributesOrigin)

BgpUpdatePathAttributesOrigin::BgpUpdatePathAttributesOrigin() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(ORIGIN);
    this->setOptionalBit(false);
    this->setTransitiveBit(true);
    this->setLength(1);

}

BgpUpdatePathAttributesOrigin::BgpUpdatePathAttributesOrigin(const BgpUpdatePathAttributesOrigin& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesOrigin::~BgpUpdatePathAttributesOrigin()
{
}

BgpUpdatePathAttributesOrigin& BgpUpdatePathAttributesOrigin::operator=(const BgpUpdatePathAttributesOrigin& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesOrigin::copy(const BgpUpdatePathAttributesOrigin& other)
{
    this->value = other.value;
}

void BgpUpdatePathAttributesOrigin::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    doParsimPacking(b,this->value);
}

void BgpUpdatePathAttributesOrigin::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
}

BgpSessionType BgpUpdatePathAttributesOrigin::getValue() const
{
    return this->value;
}

void BgpUpdatePathAttributesOrigin::setValue(BgpSessionType value)
{
    this->value = value;
}

class BgpUpdatePathAttributesOriginDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpUpdatePathAttributesOriginDescriptor();
    virtual ~BgpUpdatePathAttributesOriginDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesOriginDescriptor)

BgpUpdatePathAttributesOriginDescriptor::BgpUpdatePathAttributesOriginDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesOrigin)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesOriginDescriptor::~BgpUpdatePathAttributesOriginDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesOriginDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesOrigin *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesOriginDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesOriginDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesOriginDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpUpdatePathAttributesOriginDescriptor::getFieldTypeFlags(int field) const
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

const char *BgpUpdatePathAttributesOriginDescriptor::getFieldName(int field) const
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

int BgpUpdatePathAttributesOriginDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesOriginDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bgp::BgpSessionType",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesOriginDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_value: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BgpUpdatePathAttributesOriginDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_value:
            if (!strcmp(propertyName, "enum")) return "inet::bgp::BgpSessionType";
            return nullptr;
        default: return nullptr;
    }
}

int BgpUpdatePathAttributesOriginDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesOriginDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesOrigin'", field);
    }
}

const char *BgpUpdatePathAttributesOriginDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesOriginDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        case FIELD_value: return enum2string(pp->getValue(), "inet::bgp::BgpSessionType");
        default: return "";
    }
}

void BgpUpdatePathAttributesOriginDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue((inet::bgp::BgpSessionType)string2enum(value, "inet::bgp::BgpSessionType")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesOrigin'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesOriginDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        case FIELD_value: return static_cast<int>(pp->getValue());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesOrigin' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesOriginDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(static_cast<inet::bgp::BgpSessionType>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesOrigin'", field);
    }
}

const char *BgpUpdatePathAttributesOriginDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesOriginDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesOriginDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesOrigin *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesOrigin>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesOrigin'", field);
    }
}

Register_Class(BgpUpdatePathAttributesAsPath)

BgpUpdatePathAttributesAsPath::BgpUpdatePathAttributesAsPath() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(AS_PATH);
    this->setOptionalBit(false);
    this->setTransitiveBit(true);
    this->setLength(0);

}

BgpUpdatePathAttributesAsPath::BgpUpdatePathAttributesAsPath(const BgpUpdatePathAttributesAsPath& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesAsPath::~BgpUpdatePathAttributesAsPath()
{
    delete [] this->value;
}

BgpUpdatePathAttributesAsPath& BgpUpdatePathAttributesAsPath::operator=(const BgpUpdatePathAttributesAsPath& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesAsPath::copy(const BgpUpdatePathAttributesAsPath& other)
{
    delete [] this->value;
    this->value = (other.value_arraysize==0) ? nullptr : new BgpAsPathSegment[other.value_arraysize];
    value_arraysize = other.value_arraysize;
    for (size_t i = 0; i < value_arraysize; i++) {
        this->value[i] = other.value[i];
    }
}

void BgpUpdatePathAttributesAsPath::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    b->pack(value_arraysize);
    doParsimArrayPacking(b,this->value,value_arraysize);
}

void BgpUpdatePathAttributesAsPath::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    delete [] this->value;
    b->unpack(value_arraysize);
    if (value_arraysize == 0) {
        this->value = nullptr;
    } else {
        this->value = new BgpAsPathSegment[value_arraysize];
        doParsimArrayUnpacking(b,this->value,value_arraysize);
    }
}

size_t BgpUpdatePathAttributesAsPath::getValueArraySize() const
{
    return value_arraysize;
}

const BgpAsPathSegment& BgpUpdatePathAttributesAsPath::getValue(size_t k) const
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    return this->value[k];
}

void BgpUpdatePathAttributesAsPath::setValueArraySize(size_t newSize)
{
    BgpAsPathSegment *value2 = (newSize==0) ? nullptr : new BgpAsPathSegment[newSize];
    size_t minSize = value_arraysize < newSize ? value_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        value2[i] = this->value[i];
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

void BgpUpdatePathAttributesAsPath::setValue(size_t k, const BgpAsPathSegment& value)
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    this->value[k] = value;
}

void BgpUpdatePathAttributesAsPath::insertValue(size_t k, const BgpAsPathSegment& value)
{
    if (k > value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    size_t newSize = value_arraysize + 1;
    BgpAsPathSegment *value2 = new BgpAsPathSegment[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        value2[i] = this->value[i];
    value2[k] = value;
    for (i = k + 1; i < newSize; i++)
        value2[i] = this->value[i-1];
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

void BgpUpdatePathAttributesAsPath::appendValue(const BgpAsPathSegment& value)
{
    insertValue(value_arraysize, value);
}

void BgpUpdatePathAttributesAsPath::eraseValue(size_t k)
{
    if (k >= value_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)value_arraysize, (unsigned long)k);
    size_t newSize = value_arraysize - 1;
    BgpAsPathSegment *value2 = (newSize == 0) ? nullptr : new BgpAsPathSegment[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        value2[i] = this->value[i];
    for (i = k; i < newSize; i++)
        value2[i] = this->value[i+1];
    delete [] this->value;
    this->value = value2;
    value_arraysize = newSize;
}

class BgpUpdatePathAttributesAsPathDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpUpdatePathAttributesAsPathDescriptor();
    virtual ~BgpUpdatePathAttributesAsPathDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesAsPathDescriptor)

BgpUpdatePathAttributesAsPathDescriptor::BgpUpdatePathAttributesAsPathDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesAsPath)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesAsPathDescriptor::~BgpUpdatePathAttributesAsPathDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesAsPathDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesAsPath *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesAsPathDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesAsPathDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesAsPathDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpUpdatePathAttributesAsPathDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdatePathAttributesAsPathDescriptor::getFieldName(int field) const
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

int BgpUpdatePathAttributesAsPathDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesAsPathDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bgp::BgpAsPathSegment",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesAsPathDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesAsPathDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesAsPathDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        case FIELD_value: return pp->getValueArraySize();
        default: return 0;
    }
}

void BgpUpdatePathAttributesAsPathDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValueArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesAsPath'", field);
    }
}

const char *BgpUpdatePathAttributesAsPathDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesAsPathDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        case FIELD_value: return pp->getValue(i).str();
        default: return "";
    }
}

void BgpUpdatePathAttributesAsPathDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAsPath'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesAsPathDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        case FIELD_value: return omnetpp::toAnyPtr(&pp->getValue(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesAsPath' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesAsPathDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAsPath'", field);
    }
}

const char *BgpUpdatePathAttributesAsPathDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_value: return omnetpp::opp_typename(typeid(BgpAsPathSegment));
        default: return nullptr;
    };
}

omnetpp::any_ptr BgpUpdatePathAttributesAsPathDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        case FIELD_value: return omnetpp::toAnyPtr(&pp->getValue(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesAsPathDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAsPath *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAsPath>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAsPath'", field);
    }
}

Register_Class(BgpUpdatePathAttributesNextHop)

BgpUpdatePathAttributesNextHop::BgpUpdatePathAttributesNextHop() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(NEXT_HOP);
    this->setOptionalBit(false);
    this->setTransitiveBit(true);
    this->setLength(4);

}

BgpUpdatePathAttributesNextHop::BgpUpdatePathAttributesNextHop(const BgpUpdatePathAttributesNextHop& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesNextHop::~BgpUpdatePathAttributesNextHop()
{
}

BgpUpdatePathAttributesNextHop& BgpUpdatePathAttributesNextHop::operator=(const BgpUpdatePathAttributesNextHop& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesNextHop::copy(const BgpUpdatePathAttributesNextHop& other)
{
    this->value = other.value;
}

void BgpUpdatePathAttributesNextHop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    doParsimPacking(b,this->value);
}

void BgpUpdatePathAttributesNextHop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
}

const ::inet::Ipv4Address& BgpUpdatePathAttributesNextHop::getValue() const
{
    return this->value;
}

void BgpUpdatePathAttributesNextHop::setValue(const ::inet::Ipv4Address& value)
{
    this->value = value;
}

class BgpUpdatePathAttributesNextHopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpUpdatePathAttributesNextHopDescriptor();
    virtual ~BgpUpdatePathAttributesNextHopDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesNextHopDescriptor)

BgpUpdatePathAttributesNextHopDescriptor::BgpUpdatePathAttributesNextHopDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesNextHop)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesNextHopDescriptor::~BgpUpdatePathAttributesNextHopDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesNextHopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesNextHop *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesNextHopDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesNextHopDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesNextHopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpUpdatePathAttributesNextHopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdatePathAttributesNextHopDescriptor::getFieldName(int field) const
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

int BgpUpdatePathAttributesNextHopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesNextHopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesNextHopDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesNextHopDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesNextHopDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesNextHopDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesNextHop'", field);
    }
}

const char *BgpUpdatePathAttributesNextHopDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesNextHopDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        case FIELD_value: return pp->getValue().str();
        default: return "";
    }
}

void BgpUpdatePathAttributesNextHopDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesNextHop'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesNextHopDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        case FIELD_value: return omnetpp::toAnyPtr(&pp->getValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesNextHop' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesNextHopDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesNextHop'", field);
    }
}

const char *BgpUpdatePathAttributesNextHopDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesNextHopDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        case FIELD_value: return omnetpp::toAnyPtr(&pp->getValue()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesNextHopDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesNextHop *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesNextHop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesNextHop'", field);
    }
}

Register_Class(BgpUpdatePathAttributesMultiExitDisc)

BgpUpdatePathAttributesMultiExitDisc::BgpUpdatePathAttributesMultiExitDisc() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(MULTI_EXIT_DISC);
    this->setOptionalBit(true);
    this->setTransitiveBit(false);
    this->setLength(4);

}

BgpUpdatePathAttributesMultiExitDisc::BgpUpdatePathAttributesMultiExitDisc(const BgpUpdatePathAttributesMultiExitDisc& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesMultiExitDisc::~BgpUpdatePathAttributesMultiExitDisc()
{
}

BgpUpdatePathAttributesMultiExitDisc& BgpUpdatePathAttributesMultiExitDisc::operator=(const BgpUpdatePathAttributesMultiExitDisc& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesMultiExitDisc::copy(const BgpUpdatePathAttributesMultiExitDisc& other)
{
    this->value = other.value;
}

void BgpUpdatePathAttributesMultiExitDisc::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    doParsimPacking(b,this->value);
}

void BgpUpdatePathAttributesMultiExitDisc::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
}

uint32_t BgpUpdatePathAttributesMultiExitDisc::getValue() const
{
    return this->value;
}

void BgpUpdatePathAttributesMultiExitDisc::setValue(uint32_t value)
{
    this->value = value;
}

class BgpUpdatePathAttributesMultiExitDiscDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpUpdatePathAttributesMultiExitDiscDescriptor();
    virtual ~BgpUpdatePathAttributesMultiExitDiscDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesMultiExitDiscDescriptor)

BgpUpdatePathAttributesMultiExitDiscDescriptor::BgpUpdatePathAttributesMultiExitDiscDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesMultiExitDisc)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesMultiExitDiscDescriptor::~BgpUpdatePathAttributesMultiExitDiscDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesMultiExitDiscDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesMultiExitDisc *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesMultiExitDiscDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldTypeFlags(int field) const
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

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldName(int field) const
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

int BgpUpdatePathAttributesMultiExitDiscDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesMultiExitDiscDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesMultiExitDisc'", field);
    }
}

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        case FIELD_value: return ulong2string(pp->getValue());
        default: return "";
    }
}

void BgpUpdatePathAttributesMultiExitDiscDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesMultiExitDisc'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        case FIELD_value: return (omnetpp::intval_t)(pp->getValue());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesMultiExitDisc' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesMultiExitDiscDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesMultiExitDisc'", field);
    }
}

const char *BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesMultiExitDiscDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesMultiExitDiscDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesMultiExitDisc *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesMultiExitDisc>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesMultiExitDisc'", field);
    }
}

Register_Class(BgpUpdatePathAttributesLocalPref)

BgpUpdatePathAttributesLocalPref::BgpUpdatePathAttributesLocalPref() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(LOCAL_PREF);
    this->setOptionalBit(false);
    this->setTransitiveBit(true);
    this->setLength(4);

}

BgpUpdatePathAttributesLocalPref::BgpUpdatePathAttributesLocalPref(const BgpUpdatePathAttributesLocalPref& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesLocalPref::~BgpUpdatePathAttributesLocalPref()
{
}

BgpUpdatePathAttributesLocalPref& BgpUpdatePathAttributesLocalPref::operator=(const BgpUpdatePathAttributesLocalPref& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesLocalPref::copy(const BgpUpdatePathAttributesLocalPref& other)
{
    this->value = other.value;
}

void BgpUpdatePathAttributesLocalPref::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    doParsimPacking(b,this->value);
}

void BgpUpdatePathAttributesLocalPref::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
}

uint32_t BgpUpdatePathAttributesLocalPref::getValue() const
{
    return this->value;
}

void BgpUpdatePathAttributesLocalPref::setValue(uint32_t value)
{
    this->value = value;
}

class BgpUpdatePathAttributesLocalPrefDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_value,
    };
  public:
    BgpUpdatePathAttributesLocalPrefDescriptor();
    virtual ~BgpUpdatePathAttributesLocalPrefDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesLocalPrefDescriptor)

BgpUpdatePathAttributesLocalPrefDescriptor::BgpUpdatePathAttributesLocalPrefDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesLocalPref)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesLocalPrefDescriptor::~BgpUpdatePathAttributesLocalPrefDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesLocalPrefDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesLocalPref *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesLocalPrefDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesLocalPrefDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int BgpUpdatePathAttributesLocalPrefDescriptor::getFieldTypeFlags(int field) const
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

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getFieldName(int field) const
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

int BgpUpdatePathAttributesLocalPrefDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "value") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_value
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesLocalPrefDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesLocalPrefDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesLocalPrefDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesLocalPref'", field);
    }
}

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesLocalPrefDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        case FIELD_value: return ulong2string(pp->getValue());
        default: return "";
    }
}

void BgpUpdatePathAttributesLocalPrefDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesLocalPref'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesLocalPrefDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        case FIELD_value: return (omnetpp::intval_t)(pp->getValue());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesLocalPref' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesLocalPrefDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        case FIELD_value: pp->setValue(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesLocalPref'", field);
    }
}

const char *BgpUpdatePathAttributesLocalPrefDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesLocalPrefDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesLocalPrefDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesLocalPref *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesLocalPref>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesLocalPref'", field);
    }
}

Register_Class(BgpUpdatePathAttributesAtomicAggregate)

BgpUpdatePathAttributesAtomicAggregate::BgpUpdatePathAttributesAtomicAggregate() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(ATOMIC_AGGREGATE);
    this->setOptionalBit(false);
    this->setTransitiveBit(true);
    this->setLength(0);
}

BgpUpdatePathAttributesAtomicAggregate::BgpUpdatePathAttributesAtomicAggregate(const BgpUpdatePathAttributesAtomicAggregate& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesAtomicAggregate::~BgpUpdatePathAttributesAtomicAggregate()
{
}

BgpUpdatePathAttributesAtomicAggregate& BgpUpdatePathAttributesAtomicAggregate::operator=(const BgpUpdatePathAttributesAtomicAggregate& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesAtomicAggregate::copy(const BgpUpdatePathAttributesAtomicAggregate& other)
{
}

void BgpUpdatePathAttributesAtomicAggregate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
}

void BgpUpdatePathAttributesAtomicAggregate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
}

class BgpUpdatePathAttributesAtomicAggregateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    BgpUpdatePathAttributesAtomicAggregateDescriptor();
    virtual ~BgpUpdatePathAttributesAtomicAggregateDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesAtomicAggregateDescriptor)

BgpUpdatePathAttributesAtomicAggregateDescriptor::BgpUpdatePathAttributesAtomicAggregateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesAtomicAggregate)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesAtomicAggregateDescriptor::~BgpUpdatePathAttributesAtomicAggregateDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesAtomicAggregateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesAtomicAggregate *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesAtomicAggregateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int BgpUpdatePathAttributesAtomicAggregateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesAtomicAggregateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesAtomicAggregate'", field);
    }
}

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void BgpUpdatePathAttributesAtomicAggregateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAtomicAggregate'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesAtomicAggregate' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesAtomicAggregateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAtomicAggregate'", field);
    }
}

const char *BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr BgpUpdatePathAttributesAtomicAggregateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesAtomicAggregateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAtomicAggregate *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAtomicAggregate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAtomicAggregate'", field);
    }
}

Register_Class(BgpUpdatePathAttributesAggregator)

BgpUpdatePathAttributesAggregator::BgpUpdatePathAttributesAggregator() : ::inet::bgp::BgpUpdatePathAttributes()
{
    this->setTypeCode(AGGREGATOR);
    this->setOptionalBit(true);
    this->setTransitiveBit(true);
    this->setLength(6);

}

BgpUpdatePathAttributesAggregator::BgpUpdatePathAttributesAggregator(const BgpUpdatePathAttributesAggregator& other) : ::inet::bgp::BgpUpdatePathAttributes(other)
{
    copy(other);
}

BgpUpdatePathAttributesAggregator::~BgpUpdatePathAttributesAggregator()
{
}

BgpUpdatePathAttributesAggregator& BgpUpdatePathAttributesAggregator::operator=(const BgpUpdatePathAttributesAggregator& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpUpdatePathAttributes::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdatePathAttributesAggregator::copy(const BgpUpdatePathAttributesAggregator& other)
{
    this->asNumber = other.asNumber;
    this->bgpSpeaker = other.bgpSpeaker;
}

void BgpUpdatePathAttributesAggregator::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimPack(b);
    doParsimPacking(b,this->asNumber);
    doParsimPacking(b,this->bgpSpeaker);
}

void BgpUpdatePathAttributesAggregator::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpUpdatePathAttributes::parsimUnpack(b);
    doParsimUnpacking(b,this->asNumber);
    doParsimUnpacking(b,this->bgpSpeaker);
}

uint16_t BgpUpdatePathAttributesAggregator::getAsNumber() const
{
    return this->asNumber;
}

void BgpUpdatePathAttributesAggregator::setAsNumber(uint16_t asNumber)
{
    this->asNumber = asNumber;
}

const ::inet::Ipv4Address& BgpUpdatePathAttributesAggregator::getBgpSpeaker() const
{
    return this->bgpSpeaker;
}

void BgpUpdatePathAttributesAggregator::setBgpSpeaker(const ::inet::Ipv4Address& bgpSpeaker)
{
    this->bgpSpeaker = bgpSpeaker;
}

class BgpUpdatePathAttributesAggregatorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_asNumber,
        FIELD_bgpSpeaker,
    };
  public:
    BgpUpdatePathAttributesAggregatorDescriptor();
    virtual ~BgpUpdatePathAttributesAggregatorDescriptor();

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

Register_ClassDescriptor(BgpUpdatePathAttributesAggregatorDescriptor)

BgpUpdatePathAttributesAggregatorDescriptor::BgpUpdatePathAttributesAggregatorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdatePathAttributesAggregator)), "inet::bgp::BgpUpdatePathAttributes")
{
    propertyNames = nullptr;
}

BgpUpdatePathAttributesAggregatorDescriptor::~BgpUpdatePathAttributesAggregatorDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdatePathAttributesAggregatorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdatePathAttributesAggregator *>(obj)!=nullptr;
}

const char **BgpUpdatePathAttributesAggregatorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdatePathAttributesAggregatorDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdatePathAttributesAggregatorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int BgpUpdatePathAttributesAggregatorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_asNumber
        0,    // FIELD_bgpSpeaker
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdatePathAttributesAggregatorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "asNumber",
        "bgpSpeaker",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int BgpUpdatePathAttributesAggregatorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "asNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bgpSpeaker") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdatePathAttributesAggregatorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_asNumber
        "inet::Ipv4Address",    // FIELD_bgpSpeaker
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdatePathAttributesAggregatorDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdatePathAttributesAggregatorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdatePathAttributesAggregatorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdatePathAttributesAggregatorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdatePathAttributesAggregator'", field);
    }
}

const char *BgpUpdatePathAttributesAggregatorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdatePathAttributesAggregatorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        case FIELD_asNumber: return ulong2string(pp->getAsNumber());
        case FIELD_bgpSpeaker: return pp->getBgpSpeaker().str();
        default: return "";
    }
}

void BgpUpdatePathAttributesAggregatorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        case FIELD_asNumber: pp->setAsNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAggregator'", field);
    }
}

omnetpp::cValue BgpUpdatePathAttributesAggregatorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        case FIELD_asNumber: return (omnetpp::intval_t)(pp->getAsNumber());
        case FIELD_bgpSpeaker: return omnetpp::toAnyPtr(&pp->getBgpSpeaker()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdatePathAttributesAggregator' as cValue -- field index out of range?", field);
    }
}

void BgpUpdatePathAttributesAggregatorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        case FIELD_asNumber: pp->setAsNumber(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAggregator'", field);
    }
}

const char *BgpUpdatePathAttributesAggregatorDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdatePathAttributesAggregatorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        case FIELD_bgpSpeaker: return omnetpp::toAnyPtr(&pp->getBgpSpeaker()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdatePathAttributesAggregatorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdatePathAttributesAggregator *pp = omnetpp::fromAnyPtr<BgpUpdatePathAttributesAggregator>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdatePathAttributesAggregator'", field);
    }
}

BgpUpdateWithdrawnRoutes::BgpUpdateWithdrawnRoutes()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const BgpUpdateWithdrawnRoutes& a)
{
    doParsimPacking(b,a.length);
    doParsimPacking(b,a.prefix);
}

void __doUnpacking(omnetpp::cCommBuffer *b, BgpUpdateWithdrawnRoutes& a)
{
    doParsimUnpacking(b,a.length);
    doParsimUnpacking(b,a.prefix);
}

class BgpUpdateWithdrawnRoutesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_length,
        FIELD_prefix,
    };
  public:
    BgpUpdateWithdrawnRoutesDescriptor();
    virtual ~BgpUpdateWithdrawnRoutesDescriptor();

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

Register_ClassDescriptor(BgpUpdateWithdrawnRoutesDescriptor)

BgpUpdateWithdrawnRoutesDescriptor::BgpUpdateWithdrawnRoutesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdateWithdrawnRoutes)), "")
{
    propertyNames = nullptr;
}

BgpUpdateWithdrawnRoutesDescriptor::~BgpUpdateWithdrawnRoutesDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdateWithdrawnRoutesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdateWithdrawnRoutes *>(obj)!=nullptr;
}

const char **BgpUpdateWithdrawnRoutesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdateWithdrawnRoutesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdateWithdrawnRoutesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int BgpUpdateWithdrawnRoutesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_length
        0,    // FIELD_prefix
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdateWithdrawnRoutesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "length",
        "prefix",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int BgpUpdateWithdrawnRoutesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "prefix") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdateWithdrawnRoutesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",    // FIELD_length
        "inet::Ipv4Address",    // FIELD_prefix
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdateWithdrawnRoutesDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdateWithdrawnRoutesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdateWithdrawnRoutesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdateWithdrawnRoutesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdateWithdrawnRoutes'", field);
    }
}

const char *BgpUpdateWithdrawnRoutesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdateWithdrawnRoutesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        case FIELD_length: return ulong2string(pp->length);
        case FIELD_prefix: return pp->prefix.str();
        default: return "";
    }
}

void BgpUpdateWithdrawnRoutesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateWithdrawnRoutes'", field);
    }
}

omnetpp::cValue BgpUpdateWithdrawnRoutesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        case FIELD_length: return (omnetpp::intval_t)(pp->length);
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->prefix); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdateWithdrawnRoutes' as cValue -- field index out of range?", field);
    }
}

void BgpUpdateWithdrawnRoutesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = omnetpp::checked_int_cast<unsigned char>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateWithdrawnRoutes'", field);
    }
}

const char *BgpUpdateWithdrawnRoutesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdateWithdrawnRoutesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->prefix); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdateWithdrawnRoutesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateWithdrawnRoutes *pp = omnetpp::fromAnyPtr<BgpUpdateWithdrawnRoutes>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateWithdrawnRoutes'", field);
    }
}

BgpUpdateNlri::BgpUpdateNlri()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const BgpUpdateNlri& a)
{
    doParsimPacking(b,a.length);
    doParsimPacking(b,a.prefix);
}

void __doUnpacking(omnetpp::cCommBuffer *b, BgpUpdateNlri& a)
{
    doParsimUnpacking(b,a.length);
    doParsimUnpacking(b,a.prefix);
}

class BgpUpdateNlriDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_length,
        FIELD_prefix,
    };
  public:
    BgpUpdateNlriDescriptor();
    virtual ~BgpUpdateNlriDescriptor();

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

Register_ClassDescriptor(BgpUpdateNlriDescriptor)

BgpUpdateNlriDescriptor::BgpUpdateNlriDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdateNlri)), "")
{
    propertyNames = nullptr;
}

BgpUpdateNlriDescriptor::~BgpUpdateNlriDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdateNlriDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdateNlri *>(obj)!=nullptr;
}

const char **BgpUpdateNlriDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdateNlriDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdateNlriDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int BgpUpdateNlriDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_length
        0,    // FIELD_prefix
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdateNlriDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "length",
        "prefix",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int BgpUpdateNlriDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "prefix") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdateNlriDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_length
        "inet::Ipv4Address",    // FIELD_prefix
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdateNlriDescriptor::getFieldPropertyNames(int field) const
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

const char *BgpUpdateNlriDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int BgpUpdateNlriDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BgpUpdateNlriDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdateNlri'", field);
    }
}

const char *BgpUpdateNlriDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BgpUpdateNlriDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        case FIELD_length: return ulong2string(pp->length);
        case FIELD_prefix: return pp->prefix.str();
        default: return "";
    }
}

void BgpUpdateNlriDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateNlri'", field);
    }
}

omnetpp::cValue BgpUpdateNlriDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        case FIELD_length: return (omnetpp::intval_t)(pp->length);
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->prefix); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdateNlri' as cValue -- field index out of range?", field);
    }
}

void BgpUpdateNlriDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->length = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateNlri'", field);
    }
}

const char *BgpUpdateNlriDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr BgpUpdateNlriDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->prefix); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdateNlriDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateNlri *pp = omnetpp::fromAnyPtr<BgpUpdateNlri>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateNlri'", field);
    }
}

Register_Class(BgpUpdateMessage)

BgpUpdateMessage::BgpUpdateMessage() : ::inet::bgp::BgpHeader()
{
    this->setType(BGP_UPDATE);
    this->setChunkLength(BGP_HEADER_OCTETS + BGP_EMPTY_UPDATE_OCTETS);
    this->setTotalLength(B(BGP_HEADER_OCTETS + BGP_EMPTY_UPDATE_OCTETS).get());

}

BgpUpdateMessage::BgpUpdateMessage(const BgpUpdateMessage& other) : ::inet::bgp::BgpHeader(other)
{
    copy(other);
}

BgpUpdateMessage::~BgpUpdateMessage()
{
    delete [] this->withdrawnRoutes;
    for (size_t i = 0; i < pathAttributes_arraysize; i++)
        delete this->pathAttributes[i];
    delete [] this->pathAttributes;
    delete [] this->NLRI;
}

BgpUpdateMessage& BgpUpdateMessage::operator=(const BgpUpdateMessage& other)
{
    if (this == &other) return *this;
    ::inet::bgp::BgpHeader::operator=(other);
    copy(other);
    return *this;
}

void BgpUpdateMessage::copy(const BgpUpdateMessage& other)
{
    this->withDrawnRoutesLength = other.withDrawnRoutesLength;
    delete [] this->withdrawnRoutes;
    this->withdrawnRoutes = (other.withdrawnRoutes_arraysize==0) ? nullptr : new BgpUpdateWithdrawnRoutes[other.withdrawnRoutes_arraysize];
    withdrawnRoutes_arraysize = other.withdrawnRoutes_arraysize;
    for (size_t i = 0; i < withdrawnRoutes_arraysize; i++) {
        this->withdrawnRoutes[i] = other.withdrawnRoutes[i];
    }
    this->totalPathAttributeLength = other.totalPathAttributeLength;
    for (size_t i = 0; i < pathAttributes_arraysize; i++)
        delete this->pathAttributes[i];
    delete [] this->pathAttributes;
    this->pathAttributes = (other.pathAttributes_arraysize==0) ? nullptr : new BgpUpdatePathAttributes *[other.pathAttributes_arraysize];
    pathAttributes_arraysize = other.pathAttributes_arraysize;
    for (size_t i = 0; i < pathAttributes_arraysize; i++) {
        this->pathAttributes[i] = other.pathAttributes[i];
        if (this->pathAttributes[i] != nullptr) {
            this->pathAttributes[i] = this->pathAttributes[i]->dup();
        }
    }
    delete [] this->NLRI;
    this->NLRI = (other.NLRI_arraysize==0) ? nullptr : new BgpUpdateNlri[other.NLRI_arraysize];
    NLRI_arraysize = other.NLRI_arraysize;
    for (size_t i = 0; i < NLRI_arraysize; i++) {
        this->NLRI[i] = other.NLRI[i];
    }
}

void BgpUpdateMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::bgp::BgpHeader::parsimPack(b);
    doParsimPacking(b,this->withDrawnRoutesLength);
    b->pack(withdrawnRoutes_arraysize);
    doParsimArrayPacking(b,this->withdrawnRoutes,withdrawnRoutes_arraysize);
    doParsimPacking(b,this->totalPathAttributeLength);
    b->pack(pathAttributes_arraysize);
    doParsimArrayPacking(b,this->pathAttributes,pathAttributes_arraysize);
    b->pack(NLRI_arraysize);
    doParsimArrayPacking(b,this->NLRI,NLRI_arraysize);
}

void BgpUpdateMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::bgp::BgpHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->withDrawnRoutesLength);
    delete [] this->withdrawnRoutes;
    b->unpack(withdrawnRoutes_arraysize);
    if (withdrawnRoutes_arraysize == 0) {
        this->withdrawnRoutes = nullptr;
    } else {
        this->withdrawnRoutes = new BgpUpdateWithdrawnRoutes[withdrawnRoutes_arraysize];
        doParsimArrayUnpacking(b,this->withdrawnRoutes,withdrawnRoutes_arraysize);
    }
    doParsimUnpacking(b,this->totalPathAttributeLength);
    delete [] this->pathAttributes;
    b->unpack(pathAttributes_arraysize);
    if (pathAttributes_arraysize == 0) {
        this->pathAttributes = nullptr;
    } else {
        this->pathAttributes = new BgpUpdatePathAttributes *[pathAttributes_arraysize];
        doParsimArrayUnpacking(b,this->pathAttributes,pathAttributes_arraysize);
    }
    delete [] this->NLRI;
    b->unpack(NLRI_arraysize);
    if (NLRI_arraysize == 0) {
        this->NLRI = nullptr;
    } else {
        this->NLRI = new BgpUpdateNlri[NLRI_arraysize];
        doParsimArrayUnpacking(b,this->NLRI,NLRI_arraysize);
    }
}

uint16_t BgpUpdateMessage::getWithDrawnRoutesLength() const
{
    return this->withDrawnRoutesLength;
}

void BgpUpdateMessage::setWithDrawnRoutesLength(uint16_t withDrawnRoutesLength)
{
    handleChange();
    this->withDrawnRoutesLength = withDrawnRoutesLength;
}

size_t BgpUpdateMessage::getWithdrawnRoutesArraySize() const
{
    return withdrawnRoutes_arraysize;
}

const BgpUpdateWithdrawnRoutes& BgpUpdateMessage::getWithdrawnRoutes(size_t k) const
{
    if (k >= withdrawnRoutes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)withdrawnRoutes_arraysize, (unsigned long)k);
    return this->withdrawnRoutes[k];
}

void BgpUpdateMessage::setWithdrawnRoutesArraySize(size_t newSize)
{
    handleChange();
    BgpUpdateWithdrawnRoutes *withdrawnRoutes2 = (newSize==0) ? nullptr : new BgpUpdateWithdrawnRoutes[newSize];
    size_t minSize = withdrawnRoutes_arraysize < newSize ? withdrawnRoutes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        withdrawnRoutes2[i] = this->withdrawnRoutes[i];
    delete [] this->withdrawnRoutes;
    this->withdrawnRoutes = withdrawnRoutes2;
    withdrawnRoutes_arraysize = newSize;
}

void BgpUpdateMessage::setWithdrawnRoutes(size_t k, const BgpUpdateWithdrawnRoutes& withdrawnRoutes)
{
    if (k >= withdrawnRoutes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)withdrawnRoutes_arraysize, (unsigned long)k);
    handleChange();
    this->withdrawnRoutes[k] = withdrawnRoutes;
}

void BgpUpdateMessage::insertWithdrawnRoutes(size_t k, const BgpUpdateWithdrawnRoutes& withdrawnRoutes)
{
    if (k > withdrawnRoutes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)withdrawnRoutes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = withdrawnRoutes_arraysize + 1;
    BgpUpdateWithdrawnRoutes *withdrawnRoutes2 = new BgpUpdateWithdrawnRoutes[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        withdrawnRoutes2[i] = this->withdrawnRoutes[i];
    withdrawnRoutes2[k] = withdrawnRoutes;
    for (i = k + 1; i < newSize; i++)
        withdrawnRoutes2[i] = this->withdrawnRoutes[i-1];
    delete [] this->withdrawnRoutes;
    this->withdrawnRoutes = withdrawnRoutes2;
    withdrawnRoutes_arraysize = newSize;
}

void BgpUpdateMessage::appendWithdrawnRoutes(const BgpUpdateWithdrawnRoutes& withdrawnRoutes)
{
    insertWithdrawnRoutes(withdrawnRoutes_arraysize, withdrawnRoutes);
}

void BgpUpdateMessage::eraseWithdrawnRoutes(size_t k)
{
    if (k >= withdrawnRoutes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)withdrawnRoutes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = withdrawnRoutes_arraysize - 1;
    BgpUpdateWithdrawnRoutes *withdrawnRoutes2 = (newSize == 0) ? nullptr : new BgpUpdateWithdrawnRoutes[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        withdrawnRoutes2[i] = this->withdrawnRoutes[i];
    for (i = k; i < newSize; i++)
        withdrawnRoutes2[i] = this->withdrawnRoutes[i+1];
    delete [] this->withdrawnRoutes;
    this->withdrawnRoutes = withdrawnRoutes2;
    withdrawnRoutes_arraysize = newSize;
}

uint16_t BgpUpdateMessage::getTotalPathAttributeLength() const
{
    return this->totalPathAttributeLength;
}

void BgpUpdateMessage::setTotalPathAttributeLength(uint16_t totalPathAttributeLength)
{
    handleChange();
    this->totalPathAttributeLength = totalPathAttributeLength;
}

size_t BgpUpdateMessage::getPathAttributesArraySize() const
{
    return pathAttributes_arraysize;
}

const BgpUpdatePathAttributes * BgpUpdateMessage::getPathAttributes(size_t k) const
{
    if (k >= pathAttributes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathAttributes_arraysize, (unsigned long)k);
    return this->pathAttributes[k];
}

void BgpUpdateMessage::setPathAttributesArraySize(size_t newSize)
{
    handleChange();
    BgpUpdatePathAttributes * *pathAttributes2 = (newSize==0) ? nullptr : new BgpUpdatePathAttributes *[newSize];
    size_t minSize = pathAttributes_arraysize < newSize ? pathAttributes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        pathAttributes2[i] = this->pathAttributes[i];
    for (size_t i = minSize; i < newSize; i++)
        pathAttributes2[i] = nullptr;
    for (size_t i = newSize; i < pathAttributes_arraysize; i++)
        delete pathAttributes[i];
    delete [] this->pathAttributes;
    this->pathAttributes = pathAttributes2;
    pathAttributes_arraysize = newSize;
}

void BgpUpdateMessage::setPathAttributes(size_t k, BgpUpdatePathAttributes * pathAttributes)
{
    if (k >= pathAttributes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathAttributes_arraysize, (unsigned long)k);
    handleChange();
    if (pathAttributes == this->pathAttributes[k]) return;
    if (this->pathAttributes[k] != nullptr && this->pathAttributes[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->pathAttributes[k]); else delete this->pathAttributes[k];
    this->pathAttributes[k] = pathAttributes;
    if (this->pathAttributes[k] != nullptr && this->pathAttributes[k]->isOwnedObject()) take((cOwnedObject*)this->pathAttributes[k]);
}

BgpUpdatePathAttributes * BgpUpdateMessage::removePathAttributes(size_t k)
{
    if (k >= pathAttributes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathAttributes_arraysize, (unsigned long)k);
    handleChange();
    BgpUpdatePathAttributes * retval = this->pathAttributes[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->pathAttributes[k] = nullptr;
    return retval;
}

void BgpUpdateMessage::insertPathAttributes(size_t k, BgpUpdatePathAttributes * pathAttributes)
{
    if (k > pathAttributes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathAttributes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = pathAttributes_arraysize + 1;
    BgpUpdatePathAttributes * *pathAttributes2 = new BgpUpdatePathAttributes *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        pathAttributes2[i] = this->pathAttributes[i];
    pathAttributes2[k] = pathAttributes;
    if (pathAttributes2[k] != nullptr && pathAttributes2[k]->isOwnedObject()) take((cOwnedObject*)pathAttributes2[k]);
    for (i = k + 1; i < newSize; i++)
        pathAttributes2[i] = this->pathAttributes[i-1];
    delete [] this->pathAttributes;
    this->pathAttributes = pathAttributes2;
    pathAttributes_arraysize = newSize;
}

void BgpUpdateMessage::appendPathAttributes(BgpUpdatePathAttributes * pathAttributes)
{
    insertPathAttributes(pathAttributes_arraysize, pathAttributes);
}

void BgpUpdateMessage::erasePathAttributes(size_t k)
{
    if (k >= pathAttributes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)pathAttributes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = pathAttributes_arraysize - 1;
    BgpUpdatePathAttributes * *pathAttributes2 = (newSize == 0) ? nullptr : new BgpUpdatePathAttributes *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        pathAttributes2[i] = this->pathAttributes[i];
    for (i = k; i < newSize; i++)
        pathAttributes2[i] = this->pathAttributes[i+1];
    if (this->pathAttributes[k] != nullptr && this->pathAttributes[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->pathAttributes[k]); else delete this->pathAttributes[k];
    delete [] this->pathAttributes;
    this->pathAttributes = pathAttributes2;
    pathAttributes_arraysize = newSize;
}

size_t BgpUpdateMessage::getNLRIArraySize() const
{
    return NLRI_arraysize;
}

const BgpUpdateNlri& BgpUpdateMessage::getNLRI(size_t k) const
{
    if (k >= NLRI_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NLRI_arraysize, (unsigned long)k);
    return this->NLRI[k];
}

void BgpUpdateMessage::setNLRIArraySize(size_t newSize)
{
    handleChange();
    BgpUpdateNlri *NLRI2 = (newSize==0) ? nullptr : new BgpUpdateNlri[newSize];
    size_t minSize = NLRI_arraysize < newSize ? NLRI_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        NLRI2[i] = this->NLRI[i];
    delete [] this->NLRI;
    this->NLRI = NLRI2;
    NLRI_arraysize = newSize;
}

void BgpUpdateMessage::setNLRI(size_t k, const BgpUpdateNlri& NLRI)
{
    if (k >= NLRI_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NLRI_arraysize, (unsigned long)k);
    handleChange();
    this->NLRI[k] = NLRI;
}

void BgpUpdateMessage::insertNLRI(size_t k, const BgpUpdateNlri& NLRI)
{
    if (k > NLRI_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NLRI_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = NLRI_arraysize + 1;
    BgpUpdateNlri *NLRI2 = new BgpUpdateNlri[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        NLRI2[i] = this->NLRI[i];
    NLRI2[k] = NLRI;
    for (i = k + 1; i < newSize; i++)
        NLRI2[i] = this->NLRI[i-1];
    delete [] this->NLRI;
    this->NLRI = NLRI2;
    NLRI_arraysize = newSize;
}

void BgpUpdateMessage::appendNLRI(const BgpUpdateNlri& NLRI)
{
    insertNLRI(NLRI_arraysize, NLRI);
}

void BgpUpdateMessage::eraseNLRI(size_t k)
{
    if (k >= NLRI_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)NLRI_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = NLRI_arraysize - 1;
    BgpUpdateNlri *NLRI2 = (newSize == 0) ? nullptr : new BgpUpdateNlri[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        NLRI2[i] = this->NLRI[i];
    for (i = k; i < newSize; i++)
        NLRI2[i] = this->NLRI[i+1];
    delete [] this->NLRI;
    this->NLRI = NLRI2;
    NLRI_arraysize = newSize;
}

class BgpUpdateMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_withDrawnRoutesLength,
        FIELD_withdrawnRoutes,
        FIELD_totalPathAttributeLength,
        FIELD_pathAttributes,
        FIELD_NLRI,
    };
  public:
    BgpUpdateMessageDescriptor();
    virtual ~BgpUpdateMessageDescriptor();

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

Register_ClassDescriptor(BgpUpdateMessageDescriptor)

BgpUpdateMessageDescriptor::BgpUpdateMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::bgp::BgpUpdateMessage)), "inet::bgp::BgpHeader")
{
    propertyNames = nullptr;
}

BgpUpdateMessageDescriptor::~BgpUpdateMessageDescriptor()
{
    delete[] propertyNames;
}

bool BgpUpdateMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BgpUpdateMessage *>(obj)!=nullptr;
}

const char **BgpUpdateMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BgpUpdateMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BgpUpdateMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int BgpUpdateMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_withDrawnRoutesLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_withdrawnRoutes
        FD_ISEDITABLE,    // FIELD_totalPathAttributeLength
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_pathAttributes
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_NLRI
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *BgpUpdateMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "withDrawnRoutesLength",
        "withdrawnRoutes",
        "totalPathAttributeLength",
        "pathAttributes",
        "NLRI",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int BgpUpdateMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "withDrawnRoutesLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "withdrawnRoutes") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "totalPathAttributeLength") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pathAttributes") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "NLRI") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *BgpUpdateMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_withDrawnRoutesLength
        "inet::bgp::BgpUpdateWithdrawnRoutes",    // FIELD_withdrawnRoutes
        "uint16_t",    // FIELD_totalPathAttributeLength
        "inet::bgp::BgpUpdatePathAttributes",    // FIELD_pathAttributes
        "inet::bgp::BgpUpdateNlri",    // FIELD_NLRI
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **BgpUpdateMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_pathAttributes: {
            static const char *names[] = { "owned", "allowReplace",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BgpUpdateMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_pathAttributes:
            if (!strcmp(propertyName, "owned")) return "";
            if (!strcmp(propertyName, "allowReplace")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int BgpUpdateMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withdrawnRoutes: return pp->getWithdrawnRoutesArraySize();
        case FIELD_pathAttributes: return pp->getPathAttributesArraySize();
        case FIELD_NLRI: return pp->getNLRIArraySize();
        default: return 0;
    }
}

void BgpUpdateMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withdrawnRoutes: pp->setWithdrawnRoutesArraySize(size); break;
        case FIELD_pathAttributes: pp->setPathAttributesArraySize(size); break;
        case FIELD_NLRI: pp->setNLRIArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BgpUpdateMessage'", field);
    }
}

const char *BgpUpdateMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_pathAttributes: { const BgpUpdatePathAttributes * value = pp->getPathAttributes(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string BgpUpdateMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withDrawnRoutesLength: return ulong2string(pp->getWithDrawnRoutesLength());
        case FIELD_withdrawnRoutes: return "";
        case FIELD_totalPathAttributeLength: return ulong2string(pp->getTotalPathAttributeLength());
        case FIELD_pathAttributes: { auto obj = pp->getPathAttributes(i); return obj == nullptr ? "" : obj->str(); }
        case FIELD_NLRI: return "";
        default: return "";
    }
}

void BgpUpdateMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withDrawnRoutesLength: pp->setWithDrawnRoutesLength(string2ulong(value)); break;
        case FIELD_totalPathAttributeLength: pp->setTotalPathAttributeLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateMessage'", field);
    }
}

omnetpp::cValue BgpUpdateMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withDrawnRoutesLength: return (omnetpp::intval_t)(pp->getWithDrawnRoutesLength());
        case FIELD_withdrawnRoutes: return omnetpp::toAnyPtr(&pp->getWithdrawnRoutes(i)); break;
        case FIELD_totalPathAttributeLength: return (omnetpp::intval_t)(pp->getTotalPathAttributeLength());
        case FIELD_pathAttributes: return omnetpp::toAnyPtr(pp->getPathAttributes(i)); break;
        case FIELD_NLRI: return omnetpp::toAnyPtr(&pp->getNLRI(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BgpUpdateMessage' as cValue -- field index out of range?", field);
    }
}

void BgpUpdateMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withDrawnRoutesLength: pp->setWithDrawnRoutesLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_totalPathAttributeLength: pp->setTotalPathAttributeLength(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_pathAttributes: pp->setPathAttributes(i,omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateMessage'", field);
    }
}

const char *BgpUpdateMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_withdrawnRoutes: return omnetpp::opp_typename(typeid(BgpUpdateWithdrawnRoutes));
        case FIELD_pathAttributes: return omnetpp::opp_typename(typeid(BgpUpdatePathAttributes));
        case FIELD_NLRI: return omnetpp::opp_typename(typeid(BgpUpdateNlri));
        default: return nullptr;
    };
}

omnetpp::any_ptr BgpUpdateMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_withdrawnRoutes: return omnetpp::toAnyPtr(&pp->getWithdrawnRoutes(i)); break;
        case FIELD_pathAttributes: return omnetpp::toAnyPtr(pp->getPathAttributes(i)); break;
        case FIELD_NLRI: return omnetpp::toAnyPtr(&pp->getNLRI(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BgpUpdateMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BgpUpdateMessage *pp = omnetpp::fromAnyPtr<BgpUpdateMessage>(object); (void)pp;
    switch (field) {
        case FIELD_pathAttributes: pp->setPathAttributes(i,omnetpp::fromAnyPtr<BgpUpdatePathAttributes>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BgpUpdateMessage'", field);
    }
}

}  // namespace bgp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

