//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv6/Ipv6Header.msg.
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
#include "Ipv6Header_m.h"

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

Register_Class(Ipv6ExtensionHeader)

Ipv6ExtensionHeader::Ipv6ExtensionHeader() : ::omnetpp::cObject()
{
}

Ipv6ExtensionHeader::Ipv6ExtensionHeader(const Ipv6ExtensionHeader& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6ExtensionHeader::~Ipv6ExtensionHeader()
{
}

Ipv6ExtensionHeader& Ipv6ExtensionHeader::operator=(const Ipv6ExtensionHeader& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6ExtensionHeader::copy(const Ipv6ExtensionHeader& other)
{
    this->extensionType = other.extensionType;
    this->byteLength = other.byteLength;
}

void Ipv6ExtensionHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->extensionType);
    doParsimPacking(b,this->byteLength);
}

void Ipv6ExtensionHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->extensionType);
    doParsimUnpacking(b,this->byteLength);
}

uint8_t Ipv6ExtensionHeader::getExtensionType() const
{
    return this->extensionType;
}

void Ipv6ExtensionHeader::setExtensionType(uint8_t extensionType)
{
    this->extensionType = extensionType;
}

B Ipv6ExtensionHeader::getByteLength() const
{
    return this->byteLength;
}

void Ipv6ExtensionHeader::setByteLength(B byteLength)
{
    this->byteLength = byteLength;
}

class Ipv6ExtensionHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_extensionType,
        FIELD_byteLength,
    };
  public:
    Ipv6ExtensionHeaderDescriptor();
    virtual ~Ipv6ExtensionHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6ExtensionHeaderDescriptor)

Ipv6ExtensionHeaderDescriptor::Ipv6ExtensionHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6ExtensionHeader)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv6ExtensionHeaderDescriptor::~Ipv6ExtensionHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6ExtensionHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6ExtensionHeader *>(obj)!=nullptr;
}

const char **Ipv6ExtensionHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6ExtensionHeaderDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6ExtensionHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv6ExtensionHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_extensionType
        FD_ISEDITABLE,    // FIELD_byteLength
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6ExtensionHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "extensionType",
        "byteLength",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6ExtensionHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "extensionType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "byteLength") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6ExtensionHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_extensionType
        "inet::B",    // FIELD_byteLength
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6ExtensionHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6ExtensionHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6ExtensionHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6ExtensionHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6ExtensionHeader'", field);
    }
}

const char *Ipv6ExtensionHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6ExtensionHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        case FIELD_extensionType: return ulong2string(pp->getExtensionType());
        case FIELD_byteLength: return unit2string(pp->getByteLength());
        default: return "";
    }
}

void Ipv6ExtensionHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        case FIELD_extensionType: pp->setExtensionType(string2ulong(value)); break;
        case FIELD_byteLength: pp->setByteLength(B(string2long(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtensionHeader'", field);
    }
}

omnetpp::cValue Ipv6ExtensionHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        case FIELD_extensionType: return (omnetpp::intval_t)(pp->getExtensionType());
        case FIELD_byteLength: return cValue(pp->getByteLength().get(),"B");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6ExtensionHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6ExtensionHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        case FIELD_extensionType: pp->setExtensionType(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_byteLength: pp->setByteLength(B(value.intValueInUnit("B"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtensionHeader'", field);
    }
}

const char *Ipv6ExtensionHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6ExtensionHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6ExtensionHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtensionHeader *pp = omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtensionHeader'", field);
    }
}

Register_Class(Ipv6Header)

Ipv6Header::Ipv6Header() : ::inet::NetworkHeaderBase()
{
    this->setChunkLength(IPv6_HEADER_BYTES);

}

Ipv6Header::Ipv6Header(const Ipv6Header& other) : ::inet::NetworkHeaderBase(other)
{
    copy(other);
}

Ipv6Header::~Ipv6Header()
{
    for (size_t i = 0; i < extensionHeader_arraysize; i++)
        delete this->extensionHeader[i];
    delete [] this->extensionHeader;
}

Ipv6Header& Ipv6Header::operator=(const Ipv6Header& other)
{
    if (this == &other) return *this;
    ::inet::NetworkHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6Header::copy(const Ipv6Header& other)
{
    this->version = other.version;
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->payloadLength = other.payloadLength;
    this->trafficClass = other.trafficClass;
    this->flowLabel = other.flowLabel;
    this->hopLimit = other.hopLimit;
    this->protocolId = other.protocolId;
    for (size_t i = 0; i < extensionHeader_arraysize; i++)
        delete this->extensionHeader[i];
    delete [] this->extensionHeader;
    this->extensionHeader = (other.extensionHeader_arraysize==0) ? nullptr : new Ipv6ExtensionHeader *[other.extensionHeader_arraysize];
    extensionHeader_arraysize = other.extensionHeader_arraysize;
    for (size_t i = 0; i < extensionHeader_arraysize; i++) {
        this->extensionHeader[i] = other.extensionHeader[i];
        if (this->extensionHeader[i] != nullptr) {
            this->extensionHeader[i] = this->extensionHeader[i]->dup();
        }
    }
}

void Ipv6Header::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NetworkHeaderBase::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->payloadLength);
    doParsimPacking(b,this->trafficClass);
    doParsimPacking(b,this->flowLabel);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->protocolId);
    b->pack(extensionHeader_arraysize);
    doParsimArrayPacking(b,this->extensionHeader,extensionHeader_arraysize);
}

void Ipv6Header::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NetworkHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->payloadLength);
    doParsimUnpacking(b,this->trafficClass);
    doParsimUnpacking(b,this->flowLabel);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->protocolId);
    delete [] this->extensionHeader;
    b->unpack(extensionHeader_arraysize);
    if (extensionHeader_arraysize == 0) {
        this->extensionHeader = nullptr;
    } else {
        this->extensionHeader = new Ipv6ExtensionHeader *[extensionHeader_arraysize];
        doParsimArrayUnpacking(b,this->extensionHeader,extensionHeader_arraysize);
    }
}

uint8_t Ipv6Header::getVersion() const
{
    return this->version;
}

void Ipv6Header::setVersion(uint8_t version)
{
    handleChange();
    this->version = version;
}

const Ipv6Address& Ipv6Header::getSrcAddress() const
{
    return this->srcAddress;
}

void Ipv6Header::setSrcAddress(const Ipv6Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

const Ipv6Address& Ipv6Header::getDestAddress() const
{
    return this->destAddress;
}

void Ipv6Header::setDestAddress(const Ipv6Address& destAddress)
{
    handleChange();
    this->destAddress = destAddress;
}

B Ipv6Header::getPayloadLength() const
{
    return this->payloadLength;
}

void Ipv6Header::setPayloadLength(B payloadLength)
{
    handleChange();
    this->payloadLength = payloadLength;
}

short Ipv6Header::getTrafficClass() const
{
    return this->trafficClass;
}

void Ipv6Header::setTrafficClass(short trafficClass)
{
    handleChange();
    this->trafficClass = trafficClass;
}

unsigned int Ipv6Header::getFlowLabel() const
{
    return this->flowLabel;
}

void Ipv6Header::setFlowLabel(unsigned int flowLabel)
{
    handleChange();
    this->flowLabel = flowLabel;
}

short Ipv6Header::getHopLimit() const
{
    return this->hopLimit;
}

void Ipv6Header::setHopLimit(short hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

IpProtocolId Ipv6Header::getProtocolId() const
{
    return this->protocolId;
}

void Ipv6Header::setProtocolId(IpProtocolId protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

size_t Ipv6Header::getExtensionHeaderArraySize() const
{
    return extensionHeader_arraysize;
}

const Ipv6ExtensionHeader * Ipv6Header::getExtensionHeader(size_t k) const
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    return this->extensionHeader[k];
}

void Ipv6Header::setExtensionHeaderArraySize(size_t newSize)
{
    handleChange();
    Ipv6ExtensionHeader * *extensionHeader2 = (newSize==0) ? nullptr : new Ipv6ExtensionHeader *[newSize];
    size_t minSize = extensionHeader_arraysize < newSize ? extensionHeader_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        extensionHeader2[i] = this->extensionHeader[i];
    for (size_t i = minSize; i < newSize; i++)
        extensionHeader2[i] = nullptr;
    for (size_t i = newSize; i < extensionHeader_arraysize; i++)
        delete extensionHeader[i];
    delete [] this->extensionHeader;
    this->extensionHeader = extensionHeader2;
    extensionHeader_arraysize = newSize;
}

void Ipv6Header::setExtensionHeader(size_t k, Ipv6ExtensionHeader * extensionHeader)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    handleChange();
    if (this->extensionHeader[k] != nullptr) throw omnetpp::cRuntimeError("setExtensionHeader(): a value is already set, remove it first with removeExtensionHeader()");
    this->extensionHeader[k] = extensionHeader;
    if (this->extensionHeader[k] != nullptr && this->extensionHeader[k]->isOwnedObject()) take((cOwnedObject*)this->extensionHeader[k]);
}

Ipv6ExtensionHeader * Ipv6Header::removeExtensionHeader(size_t k)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    handleChange();
    Ipv6ExtensionHeader * retval = this->extensionHeader[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->extensionHeader[k] = nullptr;
    return retval;
}

void Ipv6Header::insertExtensionHeader(size_t k, Ipv6ExtensionHeader * extensionHeader)
{
    if (k > extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = extensionHeader_arraysize + 1;
    Ipv6ExtensionHeader * *extensionHeader2 = new Ipv6ExtensionHeader *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        extensionHeader2[i] = this->extensionHeader[i];
    extensionHeader2[k] = extensionHeader;
    if (extensionHeader2[k] != nullptr && extensionHeader2[k]->isOwnedObject()) take((cOwnedObject*)extensionHeader2[k]);
    for (i = k + 1; i < newSize; i++)
        extensionHeader2[i] = this->extensionHeader[i-1];
    delete [] this->extensionHeader;
    this->extensionHeader = extensionHeader2;
    extensionHeader_arraysize = newSize;
}

void Ipv6Header::appendExtensionHeader(Ipv6ExtensionHeader * extensionHeader)
{
    insertExtensionHeader(extensionHeader_arraysize, extensionHeader);
}

void Ipv6Header::eraseExtensionHeader(size_t k)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = extensionHeader_arraysize - 1;
    Ipv6ExtensionHeader * *extensionHeader2 = (newSize == 0) ? nullptr : new Ipv6ExtensionHeader *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        extensionHeader2[i] = this->extensionHeader[i];
    for (i = k; i < newSize; i++)
        extensionHeader2[i] = this->extensionHeader[i+1];
    if (this->extensionHeader[k] != nullptr && this->extensionHeader[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->extensionHeader[k]); else delete this->extensionHeader[k];
    delete [] this->extensionHeader;
    this->extensionHeader = extensionHeader2;
    extensionHeader_arraysize = newSize;
}

class Ipv6HeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_srcAddress,
        FIELD_destAddress,
        FIELD_payloadLength,
        FIELD_trafficClass,
        FIELD_flowLabel,
        FIELD_hopLimit,
        FIELD_protocolId,
        FIELD_extensionHeader,
    };
  public:
    Ipv6HeaderDescriptor();
    virtual ~Ipv6HeaderDescriptor();

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

Register_ClassDescriptor(Ipv6HeaderDescriptor)

Ipv6HeaderDescriptor::Ipv6HeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6Header)), "inet::NetworkHeaderBase")
{
    propertyNames = nullptr;
}

Ipv6HeaderDescriptor::~Ipv6HeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6HeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6Header *>(obj)!=nullptr;
}

const char **Ipv6HeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6HeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6HeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ipv6HeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        0,    // FIELD_srcAddress
        0,    // FIELD_destAddress
        FD_ISEDITABLE,    // FIELD_payloadLength
        FD_ISEDITABLE,    // FIELD_trafficClass
        FD_ISEDITABLE,    // FIELD_flowLabel
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_protocolId
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_extensionHeader
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6HeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "srcAddress",
        "destAddress",
        "payloadLength",
        "trafficClass",
        "flowLabel",
        "hopLimit",
        "protocolId",
        "extensionHeader",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ipv6HeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "payloadLength") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "trafficClass") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "flowLabel") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "hopLimit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "extensionHeader") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6HeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_version
        "inet::Ipv6Address",    // FIELD_srcAddress
        "inet::Ipv6Address",    // FIELD_destAddress
        "inet::B",    // FIELD_payloadLength
        "short",    // FIELD_trafficClass
        "unsigned int",    // FIELD_flowLabel
        "short",    // FIELD_hopLimit
        "inet::IpProtocolId",    // FIELD_protocolId
        "inet::Ipv6ExtensionHeader",    // FIELD_extensionHeader
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6HeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_extensionHeader: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv6HeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId:
            if (!strcmp(propertyName, "enum")) return "inet::IpProtocolId";
            return nullptr;
        case FIELD_extensionHeader:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv6HeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: return pp->getExtensionHeaderArraySize();
        default: return 0;
    }
}

void Ipv6HeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: pp->setExtensionHeaderArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6Header'", field);
    }
}

const char *Ipv6HeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: { const Ipv6ExtensionHeader * value = pp->getExtensionHeader(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ipv6HeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: return ulong2string(pp->getVersion());
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_destAddress: return pp->getDestAddress().str();
        case FIELD_payloadLength: return unit2string(pp->getPayloadLength());
        case FIELD_trafficClass: return long2string(pp->getTrafficClass());
        case FIELD_flowLabel: return ulong2string(pp->getFlowLabel());
        case FIELD_hopLimit: return long2string(pp->getHopLimit());
        case FIELD_protocolId: return enum2string(pp->getProtocolId(), "inet::IpProtocolId");
        case FIELD_extensionHeader: { auto obj = pp->getExtensionHeader(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void Ipv6HeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2ulong(value)); break;
        case FIELD_payloadLength: pp->setPayloadLength(B(string2long(value))); break;
        case FIELD_trafficClass: pp->setTrafficClass(string2long(value)); break;
        case FIELD_flowLabel: pp->setFlowLabel(string2ulong(value)); break;
        case FIELD_hopLimit: pp->setHopLimit(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId((inet::IpProtocolId)string2enum(value, "inet::IpProtocolId")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Header'", field);
    }
}

omnetpp::cValue Ipv6HeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: return (omnetpp::intval_t)(pp->getVersion());
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_payloadLength: return cValue(pp->getPayloadLength().get(),"B");
        case FIELD_trafficClass: return pp->getTrafficClass();
        case FIELD_flowLabel: return (omnetpp::intval_t)(pp->getFlowLabel());
        case FIELD_hopLimit: return pp->getHopLimit();
        case FIELD_protocolId: return static_cast<int>(pp->getProtocolId());
        case FIELD_extensionHeader: return omnetpp::toAnyPtr(pp->getExtensionHeader(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6Header' as cValue -- field index out of range?", field);
    }
}

void Ipv6HeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_payloadLength: pp->setPayloadLength(B(value.intValueInUnit("B"))); break;
        case FIELD_trafficClass: pp->setTrafficClass(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_flowLabel: pp->setFlowLabel(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_hopLimit: pp->setHopLimit(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(static_cast<inet::IpProtocolId>(value.intValue())); break;
        case FIELD_extensionHeader: pp->setExtensionHeader(i,omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Header'", field);
    }
}

const char *Ipv6HeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_extensionHeader: return omnetpp::opp_typename(typeid(Ipv6ExtensionHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6HeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_extensionHeader: return omnetpp::toAnyPtr(pp->getExtensionHeader(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6HeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Header *pp = omnetpp::fromAnyPtr<Ipv6Header>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: pp->setExtensionHeader(i,omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Header'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

