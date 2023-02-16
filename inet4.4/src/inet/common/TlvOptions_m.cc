//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/TlvOptions.msg.
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
#include "TlvOptions_m.h"

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

Register_Class(TlvOptionBase)

TlvOptionBase::TlvOptionBase() : ::omnetpp::cObject()
{
}

TlvOptionBase::TlvOptionBase(const TlvOptionBase& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

TlvOptionBase::~TlvOptionBase()
{
}

TlvOptionBase& TlvOptionBase::operator=(const TlvOptionBase& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void TlvOptionBase::copy(const TlvOptionBase& other)
{
    this->type = other.type;
    this->length = other.length;
}

void TlvOptionBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->length);
}

void TlvOptionBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->length);
}

short TlvOptionBase::getType() const
{
    return this->type;
}

void TlvOptionBase::setType(short type)
{
    this->type = type;
}

short TlvOptionBase::getLength() const
{
    return this->length;
}

void TlvOptionBase::setLength(short length)
{
    this->length = length;
}

class TlvOptionBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_type,
        FIELD_length,
    };
  public:
    TlvOptionBaseDescriptor();
    virtual ~TlvOptionBaseDescriptor();

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

Register_ClassDescriptor(TlvOptionBaseDescriptor)

TlvOptionBaseDescriptor::TlvOptionBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TlvOptionBase)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TlvOptionBaseDescriptor::~TlvOptionBaseDescriptor()
{
    delete[] propertyNames;
}

bool TlvOptionBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TlvOptionBase *>(obj)!=nullptr;
}

const char **TlvOptionBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TlvOptionBaseDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TlvOptionBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TlvOptionBaseDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TlvOptionBaseDescriptor::getFieldName(int field) const
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
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TlvOptionBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TlvOptionBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_type
        "short",    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TlvOptionBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *TlvOptionBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TlvOptionBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TlvOptionBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TlvOptionBase'", field);
    }
}

const char *TlvOptionBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TlvOptionBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_type: return long2string(pp->getType());
        case FIELD_length: return long2string(pp->getLength());
        default: return "";
    }
}

void TlvOptionBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2long(value)); break;
        case FIELD_length: pp->setLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionBase'", field);
    }
}

omnetpp::cValue TlvOptionBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_type: return pp->getType();
        case FIELD_length: return pp->getLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TlvOptionBase' as cValue -- field index out of range?", field);
    }
}

void TlvOptionBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionBase'", field);
    }
}

const char *TlvOptionBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TlvOptionBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TlvOptionBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionBase *pp = omnetpp::fromAnyPtr<TlvOptionBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionBase'", field);
    }
}

Register_Class(TlvOptionRaw)

TlvOptionRaw::TlvOptionRaw() : ::inet::TlvOptionBase()
{
}

TlvOptionRaw::TlvOptionRaw(const TlvOptionRaw& other) : ::inet::TlvOptionBase(other)
{
    copy(other);
}

TlvOptionRaw::~TlvOptionRaw()
{
    delete [] this->bytes;
}

TlvOptionRaw& TlvOptionRaw::operator=(const TlvOptionRaw& other)
{
    if (this == &other) return *this;
    ::inet::TlvOptionBase::operator=(other);
    copy(other);
    return *this;
}

void TlvOptionRaw::copy(const TlvOptionRaw& other)
{
    delete [] this->bytes;
    this->bytes = (other.bytes_arraysize==0) ? nullptr : new char[other.bytes_arraysize];
    bytes_arraysize = other.bytes_arraysize;
    for (size_t i = 0; i < bytes_arraysize; i++) {
        this->bytes[i] = other.bytes[i];
    }
}

void TlvOptionRaw::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TlvOptionBase::parsimPack(b);
    b->pack(bytes_arraysize);
    doParsimArrayPacking(b,this->bytes,bytes_arraysize);
}

void TlvOptionRaw::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TlvOptionBase::parsimUnpack(b);
    delete [] this->bytes;
    b->unpack(bytes_arraysize);
    if (bytes_arraysize == 0) {
        this->bytes = nullptr;
    } else {
        this->bytes = new char[bytes_arraysize];
        doParsimArrayUnpacking(b,this->bytes,bytes_arraysize);
    }
}

size_t TlvOptionRaw::getBytesArraySize() const
{
    return bytes_arraysize;
}

char TlvOptionRaw::getBytes(size_t k) const
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    return this->bytes[k];
}

void TlvOptionRaw::setBytesArraySize(size_t newSize)
{
    char *bytes2 = (newSize==0) ? nullptr : new char[newSize];
    size_t minSize = bytes_arraysize < newSize ? bytes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        bytes2[i] = this->bytes[i];
    for (size_t i = minSize; i < newSize; i++)
        bytes2[i] = 0;
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

void TlvOptionRaw::setBytes(size_t k, char bytes)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    this->bytes[k] = bytes;
}

void TlvOptionRaw::insertBytes(size_t k, char bytes)
{
    if (k > bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    size_t newSize = bytes_arraysize + 1;
    char *bytes2 = new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bytes2[i] = this->bytes[i];
    bytes2[k] = bytes;
    for (i = k + 1; i < newSize; i++)
        bytes2[i] = this->bytes[i-1];
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

void TlvOptionRaw::appendBytes(char bytes)
{
    insertBytes(bytes_arraysize, bytes);
}

void TlvOptionRaw::eraseBytes(size_t k)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    size_t newSize = bytes_arraysize - 1;
    char *bytes2 = (newSize == 0) ? nullptr : new char[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bytes2[i] = this->bytes[i];
    for (i = k; i < newSize; i++)
        bytes2[i] = this->bytes[i+1];
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

class TlvOptionRawDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_bytes,
    };
  public:
    TlvOptionRawDescriptor();
    virtual ~TlvOptionRawDescriptor();

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

Register_ClassDescriptor(TlvOptionRawDescriptor)

TlvOptionRawDescriptor::TlvOptionRawDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TlvOptionRaw)), "inet::TlvOptionBase")
{
    propertyNames = nullptr;
}

TlvOptionRawDescriptor::~TlvOptionRawDescriptor()
{
    delete[] propertyNames;
}

bool TlvOptionRawDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TlvOptionRaw *>(obj)!=nullptr;
}

const char **TlvOptionRawDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TlvOptionRawDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TlvOptionRawDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TlvOptionRawDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_bytes
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TlvOptionRawDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "bytes",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TlvOptionRawDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "bytes") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TlvOptionRawDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "char",    // FIELD_bytes
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TlvOptionRawDescriptor::getFieldPropertyNames(int field) const
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

const char *TlvOptionRawDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TlvOptionRawDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return pp->getBytesArraySize();
        default: return 0;
    }
}

void TlvOptionRawDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TlvOptionRaw'", field);
    }
}

const char *TlvOptionRawDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TlvOptionRawDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return long2string(pp->getBytes(i));
        default: return "";
    }
}

void TlvOptionRawDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionRaw'", field);
    }
}

omnetpp::cValue TlvOptionRawDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return pp->getBytes(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TlvOptionRaw' as cValue -- field index out of range?", field);
    }
}

void TlvOptionRawDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,omnetpp::checked_int_cast<char>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionRaw'", field);
    }
}

const char *TlvOptionRawDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TlvOptionRawDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TlvOptionRawDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptionRaw *pp = omnetpp::fromAnyPtr<TlvOptionRaw>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptionRaw'", field);
    }
}

Register_Class(TlvOptions)

TlvOptions::TlvOptions() : ::omnetpp::cObject()
{
}

TlvOptions::TlvOptions(const TlvOptions& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

TlvOptions::~TlvOptions()
{
    for (size_t i = 0; i < tlvOption_arraysize; i++)
        delete this->tlvOption[i];
    delete [] this->tlvOption;
}

TlvOptions& TlvOptions::operator=(const TlvOptions& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void TlvOptions::copy(const TlvOptions& other)
{
    for (size_t i = 0; i < tlvOption_arraysize; i++)
        delete this->tlvOption[i];
    delete [] this->tlvOption;
    this->tlvOption = (other.tlvOption_arraysize==0) ? nullptr : new TlvOptionBase *[other.tlvOption_arraysize];
    tlvOption_arraysize = other.tlvOption_arraysize;
    for (size_t i = 0; i < tlvOption_arraysize; i++) {
        this->tlvOption[i] = other.tlvOption[i];
        if (this->tlvOption[i] != nullptr) {
            this->tlvOption[i] = this->tlvOption[i]->dup();
        }
    }
}

void TlvOptions::parsimPack(omnetpp::cCommBuffer *b) const
{
    b->pack(tlvOption_arraysize);
    doParsimArrayPacking(b,this->tlvOption,tlvOption_arraysize);
}

void TlvOptions::parsimUnpack(omnetpp::cCommBuffer *b)
{
    delete [] this->tlvOption;
    b->unpack(tlvOption_arraysize);
    if (tlvOption_arraysize == 0) {
        this->tlvOption = nullptr;
    } else {
        this->tlvOption = new TlvOptionBase *[tlvOption_arraysize];
        doParsimArrayUnpacking(b,this->tlvOption,tlvOption_arraysize);
    }
}

size_t TlvOptions::getTlvOptionArraySize() const
{
    return tlvOption_arraysize;
}

const TlvOptionBase * TlvOptions::getTlvOption(size_t k) const
{
    if (k >= tlvOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tlvOption_arraysize, (unsigned long)k);
    return this->tlvOption[k];
}

void TlvOptions::setTlvOptionArraySize(size_t newSize)
{
    TlvOptionBase * *tlvOption2 = (newSize==0) ? nullptr : new TlvOptionBase *[newSize];
    size_t minSize = tlvOption_arraysize < newSize ? tlvOption_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        tlvOption2[i] = this->tlvOption[i];
    for (size_t i = minSize; i < newSize; i++)
        tlvOption2[i] = nullptr;
    for (size_t i = newSize; i < tlvOption_arraysize; i++)
        delete tlvOption[i];
    delete [] this->tlvOption;
    this->tlvOption = tlvOption2;
    tlvOption_arraysize = newSize;
}

void TlvOptions::setTlvOption(size_t k, TlvOptionBase * tlvOption)
{
    if (k >= tlvOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tlvOption_arraysize, (unsigned long)k);
    if (this->tlvOption[k] != nullptr) throw omnetpp::cRuntimeError("setTlvOption(): a value is already set, remove it first with removeTlvOption()");
    this->tlvOption[k] = tlvOption;
    if (this->tlvOption[k] != nullptr && this->tlvOption[k]->isOwnedObject()) take((cOwnedObject*)this->tlvOption[k]);
}

TlvOptionBase * TlvOptions::removeTlvOption(size_t k)
{
    if (k >= tlvOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tlvOption_arraysize, (unsigned long)k);
    TlvOptionBase * retval = this->tlvOption[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->tlvOption[k] = nullptr;
    return retval;
}

void TlvOptions::insertTlvOption(size_t k, TlvOptionBase * tlvOption)
{
    if (k > tlvOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tlvOption_arraysize, (unsigned long)k);
    size_t newSize = tlvOption_arraysize + 1;
    TlvOptionBase * *tlvOption2 = new TlvOptionBase *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tlvOption2[i] = this->tlvOption[i];
    tlvOption2[k] = tlvOption;
    if (tlvOption2[k] != nullptr && tlvOption2[k]->isOwnedObject()) take((cOwnedObject*)tlvOption2[k]);
    for (i = k + 1; i < newSize; i++)
        tlvOption2[i] = this->tlvOption[i-1];
    delete [] this->tlvOption;
    this->tlvOption = tlvOption2;
    tlvOption_arraysize = newSize;
}

void TlvOptions::appendTlvOption(TlvOptionBase * tlvOption)
{
    insertTlvOption(tlvOption_arraysize, tlvOption);
}

void TlvOptions::eraseTlvOption(size_t k)
{
    if (k >= tlvOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)tlvOption_arraysize, (unsigned long)k);
    size_t newSize = tlvOption_arraysize - 1;
    TlvOptionBase * *tlvOption2 = (newSize == 0) ? nullptr : new TlvOptionBase *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        tlvOption2[i] = this->tlvOption[i];
    for (i = k; i < newSize; i++)
        tlvOption2[i] = this->tlvOption[i+1];
    if (this->tlvOption[k] != nullptr && this->tlvOption[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->tlvOption[k]); else delete this->tlvOption[k];
    delete [] this->tlvOption;
    this->tlvOption = tlvOption2;
    tlvOption_arraysize = newSize;
}

class TlvOptionsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_tlvOption,
    };
  public:
    TlvOptionsDescriptor();
    virtual ~TlvOptionsDescriptor();

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

Register_ClassDescriptor(TlvOptionsDescriptor)

TlvOptionsDescriptor::TlvOptionsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TlvOptions)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TlvOptionsDescriptor::~TlvOptionsDescriptor()
{
    delete[] propertyNames;
}

bool TlvOptionsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TlvOptions *>(obj)!=nullptr;
}

const char **TlvOptionsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TlvOptionsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TlvOptionsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TlvOptionsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_tlvOption
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TlvOptionsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "tlvOption",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TlvOptionsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "tlvOption") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TlvOptionsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TlvOptionBase",    // FIELD_tlvOption
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TlvOptionsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOption: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TlvOptionsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOption:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int TlvOptionsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: return pp->getTlvOptionArraySize();
        default: return 0;
    }
}

void TlvOptionsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: pp->setTlvOptionArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TlvOptions'", field);
    }
}

const char *TlvOptionsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: { const TlvOptionBase * value = pp->getTlvOption(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string TlvOptionsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: { auto obj = pp->getTlvOption(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void TlvOptionsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptions'", field);
    }
}

omnetpp::cValue TlvOptionsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: return omnetpp::toAnyPtr(pp->getTlvOption(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TlvOptions' as cValue -- field index out of range?", field);
    }
}

void TlvOptionsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: pp->setTlvOption(i,omnetpp::fromAnyPtr<TlvOptionBase>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptions'", field);
    }
}

const char *TlvOptionsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_tlvOption: return omnetpp::opp_typename(typeid(TlvOptionBase));
        default: return nullptr;
    };
}

omnetpp::any_ptr TlvOptionsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: return omnetpp::toAnyPtr(pp->getTlvOption(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TlvOptionsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TlvOptions *pp = omnetpp::fromAnyPtr<TlvOptions>(object); (void)pp;
    switch (field) {
        case FIELD_tlvOption: pp->setTlvOption(i,omnetpp::fromAnyPtr<TlvOptionBase>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TlvOptions'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

