//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee80211/mgmt/Ieee80211Primitives.msg.
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
#include "Ieee80211Primitives_m.h"

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
namespace ieee80211 {

Register_Enum(inet::ieee80211::Ieee80211PrimRequestCode, (inet::ieee80211::Ieee80211PrimRequestCode::PR_SCAN_REQUEST, inet::ieee80211::Ieee80211PrimRequestCode::PR_AUTHENTICATE_REQUEST, inet::ieee80211::Ieee80211PrimRequestCode::PR_DEAUTHENTICATE_REQUEST, inet::ieee80211::Ieee80211PrimRequestCode::PR_ASSOCIATE_REQUEST, inet::ieee80211::Ieee80211PrimRequestCode::PR_REASSOCIATE_REQUEST, inet::ieee80211::Ieee80211PrimRequestCode::PR_DISASSOCIATE_REQUEST));

Register_Enum(inet::ieee80211::Ieee80211PrimConfirmCode, (inet::ieee80211::Ieee80211PrimConfirmCode::PR_SCAN_CONFIRM, inet::ieee80211::Ieee80211PrimConfirmCode::PR_AUTHENTICATE_CONFIRM, inet::ieee80211::Ieee80211PrimConfirmCode::PR_DEAUTHENTICATE_CONFIRM, inet::ieee80211::Ieee80211PrimConfirmCode::PR_ASSOCIATE_CONFIRM, inet::ieee80211::Ieee80211PrimConfirmCode::PR_REASSOCIATE_CONFIRM, inet::ieee80211::Ieee80211PrimConfirmCode::PR_DISASSOCIATE_CONFIRM));

Register_Enum(inet::ieee80211::Ieee80211BssType, (inet::ieee80211::Ieee80211BssType::BSSTYPE_ANY, inet::ieee80211::Ieee80211BssType::BSSTYPE_INFRASTRUCTURE, inet::ieee80211::Ieee80211BssType::BSSTYPE_INDEPENDENT));

Register_Enum(inet::ieee80211::Ieee80211PrimResultCode, (inet::ieee80211::Ieee80211PrimResultCode::PRC_SUCCESS, inet::ieee80211::Ieee80211PrimResultCode::PRC_INVALID_PARAMETERS, inet::ieee80211::Ieee80211PrimResultCode::PRC_TIMEOUT, inet::ieee80211::Ieee80211PrimResultCode::PRC_TOO_MANY_SIMULTANEOUS_REQUESTS, inet::ieee80211::Ieee80211PrimResultCode::PRC_REFUSED));

Register_Class(Ieee80211PrimRequest)

Ieee80211PrimRequest::Ieee80211PrimRequest() : ::omnetpp::cObject()
{
}

Ieee80211PrimRequest::Ieee80211PrimRequest(const Ieee80211PrimRequest& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee80211PrimRequest::~Ieee80211PrimRequest()
{
}

Ieee80211PrimRequest& Ieee80211PrimRequest::operator=(const Ieee80211PrimRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211PrimRequest::copy(const Ieee80211PrimRequest& other)
{
}

void Ieee80211PrimRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
}

void Ieee80211PrimRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
}

class Ieee80211PrimRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211PrimRequestDescriptor();
    virtual ~Ieee80211PrimRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211PrimRequestDescriptor)

Ieee80211PrimRequestDescriptor::Ieee80211PrimRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211PrimRequest)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ieee80211PrimRequestDescriptor::~Ieee80211PrimRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211PrimRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211PrimRequest *>(obj)!=nullptr;
}

const char **Ieee80211PrimRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211PrimRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211PrimRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211PrimRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211PrimRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211PrimRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211PrimRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211PrimRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211PrimRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211PrimRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211PrimRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211PrimRequest'", field);
    }
}

const char *Ieee80211PrimRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211PrimRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211PrimRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimRequest'", field);
    }
}

omnetpp::cValue Ieee80211PrimRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211PrimRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211PrimRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimRequest'", field);
    }
}

const char *Ieee80211PrimRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211PrimRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211PrimRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimRequest *pp = omnetpp::fromAnyPtr<Ieee80211PrimRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimRequest'", field);
    }
}

Register_Class(Ieee80211PrimConfirm)

Ieee80211PrimConfirm::Ieee80211PrimConfirm() : ::omnetpp::cObject()
{
}

Ieee80211PrimConfirm::Ieee80211PrimConfirm(const Ieee80211PrimConfirm& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee80211PrimConfirm::~Ieee80211PrimConfirm()
{
}

Ieee80211PrimConfirm& Ieee80211PrimConfirm::operator=(const Ieee80211PrimConfirm& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211PrimConfirm::copy(const Ieee80211PrimConfirm& other)
{
    this->resultCode = other.resultCode;
}

void Ieee80211PrimConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->resultCode);
}

void Ieee80211PrimConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->resultCode);
}

Ieee80211PrimResultCode Ieee80211PrimConfirm::getResultCode() const
{
    return this->resultCode;
}

void Ieee80211PrimConfirm::setResultCode(Ieee80211PrimResultCode resultCode)
{
    this->resultCode = resultCode;
}

class Ieee80211PrimConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_resultCode,
    };
  public:
    Ieee80211PrimConfirmDescriptor();
    virtual ~Ieee80211PrimConfirmDescriptor();

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

Register_ClassDescriptor(Ieee80211PrimConfirmDescriptor)

Ieee80211PrimConfirmDescriptor::Ieee80211PrimConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211PrimConfirm)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ieee80211PrimConfirmDescriptor::~Ieee80211PrimConfirmDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211PrimConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211PrimConfirm *>(obj)!=nullptr;
}

const char **Ieee80211PrimConfirmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211PrimConfirmDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211PrimConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211PrimConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_resultCode
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211PrimConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "resultCode",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211PrimConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "resultCode") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211PrimConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211PrimResultCode",    // FIELD_resultCode
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211PrimConfirmDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_resultCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211PrimConfirmDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_resultCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211PrimResultCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211PrimConfirmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211PrimConfirmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211PrimConfirm'", field);
    }
}

const char *Ieee80211PrimConfirmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211PrimConfirmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_resultCode: return enum2string(pp->getResultCode(), "inet::ieee80211::Ieee80211PrimResultCode");
        default: return "";
    }
}

void Ieee80211PrimConfirmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimConfirm'", field);
    }
}

omnetpp::cValue Ieee80211PrimConfirmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_resultCode: return static_cast<int>(pp->getResultCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211PrimConfirm' as cValue -- field index out of range?", field);
    }
}

void Ieee80211PrimConfirmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimConfirm'", field);
    }
}

const char *Ieee80211PrimConfirmDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211PrimConfirmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211PrimConfirmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211PrimConfirm *pp = omnetpp::fromAnyPtr<Ieee80211PrimConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211PrimConfirm'", field);
    }
}

Register_Class(Ieee80211Prim_ScanRequest)

Ieee80211Prim_ScanRequest::Ieee80211Prim_ScanRequest() : ::inet::ieee80211::Ieee80211PrimRequest()
{
}

Ieee80211Prim_ScanRequest::Ieee80211Prim_ScanRequest(const Ieee80211Prim_ScanRequest& other) : ::inet::ieee80211::Ieee80211PrimRequest(other)
{
    copy(other);
}

Ieee80211Prim_ScanRequest::~Ieee80211Prim_ScanRequest()
{
    delete [] this->channelList;
}

Ieee80211Prim_ScanRequest& Ieee80211Prim_ScanRequest::operator=(const Ieee80211Prim_ScanRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_ScanRequest::copy(const Ieee80211Prim_ScanRequest& other)
{
    this->BSSType = other.BSSType;
    this->BSSID = other.BSSID;
    this->SSID = other.SSID;
    this->activeScan = other.activeScan;
    this->probeDelay = other.probeDelay;
    delete [] this->channelList;
    this->channelList = (other.channelList_arraysize==0) ? nullptr : new int[other.channelList_arraysize];
    channelList_arraysize = other.channelList_arraysize;
    for (size_t i = 0; i < channelList_arraysize; i++) {
        this->channelList[i] = other.channelList[i];
    }
    this->minChannelTime = other.minChannelTime;
    this->maxChannelTime = other.maxChannelTime;
}

void Ieee80211Prim_ScanRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimPack(b);
    doParsimPacking(b,this->BSSType);
    doParsimPacking(b,this->BSSID);
    doParsimPacking(b,this->SSID);
    doParsimPacking(b,this->activeScan);
    doParsimPacking(b,this->probeDelay);
    b->pack(channelList_arraysize);
    doParsimArrayPacking(b,this->channelList,channelList_arraysize);
    doParsimPacking(b,this->minChannelTime);
    doParsimPacking(b,this->maxChannelTime);
}

void Ieee80211Prim_ScanRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimUnpack(b);
    doParsimUnpacking(b,this->BSSType);
    doParsimUnpacking(b,this->BSSID);
    doParsimUnpacking(b,this->SSID);
    doParsimUnpacking(b,this->activeScan);
    doParsimUnpacking(b,this->probeDelay);
    delete [] this->channelList;
    b->unpack(channelList_arraysize);
    if (channelList_arraysize == 0) {
        this->channelList = nullptr;
    } else {
        this->channelList = new int[channelList_arraysize];
        doParsimArrayUnpacking(b,this->channelList,channelList_arraysize);
    }
    doParsimUnpacking(b,this->minChannelTime);
    doParsimUnpacking(b,this->maxChannelTime);
}

Ieee80211BssType Ieee80211Prim_ScanRequest::getBSSType() const
{
    return this->BSSType;
}

void Ieee80211Prim_ScanRequest::setBSSType(Ieee80211BssType BSSType)
{
    this->BSSType = BSSType;
}

const ::inet::MacAddress& Ieee80211Prim_ScanRequest::getBSSID() const
{
    return this->BSSID;
}

void Ieee80211Prim_ScanRequest::setBSSID(const ::inet::MacAddress& BSSID)
{
    this->BSSID = BSSID;
}

const char * Ieee80211Prim_ScanRequest::getSSID() const
{
    return this->SSID.c_str();
}

void Ieee80211Prim_ScanRequest::setSSID(const char * SSID)
{
    this->SSID = SSID;
}

bool Ieee80211Prim_ScanRequest::getActiveScan() const
{
    return this->activeScan;
}

void Ieee80211Prim_ScanRequest::setActiveScan(bool activeScan)
{
    this->activeScan = activeScan;
}

::omnetpp::simtime_t Ieee80211Prim_ScanRequest::getProbeDelay() const
{
    return this->probeDelay;
}

void Ieee80211Prim_ScanRequest::setProbeDelay(::omnetpp::simtime_t probeDelay)
{
    this->probeDelay = probeDelay;
}

size_t Ieee80211Prim_ScanRequest::getChannelListArraySize() const
{
    return channelList_arraysize;
}

int Ieee80211Prim_ScanRequest::getChannelList(size_t k) const
{
    if (k >= channelList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)channelList_arraysize, (unsigned long)k);
    return this->channelList[k];
}

void Ieee80211Prim_ScanRequest::setChannelListArraySize(size_t newSize)
{
    int *channelList2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = channelList_arraysize < newSize ? channelList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        channelList2[i] = this->channelList[i];
    for (size_t i = minSize; i < newSize; i++)
        channelList2[i] = 0;
    delete [] this->channelList;
    this->channelList = channelList2;
    channelList_arraysize = newSize;
}

void Ieee80211Prim_ScanRequest::setChannelList(size_t k, int channelList)
{
    if (k >= channelList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)channelList_arraysize, (unsigned long)k);
    this->channelList[k] = channelList;
}

void Ieee80211Prim_ScanRequest::insertChannelList(size_t k, int channelList)
{
    if (k > channelList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)channelList_arraysize, (unsigned long)k);
    size_t newSize = channelList_arraysize + 1;
    int *channelList2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        channelList2[i] = this->channelList[i];
    channelList2[k] = channelList;
    for (i = k + 1; i < newSize; i++)
        channelList2[i] = this->channelList[i-1];
    delete [] this->channelList;
    this->channelList = channelList2;
    channelList_arraysize = newSize;
}

void Ieee80211Prim_ScanRequest::appendChannelList(int channelList)
{
    insertChannelList(channelList_arraysize, channelList);
}

void Ieee80211Prim_ScanRequest::eraseChannelList(size_t k)
{
    if (k >= channelList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)channelList_arraysize, (unsigned long)k);
    size_t newSize = channelList_arraysize - 1;
    int *channelList2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        channelList2[i] = this->channelList[i];
    for (i = k; i < newSize; i++)
        channelList2[i] = this->channelList[i+1];
    delete [] this->channelList;
    this->channelList = channelList2;
    channelList_arraysize = newSize;
}

::omnetpp::simtime_t Ieee80211Prim_ScanRequest::getMinChannelTime() const
{
    return this->minChannelTime;
}

void Ieee80211Prim_ScanRequest::setMinChannelTime(::omnetpp::simtime_t minChannelTime)
{
    this->minChannelTime = minChannelTime;
}

::omnetpp::simtime_t Ieee80211Prim_ScanRequest::getMaxChannelTime() const
{
    return this->maxChannelTime;
}

void Ieee80211Prim_ScanRequest::setMaxChannelTime(::omnetpp::simtime_t maxChannelTime)
{
    this->maxChannelTime = maxChannelTime;
}

class Ieee80211Prim_ScanRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_BSSType,
        FIELD_BSSID,
        FIELD_SSID,
        FIELD_activeScan,
        FIELD_probeDelay,
        FIELD_channelList,
        FIELD_minChannelTime,
        FIELD_maxChannelTime,
    };
  public:
    Ieee80211Prim_ScanRequestDescriptor();
    virtual ~Ieee80211Prim_ScanRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_ScanRequestDescriptor)

Ieee80211Prim_ScanRequestDescriptor::Ieee80211Prim_ScanRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_ScanRequest)), "inet::ieee80211::Ieee80211PrimRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_ScanRequestDescriptor::~Ieee80211Prim_ScanRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_ScanRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_ScanRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_ScanRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_ScanRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_ScanRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int Ieee80211Prim_ScanRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_BSSType
        0,    // FIELD_BSSID
        FD_ISEDITABLE,    // FIELD_SSID
        FD_ISEDITABLE,    // FIELD_activeScan
        FD_ISEDITABLE,    // FIELD_probeDelay
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_channelList
        FD_ISEDITABLE,    // FIELD_minChannelTime
        FD_ISEDITABLE,    // FIELD_maxChannelTime
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_ScanRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "BSSType",
        "BSSID",
        "SSID",
        "activeScan",
        "probeDelay",
        "channelList",
        "minChannelTime",
        "maxChannelTime",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_ScanRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "BSSType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "BSSID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "SSID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "activeScan") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "probeDelay") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "channelList") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "minChannelTime") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "maxChannelTime") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_ScanRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211BssType",    // FIELD_BSSType
        "inet::MacAddress",    // FIELD_BSSID
        "string",    // FIELD_SSID
        "bool",    // FIELD_activeScan
        "omnetpp::simtime_t",    // FIELD_probeDelay
        "int",    // FIELD_channelList
        "omnetpp::simtime_t",    // FIELD_minChannelTime
        "omnetpp::simtime_t",    // FIELD_maxChannelTime
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_ScanRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_BSSType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211Prim_ScanRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_BSSType:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211BssType";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211Prim_ScanRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_channelList: return pp->getChannelListArraySize();
        default: return 0;
    }
}

void Ieee80211Prim_ScanRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_channelList: pp->setChannelListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_ScanRequest'", field);
    }
}

const char *Ieee80211Prim_ScanRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_ScanRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_BSSType: return enum2string(pp->getBSSType(), "inet::ieee80211::Ieee80211BssType");
        case FIELD_BSSID: return pp->getBSSID().str();
        case FIELD_SSID: return oppstring2string(pp->getSSID());
        case FIELD_activeScan: return bool2string(pp->getActiveScan());
        case FIELD_probeDelay: return simtime2string(pp->getProbeDelay());
        case FIELD_channelList: return long2string(pp->getChannelList(i));
        case FIELD_minChannelTime: return simtime2string(pp->getMinChannelTime());
        case FIELD_maxChannelTime: return simtime2string(pp->getMaxChannelTime());
        default: return "";
    }
}

void Ieee80211Prim_ScanRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID((value)); break;
        case FIELD_activeScan: pp->setActiveScan(string2bool(value)); break;
        case FIELD_probeDelay: pp->setProbeDelay(string2simtime(value)); break;
        case FIELD_channelList: pp->setChannelList(i,string2long(value)); break;
        case FIELD_minChannelTime: pp->setMinChannelTime(string2simtime(value)); break;
        case FIELD_maxChannelTime: pp->setMaxChannelTime(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_ScanRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_BSSType: return static_cast<int>(pp->getBSSType());
        case FIELD_BSSID: return omnetpp::toAnyPtr(&pp->getBSSID()); break;
        case FIELD_SSID: return pp->getSSID();
        case FIELD_activeScan: return pp->getActiveScan();
        case FIELD_probeDelay: return pp->getProbeDelay().dbl();
        case FIELD_channelList: return pp->getChannelList(i);
        case FIELD_minChannelTime: return pp->getMinChannelTime().dbl();
        case FIELD_maxChannelTime: return pp->getMaxChannelTime().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_ScanRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_ScanRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_SSID: pp->setSSID(value.stringValue()); break;
        case FIELD_activeScan: pp->setActiveScan(value.boolValue()); break;
        case FIELD_probeDelay: pp->setProbeDelay(value.doubleValue()); break;
        case FIELD_channelList: pp->setChannelList(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_minChannelTime: pp->setMinChannelTime(value.doubleValue()); break;
        case FIELD_maxChannelTime: pp->setMaxChannelTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanRequest'", field);
    }
}

const char *Ieee80211Prim_ScanRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_ScanRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        case FIELD_BSSID: return omnetpp::toAnyPtr(&pp->getBSSID()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_ScanRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanRequest'", field);
    }
}

Register_Class(Ieee80211Prim_BssDescription)

Ieee80211Prim_BssDescription::Ieee80211Prim_BssDescription() : ::omnetpp::cObject()
{
}

Ieee80211Prim_BssDescription::Ieee80211Prim_BssDescription(const Ieee80211Prim_BssDescription& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee80211Prim_BssDescription::~Ieee80211Prim_BssDescription()
{
}

Ieee80211Prim_BssDescription& Ieee80211Prim_BssDescription::operator=(const Ieee80211Prim_BssDescription& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_BssDescription::copy(const Ieee80211Prim_BssDescription& other)
{
    this->channelNumber = other.channelNumber;
    this->BSSID = other.BSSID;
    this->SSID = other.SSID;
    this->supportedRates = other.supportedRates;
    this->beaconInterval = other.beaconInterval;
    this->rxPower = other.rxPower;
}

void Ieee80211Prim_BssDescription::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->channelNumber);
    doParsimPacking(b,this->BSSID);
    doParsimPacking(b,this->SSID);
    doParsimPacking(b,this->supportedRates);
    doParsimPacking(b,this->beaconInterval);
    doParsimPacking(b,this->rxPower);
}

void Ieee80211Prim_BssDescription::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->channelNumber);
    doParsimUnpacking(b,this->BSSID);
    doParsimUnpacking(b,this->SSID);
    doParsimUnpacking(b,this->supportedRates);
    doParsimUnpacking(b,this->beaconInterval);
    doParsimUnpacking(b,this->rxPower);
}

int Ieee80211Prim_BssDescription::getChannelNumber() const
{
    return this->channelNumber;
}

void Ieee80211Prim_BssDescription::setChannelNumber(int channelNumber)
{
    this->channelNumber = channelNumber;
}

const ::inet::MacAddress& Ieee80211Prim_BssDescription::getBSSID() const
{
    return this->BSSID;
}

void Ieee80211Prim_BssDescription::setBSSID(const ::inet::MacAddress& BSSID)
{
    this->BSSID = BSSID;
}

const char * Ieee80211Prim_BssDescription::getSSID() const
{
    return this->SSID.c_str();
}

void Ieee80211Prim_BssDescription::setSSID(const char * SSID)
{
    this->SSID = SSID;
}

const Ieee80211SupportedRatesElement& Ieee80211Prim_BssDescription::getSupportedRates() const
{
    return this->supportedRates;
}

void Ieee80211Prim_BssDescription::setSupportedRates(const Ieee80211SupportedRatesElement& supportedRates)
{
    this->supportedRates = supportedRates;
}

::omnetpp::simtime_t Ieee80211Prim_BssDescription::getBeaconInterval() const
{
    return this->beaconInterval;
}

void Ieee80211Prim_BssDescription::setBeaconInterval(::omnetpp::simtime_t beaconInterval)
{
    this->beaconInterval = beaconInterval;
}

double Ieee80211Prim_BssDescription::getRxPower() const
{
    return this->rxPower;
}

void Ieee80211Prim_BssDescription::setRxPower(double rxPower)
{
    this->rxPower = rxPower;
}

class Ieee80211Prim_BssDescriptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_channelNumber,
        FIELD_BSSID,
        FIELD_SSID,
        FIELD_supportedRates,
        FIELD_beaconInterval,
        FIELD_rxPower,
    };
  public:
    Ieee80211Prim_BssDescriptionDescriptor();
    virtual ~Ieee80211Prim_BssDescriptionDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_BssDescriptionDescriptor)

Ieee80211Prim_BssDescriptionDescriptor::Ieee80211Prim_BssDescriptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_BssDescription)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

Ieee80211Prim_BssDescriptionDescriptor::~Ieee80211Prim_BssDescriptionDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_BssDescriptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_BssDescription *>(obj)!=nullptr;
}

const char **Ieee80211Prim_BssDescriptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_BssDescriptionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_BssDescriptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int Ieee80211Prim_BssDescriptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_channelNumber
        0,    // FIELD_BSSID
        FD_ISEDITABLE,    // FIELD_SSID
        FD_ISCOMPOUND,    // FIELD_supportedRates
        FD_ISEDITABLE,    // FIELD_beaconInterval
        FD_ISEDITABLE,    // FIELD_rxPower
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_BssDescriptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "channelNumber",
        "BSSID",
        "SSID",
        "supportedRates",
        "beaconInterval",
        "rxPower",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_BssDescriptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "channelNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "BSSID") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "SSID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "supportedRates") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "beaconInterval") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "rxPower") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_BssDescriptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_channelNumber
        "inet::MacAddress",    // FIELD_BSSID
        "string",    // FIELD_SSID
        "inet::ieee80211::Ieee80211SupportedRatesElement",    // FIELD_supportedRates
        "omnetpp::simtime_t",    // FIELD_beaconInterval
        "double",    // FIELD_rxPower
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_BssDescriptionDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_BssDescriptionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_BssDescriptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_BssDescriptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_BssDescription'", field);
    }
}

const char *Ieee80211Prim_BssDescriptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_BssDescriptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        case FIELD_channelNumber: return long2string(pp->getChannelNumber());
        case FIELD_BSSID: return pp->getBSSID().str();
        case FIELD_SSID: return oppstring2string(pp->getSSID());
        case FIELD_supportedRates: return "";
        case FIELD_beaconInterval: return simtime2string(pp->getBeaconInterval());
        case FIELD_rxPower: return double2string(pp->getRxPower());
        default: return "";
    }
}

void Ieee80211Prim_BssDescriptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        case FIELD_channelNumber: pp->setChannelNumber(string2long(value)); break;
        case FIELD_SSID: pp->setSSID((value)); break;
        case FIELD_beaconInterval: pp->setBeaconInterval(string2simtime(value)); break;
        case FIELD_rxPower: pp->setRxPower(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_BssDescription'", field);
    }
}

omnetpp::cValue Ieee80211Prim_BssDescriptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        case FIELD_channelNumber: return pp->getChannelNumber();
        case FIELD_BSSID: return omnetpp::toAnyPtr(&pp->getBSSID()); break;
        case FIELD_SSID: return pp->getSSID();
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        case FIELD_beaconInterval: return pp->getBeaconInterval().dbl();
        case FIELD_rxPower: return pp->getRxPower();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_BssDescription' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_BssDescriptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        case FIELD_channelNumber: pp->setChannelNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_SSID: pp->setSSID(value.stringValue()); break;
        case FIELD_beaconInterval: pp->setBeaconInterval(value.doubleValue()); break;
        case FIELD_rxPower: pp->setRxPower(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_BssDescription'", field);
    }
}

const char *Ieee80211Prim_BssDescriptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_supportedRates: return omnetpp::opp_typename(typeid(Ieee80211SupportedRatesElement));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211Prim_BssDescriptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        case FIELD_BSSID: return omnetpp::toAnyPtr(&pp->getBSSID()); break;
        case FIELD_supportedRates: return omnetpp::toAnyPtr(&pp->getSupportedRates()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_BssDescriptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_BssDescription *pp = omnetpp::fromAnyPtr<Ieee80211Prim_BssDescription>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_BssDescription'", field);
    }
}

Register_Class(Ieee80211Prim_ScanConfirm)

Ieee80211Prim_ScanConfirm::Ieee80211Prim_ScanConfirm() : ::inet::ieee80211::Ieee80211PrimConfirm()
{
}

Ieee80211Prim_ScanConfirm::Ieee80211Prim_ScanConfirm(const Ieee80211Prim_ScanConfirm& other) : ::inet::ieee80211::Ieee80211PrimConfirm(other)
{
    copy(other);
}

Ieee80211Prim_ScanConfirm::~Ieee80211Prim_ScanConfirm()
{
    delete [] this->bssList;
}

Ieee80211Prim_ScanConfirm& Ieee80211Prim_ScanConfirm::operator=(const Ieee80211Prim_ScanConfirm& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimConfirm::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_ScanConfirm::copy(const Ieee80211Prim_ScanConfirm& other)
{
    delete [] this->bssList;
    this->bssList = (other.bssList_arraysize==0) ? nullptr : new Ieee80211Prim_BssDescription[other.bssList_arraysize];
    bssList_arraysize = other.bssList_arraysize;
    for (size_t i = 0; i < bssList_arraysize; i++) {
        this->bssList[i] = other.bssList[i];
    }
}

void Ieee80211Prim_ScanConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimPack(b);
    b->pack(bssList_arraysize);
    doParsimArrayPacking(b,this->bssList,bssList_arraysize);
}

void Ieee80211Prim_ScanConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimUnpack(b);
    delete [] this->bssList;
    b->unpack(bssList_arraysize);
    if (bssList_arraysize == 0) {
        this->bssList = nullptr;
    } else {
        this->bssList = new Ieee80211Prim_BssDescription[bssList_arraysize];
        doParsimArrayUnpacking(b,this->bssList,bssList_arraysize);
    }
}

size_t Ieee80211Prim_ScanConfirm::getBssListArraySize() const
{
    return bssList_arraysize;
}

const Ieee80211Prim_BssDescription& Ieee80211Prim_ScanConfirm::getBssList(size_t k) const
{
    if (k >= bssList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bssList_arraysize, (unsigned long)k);
    return this->bssList[k];
}

void Ieee80211Prim_ScanConfirm::setBssListArraySize(size_t newSize)
{
    Ieee80211Prim_BssDescription *bssList2 = (newSize==0) ? nullptr : new Ieee80211Prim_BssDescription[newSize];
    size_t minSize = bssList_arraysize < newSize ? bssList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        bssList2[i] = this->bssList[i];
    delete [] this->bssList;
    this->bssList = bssList2;
    bssList_arraysize = newSize;
}

void Ieee80211Prim_ScanConfirm::setBssList(size_t k, const Ieee80211Prim_BssDescription& bssList)
{
    if (k >= bssList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bssList_arraysize, (unsigned long)k);
    this->bssList[k] = bssList;
}

void Ieee80211Prim_ScanConfirm::insertBssList(size_t k, const Ieee80211Prim_BssDescription& bssList)
{
    if (k > bssList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bssList_arraysize, (unsigned long)k);
    size_t newSize = bssList_arraysize + 1;
    Ieee80211Prim_BssDescription *bssList2 = new Ieee80211Prim_BssDescription[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bssList2[i] = this->bssList[i];
    bssList2[k] = bssList;
    for (i = k + 1; i < newSize; i++)
        bssList2[i] = this->bssList[i-1];
    delete [] this->bssList;
    this->bssList = bssList2;
    bssList_arraysize = newSize;
}

void Ieee80211Prim_ScanConfirm::appendBssList(const Ieee80211Prim_BssDescription& bssList)
{
    insertBssList(bssList_arraysize, bssList);
}

void Ieee80211Prim_ScanConfirm::eraseBssList(size_t k)
{
    if (k >= bssList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bssList_arraysize, (unsigned long)k);
    size_t newSize = bssList_arraysize - 1;
    Ieee80211Prim_BssDescription *bssList2 = (newSize == 0) ? nullptr : new Ieee80211Prim_BssDescription[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        bssList2[i] = this->bssList[i];
    for (i = k; i < newSize; i++)
        bssList2[i] = this->bssList[i+1];
    delete [] this->bssList;
    this->bssList = bssList2;
    bssList_arraysize = newSize;
}

class Ieee80211Prim_ScanConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_bssList,
    };
  public:
    Ieee80211Prim_ScanConfirmDescriptor();
    virtual ~Ieee80211Prim_ScanConfirmDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_ScanConfirmDescriptor)

Ieee80211Prim_ScanConfirmDescriptor::Ieee80211Prim_ScanConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_ScanConfirm)), "inet::ieee80211::Ieee80211PrimConfirm")
{
    propertyNames = nullptr;
}

Ieee80211Prim_ScanConfirmDescriptor::~Ieee80211Prim_ScanConfirmDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_ScanConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_ScanConfirm *>(obj)!=nullptr;
}

const char **Ieee80211Prim_ScanConfirmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_ScanConfirmDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_ScanConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211Prim_ScanConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_bssList
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_ScanConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "bssList",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_ScanConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "bssList") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_ScanConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ieee80211::Ieee80211Prim_BssDescription",    // FIELD_bssList
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_ScanConfirmDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_ScanConfirmDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_ScanConfirmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_bssList: return pp->getBssListArraySize();
        default: return 0;
    }
}

void Ieee80211Prim_ScanConfirmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_bssList: pp->setBssListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_ScanConfirm'", field);
    }
}

const char *Ieee80211Prim_ScanConfirmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_ScanConfirmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_bssList: return pp->getBssList(i).str();
        default: return "";
    }
}

void Ieee80211Prim_ScanConfirmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanConfirm'", field);
    }
}

omnetpp::cValue Ieee80211Prim_ScanConfirmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_bssList: return omnetpp::toAnyPtr(&pp->getBssList(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_ScanConfirm' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_ScanConfirmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanConfirm'", field);
    }
}

const char *Ieee80211Prim_ScanConfirmDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_bssList: return omnetpp::opp_typename(typeid(Ieee80211Prim_BssDescription));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ieee80211Prim_ScanConfirmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_bssList: return omnetpp::toAnyPtr(&pp->getBssList(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_ScanConfirmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ScanConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ScanConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ScanConfirm'", field);
    }
}

Register_Class(Ieee80211Prim_AuthenticateRequest)

Ieee80211Prim_AuthenticateRequest::Ieee80211Prim_AuthenticateRequest() : ::inet::ieee80211::Ieee80211PrimRequest()
{
}

Ieee80211Prim_AuthenticateRequest::Ieee80211Prim_AuthenticateRequest(const Ieee80211Prim_AuthenticateRequest& other) : ::inet::ieee80211::Ieee80211PrimRequest(other)
{
    copy(other);
}

Ieee80211Prim_AuthenticateRequest::~Ieee80211Prim_AuthenticateRequest()
{
}

Ieee80211Prim_AuthenticateRequest& Ieee80211Prim_AuthenticateRequest::operator=(const Ieee80211Prim_AuthenticateRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_AuthenticateRequest::copy(const Ieee80211Prim_AuthenticateRequest& other)
{
    this->address = other.address;
    this->timeout = other.timeout;
}

void Ieee80211Prim_AuthenticateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->timeout);
}

void Ieee80211Prim_AuthenticateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->timeout);
}

const ::inet::MacAddress& Ieee80211Prim_AuthenticateRequest::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_AuthenticateRequest::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

::omnetpp::simtime_t Ieee80211Prim_AuthenticateRequest::getTimeout() const
{
    return this->timeout;
}

void Ieee80211Prim_AuthenticateRequest::setTimeout(::omnetpp::simtime_t timeout)
{
    this->timeout = timeout;
}

class Ieee80211Prim_AuthenticateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_timeout,
    };
  public:
    Ieee80211Prim_AuthenticateRequestDescriptor();
    virtual ~Ieee80211Prim_AuthenticateRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_AuthenticateRequestDescriptor)

Ieee80211Prim_AuthenticateRequestDescriptor::Ieee80211Prim_AuthenticateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_AuthenticateRequest)), "inet::ieee80211::Ieee80211PrimRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_AuthenticateRequestDescriptor::~Ieee80211Prim_AuthenticateRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_AuthenticateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_AuthenticateRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_AuthenticateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_AuthenticateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211Prim_AuthenticateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_timeout
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "timeout",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_AuthenticateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timeout") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
        "omnetpp::simtime_t",    // FIELD_timeout
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_AuthenticateRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_AuthenticateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_AuthenticateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_AuthenticateRequest'", field);
    }
}

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_AuthenticateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_timeout: return simtime2string(pp->getTimeout());
        default: return "";
    }
}

void Ieee80211Prim_AuthenticateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_timeout: pp->setTimeout(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_AuthenticateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_timeout: return pp->getTimeout().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_AuthenticateRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_AuthenticateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_timeout: pp->setTimeout(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateRequest'", field);
    }
}

const char *Ieee80211Prim_AuthenticateRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_AuthenticateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_AuthenticateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateRequest'", field);
    }
}

Register_Class(Ieee80211Prim_AuthenticateConfirm)

Ieee80211Prim_AuthenticateConfirm::Ieee80211Prim_AuthenticateConfirm() : ::inet::ieee80211::Ieee80211PrimConfirm()
{
}

Ieee80211Prim_AuthenticateConfirm::Ieee80211Prim_AuthenticateConfirm(const Ieee80211Prim_AuthenticateConfirm& other) : ::inet::ieee80211::Ieee80211PrimConfirm(other)
{
    copy(other);
}

Ieee80211Prim_AuthenticateConfirm::~Ieee80211Prim_AuthenticateConfirm()
{
}

Ieee80211Prim_AuthenticateConfirm& Ieee80211Prim_AuthenticateConfirm::operator=(const Ieee80211Prim_AuthenticateConfirm& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimConfirm::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_AuthenticateConfirm::copy(const Ieee80211Prim_AuthenticateConfirm& other)
{
    this->address = other.address;
}

void Ieee80211Prim_AuthenticateConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimPack(b);
    doParsimPacking(b,this->address);
}

void Ieee80211Prim_AuthenticateConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
}

const ::inet::MacAddress& Ieee80211Prim_AuthenticateConfirm::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_AuthenticateConfirm::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

class Ieee80211Prim_AuthenticateConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
    };
  public:
    Ieee80211Prim_AuthenticateConfirmDescriptor();
    virtual ~Ieee80211Prim_AuthenticateConfirmDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_AuthenticateConfirmDescriptor)

Ieee80211Prim_AuthenticateConfirmDescriptor::Ieee80211Prim_AuthenticateConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_AuthenticateConfirm)), "inet::ieee80211::Ieee80211PrimConfirm")
{
    propertyNames = nullptr;
}

Ieee80211Prim_AuthenticateConfirmDescriptor::~Ieee80211Prim_AuthenticateConfirmDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_AuthenticateConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_AuthenticateConfirm *>(obj)!=nullptr;
}

const char **Ieee80211Prim_AuthenticateConfirmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_AuthenticateConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_AuthenticateConfirmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_AuthenticateConfirm'", field);
    }
}

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        default: return "";
    }
}

void Ieee80211Prim_AuthenticateConfirmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateConfirm'", field);
    }
}

omnetpp::cValue Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_AuthenticateConfirm' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_AuthenticateConfirmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateConfirm'", field);
    }
}

const char *Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_AuthenticateConfirmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_AuthenticateConfirmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AuthenticateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AuthenticateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AuthenticateConfirm'", field);
    }
}

Register_Class(Ieee80211Prim_DeauthenticateRequest)

Ieee80211Prim_DeauthenticateRequest::Ieee80211Prim_DeauthenticateRequest() : ::inet::ieee80211::Ieee80211PrimRequest()
{
}

Ieee80211Prim_DeauthenticateRequest::Ieee80211Prim_DeauthenticateRequest(const Ieee80211Prim_DeauthenticateRequest& other) : ::inet::ieee80211::Ieee80211PrimRequest(other)
{
    copy(other);
}

Ieee80211Prim_DeauthenticateRequest::~Ieee80211Prim_DeauthenticateRequest()
{
}

Ieee80211Prim_DeauthenticateRequest& Ieee80211Prim_DeauthenticateRequest::operator=(const Ieee80211Prim_DeauthenticateRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_DeauthenticateRequest::copy(const Ieee80211Prim_DeauthenticateRequest& other)
{
    this->address = other.address;
    this->reasonCode = other.reasonCode;
}

void Ieee80211Prim_DeauthenticateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->reasonCode);
}

void Ieee80211Prim_DeauthenticateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->reasonCode);
}

const ::inet::MacAddress& Ieee80211Prim_DeauthenticateRequest::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_DeauthenticateRequest::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

Ieee80211ReasonCode Ieee80211Prim_DeauthenticateRequest::getReasonCode() const
{
    return this->reasonCode;
}

void Ieee80211Prim_DeauthenticateRequest::setReasonCode(Ieee80211ReasonCode reasonCode)
{
    this->reasonCode = reasonCode;
}

class Ieee80211Prim_DeauthenticateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_reasonCode,
    };
  public:
    Ieee80211Prim_DeauthenticateRequestDescriptor();
    virtual ~Ieee80211Prim_DeauthenticateRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_DeauthenticateRequestDescriptor)

Ieee80211Prim_DeauthenticateRequestDescriptor::Ieee80211Prim_DeauthenticateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_DeauthenticateRequest)), "inet::ieee80211::Ieee80211PrimRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_DeauthenticateRequestDescriptor::~Ieee80211Prim_DeauthenticateRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_DeauthenticateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_DeauthenticateRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_DeauthenticateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_reasonCode
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "reasonCode",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_DeauthenticateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reasonCode") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
        "inet::ieee80211::Ieee80211ReasonCode",    // FIELD_reasonCode
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211ReasonCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_DeauthenticateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_DeauthenticateRequest'", field);
    }
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_reasonCode: return enum2string(pp->getReasonCode(), "inet::ieee80211::Ieee80211ReasonCode");
        default: return "";
    }
}

void Ieee80211Prim_DeauthenticateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: pp->setReasonCode((inet::ieee80211::Ieee80211ReasonCode)string2enum(value, "inet::ieee80211::Ieee80211ReasonCode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DeauthenticateRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_reasonCode: return static_cast<int>(pp->getReasonCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_DeauthenticateRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_DeauthenticateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: pp->setReasonCode(static_cast<inet::ieee80211::Ieee80211ReasonCode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DeauthenticateRequest'", field);
    }
}

const char *Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_DeauthenticateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_DeauthenticateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DeauthenticateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DeauthenticateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DeauthenticateRequest'", field);
    }
}

Register_Class(Ieee80211Prim_AssociateRequest)

Ieee80211Prim_AssociateRequest::Ieee80211Prim_AssociateRequest() : ::inet::ieee80211::Ieee80211PrimRequest()
{
}

Ieee80211Prim_AssociateRequest::Ieee80211Prim_AssociateRequest(const Ieee80211Prim_AssociateRequest& other) : ::inet::ieee80211::Ieee80211PrimRequest(other)
{
    copy(other);
}

Ieee80211Prim_AssociateRequest::~Ieee80211Prim_AssociateRequest()
{
}

Ieee80211Prim_AssociateRequest& Ieee80211Prim_AssociateRequest::operator=(const Ieee80211Prim_AssociateRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_AssociateRequest::copy(const Ieee80211Prim_AssociateRequest& other)
{
    this->address = other.address;
    this->timeout = other.timeout;
}

void Ieee80211Prim_AssociateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->timeout);
}

void Ieee80211Prim_AssociateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->timeout);
}

const ::inet::MacAddress& Ieee80211Prim_AssociateRequest::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_AssociateRequest::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

::omnetpp::simtime_t Ieee80211Prim_AssociateRequest::getTimeout() const
{
    return this->timeout;
}

void Ieee80211Prim_AssociateRequest::setTimeout(::omnetpp::simtime_t timeout)
{
    this->timeout = timeout;
}

class Ieee80211Prim_AssociateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_timeout,
    };
  public:
    Ieee80211Prim_AssociateRequestDescriptor();
    virtual ~Ieee80211Prim_AssociateRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_AssociateRequestDescriptor)

Ieee80211Prim_AssociateRequestDescriptor::Ieee80211Prim_AssociateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_AssociateRequest)), "inet::ieee80211::Ieee80211PrimRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_AssociateRequestDescriptor::~Ieee80211Prim_AssociateRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_AssociateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_AssociateRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_AssociateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_AssociateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_AssociateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211Prim_AssociateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_timeout
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_AssociateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "timeout",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_AssociateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timeout") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_AssociateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
        "omnetpp::simtime_t",    // FIELD_timeout
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_AssociateRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_AssociateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_AssociateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_AssociateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_AssociateRequest'", field);
    }
}

const char *Ieee80211Prim_AssociateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_AssociateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_timeout: return simtime2string(pp->getTimeout());
        default: return "";
    }
}

void Ieee80211Prim_AssociateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_timeout: pp->setTimeout(string2simtime(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_AssociateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_timeout: return pp->getTimeout().dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_AssociateRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_AssociateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_timeout: pp->setTimeout(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateRequest'", field);
    }
}

const char *Ieee80211Prim_AssociateRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_AssociateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_AssociateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateRequest'", field);
    }
}

Register_Class(Ieee80211Prim_AssociateConfirm)

Ieee80211Prim_AssociateConfirm::Ieee80211Prim_AssociateConfirm() : ::inet::ieee80211::Ieee80211PrimConfirm()
{
}

Ieee80211Prim_AssociateConfirm::Ieee80211Prim_AssociateConfirm(const Ieee80211Prim_AssociateConfirm& other) : ::inet::ieee80211::Ieee80211PrimConfirm(other)
{
    copy(other);
}

Ieee80211Prim_AssociateConfirm::~Ieee80211Prim_AssociateConfirm()
{
}

Ieee80211Prim_AssociateConfirm& Ieee80211Prim_AssociateConfirm::operator=(const Ieee80211Prim_AssociateConfirm& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimConfirm::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_AssociateConfirm::copy(const Ieee80211Prim_AssociateConfirm& other)
{
    this->address = other.address;
}

void Ieee80211Prim_AssociateConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimPack(b);
    doParsimPacking(b,this->address);
}

void Ieee80211Prim_AssociateConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimConfirm::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
}

const ::inet::MacAddress& Ieee80211Prim_AssociateConfirm::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_AssociateConfirm::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

class Ieee80211Prim_AssociateConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
    };
  public:
    Ieee80211Prim_AssociateConfirmDescriptor();
    virtual ~Ieee80211Prim_AssociateConfirmDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_AssociateConfirmDescriptor)

Ieee80211Prim_AssociateConfirmDescriptor::Ieee80211Prim_AssociateConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_AssociateConfirm)), "inet::ieee80211::Ieee80211PrimConfirm")
{
    propertyNames = nullptr;
}

Ieee80211Prim_AssociateConfirmDescriptor::~Ieee80211Prim_AssociateConfirmDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_AssociateConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_AssociateConfirm *>(obj)!=nullptr;
}

const char **Ieee80211Prim_AssociateConfirmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_AssociateConfirmDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_AssociateConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ieee80211Prim_AssociateConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_AssociateConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_AssociateConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_AssociateConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_AssociateConfirmDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_AssociateConfirmDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_AssociateConfirmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_AssociateConfirmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_AssociateConfirm'", field);
    }
}

const char *Ieee80211Prim_AssociateConfirmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_AssociateConfirmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        default: return "";
    }
}

void Ieee80211Prim_AssociateConfirmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateConfirm'", field);
    }
}

omnetpp::cValue Ieee80211Prim_AssociateConfirmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_AssociateConfirm' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_AssociateConfirmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateConfirm'", field);
    }
}

const char *Ieee80211Prim_AssociateConfirmDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_AssociateConfirmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_AssociateConfirmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_AssociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_AssociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_AssociateConfirm'", field);
    }
}

Register_Class(Ieee80211Prim_ReassociateRequest)

Ieee80211Prim_ReassociateRequest::Ieee80211Prim_ReassociateRequest() : ::inet::ieee80211::Ieee80211Prim_AssociateRequest()
{
}

Ieee80211Prim_ReassociateRequest::Ieee80211Prim_ReassociateRequest(const Ieee80211Prim_ReassociateRequest& other) : ::inet::ieee80211::Ieee80211Prim_AssociateRequest(other)
{
    copy(other);
}

Ieee80211Prim_ReassociateRequest::~Ieee80211Prim_ReassociateRequest()
{
}

Ieee80211Prim_ReassociateRequest& Ieee80211Prim_ReassociateRequest::operator=(const Ieee80211Prim_ReassociateRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211Prim_AssociateRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_ReassociateRequest::copy(const Ieee80211Prim_ReassociateRequest& other)
{
}

void Ieee80211Prim_ReassociateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211Prim_AssociateRequest::parsimPack(b);
}

void Ieee80211Prim_ReassociateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211Prim_AssociateRequest::parsimUnpack(b);
}

class Ieee80211Prim_ReassociateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211Prim_ReassociateRequestDescriptor();
    virtual ~Ieee80211Prim_ReassociateRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_ReassociateRequestDescriptor)

Ieee80211Prim_ReassociateRequestDescriptor::Ieee80211Prim_ReassociateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_ReassociateRequest)), "inet::ieee80211::Ieee80211Prim_AssociateRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_ReassociateRequestDescriptor::~Ieee80211Prim_ReassociateRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_ReassociateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_ReassociateRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_ReassociateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_ReassociateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_ReassociateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211Prim_ReassociateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211Prim_ReassociateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211Prim_ReassociateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_ReassociateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211Prim_ReassociateRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_ReassociateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_ReassociateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_ReassociateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_ReassociateRequest'", field);
    }
}

const char *Ieee80211Prim_ReassociateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_ReassociateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211Prim_ReassociateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_ReassociateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_ReassociateRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_ReassociateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateRequest'", field);
    }
}

const char *Ieee80211Prim_ReassociateRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211Prim_ReassociateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_ReassociateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateRequest'", field);
    }
}

Register_Class(Ieee80211Prim_ReassociateConfirm)

Ieee80211Prim_ReassociateConfirm::Ieee80211Prim_ReassociateConfirm() : ::inet::ieee80211::Ieee80211Prim_AssociateConfirm()
{
}

Ieee80211Prim_ReassociateConfirm::Ieee80211Prim_ReassociateConfirm(const Ieee80211Prim_ReassociateConfirm& other) : ::inet::ieee80211::Ieee80211Prim_AssociateConfirm(other)
{
    copy(other);
}

Ieee80211Prim_ReassociateConfirm::~Ieee80211Prim_ReassociateConfirm()
{
}

Ieee80211Prim_ReassociateConfirm& Ieee80211Prim_ReassociateConfirm::operator=(const Ieee80211Prim_ReassociateConfirm& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211Prim_AssociateConfirm::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_ReassociateConfirm::copy(const Ieee80211Prim_ReassociateConfirm& other)
{
}

void Ieee80211Prim_ReassociateConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211Prim_AssociateConfirm::parsimPack(b);
}

void Ieee80211Prim_ReassociateConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211Prim_AssociateConfirm::parsimUnpack(b);
}

class Ieee80211Prim_ReassociateConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ieee80211Prim_ReassociateConfirmDescriptor();
    virtual ~Ieee80211Prim_ReassociateConfirmDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_ReassociateConfirmDescriptor)

Ieee80211Prim_ReassociateConfirmDescriptor::Ieee80211Prim_ReassociateConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_ReassociateConfirm)), "inet::ieee80211::Ieee80211Prim_AssociateConfirm")
{
    propertyNames = nullptr;
}

Ieee80211Prim_ReassociateConfirmDescriptor::~Ieee80211Prim_ReassociateConfirmDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_ReassociateConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_ReassociateConfirm *>(obj)!=nullptr;
}

const char **Ieee80211Prim_ReassociateConfirmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_ReassociateConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ieee80211Prim_ReassociateConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ieee80211Prim_ReassociateConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ieee80211Prim_ReassociateConfirmDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee80211Prim_ReassociateConfirmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_ReassociateConfirmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_ReassociateConfirm'", field);
    }
}

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_ReassociateConfirmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ieee80211Prim_ReassociateConfirmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateConfirm'", field);
    }
}

omnetpp::cValue Ieee80211Prim_ReassociateConfirmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_ReassociateConfirm' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_ReassociateConfirmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateConfirm'", field);
    }
}

const char *Ieee80211Prim_ReassociateConfirmDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ieee80211Prim_ReassociateConfirmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_ReassociateConfirmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_ReassociateConfirm *pp = omnetpp::fromAnyPtr<Ieee80211Prim_ReassociateConfirm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_ReassociateConfirm'", field);
    }
}

Register_Class(Ieee80211Prim_DisassociateRequest)

Ieee80211Prim_DisassociateRequest::Ieee80211Prim_DisassociateRequest() : ::inet::ieee80211::Ieee80211PrimRequest()
{
}

Ieee80211Prim_DisassociateRequest::Ieee80211Prim_DisassociateRequest(const Ieee80211Prim_DisassociateRequest& other) : ::inet::ieee80211::Ieee80211PrimRequest(other)
{
    copy(other);
}

Ieee80211Prim_DisassociateRequest::~Ieee80211Prim_DisassociateRequest()
{
}

Ieee80211Prim_DisassociateRequest& Ieee80211Prim_DisassociateRequest::operator=(const Ieee80211Prim_DisassociateRequest& other)
{
    if (this == &other) return *this;
    ::inet::ieee80211::Ieee80211PrimRequest::operator=(other);
    copy(other);
    return *this;
}

void Ieee80211Prim_DisassociateRequest::copy(const Ieee80211Prim_DisassociateRequest& other)
{
    this->address = other.address;
    this->reasonCode = other.reasonCode;
}

void Ieee80211Prim_DisassociateRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimPack(b);
    doParsimPacking(b,this->address);
    doParsimPacking(b,this->reasonCode);
}

void Ieee80211Prim_DisassociateRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ieee80211::Ieee80211PrimRequest::parsimUnpack(b);
    doParsimUnpacking(b,this->address);
    doParsimUnpacking(b,this->reasonCode);
}

const ::inet::MacAddress& Ieee80211Prim_DisassociateRequest::getAddress() const
{
    return this->address;
}

void Ieee80211Prim_DisassociateRequest::setAddress(const ::inet::MacAddress& address)
{
    this->address = address;
}

Ieee80211ReasonCode Ieee80211Prim_DisassociateRequest::getReasonCode() const
{
    return this->reasonCode;
}

void Ieee80211Prim_DisassociateRequest::setReasonCode(Ieee80211ReasonCode reasonCode)
{
    this->reasonCode = reasonCode;
}

class Ieee80211Prim_DisassociateRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_address,
        FIELD_reasonCode,
    };
  public:
    Ieee80211Prim_DisassociateRequestDescriptor();
    virtual ~Ieee80211Prim_DisassociateRequestDescriptor();

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

Register_ClassDescriptor(Ieee80211Prim_DisassociateRequestDescriptor)

Ieee80211Prim_DisassociateRequestDescriptor::Ieee80211Prim_DisassociateRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ieee80211::Ieee80211Prim_DisassociateRequest)), "inet::ieee80211::Ieee80211PrimRequest")
{
    propertyNames = nullptr;
}

Ieee80211Prim_DisassociateRequestDescriptor::~Ieee80211Prim_DisassociateRequestDescriptor()
{
    delete[] propertyNames;
}

bool Ieee80211Prim_DisassociateRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee80211Prim_DisassociateRequest *>(obj)!=nullptr;
}

const char **Ieee80211Prim_DisassociateRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee80211Prim_DisassociateRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee80211Prim_DisassociateRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_address
        FD_ISEDITABLE,    // FIELD_reasonCode
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "address",
        "reasonCode",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee80211Prim_DisassociateRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reasonCode") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_address
        "inet::ieee80211::Ieee80211ReasonCode",    // FIELD_reasonCode
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee80211Prim_DisassociateRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reasonCode:
            if (!strcmp(propertyName, "enum")) return "inet::ieee80211::Ieee80211ReasonCode";
            return nullptr;
        default: return nullptr;
    }
}

int Ieee80211Prim_DisassociateRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee80211Prim_DisassociateRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee80211Prim_DisassociateRequest'", field);
    }
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee80211Prim_DisassociateRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return pp->getAddress().str();
        case FIELD_reasonCode: return enum2string(pp->getReasonCode(), "inet::ieee80211::Ieee80211ReasonCode");
        default: return "";
    }
}

void Ieee80211Prim_DisassociateRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: pp->setReasonCode((inet::ieee80211::Ieee80211ReasonCode)string2enum(value, "inet::ieee80211::Ieee80211ReasonCode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DisassociateRequest'", field);
    }
}

omnetpp::cValue Ieee80211Prim_DisassociateRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        case FIELD_reasonCode: return static_cast<int>(pp->getReasonCode());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee80211Prim_DisassociateRequest' as cValue -- field index out of range?", field);
    }
}

void Ieee80211Prim_DisassociateRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_reasonCode: pp->setReasonCode(static_cast<inet::ieee80211::Ieee80211ReasonCode>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DisassociateRequest'", field);
    }
}

const char *Ieee80211Prim_DisassociateRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee80211Prim_DisassociateRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        case FIELD_address: return omnetpp::toAnyPtr(&pp->getAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee80211Prim_DisassociateRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee80211Prim_DisassociateRequest *pp = omnetpp::fromAnyPtr<Ieee80211Prim_DisassociateRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee80211Prim_DisassociateRequest'", field);
    }
}

}  // namespace ieee80211
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

