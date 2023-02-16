//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/icmpv6/Ipv6NdMessage.msg.
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
#include "Ipv6NdMessage_m.h"

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

Register_Enum(inet::Ipv6NdOptionTypes, (inet::Ipv6NdOptionTypes::IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION, inet::Ipv6NdOptionTypes::IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION, inet::Ipv6NdOptionTypes::IPv6ND_PREFIX_INFORMATION, inet::Ipv6NdOptionTypes::IPv6ND_REDIRECTED_HEADER, inet::Ipv6NdOptionTypes::IPv6ND_MTU, inet::Ipv6NdOptionTypes::IPv6ND_ADVERTISEMENT_INTERVAL, inet::Ipv6NdOptionTypes::IPv6ND_HOME_AGENT_INFORMATION_OPTION));

Register_Class(Ipv6NdOption)

Ipv6NdOption::Ipv6NdOption() : ::omnetpp::cObject()
{
}

Ipv6NdOption::Ipv6NdOption(const Ipv6NdOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdOption::~Ipv6NdOption()
{
    delete [] this->paddingBytes;
}

Ipv6NdOption& Ipv6NdOption::operator=(const Ipv6NdOption& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdOption::copy(const Ipv6NdOption& other)
{
    this->type = other.type;
    this->optionLength = other.optionLength;
    delete [] this->paddingBytes;
    this->paddingBytes = (other.paddingBytes_arraysize==0) ? nullptr : new char[other.paddingBytes_arraysize];
    paddingBytes_arraysize = other.paddingBytes_arraysize;
    for (size_t i = 0; i < paddingBytes_arraysize; i++) {
        this->paddingBytes[i] = other.paddingBytes[i];
    }
}

void Ipv6NdOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->optionLength);
    b->pack(paddingBytes_arraysize);
    doParsimArrayPacking(b,this->paddingBytes,paddingBytes_arraysize);
}

void Ipv6NdOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->optionLength);
    delete [] this->paddingBytes;
    b->unpack(paddingBytes_arraysize);
    if (paddingBytes_arraysize == 0) {
        this->paddingBytes = nullptr;
    } else {
        this->paddingBytes = new char[paddingBytes_arraysize];
        doParsimArrayUnpacking(b,this->paddingBytes,paddingBytes_arraysize);
    }
}

Ipv6NdOptionTypes Ipv6NdOption::getType() const
{
    return this->type;
}

void Ipv6NdOption::setType(Ipv6NdOptionTypes type)
{
    this->type = type;
}

short Ipv6NdOption::getOptionLength() const
{
    return this->optionLength;
}

void Ipv6NdOption::setOptionLength(short optionLength)
{
    this->optionLength = optionLength;
}

size_t Ipv6NdOption::getPaddingBytesArraySize() const
{
    return paddingBytes_arraysize;
}

char Ipv6NdOption::getPaddingBytes(size_t k) const
{
    if (k >= paddingBytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)paddingBytes_arraysize, (unsigned long)k);
    return this->paddingBytes[k];
}

void Ipv6NdOption::setPaddingBytesArraySize(size_t newSize)
{
    char *paddingBytes2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = paddingBytes_arraysize < newSize ? paddingBytes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        paddingBytes2[i] = this->paddingBytes[i];
    for (size_t i = minSize; i < newSize; i++)
        paddingBytes2[i] = 0;
    delete [] this->paddingBytes;
    this->paddingBytes = paddingBytes2;
    paddingBytes_arraysize = newSize;
}

void Ipv6NdOption::setPaddingBytes(size_t k, char paddingBytes)
{
    if (k >= paddingBytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)paddingBytes_arraysize, (unsigned long)k);
    this->paddingBytes[k] = paddingBytes;
}

void Ipv6NdOption::insertPaddingBytes(size_t k, char paddingBytes)
{
    if (k > paddingBytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)paddingBytes_arraysize, (unsigned long)k);
    size_t newSize = paddingBytes_arraysize + 1;
    char *paddingBytes2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        paddingBytes2[i] = this->paddingBytes[i];
    paddingBytes2[k] = paddingBytes;
    for (i = k + 1; i < newSize; i++)
        paddingBytes2[i] = this->paddingBytes[i-1];
    delete [] this->paddingBytes;
    this->paddingBytes = paddingBytes2;
    paddingBytes_arraysize = newSize;
}

void Ipv6NdOption::appendPaddingBytes(char paddingBytes)
{
    insertPaddingBytes(paddingBytes_arraysize, paddingBytes);
}

void Ipv6NdOption::erasePaddingBytes(size_t k)
{
    if (k >= paddingBytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)paddingBytes_arraysize, (unsigned long)k);
    size_t newSize = paddingBytes_arraysize - 1;
    char *paddingBytes2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        paddingBytes2[i] = this->paddingBytes[i];
    for (i = k; i < newSize; i++)
        paddingBytes2[i] = this->paddingBytes[i+1];
    delete [] this->paddingBytes;
    this->paddingBytes = paddingBytes2;
    paddingBytes_arraysize = newSize;
}

class Ipv6NdOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_optionLength,
        FIELD_paddingBytes,
    };
  public:
    Ipv6NdOptionDescriptor();
    virtual ~Ipv6NdOptionDescriptor();

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

Register_ClassDescriptor(Ipv6NdOptionDescriptor)

Ipv6NdOptionDescriptor::Ipv6NdOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdOption)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv6NdOptionDescriptor::~Ipv6NdOptionDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdOption *>(obj)!=nullptr;
}

const char **Ipv6NdOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdOptionDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ipv6NdOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_optionLength
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_paddingBytes
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "optionLength",
        "paddingBytes",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6NdOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "optionLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "paddingBytes") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6NdOptionTypes",    // FIELD_type
        "short",    // FIELD_optionLength
        "char",    // FIELD_paddingBytes
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "inet::Ipv6NdOptionTypes";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv6NdOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_paddingBytes: return pp->getPaddingBytesArraySize();
        default: return 0;
    }
}

void Ipv6NdOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_paddingBytes: pp->setPaddingBytesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdOption'", field);
    }
}

const char *Ipv6NdOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_type: return enum2string(pp->getType(), "inet::Ipv6NdOptionTypes");
        case FIELD_optionLength: return long2string(pp->getOptionLength());
        case FIELD_paddingBytes: return long2string(pp->getPaddingBytes(i));
        default: return "";
    }
}

void Ipv6NdOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_optionLength: pp->setOptionLength(string2long(value)); break;
        case FIELD_paddingBytes: pp->setPaddingBytes(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOption'", field);
    }
}

omnetpp::cValue Ipv6NdOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_optionLength: return pp->getOptionLength();
        case FIELD_paddingBytes: return pp->getPaddingBytes(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdOption' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        case FIELD_optionLength: pp->setOptionLength(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_paddingBytes: pp->setPaddingBytes(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOption'", field);
    }
}

const char *Ipv6NdOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOption *pp = omnetpp::fromAnyPtr<Ipv6NdOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOption'", field);
    }
}

Register_Class(Ipv6NdSourceTargetLinkLayerAddress)

Ipv6NdSourceTargetLinkLayerAddress::Ipv6NdSourceTargetLinkLayerAddress() : ::inet::Ipv6NdOption()
{
    this->setOptionLength(1);

}

Ipv6NdSourceTargetLinkLayerAddress::Ipv6NdSourceTargetLinkLayerAddress(const Ipv6NdSourceTargetLinkLayerAddress& other) : ::inet::Ipv6NdOption(other)
{
    copy(other);
}

Ipv6NdSourceTargetLinkLayerAddress::~Ipv6NdSourceTargetLinkLayerAddress()
{
}

Ipv6NdSourceTargetLinkLayerAddress& Ipv6NdSourceTargetLinkLayerAddress::operator=(const Ipv6NdSourceTargetLinkLayerAddress& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdOption::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdSourceTargetLinkLayerAddress::copy(const Ipv6NdSourceTargetLinkLayerAddress& other)
{
    this->linkLayerAddress = other.linkLayerAddress;
}

void Ipv6NdSourceTargetLinkLayerAddress::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdOption::parsimPack(b);
    doParsimPacking(b,this->linkLayerAddress);
}

void Ipv6NdSourceTargetLinkLayerAddress::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdOption::parsimUnpack(b);
    doParsimUnpacking(b,this->linkLayerAddress);
}

const MacAddress& Ipv6NdSourceTargetLinkLayerAddress::getLinkLayerAddress() const
{
    return this->linkLayerAddress;
}

void Ipv6NdSourceTargetLinkLayerAddress::setLinkLayerAddress(const MacAddress& linkLayerAddress)
{
    this->linkLayerAddress = linkLayerAddress;
}

class Ipv6NdSourceTargetLinkLayerAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_linkLayerAddress,
    };
  public:
    Ipv6NdSourceTargetLinkLayerAddressDescriptor();
    virtual ~Ipv6NdSourceTargetLinkLayerAddressDescriptor();

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

Register_ClassDescriptor(Ipv6NdSourceTargetLinkLayerAddressDescriptor)

Ipv6NdSourceTargetLinkLayerAddressDescriptor::Ipv6NdSourceTargetLinkLayerAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdSourceTargetLinkLayerAddress)), "inet::Ipv6NdOption")
{
    propertyNames = nullptr;
}

Ipv6NdSourceTargetLinkLayerAddressDescriptor::~Ipv6NdSourceTargetLinkLayerAddressDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdSourceTargetLinkLayerAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdSourceTargetLinkLayerAddress *>(obj)!=nullptr;
}

const char **Ipv6NdSourceTargetLinkLayerAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_linkLayerAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "linkLayerAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6NdSourceTargetLinkLayerAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "linkLayerAddress") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_linkLayerAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdSourceTargetLinkLayerAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdSourceTargetLinkLayerAddress'", field);
    }
}

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        case FIELD_linkLayerAddress: return pp->getLinkLayerAddress().str();
        default: return "";
    }
}

void Ipv6NdSourceTargetLinkLayerAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceTargetLinkLayerAddress'", field);
    }
}

omnetpp::cValue Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        case FIELD_linkLayerAddress: return omnetpp::toAnyPtr(&pp->getLinkLayerAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdSourceTargetLinkLayerAddress' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdSourceTargetLinkLayerAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceTargetLinkLayerAddress'", field);
    }
}

const char *Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdSourceTargetLinkLayerAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        case FIELD_linkLayerAddress: return omnetpp::toAnyPtr(&pp->getLinkLayerAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdSourceTargetLinkLayerAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceTargetLinkLayerAddress'", field);
    }
}

Register_Class(Ipv6NdSourceLinkLayerAddress)

Ipv6NdSourceLinkLayerAddress::Ipv6NdSourceLinkLayerAddress() : ::inet::Ipv6NdSourceTargetLinkLayerAddress()
{
    this->setType(IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION);
}

Ipv6NdSourceLinkLayerAddress::Ipv6NdSourceLinkLayerAddress(const Ipv6NdSourceLinkLayerAddress& other) : ::inet::Ipv6NdSourceTargetLinkLayerAddress(other)
{
    copy(other);
}

Ipv6NdSourceLinkLayerAddress::~Ipv6NdSourceLinkLayerAddress()
{
}

Ipv6NdSourceLinkLayerAddress& Ipv6NdSourceLinkLayerAddress::operator=(const Ipv6NdSourceLinkLayerAddress& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdSourceLinkLayerAddress::copy(const Ipv6NdSourceLinkLayerAddress& other)
{
}

void Ipv6NdSourceLinkLayerAddress::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::parsimPack(b);
}

void Ipv6NdSourceLinkLayerAddress::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::parsimUnpack(b);
}

class Ipv6NdSourceLinkLayerAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6NdSourceLinkLayerAddressDescriptor();
    virtual ~Ipv6NdSourceLinkLayerAddressDescriptor();

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

Register_ClassDescriptor(Ipv6NdSourceLinkLayerAddressDescriptor)

Ipv6NdSourceLinkLayerAddressDescriptor::Ipv6NdSourceLinkLayerAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdSourceLinkLayerAddress)), "inet::Ipv6NdSourceTargetLinkLayerAddress")
{
    propertyNames = nullptr;
}

Ipv6NdSourceLinkLayerAddressDescriptor::~Ipv6NdSourceLinkLayerAddressDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdSourceLinkLayerAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdSourceLinkLayerAddress *>(obj)!=nullptr;
}

const char **Ipv6NdSourceLinkLayerAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdSourceLinkLayerAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6NdSourceLinkLayerAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6NdSourceLinkLayerAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6NdSourceLinkLayerAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdSourceLinkLayerAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdSourceLinkLayerAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdSourceLinkLayerAddress'", field);
    }
}

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdSourceLinkLayerAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6NdSourceLinkLayerAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceLinkLayerAddress'", field);
    }
}

omnetpp::cValue Ipv6NdSourceLinkLayerAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdSourceLinkLayerAddress' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdSourceLinkLayerAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceLinkLayerAddress'", field);
    }
}

const char *Ipv6NdSourceLinkLayerAddressDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6NdSourceLinkLayerAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdSourceLinkLayerAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdSourceLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdSourceLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdSourceLinkLayerAddress'", field);
    }
}

Register_Class(Ipv6NdTargetLinkLayerAddress)

Ipv6NdTargetLinkLayerAddress::Ipv6NdTargetLinkLayerAddress() : ::inet::Ipv6NdSourceTargetLinkLayerAddress()
{
    this->setType(IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION);
}

Ipv6NdTargetLinkLayerAddress::Ipv6NdTargetLinkLayerAddress(const Ipv6NdTargetLinkLayerAddress& other) : ::inet::Ipv6NdSourceTargetLinkLayerAddress(other)
{
    copy(other);
}

Ipv6NdTargetLinkLayerAddress::~Ipv6NdTargetLinkLayerAddress()
{
}

Ipv6NdTargetLinkLayerAddress& Ipv6NdTargetLinkLayerAddress::operator=(const Ipv6NdTargetLinkLayerAddress& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdTargetLinkLayerAddress::copy(const Ipv6NdTargetLinkLayerAddress& other)
{
}

void Ipv6NdTargetLinkLayerAddress::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::parsimPack(b);
}

void Ipv6NdTargetLinkLayerAddress::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdSourceTargetLinkLayerAddress::parsimUnpack(b);
}

class Ipv6NdTargetLinkLayerAddressDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6NdTargetLinkLayerAddressDescriptor();
    virtual ~Ipv6NdTargetLinkLayerAddressDescriptor();

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

Register_ClassDescriptor(Ipv6NdTargetLinkLayerAddressDescriptor)

Ipv6NdTargetLinkLayerAddressDescriptor::Ipv6NdTargetLinkLayerAddressDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdTargetLinkLayerAddress)), "inet::Ipv6NdSourceTargetLinkLayerAddress")
{
    propertyNames = nullptr;
}

Ipv6NdTargetLinkLayerAddressDescriptor::~Ipv6NdTargetLinkLayerAddressDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdTargetLinkLayerAddressDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdTargetLinkLayerAddress *>(obj)!=nullptr;
}

const char **Ipv6NdTargetLinkLayerAddressDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdTargetLinkLayerAddressDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6NdTargetLinkLayerAddressDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6NdTargetLinkLayerAddressDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6NdTargetLinkLayerAddressDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdTargetLinkLayerAddressDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdTargetLinkLayerAddressDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdTargetLinkLayerAddress'", field);
    }
}

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdTargetLinkLayerAddressDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6NdTargetLinkLayerAddressDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdTargetLinkLayerAddress'", field);
    }
}

omnetpp::cValue Ipv6NdTargetLinkLayerAddressDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdTargetLinkLayerAddress' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdTargetLinkLayerAddressDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdTargetLinkLayerAddress'", field);
    }
}

const char *Ipv6NdTargetLinkLayerAddressDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6NdTargetLinkLayerAddressDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdTargetLinkLayerAddressDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdTargetLinkLayerAddress *pp = omnetpp::fromAnyPtr<Ipv6NdTargetLinkLayerAddress>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdTargetLinkLayerAddress'", field);
    }
}

Register_Class(Ipv6NdPrefixInformation)

Ipv6NdPrefixInformation::Ipv6NdPrefixInformation() : ::inet::Ipv6NdOption()
{
    this->setType(IPv6ND_PREFIX_INFORMATION);
    this->setOptionLength(4);

}

Ipv6NdPrefixInformation::Ipv6NdPrefixInformation(const Ipv6NdPrefixInformation& other) : ::inet::Ipv6NdOption(other)
{
    copy(other);
}

Ipv6NdPrefixInformation::~Ipv6NdPrefixInformation()
{
}

Ipv6NdPrefixInformation& Ipv6NdPrefixInformation::operator=(const Ipv6NdPrefixInformation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdOption::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdPrefixInformation::copy(const Ipv6NdPrefixInformation& other)
{
    this->prefixLength = other.prefixLength;
    this->onlinkFlag = other.onlinkFlag;
    this->autoAddressConfFlag = other.autoAddressConfFlag;
    this->routerAddressFlag = other.routerAddressFlag;
    this->reserved1 = other.reserved1;
    this->validLifetime = other.validLifetime;
    this->preferredLifetime = other.preferredLifetime;
    this->reserved2 = other.reserved2;
    this->prefix = other.prefix;
}

void Ipv6NdPrefixInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdOption::parsimPack(b);
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->onlinkFlag);
    doParsimPacking(b,this->autoAddressConfFlag);
    doParsimPacking(b,this->routerAddressFlag);
    doParsimPacking(b,this->reserved1);
    doParsimPacking(b,this->validLifetime);
    doParsimPacking(b,this->preferredLifetime);
    doParsimPacking(b,this->reserved2);
    doParsimPacking(b,this->prefix);
}

void Ipv6NdPrefixInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdOption::parsimUnpack(b);
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->onlinkFlag);
    doParsimUnpacking(b,this->autoAddressConfFlag);
    doParsimUnpacking(b,this->routerAddressFlag);
    doParsimUnpacking(b,this->reserved1);
    doParsimUnpacking(b,this->validLifetime);
    doParsimUnpacking(b,this->preferredLifetime);
    doParsimUnpacking(b,this->reserved2);
    doParsimUnpacking(b,this->prefix);
}

unsigned short Ipv6NdPrefixInformation::getPrefixLength() const
{
    return this->prefixLength;
}

void Ipv6NdPrefixInformation::setPrefixLength(unsigned short prefixLength)
{
    this->prefixLength = prefixLength;
}

bool Ipv6NdPrefixInformation::getOnlinkFlag() const
{
    return this->onlinkFlag;
}

void Ipv6NdPrefixInformation::setOnlinkFlag(bool onlinkFlag)
{
    this->onlinkFlag = onlinkFlag;
}

bool Ipv6NdPrefixInformation::getAutoAddressConfFlag() const
{
    return this->autoAddressConfFlag;
}

void Ipv6NdPrefixInformation::setAutoAddressConfFlag(bool autoAddressConfFlag)
{
    this->autoAddressConfFlag = autoAddressConfFlag;
}

bool Ipv6NdPrefixInformation::getRouterAddressFlag() const
{
    return this->routerAddressFlag;
}

void Ipv6NdPrefixInformation::setRouterAddressFlag(bool routerAddressFlag)
{
    this->routerAddressFlag = routerAddressFlag;
}

unsigned int Ipv6NdPrefixInformation::getReserved1() const
{
    return this->reserved1;
}

void Ipv6NdPrefixInformation::setReserved1(unsigned int reserved1)
{
    this->reserved1 = reserved1;
}

uint32_t Ipv6NdPrefixInformation::getValidLifetime() const
{
    return this->validLifetime;
}

void Ipv6NdPrefixInformation::setValidLifetime(uint32_t validLifetime)
{
    this->validLifetime = validLifetime;
}

uint32_t Ipv6NdPrefixInformation::getPreferredLifetime() const
{
    return this->preferredLifetime;
}

void Ipv6NdPrefixInformation::setPreferredLifetime(uint32_t preferredLifetime)
{
    this->preferredLifetime = preferredLifetime;
}

uint32_t Ipv6NdPrefixInformation::getReserved2() const
{
    return this->reserved2;
}

void Ipv6NdPrefixInformation::setReserved2(uint32_t reserved2)
{
    this->reserved2 = reserved2;
}

const Ipv6Address& Ipv6NdPrefixInformation::getPrefix() const
{
    return this->prefix;
}

void Ipv6NdPrefixInformation::setPrefix(const Ipv6Address& prefix)
{
    this->prefix = prefix;
}

class Ipv6NdPrefixInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_prefixLength,
        FIELD_onlinkFlag,
        FIELD_autoAddressConfFlag,
        FIELD_routerAddressFlag,
        FIELD_reserved1,
        FIELD_validLifetime,
        FIELD_preferredLifetime,
        FIELD_reserved2,
        FIELD_prefix,
    };
  public:
    Ipv6NdPrefixInformationDescriptor();
    virtual ~Ipv6NdPrefixInformationDescriptor();

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

Register_ClassDescriptor(Ipv6NdPrefixInformationDescriptor)

Ipv6NdPrefixInformationDescriptor::Ipv6NdPrefixInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdPrefixInformation)), "inet::Ipv6NdOption")
{
    propertyNames = nullptr;
}

Ipv6NdPrefixInformationDescriptor::~Ipv6NdPrefixInformationDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdPrefixInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdPrefixInformation *>(obj)!=nullptr;
}

const char **Ipv6NdPrefixInformationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdPrefixInformationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdPrefixInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ipv6NdPrefixInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_onlinkFlag
        FD_ISEDITABLE,    // FIELD_autoAddressConfFlag
        FD_ISEDITABLE,    // FIELD_routerAddressFlag
        FD_ISEDITABLE,    // FIELD_reserved1
        FD_ISEDITABLE,    // FIELD_validLifetime
        FD_ISEDITABLE,    // FIELD_preferredLifetime
        FD_ISEDITABLE,    // FIELD_reserved2
        0,    // FIELD_prefix
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "prefixLength",
        "onlinkFlag",
        "autoAddressConfFlag",
        "routerAddressFlag",
        "reserved1",
        "validLifetime",
        "preferredLifetime",
        "reserved2",
        "prefix",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ipv6NdPrefixInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "prefixLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "onlinkFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "autoAddressConfFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "routerAddressFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "reserved1") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "validLifetime") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "preferredLifetime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "reserved2") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "prefix") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_prefixLength
        "bool",    // FIELD_onlinkFlag
        "bool",    // FIELD_autoAddressConfFlag
        "bool",    // FIELD_routerAddressFlag
        "unsigned int",    // FIELD_reserved1
        "uint32_t",    // FIELD_validLifetime
        "uint32_t",    // FIELD_preferredLifetime
        "uint32_t",    // FIELD_reserved2
        "inet::Ipv6Address",    // FIELD_prefix
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdPrefixInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdPrefixInformationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdPrefixInformationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdPrefixInformationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdPrefixInformation'", field);
    }
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdPrefixInformationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: return ulong2string(pp->getPrefixLength());
        case FIELD_onlinkFlag: return bool2string(pp->getOnlinkFlag());
        case FIELD_autoAddressConfFlag: return bool2string(pp->getAutoAddressConfFlag());
        case FIELD_routerAddressFlag: return bool2string(pp->getRouterAddressFlag());
        case FIELD_reserved1: return ulong2string(pp->getReserved1());
        case FIELD_validLifetime: return ulong2string(pp->getValidLifetime());
        case FIELD_preferredLifetime: return ulong2string(pp->getPreferredLifetime());
        case FIELD_reserved2: return ulong2string(pp->getReserved2());
        case FIELD_prefix: return pp->getPrefix().str();
        default: return "";
    }
}

void Ipv6NdPrefixInformationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(string2ulong(value)); break;
        case FIELD_onlinkFlag: pp->setOnlinkFlag(string2bool(value)); break;
        case FIELD_autoAddressConfFlag: pp->setAutoAddressConfFlag(string2bool(value)); break;
        case FIELD_routerAddressFlag: pp->setRouterAddressFlag(string2bool(value)); break;
        case FIELD_reserved1: pp->setReserved1(string2ulong(value)); break;
        case FIELD_validLifetime: pp->setValidLifetime(string2ulong(value)); break;
        case FIELD_preferredLifetime: pp->setPreferredLifetime(string2ulong(value)); break;
        case FIELD_reserved2: pp->setReserved2(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdPrefixInformation'", field);
    }
}

omnetpp::cValue Ipv6NdPrefixInformationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: return (omnetpp::intval_t)(pp->getPrefixLength());
        case FIELD_onlinkFlag: return pp->getOnlinkFlag();
        case FIELD_autoAddressConfFlag: return pp->getAutoAddressConfFlag();
        case FIELD_routerAddressFlag: return pp->getRouterAddressFlag();
        case FIELD_reserved1: return (omnetpp::intval_t)(pp->getReserved1());
        case FIELD_validLifetime: return (omnetpp::intval_t)(pp->getValidLifetime());
        case FIELD_preferredLifetime: return (omnetpp::intval_t)(pp->getPreferredLifetime());
        case FIELD_reserved2: return (omnetpp::intval_t)(pp->getReserved2());
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->getPrefix()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdPrefixInformation' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdPrefixInformationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_onlinkFlag: pp->setOnlinkFlag(value.boolValue()); break;
        case FIELD_autoAddressConfFlag: pp->setAutoAddressConfFlag(value.boolValue()); break;
        case FIELD_routerAddressFlag: pp->setRouterAddressFlag(value.boolValue()); break;
        case FIELD_reserved1: pp->setReserved1(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_validLifetime: pp->setValidLifetime(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_preferredLifetime: pp->setPreferredLifetime(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_reserved2: pp->setReserved2(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdPrefixInformation'", field);
    }
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdPrefixInformationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        case FIELD_prefix: return omnetpp::toAnyPtr(&pp->getPrefix()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdPrefixInformationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = omnetpp::fromAnyPtr<Ipv6NdPrefixInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdPrefixInformation'", field);
    }
}

Register_Class(Ipv6NdMtu)

Ipv6NdMtu::Ipv6NdMtu() : ::inet::Ipv6NdOption()
{
    this->setType(IPv6ND_MTU);
    this->setOptionLength(1);

}

Ipv6NdMtu::Ipv6NdMtu(const Ipv6NdMtu& other) : ::inet::Ipv6NdOption(other)
{
    copy(other);
}

Ipv6NdMtu::~Ipv6NdMtu()
{
}

Ipv6NdMtu& Ipv6NdMtu::operator=(const Ipv6NdMtu& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdOption::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdMtu::copy(const Ipv6NdMtu& other)
{
    this->reserved = other.reserved;
    this->mtu = other.mtu;
}

void Ipv6NdMtu::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdOption::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->mtu);
}

void Ipv6NdMtu::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdOption::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->mtu);
}

uint16_t Ipv6NdMtu::getReserved() const
{
    return this->reserved;
}

void Ipv6NdMtu::setReserved(uint16_t reserved)
{
    this->reserved = reserved;
}

uint32_t Ipv6NdMtu::getMtu() const
{
    return this->mtu;
}

void Ipv6NdMtu::setMtu(uint32_t mtu)
{
    this->mtu = mtu;
}

class Ipv6NdMtuDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_mtu,
    };
  public:
    Ipv6NdMtuDescriptor();
    virtual ~Ipv6NdMtuDescriptor();

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

Register_ClassDescriptor(Ipv6NdMtuDescriptor)

Ipv6NdMtuDescriptor::Ipv6NdMtuDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdMtu)), "inet::Ipv6NdOption")
{
    propertyNames = nullptr;
}

Ipv6NdMtuDescriptor::~Ipv6NdMtuDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdMtuDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdMtu *>(obj)!=nullptr;
}

const char **Ipv6NdMtuDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdMtuDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdMtuDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv6NdMtuDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_mtu
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdMtuDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "mtu",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6NdMtuDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "mtu") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdMtuDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "uint32_t",    // FIELD_mtu
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdMtuDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdMtuDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdMtuDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdMtuDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdMtu'", field);
    }
}

const char *Ipv6NdMtuDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdMtuDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_mtu: return ulong2string(pp->getMtu());
        default: return "";
    }
}

void Ipv6NdMtuDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_mtu: pp->setMtu(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMtu'", field);
    }
}

omnetpp::cValue Ipv6NdMtuDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_mtu: return (omnetpp::intval_t)(pp->getMtu());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdMtu' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdMtuDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_mtu: pp->setMtu(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMtu'", field);
    }
}

const char *Ipv6NdMtuDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdMtuDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdMtuDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMtu *pp = omnetpp::fromAnyPtr<Ipv6NdMtu>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMtu'", field);
    }
}

Register_Class(Mipv6NdAdvertisementInterval)

Mipv6NdAdvertisementInterval::Mipv6NdAdvertisementInterval() : ::inet::Ipv6NdOption()
{
    this->setType(IPv6ND_ADVERTISEMENT_INTERVAL);
    this->setOptionLength(1);

}

Mipv6NdAdvertisementInterval::Mipv6NdAdvertisementInterval(const Mipv6NdAdvertisementInterval& other) : ::inet::Ipv6NdOption(other)
{
    copy(other);
}

Mipv6NdAdvertisementInterval::~Mipv6NdAdvertisementInterval()
{
}

Mipv6NdAdvertisementInterval& Mipv6NdAdvertisementInterval::operator=(const Mipv6NdAdvertisementInterval& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdOption::operator=(other);
    copy(other);
    return *this;
}

void Mipv6NdAdvertisementInterval::copy(const Mipv6NdAdvertisementInterval& other)
{
    this->reserved = other.reserved;
    this->advertisementInterval = other.advertisementInterval;
}

void Mipv6NdAdvertisementInterval::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdOption::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->advertisementInterval);
}

void Mipv6NdAdvertisementInterval::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdOption::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->advertisementInterval);
}

uint16_t Mipv6NdAdvertisementInterval::getReserved() const
{
    return this->reserved;
}

void Mipv6NdAdvertisementInterval::setReserved(uint16_t reserved)
{
    this->reserved = reserved;
}

uint32_t Mipv6NdAdvertisementInterval::getAdvertisementInterval() const
{
    return this->advertisementInterval;
}

void Mipv6NdAdvertisementInterval::setAdvertisementInterval(uint32_t advertisementInterval)
{
    this->advertisementInterval = advertisementInterval;
}

class Mipv6NdAdvertisementIntervalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_advertisementInterval,
    };
  public:
    Mipv6NdAdvertisementIntervalDescriptor();
    virtual ~Mipv6NdAdvertisementIntervalDescriptor();

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

Register_ClassDescriptor(Mipv6NdAdvertisementIntervalDescriptor)

Mipv6NdAdvertisementIntervalDescriptor::Mipv6NdAdvertisementIntervalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Mipv6NdAdvertisementInterval)), "inet::Ipv6NdOption")
{
    propertyNames = nullptr;
}

Mipv6NdAdvertisementIntervalDescriptor::~Mipv6NdAdvertisementIntervalDescriptor()
{
    delete[] propertyNames;
}

bool Mipv6NdAdvertisementIntervalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Mipv6NdAdvertisementInterval *>(obj)!=nullptr;
}

const char **Mipv6NdAdvertisementIntervalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Mipv6NdAdvertisementIntervalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Mipv6NdAdvertisementIntervalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_advertisementInterval
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "advertisementInterval",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Mipv6NdAdvertisementIntervalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "advertisementInterval") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "uint32_t",    // FIELD_advertisementInterval
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Mipv6NdAdvertisementIntervalDescriptor::getFieldPropertyNames(int field) const
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

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Mipv6NdAdvertisementIntervalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Mipv6NdAdvertisementIntervalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Mipv6NdAdvertisementInterval'", field);
    }
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Mipv6NdAdvertisementIntervalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_advertisementInterval: return ulong2string(pp->getAdvertisementInterval());
        default: return "";
    }
}

void Mipv6NdAdvertisementIntervalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_advertisementInterval: pp->setAdvertisementInterval(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6NdAdvertisementInterval'", field);
    }
}

omnetpp::cValue Mipv6NdAdvertisementIntervalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_advertisementInterval: return (omnetpp::intval_t)(pp->getAdvertisementInterval());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Mipv6NdAdvertisementInterval' as cValue -- field index out of range?", field);
    }
}

void Mipv6NdAdvertisementIntervalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_advertisementInterval: pp->setAdvertisementInterval(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6NdAdvertisementInterval'", field);
    }
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Mipv6NdAdvertisementIntervalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Mipv6NdAdvertisementIntervalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = omnetpp::fromAnyPtr<Mipv6NdAdvertisementInterval>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6NdAdvertisementInterval'", field);
    }
}

Register_Class(Mipv6HaInformation)

Mipv6HaInformation::Mipv6HaInformation() : ::inet::Ipv6NdOption()
{
    this->setType(IPv6ND_HOME_AGENT_INFORMATION_OPTION);
    this->setOptionLength(1);

}

Mipv6HaInformation::Mipv6HaInformation(const Mipv6HaInformation& other) : ::inet::Ipv6NdOption(other)
{
    copy(other);
}

Mipv6HaInformation::~Mipv6HaInformation()
{
}

Mipv6HaInformation& Mipv6HaInformation::operator=(const Mipv6HaInformation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdOption::operator=(other);
    copy(other);
    return *this;
}

void Mipv6HaInformation::copy(const Mipv6HaInformation& other)
{
    this->reserved = other.reserved;
    this->homeAgentPreference = other.homeAgentPreference;
    this->homeAgentLifetime = other.homeAgentLifetime;
}

void Mipv6HaInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdOption::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->homeAgentPreference);
    doParsimPacking(b,this->homeAgentLifetime);
}

void Mipv6HaInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdOption::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->homeAgentPreference);
    doParsimUnpacking(b,this->homeAgentLifetime);
}

uint16_t Mipv6HaInformation::getReserved() const
{
    return this->reserved;
}

void Mipv6HaInformation::setReserved(uint16_t reserved)
{
    this->reserved = reserved;
}

uint16_t Mipv6HaInformation::getHomeAgentPreference() const
{
    return this->homeAgentPreference;
}

void Mipv6HaInformation::setHomeAgentPreference(uint16_t homeAgentPreference)
{
    this->homeAgentPreference = homeAgentPreference;
}

uint16_t Mipv6HaInformation::getHomeAgentLifetime() const
{
    return this->homeAgentLifetime;
}

void Mipv6HaInformation::setHomeAgentLifetime(uint16_t homeAgentLifetime)
{
    this->homeAgentLifetime = homeAgentLifetime;
}

class Mipv6HaInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_homeAgentPreference,
        FIELD_homeAgentLifetime,
    };
  public:
    Mipv6HaInformationDescriptor();
    virtual ~Mipv6HaInformationDescriptor();

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

Register_ClassDescriptor(Mipv6HaInformationDescriptor)

Mipv6HaInformationDescriptor::Mipv6HaInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Mipv6HaInformation)), "inet::Ipv6NdOption")
{
    propertyNames = nullptr;
}

Mipv6HaInformationDescriptor::~Mipv6HaInformationDescriptor()
{
    delete[] propertyNames;
}

bool Mipv6HaInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Mipv6HaInformation *>(obj)!=nullptr;
}

const char **Mipv6HaInformationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Mipv6HaInformationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Mipv6HaInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Mipv6HaInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_homeAgentPreference
        FD_ISEDITABLE,    // FIELD_homeAgentLifetime
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Mipv6HaInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "homeAgentPreference",
        "homeAgentLifetime",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Mipv6HaInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "homeAgentPreference") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "homeAgentLifetime") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Mipv6HaInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_reserved
        "uint16_t",    // FIELD_homeAgentPreference
        "uint16_t",    // FIELD_homeAgentLifetime
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Mipv6HaInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Mipv6HaInformationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Mipv6HaInformationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Mipv6HaInformationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Mipv6HaInformation'", field);
    }
}

const char *Mipv6HaInformationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Mipv6HaInformationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_homeAgentPreference: return ulong2string(pp->getHomeAgentPreference());
        case FIELD_homeAgentLifetime: return ulong2string(pp->getHomeAgentLifetime());
        default: return "";
    }
}

void Mipv6HaInformationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_homeAgentPreference: pp->setHomeAgentPreference(string2ulong(value)); break;
        case FIELD_homeAgentLifetime: pp->setHomeAgentLifetime(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6HaInformation'", field);
    }
}

omnetpp::cValue Mipv6HaInformationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_homeAgentPreference: return (omnetpp::intval_t)(pp->getHomeAgentPreference());
        case FIELD_homeAgentLifetime: return (omnetpp::intval_t)(pp->getHomeAgentLifetime());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Mipv6HaInformation' as cValue -- field index out of range?", field);
    }
}

void Mipv6HaInformationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_homeAgentPreference: pp->setHomeAgentPreference(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_homeAgentLifetime: pp->setHomeAgentLifetime(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6HaInformation'", field);
    }
}

const char *Mipv6HaInformationDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Mipv6HaInformationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Mipv6HaInformationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Mipv6HaInformation *pp = omnetpp::fromAnyPtr<Mipv6HaInformation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Mipv6HaInformation'", field);
    }
}

Register_Class(Ipv6NdOptions)

Ipv6NdOptions::Ipv6NdOptions() : ::omnetpp::cObject()
{
}

Ipv6NdOptions::Ipv6NdOptions(const Ipv6NdOptions& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdOptions::~Ipv6NdOptions()
{
    for (size_t i = 0; i < option_arraysize; i++)
        delete this->option[i];
    delete [] this->option;
}

Ipv6NdOptions& Ipv6NdOptions::operator=(const Ipv6NdOptions& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdOptions::copy(const Ipv6NdOptions& other)
{
    for (size_t i = 0; i < option_arraysize; i++)
        delete this->option[i];
    delete [] this->option;
    this->option = (other.option_arraysize==0) ? nullptr : new Ipv6NdOption *[other.option_arraysize];
    option_arraysize = other.option_arraysize;
    for (size_t i = 0; i < option_arraysize; i++) {
        this->option[i] = other.option[i];
        if (this->option[i] != nullptr) {
            this->option[i] = this->option[i]->dup();
        }
    }
}

void Ipv6NdOptions::parsimPack(omnetpp::cCommBuffer *b) const
{
    b->pack(option_arraysize);
    doParsimArrayPacking(b,this->option,option_arraysize);
}

void Ipv6NdOptions::parsimUnpack(omnetpp::cCommBuffer *b)
{
    delete [] this->option;
    b->unpack(option_arraysize);
    if (option_arraysize == 0) {
        this->option = nullptr;
    } else {
        this->option = new Ipv6NdOption *[option_arraysize];
        doParsimArrayUnpacking(b,this->option,option_arraysize);
    }
}

size_t Ipv6NdOptions::getOptionArraySize() const
{
    return option_arraysize;
}

const Ipv6NdOption * Ipv6NdOptions::getOption(size_t k) const
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    return this->option[k];
}

void Ipv6NdOptions::setOptionArraySize(size_t newSize)
{
    Ipv6NdOption * *option2 = (newSize==0) ? nullptr : new Ipv6NdOption *[newSize];
    size_t minSize = option_arraysize < newSize ? option_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        option2[i] = this->option[i];
    for (size_t i = minSize; i < newSize; i++)
        option2[i] = nullptr;
    for (size_t i = newSize; i < option_arraysize; i++)
        delete option[i];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

void Ipv6NdOptions::setOption(size_t k, Ipv6NdOption * option)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    if (this->option[k] != nullptr) throw omnetpp::cRuntimeError("setOption(): a value is already set, remove it first with removeOption()");
    this->option[k] = option;
    if (this->option[k] != nullptr && this->option[k]->isOwnedObject()) take((cOwnedObject*)this->option[k]);
}

Ipv6NdOption * Ipv6NdOptions::removeOption(size_t k)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    Ipv6NdOption * retval = this->option[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->option[k] = nullptr;
    return retval;
}

void Ipv6NdOptions::insertOption(size_t k, Ipv6NdOption * option)
{
    if (k > option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    size_t newSize = option_arraysize + 1;
    Ipv6NdOption * *option2 = new Ipv6NdOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        option2[i] = this->option[i];
    option2[k] = option;
    if (option2[k] != nullptr && option2[k]->isOwnedObject()) take((cOwnedObject*)option2[k]);
    for (i = k + 1; i < newSize; i++)
        option2[i] = this->option[i-1];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

void Ipv6NdOptions::appendOption(Ipv6NdOption * option)
{
    insertOption(option_arraysize, option);
}

void Ipv6NdOptions::eraseOption(size_t k)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    size_t newSize = option_arraysize - 1;
    Ipv6NdOption * *option2 = (newSize == 0) ? nullptr : new Ipv6NdOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        option2[i] = this->option[i];
    for (i = k; i < newSize; i++)
        option2[i] = this->option[i+1];
    if (this->option[k] != nullptr && this->option[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->option[k]); else delete this->option[k];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

class Ipv6NdOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_option,
    };
  public:
    Ipv6NdOptionsDescriptor();
    virtual ~Ipv6NdOptionsDescriptor();

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

Register_ClassDescriptor(Ipv6NdOptionsDescriptor)

Ipv6NdOptionsDescriptor::Ipv6NdOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdOptions)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv6NdOptionsDescriptor::~Ipv6NdOptionsDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdOptions *>(obj)!=nullptr;
}

const char **Ipv6NdOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdOptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6NdOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_option
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "option",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6NdOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "option") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6NdOption",    // FIELD_option
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdOptionsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv6NdOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv6NdOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: return pp->getOptionArraySize();
        default: return 0;
    }
}

void Ipv6NdOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOptionArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdOptions'", field);
    }
}

const char *Ipv6NdOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: { const Ipv6NdOption * value = pp->getOption(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ipv6NdOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: { auto obj = pp->getOption(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void Ipv6NdOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOptions'", field);
    }
}

omnetpp::cValue Ipv6NdOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: return omnetpp::toAnyPtr(pp->getOption(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdOptions' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOption(i,omnetpp::fromAnyPtr<Ipv6NdOption>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOptions'", field);
    }
}

const char *Ipv6NdOptionsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option: return omnetpp::opp_typename(typeid(Ipv6NdOption));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6NdOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: return omnetpp::toAnyPtr(pp->getOption(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdOptions *pp = omnetpp::fromAnyPtr<Ipv6NdOptions>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOption(i,omnetpp::fromAnyPtr<Ipv6NdOption>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdOptions'", field);
    }
}

Register_Class(Ipv6NdMessage)

Ipv6NdMessage::Ipv6NdMessage() : ::inet::Icmpv6Header()
{
}

Ipv6NdMessage::Ipv6NdMessage(const Ipv6NdMessage& other) : ::inet::Icmpv6Header(other)
{
    copy(other);
}

Ipv6NdMessage::~Ipv6NdMessage()
{
}

Ipv6NdMessage& Ipv6NdMessage::operator=(const Ipv6NdMessage& other)
{
    if (this == &other) return *this;
    ::inet::Icmpv6Header::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdMessage::copy(const Ipv6NdMessage& other)
{
    this->code = other.code;
}

void Ipv6NdMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Icmpv6Header::parsimPack(b);
    doParsimPacking(b,this->code);
}

void Ipv6NdMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Icmpv6Header::parsimUnpack(b);
    doParsimUnpacking(b,this->code);
}

int Ipv6NdMessage::getCode() const
{
    return this->code;
}

void Ipv6NdMessage::setCode(int code)
{
    handleChange();
    this->code = code;
}

class Ipv6NdMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_code,
    };
  public:
    Ipv6NdMessageDescriptor();
    virtual ~Ipv6NdMessageDescriptor();

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

Register_ClassDescriptor(Ipv6NdMessageDescriptor)

Ipv6NdMessageDescriptor::Ipv6NdMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdMessage)), "inet::Icmpv6Header")
{
    propertyNames = nullptr;
}

Ipv6NdMessageDescriptor::~Ipv6NdMessageDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdMessage *>(obj)!=nullptr;
}

const char **Ipv6NdMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6NdMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_code
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "code",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6NdMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "code") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_code
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdMessage'", field);
    }
}

const char *Ipv6NdMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        case FIELD_code: return long2string(pp->getCode());
        default: return "";
    }
}

void Ipv6NdMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        case FIELD_code: pp->setCode(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMessage'", field);
    }
}

omnetpp::cValue Ipv6NdMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        case FIELD_code: return pp->getCode();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdMessage' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        case FIELD_code: pp->setCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMessage'", field);
    }
}

const char *Ipv6NdMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdMessage *pp = omnetpp::fromAnyPtr<Ipv6NdMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdMessage'", field);
    }
}

Register_Class(Ipv6RouterSolicitation)

Ipv6RouterSolicitation::Ipv6RouterSolicitation() : ::inet::Ipv6NdMessage()
{
    this->setChunkLength(B(8));
    this->setType(ICMPv6_ROUTER_SOL);

}

Ipv6RouterSolicitation::Ipv6RouterSolicitation(const Ipv6RouterSolicitation& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6RouterSolicitation::~Ipv6RouterSolicitation()
{
}

Ipv6RouterSolicitation& Ipv6RouterSolicitation::operator=(const Ipv6RouterSolicitation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6RouterSolicitation::copy(const Ipv6RouterSolicitation& other)
{
    this->reserved = other.reserved;
    this->options = other.options;
}

void Ipv6RouterSolicitation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->options);
}

void Ipv6RouterSolicitation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->options);
}

uint32_t Ipv6RouterSolicitation::getReserved() const
{
    return this->reserved;
}

void Ipv6RouterSolicitation::setReserved(uint32_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

const Ipv6NdOptions& Ipv6RouterSolicitation::getOptions() const
{
    return this->options;
}

void Ipv6RouterSolicitation::setOptions(const Ipv6NdOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv6RouterSolicitationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_options,
    };
  public:
    Ipv6RouterSolicitationDescriptor();
    virtual ~Ipv6RouterSolicitationDescriptor();

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

Register_ClassDescriptor(Ipv6RouterSolicitationDescriptor)

Ipv6RouterSolicitationDescriptor::Ipv6RouterSolicitationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6RouterSolicitation)), "inet::Ipv6NdMessage")
{
    propertyNames = nullptr;
}

Ipv6RouterSolicitationDescriptor::~Ipv6RouterSolicitationDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6RouterSolicitationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6RouterSolicitation *>(obj)!=nullptr;
}

const char **Ipv6RouterSolicitationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6RouterSolicitationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6RouterSolicitationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv6RouterSolicitationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RouterSolicitationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "options",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6RouterSolicitationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6RouterSolicitationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_reserved
        "inet::Ipv6NdOptions",    // FIELD_options
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RouterSolicitationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RouterSolicitationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6RouterSolicitationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6RouterSolicitationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6RouterSolicitation'", field);
    }
}

const char *Ipv6RouterSolicitationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RouterSolicitationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv6RouterSolicitationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterSolicitation'", field);
    }
}

omnetpp::cValue Ipv6RouterSolicitationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6RouterSolicitation' as cValue -- field index out of range?", field);
    }
}

void Ipv6RouterSolicitationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterSolicitation'", field);
    }
}

const char *Ipv6RouterSolicitationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ipv6NdOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6RouterSolicitationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6RouterSolicitationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = omnetpp::fromAnyPtr<Ipv6RouterSolicitation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterSolicitation'", field);
    }
}

Register_Class(Ipv6RouterAdvertisement)

Ipv6RouterAdvertisement::Ipv6RouterAdvertisement() : ::inet::Ipv6NdMessage()
{
    this->setChunkLength(B(16));
    this->setType(ICMPv6_ROUTER_AD);

}

Ipv6RouterAdvertisement::Ipv6RouterAdvertisement(const Ipv6RouterAdvertisement& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6RouterAdvertisement::~Ipv6RouterAdvertisement()
{
}

Ipv6RouterAdvertisement& Ipv6RouterAdvertisement::operator=(const Ipv6RouterAdvertisement& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6RouterAdvertisement::copy(const Ipv6RouterAdvertisement& other)
{
    this->curHopLimit = other.curHopLimit;
    this->managedAddrConfFlag = other.managedAddrConfFlag;
    this->otherStatefulConfFlag = other.otherStatefulConfFlag;
    this->homeAgentFlag = other.homeAgentFlag;
    this->reserved = other.reserved;
    this->routerLifetime = other.routerLifetime;
    this->reachableTime = other.reachableTime;
    this->retransTimer = other.retransTimer;
    this->options = other.options;
}

void Ipv6RouterAdvertisement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->curHopLimit);
    doParsimPacking(b,this->managedAddrConfFlag);
    doParsimPacking(b,this->otherStatefulConfFlag);
    doParsimPacking(b,this->homeAgentFlag);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->routerLifetime);
    doParsimPacking(b,this->reachableTime);
    doParsimPacking(b,this->retransTimer);
    doParsimPacking(b,this->options);
}

void Ipv6RouterAdvertisement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->curHopLimit);
    doParsimUnpacking(b,this->managedAddrConfFlag);
    doParsimUnpacking(b,this->otherStatefulConfFlag);
    doParsimUnpacking(b,this->homeAgentFlag);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->routerLifetime);
    doParsimUnpacking(b,this->reachableTime);
    doParsimUnpacking(b,this->retransTimer);
    doParsimUnpacking(b,this->options);
}

unsigned short Ipv6RouterAdvertisement::getCurHopLimit() const
{
    return this->curHopLimit;
}

void Ipv6RouterAdvertisement::setCurHopLimit(unsigned short curHopLimit)
{
    handleChange();
    this->curHopLimit = curHopLimit;
}

bool Ipv6RouterAdvertisement::getManagedAddrConfFlag() const
{
    return this->managedAddrConfFlag;
}

void Ipv6RouterAdvertisement::setManagedAddrConfFlag(bool managedAddrConfFlag)
{
    handleChange();
    this->managedAddrConfFlag = managedAddrConfFlag;
}

bool Ipv6RouterAdvertisement::getOtherStatefulConfFlag() const
{
    return this->otherStatefulConfFlag;
}

void Ipv6RouterAdvertisement::setOtherStatefulConfFlag(bool otherStatefulConfFlag)
{
    handleChange();
    this->otherStatefulConfFlag = otherStatefulConfFlag;
}

bool Ipv6RouterAdvertisement::getHomeAgentFlag() const
{
    return this->homeAgentFlag;
}

void Ipv6RouterAdvertisement::setHomeAgentFlag(bool homeAgentFlag)
{
    handleChange();
    this->homeAgentFlag = homeAgentFlag;
}

uint8_t Ipv6RouterAdvertisement::getReserved() const
{
    return this->reserved;
}

void Ipv6RouterAdvertisement::setReserved(uint8_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

unsigned short Ipv6RouterAdvertisement::getRouterLifetime() const
{
    return this->routerLifetime;
}

void Ipv6RouterAdvertisement::setRouterLifetime(unsigned short routerLifetime)
{
    handleChange();
    this->routerLifetime = routerLifetime;
}

unsigned int Ipv6RouterAdvertisement::getReachableTime() const
{
    return this->reachableTime;
}

void Ipv6RouterAdvertisement::setReachableTime(unsigned int reachableTime)
{
    handleChange();
    this->reachableTime = reachableTime;
}

unsigned int Ipv6RouterAdvertisement::getRetransTimer() const
{
    return this->retransTimer;
}

void Ipv6RouterAdvertisement::setRetransTimer(unsigned int retransTimer)
{
    handleChange();
    this->retransTimer = retransTimer;
}

const Ipv6NdOptions& Ipv6RouterAdvertisement::getOptions() const
{
    return this->options;
}

void Ipv6RouterAdvertisement::setOptions(const Ipv6NdOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv6RouterAdvertisementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_curHopLimit,
        FIELD_managedAddrConfFlag,
        FIELD_otherStatefulConfFlag,
        FIELD_homeAgentFlag,
        FIELD_reserved,
        FIELD_routerLifetime,
        FIELD_reachableTime,
        FIELD_retransTimer,
        FIELD_options,
    };
  public:
    Ipv6RouterAdvertisementDescriptor();
    virtual ~Ipv6RouterAdvertisementDescriptor();

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

Register_ClassDescriptor(Ipv6RouterAdvertisementDescriptor)

Ipv6RouterAdvertisementDescriptor::Ipv6RouterAdvertisementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6RouterAdvertisement)), "inet::Ipv6NdMessage")
{
    propertyNames = nullptr;
}

Ipv6RouterAdvertisementDescriptor::~Ipv6RouterAdvertisementDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6RouterAdvertisementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6RouterAdvertisement *>(obj)!=nullptr;
}

const char **Ipv6RouterAdvertisementDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6RouterAdvertisementDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6RouterAdvertisementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int Ipv6RouterAdvertisementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_curHopLimit
        FD_ISEDITABLE,    // FIELD_managedAddrConfFlag
        FD_ISEDITABLE,    // FIELD_otherStatefulConfFlag
        FD_ISEDITABLE,    // FIELD_homeAgentFlag
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_routerLifetime
        FD_ISEDITABLE,    // FIELD_reachableTime
        FD_ISEDITABLE,    // FIELD_retransTimer
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "curHopLimit",
        "managedAddrConfFlag",
        "otherStatefulConfFlag",
        "homeAgentFlag",
        "reserved",
        "routerLifetime",
        "reachableTime",
        "retransTimer",
        "options",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ipv6RouterAdvertisementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "curHopLimit") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "managedAddrConfFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "otherStatefulConfFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "homeAgentFlag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "routerLifetime") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "reachableTime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "retransTimer") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_curHopLimit
        "bool",    // FIELD_managedAddrConfFlag
        "bool",    // FIELD_otherStatefulConfFlag
        "bool",    // FIELD_homeAgentFlag
        "uint8_t",    // FIELD_reserved
        "unsigned short",    // FIELD_routerLifetime
        "unsigned int",    // FIELD_reachableTime
        "unsigned int",    // FIELD_retransTimer
        "inet::Ipv6NdOptions",    // FIELD_options
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RouterAdvertisementDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RouterAdvertisementDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6RouterAdvertisementDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6RouterAdvertisementDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6RouterAdvertisement'", field);
    }
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RouterAdvertisementDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_curHopLimit: return ulong2string(pp->getCurHopLimit());
        case FIELD_managedAddrConfFlag: return bool2string(pp->getManagedAddrConfFlag());
        case FIELD_otherStatefulConfFlag: return bool2string(pp->getOtherStatefulConfFlag());
        case FIELD_homeAgentFlag: return bool2string(pp->getHomeAgentFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_routerLifetime: return ulong2string(pp->getRouterLifetime());
        case FIELD_reachableTime: return ulong2string(pp->getReachableTime());
        case FIELD_retransTimer: return ulong2string(pp->getRetransTimer());
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv6RouterAdvertisementDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_curHopLimit: pp->setCurHopLimit(string2ulong(value)); break;
        case FIELD_managedAddrConfFlag: pp->setManagedAddrConfFlag(string2bool(value)); break;
        case FIELD_otherStatefulConfFlag: pp->setOtherStatefulConfFlag(string2bool(value)); break;
        case FIELD_homeAgentFlag: pp->setHomeAgentFlag(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        case FIELD_routerLifetime: pp->setRouterLifetime(string2ulong(value)); break;
        case FIELD_reachableTime: pp->setReachableTime(string2ulong(value)); break;
        case FIELD_retransTimer: pp->setRetransTimer(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterAdvertisement'", field);
    }
}

omnetpp::cValue Ipv6RouterAdvertisementDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_curHopLimit: return (omnetpp::intval_t)(pp->getCurHopLimit());
        case FIELD_managedAddrConfFlag: return pp->getManagedAddrConfFlag();
        case FIELD_otherStatefulConfFlag: return pp->getOtherStatefulConfFlag();
        case FIELD_homeAgentFlag: return pp->getHomeAgentFlag();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_routerLifetime: return (omnetpp::intval_t)(pp->getRouterLifetime());
        case FIELD_reachableTime: return (omnetpp::intval_t)(pp->getReachableTime());
        case FIELD_retransTimer: return (omnetpp::intval_t)(pp->getRetransTimer());
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6RouterAdvertisement' as cValue -- field index out of range?", field);
    }
}

void Ipv6RouterAdvertisementDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_curHopLimit: pp->setCurHopLimit(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_managedAddrConfFlag: pp->setManagedAddrConfFlag(value.boolValue()); break;
        case FIELD_otherStatefulConfFlag: pp->setOtherStatefulConfFlag(value.boolValue()); break;
        case FIELD_homeAgentFlag: pp->setHomeAgentFlag(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_routerLifetime: pp->setRouterLifetime(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_reachableTime: pp->setReachableTime(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_retransTimer: pp->setRetransTimer(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterAdvertisement'", field);
    }
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ipv6NdOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6RouterAdvertisementDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6RouterAdvertisementDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6RouterAdvertisement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6RouterAdvertisement'", field);
    }
}

Register_Class(Ipv6NeighbourSolicitation)

Ipv6NeighbourSolicitation::Ipv6NeighbourSolicitation() : ::inet::Ipv6NdMessage()
{
    this->setChunkLength(B(24));
    this->setType(ICMPv6_NEIGHBOUR_SOL);

}

Ipv6NeighbourSolicitation::Ipv6NeighbourSolicitation(const Ipv6NeighbourSolicitation& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6NeighbourSolicitation::~Ipv6NeighbourSolicitation()
{
}

Ipv6NeighbourSolicitation& Ipv6NeighbourSolicitation::operator=(const Ipv6NeighbourSolicitation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NeighbourSolicitation::copy(const Ipv6NeighbourSolicitation& other)
{
    this->reserved = other.reserved;
    this->targetAddress = other.targetAddress;
    this->options = other.options;
}

void Ipv6NeighbourSolicitation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->options);
}

void Ipv6NeighbourSolicitation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->options);
}

uint32_t Ipv6NeighbourSolicitation::getReserved() const
{
    return this->reserved;
}

void Ipv6NeighbourSolicitation::setReserved(uint32_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

const Ipv6Address& Ipv6NeighbourSolicitation::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6NeighbourSolicitation::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const Ipv6NdOptions& Ipv6NeighbourSolicitation::getOptions() const
{
    return this->options;
}

void Ipv6NeighbourSolicitation::setOptions(const Ipv6NdOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv6NeighbourSolicitationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reserved,
        FIELD_targetAddress,
        FIELD_options,
    };
  public:
    Ipv6NeighbourSolicitationDescriptor();
    virtual ~Ipv6NeighbourSolicitationDescriptor();

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

Register_ClassDescriptor(Ipv6NeighbourSolicitationDescriptor)

Ipv6NeighbourSolicitationDescriptor::Ipv6NeighbourSolicitationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NeighbourSolicitation)), "inet::Ipv6NdMessage")
{
    propertyNames = nullptr;
}

Ipv6NeighbourSolicitationDescriptor::~Ipv6NeighbourSolicitationDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NeighbourSolicitationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NeighbourSolicitation *>(obj)!=nullptr;
}

const char **Ipv6NeighbourSolicitationDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NeighbourSolicitationDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NeighbourSolicitationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ipv6NeighbourSolicitationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_reserved
        0,    // FIELD_targetAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reserved",
        "targetAddress",
        "options",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6NeighbourSolicitationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "targetAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_reserved
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::Ipv6NdOptions",    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NeighbourSolicitationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NeighbourSolicitationDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NeighbourSolicitationDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NeighbourSolicitationDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NeighbourSolicitation'", field);
    }
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NeighbourSolicitationDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv6NeighbourSolicitationDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourSolicitation'", field);
    }
}

omnetpp::cValue Ipv6NeighbourSolicitationDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NeighbourSolicitation' as cValue -- field index out of range?", field);
    }
}

void Ipv6NeighbourSolicitationDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourSolicitation'", field);
    }
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ipv6NdOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6NeighbourSolicitationDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NeighbourSolicitationDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = omnetpp::fromAnyPtr<Ipv6NeighbourSolicitation>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourSolicitation'", field);
    }
}

Register_Class(Ipv6NeighbourAdvertisement)

Ipv6NeighbourAdvertisement::Ipv6NeighbourAdvertisement() : ::inet::Ipv6NdMessage()
{
    this->setChunkLength(B(24));
    this->setType(ICMPv6_NEIGHBOUR_AD);

}

Ipv6NeighbourAdvertisement::Ipv6NeighbourAdvertisement(const Ipv6NeighbourAdvertisement& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6NeighbourAdvertisement::~Ipv6NeighbourAdvertisement()
{
}

Ipv6NeighbourAdvertisement& Ipv6NeighbourAdvertisement::operator=(const Ipv6NeighbourAdvertisement& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NeighbourAdvertisement::copy(const Ipv6NeighbourAdvertisement& other)
{
    this->routerFlag = other.routerFlag;
    this->solicitedFlag = other.solicitedFlag;
    this->overrideFlag = other.overrideFlag;
    this->reserved = other.reserved;
    this->targetAddress = other.targetAddress;
    this->options = other.options;
}

void Ipv6NeighbourAdvertisement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->routerFlag);
    doParsimPacking(b,this->solicitedFlag);
    doParsimPacking(b,this->overrideFlag);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->options);
}

void Ipv6NeighbourAdvertisement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->routerFlag);
    doParsimUnpacking(b,this->solicitedFlag);
    doParsimUnpacking(b,this->overrideFlag);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->options);
}

bool Ipv6NeighbourAdvertisement::getRouterFlag() const
{
    return this->routerFlag;
}

void Ipv6NeighbourAdvertisement::setRouterFlag(bool routerFlag)
{
    handleChange();
    this->routerFlag = routerFlag;
}

bool Ipv6NeighbourAdvertisement::getSolicitedFlag() const
{
    return this->solicitedFlag;
}

void Ipv6NeighbourAdvertisement::setSolicitedFlag(bool solicitedFlag)
{
    handleChange();
    this->solicitedFlag = solicitedFlag;
}

bool Ipv6NeighbourAdvertisement::getOverrideFlag() const
{
    return this->overrideFlag;
}

void Ipv6NeighbourAdvertisement::setOverrideFlag(bool overrideFlag)
{
    handleChange();
    this->overrideFlag = overrideFlag;
}

uint32_t Ipv6NeighbourAdvertisement::getReserved() const
{
    return this->reserved;
}

void Ipv6NeighbourAdvertisement::setReserved(uint32_t reserved)
{
    handleChange();
    this->reserved = reserved;
}

const Ipv6Address& Ipv6NeighbourAdvertisement::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6NeighbourAdvertisement::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const Ipv6NdOptions& Ipv6NeighbourAdvertisement::getOptions() const
{
    return this->options;
}

void Ipv6NeighbourAdvertisement::setOptions(const Ipv6NdOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv6NeighbourAdvertisementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_routerFlag,
        FIELD_solicitedFlag,
        FIELD_overrideFlag,
        FIELD_reserved,
        FIELD_targetAddress,
        FIELD_options,
    };
  public:
    Ipv6NeighbourAdvertisementDescriptor();
    virtual ~Ipv6NeighbourAdvertisementDescriptor();

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

Register_ClassDescriptor(Ipv6NeighbourAdvertisementDescriptor)

Ipv6NeighbourAdvertisementDescriptor::Ipv6NeighbourAdvertisementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NeighbourAdvertisement)), "inet::Ipv6NdMessage")
{
    propertyNames = nullptr;
}

Ipv6NeighbourAdvertisementDescriptor::~Ipv6NeighbourAdvertisementDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NeighbourAdvertisementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NeighbourAdvertisement *>(obj)!=nullptr;
}

const char **Ipv6NeighbourAdvertisementDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NeighbourAdvertisementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int Ipv6NeighbourAdvertisementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routerFlag
        FD_ISEDITABLE,    // FIELD_solicitedFlag
        FD_ISEDITABLE,    // FIELD_overrideFlag
        FD_ISEDITABLE,    // FIELD_reserved
        0,    // FIELD_targetAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerFlag",
        "solicitedFlag",
        "overrideFlag",
        "reserved",
        "targetAddress",
        "options",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int Ipv6NeighbourAdvertisementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "routerFlag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "solicitedFlag") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "overrideFlag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "targetAddress") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_routerFlag
        "bool",    // FIELD_solicitedFlag
        "bool",    // FIELD_overrideFlag
        "uint32_t",    // FIELD_reserved
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::Ipv6NdOptions",    // FIELD_options
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NeighbourAdvertisementDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NeighbourAdvertisementDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NeighbourAdvertisementDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NeighbourAdvertisement'", field);
    }
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NeighbourAdvertisementDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_routerFlag: return bool2string(pp->getRouterFlag());
        case FIELD_solicitedFlag: return bool2string(pp->getSolicitedFlag());
        case FIELD_overrideFlag: return bool2string(pp->getOverrideFlag());
        case FIELD_reserved: return ulong2string(pp->getReserved());
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv6NeighbourAdvertisementDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_routerFlag: pp->setRouterFlag(string2bool(value)); break;
        case FIELD_solicitedFlag: pp->setSolicitedFlag(string2bool(value)); break;
        case FIELD_overrideFlag: pp->setOverrideFlag(string2bool(value)); break;
        case FIELD_reserved: pp->setReserved(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourAdvertisement'", field);
    }
}

omnetpp::cValue Ipv6NeighbourAdvertisementDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_routerFlag: return pp->getRouterFlag();
        case FIELD_solicitedFlag: return pp->getSolicitedFlag();
        case FIELD_overrideFlag: return pp->getOverrideFlag();
        case FIELD_reserved: return (omnetpp::intval_t)(pp->getReserved());
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NeighbourAdvertisement' as cValue -- field index out of range?", field);
    }
}

void Ipv6NeighbourAdvertisementDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_routerFlag: pp->setRouterFlag(value.boolValue()); break;
        case FIELD_solicitedFlag: pp->setSolicitedFlag(value.boolValue()); break;
        case FIELD_overrideFlag: pp->setOverrideFlag(value.boolValue()); break;
        case FIELD_reserved: pp->setReserved(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourAdvertisement'", field);
    }
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ipv6NdOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6NeighbourAdvertisementDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NeighbourAdvertisementDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = omnetpp::fromAnyPtr<Ipv6NeighbourAdvertisement>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NeighbourAdvertisement'", field);
    }
}

Register_Class(Ipv6Redirect)

Ipv6Redirect::Ipv6Redirect() : ::inet::Ipv6NdMessage()
{
    this->setChunkLength(B(40));
    this->setType(ICMPv6_REDIRECT);

}

Ipv6Redirect::Ipv6Redirect(const Ipv6Redirect& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6Redirect::~Ipv6Redirect()
{
}

Ipv6Redirect& Ipv6Redirect::operator=(const Ipv6Redirect& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6Redirect::copy(const Ipv6Redirect& other)
{
    this->targetAddress = other.targetAddress;
    this->destinationAddress = other.destinationAddress;
    this->options = other.options;
}

void Ipv6Redirect::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->options);
}

void Ipv6Redirect::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->options);
}

const Ipv6Address& Ipv6Redirect::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6Redirect::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const Ipv6Address& Ipv6Redirect::getDestinationAddress() const
{
    return this->destinationAddress;
}

void Ipv6Redirect::setDestinationAddress(const Ipv6Address& destinationAddress)
{
    handleChange();
    this->destinationAddress = destinationAddress;
}

const Ipv6NdOptions& Ipv6Redirect::getOptions() const
{
    return this->options;
}

void Ipv6Redirect::setOptions(const Ipv6NdOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv6RedirectDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_targetAddress,
        FIELD_destinationAddress,
        FIELD_options,
    };
  public:
    Ipv6RedirectDescriptor();
    virtual ~Ipv6RedirectDescriptor();

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

Register_ClassDescriptor(Ipv6RedirectDescriptor)

Ipv6RedirectDescriptor::Ipv6RedirectDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6Redirect)), "inet::Ipv6NdMessage")
{
    propertyNames = nullptr;
}

Ipv6RedirectDescriptor::~Ipv6RedirectDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6RedirectDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6Redirect *>(obj)!=nullptr;
}

const char **Ipv6RedirectDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6RedirectDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6RedirectDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ipv6RedirectDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_targetAddress
        0,    // FIELD_destinationAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RedirectDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetAddress",
        "destinationAddress",
        "options",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6RedirectDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "targetAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destinationAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6RedirectDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::Ipv6Address",    // FIELD_destinationAddress
        "inet::Ipv6NdOptions",    // FIELD_options
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RedirectDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RedirectDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6RedirectDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6RedirectDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6Redirect'", field);
    }
}

const char *Ipv6RedirectDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RedirectDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv6RedirectDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Redirect'", field);
    }
}

omnetpp::cValue Ipv6RedirectDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_destinationAddress: return omnetpp::toAnyPtr(&pp->getDestinationAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6Redirect' as cValue -- field index out of range?", field);
    }
}

void Ipv6RedirectDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Redirect'", field);
    }
}

const char *Ipv6RedirectDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(Ipv6NdOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv6RedirectDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        case FIELD_targetAddress: return omnetpp::toAnyPtr(&pp->getTargetAddress()); break;
        case FIELD_destinationAddress: return omnetpp::toAnyPtr(&pp->getDestinationAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6RedirectDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6Redirect *pp = omnetpp::fromAnyPtr<Ipv6Redirect>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6Redirect'", field);
    }
}

Register_Class(Ipv6NdControlInfo)

Ipv6NdControlInfo::Ipv6NdControlInfo() : ::omnetpp::cObject()
{
}

Ipv6NdControlInfo::Ipv6NdControlInfo(const Ipv6NdControlInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdControlInfo::~Ipv6NdControlInfo()
{
}

Ipv6NdControlInfo& Ipv6NdControlInfo::operator=(const Ipv6NdControlInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdControlInfo::copy(const Ipv6NdControlInfo& other)
{
    this->nextHop = other.nextHop;
    this->interfaceId = other.interfaceId;
    this->fromHL = other.fromHL;
}

void Ipv6NdControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->nextHop);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->fromHL);
}

void Ipv6NdControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->nextHop);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->fromHL);
}

const Ipv6Address& Ipv6NdControlInfo::getNextHop() const
{
    return this->nextHop;
}

void Ipv6NdControlInfo::setNextHop(const Ipv6Address& nextHop)
{
    this->nextHop = nextHop;
}

int Ipv6NdControlInfo::getInterfaceId() const
{
    return this->interfaceId;
}

void Ipv6NdControlInfo::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

bool Ipv6NdControlInfo::getFromHL() const
{
    return this->fromHL;
}

void Ipv6NdControlInfo::setFromHL(bool fromHL)
{
    this->fromHL = fromHL;
}

class Ipv6NdControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_nextHop,
        FIELD_interfaceId,
        FIELD_fromHL,
    };
  public:
    Ipv6NdControlInfoDescriptor();
    virtual ~Ipv6NdControlInfoDescriptor();

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

Register_ClassDescriptor(Ipv6NdControlInfoDescriptor)

Ipv6NdControlInfoDescriptor::Ipv6NdControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdControlInfo)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ipv6NdControlInfoDescriptor::~Ipv6NdControlInfoDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6NdControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdControlInfo *>(obj)!=nullptr;
}

const char **Ipv6NdControlInfoDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6NdControlInfoDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6NdControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int Ipv6NdControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_nextHop
        FD_ISEDITABLE,    // FIELD_interfaceId
        FD_ISEDITABLE,    // FIELD_fromHL
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nextHop",
        "interfaceId",
        "fromHL",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6NdControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "nextHop") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "interfaceId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fromHL") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6NdControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_nextHop
        "int",    // FIELD_interfaceId
        "bool",    // FIELD_fromHL
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdControlInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdControlInfoDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6NdControlInfoDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6NdControlInfoDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6NdControlInfo'", field);
    }
}

const char *Ipv6NdControlInfoDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdControlInfoDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_nextHop: return pp->getNextHop().str();
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_fromHL: return bool2string(pp->getFromHL());
        default: return "";
    }
}

void Ipv6NdControlInfoDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); break;
        case FIELD_fromHL: pp->setFromHL(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdControlInfo'", field);
    }
}

omnetpp::cValue Ipv6NdControlInfoDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_nextHop: return omnetpp::toAnyPtr(&pp->getNextHop()); break;
        case FIELD_interfaceId: return pp->getInterfaceId();
        case FIELD_fromHL: return pp->getFromHL();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6NdControlInfo' as cValue -- field index out of range?", field);
    }
}

void Ipv6NdControlInfoDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fromHL: pp->setFromHL(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdControlInfo'", field);
    }
}

const char *Ipv6NdControlInfoDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6NdControlInfoDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        case FIELD_nextHop: return omnetpp::toAnyPtr(&pp->getNextHop()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6NdControlInfoDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6NdControlInfo *pp = omnetpp::fromAnyPtr<Ipv6NdControlInfo>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6NdControlInfo'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

