//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/Ipv4Header.msg.
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
#include "Ipv4Header_m.h"

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

Register_Enum(inet::Ipv4OptionClass, (inet::Ipv4OptionClass::IPOPTION_CLASS_CONTROL, inet::Ipv4OptionClass::IPOPTION_CLASS_RESERVED, inet::Ipv4OptionClass::IPOPTION_CLASS_DEBUGGING, inet::Ipv4OptionClass::IPOPTION_CLASS_RESERVED2));

Register_Enum(inet::Ipv4OptionType, (inet::Ipv4OptionType::IPOPTION_END_OF_OPTIONS, inet::Ipv4OptionType::IPOPTION_NO_OPTION, inet::Ipv4OptionType::IPOPTION_STREAM_ID, inet::Ipv4OptionType::IPOPTION_TIMESTAMP, inet::Ipv4OptionType::IPOPTION_SECURITY, inet::Ipv4OptionType::IPOPTION_LOOSE_SOURCE_ROUTING, inet::Ipv4OptionType::IPOPTION_RECORD_ROUTE, inet::Ipv4OptionType::IPOPTION_STRICT_SOURCE_ROUTING, inet::Ipv4OptionType::IPOPTION_ROUTER_ALERT, inet::Ipv4OptionType::IPOPTION_TLV_GPSR));

Register_Enum(inet::TimestampFlag, (inet::TimestampFlag::IP_TIMESTAMP_TIMESTAMP_ONLY, inet::TimestampFlag::IP_TIMESTAMP_WITH_ADDRESS, inet::TimestampFlag::IP_TIMESTAMP_SENDER_INIT_ADDRESS));

Register_Class(Ipv4Option)

Ipv4Option::Ipv4Option() : ::inet::TlvOptionBase()
{
}

Ipv4Option::Ipv4Option(const Ipv4Option& other) : ::inet::TlvOptionBase(other)
{
    copy(other);
}

Ipv4Option::~Ipv4Option()
{
}

Ipv4Option& Ipv4Option::operator=(const Ipv4Option& other)
{
    if (this == &other) return *this;
    ::inet::TlvOptionBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv4Option::copy(const Ipv4Option& other)
{
}

void Ipv4Option::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TlvOptionBase::parsimPack(b);
}

void Ipv4Option::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TlvOptionBase::parsimUnpack(b);
}

class Ipv4OptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv4OptionDescriptor();
    virtual ~Ipv4OptionDescriptor();

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

Register_ClassDescriptor(Ipv4OptionDescriptor)

Ipv4OptionDescriptor::Ipv4OptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4Option)), "inet::TlvOptionBase")
{
    propertyNames = nullptr;
}

Ipv4OptionDescriptor::~Ipv4OptionDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4Option *>(obj)!=nullptr;
}

const char **Ipv4OptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv4OptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv4OptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv4OptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv4OptionDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4Option'", field);
    }
}

const char *Ipv4OptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv4OptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Option'", field);
    }
}

omnetpp::cValue Ipv4OptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4Option' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Option'", field);
    }
}

const char *Ipv4OptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv4OptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Option *pp = omnetpp::fromAnyPtr<Ipv4Option>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Option'", field);
    }
}

Register_Class(Ipv4OptionNop)

Ipv4OptionNop::Ipv4OptionNop() : ::inet::Ipv4Option()
{
    this->setType(IPOPTION_NO_OPTION);
    this->setLength(1);
}

Ipv4OptionNop::Ipv4OptionNop(const Ipv4OptionNop& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionNop::~Ipv4OptionNop()
{
}

Ipv4OptionNop& Ipv4OptionNop::operator=(const Ipv4OptionNop& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionNop::copy(const Ipv4OptionNop& other)
{
}

void Ipv4OptionNop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
}

void Ipv4OptionNop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
}

class Ipv4OptionNopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv4OptionNopDescriptor();
    virtual ~Ipv4OptionNopDescriptor();

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

Register_ClassDescriptor(Ipv4OptionNopDescriptor)

Ipv4OptionNopDescriptor::Ipv4OptionNopDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionNop)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionNopDescriptor::~Ipv4OptionNopDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionNopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionNop *>(obj)!=nullptr;
}

const char **Ipv4OptionNopDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionNopDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionNopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv4OptionNopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv4OptionNopDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv4OptionNopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionNopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv4OptionNopDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionNopDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionNopDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionNopDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionNop'", field);
    }
}

const char *Ipv4OptionNopDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionNopDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv4OptionNopDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionNop'", field);
    }
}

omnetpp::cValue Ipv4OptionNopDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionNop' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionNopDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionNop'", field);
    }
}

const char *Ipv4OptionNopDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv4OptionNopDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionNopDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionNop *pp = omnetpp::fromAnyPtr<Ipv4OptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionNop'", field);
    }
}

Register_Class(Ipv4OptionEnd)

Ipv4OptionEnd::Ipv4OptionEnd() : ::inet::Ipv4Option()
{
    this->setType(IPOPTION_END_OF_OPTIONS);
    this->setLength(1);
}

Ipv4OptionEnd::Ipv4OptionEnd(const Ipv4OptionEnd& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionEnd::~Ipv4OptionEnd()
{
}

Ipv4OptionEnd& Ipv4OptionEnd::operator=(const Ipv4OptionEnd& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionEnd::copy(const Ipv4OptionEnd& other)
{
}

void Ipv4OptionEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
}

void Ipv4OptionEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
}

class Ipv4OptionEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv4OptionEndDescriptor();
    virtual ~Ipv4OptionEndDescriptor();

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

Register_ClassDescriptor(Ipv4OptionEndDescriptor)

Ipv4OptionEndDescriptor::Ipv4OptionEndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionEnd)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionEndDescriptor::~Ipv4OptionEndDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionEnd *>(obj)!=nullptr;
}

const char **Ipv4OptionEndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionEndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv4OptionEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv4OptionEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv4OptionEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv4OptionEndDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionEndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionEndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionEndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionEnd'", field);
    }
}

const char *Ipv4OptionEndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionEndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv4OptionEndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionEnd'", field);
    }
}

omnetpp::cValue Ipv4OptionEndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionEnd' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionEndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionEnd'", field);
    }
}

const char *Ipv4OptionEndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv4OptionEndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionEndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionEnd *pp = omnetpp::fromAnyPtr<Ipv4OptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionEnd'", field);
    }
}

Register_Class(Ipv4OptionRecordRoute)

Ipv4OptionRecordRoute::Ipv4OptionRecordRoute() : ::inet::Ipv4Option()
{
}

Ipv4OptionRecordRoute::Ipv4OptionRecordRoute(const Ipv4OptionRecordRoute& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionRecordRoute::~Ipv4OptionRecordRoute()
{
    delete [] this->recordAddress;
}

Ipv4OptionRecordRoute& Ipv4OptionRecordRoute::operator=(const Ipv4OptionRecordRoute& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionRecordRoute::copy(const Ipv4OptionRecordRoute& other)
{
    this->nextAddressIdx = other.nextAddressIdx;
    delete [] this->recordAddress;
    this->recordAddress = (other.recordAddress_arraysize==0) ? nullptr : new Ipv4Address[other.recordAddress_arraysize];
    recordAddress_arraysize = other.recordAddress_arraysize;
    for (size_t i = 0; i < recordAddress_arraysize; i++) {
        this->recordAddress[i] = other.recordAddress[i];
    }
}

void Ipv4OptionRecordRoute::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
    doParsimPacking(b,this->nextAddressIdx);
    b->pack(recordAddress_arraysize);
    doParsimArrayPacking(b,this->recordAddress,recordAddress_arraysize);
}

void Ipv4OptionRecordRoute::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
    doParsimUnpacking(b,this->nextAddressIdx);
    delete [] this->recordAddress;
    b->unpack(recordAddress_arraysize);
    if (recordAddress_arraysize == 0) {
        this->recordAddress = nullptr;
    } else {
        this->recordAddress = new Ipv4Address[recordAddress_arraysize];
        doParsimArrayUnpacking(b,this->recordAddress,recordAddress_arraysize);
    }
}

short Ipv4OptionRecordRoute::getNextAddressIdx() const
{
    return this->nextAddressIdx;
}

void Ipv4OptionRecordRoute::setNextAddressIdx(short nextAddressIdx)
{
    this->nextAddressIdx = nextAddressIdx;
}

size_t Ipv4OptionRecordRoute::getRecordAddressArraySize() const
{
    return recordAddress_arraysize;
}

const Ipv4Address& Ipv4OptionRecordRoute::getRecordAddress(size_t k) const
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    return this->recordAddress[k];
}

void Ipv4OptionRecordRoute::setRecordAddressArraySize(size_t newSize)
{
    Ipv4Address *recordAddress2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = recordAddress_arraysize < newSize ? recordAddress_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        recordAddress2[i] = this->recordAddress[i];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

void Ipv4OptionRecordRoute::setRecordAddress(size_t k, const Ipv4Address& recordAddress)
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    this->recordAddress[k] = recordAddress;
}

void Ipv4OptionRecordRoute::insertRecordAddress(size_t k, const Ipv4Address& recordAddress)
{
    if (k > recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    size_t newSize = recordAddress_arraysize + 1;
    Ipv4Address *recordAddress2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordAddress2[i] = this->recordAddress[i];
    recordAddress2[k] = recordAddress;
    for (i = k + 1; i < newSize; i++)
        recordAddress2[i] = this->recordAddress[i-1];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

void Ipv4OptionRecordRoute::appendRecordAddress(const Ipv4Address& recordAddress)
{
    insertRecordAddress(recordAddress_arraysize, recordAddress);
}

void Ipv4OptionRecordRoute::eraseRecordAddress(size_t k)
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    size_t newSize = recordAddress_arraysize - 1;
    Ipv4Address *recordAddress2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordAddress2[i] = this->recordAddress[i];
    for (i = k; i < newSize; i++)
        recordAddress2[i] = this->recordAddress[i+1];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

class Ipv4OptionRecordRouteDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_nextAddressIdx,
        FIELD_recordAddress,
    };
  public:
    Ipv4OptionRecordRouteDescriptor();
    virtual ~Ipv4OptionRecordRouteDescriptor();

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

Register_ClassDescriptor(Ipv4OptionRecordRouteDescriptor)

Ipv4OptionRecordRouteDescriptor::Ipv4OptionRecordRouteDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionRecordRoute)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionRecordRouteDescriptor::~Ipv4OptionRecordRouteDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionRecordRouteDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionRecordRoute *>(obj)!=nullptr;
}

const char **Ipv4OptionRecordRouteDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionRecordRouteDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionRecordRouteDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ipv4OptionRecordRouteDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_nextAddressIdx
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_recordAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4OptionRecordRouteDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nextAddressIdx",
        "recordAddress",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv4OptionRecordRouteDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "nextAddressIdx") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "recordAddress") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionRecordRouteDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_nextAddressIdx
        "inet::Ipv4Address",    // FIELD_recordAddress
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionRecordRouteDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionRecordRouteDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionRecordRouteDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: return pp->getRecordAddressArraySize();
        default: return 0;
    }
}

void Ipv4OptionRecordRouteDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: pp->setRecordAddressArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionRecordRoute'", field);
    }
}

const char *Ipv4OptionRecordRouteDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionRecordRouteDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_nextAddressIdx: return long2string(pp->getNextAddressIdx());
        case FIELD_recordAddress: return pp->getRecordAddress(i).str();
        default: return "";
    }
}

void Ipv4OptionRecordRouteDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_nextAddressIdx: pp->setNextAddressIdx(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRecordRoute'", field);
    }
}

omnetpp::cValue Ipv4OptionRecordRouteDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_nextAddressIdx: return pp->getNextAddressIdx();
        case FIELD_recordAddress: return omnetpp::toAnyPtr(&pp->getRecordAddress(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionRecordRoute' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionRecordRouteDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_nextAddressIdx: pp->setNextAddressIdx(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRecordRoute'", field);
    }
}

const char *Ipv4OptionRecordRouteDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4OptionRecordRouteDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: return omnetpp::toAnyPtr(&pp->getRecordAddress(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionRecordRouteDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRecordRoute *pp = omnetpp::fromAnyPtr<Ipv4OptionRecordRoute>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRecordRoute'", field);
    }
}

Register_Class(Ipv4OptionTimestamp)

Ipv4OptionTimestamp::Ipv4OptionTimestamp() : ::inet::Ipv4Option()
{
    this->setType(IPOPTION_TIMESTAMP);

}

Ipv4OptionTimestamp::Ipv4OptionTimestamp(const Ipv4OptionTimestamp& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionTimestamp::~Ipv4OptionTimestamp()
{
    delete [] this->recordAddress;
    delete [] this->recordTimestamp;
}

Ipv4OptionTimestamp& Ipv4OptionTimestamp::operator=(const Ipv4OptionTimestamp& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionTimestamp::copy(const Ipv4OptionTimestamp& other)
{
    this->flag = other.flag;
    this->overflow = other.overflow;
    this->nextIdx = other.nextIdx;
    delete [] this->recordAddress;
    this->recordAddress = (other.recordAddress_arraysize==0) ? nullptr : new Ipv4Address[other.recordAddress_arraysize];
    recordAddress_arraysize = other.recordAddress_arraysize;
    for (size_t i = 0; i < recordAddress_arraysize; i++) {
        this->recordAddress[i] = other.recordAddress[i];
    }
    delete [] this->recordTimestamp;
    this->recordTimestamp = (other.recordTimestamp_arraysize==0) ? nullptr : new ::omnetpp::simtime_t[other.recordTimestamp_arraysize];
    recordTimestamp_arraysize = other.recordTimestamp_arraysize;
    for (size_t i = 0; i < recordTimestamp_arraysize; i++) {
        this->recordTimestamp[i] = other.recordTimestamp[i];
    }
}

void Ipv4OptionTimestamp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
    doParsimPacking(b,this->flag);
    doParsimPacking(b,this->overflow);
    doParsimPacking(b,this->nextIdx);
    b->pack(recordAddress_arraysize);
    doParsimArrayPacking(b,this->recordAddress,recordAddress_arraysize);
    b->pack(recordTimestamp_arraysize);
    doParsimArrayPacking(b,this->recordTimestamp,recordTimestamp_arraysize);
}

void Ipv4OptionTimestamp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
    doParsimUnpacking(b,this->flag);
    doParsimUnpacking(b,this->overflow);
    doParsimUnpacking(b,this->nextIdx);
    delete [] this->recordAddress;
    b->unpack(recordAddress_arraysize);
    if (recordAddress_arraysize == 0) {
        this->recordAddress = nullptr;
    } else {
        this->recordAddress = new Ipv4Address[recordAddress_arraysize];
        doParsimArrayUnpacking(b,this->recordAddress,recordAddress_arraysize);
    }
    delete [] this->recordTimestamp;
    b->unpack(recordTimestamp_arraysize);
    if (recordTimestamp_arraysize == 0) {
        this->recordTimestamp = nullptr;
    } else {
        this->recordTimestamp = new ::omnetpp::simtime_t[recordTimestamp_arraysize];
        doParsimArrayUnpacking(b,this->recordTimestamp,recordTimestamp_arraysize);
    }
}

TimestampFlag Ipv4OptionTimestamp::getFlag() const
{
    return this->flag;
}

void Ipv4OptionTimestamp::setFlag(TimestampFlag flag)
{
    this->flag = flag;
}

short Ipv4OptionTimestamp::getOverflow() const
{
    return this->overflow;
}

void Ipv4OptionTimestamp::setOverflow(short overflow)
{
    this->overflow = overflow;
}

short Ipv4OptionTimestamp::getNextIdx() const
{
    return this->nextIdx;
}

void Ipv4OptionTimestamp::setNextIdx(short nextIdx)
{
    this->nextIdx = nextIdx;
}

size_t Ipv4OptionTimestamp::getRecordAddressArraySize() const
{
    return recordAddress_arraysize;
}

const Ipv4Address& Ipv4OptionTimestamp::getRecordAddress(size_t k) const
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    return this->recordAddress[k];
}

void Ipv4OptionTimestamp::setRecordAddressArraySize(size_t newSize)
{
    Ipv4Address *recordAddress2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = recordAddress_arraysize < newSize ? recordAddress_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        recordAddress2[i] = this->recordAddress[i];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

void Ipv4OptionTimestamp::setRecordAddress(size_t k, const Ipv4Address& recordAddress)
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    this->recordAddress[k] = recordAddress;
}

void Ipv4OptionTimestamp::insertRecordAddress(size_t k, const Ipv4Address& recordAddress)
{
    if (k > recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    size_t newSize = recordAddress_arraysize + 1;
    Ipv4Address *recordAddress2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordAddress2[i] = this->recordAddress[i];
    recordAddress2[k] = recordAddress;
    for (i = k + 1; i < newSize; i++)
        recordAddress2[i] = this->recordAddress[i-1];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

void Ipv4OptionTimestamp::appendRecordAddress(const Ipv4Address& recordAddress)
{
    insertRecordAddress(recordAddress_arraysize, recordAddress);
}

void Ipv4OptionTimestamp::eraseRecordAddress(size_t k)
{
    if (k >= recordAddress_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordAddress_arraysize, (unsigned long)k);
    size_t newSize = recordAddress_arraysize - 1;
    Ipv4Address *recordAddress2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordAddress2[i] = this->recordAddress[i];
    for (i = k; i < newSize; i++)
        recordAddress2[i] = this->recordAddress[i+1];
    delete [] this->recordAddress;
    this->recordAddress = recordAddress2;
    recordAddress_arraysize = newSize;
}

size_t Ipv4OptionTimestamp::getRecordTimestampArraySize() const
{
    return recordTimestamp_arraysize;
}

::omnetpp::simtime_t Ipv4OptionTimestamp::getRecordTimestamp(size_t k) const
{
    if (k >= recordTimestamp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordTimestamp_arraysize, (unsigned long)k);
    return this->recordTimestamp[k];
}

void Ipv4OptionTimestamp::setRecordTimestampArraySize(size_t newSize)
{
    ::omnetpp::simtime_t *recordTimestamp2 = (newSize==0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t minSize = recordTimestamp_arraysize < newSize ? recordTimestamp_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        recordTimestamp2[i] = this->recordTimestamp[i];
    for (size_t i = minSize; i < newSize; i++)
        recordTimestamp2[i] = SIMTIME_ZERO;
    delete [] this->recordTimestamp;
    this->recordTimestamp = recordTimestamp2;
    recordTimestamp_arraysize = newSize;
}

void Ipv4OptionTimestamp::setRecordTimestamp(size_t k, ::omnetpp::simtime_t recordTimestamp)
{
    if (k >= recordTimestamp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordTimestamp_arraysize, (unsigned long)k);
    this->recordTimestamp[k] = recordTimestamp;
}

void Ipv4OptionTimestamp::insertRecordTimestamp(size_t k, ::omnetpp::simtime_t recordTimestamp)
{
    if (k > recordTimestamp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordTimestamp_arraysize, (unsigned long)k);
    size_t newSize = recordTimestamp_arraysize + 1;
    ::omnetpp::simtime_t *recordTimestamp2 = new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordTimestamp2[i] = this->recordTimestamp[i];
    recordTimestamp2[k] = recordTimestamp;
    for (i = k + 1; i < newSize; i++)
        recordTimestamp2[i] = this->recordTimestamp[i-1];
    delete [] this->recordTimestamp;
    this->recordTimestamp = recordTimestamp2;
    recordTimestamp_arraysize = newSize;
}

void Ipv4OptionTimestamp::appendRecordTimestamp(::omnetpp::simtime_t recordTimestamp)
{
    insertRecordTimestamp(recordTimestamp_arraysize, recordTimestamp);
}

void Ipv4OptionTimestamp::eraseRecordTimestamp(size_t k)
{
    if (k >= recordTimestamp_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)recordTimestamp_arraysize, (unsigned long)k);
    size_t newSize = recordTimestamp_arraysize - 1;
    ::omnetpp::simtime_t *recordTimestamp2 = (newSize == 0) ? nullptr : new ::omnetpp::simtime_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        recordTimestamp2[i] = this->recordTimestamp[i];
    for (i = k; i < newSize; i++)
        recordTimestamp2[i] = this->recordTimestamp[i+1];
    delete [] this->recordTimestamp;
    this->recordTimestamp = recordTimestamp2;
    recordTimestamp_arraysize = newSize;
}

class Ipv4OptionTimestampDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flag,
        FIELD_overflow,
        FIELD_nextIdx,
        FIELD_recordAddress,
        FIELD_recordTimestamp,
    };
  public:
    Ipv4OptionTimestampDescriptor();
    virtual ~Ipv4OptionTimestampDescriptor();

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

Register_ClassDescriptor(Ipv4OptionTimestampDescriptor)

Ipv4OptionTimestampDescriptor::Ipv4OptionTimestampDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionTimestamp)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionTimestampDescriptor::~Ipv4OptionTimestampDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionTimestampDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionTimestamp *>(obj)!=nullptr;
}

const char **Ipv4OptionTimestampDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionTimestampDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionTimestampDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int Ipv4OptionTimestampDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_flag
        FD_ISEDITABLE,    // FIELD_overflow
        FD_ISEDITABLE,    // FIELD_nextIdx
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_recordAddress
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_recordTimestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4OptionTimestampDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flag",
        "overflow",
        "nextIdx",
        "recordAddress",
        "recordTimestamp",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ipv4OptionTimestampDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flag") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "overflow") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "nextIdx") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "recordAddress") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "recordTimestamp") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionTimestampDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::TimestampFlag",    // FIELD_flag
        "short",    // FIELD_overflow
        "short",    // FIELD_nextIdx
        "inet::Ipv4Address",    // FIELD_recordAddress
        "omnetpp::simtime_t",    // FIELD_recordTimestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionTimestampDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_flag: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv4OptionTimestampDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_flag:
            if (!strcmp(propertyName, "enum")) return "inet::TimestampFlag";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv4OptionTimestampDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: return pp->getRecordAddressArraySize();
        case FIELD_recordTimestamp: return pp->getRecordTimestampArraySize();
        default: return 0;
    }
}

void Ipv4OptionTimestampDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: pp->setRecordAddressArraySize(size); break;
        case FIELD_recordTimestamp: pp->setRecordTimestampArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionTimestamp'", field);
    }
}

const char *Ipv4OptionTimestampDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionTimestampDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_flag: return enum2string(pp->getFlag(), "inet::TimestampFlag");
        case FIELD_overflow: return long2string(pp->getOverflow());
        case FIELD_nextIdx: return long2string(pp->getNextIdx());
        case FIELD_recordAddress: return pp->getRecordAddress(i).str();
        case FIELD_recordTimestamp: return simtime2string(pp->getRecordTimestamp(i));
        default: return "";
    }
}

void Ipv4OptionTimestampDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_overflow: pp->setOverflow(string2long(value)); break;
        case FIELD_nextIdx: pp->setNextIdx(string2long(value)); break;
        case FIELD_recordTimestamp: pp->setRecordTimestamp(i,string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionTimestamp'", field);
    }
}

omnetpp::cValue Ipv4OptionTimestampDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_flag: return static_cast<int>(pp->getFlag());
        case FIELD_overflow: return pp->getOverflow();
        case FIELD_nextIdx: return pp->getNextIdx();
        case FIELD_recordAddress: return omnetpp::toAnyPtr(&pp->getRecordAddress(i)); break;
        case FIELD_recordTimestamp: return pp->getRecordTimestamp(i).dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionTimestamp' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionTimestampDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_overflow: pp->setOverflow(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_nextIdx: pp->setNextIdx(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_recordTimestamp: pp->setRecordTimestamp(i,value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionTimestamp'", field);
    }
}

const char *Ipv4OptionTimestampDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4OptionTimestampDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_recordAddress: return omnetpp::toAnyPtr(&pp->getRecordAddress(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionTimestampDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionTimestamp *pp = omnetpp::fromAnyPtr<Ipv4OptionTimestamp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionTimestamp'", field);
    }
}

Register_Class(Ipv4OptionStreamId)

Ipv4OptionStreamId::Ipv4OptionStreamId() : ::inet::Ipv4Option()
{
    this->setType(IPOPTION_STREAM_ID);
    this->setLength(4);

}

Ipv4OptionStreamId::Ipv4OptionStreamId(const Ipv4OptionStreamId& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionStreamId::~Ipv4OptionStreamId()
{
}

Ipv4OptionStreamId& Ipv4OptionStreamId::operator=(const Ipv4OptionStreamId& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionStreamId::copy(const Ipv4OptionStreamId& other)
{
    this->streamId = other.streamId;
}

void Ipv4OptionStreamId::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
    doParsimPacking(b,this->streamId);
}

void Ipv4OptionStreamId::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
    doParsimUnpacking(b,this->streamId);
}

short Ipv4OptionStreamId::getStreamId() const
{
    return this->streamId;
}

void Ipv4OptionStreamId::setStreamId(short streamId)
{
    this->streamId = streamId;
}

class Ipv4OptionStreamIdDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_streamId,
    };
  public:
    Ipv4OptionStreamIdDescriptor();
    virtual ~Ipv4OptionStreamIdDescriptor();

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

Register_ClassDescriptor(Ipv4OptionStreamIdDescriptor)

Ipv4OptionStreamIdDescriptor::Ipv4OptionStreamIdDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionStreamId)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionStreamIdDescriptor::~Ipv4OptionStreamIdDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionStreamIdDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionStreamId *>(obj)!=nullptr;
}

const char **Ipv4OptionStreamIdDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionStreamIdDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionStreamIdDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv4OptionStreamIdDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_streamId
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4OptionStreamIdDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "streamId",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv4OptionStreamIdDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "streamId") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionStreamIdDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_streamId
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionStreamIdDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionStreamIdDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionStreamIdDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionStreamIdDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionStreamId'", field);
    }
}

const char *Ipv4OptionStreamIdDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionStreamIdDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        case FIELD_streamId: return long2string(pp->getStreamId());
        default: return "";
    }
}

void Ipv4OptionStreamIdDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        case FIELD_streamId: pp->setStreamId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionStreamId'", field);
    }
}

omnetpp::cValue Ipv4OptionStreamIdDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        case FIELD_streamId: return pp->getStreamId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionStreamId' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionStreamIdDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        case FIELD_streamId: pp->setStreamId(omnetpp::checked_int_cast<short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionStreamId'", field);
    }
}

const char *Ipv4OptionStreamIdDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4OptionStreamIdDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionStreamIdDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionStreamId *pp = omnetpp::fromAnyPtr<Ipv4OptionStreamId>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionStreamId'", field);
    }
}

Register_Class(Ipv4OptionRouterAlert)

Ipv4OptionRouterAlert::Ipv4OptionRouterAlert() : ::inet::Ipv4Option()
{
    this->setType(IPOPTION_ROUTER_ALERT);
    this->setLength(4);

}

Ipv4OptionRouterAlert::Ipv4OptionRouterAlert(const Ipv4OptionRouterAlert& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionRouterAlert::~Ipv4OptionRouterAlert()
{
}

Ipv4OptionRouterAlert& Ipv4OptionRouterAlert::operator=(const Ipv4OptionRouterAlert& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionRouterAlert::copy(const Ipv4OptionRouterAlert& other)
{
    this->routerAlert = other.routerAlert;
}

void Ipv4OptionRouterAlert::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
    doParsimPacking(b,this->routerAlert);
}

void Ipv4OptionRouterAlert::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
    doParsimUnpacking(b,this->routerAlert);
}

uint16_t Ipv4OptionRouterAlert::getRouterAlert() const
{
    return this->routerAlert;
}

void Ipv4OptionRouterAlert::setRouterAlert(uint16_t routerAlert)
{
    this->routerAlert = routerAlert;
}

class Ipv4OptionRouterAlertDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_routerAlert,
    };
  public:
    Ipv4OptionRouterAlertDescriptor();
    virtual ~Ipv4OptionRouterAlertDescriptor();

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

Register_ClassDescriptor(Ipv4OptionRouterAlertDescriptor)

Ipv4OptionRouterAlertDescriptor::Ipv4OptionRouterAlertDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionRouterAlert)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionRouterAlertDescriptor::~Ipv4OptionRouterAlertDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionRouterAlertDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionRouterAlert *>(obj)!=nullptr;
}

const char **Ipv4OptionRouterAlertDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionRouterAlertDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionRouterAlertDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv4OptionRouterAlertDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routerAlert
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4OptionRouterAlertDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerAlert",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv4OptionRouterAlertDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "routerAlert") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionRouterAlertDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_routerAlert
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionRouterAlertDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionRouterAlertDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionRouterAlertDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionRouterAlertDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionRouterAlert'", field);
    }
}

const char *Ipv4OptionRouterAlertDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionRouterAlertDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        case FIELD_routerAlert: return ulong2string(pp->getRouterAlert());
        default: return "";
    }
}

void Ipv4OptionRouterAlertDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        case FIELD_routerAlert: pp->setRouterAlert(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRouterAlert'", field);
    }
}

omnetpp::cValue Ipv4OptionRouterAlertDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        case FIELD_routerAlert: return (omnetpp::intval_t)(pp->getRouterAlert());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionRouterAlert' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionRouterAlertDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        case FIELD_routerAlert: pp->setRouterAlert(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRouterAlert'", field);
    }
}

const char *Ipv4OptionRouterAlertDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4OptionRouterAlertDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionRouterAlertDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionRouterAlert *pp = omnetpp::fromAnyPtr<Ipv4OptionRouterAlert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionRouterAlert'", field);
    }
}

Register_Class(Ipv4OptionUnknown)

Ipv4OptionUnknown::Ipv4OptionUnknown() : ::inet::Ipv4Option()
{
}

Ipv4OptionUnknown::Ipv4OptionUnknown(const Ipv4OptionUnknown& other) : ::inet::Ipv4Option(other)
{
    copy(other);
}

Ipv4OptionUnknown::~Ipv4OptionUnknown()
{
    delete [] this->bytes;
}

Ipv4OptionUnknown& Ipv4OptionUnknown::operator=(const Ipv4OptionUnknown& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4Option::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionUnknown::copy(const Ipv4OptionUnknown& other)
{
    delete [] this->bytes;
    this->bytes = (other.bytes_arraysize==0) ? nullptr : new uint8_t[other.bytes_arraysize];
    bytes_arraysize = other.bytes_arraysize;
    for (size_t i = 0; i < bytes_arraysize; i++) {
        this->bytes[i] = other.bytes[i];
    }
}

void Ipv4OptionUnknown::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4Option::parsimPack(b);
    b->pack(bytes_arraysize);
    doParsimArrayPacking(b,this->bytes,bytes_arraysize);
}

void Ipv4OptionUnknown::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4Option::parsimUnpack(b);
    delete [] this->bytes;
    b->unpack(bytes_arraysize);
    if (bytes_arraysize == 0) {
        this->bytes = nullptr;
    } else {
        this->bytes = new uint8_t[bytes_arraysize];
        doParsimArrayUnpacking(b,this->bytes,bytes_arraysize);
    }
}

size_t Ipv4OptionUnknown::getBytesArraySize() const
{
    return bytes_arraysize;
}

uint8_t Ipv4OptionUnknown::getBytes(size_t k) const
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    return this->bytes[k];
}

void Ipv4OptionUnknown::setBytesArraySize(size_t newSize)
{
    uint8_t *bytes2 = (newSize==0) ? nullptr : new uint8_t[newSize];
    size_t minSize = bytes_arraysize < newSize ? bytes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        bytes2[i] = this->bytes[i];
    for (size_t i = minSize; i < newSize; i++)
        bytes2[i] = 0;
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

void Ipv4OptionUnknown::setBytes(size_t k, uint8_t bytes)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    this->bytes[k] = bytes;
}

void Ipv4OptionUnknown::insertBytes(size_t k, uint8_t bytes)
{
    if (k > bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    size_t newSize = bytes_arraysize + 1;
    uint8_t *bytes2 = new uint8_t[newSize];
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

void Ipv4OptionUnknown::appendBytes(uint8_t bytes)
{
    insertBytes(bytes_arraysize, bytes);
}

void Ipv4OptionUnknown::eraseBytes(size_t k)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    size_t newSize = bytes_arraysize - 1;
    uint8_t *bytes2 = (newSize == 0) ? nullptr : new uint8_t[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bytes2[i] = this->bytes[i];
    for (i = k; i < newSize; i++)
        bytes2[i] = this->bytes[i+1];
    delete [] this->bytes;
    this->bytes = bytes2;
    bytes_arraysize = newSize;
}

class Ipv4OptionUnknownDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_bytes,
    };
  public:
    Ipv4OptionUnknownDescriptor();
    virtual ~Ipv4OptionUnknownDescriptor();

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

Register_ClassDescriptor(Ipv4OptionUnknownDescriptor)

Ipv4OptionUnknownDescriptor::Ipv4OptionUnknownDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionUnknown)), "inet::Ipv4Option")
{
    propertyNames = nullptr;
}

Ipv4OptionUnknownDescriptor::~Ipv4OptionUnknownDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionUnknownDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionUnknown *>(obj)!=nullptr;
}

const char **Ipv4OptionUnknownDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionUnknownDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionUnknownDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv4OptionUnknownDescriptor::getFieldTypeFlags(int field) const
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

const char *Ipv4OptionUnknownDescriptor::getFieldName(int field) const
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

int Ipv4OptionUnknownDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "bytes") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionUnknownDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_bytes
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionUnknownDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionUnknownDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionUnknownDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return pp->getBytesArraySize();
        default: return 0;
    }
}

void Ipv4OptionUnknownDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionUnknown'", field);
    }
}

const char *Ipv4OptionUnknownDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionUnknownDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return ulong2string(pp->getBytes(i));
        default: return "";
    }
}

void Ipv4OptionUnknownDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionUnknown'", field);
    }
}

omnetpp::cValue Ipv4OptionUnknownDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return (omnetpp::intval_t)(pp->getBytes(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionUnknown' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionUnknownDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionUnknown'", field);
    }
}

const char *Ipv4OptionUnknownDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ipv4OptionUnknownDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionUnknownDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionUnknown *pp = omnetpp::fromAnyPtr<Ipv4OptionUnknown>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionUnknown'", field);
    }
}

Register_Class(Ipv4Header)

Ipv4Header::Ipv4Header() : ::inet::NetworkHeaderBase()
{
    this->setChunkLength(IPv4_MIN_HEADER_LENGTH);

}

Ipv4Header::Ipv4Header(const Ipv4Header& other) : ::inet::NetworkHeaderBase(other)
{
    copy(other);
}

Ipv4Header::~Ipv4Header()
{
}

Ipv4Header& Ipv4Header::operator=(const Ipv4Header& other)
{
    if (this == &other) return *this;
    ::inet::NetworkHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv4Header::copy(const Ipv4Header& other)
{
    this->version = other.version;
    this->headerLength = other.headerLength;
    this->typeOfService = other.typeOfService;
    this->totalLengthField = other.totalLengthField;
    this->identification = other.identification;
    this->reservedBit = other.reservedBit;
    this->moreFragments = other.moreFragments;
    this->dontFragment = other.dontFragment;
    this->fragmentOffset = other.fragmentOffset;
    this->timeToLive = other.timeToLive;
    this->protocolId = other.protocolId;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
    this->srcAddress = other.srcAddress;
    this->destAddress = other.destAddress;
    this->options = other.options;
}

void Ipv4Header::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NetworkHeaderBase::parsimPack(b);
    doParsimPacking(b,this->version);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->typeOfService);
    doParsimPacking(b,this->totalLengthField);
    doParsimPacking(b,this->identification);
    doParsimPacking(b,this->reservedBit);
    doParsimPacking(b,this->moreFragments);
    doParsimPacking(b,this->dontFragment);
    doParsimPacking(b,this->fragmentOffset);
    doParsimPacking(b,this->timeToLive);
    doParsimPacking(b,this->protocolId);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
    doParsimPacking(b,this->srcAddress);
    doParsimPacking(b,this->destAddress);
    doParsimPacking(b,this->options);
}

void Ipv4Header::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NetworkHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->version);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->typeOfService);
    doParsimUnpacking(b,this->totalLengthField);
    doParsimUnpacking(b,this->identification);
    doParsimUnpacking(b,this->reservedBit);
    doParsimUnpacking(b,this->moreFragments);
    doParsimUnpacking(b,this->dontFragment);
    doParsimUnpacking(b,this->fragmentOffset);
    doParsimUnpacking(b,this->timeToLive);
    doParsimUnpacking(b,this->protocolId);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
    doParsimUnpacking(b,this->srcAddress);
    doParsimUnpacking(b,this->destAddress);
    doParsimUnpacking(b,this->options);
}

short Ipv4Header::getVersion() const
{
    return this->version;
}

void Ipv4Header::setVersion(short version)
{
    handleChange();
    this->version = version;
}

B Ipv4Header::getHeaderLength() const
{
    return this->headerLength;
}

void Ipv4Header::setHeaderLength(B headerLength)
{
    handleChange();
    this->headerLength = headerLength;
}

short Ipv4Header::getTypeOfService() const
{
    return this->typeOfService;
}

void Ipv4Header::setTypeOfService(short typeOfService)
{
    handleChange();
    this->typeOfService = typeOfService;
}

B Ipv4Header::getTotalLengthField() const
{
    return this->totalLengthField;
}

void Ipv4Header::setTotalLengthField(B totalLengthField)
{
    handleChange();
    this->totalLengthField = totalLengthField;
}

uint16_t Ipv4Header::getIdentification() const
{
    return this->identification;
}

void Ipv4Header::setIdentification(uint16_t identification)
{
    handleChange();
    this->identification = identification;
}

bool Ipv4Header::getReservedBit() const
{
    return this->reservedBit;
}

void Ipv4Header::setReservedBit(bool reservedBit)
{
    handleChange();
    this->reservedBit = reservedBit;
}

bool Ipv4Header::getMoreFragments() const
{
    return this->moreFragments;
}

void Ipv4Header::setMoreFragments(bool moreFragments)
{
    handleChange();
    this->moreFragments = moreFragments;
}

bool Ipv4Header::getDontFragment() const
{
    return this->dontFragment;
}

void Ipv4Header::setDontFragment(bool dontFragment)
{
    handleChange();
    this->dontFragment = dontFragment;
}

uint16_t Ipv4Header::getFragmentOffset() const
{
    return this->fragmentOffset;
}

void Ipv4Header::setFragmentOffset(uint16_t fragmentOffset)
{
    handleChange();
    this->fragmentOffset = fragmentOffset;
}

short Ipv4Header::getTimeToLive() const
{
    return this->timeToLive;
}

void Ipv4Header::setTimeToLive(short timeToLive)
{
    handleChange();
    this->timeToLive = timeToLive;
}

IpProtocolId Ipv4Header::getProtocolId() const
{
    return this->protocolId;
}

void Ipv4Header::setProtocolId(IpProtocolId protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

uint16_t Ipv4Header::getCrc() const
{
    return this->crc;
}

void Ipv4Header::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

CrcMode Ipv4Header::getCrcMode() const
{
    return this->crcMode;
}

void Ipv4Header::setCrcMode(CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

const Ipv4Address& Ipv4Header::getSrcAddress() const
{
    return this->srcAddress;
}

void Ipv4Header::setSrcAddress(const Ipv4Address& srcAddress)
{
    handleChange();
    this->srcAddress = srcAddress;
}

const Ipv4Address& Ipv4Header::getDestAddress() const
{
    return this->destAddress;
}

void Ipv4Header::setDestAddress(const Ipv4Address& destAddress)
{
    handleChange();
    this->destAddress = destAddress;
}

const TlvOptions& Ipv4Header::getOptions() const
{
    return this->options;
}

void Ipv4Header::setOptions(const TlvOptions& options)
{
    handleChange();
    this->options = options;
}

class Ipv4HeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_version,
        FIELD_headerLength,
        FIELD_typeOfService,
        FIELD_totalLengthField,
        FIELD_identification,
        FIELD_reservedBit,
        FIELD_moreFragments,
        FIELD_dontFragment,
        FIELD_fragmentOffset,
        FIELD_timeToLive,
        FIELD_protocolId,
        FIELD_crc,
        FIELD_crcMode,
        FIELD_srcAddress,
        FIELD_destAddress,
        FIELD_options,
    };
  public:
    Ipv4HeaderDescriptor();
    virtual ~Ipv4HeaderDescriptor();

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

Register_ClassDescriptor(Ipv4HeaderDescriptor)

Ipv4HeaderDescriptor::Ipv4HeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4Header)), "inet::NetworkHeaderBase")
{
    propertyNames = nullptr;
}

Ipv4HeaderDescriptor::~Ipv4HeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4HeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4Header *>(obj)!=nullptr;
}

const char **Ipv4HeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4HeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4HeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 16+base->getFieldCount() : 16;
}

unsigned int Ipv4HeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_version
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_typeOfService
        FD_ISEDITABLE,    // FIELD_totalLengthField
        FD_ISEDITABLE,    // FIELD_identification
        FD_ISEDITABLE,    // FIELD_reservedBit
        FD_ISEDITABLE,    // FIELD_moreFragments
        FD_ISEDITABLE,    // FIELD_dontFragment
        FD_ISEDITABLE,    // FIELD_fragmentOffset
        FD_ISEDITABLE,    // FIELD_timeToLive
        FD_ISEDITABLE,    // FIELD_protocolId
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
        0,    // FIELD_srcAddress
        0,    // FIELD_destAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_options
    };
    return (field >= 0 && field < 16) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4HeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "version",
        "headerLength",
        "typeOfService",
        "totalLengthField",
        "identification",
        "reservedBit",
        "moreFragments",
        "dontFragment",
        "fragmentOffset",
        "timeToLive",
        "protocolId",
        "crc",
        "crcMode",
        "srcAddress",
        "destAddress",
        "options",
    };
    return (field >= 0 && field < 16) ? fieldNames[field] : nullptr;
}

int Ipv4HeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "version") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "typeOfService") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "totalLengthField") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "identification") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "reservedBit") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "moreFragments") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "dontFragment") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "fragmentOffset") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "timeToLive") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "srcAddress") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "destAddress") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "options") == 0) return baseIndex + 15;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4HeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_version
        "inet::B",    // FIELD_headerLength
        "short",    // FIELD_typeOfService
        "inet::B",    // FIELD_totalLengthField
        "uint16_t",    // FIELD_identification
        "bool",    // FIELD_reservedBit
        "bool",    // FIELD_moreFragments
        "bool",    // FIELD_dontFragment
        "uint16_t",    // FIELD_fragmentOffset
        "short",    // FIELD_timeToLive
        "inet::IpProtocolId",    // FIELD_protocolId
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
        "inet::Ipv4Address",    // FIELD_srcAddress
        "inet::Ipv4Address",    // FIELD_destAddress
        "inet::TlvOptions",    // FIELD_options
    };
    return (field >= 0 && field < 16) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4HeaderDescriptor::getFieldPropertyNames(int field) const
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
        case FIELD_crcMode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv4HeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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
        case FIELD_crcMode:
            if (!strcmp(propertyName, "enum")) return "inet::CrcMode";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv4HeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4HeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4Header'", field);
    }
}

const char *Ipv4HeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4HeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: return long2string(pp->getVersion());
        case FIELD_headerLength: return unit2string(pp->getHeaderLength());
        case FIELD_typeOfService: return long2string(pp->getTypeOfService());
        case FIELD_totalLengthField: return unit2string(pp->getTotalLengthField());
        case FIELD_identification: return ulong2string(pp->getIdentification());
        case FIELD_reservedBit: return bool2string(pp->getReservedBit());
        case FIELD_moreFragments: return bool2string(pp->getMoreFragments());
        case FIELD_dontFragment: return bool2string(pp->getDontFragment());
        case FIELD_fragmentOffset: return ulong2string(pp->getFragmentOffset());
        case FIELD_timeToLive: return long2string(pp->getTimeToLive());
        case FIELD_protocolId: return enum2string(pp->getProtocolId(), "inet::IpProtocolId");
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        case FIELD_srcAddress: return pp->getSrcAddress().str();
        case FIELD_destAddress: return pp->getDestAddress().str();
        case FIELD_options: return pp->getOptions().str();
        default: return "";
    }
}

void Ipv4HeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(string2long(value)); break;
        case FIELD_headerLength: pp->setHeaderLength(B(string2long(value))); break;
        case FIELD_typeOfService: pp->setTypeOfService(string2long(value)); break;
        case FIELD_totalLengthField: pp->setTotalLengthField(B(string2long(value))); break;
        case FIELD_identification: pp->setIdentification(string2ulong(value)); break;
        case FIELD_reservedBit: pp->setReservedBit(string2bool(value)); break;
        case FIELD_moreFragments: pp->setMoreFragments(string2bool(value)); break;
        case FIELD_dontFragment: pp->setDontFragment(string2bool(value)); break;
        case FIELD_fragmentOffset: pp->setFragmentOffset(string2ulong(value)); break;
        case FIELD_timeToLive: pp->setTimeToLive(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId((inet::IpProtocolId)string2enum(value, "inet::IpProtocolId")); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Header'", field);
    }
}

omnetpp::cValue Ipv4HeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: return pp->getVersion();
        case FIELD_headerLength: return cValue(pp->getHeaderLength().get(),"B");
        case FIELD_typeOfService: return pp->getTypeOfService();
        case FIELD_totalLengthField: return cValue(pp->getTotalLengthField().get(),"B");
        case FIELD_identification: return (omnetpp::intval_t)(pp->getIdentification());
        case FIELD_reservedBit: return pp->getReservedBit();
        case FIELD_moreFragments: return pp->getMoreFragments();
        case FIELD_dontFragment: return pp->getDontFragment();
        case FIELD_fragmentOffset: return (omnetpp::intval_t)(pp->getFragmentOffset());
        case FIELD_timeToLive: return pp->getTimeToLive();
        case FIELD_protocolId: return static_cast<int>(pp->getProtocolId());
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4Header' as cValue -- field index out of range?", field);
    }
}

void Ipv4HeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        case FIELD_version: pp->setVersion(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(B(value.intValueInUnit("B"))); break;
        case FIELD_typeOfService: pp->setTypeOfService(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_totalLengthField: pp->setTotalLengthField(B(value.intValueInUnit("B"))); break;
        case FIELD_identification: pp->setIdentification(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_reservedBit: pp->setReservedBit(value.boolValue()); break;
        case FIELD_moreFragments: pp->setMoreFragments(value.boolValue()); break;
        case FIELD_dontFragment: pp->setDontFragment(value.boolValue()); break;
        case FIELD_fragmentOffset: pp->setFragmentOffset(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_timeToLive: pp->setTimeToLive(omnetpp::checked_int_cast<short>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(static_cast<inet::IpProtocolId>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Header'", field);
    }
}

const char *Ipv4HeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_options: return omnetpp::opp_typename(typeid(TlvOptions));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv4HeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddress: return omnetpp::toAnyPtr(&pp->getSrcAddress()); break;
        case FIELD_destAddress: return omnetpp::toAnyPtr(&pp->getDestAddress()); break;
        case FIELD_options: return omnetpp::toAnyPtr(&pp->getOptions()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4HeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4Header *pp = omnetpp::fromAnyPtr<Ipv4Header>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4Header'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

