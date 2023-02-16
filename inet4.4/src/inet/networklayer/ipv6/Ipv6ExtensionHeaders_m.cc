//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv6/Ipv6ExtensionHeaders.msg.
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
#include "Ipv6ExtensionHeaders_m.h"

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

Register_Enum(inet::Ipv6TlvOptionTypes, (inet::Ipv6TlvOptionTypes::IPv6TLVOPTION_NOP1, inet::Ipv6TlvOptionTypes::IPv6TLVOPTION_NOPN, inet::Ipv6TlvOptionTypes::IPv6TLVOPTION_TLV_GPSR));

Register_Class(Ipv6HopByHopOptionsHeader)

Ipv6HopByHopOptionsHeader::Ipv6HopByHopOptionsHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_HOP);

}

Ipv6HopByHopOptionsHeader::Ipv6HopByHopOptionsHeader(const Ipv6HopByHopOptionsHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6HopByHopOptionsHeader::~Ipv6HopByHopOptionsHeader()
{
}

Ipv6HopByHopOptionsHeader& Ipv6HopByHopOptionsHeader::operator=(const Ipv6HopByHopOptionsHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6HopByHopOptionsHeader::copy(const Ipv6HopByHopOptionsHeader& other)
{
    this->tlvOptions = other.tlvOptions;
}

void Ipv6HopByHopOptionsHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
    doParsimPacking(b,this->tlvOptions);
}

void Ipv6HopByHopOptionsHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->tlvOptions);
}

const TlvOptions& Ipv6HopByHopOptionsHeader::getTlvOptions() const
{
    return this->tlvOptions;
}

void Ipv6HopByHopOptionsHeader::setTlvOptions(const TlvOptions& tlvOptions)
{
    this->tlvOptions = tlvOptions;
}

class Ipv6HopByHopOptionsHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tlvOptions,
    };
  public:
    Ipv6HopByHopOptionsHeaderDescriptor();
    virtual ~Ipv6HopByHopOptionsHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6HopByHopOptionsHeaderDescriptor)

Ipv6HopByHopOptionsHeaderDescriptor::Ipv6HopByHopOptionsHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6HopByHopOptionsHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6HopByHopOptionsHeaderDescriptor::~Ipv6HopByHopOptionsHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6HopByHopOptionsHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6HopByHopOptionsHeader *>(obj)!=nullptr;
}

const char **Ipv6HopByHopOptionsHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6HopByHopOptionsHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6HopByHopOptionsHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6HopByHopOptionsHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6HopByHopOptionsHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tlvOptions",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6HopByHopOptionsHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tlvOptions") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6HopByHopOptionsHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TlvOptions",    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6HopByHopOptionsHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6HopByHopOptionsHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6HopByHopOptionsHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6HopByHopOptionsHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6HopByHopOptionsHeader'", field);
    }
}

const char *Ipv6HopByHopOptionsHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6HopByHopOptionsHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return pp->getTlvOptions().str();
        default: return "";
    }
}

void Ipv6HopByHopOptionsHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6HopByHopOptionsHeader'", field);
    }
}

omnetpp::cValue Ipv6HopByHopOptionsHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6HopByHopOptionsHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6HopByHopOptionsHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6HopByHopOptionsHeader'", field);
    }
}

const char *Ipv6HopByHopOptionsHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::opp_typename(typeid(TlvOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6HopByHopOptionsHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6HopByHopOptionsHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6HopByHopOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6HopByHopOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6HopByHopOptionsHeader'", field);
    }
}

Register_Class(Ipv6RoutingHeader)

Ipv6RoutingHeader::Ipv6RoutingHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_ROUTING);
    this->setByteLength(B(8));

}

Ipv6RoutingHeader::Ipv6RoutingHeader(const Ipv6RoutingHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6RoutingHeader::~Ipv6RoutingHeader()
{
    delete [] this->address;
}

Ipv6RoutingHeader& Ipv6RoutingHeader::operator=(const Ipv6RoutingHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6RoutingHeader::copy(const Ipv6RoutingHeader& other)
{
    this->routingType = other.routingType;
    this->segmentsLeft = other.segmentsLeft;
    delete [] this->address;
    this->address = (other.address_arraysize==0) ? nullptr : new Ipv6Address[other.address_arraysize];
    address_arraysize = other.address_arraysize;
    for (size_t i = 0; i < address_arraysize; i++) {
        this->address[i] = other.address[i];
    }
}

void Ipv6RoutingHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
    doParsimPacking(b,this->routingType);
    doParsimPacking(b,this->segmentsLeft);
    b->pack(address_arraysize);
    doParsimArrayPacking(b,this->address,address_arraysize);
}

void Ipv6RoutingHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->routingType);
    doParsimUnpacking(b,this->segmentsLeft);
    delete [] this->address;
    b->unpack(address_arraysize);
    if (address_arraysize == 0) {
        this->address = nullptr;
    } else {
        this->address = new Ipv6Address[address_arraysize];
        doParsimArrayUnpacking(b,this->address,address_arraysize);
    }
}

uint8_t Ipv6RoutingHeader::getRoutingType() const
{
    return this->routingType;
}

void Ipv6RoutingHeader::setRoutingType(uint8_t routingType)
{
    this->routingType = routingType;
}

uint8_t Ipv6RoutingHeader::getSegmentsLeft() const
{
    return this->segmentsLeft;
}

void Ipv6RoutingHeader::setSegmentsLeft(uint8_t segmentsLeft)
{
    this->segmentsLeft = segmentsLeft;
}

size_t Ipv6RoutingHeader::getAddressArraySize() const
{
    return address_arraysize;
}

const Ipv6Address& Ipv6RoutingHeader::getAddress(size_t k) const
{
    if (k >= address_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)address_arraysize, (unsigned long)k);
    return this->address[k];
}

void Ipv6RoutingHeader::setAddressArraySize(size_t newSize)
{
    Ipv6Address *address2 = (newSize==0) ? nullptr : new Ipv6Address[newSize];
    size_t minSize = address_arraysize < newSize ? address_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        address2[i] = this->address[i];
    delete [] this->address;
    this->address = address2;
    address_arraysize = newSize;
}

void Ipv6RoutingHeader::setAddress(size_t k, const Ipv6Address& address)
{
    if (k >= address_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)address_arraysize, (unsigned long)k);
    this->address[k] = address;
}

void Ipv6RoutingHeader::insertAddress(size_t k, const Ipv6Address& address)
{
    if (k > address_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)address_arraysize, (unsigned long)k);
    size_t newSize = address_arraysize + 1;
    Ipv6Address *address2 = new Ipv6Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        address2[i] = this->address[i];
    address2[k] = address;
    for (i = k + 1; i < newSize; i++)
        address2[i] = this->address[i-1];
    delete [] this->address;
    this->address = address2;
    address_arraysize = newSize;
}

void Ipv6RoutingHeader::appendAddress(const Ipv6Address& address)
{
    insertAddress(address_arraysize, address);
}

void Ipv6RoutingHeader::eraseAddress(size_t k)
{
    if (k >= address_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)address_arraysize, (unsigned long)k);
    size_t newSize = address_arraysize - 1;
    Ipv6Address *address2 = (newSize == 0) ? nullptr : new Ipv6Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        address2[i] = this->address[i];
    for (i = k; i < newSize; i++)
        address2[i] = this->address[i+1];
    delete [] this->address;
    this->address = address2;
    address_arraysize = newSize;
}

class Ipv6RoutingHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_routingType,
        FIELD_segmentsLeft,
        FIELD_address,
    };
  public:
    Ipv6RoutingHeaderDescriptor();
    virtual ~Ipv6RoutingHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6RoutingHeaderDescriptor)

Ipv6RoutingHeaderDescriptor::Ipv6RoutingHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6RoutingHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6RoutingHeaderDescriptor::~Ipv6RoutingHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6RoutingHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6RoutingHeader *>(obj)!=nullptr;
}

const char **Ipv6RoutingHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6RoutingHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6RoutingHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ipv6RoutingHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routingType
        FD_ISEDITABLE,    // FIELD_segmentsLeft
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_address
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RoutingHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routingType",
        "segmentsLeft",
        "address",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6RoutingHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "routingType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "segmentsLeft") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6RoutingHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_routingType
        "uint8_t",    // FIELD_segmentsLeft
        "inet::Ipv6Address",    // FIELD_address
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RoutingHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RoutingHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6RoutingHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddressArraySize();
        default: return 0;
    }
}

void Ipv6RoutingHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address: pp->setAddressArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6RoutingHeader'", field);
    }
}

const char *Ipv6RoutingHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RoutingHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_routingType: return ulong2string(pp->getRoutingType());
        case FIELD_segmentsLeft: return ulong2string(pp->getSegmentsLeft());
        case FIELD_address: return pp->getAddress(i).str();
        default: return "";
    }
}

void Ipv6RoutingHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_routingType: pp->setRoutingType(string2ulong(value)); break;
        case FIELD_segmentsLeft: pp->setSegmentsLeft(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RoutingHeader'", field);
    }
}

omnetpp::cValue Ipv6RoutingHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_routingType: return (omnetpp::intval_t)(pp->getRoutingType());
        case FIELD_segmentsLeft: return (omnetpp::intval_t)(pp->getSegmentsLeft());
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6RoutingHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6RoutingHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_routingType: pp->setRoutingType(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_segmentsLeft: pp->setSegmentsLeft(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RoutingHeader'", field);
    }
}

const char *Ipv6RoutingHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6RoutingHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6RoutingHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RoutingHeader *pp = omnetpp::fromAnyPtr<Ipv6RoutingHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RoutingHeader'", field);
    }
}

Register_Class(Ipv6FragmentHeader)

Ipv6FragmentHeader::Ipv6FragmentHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_FRAGMENT);
    this->setByteLength(IPv6_FRAGMENT_HEADER_LENGTH);

}

Ipv6FragmentHeader::Ipv6FragmentHeader(const Ipv6FragmentHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6FragmentHeader::~Ipv6FragmentHeader()
{
}

Ipv6FragmentHeader& Ipv6FragmentHeader::operator=(const Ipv6FragmentHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6FragmentHeader::copy(const Ipv6FragmentHeader& other)
{
    this->fragmentOffset = other.fragmentOffset;
    this->reserved = other.reserved;
    this->moreFragments = other.moreFragments;
    this->identification = other.identification;
}

void Ipv6FragmentHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
    doParsimPacking(b,this->fragmentOffset);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->moreFragments);
    doParsimPacking(b,this->identification);
}

void Ipv6FragmentHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->fragmentOffset);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->moreFragments);
    doParsimUnpacking(b,this->identification);
}

uint16_t Ipv6FragmentHeader::getFragmentOffset() const
{
    return this->fragmentOffset;
}

void Ipv6FragmentHeader::setFragmentOffset(uint16_t fragmentOffset)
{
    this->fragmentOffset = fragmentOffset;
}

uint8_t Ipv6FragmentHeader::getReserved() const
{
    return this->reserved;
}

void Ipv6FragmentHeader::setReserved(uint8_t reserved)
{
    this->reserved = reserved;
}

bool Ipv6FragmentHeader::getMoreFragments() const
{
    return this->moreFragments;
}

void Ipv6FragmentHeader::setMoreFragments(bool moreFragments)
{
    this->moreFragments = moreFragments;
}

uint32_t Ipv6FragmentHeader::getIdentification() const
{
    return this->identification;
}

void Ipv6FragmentHeader::setIdentification(uint32_t identification)
{
    this->identification = identification;
}

class Ipv6FragmentHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_fragmentOffset,
        FIELD_reserved,
        FIELD_moreFragments,
        FIELD_identification,
    };
  public:
    Ipv6FragmentHeaderDescriptor();
    virtual ~Ipv6FragmentHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6FragmentHeaderDescriptor)

Ipv6FragmentHeaderDescriptor::Ipv6FragmentHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6FragmentHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6FragmentHeaderDescriptor::~Ipv6FragmentHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6FragmentHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6FragmentHeader *>(obj)!=nullptr;
}

const char **Ipv6FragmentHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6FragmentHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6FragmentHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ipv6FragmentHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_fragmentOffset
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_moreFragments
        FD_ISEDITABLE,    // FIELD_identification
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6FragmentHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "fragmentOffset",
        "reserved",
        "moreFragments",
        "identification",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ipv6FragmentHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "fragmentOffset") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "moreFragments") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "identification") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6FragmentHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_fragmentOffset
        "uint8_t",    // FIELD_reserved
        "bool",    // FIELD_moreFragments
        "uint32_t",    // FIELD_identification
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6FragmentHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6FragmentHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6FragmentHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6FragmentHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6FragmentHeader'", field);
    }
}

const char *Ipv6FragmentHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6FragmentHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentOffset: return ulong2string(pp->getFragmentOffset());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_moreFragments: return bool2string(pp->getMoreFragments());
        case FIELD_identification: return ulong2string(pp->getIdentification());
        default: return "";
    }
}

void Ipv6FragmentHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentOffset: pp->setFragmentOffset(string2ulong(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_moreFragments: pp->setMoreFragments(string2bool(value)); break;
        case FIELD_identification: pp->setIdentification(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6FragmentHeader'", field);
    }
}

omnetpp::cValue Ipv6FragmentHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentOffset: return (omnetpp::intval_t)(pp->getFragmentOffset());
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_moreFragments: return pp->getMoreFragments();
        case FIELD_identification: return (omnetpp::intval_t)(pp->getIdentification());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6FragmentHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6FragmentHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        case FIELD_fragmentOffset: pp->setFragmentOffset(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_moreFragments: pp->setMoreFragments(value.boolValue()); break;
        case FIELD_identification: pp->setIdentification(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6FragmentHeader'", field);
    }
}

const char *Ipv6FragmentHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6FragmentHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6FragmentHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6FragmentHeader *pp = omnetpp::fromAnyPtr<Ipv6FragmentHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6FragmentHeader'", field);
    }
}

Register_Class(Ipv6DestinationOptionsHeader)

Ipv6DestinationOptionsHeader::Ipv6DestinationOptionsHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_DEST);
    this->setByteLength(B(8));

}

Ipv6DestinationOptionsHeader::Ipv6DestinationOptionsHeader(const Ipv6DestinationOptionsHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6DestinationOptionsHeader::~Ipv6DestinationOptionsHeader()
{
}

Ipv6DestinationOptionsHeader& Ipv6DestinationOptionsHeader::operator=(const Ipv6DestinationOptionsHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6DestinationOptionsHeader::copy(const Ipv6DestinationOptionsHeader& other)
{
    this->tlvOptions = other.tlvOptions;
}

void Ipv6DestinationOptionsHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
    doParsimPacking(b,this->tlvOptions);
}

void Ipv6DestinationOptionsHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->tlvOptions);
}

const TlvOptions& Ipv6DestinationOptionsHeader::getTlvOptions() const
{
    return this->tlvOptions;
}

void Ipv6DestinationOptionsHeader::setTlvOptions(const TlvOptions& tlvOptions)
{
    this->tlvOptions = tlvOptions;
}

class Ipv6DestinationOptionsHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tlvOptions,
    };
  public:
    Ipv6DestinationOptionsHeaderDescriptor();
    virtual ~Ipv6DestinationOptionsHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6DestinationOptionsHeaderDescriptor)

Ipv6DestinationOptionsHeaderDescriptor::Ipv6DestinationOptionsHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6DestinationOptionsHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6DestinationOptionsHeaderDescriptor::~Ipv6DestinationOptionsHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6DestinationOptionsHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6DestinationOptionsHeader *>(obj)!=nullptr;
}

const char **Ipv6DestinationOptionsHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6DestinationOptionsHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6DestinationOptionsHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6DestinationOptionsHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6DestinationOptionsHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tlvOptions",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6DestinationOptionsHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tlvOptions") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6DestinationOptionsHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TlvOptions",    // FIELD_tlvOptions
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6DestinationOptionsHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6DestinationOptionsHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6DestinationOptionsHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6DestinationOptionsHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6DestinationOptionsHeader'", field);
    }
}

const char *Ipv6DestinationOptionsHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6DestinationOptionsHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return pp->getTlvOptions().str();
        default: return "";
    }
}

void Ipv6DestinationOptionsHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6DestinationOptionsHeader'", field);
    }
}

omnetpp::cValue Ipv6DestinationOptionsHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6DestinationOptionsHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6DestinationOptionsHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6DestinationOptionsHeader'", field);
    }
}

const char *Ipv6DestinationOptionsHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::opp_typename(typeid(TlvOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6DestinationOptionsHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOptions: return omnetpp::toAnyPtr(&pp->getTlvOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6DestinationOptionsHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6DestinationOptionsHeader *pp = omnetpp::fromAnyPtr<Ipv6DestinationOptionsHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6DestinationOptionsHeader'", field);
    }
}

Register_Class(Ipv6AuthenticationHeader)

Ipv6AuthenticationHeader::Ipv6AuthenticationHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_AUTH);
    this->setByteLength(B(8));
}

Ipv6AuthenticationHeader::Ipv6AuthenticationHeader(const Ipv6AuthenticationHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6AuthenticationHeader::~Ipv6AuthenticationHeader()
{
}

Ipv6AuthenticationHeader& Ipv6AuthenticationHeader::operator=(const Ipv6AuthenticationHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6AuthenticationHeader::copy(const Ipv6AuthenticationHeader& other)
{
}

void Ipv6AuthenticationHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
}

void Ipv6AuthenticationHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
}

class Ipv6AuthenticationHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6AuthenticationHeaderDescriptor();
    virtual ~Ipv6AuthenticationHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6AuthenticationHeaderDescriptor)

Ipv6AuthenticationHeaderDescriptor::Ipv6AuthenticationHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6AuthenticationHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6AuthenticationHeaderDescriptor::~Ipv6AuthenticationHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6AuthenticationHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6AuthenticationHeader *>(obj)!=nullptr;
}

const char **Ipv6AuthenticationHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6AuthenticationHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6AuthenticationHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6AuthenticationHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6AuthenticationHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6AuthenticationHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6AuthenticationHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6AuthenticationHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6AuthenticationHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6AuthenticationHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6AuthenticationHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6AuthenticationHeader'", field);
    }
}

const char *Ipv6AuthenticationHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6AuthenticationHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6AuthenticationHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6AuthenticationHeader'", field);
    }
}

omnetpp::cValue Ipv6AuthenticationHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6AuthenticationHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6AuthenticationHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6AuthenticationHeader'", field);
    }
}

const char *Ipv6AuthenticationHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6AuthenticationHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6AuthenticationHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6AuthenticationHeader *pp = omnetpp::fromAnyPtr<Ipv6AuthenticationHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6AuthenticationHeader'", field);
    }
}

Register_Class(Ipv6EncapsulatingSecurityPayloadHeader)

Ipv6EncapsulatingSecurityPayloadHeader::Ipv6EncapsulatingSecurityPayloadHeader() : ::inet::Ipv6ExtensionHeader()
{
    this->setExtensionType(IP_PROT_IPv6EXT_ESP);
    this->setByteLength(B(8));
}

Ipv6EncapsulatingSecurityPayloadHeader::Ipv6EncapsulatingSecurityPayloadHeader(const Ipv6EncapsulatingSecurityPayloadHeader& other) : ::inet::Ipv6ExtensionHeader(other)
{
    copy(other);
}

Ipv6EncapsulatingSecurityPayloadHeader::~Ipv6EncapsulatingSecurityPayloadHeader()
{
}

Ipv6EncapsulatingSecurityPayloadHeader& Ipv6EncapsulatingSecurityPayloadHeader::operator=(const Ipv6EncapsulatingSecurityPayloadHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtensionHeader::operator=(other);
    copy(other);
    return *this;
}

void Ipv6EncapsulatingSecurityPayloadHeader::copy(const Ipv6EncapsulatingSecurityPayloadHeader& other)
{
}

void Ipv6EncapsulatingSecurityPayloadHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtensionHeader::parsimPack(b);
}

void Ipv6EncapsulatingSecurityPayloadHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtensionHeader::parsimUnpack(b);
}

class Ipv6EncapsulatingSecurityPayloadHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6EncapsulatingSecurityPayloadHeaderDescriptor();
    virtual ~Ipv6EncapsulatingSecurityPayloadHeaderDescriptor();

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

Register_ClassDescriptor(Ipv6EncapsulatingSecurityPayloadHeaderDescriptor)

Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::Ipv6EncapsulatingSecurityPayloadHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6EncapsulatingSecurityPayloadHeader)), "inet::Ipv6ExtensionHeader")
{
    propertyNames = nullptr;
}

Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::~Ipv6EncapsulatingSecurityPayloadHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6EncapsulatingSecurityPayloadHeader *>(obj)!=nullptr;
}

const char **Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6EncapsulatingSecurityPayloadHeader'", field);
    }
}

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6EncapsulatingSecurityPayloadHeader'", field);
    }
}

omnetpp::cValue Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6EncapsulatingSecurityPayloadHeader' as cValue -- field index out of range?", field);
    }
}

void Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6EncapsulatingSecurityPayloadHeader'", field);
    }
}

const char *Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6EncapsulatingSecurityPayloadHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6EncapsulatingSecurityPayloadHeader *pp = omnetpp::fromAnyPtr<Ipv6EncapsulatingSecurityPayloadHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6EncapsulatingSecurityPayloadHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

