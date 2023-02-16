//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wired/ethernet/EthernetSignal.msg.
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
#include "EthernetSignal_m.h"

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

Register_Class(EthernetSignalBase)

EthernetSignalBase::EthernetSignalBase(const char *name, short kind) : ::inet::physicallayer::Signal(name, kind)
{
}

EthernetSignalBase::EthernetSignalBase(const EthernetSignalBase& other) : ::inet::physicallayer::Signal(other)
{
    copy(other);
}

EthernetSignalBase::~EthernetSignalBase()
{
}

EthernetSignalBase& EthernetSignalBase::operator=(const EthernetSignalBase& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::Signal::operator=(other);
    copy(other);
    return *this;
}

void EthernetSignalBase::copy(const EthernetSignalBase& other)
{
    this->srcMacFullDuplex = other.srcMacFullDuplex;
    this->bitrate = other.bitrate;
}

void EthernetSignalBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::Signal::parsimPack(b);
    doParsimPacking(b,this->srcMacFullDuplex);
    doParsimPacking(b,this->bitrate);
}

void EthernetSignalBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::Signal::parsimUnpack(b);
    doParsimUnpacking(b,this->srcMacFullDuplex);
    doParsimUnpacking(b,this->bitrate);
}

bool EthernetSignalBase::getSrcMacFullDuplex() const
{
    return this->srcMacFullDuplex;
}

void EthernetSignalBase::setSrcMacFullDuplex(bool srcMacFullDuplex)
{
    this->srcMacFullDuplex = srcMacFullDuplex;
}

double EthernetSignalBase::getBitrate() const
{
    return this->bitrate;
}

void EthernetSignalBase::setBitrate(double bitrate)
{
    this->bitrate = bitrate;
}

class EthernetSignalBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcMacFullDuplex,
        FIELD_bitrate,
    };
  public:
    EthernetSignalBaseDescriptor();
    virtual ~EthernetSignalBaseDescriptor();

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

Register_ClassDescriptor(EthernetSignalBaseDescriptor)

EthernetSignalBaseDescriptor::EthernetSignalBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetSignalBase)), "inet::physicallayer::Signal")
{
    propertyNames = nullptr;
}

EthernetSignalBaseDescriptor::~EthernetSignalBaseDescriptor()
{
    delete[] propertyNames;
}

bool EthernetSignalBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetSignalBase *>(obj)!=nullptr;
}

const char **EthernetSignalBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetSignalBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetSignalBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int EthernetSignalBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcMacFullDuplex
        FD_ISEDITABLE,    // FIELD_bitrate
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *EthernetSignalBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcMacFullDuplex",
        "bitrate",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int EthernetSignalBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcMacFullDuplex") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "bitrate") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetSignalBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_srcMacFullDuplex
        "double",    // FIELD_bitrate
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **EthernetSignalBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetSignalBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetSignalBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetSignalBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetSignalBase'", field);
    }
}

const char *EthernetSignalBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetSignalBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcMacFullDuplex: return bool2string(pp->getSrcMacFullDuplex());
        case FIELD_bitrate: return double2string(pp->getBitrate());
        default: return "";
    }
}

void EthernetSignalBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcMacFullDuplex: pp->setSrcMacFullDuplex(string2bool(value)); break;
        case FIELD_bitrate: pp->setBitrate(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignalBase'", field);
    }
}

omnetpp::cValue EthernetSignalBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcMacFullDuplex: return pp->getSrcMacFullDuplex();
        case FIELD_bitrate: return pp->getBitrate();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetSignalBase' as cValue -- field index out of range?", field);
    }
}

void EthernetSignalBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        case FIELD_srcMacFullDuplex: pp->setSrcMacFullDuplex(value.boolValue()); break;
        case FIELD_bitrate: pp->setBitrate(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignalBase'", field);
    }
}

const char *EthernetSignalBaseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EthernetSignalBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetSignalBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignalBase *pp = omnetpp::fromAnyPtr<EthernetSignalBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignalBase'", field);
    }
}

Register_Class(EthernetSignal)

EthernetSignal::EthernetSignal(const char *name, short kind) : ::inet::physicallayer::EthernetSignalBase(name, kind)
{
}

EthernetSignal::EthernetSignal(const EthernetSignal& other) : ::inet::physicallayer::EthernetSignalBase(other)
{
    copy(other);
}

EthernetSignal::~EthernetSignal()
{
}

EthernetSignal& EthernetSignal::operator=(const EthernetSignal& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::EthernetSignalBase::operator=(other);
    copy(other);
    return *this;
}

void EthernetSignal::copy(const EthernetSignal& other)
{
}

void EthernetSignal::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::EthernetSignalBase::parsimPack(b);
}

void EthernetSignal::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::EthernetSignalBase::parsimUnpack(b);
}

class EthernetSignalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EthernetSignalDescriptor();
    virtual ~EthernetSignalDescriptor();

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

Register_ClassDescriptor(EthernetSignalDescriptor)

EthernetSignalDescriptor::EthernetSignalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetSignal)), "inet::physicallayer::EthernetSignalBase")
{
    propertyNames = nullptr;
}

EthernetSignalDescriptor::~EthernetSignalDescriptor()
{
    delete[] propertyNames;
}

bool EthernetSignalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetSignal *>(obj)!=nullptr;
}

const char **EthernetSignalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetSignalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetSignalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EthernetSignalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EthernetSignalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EthernetSignalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetSignalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EthernetSignalDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetSignalDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetSignalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetSignalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetSignal'", field);
    }
}

const char *EthernetSignalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetSignalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EthernetSignalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignal'", field);
    }
}

omnetpp::cValue EthernetSignalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetSignal' as cValue -- field index out of range?", field);
    }
}

void EthernetSignalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignal'", field);
    }
}

const char *EthernetSignalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EthernetSignalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetSignalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetSignal *pp = omnetpp::fromAnyPtr<EthernetSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetSignal'", field);
    }
}

Register_Class(EthernetJamSignal)

EthernetJamSignal::EthernetJamSignal(const char *name, short kind) : ::inet::physicallayer::EthernetSignalBase(name, kind)
{
    this->setSrcMacFullDuplex(false);

}

EthernetJamSignal::EthernetJamSignal(const EthernetJamSignal& other) : ::inet::physicallayer::EthernetSignalBase(other)
{
    copy(other);
}

EthernetJamSignal::~EthernetJamSignal()
{
}

EthernetJamSignal& EthernetJamSignal::operator=(const EthernetJamSignal& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::EthernetSignalBase::operator=(other);
    copy(other);
    return *this;
}

void EthernetJamSignal::copy(const EthernetJamSignal& other)
{
    this->abortedPkTreeID = other.abortedPkTreeID;
}

void EthernetJamSignal::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::EthernetSignalBase::parsimPack(b);
    doParsimPacking(b,this->abortedPkTreeID);
}

void EthernetJamSignal::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::EthernetSignalBase::parsimUnpack(b);
    doParsimUnpacking(b,this->abortedPkTreeID);
}

long EthernetJamSignal::getAbortedPkTreeID() const
{
    return this->abortedPkTreeID;
}

void EthernetJamSignal::setAbortedPkTreeID(long abortedPkTreeID)
{
    this->abortedPkTreeID = abortedPkTreeID;
}

class EthernetJamSignalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_abortedPkTreeID,
    };
  public:
    EthernetJamSignalDescriptor();
    virtual ~EthernetJamSignalDescriptor();

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

Register_ClassDescriptor(EthernetJamSignalDescriptor)

EthernetJamSignalDescriptor::EthernetJamSignalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetJamSignal)), "inet::physicallayer::EthernetSignalBase")
{
    propertyNames = nullptr;
}

EthernetJamSignalDescriptor::~EthernetJamSignalDescriptor()
{
    delete[] propertyNames;
}

bool EthernetJamSignalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetJamSignal *>(obj)!=nullptr;
}

const char **EthernetJamSignalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetJamSignalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetJamSignalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int EthernetJamSignalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_abortedPkTreeID
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *EthernetJamSignalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "abortedPkTreeID",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int EthernetJamSignalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "abortedPkTreeID") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetJamSignalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "long",    // FIELD_abortedPkTreeID
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **EthernetJamSignalDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetJamSignalDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetJamSignalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetJamSignalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetJamSignal'", field);
    }
}

const char *EthernetJamSignalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetJamSignalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        case FIELD_abortedPkTreeID: return long2string(pp->getAbortedPkTreeID());
        default: return "";
    }
}

void EthernetJamSignalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        case FIELD_abortedPkTreeID: pp->setAbortedPkTreeID(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetJamSignal'", field);
    }
}

omnetpp::cValue EthernetJamSignalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        case FIELD_abortedPkTreeID: return (omnetpp::intval_t)(pp->getAbortedPkTreeID());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetJamSignal' as cValue -- field index out of range?", field);
    }
}

void EthernetJamSignalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        case FIELD_abortedPkTreeID: pp->setAbortedPkTreeID(omnetpp::checked_int_cast<long>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetJamSignal'", field);
    }
}

const char *EthernetJamSignalDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EthernetJamSignalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetJamSignalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetJamSignal *pp = omnetpp::fromAnyPtr<EthernetJamSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetJamSignal'", field);
    }
}

Register_Class(EthernetFilledIfgSignal)

EthernetFilledIfgSignal::EthernetFilledIfgSignal(const char *name, short kind) : ::inet::physicallayer::EthernetSignalBase(name, kind)
{
    this->setSrcMacFullDuplex(false);
    this->setBitLength(b(INTERFRAME_GAP_BITS).get());
}

EthernetFilledIfgSignal::EthernetFilledIfgSignal(const EthernetFilledIfgSignal& other) : ::inet::physicallayer::EthernetSignalBase(other)
{
    copy(other);
}

EthernetFilledIfgSignal::~EthernetFilledIfgSignal()
{
}

EthernetFilledIfgSignal& EthernetFilledIfgSignal::operator=(const EthernetFilledIfgSignal& other)
{
    if (this == &other) return *this;
    ::inet::physicallayer::EthernetSignalBase::operator=(other);
    copy(other);
    return *this;
}

void EthernetFilledIfgSignal::copy(const EthernetFilledIfgSignal& other)
{
}

void EthernetFilledIfgSignal::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::physicallayer::EthernetSignalBase::parsimPack(b);
}

void EthernetFilledIfgSignal::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::physicallayer::EthernetSignalBase::parsimUnpack(b);
}

class EthernetFilledIfgSignalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EthernetFilledIfgSignalDescriptor();
    virtual ~EthernetFilledIfgSignalDescriptor();

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

Register_ClassDescriptor(EthernetFilledIfgSignalDescriptor)

EthernetFilledIfgSignalDescriptor::EthernetFilledIfgSignalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::physicallayer::EthernetFilledIfgSignal)), "inet::physicallayer::EthernetSignalBase")
{
    propertyNames = nullptr;
}

EthernetFilledIfgSignalDescriptor::~EthernetFilledIfgSignalDescriptor()
{
    delete[] propertyNames;
}

bool EthernetFilledIfgSignalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetFilledIfgSignal *>(obj)!=nullptr;
}

const char **EthernetFilledIfgSignalDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetFilledIfgSignalDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetFilledIfgSignalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EthernetFilledIfgSignalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EthernetFilledIfgSignalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EthernetFilledIfgSignalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetFilledIfgSignalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EthernetFilledIfgSignalDescriptor::getFieldPropertyNames(int field) const
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

const char *EthernetFilledIfgSignalDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EthernetFilledIfgSignalDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetFilledIfgSignalDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetFilledIfgSignal'", field);
    }
}

const char *EthernetFilledIfgSignalDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetFilledIfgSignalDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EthernetFilledIfgSignalDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFilledIfgSignal'", field);
    }
}

omnetpp::cValue EthernetFilledIfgSignalDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetFilledIfgSignal' as cValue -- field index out of range?", field);
    }
}

void EthernetFilledIfgSignalDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFilledIfgSignal'", field);
    }
}

const char *EthernetFilledIfgSignalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EthernetFilledIfgSignalDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetFilledIfgSignalDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFilledIfgSignal *pp = omnetpp::fromAnyPtr<EthernetFilledIfgSignal>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFilledIfgSignal'", field);
    }
}

}  // namespace physicallayer
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

