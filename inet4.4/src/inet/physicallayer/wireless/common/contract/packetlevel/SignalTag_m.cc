//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/common/contract/packetlevel/SignalTag.msg.
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
#include "SignalTag_m.h"

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

Register_Class(SignalTagBase)

SignalTagBase::SignalTagBase() : ::inet::TagBase()
{
}

SignalTagBase::SignalTagBase(const SignalTagBase& other) : ::inet::TagBase(other)
{
    copy(other);
}

SignalTagBase::~SignalTagBase()
{
}

SignalTagBase& SignalTagBase::operator=(const SignalTagBase& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalTagBase::copy(const SignalTagBase& other)
{
}

void SignalTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
}

void SignalTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
}

class SignalTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalTagBaseDescriptor();
    virtual ~SignalTagBaseDescriptor();

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

Register_ClassDescriptor(SignalTagBaseDescriptor)

SignalTagBaseDescriptor::SignalTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalTagBase)), "inet::TagBase")
{
    propertyNames = nullptr;
}

SignalTagBaseDescriptor::~SignalTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool SignalTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalTagBase *>(obj)!=nullptr;
}

const char **SignalTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalTagBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalTagBase'", field);
    }
}

const char *SignalTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTagBase'", field);
    }
}

omnetpp::cValue SignalTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalTagBase' as cValue -- field index out of range?", field);
    }
}

void SignalTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTagBase'", field);
    }
}

const char *SignalTagBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTagBase *pp = omnetpp::fromAnyPtr<SignalTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTagBase'", field);
    }
}

Register_Class(SignalPowerTagBase)

SignalPowerTagBase::SignalPowerTagBase() : ::inet::SignalTagBase()
{
}

SignalPowerTagBase::SignalPowerTagBase(const SignalPowerTagBase& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

SignalPowerTagBase::~SignalPowerTagBase()
{
}

SignalPowerTagBase& SignalPowerTagBase::operator=(const SignalPowerTagBase& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalPowerTagBase::copy(const SignalPowerTagBase& other)
{
    this->power = other.power;
}

void SignalPowerTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->power);
}

void SignalPowerTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->power);
}

W SignalPowerTagBase::getPower() const
{
    return this->power;
}

void SignalPowerTagBase::setPower(W power)
{
    this->power = power;
}

class SignalPowerTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_power,
    };
  public:
    SignalPowerTagBaseDescriptor();
    virtual ~SignalPowerTagBaseDescriptor();

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

Register_ClassDescriptor(SignalPowerTagBaseDescriptor)

SignalPowerTagBaseDescriptor::SignalPowerTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalPowerTagBase)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

SignalPowerTagBaseDescriptor::~SignalPowerTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool SignalPowerTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalPowerTagBase *>(obj)!=nullptr;
}

const char **SignalPowerTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalPowerTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalPowerTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SignalPowerTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_power
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SignalPowerTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "power",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SignalPowerTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "power") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SignalPowerTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::W",    // FIELD_power
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SignalPowerTagBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalPowerTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalPowerTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalPowerTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalPowerTagBase'", field);
    }
}

const char *SignalPowerTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalPowerTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_power: return unit2string(pp->getPower());
        default: return "";
    }
}

void SignalPowerTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_power: pp->setPower(W(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerTagBase'", field);
    }
}

omnetpp::cValue SignalPowerTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_power: return cValue(pp->getPower().get(),"W");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalPowerTagBase' as cValue -- field index out of range?", field);
    }
}

void SignalPowerTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_power: pp->setPower(W(value.doubleValueInUnit("W"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerTagBase'", field);
    }
}

const char *SignalPowerTagBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SignalPowerTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalPowerTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerTagBase *pp = omnetpp::fromAnyPtr<SignalPowerTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerTagBase'", field);
    }
}

Register_Class(SignalPowerReq)

SignalPowerReq::SignalPowerReq() : ::inet::SignalPowerTagBase()
{
}

SignalPowerReq::SignalPowerReq(const SignalPowerReq& other) : ::inet::SignalPowerTagBase(other)
{
    copy(other);
}

SignalPowerReq::~SignalPowerReq()
{
}

SignalPowerReq& SignalPowerReq::operator=(const SignalPowerReq& other)
{
    if (this == &other) return *this;
    ::inet::SignalPowerTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalPowerReq::copy(const SignalPowerReq& other)
{
}

void SignalPowerReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalPowerTagBase::parsimPack(b);
}

void SignalPowerReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalPowerTagBase::parsimUnpack(b);
}

class SignalPowerReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalPowerReqDescriptor();
    virtual ~SignalPowerReqDescriptor();

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

Register_ClassDescriptor(SignalPowerReqDescriptor)

SignalPowerReqDescriptor::SignalPowerReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalPowerReq)), "inet::SignalPowerTagBase")
{
    propertyNames = nullptr;
}

SignalPowerReqDescriptor::~SignalPowerReqDescriptor()
{
    delete[] propertyNames;
}

bool SignalPowerReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalPowerReq *>(obj)!=nullptr;
}

const char **SignalPowerReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalPowerReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalPowerReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalPowerReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalPowerReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalPowerReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalPowerReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalPowerReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalPowerReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalPowerReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalPowerReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalPowerReq'", field);
    }
}

const char *SignalPowerReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalPowerReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalPowerReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerReq'", field);
    }
}

omnetpp::cValue SignalPowerReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalPowerReq' as cValue -- field index out of range?", field);
    }
}

void SignalPowerReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerReq'", field);
    }
}

const char *SignalPowerReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalPowerReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalPowerReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerReq *pp = omnetpp::fromAnyPtr<SignalPowerReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerReq'", field);
    }
}

Register_Class(SignalPowerInd)

SignalPowerInd::SignalPowerInd() : ::inet::SignalPowerTagBase()
{
}

SignalPowerInd::SignalPowerInd(const SignalPowerInd& other) : ::inet::SignalPowerTagBase(other)
{
    copy(other);
}

SignalPowerInd::~SignalPowerInd()
{
}

SignalPowerInd& SignalPowerInd::operator=(const SignalPowerInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalPowerTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalPowerInd::copy(const SignalPowerInd& other)
{
}

void SignalPowerInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalPowerTagBase::parsimPack(b);
}

void SignalPowerInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalPowerTagBase::parsimUnpack(b);
}

class SignalPowerIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalPowerIndDescriptor();
    virtual ~SignalPowerIndDescriptor();

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

Register_ClassDescriptor(SignalPowerIndDescriptor)

SignalPowerIndDescriptor::SignalPowerIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalPowerInd)), "inet::SignalPowerTagBase")
{
    propertyNames = nullptr;
}

SignalPowerIndDescriptor::~SignalPowerIndDescriptor()
{
    delete[] propertyNames;
}

bool SignalPowerIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalPowerInd *>(obj)!=nullptr;
}

const char **SignalPowerIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalPowerIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalPowerIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalPowerIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalPowerIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalPowerIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalPowerIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalPowerIndDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalPowerIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalPowerIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalPowerIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalPowerInd'", field);
    }
}

const char *SignalPowerIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalPowerIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalPowerIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerInd'", field);
    }
}

omnetpp::cValue SignalPowerIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalPowerInd' as cValue -- field index out of range?", field);
    }
}

void SignalPowerIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerInd'", field);
    }
}

const char *SignalPowerIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalPowerIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalPowerIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalPowerInd *pp = omnetpp::fromAnyPtr<SignalPowerInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalPowerInd'", field);
    }
}

Register_Class(SignalBandTagBase)

SignalBandTagBase::SignalBandTagBase() : ::inet::SignalTagBase()
{
}

SignalBandTagBase::SignalBandTagBase(const SignalBandTagBase& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

SignalBandTagBase::~SignalBandTagBase()
{
}

SignalBandTagBase& SignalBandTagBase::operator=(const SignalBandTagBase& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBandTagBase::copy(const SignalBandTagBase& other)
{
    this->centerFrequency = other.centerFrequency;
    this->bandwidth = other.bandwidth;
}

void SignalBandTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->centerFrequency);
    doParsimPacking(b,this->bandwidth);
}

void SignalBandTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->centerFrequency);
    doParsimUnpacking(b,this->bandwidth);
}

Hz SignalBandTagBase::getCenterFrequency() const
{
    return this->centerFrequency;
}

void SignalBandTagBase::setCenterFrequency(Hz centerFrequency)
{
    this->centerFrequency = centerFrequency;
}

Hz SignalBandTagBase::getBandwidth() const
{
    return this->bandwidth;
}

void SignalBandTagBase::setBandwidth(Hz bandwidth)
{
    this->bandwidth = bandwidth;
}

class SignalBandTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_centerFrequency,
        FIELD_bandwidth,
    };
  public:
    SignalBandTagBaseDescriptor();
    virtual ~SignalBandTagBaseDescriptor();

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

Register_ClassDescriptor(SignalBandTagBaseDescriptor)

SignalBandTagBaseDescriptor::SignalBandTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBandTagBase)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

SignalBandTagBaseDescriptor::~SignalBandTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool SignalBandTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBandTagBase *>(obj)!=nullptr;
}

const char **SignalBandTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBandTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBandTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SignalBandTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_centerFrequency
        FD_ISEDITABLE,    // FIELD_bandwidth
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SignalBandTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "centerFrequency",
        "bandwidth",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SignalBandTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "centerFrequency") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bandwidth") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBandTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Hz",    // FIELD_centerFrequency
        "inet::Hz",    // FIELD_bandwidth
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SignalBandTagBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBandTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBandTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBandTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBandTagBase'", field);
    }
}

const char *SignalBandTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBandTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: return unit2string(pp->getCenterFrequency());
        case FIELD_bandwidth: return unit2string(pp->getBandwidth());
        default: return "";
    }
}

void SignalBandTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(string2double(value))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandTagBase'", field);
    }
}

omnetpp::cValue SignalBandTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: return cValue(pp->getCenterFrequency().get(),"Hz");
        case FIELD_bandwidth: return cValue(pp->getBandwidth().get(),"Hz");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBandTagBase' as cValue -- field index out of range?", field);
    }
}

void SignalBandTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_centerFrequency: pp->setCenterFrequency(Hz(value.doubleValueInUnit("Hz"))); break;
        case FIELD_bandwidth: pp->setBandwidth(Hz(value.doubleValueInUnit("Hz"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandTagBase'", field);
    }
}

const char *SignalBandTagBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SignalBandTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBandTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandTagBase *pp = omnetpp::fromAnyPtr<SignalBandTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandTagBase'", field);
    }
}

Register_Class(SignalBandReq)

SignalBandReq::SignalBandReq() : ::inet::SignalBandTagBase()
{
}

SignalBandReq::SignalBandReq(const SignalBandReq& other) : ::inet::SignalBandTagBase(other)
{
    copy(other);
}

SignalBandReq::~SignalBandReq()
{
}

SignalBandReq& SignalBandReq::operator=(const SignalBandReq& other)
{
    if (this == &other) return *this;
    ::inet::SignalBandTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBandReq::copy(const SignalBandReq& other)
{
}

void SignalBandReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalBandTagBase::parsimPack(b);
}

void SignalBandReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalBandTagBase::parsimUnpack(b);
}

class SignalBandReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalBandReqDescriptor();
    virtual ~SignalBandReqDescriptor();

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

Register_ClassDescriptor(SignalBandReqDescriptor)

SignalBandReqDescriptor::SignalBandReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBandReq)), "inet::SignalBandTagBase")
{
    propertyNames = nullptr;
}

SignalBandReqDescriptor::~SignalBandReqDescriptor()
{
    delete[] propertyNames;
}

bool SignalBandReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBandReq *>(obj)!=nullptr;
}

const char **SignalBandReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBandReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBandReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalBandReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalBandReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalBandReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBandReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalBandReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBandReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBandReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBandReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBandReq'", field);
    }
}

const char *SignalBandReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBandReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalBandReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandReq'", field);
    }
}

omnetpp::cValue SignalBandReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBandReq' as cValue -- field index out of range?", field);
    }
}

void SignalBandReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandReq'", field);
    }
}

const char *SignalBandReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalBandReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBandReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandReq *pp = omnetpp::fromAnyPtr<SignalBandReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandReq'", field);
    }
}

Register_Class(SignalBandInd)

SignalBandInd::SignalBandInd() : ::inet::SignalBandTagBase()
{
}

SignalBandInd::SignalBandInd(const SignalBandInd& other) : ::inet::SignalBandTagBase(other)
{
    copy(other);
}

SignalBandInd::~SignalBandInd()
{
}

SignalBandInd& SignalBandInd::operator=(const SignalBandInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalBandTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBandInd::copy(const SignalBandInd& other)
{
}

void SignalBandInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalBandTagBase::parsimPack(b);
}

void SignalBandInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalBandTagBase::parsimUnpack(b);
}

class SignalBandIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalBandIndDescriptor();
    virtual ~SignalBandIndDescriptor();

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

Register_ClassDescriptor(SignalBandIndDescriptor)

SignalBandIndDescriptor::SignalBandIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBandInd)), "inet::SignalBandTagBase")
{
    propertyNames = nullptr;
}

SignalBandIndDescriptor::~SignalBandIndDescriptor()
{
    delete[] propertyNames;
}

bool SignalBandIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBandInd *>(obj)!=nullptr;
}

const char **SignalBandIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBandIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBandIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalBandIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalBandIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalBandIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBandIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalBandIndDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBandIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBandIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBandIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBandInd'", field);
    }
}

const char *SignalBandIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBandIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalBandIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandInd'", field);
    }
}

omnetpp::cValue SignalBandIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBandInd' as cValue -- field index out of range?", field);
    }
}

void SignalBandIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandInd'", field);
    }
}

const char *SignalBandIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalBandIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBandIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBandInd *pp = omnetpp::fromAnyPtr<SignalBandInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBandInd'", field);
    }
}

Register_Class(SignalBitrateTagBase)

SignalBitrateTagBase::SignalBitrateTagBase() : ::inet::SignalTagBase()
{
}

SignalBitrateTagBase::SignalBitrateTagBase(const SignalBitrateTagBase& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

SignalBitrateTagBase::~SignalBitrateTagBase()
{
}

SignalBitrateTagBase& SignalBitrateTagBase::operator=(const SignalBitrateTagBase& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBitrateTagBase::copy(const SignalBitrateTagBase& other)
{
    this->preambleBitrate = other.preambleBitrate;
    this->headerBitrate = other.headerBitrate;
    this->dataBitrate = other.dataBitrate;
}

void SignalBitrateTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->preambleBitrate);
    doParsimPacking(b,this->headerBitrate);
    doParsimPacking(b,this->dataBitrate);
}

void SignalBitrateTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->preambleBitrate);
    doParsimUnpacking(b,this->headerBitrate);
    doParsimUnpacking(b,this->dataBitrate);
}

bps SignalBitrateTagBase::getPreambleBitrate() const
{
    return this->preambleBitrate;
}

void SignalBitrateTagBase::setPreambleBitrate(bps preambleBitrate)
{
    this->preambleBitrate = preambleBitrate;
}

bps SignalBitrateTagBase::getHeaderBitrate() const
{
    return this->headerBitrate;
}

void SignalBitrateTagBase::setHeaderBitrate(bps headerBitrate)
{
    this->headerBitrate = headerBitrate;
}

bps SignalBitrateTagBase::getDataBitrate() const
{
    return this->dataBitrate;
}

void SignalBitrateTagBase::setDataBitrate(bps dataBitrate)
{
    this->dataBitrate = dataBitrate;
}

class SignalBitrateTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_preambleBitrate,
        FIELD_headerBitrate,
        FIELD_dataBitrate,
    };
  public:
    SignalBitrateTagBaseDescriptor();
    virtual ~SignalBitrateTagBaseDescriptor();

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

Register_ClassDescriptor(SignalBitrateTagBaseDescriptor)

SignalBitrateTagBaseDescriptor::SignalBitrateTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBitrateTagBase)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

SignalBitrateTagBaseDescriptor::~SignalBitrateTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool SignalBitrateTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBitrateTagBase *>(obj)!=nullptr;
}

const char **SignalBitrateTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBitrateTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBitrateTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SignalBitrateTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_preambleBitrate
        FD_ISEDITABLE,    // FIELD_headerBitrate
        FD_ISEDITABLE,    // FIELD_dataBitrate
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SignalBitrateTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "preambleBitrate",
        "headerBitrate",
        "dataBitrate",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SignalBitrateTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "preambleBitrate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "headerBitrate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "dataBitrate") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBitrateTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::bps",    // FIELD_preambleBitrate
        "inet::bps",    // FIELD_headerBitrate
        "inet::bps",    // FIELD_dataBitrate
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SignalBitrateTagBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBitrateTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBitrateTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBitrateTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBitrateTagBase'", field);
    }
}

const char *SignalBitrateTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBitrateTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_preambleBitrate: return unit2string(pp->getPreambleBitrate());
        case FIELD_headerBitrate: return unit2string(pp->getHeaderBitrate());
        case FIELD_dataBitrate: return unit2string(pp->getDataBitrate());
        default: return "";
    }
}

void SignalBitrateTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_preambleBitrate: pp->setPreambleBitrate(bps(string2double(value))); break;
        case FIELD_headerBitrate: pp->setHeaderBitrate(bps(string2double(value))); break;
        case FIELD_dataBitrate: pp->setDataBitrate(bps(string2double(value))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateTagBase'", field);
    }
}

omnetpp::cValue SignalBitrateTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_preambleBitrate: return cValue(pp->getPreambleBitrate().get(),"bps");
        case FIELD_headerBitrate: return cValue(pp->getHeaderBitrate().get(),"bps");
        case FIELD_dataBitrate: return cValue(pp->getDataBitrate().get(),"bps");
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBitrateTagBase' as cValue -- field index out of range?", field);
    }
}

void SignalBitrateTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_preambleBitrate: pp->setPreambleBitrate(bps(value.doubleValueInUnit("bps"))); break;
        case FIELD_headerBitrate: pp->setHeaderBitrate(bps(value.doubleValueInUnit("bps"))); break;
        case FIELD_dataBitrate: pp->setDataBitrate(bps(value.doubleValueInUnit("bps"))); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateTagBase'", field);
    }
}

const char *SignalBitrateTagBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SignalBitrateTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBitrateTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateTagBase *pp = omnetpp::fromAnyPtr<SignalBitrateTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateTagBase'", field);
    }
}

Register_Class(SignalBitrateReq)

SignalBitrateReq::SignalBitrateReq() : ::inet::SignalBitrateTagBase()
{
}

SignalBitrateReq::SignalBitrateReq(const SignalBitrateReq& other) : ::inet::SignalBitrateTagBase(other)
{
    copy(other);
}

SignalBitrateReq::~SignalBitrateReq()
{
}

SignalBitrateReq& SignalBitrateReq::operator=(const SignalBitrateReq& other)
{
    if (this == &other) return *this;
    ::inet::SignalBitrateTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBitrateReq::copy(const SignalBitrateReq& other)
{
}

void SignalBitrateReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalBitrateTagBase::parsimPack(b);
}

void SignalBitrateReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalBitrateTagBase::parsimUnpack(b);
}

class SignalBitrateReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalBitrateReqDescriptor();
    virtual ~SignalBitrateReqDescriptor();

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

Register_ClassDescriptor(SignalBitrateReqDescriptor)

SignalBitrateReqDescriptor::SignalBitrateReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBitrateReq)), "inet::SignalBitrateTagBase")
{
    propertyNames = nullptr;
}

SignalBitrateReqDescriptor::~SignalBitrateReqDescriptor()
{
    delete[] propertyNames;
}

bool SignalBitrateReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBitrateReq *>(obj)!=nullptr;
}

const char **SignalBitrateReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBitrateReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBitrateReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalBitrateReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalBitrateReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalBitrateReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBitrateReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalBitrateReqDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBitrateReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBitrateReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBitrateReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBitrateReq'", field);
    }
}

const char *SignalBitrateReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBitrateReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalBitrateReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateReq'", field);
    }
}

omnetpp::cValue SignalBitrateReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBitrateReq' as cValue -- field index out of range?", field);
    }
}

void SignalBitrateReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateReq'", field);
    }
}

const char *SignalBitrateReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalBitrateReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBitrateReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateReq *pp = omnetpp::fromAnyPtr<SignalBitrateReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateReq'", field);
    }
}

Register_Class(SignalBitrateInd)

SignalBitrateInd::SignalBitrateInd() : ::inet::SignalBitrateTagBase()
{
}

SignalBitrateInd::SignalBitrateInd(const SignalBitrateInd& other) : ::inet::SignalBitrateTagBase(other)
{
    copy(other);
}

SignalBitrateInd::~SignalBitrateInd()
{
}

SignalBitrateInd& SignalBitrateInd::operator=(const SignalBitrateInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalBitrateTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalBitrateInd::copy(const SignalBitrateInd& other)
{
}

void SignalBitrateInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalBitrateTagBase::parsimPack(b);
}

void SignalBitrateInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalBitrateTagBase::parsimUnpack(b);
}

class SignalBitrateIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SignalBitrateIndDescriptor();
    virtual ~SignalBitrateIndDescriptor();

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

Register_ClassDescriptor(SignalBitrateIndDescriptor)

SignalBitrateIndDescriptor::SignalBitrateIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalBitrateInd)), "inet::SignalBitrateTagBase")
{
    propertyNames = nullptr;
}

SignalBitrateIndDescriptor::~SignalBitrateIndDescriptor()
{
    delete[] propertyNames;
}

bool SignalBitrateIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalBitrateInd *>(obj)!=nullptr;
}

const char **SignalBitrateIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalBitrateIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalBitrateIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SignalBitrateIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SignalBitrateIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SignalBitrateIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SignalBitrateIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SignalBitrateIndDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalBitrateIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalBitrateIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalBitrateIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalBitrateInd'", field);
    }
}

const char *SignalBitrateIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalBitrateIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SignalBitrateIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateInd'", field);
    }
}

omnetpp::cValue SignalBitrateIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalBitrateInd' as cValue -- field index out of range?", field);
    }
}

void SignalBitrateIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateInd'", field);
    }
}

const char *SignalBitrateIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SignalBitrateIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalBitrateIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalBitrateInd *pp = omnetpp::fromAnyPtr<SignalBitrateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalBitrateInd'", field);
    }
}

Register_Class(SnirInd)

SnirInd::SnirInd() : ::inet::SignalTagBase()
{
}

SnirInd::SnirInd(const SnirInd& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

SnirInd::~SnirInd()
{
}

SnirInd& SnirInd::operator=(const SnirInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void SnirInd::copy(const SnirInd& other)
{
    this->minimumSnir = other.minimumSnir;
    this->maximumSnir = other.maximumSnir;
    this->averageSnir = other.averageSnir;
}

void SnirInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->minimumSnir);
    doParsimPacking(b,this->maximumSnir);
    doParsimPacking(b,this->averageSnir);
}

void SnirInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->minimumSnir);
    doParsimUnpacking(b,this->maximumSnir);
    doParsimUnpacking(b,this->averageSnir);
}

double SnirInd::getMinimumSnir() const
{
    return this->minimumSnir;
}

void SnirInd::setMinimumSnir(double minimumSnir)
{
    this->minimumSnir = minimumSnir;
}

double SnirInd::getMaximumSnir() const
{
    return this->maximumSnir;
}

void SnirInd::setMaximumSnir(double maximumSnir)
{
    this->maximumSnir = maximumSnir;
}

double SnirInd::getAverageSnir() const
{
    return this->averageSnir;
}

void SnirInd::setAverageSnir(double averageSnir)
{
    this->averageSnir = averageSnir;
}

class SnirIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_minimumSnir,
        FIELD_maximumSnir,
        FIELD_averageSnir,
    };
  public:
    SnirIndDescriptor();
    virtual ~SnirIndDescriptor();

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

Register_ClassDescriptor(SnirIndDescriptor)

SnirIndDescriptor::SnirIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SnirInd)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

SnirIndDescriptor::~SnirIndDescriptor()
{
    delete[] propertyNames;
}

bool SnirIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SnirInd *>(obj)!=nullptr;
}

const char **SnirIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SnirIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SnirIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SnirIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_minimumSnir
        FD_ISEDITABLE,    // FIELD_maximumSnir
        FD_ISEDITABLE,    // FIELD_averageSnir
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SnirIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "minimumSnir",
        "maximumSnir",
        "averageSnir",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SnirIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "minimumSnir") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "maximumSnir") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "averageSnir") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SnirIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_minimumSnir
        "double",    // FIELD_maximumSnir
        "double",    // FIELD_averageSnir
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SnirIndDescriptor::getFieldPropertyNames(int field) const
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

const char *SnirIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SnirIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SnirIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SnirInd'", field);
    }
}

const char *SnirIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SnirIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        case FIELD_minimumSnir: return double2string(pp->getMinimumSnir());
        case FIELD_maximumSnir: return double2string(pp->getMaximumSnir());
        case FIELD_averageSnir: return double2string(pp->getAverageSnir());
        default: return "";
    }
}

void SnirIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        case FIELD_minimumSnir: pp->setMinimumSnir(string2double(value)); break;
        case FIELD_maximumSnir: pp->setMaximumSnir(string2double(value)); break;
        case FIELD_averageSnir: pp->setAverageSnir(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SnirInd'", field);
    }
}

omnetpp::cValue SnirIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        case FIELD_minimumSnir: return pp->getMinimumSnir();
        case FIELD_maximumSnir: return pp->getMaximumSnir();
        case FIELD_averageSnir: return pp->getAverageSnir();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SnirInd' as cValue -- field index out of range?", field);
    }
}

void SnirIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        case FIELD_minimumSnir: pp->setMinimumSnir(value.doubleValue()); break;
        case FIELD_maximumSnir: pp->setMaximumSnir(value.doubleValue()); break;
        case FIELD_averageSnir: pp->setAverageSnir(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SnirInd'", field);
    }
}

const char *SnirIndDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SnirIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SnirIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SnirInd *pp = omnetpp::fromAnyPtr<SnirInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SnirInd'", field);
    }
}

Register_Class(ErrorRateInd)

ErrorRateInd::ErrorRateInd() : ::inet::SignalTagBase()
{
}

ErrorRateInd::ErrorRateInd(const ErrorRateInd& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

ErrorRateInd::~ErrorRateInd()
{
}

ErrorRateInd& ErrorRateInd::operator=(const ErrorRateInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void ErrorRateInd::copy(const ErrorRateInd& other)
{
    this->packetErrorRate = other.packetErrorRate;
    this->bitErrorRate = other.bitErrorRate;
    this->symbolErrorRate = other.symbolErrorRate;
}

void ErrorRateInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->packetErrorRate);
    doParsimPacking(b,this->bitErrorRate);
    doParsimPacking(b,this->symbolErrorRate);
}

void ErrorRateInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->packetErrorRate);
    doParsimUnpacking(b,this->bitErrorRate);
    doParsimUnpacking(b,this->symbolErrorRate);
}

double ErrorRateInd::getPacketErrorRate() const
{
    return this->packetErrorRate;
}

void ErrorRateInd::setPacketErrorRate(double packetErrorRate)
{
    this->packetErrorRate = packetErrorRate;
}

double ErrorRateInd::getBitErrorRate() const
{
    return this->bitErrorRate;
}

void ErrorRateInd::setBitErrorRate(double bitErrorRate)
{
    this->bitErrorRate = bitErrorRate;
}

double ErrorRateInd::getSymbolErrorRate() const
{
    return this->symbolErrorRate;
}

void ErrorRateInd::setSymbolErrorRate(double symbolErrorRate)
{
    this->symbolErrorRate = symbolErrorRate;
}

class ErrorRateIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_packetErrorRate,
        FIELD_bitErrorRate,
        FIELD_symbolErrorRate,
    };
  public:
    ErrorRateIndDescriptor();
    virtual ~ErrorRateIndDescriptor();

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

Register_ClassDescriptor(ErrorRateIndDescriptor)

ErrorRateIndDescriptor::ErrorRateIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ErrorRateInd)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

ErrorRateIndDescriptor::~ErrorRateIndDescriptor()
{
    delete[] propertyNames;
}

bool ErrorRateIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ErrorRateInd *>(obj)!=nullptr;
}

const char **ErrorRateIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ErrorRateIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ErrorRateIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int ErrorRateIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_packetErrorRate
        FD_ISEDITABLE,    // FIELD_bitErrorRate
        FD_ISEDITABLE,    // FIELD_symbolErrorRate
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ErrorRateIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetErrorRate",
        "bitErrorRate",
        "symbolErrorRate",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ErrorRateIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "packetErrorRate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bitErrorRate") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "symbolErrorRate") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *ErrorRateIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_packetErrorRate
        "double",    // FIELD_bitErrorRate
        "double",    // FIELD_symbolErrorRate
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ErrorRateIndDescriptor::getFieldPropertyNames(int field) const
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

const char *ErrorRateIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ErrorRateIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ErrorRateIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ErrorRateInd'", field);
    }
}

const char *ErrorRateIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ErrorRateIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        case FIELD_packetErrorRate: return double2string(pp->getPacketErrorRate());
        case FIELD_bitErrorRate: return double2string(pp->getBitErrorRate());
        case FIELD_symbolErrorRate: return double2string(pp->getSymbolErrorRate());
        default: return "";
    }
}

void ErrorRateIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        case FIELD_packetErrorRate: pp->setPacketErrorRate(string2double(value)); break;
        case FIELD_bitErrorRate: pp->setBitErrorRate(string2double(value)); break;
        case FIELD_symbolErrorRate: pp->setSymbolErrorRate(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ErrorRateInd'", field);
    }
}

omnetpp::cValue ErrorRateIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        case FIELD_packetErrorRate: return pp->getPacketErrorRate();
        case FIELD_bitErrorRate: return pp->getBitErrorRate();
        case FIELD_symbolErrorRate: return pp->getSymbolErrorRate();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ErrorRateInd' as cValue -- field index out of range?", field);
    }
}

void ErrorRateIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        case FIELD_packetErrorRate: pp->setPacketErrorRate(value.doubleValue()); break;
        case FIELD_bitErrorRate: pp->setBitErrorRate(value.doubleValue()); break;
        case FIELD_symbolErrorRate: pp->setSymbolErrorRate(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ErrorRateInd'", field);
    }
}

const char *ErrorRateIndDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ErrorRateIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ErrorRateIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ErrorRateInd *pp = omnetpp::fromAnyPtr<ErrorRateInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ErrorRateInd'", field);
    }
}

Register_Class(SignalTimeInd)

SignalTimeInd::SignalTimeInd() : ::inet::SignalTagBase()
{
}

SignalTimeInd::SignalTimeInd(const SignalTimeInd& other) : ::inet::SignalTagBase(other)
{
    copy(other);
}

SignalTimeInd::~SignalTimeInd()
{
}

SignalTimeInd& SignalTimeInd::operator=(const SignalTimeInd& other)
{
    if (this == &other) return *this;
    ::inet::SignalTagBase::operator=(other);
    copy(other);
    return *this;
}

void SignalTimeInd::copy(const SignalTimeInd& other)
{
    this->startTime = other.startTime;
    this->endTime = other.endTime;
}

void SignalTimeInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::SignalTagBase::parsimPack(b);
    doParsimPacking(b,this->startTime);
    doParsimPacking(b,this->endTime);
}

void SignalTimeInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::SignalTagBase::parsimUnpack(b);
    doParsimUnpacking(b,this->startTime);
    doParsimUnpacking(b,this->endTime);
}

::omnetpp::simtime_t SignalTimeInd::getStartTime() const
{
    return this->startTime;
}

void SignalTimeInd::setStartTime(::omnetpp::simtime_t startTime)
{
    this->startTime = startTime;
}

::omnetpp::simtime_t SignalTimeInd::getEndTime() const
{
    return this->endTime;
}

void SignalTimeInd::setEndTime(::omnetpp::simtime_t endTime)
{
    this->endTime = endTime;
}

class SignalTimeIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_startTime,
        FIELD_endTime,
    };
  public:
    SignalTimeIndDescriptor();
    virtual ~SignalTimeIndDescriptor();

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

Register_ClassDescriptor(SignalTimeIndDescriptor)

SignalTimeIndDescriptor::SignalTimeIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SignalTimeInd)), "inet::SignalTagBase")
{
    propertyNames = nullptr;
}

SignalTimeIndDescriptor::~SignalTimeIndDescriptor()
{
    delete[] propertyNames;
}

bool SignalTimeIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignalTimeInd *>(obj)!=nullptr;
}

const char **SignalTimeIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignalTimeIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignalTimeIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SignalTimeIndDescriptor::getFieldTypeFlags(int field) const
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

const char *SignalTimeIndDescriptor::getFieldName(int field) const
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

int SignalTimeIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "startTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "endTime") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SignalTimeIndDescriptor::getFieldTypeString(int field) const
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

const char **SignalTimeIndDescriptor::getFieldPropertyNames(int field) const
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

const char *SignalTimeIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SignalTimeIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignalTimeIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignalTimeInd'", field);
    }
}

const char *SignalTimeIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignalTimeIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return simtime2string(pp->getStartTime());
        case FIELD_endTime: return simtime2string(pp->getEndTime());
        default: return "";
    }
}

void SignalTimeIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: pp->setStartTime(string2simtime(value)); break;
        case FIELD_endTime: pp->setEndTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTimeInd'", field);
    }
}

omnetpp::cValue SignalTimeIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: return pp->getStartTime().dbl();
        case FIELD_endTime: return pp->getEndTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignalTimeInd' as cValue -- field index out of range?", field);
    }
}

void SignalTimeIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        case FIELD_startTime: pp->setStartTime(value.doubleValue()); break;
        case FIELD_endTime: pp->setEndTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTimeInd'", field);
    }
}

const char *SignalTimeIndDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SignalTimeIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignalTimeIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignalTimeInd *pp = omnetpp::fromAnyPtr<SignalTimeInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignalTimeInd'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

