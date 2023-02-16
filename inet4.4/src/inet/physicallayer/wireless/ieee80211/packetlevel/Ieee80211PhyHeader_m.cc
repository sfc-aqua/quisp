//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211PhyHeader.msg.
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
#include "Ieee80211PhyHeader_m.h"

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

Register_Class(Ieee80211PhyPreamble)

Ieee80211PhyPreamble::Ieee80211PhyPreamble() : ::inet::FieldsChunk()
{
}

Ieee80211PhyPreamble::Ieee80211PhyPreamble(const Ieee80211PhyPreamble& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211PhyPreamble::~Ieee80211PhyPreamble()
{
}

Ieee80211PhyPreamble& Ieee80211PhyPreamble::operator=(const Ieee80211PhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211PhyPreamble::copy(const Ieee80211PhyPreamble& other)
{
}

void Ieee80211PhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
}

void Ieee80211PhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
}

class Ieee80211PhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211PhyPreambleDescriptor();
    virtual ~Ieee80211PhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211PhyPreambleDescriptor)

Ieee80211PhyPreambleDescriptor::Ieee80211PhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211PhyPreamble)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211PhyPreambleDescriptor::~Ieee80211PhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211PhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211PhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211PhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211PhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211PhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211PhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211PhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211PhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211PhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211PhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211PhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211PhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211PhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211PhyPreamble'", field);
    }
}

const char *Ieee80211PhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211PhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211PhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211PhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211PhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211PhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyPreamble'", field);
    }
}

const char *Ieee80211PhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211PhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211PhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211PhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyPreamble'", field);
    }
}

Register_Class(Ieee80211PhyHeader)

Ieee80211PhyHeader::Ieee80211PhyHeader() : ::inet::FieldsChunk()
{
}

Ieee80211PhyHeader::Ieee80211PhyHeader(const Ieee80211PhyHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee80211PhyHeader::~Ieee80211PhyHeader()
{
}

Ieee80211PhyHeader& Ieee80211PhyHeader::operator=(const Ieee80211PhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211PhyHeader::copy(const Ieee80211PhyHeader& other)
{
    this->lengthField = other.lengthField;
}

void Ieee80211PhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->lengthField);
}

void Ieee80211PhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->lengthField);
}

::inet::B Ieee80211PhyHeader::getLengthField() const
{
    return this->lengthField;
}

void Ieee80211PhyHeader::setLengthField(::inet::B lengthField)
{
    handleChange();
    this->lengthField = lengthField;
}

class Ieee80211PhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_lengthField,
    };
  public:
    Ieee80211PhyHeaderDescriptor();
    virtual ~Ieee80211PhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211PhyHeaderDescriptor)

Ieee80211PhyHeaderDescriptor::Ieee80211PhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211PhyHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee80211PhyHeaderDescriptor::~Ieee80211PhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211PhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211PhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211PhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211PhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211PhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211PhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lengthField
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211PhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lengthField",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211PhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "lengthField") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211PhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::B",    // FIELD_lengthField
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211PhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211PhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211PhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211PhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211PhyHeader'", field);
    }
}

const char *Ieee80211PhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211PhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: return unit2string(pp->getLengthField());
        default: return "";
    }
}

void Ieee80211PhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(B(string2long(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211PhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: return cValue(pp->getLengthField().get(),"B");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211PhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211PhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_lengthField: pp->setLengthField(B(value.intValueInUnit("B"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyHeader'", field);
    }
}

const char *Ieee80211PhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211PhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211PhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211PhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PhyHeader'", field);
    }
}

Register_Class(Ieee80211FhssPhyPreamble)

Ieee80211FhssPhyPreamble::Ieee80211FhssPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
    this->setChunkLength(b(96));
}

Ieee80211FhssPhyPreamble::Ieee80211FhssPhyPreamble(const Ieee80211FhssPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211FhssPhyPreamble::~Ieee80211FhssPhyPreamble()
{
}

Ieee80211FhssPhyPreamble& Ieee80211FhssPhyPreamble::operator=(const Ieee80211FhssPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211FhssPhyPreamble::copy(const Ieee80211FhssPhyPreamble& other)
{
}

void Ieee80211FhssPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211FhssPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211FhssPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211FhssPhyPreambleDescriptor();
    virtual ~Ieee80211FhssPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211FhssPhyPreambleDescriptor)

Ieee80211FhssPhyPreambleDescriptor::Ieee80211FhssPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211FhssPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211FhssPhyPreambleDescriptor::~Ieee80211FhssPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211FhssPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211FhssPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211FhssPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211FhssPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211FhssPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211FhssPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211FhssPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211FhssPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211FhssPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211FhssPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211FhssPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211FhssPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211FhssPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211FhssPhyPreamble'", field);
    }
}

const char *Ieee80211FhssPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211FhssPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211FhssPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211FhssPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211FhssPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211FhssPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyPreamble'", field);
    }
}

const char *Ieee80211FhssPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211FhssPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211FhssPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyPreamble'", field);
    }
}

Register_Class(Ieee80211FhssPhyHeader)

Ieee80211FhssPhyHeader::Ieee80211FhssPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
    this->setChunkLength(b(32));

}

Ieee80211FhssPhyHeader::Ieee80211FhssPhyHeader(const Ieee80211FhssPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211FhssPhyHeader::~Ieee80211FhssPhyHeader()
{
}

Ieee80211FhssPhyHeader& Ieee80211FhssPhyHeader::operator=(const Ieee80211FhssPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211FhssPhyHeader::copy(const Ieee80211FhssPhyHeader& other)
{
    this->plw = other.plw;
    this->psf = other.psf;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void Ieee80211FhssPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
    doParsimPacking(b,this->plw);
    doParsimPacking(b,this->psf);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void Ieee80211FhssPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->plw);
    doParsimUnpacking(b,this->psf);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

uint16_t Ieee80211FhssPhyHeader::getPlw() const
{
    return this->plw;
}

void Ieee80211FhssPhyHeader::setPlw(uint16_t plw)
{
    handleChange();
    this->plw = plw;
}

uint8_t Ieee80211FhssPhyHeader::getPsf() const
{
    return this->psf;
}

void Ieee80211FhssPhyHeader::setPsf(uint8_t psf)
{
    handleChange();
    this->psf = psf;
}

uint16_t Ieee80211FhssPhyHeader::getCrc() const
{
    return this->crc;
}

void Ieee80211FhssPhyHeader::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode Ieee80211FhssPhyHeader::getCrcMode() const
{
    return this->crcMode;
}

void Ieee80211FhssPhyHeader::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class Ieee80211FhssPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_plw,
        FIELD_psf,
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    Ieee80211FhssPhyHeaderDescriptor();
    virtual ~Ieee80211FhssPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211FhssPhyHeaderDescriptor)

Ieee80211FhssPhyHeaderDescriptor::Ieee80211FhssPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211FhssPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211FhssPhyHeaderDescriptor::~Ieee80211FhssPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211FhssPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211FhssPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211FhssPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211FhssPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211FhssPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211FhssPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_plw
        FD_ISEDITABLE,    // FIELD_psf
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211FhssPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "plw",
        "psf",
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211FhssPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "plw") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "psf") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211FhssPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_plw
        "uint8_t",    // FIELD_psf
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211FhssPhyHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211FhssPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211FhssPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211FhssPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211FhssPhyHeader'", field);
    }
}

const char *Ieee80211FhssPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211FhssPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_plw: return ulong2string(pp->getPlw());
        case FIELD_psf: return ulong2string(pp->getPsf());
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void Ieee80211FhssPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_plw: pp->setPlw(string2ulong(value)); break;
        case FIELD_psf: pp->setPsf(string2ulong(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211FhssPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_plw: return (omnetpp::intval_t)(pp->getPlw());
        case FIELD_psf: return (omnetpp::intval_t)(pp->getPsf());
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211FhssPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211FhssPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_plw: pp->setPlw(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_psf: pp->setPsf(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyHeader'", field);
    }
}

const char *Ieee80211FhssPhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211FhssPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211FhssPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211FhssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211FhssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211FhssPhyHeader'", field);
    }
}

Register_Class(Ieee80211IrPhyPreamble)

Ieee80211IrPhyPreamble::Ieee80211IrPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
}

Ieee80211IrPhyPreamble::Ieee80211IrPhyPreamble(const Ieee80211IrPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211IrPhyPreamble::~Ieee80211IrPhyPreamble()
{
}

Ieee80211IrPhyPreamble& Ieee80211IrPhyPreamble::operator=(const Ieee80211IrPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211IrPhyPreamble::copy(const Ieee80211IrPhyPreamble& other)
{
}

void Ieee80211IrPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211IrPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211IrPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211IrPhyPreambleDescriptor();
    virtual ~Ieee80211IrPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211IrPhyPreambleDescriptor)

Ieee80211IrPhyPreambleDescriptor::Ieee80211IrPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211IrPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211IrPhyPreambleDescriptor::~Ieee80211IrPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211IrPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211IrPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211IrPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211IrPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211IrPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211IrPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211IrPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211IrPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211IrPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211IrPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211IrPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211IrPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211IrPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211IrPhyPreamble'", field);
    }
}

const char *Ieee80211IrPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211IrPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211IrPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211IrPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211IrPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211IrPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyPreamble'", field);
    }
}

const char *Ieee80211IrPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211IrPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211IrPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyPreamble'", field);
    }
}

Register_Class(Ieee80211IrPhyHeader)

Ieee80211IrPhyHeader::Ieee80211IrPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
}

Ieee80211IrPhyHeader::Ieee80211IrPhyHeader(const Ieee80211IrPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211IrPhyHeader::~Ieee80211IrPhyHeader()
{
}

Ieee80211IrPhyHeader& Ieee80211IrPhyHeader::operator=(const Ieee80211IrPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211IrPhyHeader::copy(const Ieee80211IrPhyHeader& other)
{
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void Ieee80211IrPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void Ieee80211IrPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

uint16_t Ieee80211IrPhyHeader::getCrc() const
{
    return this->crc;
}

void Ieee80211IrPhyHeader::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode Ieee80211IrPhyHeader::getCrcMode() const
{
    return this->crcMode;
}

void Ieee80211IrPhyHeader::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class Ieee80211IrPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    Ieee80211IrPhyHeaderDescriptor();
    virtual ~Ieee80211IrPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211IrPhyHeaderDescriptor)

Ieee80211IrPhyHeaderDescriptor::Ieee80211IrPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211IrPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211IrPhyHeaderDescriptor::~Ieee80211IrPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211IrPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211IrPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211IrPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211IrPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211IrPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211IrPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211IrPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211IrPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211IrPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211IrPhyHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211IrPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211IrPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211IrPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211IrPhyHeader'", field);
    }
}

const char *Ieee80211IrPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211IrPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void Ieee80211IrPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211IrPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211IrPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211IrPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyHeader'", field);
    }
}

const char *Ieee80211IrPhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211IrPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211IrPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211IrPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211IrPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211IrPhyHeader'", field);
    }
}

Register_Class(Ieee80211DsssPhyPreamble)

Ieee80211DsssPhyPreamble::Ieee80211DsssPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
    this->setChunkLength(b(144));
}

Ieee80211DsssPhyPreamble::Ieee80211DsssPhyPreamble(const Ieee80211DsssPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211DsssPhyPreamble::~Ieee80211DsssPhyPreamble()
{
}

Ieee80211DsssPhyPreamble& Ieee80211DsssPhyPreamble::operator=(const Ieee80211DsssPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DsssPhyPreamble::copy(const Ieee80211DsssPhyPreamble& other)
{
}

void Ieee80211DsssPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211DsssPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211DsssPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211DsssPhyPreambleDescriptor();
    virtual ~Ieee80211DsssPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211DsssPhyPreambleDescriptor)

Ieee80211DsssPhyPreambleDescriptor::Ieee80211DsssPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211DsssPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211DsssPhyPreambleDescriptor::~Ieee80211DsssPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DsssPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DsssPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211DsssPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DsssPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DsssPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211DsssPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211DsssPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211DsssPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DsssPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211DsssPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211DsssPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211DsssPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DsssPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DsssPhyPreamble'", field);
    }
}

const char *Ieee80211DsssPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DsssPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211DsssPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211DsssPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DsssPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DsssPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyPreamble'", field);
    }
}

const char *Ieee80211DsssPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211DsssPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DsssPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyPreamble'", field);
    }
}

Register_Class(Ieee80211DsssPhyHeader)

Ieee80211DsssPhyHeader::Ieee80211DsssPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
    this->setChunkLength(b(32));

}

Ieee80211DsssPhyHeader::Ieee80211DsssPhyHeader(const Ieee80211DsssPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211DsssPhyHeader::~Ieee80211DsssPhyHeader()
{
}

Ieee80211DsssPhyHeader& Ieee80211DsssPhyHeader::operator=(const Ieee80211DsssPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211DsssPhyHeader::copy(const Ieee80211DsssPhyHeader& other)
{
    this->signal = other.signal;
    this->service = other.service;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
}

void Ieee80211DsssPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
    doParsimPacking(b,this->signal);
    doParsimPacking(b,this->service);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
}

void Ieee80211DsssPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->signal);
    doParsimUnpacking(b,this->service);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
}

uint8_t Ieee80211DsssPhyHeader::getSignal() const
{
    return this->signal;
}

void Ieee80211DsssPhyHeader::setSignal(uint8_t signal)
{
    handleChange();
    this->signal = signal;
}

uint8_t Ieee80211DsssPhyHeader::getService() const
{
    return this->service;
}

void Ieee80211DsssPhyHeader::setService(uint8_t service)
{
    handleChange();
    this->service = service;
}

uint16_t Ieee80211DsssPhyHeader::getCrc() const
{
    return this->crc;
}

void Ieee80211DsssPhyHeader::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode Ieee80211DsssPhyHeader::getCrcMode() const
{
    return this->crcMode;
}

void Ieee80211DsssPhyHeader::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

class Ieee80211DsssPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_signal,
        FIELD_service,
        FIELD_crc,
        FIELD_crcMode,
    };
  public:
    Ieee80211DsssPhyHeaderDescriptor();
    virtual ~Ieee80211DsssPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211DsssPhyHeaderDescriptor)

Ieee80211DsssPhyHeaderDescriptor::Ieee80211DsssPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211DsssPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211DsssPhyHeaderDescriptor::~Ieee80211DsssPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211DsssPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211DsssPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211DsssPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211DsssPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211DsssPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int Ieee80211DsssPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_signal
        FD_ISEDITABLE,    // FIELD_service
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211DsssPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "signal",
        "service",
        "crc",
        "crcMode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int Ieee80211DsssPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "signal") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "service") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211DsssPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_signal
        "uint8_t",    // FIELD_service
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211DsssPhyHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211DsssPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211DsssPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211DsssPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211DsssPhyHeader'", field);
    }
}

const char *Ieee80211DsssPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211DsssPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_signal: return ulong2string(pp->getSignal());
        case FIELD_service: return ulong2string(pp->getService());
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        default: return "";
    }
}

void Ieee80211DsssPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_signal: pp->setSignal(string2ulong(value)); break;
        case FIELD_service: pp->setService(string2ulong(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211DsssPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_signal: return (omnetpp::intval_t)(pp->getSignal());
        case FIELD_service: return (omnetpp::intval_t)(pp->getService());
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211DsssPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211DsssPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_signal: pp->setSignal(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_service: pp->setService(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyHeader'", field);
    }
}

const char *Ieee80211DsssPhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211DsssPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211DsssPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211DsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211DsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211DsssPhyHeader'", field);
    }
}

Register_Class(Ieee80211HrDsssPhyPreamble)

Ieee80211HrDsssPhyPreamble::Ieee80211HrDsssPhyPreamble() : ::inet::physicallayer::Ieee80211DsssPhyPreamble()
{
}

Ieee80211HrDsssPhyPreamble::Ieee80211HrDsssPhyPreamble(const Ieee80211HrDsssPhyPreamble& other) : ::inet::physicallayer::Ieee80211DsssPhyPreamble(other)
{
    copy(other);
}

Ieee80211HrDsssPhyPreamble::~Ieee80211HrDsssPhyPreamble()
{
}

Ieee80211HrDsssPhyPreamble& Ieee80211HrDsssPhyPreamble::operator=(const Ieee80211HrDsssPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211DsssPhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HrDsssPhyPreamble::copy(const Ieee80211HrDsssPhyPreamble& other)
{
}

void Ieee80211HrDsssPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211DsssPhyPreamble::parsimPack(b);
}

void Ieee80211HrDsssPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211DsssPhyPreamble::parsimUnpack(b);
}

class Ieee80211HrDsssPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211HrDsssPhyPreambleDescriptor();
    virtual ~Ieee80211HrDsssPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211HrDsssPhyPreambleDescriptor)

Ieee80211HrDsssPhyPreambleDescriptor::Ieee80211HrDsssPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211HrDsssPhyPreamble)), "inet::physicallayer::Ieee80211DsssPhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211HrDsssPhyPreambleDescriptor::~Ieee80211HrDsssPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211HrDsssPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211HrDsssPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211HrDsssPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211HrDsssPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211HrDsssPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211HrDsssPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211HrDsssPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211HrDsssPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211HrDsssPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211HrDsssPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211HrDsssPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211HrDsssPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211HrDsssPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211HrDsssPhyPreamble'", field);
    }
}

const char *Ieee80211HrDsssPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211HrDsssPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211HrDsssPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211HrDsssPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211HrDsssPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211HrDsssPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyPreamble'", field);
    }
}

const char *Ieee80211HrDsssPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211HrDsssPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211HrDsssPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyPreamble'", field);
    }
}

Register_Class(Ieee80211HrDsssPhyHeader)

Ieee80211HrDsssPhyHeader::Ieee80211HrDsssPhyHeader() : ::inet::physicallayer::Ieee80211DsssPhyHeader()
{
}

Ieee80211HrDsssPhyHeader::Ieee80211HrDsssPhyHeader(const Ieee80211HrDsssPhyHeader& other) : ::inet::physicallayer::Ieee80211DsssPhyHeader(other)
{
    copy(other);
}

Ieee80211HrDsssPhyHeader::~Ieee80211HrDsssPhyHeader()
{
}

Ieee80211HrDsssPhyHeader& Ieee80211HrDsssPhyHeader::operator=(const Ieee80211HrDsssPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211DsssPhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HrDsssPhyHeader::copy(const Ieee80211HrDsssPhyHeader& other)
{
}

void Ieee80211HrDsssPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211DsssPhyHeader::parsimPack(b);
}

void Ieee80211HrDsssPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211DsssPhyHeader::parsimUnpack(b);
}

class Ieee80211HrDsssPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211HrDsssPhyHeaderDescriptor();
    virtual ~Ieee80211HrDsssPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211HrDsssPhyHeaderDescriptor)

Ieee80211HrDsssPhyHeaderDescriptor::Ieee80211HrDsssPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211HrDsssPhyHeader)), "inet::physicallayer::Ieee80211DsssPhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211HrDsssPhyHeaderDescriptor::~Ieee80211HrDsssPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211HrDsssPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211HrDsssPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211HrDsssPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211HrDsssPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211HrDsssPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211HrDsssPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211HrDsssPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211HrDsssPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211HrDsssPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211HrDsssPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211HrDsssPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211HrDsssPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211HrDsssPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211HrDsssPhyHeader'", field);
    }
}

const char *Ieee80211HrDsssPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211HrDsssPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211HrDsssPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211HrDsssPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211HrDsssPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211HrDsssPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyHeader'", field);
    }
}

const char *Ieee80211HrDsssPhyHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211HrDsssPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211HrDsssPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HrDsssPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HrDsssPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HrDsssPhyHeader'", field);
    }
}

Register_Class(Ieee80211OfdmPhyPreamble)

Ieee80211OfdmPhyPreamble::Ieee80211OfdmPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
}

Ieee80211OfdmPhyPreamble::Ieee80211OfdmPhyPreamble(const Ieee80211OfdmPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211OfdmPhyPreamble::~Ieee80211OfdmPhyPreamble()
{
}

Ieee80211OfdmPhyPreamble& Ieee80211OfdmPhyPreamble::operator=(const Ieee80211OfdmPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211OfdmPhyPreamble::copy(const Ieee80211OfdmPhyPreamble& other)
{
}

void Ieee80211OfdmPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211OfdmPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211OfdmPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211OfdmPhyPreambleDescriptor();
    virtual ~Ieee80211OfdmPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211OfdmPhyPreambleDescriptor)

Ieee80211OfdmPhyPreambleDescriptor::Ieee80211OfdmPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211OfdmPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211OfdmPhyPreambleDescriptor::~Ieee80211OfdmPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211OfdmPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211OfdmPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211OfdmPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211OfdmPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211OfdmPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211OfdmPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211OfdmPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211OfdmPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211OfdmPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211OfdmPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211OfdmPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211OfdmPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211OfdmPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211OfdmPhyPreamble'", field);
    }
}

const char *Ieee80211OfdmPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211OfdmPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211OfdmPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211OfdmPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211OfdmPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211OfdmPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyPreamble'", field);
    }
}

const char *Ieee80211OfdmPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211OfdmPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211OfdmPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyPreamble'", field);
    }
}

Register_Class(Ieee80211OfdmPhyHeader)

Ieee80211OfdmPhyHeader::Ieee80211OfdmPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
    this->setChunkLength(B(5));

}

Ieee80211OfdmPhyHeader::Ieee80211OfdmPhyHeader(const Ieee80211OfdmPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211OfdmPhyHeader::~Ieee80211OfdmPhyHeader()
{
}

Ieee80211OfdmPhyHeader& Ieee80211OfdmPhyHeader::operator=(const Ieee80211OfdmPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211OfdmPhyHeader::copy(const Ieee80211OfdmPhyHeader& other)
{
    this->rate = other.rate;
    this->reserved = other.reserved;
    this->parity = other.parity;
    this->tail = other.tail;
    this->service = other.service;
}

void Ieee80211OfdmPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
    doParsimPacking(b,this->rate);
    doParsimPacking(b,this->reserved);
    doParsimPacking(b,this->parity);
    doParsimPacking(b,this->tail);
    doParsimPacking(b,this->service);
}

void Ieee80211OfdmPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->rate);
    doParsimUnpacking(b,this->reserved);
    doParsimUnpacking(b,this->parity);
    doParsimUnpacking(b,this->tail);
    doParsimUnpacking(b,this->service);
}

uint8_t Ieee80211OfdmPhyHeader::getRate() const
{
    return this->rate;
}

void Ieee80211OfdmPhyHeader::setRate(uint8_t rate)
{
    handleChange();
    this->rate = rate;
}

bool Ieee80211OfdmPhyHeader::getReserved() const
{
    return this->reserved;
}

void Ieee80211OfdmPhyHeader::setReserved(bool reserved)
{
    handleChange();
    this->reserved = reserved;
}

bool Ieee80211OfdmPhyHeader::getParity() const
{
    return this->parity;
}

void Ieee80211OfdmPhyHeader::setParity(bool parity)
{
    handleChange();
    this->parity = parity;
}

uint8_t Ieee80211OfdmPhyHeader::getTail() const
{
    return this->tail;
}

void Ieee80211OfdmPhyHeader::setTail(uint8_t tail)
{
    handleChange();
    this->tail = tail;
}

uint16_t Ieee80211OfdmPhyHeader::getService() const
{
    return this->service;
}

void Ieee80211OfdmPhyHeader::setService(uint16_t service)
{
    handleChange();
    this->service = service;
}

class Ieee80211OfdmPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rate,
        FIELD_reserved,
        FIELD_parity,
        FIELD_tail,
        FIELD_service,
    };
  public:
    Ieee80211OfdmPhyHeaderDescriptor();
    virtual ~Ieee80211OfdmPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211OfdmPhyHeaderDescriptor)

Ieee80211OfdmPhyHeaderDescriptor::Ieee80211OfdmPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211OfdmPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211OfdmPhyHeaderDescriptor::~Ieee80211OfdmPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211OfdmPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211OfdmPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211OfdmPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211OfdmPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211OfdmPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ieee80211OfdmPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_rate
        FD_ISEDITABLE,    // FIELD_reserved
        FD_ISEDITABLE,    // FIELD_parity
        FD_ISEDITABLE,    // FIELD_tail
        FD_ISEDITABLE,    // FIELD_service
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211OfdmPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rate",
        "reserved",
        "parity",
        "tail",
        "service",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ieee80211OfdmPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reserved") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "parity") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "tail") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "service") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211OfdmPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_rate
        "bool",    // FIELD_reserved
        "bool",    // FIELD_parity
        "uint8_t",    // FIELD_tail
        "uint16_t",    // FIELD_service
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211OfdmPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211OfdmPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211OfdmPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211OfdmPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211OfdmPhyHeader'", field);
    }
}

const char *Ieee80211OfdmPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211OfdmPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_rate: return ulong2string(pp->getRate());
        case FIELD_reserved: return bool2string(pp->getReserved());
        case FIELD_parity: return bool2string(pp->getParity());
        case FIELD_tail: return ulong2string(pp->getTail());
        case FIELD_service: return ulong2string(pp->getService());
        default: return "";
    }
}

void Ieee80211OfdmPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_rate: pp->setRate(string2ulong(value)); break;
        case FIELD_reserved: pp->setReserved(string2bool(value)); break;
        case FIELD_parity: pp->setParity(string2bool(value)); break;
        case FIELD_tail: pp->setTail(string2ulong(value)); break;
        case FIELD_service: pp->setService(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211OfdmPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_rate: return (omnetpp::intval_t)(pp->getRate());
        case FIELD_reserved: return pp->getReserved();
        case FIELD_parity: return pp->getParity();
        case FIELD_tail: return (omnetpp::intval_t)(pp->getTail());
        case FIELD_service: return (omnetpp::intval_t)(pp->getService());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211OfdmPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211OfdmPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        case FIELD_rate: pp->setRate(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_reserved: pp->setReserved(value.boolValue()); break;
        case FIELD_parity: pp->setParity(value.boolValue()); break;
        case FIELD_tail: pp->setTail(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_service: pp->setService(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyHeader'", field);
    }
}

const char *Ieee80211OfdmPhyHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211OfdmPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211OfdmPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211OfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211OfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211OfdmPhyHeader'", field);
    }
}

Register_Class(Ieee80211ErpOfdmPhyPreamble)

Ieee80211ErpOfdmPhyPreamble::Ieee80211ErpOfdmPhyPreamble() : ::inet::physicallayer::Ieee80211OfdmPhyPreamble()
{
}

Ieee80211ErpOfdmPhyPreamble::Ieee80211ErpOfdmPhyPreamble(const Ieee80211ErpOfdmPhyPreamble& other) : ::inet::physicallayer::Ieee80211OfdmPhyPreamble(other)
{
    copy(other);
}

Ieee80211ErpOfdmPhyPreamble::~Ieee80211ErpOfdmPhyPreamble()
{
}

Ieee80211ErpOfdmPhyPreamble& Ieee80211ErpOfdmPhyPreamble::operator=(const Ieee80211ErpOfdmPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211OfdmPhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ErpOfdmPhyPreamble::copy(const Ieee80211ErpOfdmPhyPreamble& other)
{
}

void Ieee80211ErpOfdmPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211OfdmPhyPreamble::parsimPack(b);
}

void Ieee80211ErpOfdmPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211OfdmPhyPreamble::parsimUnpack(b);
}

class Ieee80211ErpOfdmPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211ErpOfdmPhyPreambleDescriptor();
    virtual ~Ieee80211ErpOfdmPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211ErpOfdmPhyPreambleDescriptor)

Ieee80211ErpOfdmPhyPreambleDescriptor::Ieee80211ErpOfdmPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211ErpOfdmPhyPreamble)), "inet::physicallayer::Ieee80211OfdmPhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211ErpOfdmPhyPreambleDescriptor::~Ieee80211ErpOfdmPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ErpOfdmPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ErpOfdmPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211ErpOfdmPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211ErpOfdmPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ErpOfdmPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ErpOfdmPhyPreamble'", field);
    }
}

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211ErpOfdmPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ErpOfdmPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ErpOfdmPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyPreamble'", field);
    }
}

const char *Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211ErpOfdmPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ErpOfdmPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyPreamble'", field);
    }
}

Register_Class(Ieee80211ErpOfdmPhyHeader)

Ieee80211ErpOfdmPhyHeader::Ieee80211ErpOfdmPhyHeader() : ::inet::physicallayer::Ieee80211OfdmPhyHeader()
{
}

Ieee80211ErpOfdmPhyHeader::Ieee80211ErpOfdmPhyHeader(const Ieee80211ErpOfdmPhyHeader& other) : ::inet::physicallayer::Ieee80211OfdmPhyHeader(other)
{
    copy(other);
}

Ieee80211ErpOfdmPhyHeader::~Ieee80211ErpOfdmPhyHeader()
{
}

Ieee80211ErpOfdmPhyHeader& Ieee80211ErpOfdmPhyHeader::operator=(const Ieee80211ErpOfdmPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211OfdmPhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211ErpOfdmPhyHeader::copy(const Ieee80211ErpOfdmPhyHeader& other)
{
}

void Ieee80211ErpOfdmPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211OfdmPhyHeader::parsimPack(b);
}

void Ieee80211ErpOfdmPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211OfdmPhyHeader::parsimUnpack(b);
}

class Ieee80211ErpOfdmPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211ErpOfdmPhyHeaderDescriptor();
    virtual ~Ieee80211ErpOfdmPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211ErpOfdmPhyHeaderDescriptor)

Ieee80211ErpOfdmPhyHeaderDescriptor::Ieee80211ErpOfdmPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211ErpOfdmPhyHeader)), "inet::physicallayer::Ieee80211OfdmPhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211ErpOfdmPhyHeaderDescriptor::~Ieee80211ErpOfdmPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211ErpOfdmPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211ErpOfdmPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211ErpOfdmPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211ErpOfdmPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211ErpOfdmPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211ErpOfdmPhyHeader'", field);
    }
}

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211ErpOfdmPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211ErpOfdmPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211ErpOfdmPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyHeader'", field);
    }
}

const char *Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211ErpOfdmPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211ErpOfdmPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211ErpOfdmPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211ErpOfdmPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211ErpOfdmPhyHeader'", field);
    }
}

Register_Class(Ieee80211HtPhyPreamble)

Ieee80211HtPhyPreamble::Ieee80211HtPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
}

Ieee80211HtPhyPreamble::Ieee80211HtPhyPreamble(const Ieee80211HtPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211HtPhyPreamble::~Ieee80211HtPhyPreamble()
{
}

Ieee80211HtPhyPreamble& Ieee80211HtPhyPreamble::operator=(const Ieee80211HtPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HtPhyPreamble::copy(const Ieee80211HtPhyPreamble& other)
{
}

void Ieee80211HtPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211HtPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211HtPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211HtPhyPreambleDescriptor();
    virtual ~Ieee80211HtPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211HtPhyPreambleDescriptor)

Ieee80211HtPhyPreambleDescriptor::Ieee80211HtPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211HtPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211HtPhyPreambleDescriptor::~Ieee80211HtPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211HtPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211HtPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211HtPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211HtPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211HtPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211HtPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211HtPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211HtPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211HtPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211HtPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211HtPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211HtPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211HtPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211HtPhyPreamble'", field);
    }
}

const char *Ieee80211HtPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211HtPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211HtPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211HtPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211HtPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211HtPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyPreamble'", field);
    }
}

const char *Ieee80211HtPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211HtPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211HtPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyPreamble'", field);
    }
}

Register_Class(Ieee80211HtPhyHeader)

Ieee80211HtPhyHeader::Ieee80211HtPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
}

Ieee80211HtPhyHeader::Ieee80211HtPhyHeader(const Ieee80211HtPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211HtPhyHeader::~Ieee80211HtPhyHeader()
{
}

Ieee80211HtPhyHeader& Ieee80211HtPhyHeader::operator=(const Ieee80211HtPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211HtPhyHeader::copy(const Ieee80211HtPhyHeader& other)
{
}

void Ieee80211HtPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
}

void Ieee80211HtPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
}

class Ieee80211HtPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211HtPhyHeaderDescriptor();
    virtual ~Ieee80211HtPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211HtPhyHeaderDescriptor)

Ieee80211HtPhyHeaderDescriptor::Ieee80211HtPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211HtPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211HtPhyHeaderDescriptor::~Ieee80211HtPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211HtPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211HtPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211HtPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211HtPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211HtPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211HtPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211HtPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211HtPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211HtPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211HtPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211HtPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211HtPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211HtPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211HtPhyHeader'", field);
    }
}

const char *Ieee80211HtPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211HtPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211HtPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211HtPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211HtPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211HtPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyHeader'", field);
    }
}

const char *Ieee80211HtPhyHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211HtPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211HtPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211HtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211HtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211HtPhyHeader'", field);
    }
}

Register_Class(Ieee80211VhtPhyPreamble)

Ieee80211VhtPhyPreamble::Ieee80211VhtPhyPreamble() : ::inet::physicallayer::Ieee80211PhyPreamble()
{
}

Ieee80211VhtPhyPreamble::Ieee80211VhtPhyPreamble(const Ieee80211VhtPhyPreamble& other) : ::inet::physicallayer::Ieee80211PhyPreamble(other)
{
    copy(other);
}

Ieee80211VhtPhyPreamble::~Ieee80211VhtPhyPreamble()
{
}

Ieee80211VhtPhyPreamble& Ieee80211VhtPhyPreamble::operator=(const Ieee80211VhtPhyPreamble& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyPreamble::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211VhtPhyPreamble::copy(const Ieee80211VhtPhyPreamble& other)
{
}

void Ieee80211VhtPhyPreamble::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimPack(b);
}

void Ieee80211VhtPhyPreamble::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyPreamble::parsimUnpack(b);
}

class Ieee80211VhtPhyPreambleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211VhtPhyPreambleDescriptor();
    virtual ~Ieee80211VhtPhyPreambleDescriptor();

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

Register_ClassDescriptor(Ieee80211VhtPhyPreambleDescriptor)

Ieee80211VhtPhyPreambleDescriptor::Ieee80211VhtPhyPreambleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211VhtPhyPreamble)), "inet::physicallayer::Ieee80211PhyPreamble")
{
    propertyNames = nullptr;
}

Ieee80211VhtPhyPreambleDescriptor::~Ieee80211VhtPhyPreambleDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211VhtPhyPreambleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211VhtPhyPreamble *>(obj)!=nullptr;
}

const char **Ieee80211VhtPhyPreambleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211VhtPhyPreambleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211VhtPhyPreambleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211VhtPhyPreambleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211VhtPhyPreambleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211VhtPhyPreambleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211VhtPhyPreambleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211VhtPhyPreambleDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211VhtPhyPreambleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211VhtPhyPreambleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211VhtPhyPreambleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211VhtPhyPreamble'", field);
    }
}

const char *Ieee80211VhtPhyPreambleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211VhtPhyPreambleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211VhtPhyPreambleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyPreamble'", field);
    }
}

omnetpp::cValue Ieee80211VhtPhyPreambleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211VhtPhyPreamble' as cValue -- field index out of range?", field);
    }
}

void Ieee80211VhtPhyPreambleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyPreamble'", field);
    }
}

const char *Ieee80211VhtPhyPreambleDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211VhtPhyPreambleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211VhtPhyPreambleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyPreamble *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyPreamble>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyPreamble'", field);
    }
}

Register_Class(Ieee80211VhtPhyHeader)

Ieee80211VhtPhyHeader::Ieee80211VhtPhyHeader() : ::inet::physicallayer::Ieee80211PhyHeader()
{
}

Ieee80211VhtPhyHeader::Ieee80211VhtPhyHeader(const Ieee80211VhtPhyHeader& other) : ::inet::physicallayer::Ieee80211PhyHeader(other)
{
    copy(other);
}

Ieee80211VhtPhyHeader::~Ieee80211VhtPhyHeader()
{
}

Ieee80211VhtPhyHeader& Ieee80211VhtPhyHeader::operator=(const Ieee80211VhtPhyHeader& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Ieee80211PhyHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211VhtPhyHeader::copy(const Ieee80211VhtPhyHeader& other)
{
}

void Ieee80211VhtPhyHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimPack(b);
}

void Ieee80211VhtPhyHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Ieee80211PhyHeader::parsimUnpack(b);
}

class Ieee80211VhtPhyHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211VhtPhyHeaderDescriptor();
    virtual ~Ieee80211VhtPhyHeaderDescriptor();

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

Register_ClassDescriptor(Ieee80211VhtPhyHeaderDescriptor)

Ieee80211VhtPhyHeaderDescriptor::Ieee80211VhtPhyHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::Ieee80211VhtPhyHeader)), "inet::physicallayer::Ieee80211PhyHeader")
{
    propertyNames = nullptr;
}

Ieee80211VhtPhyHeaderDescriptor::~Ieee80211VhtPhyHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211VhtPhyHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211VhtPhyHeader *>(obj)!=nullptr;
}

const char **Ieee80211VhtPhyHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211VhtPhyHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211VhtPhyHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211VhtPhyHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211VhtPhyHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211VhtPhyHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211VhtPhyHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211VhtPhyHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211VhtPhyHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211VhtPhyHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211VhtPhyHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211VhtPhyHeader'", field);
    }
}

const char *Ieee80211VhtPhyHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211VhtPhyHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211VhtPhyHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyHeader'", field);
    }
}

omnetpp::cValue Ieee80211VhtPhyHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211VhtPhyHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee80211VhtPhyHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyHeader'", field);
    }
}

const char *Ieee80211VhtPhyHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211VhtPhyHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211VhtPhyHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211VhtPhyHeader *pp = omnetpp::fromAnyPtr<Ieee80211VhtPhyHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211VhtPhyHeader'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

