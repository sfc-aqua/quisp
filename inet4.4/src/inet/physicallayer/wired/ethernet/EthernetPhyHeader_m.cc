//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg.
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
#include "EthernetPhyHeader_m.h"

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
namespace physicallayer {

Register_Class(EthernetPhyHeaderBase)

EthernetPhyHeaderBase::EthernetPhyHeaderBase() : ::inet::FieldsChunk()
{
    this->setChunkLength(ETHERNET_PHY_HEADER_LEN);
}

EthernetPhyHeaderBase::EthernetPhyHeaderBase(const EthernetPhyHeaderBase& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

EthernetPhyHeaderBase::~EthernetPhyHeaderBase()
{
}

EthernetPhyHeaderBase& EthernetPhyHeaderBase::operator=(const EthernetPhyHeaderBase& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void EthernetPhyHeaderBase::copy(const EthernetPhyHeaderBase& other)
{
}

void EthernetPhyHeaderBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
}

void EthernetPhyHeaderBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
}

class EthernetPhyHeaderBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EthernetPhyHeaderBaseDescriptor();
    virtual ~EthernetPhyHeaderBaseDescriptor();

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

Register_ClassDescriptor(EthernetPhyHeaderBaseDescriptor)

EthernetPhyHeaderBaseDescriptor::EthernetPhyHeaderBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetPhyHeaderBase)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

EthernetPhyHeaderBaseDescriptor::~EthernetPhyHeaderBaseDescriptor()
{
    delete[] propertyNames;
}

bool EthernetPhyHeaderBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetPhyHeaderBase *>(obj)!=nullptr;
}

const char **EthernetPhyHeaderBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetPhyHeaderBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetPhyHeaderBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EthernetPhyHeaderBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EthernetPhyHeaderBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EthernetPhyHeaderBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetPhyHeaderBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EthernetPhyHeaderBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetPhyHeaderBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetPhyHeaderBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetPhyHeaderBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetPhyHeaderBase'", field);
    }
}

const char *EthernetPhyHeaderBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetPhyHeaderBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EthernetPhyHeaderBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeaderBase'", field);
    }
}

omnetpp::cValue EthernetPhyHeaderBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetPhyHeaderBase' as cValue -- field index out of range?", field);
    }
}

void EthernetPhyHeaderBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeaderBase'", field);
    }
}

const char *EthernetPhyHeaderBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EthernetPhyHeaderBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetPhyHeaderBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeaderBase *pp = omnetpp::fromAnyPtr<EthernetPhyHeaderBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeaderBase'", field);
    }
}

Register_Class(EthernetPhyHeader)

EthernetPhyHeader::EthernetPhyHeader() : ::inet::physicallayer::EthernetPhyHeaderBase()
{
}

EthernetPhyHeader::EthernetPhyHeader(const EthernetPhyHeader& other) : ::inet::physicallayer::EthernetPhyHeaderBase(other)
{
    copy(other);
}

EthernetPhyHeader::~EthernetPhyHeader()
{
}

EthernetPhyHeader& EthernetPhyHeader::operator=(const EthernetPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::EthernetPhyHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void EthernetPhyHeader::copy(const EthernetPhyHeader& other)
{
}

void EthernetPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::EthernetPhyHeaderBase::parsimPack(b);
}

void EthernetPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::EthernetPhyHeaderBase::parsimUnpack(b);
}

class EthernetPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EthernetPhyHeaderDescriptor();
    virtual ~EthernetPhyHeaderDescriptor();

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

Register_ClassDescriptor(EthernetPhyHeaderDescriptor)

EthernetPhyHeaderDescriptor::EthernetPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetPhyHeader)), "inet::physicallayer::EthernetPhyHeaderBase")
{
    propertyNames = nullptr;
}

EthernetPhyHeaderDescriptor::~EthernetPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool EthernetPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetPhyHeader *>(obj)!=nullptr;
}

const char **EthernetPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EthernetPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EthernetPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EthernetPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EthernetPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetPhyHeader'", field);
    }
}

const char *EthernetPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EthernetPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeader'", field);
    }
}

omnetpp::cValue EthernetPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetPhyHeader' as cValue -- field index out of range?", field);
    }
}

void EthernetPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeader'", field);
    }
}

const char *EthernetPhyHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EthernetPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetPhyHeader *pp = omnetpp::fromAnyPtr<EthernetPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetPhyHeader'", field);
    }
}

Register_Enum(inet::physicallayer::EthernetPhyHeaderType, (inet::physicallayer::EthernetPhyHeaderType::SFD, inet::physicallayer::EthernetPhyHeaderType::SMD_E, inet::physicallayer::EthernetPhyHeaderType::SMD_Verify, inet::physicallayer::EthernetPhyHeaderType::SMD_Respond, inet::physicallayer::EthernetPhyHeaderType::SMD_Sx, inet::physicallayer::EthernetPhyHeaderType::SMD_Cx));

Register_Class(EthernetFragmentPhyHeader)

EthernetFragmentPhyHeader::EthernetFragmentPhyHeader() : ::inet::physicallayer::EthernetPhyHeaderBase()
{
}

EthernetFragmentPhyHeader::EthernetFragmentPhyHeader(const EthernetFragmentPhyHeader& other) : ::inet::physicallayer::EthernetPhyHeaderBase(other)
{
    copy(other);
}

EthernetFragmentPhyHeader::~EthernetFragmentPhyHeader()
{
}

EthernetFragmentPhyHeader& EthernetFragmentPhyHeader::operator=(const EthernetFragmentPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::EthernetPhyHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void EthernetFragmentPhyHeader::copy(const EthernetFragmentPhyHeader& other)
{
    this->preambleType = other.preambleType;
    this->smdNumber = other.smdNumber;
    this->fragmentNumber = other.fragmentNumber;
}

void EthernetFragmentPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::EthernetPhyHeaderBase::parsimPack(b);
    doParsimPacking(b,this->preambleType);
    doParsimPacking(b,this->smdNumber);
    doParsimPacking(b,this->fragmentNumber);
}

void EthernetFragmentPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::EthernetPhyHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->preambleType);
    doParsimUnpacking(b,this->smdNumber);
    doParsimUnpacking(b,this->fragmentNumber);
}

EthernetPhyHeaderType EthernetFragmentPhyHeader::getPreambleType() const
{
    return this->preambleType;
}

void EthernetFragmentPhyHeader::setPreambleType(EthernetPhyHeaderType preambleType)
{
    handleChange();
    this->preambleType = preambleType;
}

uint8_t EthernetFragmentPhyHeader::getSmdNumber() const
{
    return this->smdNumber;
}

void EthernetFragmentPhyHeader::setSmdNumber(uint8_t smdNumber)
{
    handleChange();
    this->smdNumber = smdNumber;
}

uint8_t EthernetFragmentPhyHeader::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void EthernetFragmentPhyHeader::setFragmentNumber(uint8_t fragmentNumber)
{
    handleChange();
    this->fragmentNumber = fragmentNumber;
}

class EthernetFragmentPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_preambleType,
        FIELD_smdNumber,
        FIELD_fragmentNumber,
    };
  public:
    EthernetFragmentPhyHeaderDescriptor();
    virtual ~EthernetFragmentPhyHeaderDescriptor();

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

Register_ClassDescriptor(EthernetFragmentPhyHeaderDescriptor)

EthernetFragmentPhyHeaderDescriptor::EthernetFragmentPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetFragmentPhyHeader)), "inet::physicallayer::EthernetPhyHeaderBase")
{
    propertyNames = nullptr;
}

EthernetFragmentPhyHeaderDescriptor::~EthernetFragmentPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool EthernetFragmentPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetFragmentPhyHeader *>(obj)!=nullptr;
}

const char **EthernetFragmentPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetFragmentPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetFragmentPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int EthernetFragmentPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_preambleType
        FD_ISEDITABLE,    // FIELD_smdNumber
        FD_ISEDITABLE,    // FIELD_fragmentNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *EthernetFragmentPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "preambleType",
        "smdNumber",
        "fragmentNumber",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int EthernetFragmentPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "preambleType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "smdNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "fragmentNumber") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetFragmentPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::physicallayer::EthernetPhyHeaderType",    // FIELD_preambleType
        "uint8_t",    // FIELD_smdNumber
        "uint8_t",    // FIELD_fragmentNumber
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **EthernetFragmentPhyHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_preambleType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *EthernetFragmentPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_preambleType:
            if (!strcmp(propertyName, "enum")) return "inet::physicallayer::EthernetPhyHeaderType";
            return nullptr;
        default: return nullptr;
    }
}

int EthernetFragmentPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetFragmentPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetFragmentPhyHeader'", field);
    }
}

const char *EthernetFragmentPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetFragmentPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_preambleType: return enum2string(pp->getPreambleType(), "inet::physicallayer::EthernetPhyHeaderType");
        case FIELD_smdNumber: return ulong2string(pp->getSmdNumber());
        case FIELD_fragmentNumber: return ulong2string(pp->getFragmentNumber());
        default: return "";
    }
}

void EthernetFragmentPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_smdNumber: pp->setSmdNumber(string2ulong(value)); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFragmentPhyHeader'", field);
    }
}

omnetpp::cValue EthernetFragmentPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_preambleType: return static_cast<int>(pp->getPreambleType());
        case FIELD_smdNumber: return (omnetpp::intval_t)(pp->getSmdNumber());
        case FIELD_fragmentNumber: return (omnetpp::intval_t)(pp->getFragmentNumber());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetFragmentPhyHeader' as cValue -- field index out of range?", field);
    }
}

void EthernetFragmentPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_smdNumber: pp->setSmdNumber(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_fragmentNumber: pp->setFragmentNumber(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFragmentPhyHeader'", field);
    }
}

const char *EthernetFragmentPhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EthernetFragmentPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetFragmentPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFragmentPhyHeader *pp = omnetpp::fromAnyPtr<EthernetFragmentPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFragmentPhyHeader'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

