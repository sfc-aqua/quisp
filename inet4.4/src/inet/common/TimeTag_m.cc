//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/TimeTag.msg.
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
#include "TimeTag_m.h"

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

Register_Class(CreationTimeTag)

CreationTimeTag::CreationTimeTag() : ::inet::TagBase()
{
}

CreationTimeTag::CreationTimeTag(const CreationTimeTag& other) : ::inet::TagBase(other)
{
    copy(other);
}

CreationTimeTag::~CreationTimeTag()
{
}

CreationTimeTag& CreationTimeTag::operator=(const CreationTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void CreationTimeTag::copy(const CreationTimeTag& other)
{
    this->creationTime = other.creationTime;
}

void CreationTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->creationTime);
}

void CreationTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->creationTime);
}

::omnetpp::simtime_t CreationTimeTag::getCreationTime() const
{
    return this->creationTime;
}

void CreationTimeTag::setCreationTime(::omnetpp::simtime_t creationTime)
{
    this->creationTime = creationTime;
}

class CreationTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_creationTime,
    };
  public:
    CreationTimeTagDescriptor();
    virtual ~CreationTimeTagDescriptor();

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

Register_ClassDescriptor(CreationTimeTagDescriptor)

CreationTimeTagDescriptor::CreationTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::CreationTimeTag)), "inet::TagBase")
{
    propertyNames = nullptr;
}

CreationTimeTagDescriptor::~CreationTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool CreationTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CreationTimeTag *>(obj)!=nullptr;
}

const char **CreationTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CreationTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CreationTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int CreationTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_creationTime
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *CreationTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "creationTime",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int CreationTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "creationTime") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *CreationTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_creationTime
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **CreationTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *CreationTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CreationTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CreationTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CreationTimeTag'", field);
    }
}

const char *CreationTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CreationTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return simtime2string(pp->getCreationTime());
        default: return "";
    }
}

void CreationTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CreationTimeTag'", field);
    }
}

omnetpp::cValue CreationTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return pp->getCreationTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CreationTimeTag' as cValue -- field index out of range?", field);
    }
}

void CreationTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CreationTimeTag'", field);
    }
}

const char *CreationTimeTagDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CreationTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CreationTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CreationTimeTag *pp = omnetpp::fromAnyPtr<CreationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CreationTimeTag'", field);
    }
}

Register_Class(ResidenceTimeTag)

ResidenceTimeTag::ResidenceTimeTag() : ::inet::TagBase()
{
}

ResidenceTimeTag::ResidenceTimeTag(const ResidenceTimeTag& other) : ::inet::TagBase(other)
{
    copy(other);
}

ResidenceTimeTag::~ResidenceTimeTag()
{
}

ResidenceTimeTag& ResidenceTimeTag::operator=(const ResidenceTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void ResidenceTimeTag::copy(const ResidenceTimeTag& other)
{
    this->startTime = other.startTime;
    this->endTime = other.endTime;
}

void ResidenceTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->endTime);
}

void ResidenceTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->endTime);
}

::omnetpp::simtime_t ResidenceTimeTag::getStartTime() const
{
    return this->startTime;
}

void ResidenceTimeTag::setStartTime(::omnetpp::simtime_t startTime)
{
    this->startTime = startTime;
}

::omnetpp::simtime_t ResidenceTimeTag::getEndTime() const
{
    return this->endTime;
}

void ResidenceTimeTag::setEndTime(::omnetpp::simtime_t endTime)
{
    this->endTime = endTime;
}

class ResidenceTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_startTime,
        FIELD_endTime,
    };
  public:
    ResidenceTimeTagDescriptor();
    virtual ~ResidenceTimeTagDescriptor();

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

Register_ClassDescriptor(ResidenceTimeTagDescriptor)

ResidenceTimeTagDescriptor::ResidenceTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ResidenceTimeTag)), "inet::TagBase")
{
    propertyNames = nullptr;
}

ResidenceTimeTagDescriptor::~ResidenceTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool ResidenceTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ResidenceTimeTag *>(obj)!=nullptr;
}

const char **ResidenceTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ResidenceTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ResidenceTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int ResidenceTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_startTime
        FD_ISEDITABLE,    // FIELD_endTime
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *ResidenceTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "startTime",
        "endTime",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int ResidenceTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "startTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "endTime") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *ResidenceTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_startTime
        "omnetpp::simtime_t",    // FIELD_endTime
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **ResidenceTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *ResidenceTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ResidenceTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ResidenceTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ResidenceTimeTag'", field);
    }
}

const char *ResidenceTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ResidenceTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return simtime2string(pp->getStartTime());
        case FIELD_endTime: return simtime2string(pp->getEndTime());
        default: return "";
    }
}

void ResidenceTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: pp->setStartTime(string2simtime(value)); break;
        case FIELD_endTime: pp->setEndTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResidenceTimeTag'", field);
    }
}

omnetpp::cValue ResidenceTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return pp->getStartTime().dbl();
        case FIELD_endTime: return pp->getEndTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ResidenceTimeTag' as cValue -- field index out of range?", field);
    }
}

void ResidenceTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: pp->setStartTime(value.doubleValue()); break;
        case FIELD_endTime: pp->setEndTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResidenceTimeTag'", field);
    }
}

const char *ResidenceTimeTagDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ResidenceTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ResidenceTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ResidenceTimeTag *pp = omnetpp::fromAnyPtr<ResidenceTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ResidenceTimeTag'", field);
    }
}

Register_Class(TimeTagBase)

TimeTagBase::TimeTagBase() : ::inet::TagBase()
{
}

TimeTagBase::TimeTagBase(const TimeTagBase& other) : ::inet::TagBase(other)
{
    copy(other);
}

TimeTagBase::~TimeTagBase()
{
    delete [] this->flowNames;
    delete [] this->bitTotalTimes;
    delete [] this->packetTotalTimes;
}

TimeTagBase& TimeTagBase::operator=(const TimeTagBase& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void TimeTagBase::copy(const TimeTagBase& other)
{
    delete [] this->flowNames;
    this->flowNames = (other.flowNames_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.flowNames_arraysize];
    flowNames_arraysize = other.flowNames_arraysize;
    for (size_t i = 0; i < flowNames_arraysize; i++) {
        this->flowNames[i] = other.flowNames[i];
    }
    delete [] this->bitTotalTimes;
    this->bitTotalTimes = (other.bitTotalTimes_arraysize==0) ? nullptr : new ::omnetpp::simtime_t[other.bitTotalTimes_arraysize];
    bitTotalTimes_arraysize = other.bitTotalTimes_arraysize;
    for (size_t i = 0; i < bitTotalTimes_arraysize; i++) {
        this->bitTotalTimes[i] = other.bitTotalTimes[i];
    }
    delete [] this->packetTotalTimes;
    this->packetTotalTimes = (other.packetTotalTimes_arraysize==0) ? nullptr : new ::omnetpp::simtime_t[other.packetTotalTimes_arraysize];
    packetTotalTimes_arraysize = other.packetTotalTimes_arraysize;
    for (size_t i = 0; i < packetTotalTimes_arraysize; i++) {
        this->packetTotalTimes[i] = other.packetTotalTimes[i];
    }
}

void TimeTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    b->pack(flowNames_arraysize);
    doParsimArrayPacking(b,this->flowNames,flowNames_arraysize);
    b->pack(bitTotalTimes_arraysize);
    doParsimArrayPacking(b,this->bitTotalTimes,bitTotalTimes_arraysize);
    b->pack(packetTotalTimes_arraysize);
    doParsimArrayPacking(b,this->packetTotalTimes,packetTotalTimes_arraysize);
}

void TimeTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    delete [] this->flowNames;
    b->unpack(flowNames_arraysize);
    if (flowNames_arraysize == 0) {
        this->flowNames = nullptr;
    } else {
        this->flowNames = new ::omnetpp::opp_string[flowNames_arraysize];
        doParsimArrayUnpacking(b,this->flowNames,flowNames_arraysize);
    }
    delete [] this->bitTotalTimes;
    b->unpack(bitTotalTimes_arraysize);
    if (bitTotalTimes_arraysize == 0) {
        this->bitTotalTimes = nullptr;
    } else {
        this->bitTotalTimes = new ::omnetpp::simtime_t[bitTotalTimes_arraysize];
        doParsimArrayUnpacking(b,this->bitTotalTimes,bitTotalTimes_arraysize);
    }
    delete [] this->packetTotalTimes;
    b->unpack(packetTotalTimes_arraysize);
    if (packetTotalTimes_arraysize == 0) {
        this->packetTotalTimes = nullptr;
    } else {
        this->packetTotalTimes = new ::omnetpp::simtime_t[packetTotalTimes_arraysize];
        doParsimArrayUnpacking(b,this->packetTotalTimes,packetTotalTimes_arraysize);
    }
}

size_t TimeTagBase::getFlowNamesArraySize() const
{
    return flowNames_arraysize;
}

const char * TimeTagBase::getFlowNames(size_t k) const
{
    if (k >= flowNames_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flowNames_arraysize, (unsigned long)k);
    return this->flowNames[k].c_str();
}

void TimeTagBase::setFlowNamesArraySize(size_t newSize)
{
    ::omnetpp::opp_string *flowNames2 = (newSize==0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t minSize = flowNames_arraysize < newSize ? flowNames_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        flowNames2[i] = this->flowNames[i];
    delete [] this->flowNames;
    this->flowNames = flowNames2;
    flowNames_arraysize = newSize;
}

void TimeTagBase::setFlowNames(size_t k, const char * flowNames)
{
    if (k >= flowNames_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flowNames_arraysize, (unsigned long)k);
    this->flowNames[k] = flowNames;
}

void TimeTagBase::insertFlowNames(size_t k, const char * flowNames)
{
    if (k > flowNames_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flowNames_arraysize, (unsigned long)k);
    size_t newSize = flowNames_arraysize + 1;
    ::omnetpp::opp_string *flowNames2 = new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        flowNames2[i] = this->flowNames[i];
    flowNames2[k] = flowNames;
    for (i = k + 1; i < newSize; i++)
        flowNames2[i] = this->flowNames[i-1];
    delete [] this->flowNames;
    this->flowNames = flowNames2;
    flowNames_arraysize = newSize;
}

void TimeTagBase::appendFlowNames(const char * flowNames)
{
    insertFlowNames(flowNames_arraysize, flowNames);
}

void TimeTagBase::eraseFlowNames(size_t k)
{
    if (k >= flowNames_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flowNames_arraysize, (unsigned long)k);
    size_t newSize = flowNames_arraysize - 1;
    ::omnetpp::opp_string *flowNames2 = (newSize == 0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        flowNames2[i] = this->flowNames[i];
    for (i = k; i < newSize; i++)
        flowNames2[i] = this->flowNames[i+1];
    delete [] this->flowNames;
    this->flowNames = flowNames2;
    flowNames_arraysize = newSize;
}

size_t TimeTagBase::getBitTotalTimesArraySize() const
{
    return bitTotalTimes_arraysize;
}

::omnetpp::simtime_t TimeTagBase::getBitTotalTimes(size_t k) const
{
    if (k >= bitTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bitTotalTimes_arraysize, (unsigned long)k);
    return this->bitTotalTimes[k];
}

void TimeTagBase::setBitTotalTimesArraySize(size_t newSize)
{
    ::omnetpp::simtime_t *bitTotalTimes2 = (newSize==0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t minSize = bitTotalTimes_arraysize < newSize ? bitTotalTimes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        bitTotalTimes2[i] = this->bitTotalTimes[i];
    for (size_t i = minSize; i < newSize; i++)
        bitTotalTimes2[i] = SIMTIME_ZERO;
    delete [] this->bitTotalTimes;
    this->bitTotalTimes = bitTotalTimes2;
    bitTotalTimes_arraysize = newSize;
}

void TimeTagBase::setBitTotalTimes(size_t k, ::omnetpp::simtime_t bitTotalTimes)
{
    if (k >= bitTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bitTotalTimes_arraysize, (unsigned long)k);
    this->bitTotalTimes[k] = bitTotalTimes;
}

void TimeTagBase::insertBitTotalTimes(size_t k, ::omnetpp::simtime_t bitTotalTimes)
{
    if (k > bitTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bitTotalTimes_arraysize, (unsigned long)k);
    size_t newSize = bitTotalTimes_arraysize + 1;
    ::omnetpp::simtime_t *bitTotalTimes2 = new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bitTotalTimes2[i] = this->bitTotalTimes[i];
    bitTotalTimes2[k] = bitTotalTimes;
    for (i = k + 1; i < newSize; i++)
        bitTotalTimes2[i] = this->bitTotalTimes[i-1];
    delete [] this->bitTotalTimes;
    this->bitTotalTimes = bitTotalTimes2;
    bitTotalTimes_arraysize = newSize;
}

void TimeTagBase::appendBitTotalTimes(::omnetpp::simtime_t bitTotalTimes)
{
    insertBitTotalTimes(bitTotalTimes_arraysize, bitTotalTimes);
}

void TimeTagBase::eraseBitTotalTimes(size_t k)
{
    if (k >= bitTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bitTotalTimes_arraysize, (unsigned long)k);
    size_t newSize = bitTotalTimes_arraysize - 1;
    ::omnetpp::simtime_t *bitTotalTimes2 = (newSize == 0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bitTotalTimes2[i] = this->bitTotalTimes[i];
    for (i = k; i < newSize; i++)
        bitTotalTimes2[i] = this->bitTotalTimes[i+1];
    delete [] this->bitTotalTimes;
    this->bitTotalTimes = bitTotalTimes2;
    bitTotalTimes_arraysize = newSize;
}

size_t TimeTagBase::getPacketTotalTimesArraySize() const
{
    return packetTotalTimes_arraysize;
}

::omnetpp::simtime_t TimeTagBase::getPacketTotalTimes(size_t k) const
{
    if (k >= packetTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)packetTotalTimes_arraysize, (unsigned long)k);
    return this->packetTotalTimes[k];
}

void TimeTagBase::setPacketTotalTimesArraySize(size_t newSize)
{
    ::omnetpp::simtime_t *packetTotalTimes2 = (newSize==0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t minSize = packetTotalTimes_arraysize < newSize ? packetTotalTimes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        packetTotalTimes2[i] = this->packetTotalTimes[i];
    for (size_t i = minSize; i < newSize; i++)
        packetTotalTimes2[i] = SIMTIME_ZERO;
    delete [] this->packetTotalTimes;
    this->packetTotalTimes = packetTotalTimes2;
    packetTotalTimes_arraysize = newSize;
}

void TimeTagBase::setPacketTotalTimes(size_t k, ::omnetpp::simtime_t packetTotalTimes)
{
    if (k >= packetTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)packetTotalTimes_arraysize, (unsigned long)k);
    this->packetTotalTimes[k] = packetTotalTimes;
}

void TimeTagBase::insertPacketTotalTimes(size_t k, ::omnetpp::simtime_t packetTotalTimes)
{
    if (k > packetTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)packetTotalTimes_arraysize, (unsigned long)k);
    size_t newSize = packetTotalTimes_arraysize + 1;
    ::omnetpp::simtime_t *packetTotalTimes2 = new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        packetTotalTimes2[i] = this->packetTotalTimes[i];
    packetTotalTimes2[k] = packetTotalTimes;
    for (i = k + 1; i < newSize; i++)
        packetTotalTimes2[i] = this->packetTotalTimes[i-1];
    delete [] this->packetTotalTimes;
    this->packetTotalTimes = packetTotalTimes2;
    packetTotalTimes_arraysize = newSize;
}

void TimeTagBase::appendPacketTotalTimes(::omnetpp::simtime_t packetTotalTimes)
{
    insertPacketTotalTimes(packetTotalTimes_arraysize, packetTotalTimes);
}

void TimeTagBase::erasePacketTotalTimes(size_t k)
{
    if (k >= packetTotalTimes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)packetTotalTimes_arraysize, (unsigned long)k);
    size_t newSize = packetTotalTimes_arraysize - 1;
    ::omnetpp::simtime_t *packetTotalTimes2 = (newSize == 0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        packetTotalTimes2[i] = this->packetTotalTimes[i];
    for (i = k; i < newSize; i++)
        packetTotalTimes2[i] = this->packetTotalTimes[i+1];
    delete [] this->packetTotalTimes;
    this->packetTotalTimes = packetTotalTimes2;
    packetTotalTimes_arraysize = newSize;
}

class TimeTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flowNames,
        FIELD_bitTotalTimes,
        FIELD_packetTotalTimes,
    };
  public:
    TimeTagBaseDescriptor();
    virtual ~TimeTagBaseDescriptor();

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

Register_ClassDescriptor(TimeTagBaseDescriptor)

TimeTagBaseDescriptor::TimeTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TimeTagBase)), "inet::TagBase")
{
    propertyNames = nullptr;
}

TimeTagBaseDescriptor::~TimeTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool TimeTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TimeTagBase *>(obj)!=nullptr;
}

const char **TimeTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TimeTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TimeTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int TimeTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_flowNames
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_bitTotalTimes
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_packetTotalTimes
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *TimeTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flowNames",
        "bitTotalTimes",
        "packetTotalTimes",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int TimeTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flowNames") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bitTotalTimes") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "packetTotalTimes") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *TimeTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_flowNames
        "omnetpp::simtime_t",    // FIELD_bitTotalTimes
        "omnetpp::simtime_t",    // FIELD_packetTotalTimes
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **TimeTagBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *TimeTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TimeTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: return pp->getFlowNamesArraySize();
        case FIELD_bitTotalTimes: return pp->getBitTotalTimesArraySize();
        case FIELD_packetTotalTimes: return pp->getPacketTotalTimesArraySize();
        default: return 0;
    }
}

void TimeTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: pp->setFlowNamesArraySize(size); break;
        case FIELD_bitTotalTimes: pp->setBitTotalTimesArraySize(size); break;
        case FIELD_packetTotalTimes: pp->setPacketTotalTimesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TimeTagBase'", field);
    }
}

const char *TimeTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TimeTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: return oppstring2string(pp->getFlowNames(i));
        case FIELD_bitTotalTimes: return simtime2string(pp->getBitTotalTimes(i));
        case FIELD_packetTotalTimes: return simtime2string(pp->getPacketTotalTimes(i));
        default: return "";
    }
}

void TimeTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: pp->setFlowNames(i,(value)); break;
        case FIELD_bitTotalTimes: pp->setBitTotalTimes(i,string2simtime(value)); break;
        case FIELD_packetTotalTimes: pp->setPacketTotalTimes(i,string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeTagBase'", field);
    }
}

omnetpp::cValue TimeTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: return pp->getFlowNames(i);
        case FIELD_bitTotalTimes: return pp->getBitTotalTimes(i).dbl();
        case FIELD_packetTotalTimes: return pp->getPacketTotalTimes(i).dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TimeTagBase' as cValue -- field index out of range?", field);
    }
}

void TimeTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_flowNames: pp->setFlowNames(i,value.stringValue()); break;
        case FIELD_bitTotalTimes: pp->setBitTotalTimes(i,value.doubleValue()); break;
        case FIELD_packetTotalTimes: pp->setPacketTotalTimes(i,value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeTagBase'", field);
    }
}

const char *TimeTagBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TimeTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TimeTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeTagBase *pp = omnetpp::fromAnyPtr<TimeTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeTagBase'", field);
    }
}

Register_Class(ElapsedTimeTag)

ElapsedTimeTag::ElapsedTimeTag() : ::inet::TimeTagBase()
{
}

ElapsedTimeTag::ElapsedTimeTag(const ElapsedTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

ElapsedTimeTag::~ElapsedTimeTag()
{
}

ElapsedTimeTag& ElapsedTimeTag::operator=(const ElapsedTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void ElapsedTimeTag::copy(const ElapsedTimeTag& other)
{
}

void ElapsedTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void ElapsedTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class ElapsedTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    ElapsedTimeTagDescriptor();
    virtual ~ElapsedTimeTagDescriptor();

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

Register_ClassDescriptor(ElapsedTimeTagDescriptor)

ElapsedTimeTagDescriptor::ElapsedTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ElapsedTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

ElapsedTimeTagDescriptor::~ElapsedTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool ElapsedTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ElapsedTimeTag *>(obj)!=nullptr;
}

const char **ElapsedTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ElapsedTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ElapsedTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int ElapsedTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *ElapsedTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int ElapsedTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *ElapsedTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **ElapsedTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *ElapsedTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ElapsedTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ElapsedTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ElapsedTimeTag'", field);
    }
}

const char *ElapsedTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ElapsedTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void ElapsedTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ElapsedTimeTag'", field);
    }
}

omnetpp::cValue ElapsedTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ElapsedTimeTag' as cValue -- field index out of range?", field);
    }
}

void ElapsedTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ElapsedTimeTag'", field);
    }
}

const char *ElapsedTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr ElapsedTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ElapsedTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ElapsedTimeTag *pp = omnetpp::fromAnyPtr<ElapsedTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ElapsedTimeTag'", field);
    }
}

Register_Class(DelayingTimeTag)

DelayingTimeTag::DelayingTimeTag() : ::inet::TimeTagBase()
{
}

DelayingTimeTag::DelayingTimeTag(const DelayingTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

DelayingTimeTag::~DelayingTimeTag()
{
}

DelayingTimeTag& DelayingTimeTag::operator=(const DelayingTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void DelayingTimeTag::copy(const DelayingTimeTag& other)
{
}

void DelayingTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void DelayingTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class DelayingTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    DelayingTimeTagDescriptor();
    virtual ~DelayingTimeTagDescriptor();

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

Register_ClassDescriptor(DelayingTimeTagDescriptor)

DelayingTimeTagDescriptor::DelayingTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::DelayingTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

DelayingTimeTagDescriptor::~DelayingTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool DelayingTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DelayingTimeTag *>(obj)!=nullptr;
}

const char **DelayingTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DelayingTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DelayingTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int DelayingTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *DelayingTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int DelayingTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *DelayingTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **DelayingTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *DelayingTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int DelayingTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DelayingTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DelayingTimeTag'", field);
    }
}

const char *DelayingTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DelayingTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void DelayingTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DelayingTimeTag'", field);
    }
}

omnetpp::cValue DelayingTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DelayingTimeTag' as cValue -- field index out of range?", field);
    }
}

void DelayingTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DelayingTimeTag'", field);
    }
}

const char *DelayingTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr DelayingTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DelayingTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DelayingTimeTag *pp = omnetpp::fromAnyPtr<DelayingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DelayingTimeTag'", field);
    }
}

Register_Class(QueueingTimeTag)

QueueingTimeTag::QueueingTimeTag() : ::inet::TimeTagBase()
{
}

QueueingTimeTag::QueueingTimeTag(const QueueingTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

QueueingTimeTag::~QueueingTimeTag()
{
}

QueueingTimeTag& QueueingTimeTag::operator=(const QueueingTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void QueueingTimeTag::copy(const QueueingTimeTag& other)
{
}

void QueueingTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void QueueingTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class QueueingTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    QueueingTimeTagDescriptor();
    virtual ~QueueingTimeTagDescriptor();

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

Register_ClassDescriptor(QueueingTimeTagDescriptor)

QueueingTimeTagDescriptor::QueueingTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::QueueingTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

QueueingTimeTagDescriptor::~QueueingTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool QueueingTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<QueueingTimeTag *>(obj)!=nullptr;
}

const char **QueueingTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *QueueingTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int QueueingTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int QueueingTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *QueueingTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int QueueingTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *QueueingTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **QueueingTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *QueueingTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int QueueingTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void QueueingTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'QueueingTimeTag'", field);
    }
}

const char *QueueingTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string QueueingTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void QueueingTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QueueingTimeTag'", field);
    }
}

omnetpp::cValue QueueingTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'QueueingTimeTag' as cValue -- field index out of range?", field);
    }
}

void QueueingTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QueueingTimeTag'", field);
    }
}

const char *QueueingTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr QueueingTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void QueueingTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    QueueingTimeTag *pp = omnetpp::fromAnyPtr<QueueingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'QueueingTimeTag'", field);
    }
}

Register_Class(ProcessingTimeTag)

ProcessingTimeTag::ProcessingTimeTag() : ::inet::TimeTagBase()
{
}

ProcessingTimeTag::ProcessingTimeTag(const ProcessingTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

ProcessingTimeTag::~ProcessingTimeTag()
{
}

ProcessingTimeTag& ProcessingTimeTag::operator=(const ProcessingTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void ProcessingTimeTag::copy(const ProcessingTimeTag& other)
{
}

void ProcessingTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void ProcessingTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class ProcessingTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    ProcessingTimeTagDescriptor();
    virtual ~ProcessingTimeTagDescriptor();

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

Register_ClassDescriptor(ProcessingTimeTagDescriptor)

ProcessingTimeTagDescriptor::ProcessingTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ProcessingTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

ProcessingTimeTagDescriptor::~ProcessingTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool ProcessingTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ProcessingTimeTag *>(obj)!=nullptr;
}

const char **ProcessingTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ProcessingTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ProcessingTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int ProcessingTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *ProcessingTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int ProcessingTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *ProcessingTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **ProcessingTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *ProcessingTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ProcessingTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ProcessingTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ProcessingTimeTag'", field);
    }
}

const char *ProcessingTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ProcessingTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void ProcessingTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessingTimeTag'", field);
    }
}

omnetpp::cValue ProcessingTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ProcessingTimeTag' as cValue -- field index out of range?", field);
    }
}

void ProcessingTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessingTimeTag'", field);
    }
}

const char *ProcessingTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr ProcessingTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ProcessingTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessingTimeTag *pp = omnetpp::fromAnyPtr<ProcessingTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessingTimeTag'", field);
    }
}

Register_Class(TransmissionTimeTag)

TransmissionTimeTag::TransmissionTimeTag() : ::inet::TimeTagBase()
{
}

TransmissionTimeTag::TransmissionTimeTag(const TransmissionTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

TransmissionTimeTag::~TransmissionTimeTag()
{
}

TransmissionTimeTag& TransmissionTimeTag::operator=(const TransmissionTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void TransmissionTimeTag::copy(const TransmissionTimeTag& other)
{
}

void TransmissionTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void TransmissionTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class TransmissionTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TransmissionTimeTagDescriptor();
    virtual ~TransmissionTimeTagDescriptor();

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

Register_ClassDescriptor(TransmissionTimeTagDescriptor)

TransmissionTimeTagDescriptor::TransmissionTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::TransmissionTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

TransmissionTimeTagDescriptor::~TransmissionTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool TransmissionTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TransmissionTimeTag *>(obj)!=nullptr;
}

const char **TransmissionTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TransmissionTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TransmissionTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TransmissionTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TransmissionTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TransmissionTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TransmissionTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TransmissionTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *TransmissionTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TransmissionTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TransmissionTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TransmissionTimeTag'", field);
    }
}

const char *TransmissionTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TransmissionTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TransmissionTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransmissionTimeTag'", field);
    }
}

omnetpp::cValue TransmissionTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TransmissionTimeTag' as cValue -- field index out of range?", field);
    }
}

void TransmissionTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransmissionTimeTag'", field);
    }
}

const char *TransmissionTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TransmissionTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TransmissionTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TransmissionTimeTag *pp = omnetpp::fromAnyPtr<TransmissionTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TransmissionTimeTag'", field);
    }
}

Register_Class(PropagationTimeTag)

PropagationTimeTag::PropagationTimeTag() : ::inet::TimeTagBase()
{
}

PropagationTimeTag::PropagationTimeTag(const PropagationTimeTag& other) : ::inet::TimeTagBase(other)
{
    copy(other);
}

PropagationTimeTag::~PropagationTimeTag()
{
}

PropagationTimeTag& PropagationTimeTag::operator=(const PropagationTimeTag& other)
{
    if (this == &other) return *this;
    ::inet::TimeTagBase::operator=(other);
    copy(other);
    return *this;
}

void PropagationTimeTag::copy(const PropagationTimeTag& other)
{
}

void PropagationTimeTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TimeTagBase::parsimPack(b);
}

void PropagationTimeTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TimeTagBase::parsimUnpack(b);
}

class PropagationTimeTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    PropagationTimeTagDescriptor();
    virtual ~PropagationTimeTagDescriptor();

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

Register_ClassDescriptor(PropagationTimeTagDescriptor)

PropagationTimeTagDescriptor::PropagationTimeTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::PropagationTimeTag)), "inet::TimeTagBase")
{
    propertyNames = nullptr;
}

PropagationTimeTagDescriptor::~PropagationTimeTagDescriptor()
{
    delete[] propertyNames;
}

bool PropagationTimeTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PropagationTimeTag *>(obj)!=nullptr;
}

const char **PropagationTimeTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PropagationTimeTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PropagationTimeTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int PropagationTimeTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *PropagationTimeTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int PropagationTimeTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *PropagationTimeTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **PropagationTimeTagDescriptor::getFieldPropertyNames(int field) const
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

const char *PropagationTimeTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PropagationTimeTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PropagationTimeTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PropagationTimeTag'", field);
    }
}

const char *PropagationTimeTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PropagationTimeTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void PropagationTimeTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PropagationTimeTag'", field);
    }
}

omnetpp::cValue PropagationTimeTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PropagationTimeTag' as cValue -- field index out of range?", field);
    }
}

void PropagationTimeTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PropagationTimeTag'", field);
    }
}

const char *PropagationTimeTagDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr PropagationTimeTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PropagationTimeTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PropagationTimeTag *pp = omnetpp::fromAnyPtr<PropagationTimeTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PropagationTimeTag'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

