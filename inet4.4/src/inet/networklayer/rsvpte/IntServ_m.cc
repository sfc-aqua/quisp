//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/IntServ.msg.
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
#include "IntServ_m.h"

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

class EroVectorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    EroVectorDescriptor();
    virtual ~EroVectorDescriptor();

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

Register_ClassDescriptor(EroVectorDescriptor)

EroVectorDescriptor::EroVectorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EroVector)), "")
{
    propertyNames = nullptr;
}

EroVectorDescriptor::~EroVectorDescriptor()
{
    delete[] propertyNames;
}

bool EroVectorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EroVector *>(obj)!=nullptr;
}

const char **EroVectorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EroVectorDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EroVectorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int EroVectorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *EroVectorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int EroVectorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *EroVectorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **EroVectorDescriptor::getFieldPropertyNames(int field) const
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

const char *EroVectorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EroVectorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EroVectorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EroVector'", field);
    }
}

const char *EroVectorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EroVectorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void EroVectorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroVector'", field);
    }
}

omnetpp::cValue EroVectorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EroVector' as cValue -- field index out of range?", field);
    }
}

void EroVectorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroVector'", field);
    }
}

const char *EroVectorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr EroVectorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EroVectorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EroVector *pp = omnetpp::fromAnyPtr<EroVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroVector'", field);
    }
}

class FlowDescriptorVectorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    FlowDescriptorVectorDescriptor();
    virtual ~FlowDescriptorVectorDescriptor();

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

Register_ClassDescriptor(FlowDescriptorVectorDescriptor)

FlowDescriptorVectorDescriptor::FlowDescriptorVectorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FlowDescriptorVector)), "")
{
    propertyNames = nullptr;
}

FlowDescriptorVectorDescriptor::~FlowDescriptorVectorDescriptor()
{
    delete[] propertyNames;
}

bool FlowDescriptorVectorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowDescriptorVector *>(obj)!=nullptr;
}

const char **FlowDescriptorVectorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowDescriptorVectorDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowDescriptorVectorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int FlowDescriptorVectorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *FlowDescriptorVectorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int FlowDescriptorVectorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *FlowDescriptorVectorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **FlowDescriptorVectorDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowDescriptorVectorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FlowDescriptorVectorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FlowDescriptorVectorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowDescriptorVector'", field);
    }
}

const char *FlowDescriptorVectorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowDescriptorVectorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void FlowDescriptorVectorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptorVector'", field);
    }
}

omnetpp::cValue FlowDescriptorVectorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowDescriptorVector' as cValue -- field index out of range?", field);
    }
}

void FlowDescriptorVectorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptorVector'", field);
    }
}

const char *FlowDescriptorVectorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr FlowDescriptorVectorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowDescriptorVectorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptorVector *pp = omnetpp::fromAnyPtr<FlowDescriptorVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptorVector'", field);
    }
}

SessionObj::SessionObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const SessionObj& a)
{
    doParsimPacking(b,a.Tunnel_Id);
    doParsimPacking(b,a.Extended_Tunnel_Id);
    doParsimPacking(b,a.DestAddress);
    doParsimPacking(b,a.setupPri);
    doParsimPacking(b,a.holdingPri);
}

void __doUnpacking(omnetpp::cCommBuffer *b, SessionObj& a)
{
    doParsimUnpacking(b,a.Tunnel_Id);
    doParsimUnpacking(b,a.Extended_Tunnel_Id);
    doParsimUnpacking(b,a.DestAddress);
    doParsimUnpacking(b,a.setupPri);
    doParsimUnpacking(b,a.holdingPri);
}

class SessionObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_Tunnel_Id,
        FIELD_Extended_Tunnel_Id,
        FIELD_DestAddress,
        FIELD_setupPri,
        FIELD_holdingPri,
    };
  public:
    SessionObjDescriptor();
    virtual ~SessionObjDescriptor();

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

Register_ClassDescriptor(SessionObjDescriptor)

SessionObjDescriptor::SessionObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SessionObj)), "")
{
    propertyNames = nullptr;
}

SessionObjDescriptor::~SessionObjDescriptor()
{
    delete[] propertyNames;
}

bool SessionObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SessionObj *>(obj)!=nullptr;
}

const char **SessionObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SessionObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SessionObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int SessionObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_Tunnel_Id
        FD_ISEDITABLE,    // FIELD_Extended_Tunnel_Id
        0,    // FIELD_DestAddress
        FD_ISEDITABLE,    // FIELD_setupPri
        FD_ISEDITABLE,    // FIELD_holdingPri
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *SessionObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Tunnel_Id",
        "Extended_Tunnel_Id",
        "DestAddress",
        "setupPri",
        "holdingPri",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int SessionObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "Tunnel_Id") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "Extended_Tunnel_Id") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "DestAddress") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "setupPri") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "holdingPri") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *SessionObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_Tunnel_Id
        "int",    // FIELD_Extended_Tunnel_Id
        "inet::Ipv4Address",    // FIELD_DestAddress
        "int",    // FIELD_setupPri
        "int",    // FIELD_holdingPri
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **SessionObjDescriptor::getFieldPropertyNames(int field) const
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

const char *SessionObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SessionObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SessionObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SessionObj'", field);
    }
}

const char *SessionObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SessionObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        case FIELD_Tunnel_Id: return long2string(pp->Tunnel_Id);
        case FIELD_Extended_Tunnel_Id: return long2string(pp->Extended_Tunnel_Id);
        case FIELD_DestAddress: return pp->DestAddress.str();
        case FIELD_setupPri: return long2string(pp->setupPri);
        case FIELD_holdingPri: return long2string(pp->holdingPri);
        default: return "";
    }
}

void SessionObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        case FIELD_Tunnel_Id: pp->Tunnel_Id = string2long(value); break;
        case FIELD_Extended_Tunnel_Id: pp->Extended_Tunnel_Id = string2long(value); break;
        case FIELD_setupPri: pp->setupPri = string2long(value); break;
        case FIELD_holdingPri: pp->holdingPri = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SessionObj'", field);
    }
}

omnetpp::cValue SessionObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        case FIELD_Tunnel_Id: return pp->Tunnel_Id;
        case FIELD_Extended_Tunnel_Id: return pp->Extended_Tunnel_Id;
        case FIELD_DestAddress: return omnetpp::toAnyPtr(&pp->DestAddress); break;
        case FIELD_setupPri: return pp->setupPri;
        case FIELD_holdingPri: return pp->holdingPri;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SessionObj' as cValue -- field index out of range?", field);
    }
}

void SessionObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        case FIELD_Tunnel_Id: pp->Tunnel_Id = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_Extended_Tunnel_Id: pp->Extended_Tunnel_Id = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_setupPri: pp->setupPri = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_holdingPri: pp->holdingPri = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SessionObj'", field);
    }
}

const char *SessionObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SessionObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        case FIELD_DestAddress: return omnetpp::toAnyPtr(&pp->DestAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SessionObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SessionObj *pp = omnetpp::fromAnyPtr<SessionObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SessionObj'", field);
    }
}

RsvpHopObj::RsvpHopObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RsvpHopObj& a)
{
    doParsimPacking(b,a.Next_Hop_Address);
    doParsimPacking(b,a.Logical_Interface_Handle);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RsvpHopObj& a)
{
    doParsimUnpacking(b,a.Next_Hop_Address);
    doParsimUnpacking(b,a.Logical_Interface_Handle);
}

class RsvpHopObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_Next_Hop_Address,
        FIELD_Logical_Interface_Handle,
    };
  public:
    RsvpHopObjDescriptor();
    virtual ~RsvpHopObjDescriptor();

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

Register_ClassDescriptor(RsvpHopObjDescriptor)

RsvpHopObjDescriptor::RsvpHopObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::RsvpHopObj)), "")
{
    propertyNames = nullptr;
}

RsvpHopObjDescriptor::~RsvpHopObjDescriptor()
{
    delete[] propertyNames;
}

bool RsvpHopObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RsvpHopObj *>(obj)!=nullptr;
}

const char **RsvpHopObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RsvpHopObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RsvpHopObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RsvpHopObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_Next_Hop_Address
        0,    // FIELD_Logical_Interface_Handle
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RsvpHopObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Next_Hop_Address",
        "Logical_Interface_Handle",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RsvpHopObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "Next_Hop_Address") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "Logical_Interface_Handle") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RsvpHopObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_Next_Hop_Address
        "inet::Ipv4Address",    // FIELD_Logical_Interface_Handle
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RsvpHopObjDescriptor::getFieldPropertyNames(int field) const
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

const char *RsvpHopObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int RsvpHopObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RsvpHopObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RsvpHopObj'", field);
    }
}

const char *RsvpHopObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RsvpHopObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        case FIELD_Next_Hop_Address: return pp->Next_Hop_Address.str();
        case FIELD_Logical_Interface_Handle: return pp->Logical_Interface_Handle.str();
        default: return "";
    }
}

void RsvpHopObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHopObj'", field);
    }
}

omnetpp::cValue RsvpHopObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        case FIELD_Next_Hop_Address: return omnetpp::toAnyPtr(&pp->Next_Hop_Address); break;
        case FIELD_Logical_Interface_Handle: return omnetpp::toAnyPtr(&pp->Logical_Interface_Handle); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RsvpHopObj' as cValue -- field index out of range?", field);
    }
}

void RsvpHopObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHopObj'", field);
    }
}

const char *RsvpHopObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr RsvpHopObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        case FIELD_Next_Hop_Address: return omnetpp::toAnyPtr(&pp->Next_Hop_Address); break;
        case FIELD_Logical_Interface_Handle: return omnetpp::toAnyPtr(&pp->Logical_Interface_Handle); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RsvpHopObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RsvpHopObj *pp = omnetpp::fromAnyPtr<RsvpHopObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RsvpHopObj'", field);
    }
}

SenderTemplateObj::SenderTemplateObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const SenderTemplateObj& a)
{
    doParsimPacking(b,a.SrcAddress);
    doParsimPacking(b,a.Lsp_Id);
}

void __doUnpacking(omnetpp::cCommBuffer *b, SenderTemplateObj& a)
{
    doParsimUnpacking(b,a.SrcAddress);
    doParsimUnpacking(b,a.Lsp_Id);
}

class SenderTemplateObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_SrcAddress,
        FIELD_Lsp_Id,
    };
  public:
    SenderTemplateObjDescriptor();
    virtual ~SenderTemplateObjDescriptor();

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

Register_ClassDescriptor(SenderTemplateObjDescriptor)

SenderTemplateObjDescriptor::SenderTemplateObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SenderTemplateObj)), "")
{
    propertyNames = nullptr;
}

SenderTemplateObjDescriptor::~SenderTemplateObjDescriptor()
{
    delete[] propertyNames;
}

bool SenderTemplateObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SenderTemplateObj *>(obj)!=nullptr;
}

const char **SenderTemplateObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SenderTemplateObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SenderTemplateObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SenderTemplateObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_SrcAddress
        FD_ISEDITABLE,    // FIELD_Lsp_Id
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SenderTemplateObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "SrcAddress",
        "Lsp_Id",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SenderTemplateObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "SrcAddress") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "Lsp_Id") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SenderTemplateObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_SrcAddress
        "int",    // FIELD_Lsp_Id
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SenderTemplateObjDescriptor::getFieldPropertyNames(int field) const
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

const char *SenderTemplateObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SenderTemplateObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SenderTemplateObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SenderTemplateObj'", field);
    }
}

const char *SenderTemplateObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SenderTemplateObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        case FIELD_SrcAddress: return pp->SrcAddress.str();
        case FIELD_Lsp_Id: return long2string(pp->Lsp_Id);
        default: return "";
    }
}

void SenderTemplateObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        case FIELD_Lsp_Id: pp->Lsp_Id = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTemplateObj'", field);
    }
}

omnetpp::cValue SenderTemplateObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        case FIELD_SrcAddress: return omnetpp::toAnyPtr(&pp->SrcAddress); break;
        case FIELD_Lsp_Id: return pp->Lsp_Id;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SenderTemplateObj' as cValue -- field index out of range?", field);
    }
}

void SenderTemplateObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        case FIELD_Lsp_Id: pp->Lsp_Id = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTemplateObj'", field);
    }
}

const char *SenderTemplateObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SenderTemplateObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        case FIELD_SrcAddress: return omnetpp::toAnyPtr(&pp->SrcAddress); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SenderTemplateObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTemplateObj *pp = omnetpp::fromAnyPtr<SenderTemplateObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTemplateObj'", field);
    }
}

SenderTspecObj::SenderTspecObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const SenderTspecObj& a)
{
    doParsimPacking(b,a.req_bandwidth);
}

void __doUnpacking(omnetpp::cCommBuffer *b, SenderTspecObj& a)
{
    doParsimUnpacking(b,a.req_bandwidth);
}

class SenderTspecObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_req_bandwidth,
    };
  public:
    SenderTspecObjDescriptor();
    virtual ~SenderTspecObjDescriptor();

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

Register_ClassDescriptor(SenderTspecObjDescriptor)

SenderTspecObjDescriptor::SenderTspecObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SenderTspecObj)), "")
{
    propertyNames = nullptr;
}

SenderTspecObjDescriptor::~SenderTspecObjDescriptor()
{
    delete[] propertyNames;
}

bool SenderTspecObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SenderTspecObj *>(obj)!=nullptr;
}

const char **SenderTspecObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SenderTspecObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SenderTspecObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int SenderTspecObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_req_bandwidth
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *SenderTspecObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "req_bandwidth",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int SenderTspecObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "req_bandwidth") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *SenderTspecObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_req_bandwidth
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **SenderTspecObjDescriptor::getFieldPropertyNames(int field) const
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

const char *SenderTspecObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SenderTspecObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SenderTspecObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SenderTspecObj'", field);
    }
}

const char *SenderTspecObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SenderTspecObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        case FIELD_req_bandwidth: return double2string(pp->req_bandwidth);
        default: return "";
    }
}

void SenderTspecObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        case FIELD_req_bandwidth: pp->req_bandwidth = string2double(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTspecObj'", field);
    }
}

omnetpp::cValue SenderTspecObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        case FIELD_req_bandwidth: return pp->req_bandwidth;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SenderTspecObj' as cValue -- field index out of range?", field);
    }
}

void SenderTspecObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        case FIELD_req_bandwidth: pp->req_bandwidth = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTspecObj'", field);
    }
}

const char *SenderTspecObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SenderTspecObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SenderTspecObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderTspecObj *pp = omnetpp::fromAnyPtr<SenderTspecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderTspecObj'", field);
    }
}

FlowSpecObj::FlowSpecObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FlowSpecObj& a)
{
    doParsimPacking(b,(::inet::SenderTspecObj&)a);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FlowSpecObj& a)
{
    doParsimUnpacking(b,(::inet::SenderTspecObj&)a);
}

class FlowSpecObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    FlowSpecObjDescriptor();
    virtual ~FlowSpecObjDescriptor();

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

Register_ClassDescriptor(FlowSpecObjDescriptor)

FlowSpecObjDescriptor::FlowSpecObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FlowSpecObj)), "inet::SenderTspecObj")
{
    propertyNames = nullptr;
}

FlowSpecObjDescriptor::~FlowSpecObjDescriptor()
{
    delete[] propertyNames;
}

bool FlowSpecObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowSpecObj *>(obj)!=nullptr;
}

const char **FlowSpecObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowSpecObjDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowSpecObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int FlowSpecObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *FlowSpecObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int FlowSpecObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *FlowSpecObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **FlowSpecObjDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowSpecObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FlowSpecObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FlowSpecObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowSpecObj'", field);
    }
}

const char *FlowSpecObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowSpecObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void FlowSpecObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowSpecObj'", field);
    }
}

omnetpp::cValue FlowSpecObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowSpecObj' as cValue -- field index out of range?", field);
    }
}

void FlowSpecObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowSpecObj'", field);
    }
}

const char *FlowSpecObjDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr FlowSpecObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowSpecObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowSpecObj *pp = omnetpp::fromAnyPtr<FlowSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowSpecObj'", field);
    }
}

FilterSpecObj::FilterSpecObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FilterSpecObj& a)
{
    doParsimPacking(b,(::inet::SenderTemplateObj&)a);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FilterSpecObj& a)
{
    doParsimUnpacking(b,(::inet::SenderTemplateObj&)a);
}

class FilterSpecObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    FilterSpecObjDescriptor();
    virtual ~FilterSpecObjDescriptor();

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

Register_ClassDescriptor(FilterSpecObjDescriptor)

FilterSpecObjDescriptor::FilterSpecObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FilterSpecObj)), "inet::SenderTemplateObj")
{
    propertyNames = nullptr;
}

FilterSpecObjDescriptor::~FilterSpecObjDescriptor()
{
    delete[] propertyNames;
}

bool FilterSpecObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FilterSpecObj *>(obj)!=nullptr;
}

const char **FilterSpecObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FilterSpecObjDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FilterSpecObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int FilterSpecObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *FilterSpecObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int FilterSpecObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *FilterSpecObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **FilterSpecObjDescriptor::getFieldPropertyNames(int field) const
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

const char *FilterSpecObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FilterSpecObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FilterSpecObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FilterSpecObj'", field);
    }
}

const char *FilterSpecObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FilterSpecObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void FilterSpecObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FilterSpecObj'", field);
    }
}

omnetpp::cValue FilterSpecObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FilterSpecObj' as cValue -- field index out of range?", field);
    }
}

void FilterSpecObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FilterSpecObj'", field);
    }
}

const char *FilterSpecObjDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr FilterSpecObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FilterSpecObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FilterSpecObj *pp = omnetpp::fromAnyPtr<FilterSpecObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FilterSpecObj'", field);
    }
}

LabelRequestObj::LabelRequestObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const LabelRequestObj& a)
{
    doParsimPacking(b,a.prot);
}

void __doUnpacking(omnetpp::cCommBuffer *b, LabelRequestObj& a)
{
    doParsimUnpacking(b,a.prot);
}

class LabelRequestObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_prot,
    };
  public:
    LabelRequestObjDescriptor();
    virtual ~LabelRequestObjDescriptor();

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

Register_ClassDescriptor(LabelRequestObjDescriptor)

LabelRequestObjDescriptor::LabelRequestObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LabelRequestObj)), "")
{
    propertyNames = nullptr;
}

LabelRequestObjDescriptor::~LabelRequestObjDescriptor()
{
    delete[] propertyNames;
}

bool LabelRequestObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LabelRequestObj *>(obj)!=nullptr;
}

const char **LabelRequestObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LabelRequestObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LabelRequestObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LabelRequestObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_prot
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LabelRequestObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "prot",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LabelRequestObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "prot") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LabelRequestObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_prot
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LabelRequestObjDescriptor::getFieldPropertyNames(int field) const
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

const char *LabelRequestObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LabelRequestObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LabelRequestObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LabelRequestObj'", field);
    }
}

const char *LabelRequestObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LabelRequestObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        case FIELD_prot: return long2string(pp->prot);
        default: return "";
    }
}

void LabelRequestObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        case FIELD_prot: pp->prot = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelRequestObj'", field);
    }
}

omnetpp::cValue LabelRequestObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        case FIELD_prot: return pp->prot;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LabelRequestObj' as cValue -- field index out of range?", field);
    }
}

void LabelRequestObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        case FIELD_prot: pp->prot = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelRequestObj'", field);
    }
}

const char *LabelRequestObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LabelRequestObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LabelRequestObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelRequestObj *pp = omnetpp::fromAnyPtr<LabelRequestObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelRequestObj'", field);
    }
}

SenderDescriptor_t::SenderDescriptor_t()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const SenderDescriptor_t& a)
{
    doParsimPacking(b,a.Sender_Template_Object);
    doParsimPacking(b,a.Sender_Tspec_Object);
}

void __doUnpacking(omnetpp::cCommBuffer *b, SenderDescriptor_t& a)
{
    doParsimUnpacking(b,a.Sender_Template_Object);
    doParsimUnpacking(b,a.Sender_Tspec_Object);
}

class SenderDescriptor_tDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_Sender_Template_Object,
        FIELD_Sender_Tspec_Object,
    };
  public:
    SenderDescriptor_tDescriptor();
    virtual ~SenderDescriptor_tDescriptor();

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

Register_ClassDescriptor(SenderDescriptor_tDescriptor)

SenderDescriptor_tDescriptor::SenderDescriptor_tDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SenderDescriptor_t)), "")
{
    propertyNames = nullptr;
}

SenderDescriptor_tDescriptor::~SenderDescriptor_tDescriptor()
{
    delete[] propertyNames;
}

bool SenderDescriptor_tDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SenderDescriptor_t *>(obj)!=nullptr;
}

const char **SenderDescriptor_tDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SenderDescriptor_tDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SenderDescriptor_tDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SenderDescriptor_tDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_Sender_Template_Object
        FD_ISCOMPOUND,    // FIELD_Sender_Tspec_Object
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SenderDescriptor_tDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Sender_Template_Object",
        "Sender_Tspec_Object",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SenderDescriptor_tDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "Sender_Template_Object") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "Sender_Tspec_Object") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SenderDescriptor_tDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::SenderTemplateObj",    // FIELD_Sender_Template_Object
        "inet::SenderTspecObj",    // FIELD_Sender_Tspec_Object
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SenderDescriptor_tDescriptor::getFieldPropertyNames(int field) const
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

const char *SenderDescriptor_tDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SenderDescriptor_tDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SenderDescriptor_tDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SenderDescriptor_t'", field);
    }
}

const char *SenderDescriptor_tDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SenderDescriptor_tDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Sender_Template_Object: return "";
        case FIELD_Sender_Tspec_Object: return "";
        default: return "";
    }
}

void SenderDescriptor_tDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderDescriptor_t'", field);
    }
}

omnetpp::cValue SenderDescriptor_tDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Sender_Template_Object: return omnetpp::toAnyPtr(&pp->Sender_Template_Object); break;
        case FIELD_Sender_Tspec_Object: return omnetpp::toAnyPtr(&pp->Sender_Tspec_Object); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SenderDescriptor_t' as cValue -- field index out of range?", field);
    }
}

void SenderDescriptor_tDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderDescriptor_t'", field);
    }
}

const char *SenderDescriptor_tDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_Sender_Template_Object: return omnetpp::opp_typename(typeid(SenderTemplateObj));
        case FIELD_Sender_Tspec_Object: return omnetpp::opp_typename(typeid(SenderTspecObj));
        default: return nullptr;
    };
}

omnetpp::any_ptr SenderDescriptor_tDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Sender_Template_Object: return omnetpp::toAnyPtr(&pp->Sender_Template_Object); break;
        case FIELD_Sender_Tspec_Object: return omnetpp::toAnyPtr(&pp->Sender_Tspec_Object); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SenderDescriptor_tDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SenderDescriptor_t *pp = omnetpp::fromAnyPtr<SenderDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SenderDescriptor_t'", field);
    }
}

EroObj::EroObj()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const EroObj& a)
{
    doParsimPacking(b,a.L);
    doParsimPacking(b,a.node);
}

void __doUnpacking(omnetpp::cCommBuffer *b, EroObj& a)
{
    doParsimUnpacking(b,a.L);
    doParsimUnpacking(b,a.node);
}

class EroObjDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_L,
        FIELD_node,
    };
  public:
    EroObjDescriptor();
    virtual ~EroObjDescriptor();

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

Register_ClassDescriptor(EroObjDescriptor)

EroObjDescriptor::EroObjDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::EroObj)), "")
{
    propertyNames = nullptr;
}

EroObjDescriptor::~EroObjDescriptor()
{
    delete[] propertyNames;
}

bool EroObjDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EroObj *>(obj)!=nullptr;
}

const char **EroObjDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EroObjDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EroObjDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int EroObjDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_L
        0,    // FIELD_node
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *EroObjDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "L",
        "node",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int EroObjDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "L") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "node") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *EroObjDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_L
        "inet::Ipv4Address",    // FIELD_node
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **EroObjDescriptor::getFieldPropertyNames(int field) const
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

const char *EroObjDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int EroObjDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EroObjDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EroObj'", field);
    }
}

const char *EroObjDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EroObjDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        case FIELD_L: return bool2string(pp->L);
        case FIELD_node: return pp->node.str();
        default: return "";
    }
}

void EroObjDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        case FIELD_L: pp->L = string2bool(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroObj'", field);
    }
}

omnetpp::cValue EroObjDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        case FIELD_L: return pp->L;
        case FIELD_node: return omnetpp::toAnyPtr(&pp->node); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EroObj' as cValue -- field index out of range?", field);
    }
}

void EroObjDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        case FIELD_L: pp->L = value.boolValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroObj'", field);
    }
}

const char *EroObjDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr EroObjDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        case FIELD_node: return omnetpp::toAnyPtr(&pp->node); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EroObjDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EroObj *pp = omnetpp::fromAnyPtr<EroObj>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EroObj'", field);
    }
}

FlowDescriptor_t::FlowDescriptor_t()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FlowDescriptor_t& a)
{
    doParsimPacking(b,a.Flowspec_Object);
    doParsimPacking(b,a.Filter_Spec_Object);
    doParsimPacking(b,a.RRO);
    doParsimPacking(b,a.label);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FlowDescriptor_t& a)
{
    doParsimUnpacking(b,a.Flowspec_Object);
    doParsimUnpacking(b,a.Filter_Spec_Object);
    doParsimUnpacking(b,a.RRO);
    doParsimUnpacking(b,a.label);
}

class FlowDescriptor_tDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_Flowspec_Object,
        FIELD_Filter_Spec_Object,
        FIELD_RRO,
        FIELD_label,
    };
  public:
    FlowDescriptor_tDescriptor();
    virtual ~FlowDescriptor_tDescriptor();

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

Register_ClassDescriptor(FlowDescriptor_tDescriptor)

FlowDescriptor_tDescriptor::FlowDescriptor_tDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FlowDescriptor_t)), "")
{
    propertyNames = nullptr;
}

FlowDescriptor_tDescriptor::~FlowDescriptor_tDescriptor()
{
    delete[] propertyNames;
}

bool FlowDescriptor_tDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowDescriptor_t *>(obj)!=nullptr;
}

const char **FlowDescriptor_tDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowDescriptor_tDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowDescriptor_tDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int FlowDescriptor_tDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_Flowspec_Object
        FD_ISCOMPOUND,    // FIELD_Filter_Spec_Object
        FD_ISCOMPOUND,    // FIELD_RRO
        FD_ISEDITABLE,    // FIELD_label
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *FlowDescriptor_tDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Flowspec_Object",
        "Filter_Spec_Object",
        "RRO",
        "label",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int FlowDescriptor_tDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "Flowspec_Object") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "Filter_Spec_Object") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "RRO") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "label") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *FlowDescriptor_tDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::FlowSpecObj",    // FIELD_Flowspec_Object
        "inet::FilterSpecObj",    // FIELD_Filter_Spec_Object
        "inet::Ipv4AddressVector",    // FIELD_RRO
        "int",    // FIELD_label
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowDescriptor_tDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowDescriptor_tDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FlowDescriptor_tDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FlowDescriptor_tDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowDescriptor_t'", field);
    }
}

const char *FlowDescriptor_tDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowDescriptor_tDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Flowspec_Object: return "";
        case FIELD_Filter_Spec_Object: return "";
        case FIELD_RRO: return "";
        case FIELD_label: return long2string(pp->label);
        default: return "";
    }
}

void FlowDescriptor_tDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->label = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptor_t'", field);
    }
}

omnetpp::cValue FlowDescriptor_tDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Flowspec_Object: return omnetpp::toAnyPtr(&pp->Flowspec_Object); break;
        case FIELD_Filter_Spec_Object: return omnetpp::toAnyPtr(&pp->Filter_Spec_Object); break;
        case FIELD_RRO: return omnetpp::toAnyPtr(&pp->RRO); break;
        case FIELD_label: return pp->label;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowDescriptor_t' as cValue -- field index out of range?", field);
    }
}

void FlowDescriptor_tDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_label: pp->label = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptor_t'", field);
    }
}

const char *FlowDescriptor_tDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_Flowspec_Object: return omnetpp::opp_typename(typeid(FlowSpecObj));
        case FIELD_Filter_Spec_Object: return omnetpp::opp_typename(typeid(FilterSpecObj));
        case FIELD_RRO: return omnetpp::opp_typename(typeid(Ipv4AddressVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr FlowDescriptor_tDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        case FIELD_Flowspec_Object: return omnetpp::toAnyPtr(&pp->Flowspec_Object); break;
        case FIELD_Filter_Spec_Object: return omnetpp::toAnyPtr(&pp->Filter_Spec_Object); break;
        case FIELD_RRO: return omnetpp::toAnyPtr(&pp->RRO); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowDescriptor_tDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowDescriptor_t *pp = omnetpp::fromAnyPtr<FlowDescriptor_t>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowDescriptor_t'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

