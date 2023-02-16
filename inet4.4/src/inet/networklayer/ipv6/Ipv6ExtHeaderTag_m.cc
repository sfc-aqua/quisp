//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv6/Ipv6ExtHeaderTag.msg.
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
#include "Ipv6ExtHeaderTag_m.h"

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

Register_Class(Ipv6ExtHeaderTagBase)

Ipv6ExtHeaderTagBase::Ipv6ExtHeaderTagBase() : ::inet::TagBase()
{
}

Ipv6ExtHeaderTagBase::Ipv6ExtHeaderTagBase(const Ipv6ExtHeaderTagBase& other) : ::inet::TagBase(other)
{
    copy(other);
}

Ipv6ExtHeaderTagBase::~Ipv6ExtHeaderTagBase()
{
    for (size_t i = 0; i < extensionHeader_arraysize; i++)
        delete this->extensionHeader[i];
    delete [] this->extensionHeader;
}

Ipv6ExtHeaderTagBase& Ipv6ExtHeaderTagBase::operator=(const Ipv6ExtHeaderTagBase& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6ExtHeaderTagBase::copy(const Ipv6ExtHeaderTagBase& other)
{
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

void Ipv6ExtHeaderTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    b->pack(extensionHeader_arraysize);
    doParsimArrayPacking(b,this->extensionHeader,extensionHeader_arraysize);
}

void Ipv6ExtHeaderTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    delete [] this->extensionHeader;
    b->unpack(extensionHeader_arraysize);
    if (extensionHeader_arraysize == 0) {
        this->extensionHeader = nullptr;
    } else {
        this->extensionHeader = new Ipv6ExtensionHeader *[extensionHeader_arraysize];
        doParsimArrayUnpacking(b,this->extensionHeader,extensionHeader_arraysize);
    }
}

size_t Ipv6ExtHeaderTagBase::getExtensionHeaderArraySize() const
{
    return extensionHeader_arraysize;
}

const Ipv6ExtensionHeader * Ipv6ExtHeaderTagBase::getExtensionHeader(size_t k) const
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    return this->extensionHeader[k];
}

void Ipv6ExtHeaderTagBase::setExtensionHeaderArraySize(size_t newSize)
{
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

void Ipv6ExtHeaderTagBase::setExtensionHeader(size_t k, Ipv6ExtensionHeader * extensionHeader)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    if (this->extensionHeader[k] != nullptr) throw omnetpp::cRuntimeError("setExtensionHeader(): a value is already set, remove it first with removeExtensionHeader()");
    this->extensionHeader[k] = extensionHeader;
    if (this->extensionHeader[k] != nullptr && this->extensionHeader[k]->isOwnedObject()) take((cOwnedObject*)this->extensionHeader[k]);
}

Ipv6ExtensionHeader * Ipv6ExtHeaderTagBase::removeExtensionHeader(size_t k)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
    Ipv6ExtensionHeader * retval = this->extensionHeader[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->extensionHeader[k] = nullptr;
    return retval;
}

void Ipv6ExtHeaderTagBase::insertExtensionHeader(size_t k, Ipv6ExtensionHeader * extensionHeader)
{
    if (k > extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
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

void Ipv6ExtHeaderTagBase::appendExtensionHeader(Ipv6ExtensionHeader * extensionHeader)
{
    insertExtensionHeader(extensionHeader_arraysize, extensionHeader);
}

void Ipv6ExtHeaderTagBase::eraseExtensionHeader(size_t k)
{
    if (k >= extensionHeader_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)extensionHeader_arraysize, (unsigned long)k);
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

class Ipv6ExtHeaderTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_extensionHeader,
    };
  public:
    Ipv6ExtHeaderTagBaseDescriptor();
    virtual ~Ipv6ExtHeaderTagBaseDescriptor();

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

Register_ClassDescriptor(Ipv6ExtHeaderTagBaseDescriptor)

Ipv6ExtHeaderTagBaseDescriptor::Ipv6ExtHeaderTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6ExtHeaderTagBase)), "inet::TagBase")
{
    propertyNames = nullptr;
}

Ipv6ExtHeaderTagBaseDescriptor::~Ipv6ExtHeaderTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6ExtHeaderTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6ExtHeaderTagBase *>(obj)!=nullptr;
}

const char **Ipv6ExtHeaderTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6ExtHeaderTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv6ExtHeaderTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_extensionHeader
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "extensionHeader",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6ExtHeaderTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "extensionHeader") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6ExtensionHeader",    // FIELD_extensionHeader
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6ExtHeaderTagBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_extensionHeader: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_extensionHeader:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv6ExtHeaderTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: return pp->getExtensionHeaderArraySize();
        default: return 0;
    }
}

void Ipv6ExtHeaderTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: pp->setExtensionHeaderArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6ExtHeaderTagBase'", field);
    }
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: { const Ipv6ExtensionHeader * value = pp->getExtensionHeader(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ipv6ExtHeaderTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: { auto obj = pp->getExtensionHeader(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void Ipv6ExtHeaderTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderTagBase'", field);
    }
}

omnetpp::cValue Ipv6ExtHeaderTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: return omnetpp::toAnyPtr(pp->getExtensionHeader(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6ExtHeaderTagBase' as cValue -- field index out of range?", field);
    }
}

void Ipv6ExtHeaderTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: pp->setExtensionHeader(i,omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderTagBase'", field);
    }
}

const char *Ipv6ExtHeaderTagBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv6ExtHeaderTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: return omnetpp::toAnyPtr(pp->getExtensionHeader(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6ExtHeaderTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderTagBase *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_extensionHeader: pp->setExtensionHeader(i,omnetpp::fromAnyPtr<Ipv6ExtensionHeader>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderTagBase'", field);
    }
}

Register_Class(Ipv6ExtHeaderReq)

Ipv6ExtHeaderReq::Ipv6ExtHeaderReq() : ::inet::Ipv6ExtHeaderTagBase()
{
}

Ipv6ExtHeaderReq::Ipv6ExtHeaderReq(const Ipv6ExtHeaderReq& other) : ::inet::Ipv6ExtHeaderTagBase(other)
{
    copy(other);
}

Ipv6ExtHeaderReq::~Ipv6ExtHeaderReq()
{
}

Ipv6ExtHeaderReq& Ipv6ExtHeaderReq::operator=(const Ipv6ExtHeaderReq& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtHeaderTagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6ExtHeaderReq::copy(const Ipv6ExtHeaderReq& other)
{
}

void Ipv6ExtHeaderReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtHeaderTagBase::parsimPack(b);
}

void Ipv6ExtHeaderReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtHeaderTagBase::parsimUnpack(b);
}

class Ipv6ExtHeaderReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6ExtHeaderReqDescriptor();
    virtual ~Ipv6ExtHeaderReqDescriptor();

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

Register_ClassDescriptor(Ipv6ExtHeaderReqDescriptor)

Ipv6ExtHeaderReqDescriptor::Ipv6ExtHeaderReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6ExtHeaderReq)), "inet::Ipv6ExtHeaderTagBase")
{
    propertyNames = nullptr;
}

Ipv6ExtHeaderReqDescriptor::~Ipv6ExtHeaderReqDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6ExtHeaderReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6ExtHeaderReq *>(obj)!=nullptr;
}

const char **Ipv6ExtHeaderReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6ExtHeaderReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6ExtHeaderReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6ExtHeaderReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6ExtHeaderReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6ExtHeaderReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6ExtHeaderReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6ExtHeaderReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6ExtHeaderReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6ExtHeaderReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6ExtHeaderReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6ExtHeaderReq'", field);
    }
}

const char *Ipv6ExtHeaderReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6ExtHeaderReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6ExtHeaderReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderReq'", field);
    }
}

omnetpp::cValue Ipv6ExtHeaderReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6ExtHeaderReq' as cValue -- field index out of range?", field);
    }
}

void Ipv6ExtHeaderReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderReq'", field);
    }
}

const char *Ipv6ExtHeaderReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6ExtHeaderReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6ExtHeaderReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderReq *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderReq'", field);
    }
}

Register_Class(Ipv6ExtHeaderInd)

Ipv6ExtHeaderInd::Ipv6ExtHeaderInd() : ::inet::Ipv6ExtHeaderTagBase()
{
}

Ipv6ExtHeaderInd::Ipv6ExtHeaderInd(const Ipv6ExtHeaderInd& other) : ::inet::Ipv6ExtHeaderTagBase(other)
{
    copy(other);
}

Ipv6ExtHeaderInd::~Ipv6ExtHeaderInd()
{
}

Ipv6ExtHeaderInd& Ipv6ExtHeaderInd::operator=(const Ipv6ExtHeaderInd& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6ExtHeaderTagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv6ExtHeaderInd::copy(const Ipv6ExtHeaderInd& other)
{
}

void Ipv6ExtHeaderInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6ExtHeaderTagBase::parsimPack(b);
}

void Ipv6ExtHeaderInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6ExtHeaderTagBase::parsimUnpack(b);
}

class Ipv6ExtHeaderIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv6ExtHeaderIndDescriptor();
    virtual ~Ipv6ExtHeaderIndDescriptor();

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

Register_ClassDescriptor(Ipv6ExtHeaderIndDescriptor)

Ipv6ExtHeaderIndDescriptor::Ipv6ExtHeaderIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6ExtHeaderInd)), "inet::Ipv6ExtHeaderTagBase")
{
    propertyNames = nullptr;
}

Ipv6ExtHeaderIndDescriptor::~Ipv6ExtHeaderIndDescriptor()
{
    delete[] propertyNames;
}

bool Ipv6ExtHeaderIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6ExtHeaderInd *>(obj)!=nullptr;
}

const char **Ipv6ExtHeaderIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv6ExtHeaderIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv6ExtHeaderIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv6ExtHeaderIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv6ExtHeaderIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv6ExtHeaderIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv6ExtHeaderIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv6ExtHeaderIndDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6ExtHeaderIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv6ExtHeaderIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv6ExtHeaderIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv6ExtHeaderInd'", field);
    }
}

const char *Ipv6ExtHeaderIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6ExtHeaderIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv6ExtHeaderIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderInd'", field);
    }
}

omnetpp::cValue Ipv6ExtHeaderIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv6ExtHeaderInd' as cValue -- field index out of range?", field);
    }
}

void Ipv6ExtHeaderIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderInd'", field);
    }
}

const char *Ipv6ExtHeaderIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv6ExtHeaderIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv6ExtHeaderIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv6ExtHeaderInd *pp = omnetpp::fromAnyPtr<Ipv6ExtHeaderInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv6ExtHeaderInd'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

