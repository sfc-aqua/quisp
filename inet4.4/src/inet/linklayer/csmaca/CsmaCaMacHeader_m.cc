//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/csmaca/CsmaCaMacHeader.msg.
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
#include "CsmaCaMacHeader_m.h"

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

Register_Enum(inet::CsmaCaMacHeaderType, (inet::CsmaCaMacHeaderType::CSMA_DATA, inet::CsmaCaMacHeaderType::CSMA_ACK));

Register_Class(CsmaCaMacHeader)

CsmaCaMacHeader::CsmaCaMacHeader() : ::inet::FieldsChunk()
{
}

CsmaCaMacHeader::CsmaCaMacHeader(const CsmaCaMacHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

CsmaCaMacHeader::~CsmaCaMacHeader()
{
}

CsmaCaMacHeader& CsmaCaMacHeader::operator=(const CsmaCaMacHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacHeader::copy(const CsmaCaMacHeader& other)
{
    this->type = other.type;
    this->headerLengthField = other.headerLengthField;
    this->transmitterAddress = other.transmitterAddress;
    this->receiverAddress = other.receiverAddress;
}

void CsmaCaMacHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->headerLengthField);
    doParsimPacking(b,this->transmitterAddress);
    doParsimPacking(b,this->receiverAddress);
}

void CsmaCaMacHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->headerLengthField);
    doParsimUnpacking(b,this->transmitterAddress);
    doParsimUnpacking(b,this->receiverAddress);
}

CsmaCaMacHeaderType CsmaCaMacHeader::getType() const
{
    return this->type;
}

void CsmaCaMacHeader::setType(CsmaCaMacHeaderType type)
{
    handleChange();
    this->type = type;
}

uint8_t CsmaCaMacHeader::getHeaderLengthField() const
{
    return this->headerLengthField;
}

void CsmaCaMacHeader::setHeaderLengthField(uint8_t headerLengthField)
{
    handleChange();
    this->headerLengthField = headerLengthField;
}

const MacAddress& CsmaCaMacHeader::getTransmitterAddress() const
{
    return this->transmitterAddress;
}

void CsmaCaMacHeader::setTransmitterAddress(const MacAddress& transmitterAddress)
{
    handleChange();
    this->transmitterAddress = transmitterAddress;
}

const MacAddress& CsmaCaMacHeader::getReceiverAddress() const
{
    return this->receiverAddress;
}

void CsmaCaMacHeader::setReceiverAddress(const MacAddress& receiverAddress)
{
    handleChange();
    this->receiverAddress = receiverAddress;
}

class CsmaCaMacHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_headerLengthField,
        FIELD_transmitterAddress,
        FIELD_receiverAddress,
    };
  public:
    CsmaCaMacHeaderDescriptor();
    virtual ~CsmaCaMacHeaderDescriptor();

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

Register_ClassDescriptor(CsmaCaMacHeaderDescriptor)

CsmaCaMacHeaderDescriptor::CsmaCaMacHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CsmaCaMacHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

CsmaCaMacHeaderDescriptor::~CsmaCaMacHeaderDescriptor()
{
    delete[] propertyNames;
}

bool CsmaCaMacHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacHeader *>(obj)!=nullptr;
}

const char **CsmaCaMacHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CsmaCaMacHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CsmaCaMacHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int CsmaCaMacHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_headerLengthField
        0,    // FIELD_transmitterAddress
        0,    // FIELD_receiverAddress
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *CsmaCaMacHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "headerLengthField",
        "transmitterAddress",
        "receiverAddress",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int CsmaCaMacHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "headerLengthField") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "transmitterAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "receiverAddress") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *CsmaCaMacHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::CsmaCaMacHeaderType",    // FIELD_type
        "uint8_t",    // FIELD_headerLengthField
        "inet::MacAddress",    // FIELD_transmitterAddress
        "inet::MacAddress",    // FIELD_receiverAddress
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **CsmaCaMacHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::CsmaCaMacHeaderType";
            return nullptr;
        default: return nullptr;
    }
}

int CsmaCaMacHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CsmaCaMacHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CsmaCaMacHeader'", field);
    }
}

const char *CsmaCaMacHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CsmaCaMacHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::CsmaCaMacHeaderType");
        case FIELD_headerLengthField: return ulong2string(pp->getHeaderLengthField());
        case FIELD_transmitterAddress: return pp->getTransmitterAddress().str();
        case FIELD_receiverAddress: return pp->getReceiverAddress().str();
        default: return "";
    }
}

void CsmaCaMacHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLengthField: pp->setHeaderLengthField(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacHeader'", field);
    }
}

omnetpp::cValue CsmaCaMacHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_headerLengthField: return (omnetpp::intval_t)(pp->getHeaderLengthField());
        case FIELD_transmitterAddress: return omnetpp::toAnyPtr(&pp->getTransmitterAddress()); break;
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CsmaCaMacHeader' as cValue -- field index out of range?", field);
    }
}

void CsmaCaMacHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerLengthField: pp->setHeaderLengthField(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacHeader'", field);
    }
}

const char *CsmaCaMacHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CsmaCaMacHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        case FIELD_transmitterAddress: return omnetpp::toAnyPtr(&pp->getTransmitterAddress()); break;
        case FIELD_receiverAddress: return omnetpp::toAnyPtr(&pp->getReceiverAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CsmaCaMacHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacHeader'", field);
    }
}

Register_Class(CsmaCaMacAckHeader)

CsmaCaMacAckHeader::CsmaCaMacAckHeader() : ::inet::CsmaCaMacHeader()
{
    this->setChunkLength(B(14));
    this->setType(CSMA_ACK);
}

CsmaCaMacAckHeader::CsmaCaMacAckHeader(const CsmaCaMacAckHeader& other) : ::inet::CsmaCaMacHeader(other)
{
    copy(other);
}

CsmaCaMacAckHeader::~CsmaCaMacAckHeader()
{
}

CsmaCaMacAckHeader& CsmaCaMacAckHeader::operator=(const CsmaCaMacAckHeader& other)
{
    if (this == &other) return *this;
    ::inet::CsmaCaMacHeader::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacAckHeader::copy(const CsmaCaMacAckHeader& other)
{
}

void CsmaCaMacAckHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::CsmaCaMacHeader::parsimPack(b);
}

void CsmaCaMacAckHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::CsmaCaMacHeader::parsimUnpack(b);
}

class CsmaCaMacAckHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    CsmaCaMacAckHeaderDescriptor();
    virtual ~CsmaCaMacAckHeaderDescriptor();

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

Register_ClassDescriptor(CsmaCaMacAckHeaderDescriptor)

CsmaCaMacAckHeaderDescriptor::CsmaCaMacAckHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CsmaCaMacAckHeader)), "inet::CsmaCaMacHeader")
{
    propertyNames = nullptr;
}

CsmaCaMacAckHeaderDescriptor::~CsmaCaMacAckHeaderDescriptor()
{
    delete[] propertyNames;
}

bool CsmaCaMacAckHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacAckHeader *>(obj)!=nullptr;
}

const char **CsmaCaMacAckHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CsmaCaMacAckHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CsmaCaMacAckHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int CsmaCaMacAckHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *CsmaCaMacAckHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int CsmaCaMacAckHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *CsmaCaMacAckHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **CsmaCaMacAckHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacAckHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CsmaCaMacAckHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CsmaCaMacAckHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CsmaCaMacAckHeader'", field);
    }
}

const char *CsmaCaMacAckHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CsmaCaMacAckHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void CsmaCaMacAckHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacAckHeader'", field);
    }
}

omnetpp::cValue CsmaCaMacAckHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CsmaCaMacAckHeader' as cValue -- field index out of range?", field);
    }
}

void CsmaCaMacAckHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacAckHeader'", field);
    }
}

const char *CsmaCaMacAckHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr CsmaCaMacAckHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CsmaCaMacAckHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacAckHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacAckHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacAckHeader'", field);
    }
}

Register_Class(CsmaCaMacDataHeader)

CsmaCaMacDataHeader::CsmaCaMacDataHeader() : ::inet::CsmaCaMacHeader()
{
    this->setChunkLength(B(17));
    this->setType(CSMA_DATA);

}

CsmaCaMacDataHeader::CsmaCaMacDataHeader(const CsmaCaMacDataHeader& other) : ::inet::CsmaCaMacHeader(other)
{
    copy(other);
}

CsmaCaMacDataHeader::~CsmaCaMacDataHeader()
{
}

CsmaCaMacDataHeader& CsmaCaMacDataHeader::operator=(const CsmaCaMacDataHeader& other)
{
    if (this == &other) return *this;
    ::inet::CsmaCaMacHeader::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacDataHeader::copy(const CsmaCaMacDataHeader& other)
{
    this->networkProtocol = other.networkProtocol;
    this->priority = other.priority;
}

void CsmaCaMacDataHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::CsmaCaMacHeader::parsimPack(b);
    doParsimPacking(b,this->networkProtocol);
    doParsimPacking(b,this->priority);
}

void CsmaCaMacDataHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::CsmaCaMacHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->networkProtocol);
    doParsimUnpacking(b,this->priority);
}

int CsmaCaMacDataHeader::getNetworkProtocol() const
{
    return this->networkProtocol;
}

void CsmaCaMacDataHeader::setNetworkProtocol(int networkProtocol)
{
    handleChange();
    this->networkProtocol = networkProtocol;
}

int CsmaCaMacDataHeader::getPriority() const
{
    return this->priority;
}

void CsmaCaMacDataHeader::setPriority(int priority)
{
    handleChange();
    this->priority = priority;
}

class CsmaCaMacDataHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_networkProtocol,
        FIELD_priority,
    };
  public:
    CsmaCaMacDataHeaderDescriptor();
    virtual ~CsmaCaMacDataHeaderDescriptor();

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

Register_ClassDescriptor(CsmaCaMacDataHeaderDescriptor)

CsmaCaMacDataHeaderDescriptor::CsmaCaMacDataHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CsmaCaMacDataHeader)), "inet::CsmaCaMacHeader")
{
    propertyNames = nullptr;
}

CsmaCaMacDataHeaderDescriptor::~CsmaCaMacDataHeaderDescriptor()
{
    delete[] propertyNames;
}

bool CsmaCaMacDataHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacDataHeader *>(obj)!=nullptr;
}

const char **CsmaCaMacDataHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CsmaCaMacDataHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CsmaCaMacDataHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int CsmaCaMacDataHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_networkProtocol
        FD_ISEDITABLE,    // FIELD_priority
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *CsmaCaMacDataHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "networkProtocol",
        "priority",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int CsmaCaMacDataHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "networkProtocol") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *CsmaCaMacDataHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_networkProtocol
        "int",    // FIELD_priority
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **CsmaCaMacDataHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *CsmaCaMacDataHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CsmaCaMacDataHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CsmaCaMacDataHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CsmaCaMacDataHeader'", field);
    }
}

const char *CsmaCaMacDataHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CsmaCaMacDataHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: return long2string(pp->getNetworkProtocol());
        case FIELD_priority: return long2string(pp->getPriority());
        default: return "";
    }
}

void CsmaCaMacDataHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: pp->setNetworkProtocol(string2long(value)); break;
        case FIELD_priority: pp->setPriority(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacDataHeader'", field);
    }
}

omnetpp::cValue CsmaCaMacDataHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: return pp->getNetworkProtocol();
        case FIELD_priority: return pp->getPriority();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CsmaCaMacDataHeader' as cValue -- field index out of range?", field);
    }
}

void CsmaCaMacDataHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        case FIELD_networkProtocol: pp->setNetworkProtocol(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacDataHeader'", field);
    }
}

const char *CsmaCaMacDataHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CsmaCaMacDataHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CsmaCaMacDataHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacDataHeader *pp = omnetpp::fromAnyPtr<CsmaCaMacDataHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacDataHeader'", field);
    }
}

Register_Class(CsmaCaMacTrailer)

CsmaCaMacTrailer::CsmaCaMacTrailer() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(4));

}

CsmaCaMacTrailer::CsmaCaMacTrailer(const CsmaCaMacTrailer& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

CsmaCaMacTrailer::~CsmaCaMacTrailer()
{
}

CsmaCaMacTrailer& CsmaCaMacTrailer::operator=(const CsmaCaMacTrailer& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void CsmaCaMacTrailer::copy(const CsmaCaMacTrailer& other)
{
    this->fcs = other.fcs;
    this->fcsMode = other.fcsMode;
}

void CsmaCaMacTrailer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->fcs);
    doParsimPacking(b,this->fcsMode);
}

void CsmaCaMacTrailer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->fcs);
    doParsimUnpacking(b,this->fcsMode);
}

uint32_t CsmaCaMacTrailer::getFcs() const
{
    return this->fcs;
}

void CsmaCaMacTrailer::setFcs(uint32_t fcs)
{
    handleChange();
    this->fcs = fcs;
}

FcsMode CsmaCaMacTrailer::getFcsMode() const
{
    return this->fcsMode;
}

void CsmaCaMacTrailer::setFcsMode(FcsMode fcsMode)
{
    handleChange();
    this->fcsMode = fcsMode;
}

class CsmaCaMacTrailerDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fcs,
        FIELD_fcsMode,
    };
  public:
    CsmaCaMacTrailerDescriptor();
    virtual ~CsmaCaMacTrailerDescriptor();

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

Register_ClassDescriptor(CsmaCaMacTrailerDescriptor)

CsmaCaMacTrailerDescriptor::CsmaCaMacTrailerDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CsmaCaMacTrailer)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

CsmaCaMacTrailerDescriptor::~CsmaCaMacTrailerDescriptor()
{
    delete[] propertyNames;
}

bool CsmaCaMacTrailerDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsmaCaMacTrailer *>(obj)!=nullptr;
}

const char **CsmaCaMacTrailerDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CsmaCaMacTrailerDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CsmaCaMacTrailerDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int CsmaCaMacTrailerDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fcs
        FD_ISEDITABLE,    // FIELD_fcsMode
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *CsmaCaMacTrailerDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fcs",
        "fcsMode",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int CsmaCaMacTrailerDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fcs") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fcsMode") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *CsmaCaMacTrailerDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_fcs
        "inet::FcsMode",    // FIELD_fcsMode
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **CsmaCaMacTrailerDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fcsMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CsmaCaMacTrailerDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_fcsMode:
            if (!strcmp(propertyName, "enum")) return "inet::FcsMode";
            return nullptr;
        default: return nullptr;
    }
}

int CsmaCaMacTrailerDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CsmaCaMacTrailerDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CsmaCaMacTrailer'", field);
    }
}

const char *CsmaCaMacTrailerDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CsmaCaMacTrailerDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return ulong2string(pp->getFcs());
        case FIELD_fcsMode: return enum2string(pp->getFcsMode(), "inet::FcsMode");
        default: return "";
    }
}

void CsmaCaMacTrailerDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(string2ulong(value)); break;
        case FIELD_fcsMode: pp->setFcsMode((inet::FcsMode)string2enum(value, "inet::FcsMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacTrailer'", field);
    }
}

omnetpp::cValue CsmaCaMacTrailerDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: return (omnetpp::intval_t)(pp->getFcs());
        case FIELD_fcsMode: return static_cast<int>(pp->getFcsMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CsmaCaMacTrailer' as cValue -- field index out of range?", field);
    }
}

void CsmaCaMacTrailerDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        case FIELD_fcs: pp->setFcs(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_fcsMode: pp->setFcsMode(static_cast<inet::FcsMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacTrailer'", field);
    }
}

const char *CsmaCaMacTrailerDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CsmaCaMacTrailerDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CsmaCaMacTrailerDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CsmaCaMacTrailer *pp = omnetpp::fromAnyPtr<CsmaCaMacTrailer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CsmaCaMacTrailer'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

