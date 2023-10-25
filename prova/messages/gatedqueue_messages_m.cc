//
// Generated file, do not edit! Created by opp_msgtool 6.0 from messages/gatedqueue_messages.msg.
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
#include "gatedqueue_messages_m.h"

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

namespace messages {

Register_Class(GQ_ctrl)

GQ_ctrl::GQ_ctrl(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

GQ_ctrl::GQ_ctrl(const GQ_ctrl& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

GQ_ctrl::~GQ_ctrl()
{
}

GQ_ctrl& GQ_ctrl::operator=(const GQ_ctrl& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GQ_ctrl::copy(const GQ_ctrl& other)
{
    this->ctrl_signal = other.ctrl_signal;
    this->is_copy = other.is_copy;
}

void GQ_ctrl::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->ctrl_signal);
    doParsimPacking(b,this->is_copy);
}

void GQ_ctrl::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->ctrl_signal);
    doParsimUnpacking(b,this->is_copy);
}

bool GQ_ctrl::getCtrl_signal() const
{
    return this->ctrl_signal;
}

void GQ_ctrl::setCtrl_signal(bool ctrl_signal)
{
    this->ctrl_signal = ctrl_signal;
}

bool GQ_ctrl::getIs_copy() const
{
    return this->is_copy;
}

void GQ_ctrl::setIs_copy(bool is_copy)
{
    this->is_copy = is_copy;
}

class GQ_ctrlDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ctrl_signal,
        FIELD_is_copy,
    };
  public:
    GQ_ctrlDescriptor();
    virtual ~GQ_ctrlDescriptor();

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

Register_ClassDescriptor(GQ_ctrlDescriptor)

GQ_ctrlDescriptor::GQ_ctrlDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(messages::GQ_ctrl)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

GQ_ctrlDescriptor::~GQ_ctrlDescriptor()
{
    delete[] propertyNames;
}

bool GQ_ctrlDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GQ_ctrl *>(obj)!=nullptr;
}

const char **GQ_ctrlDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GQ_ctrlDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GQ_ctrlDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int GQ_ctrlDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ctrl_signal
        FD_ISEDITABLE,    // FIELD_is_copy
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *GQ_ctrlDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ctrl_signal",
        "is_copy",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int GQ_ctrlDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ctrl_signal") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "is_copy") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *GQ_ctrlDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_ctrl_signal
        "bool",    // FIELD_is_copy
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **GQ_ctrlDescriptor::getFieldPropertyNames(int field) const
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

const char *GQ_ctrlDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GQ_ctrlDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GQ_ctrlDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GQ_ctrl'", field);
    }
}

const char *GQ_ctrlDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GQ_ctrlDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        case FIELD_ctrl_signal: return bool2string(pp->getCtrl_signal());
        case FIELD_is_copy: return bool2string(pp->getIs_copy());
        default: return "";
    }
}

void GQ_ctrlDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        case FIELD_ctrl_signal: pp->setCtrl_signal(string2bool(value)); break;
        case FIELD_is_copy: pp->setIs_copy(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GQ_ctrl'", field);
    }
}

omnetpp::cValue GQ_ctrlDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        case FIELD_ctrl_signal: return pp->getCtrl_signal();
        case FIELD_is_copy: return pp->getIs_copy();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GQ_ctrl' as cValue -- field index out of range?", field);
    }
}

void GQ_ctrlDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        case FIELD_ctrl_signal: pp->setCtrl_signal(value.boolValue()); break;
        case FIELD_is_copy: pp->setIs_copy(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GQ_ctrl'", field);
    }
}

const char *GQ_ctrlDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr GQ_ctrlDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GQ_ctrlDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GQ_ctrl *pp = omnetpp::fromAnyPtr<GQ_ctrl>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GQ_ctrl'", field);
    }
}

NeighborTable::NeighborTable()
{
}

NeighborTable::NeighborTable(const NeighborTable& other)
{
    copy(other);
}

NeighborTable::~NeighborTable()
{
}

NeighborTable& NeighborTable::operator=(const NeighborTable& other)
{
    if (this == &other) return *this;
    copy(other);
    return *this;
}

void NeighborTable::copy(const NeighborTable& other)
{
    this->neighbor = other.neighbor;
    this->st = other.st;
}

void NeighborTable::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->neighbor);
    doParsimPacking(b,this->st);
}

void NeighborTable::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->neighbor);
    doParsimUnpacking(b,this->st);
}

int NeighborTable::getNeighbor() const
{
    return this->neighbor;
}

void NeighborTable::setNeighbor(int neighbor)
{
    this->neighbor = neighbor;
}

const char * NeighborTable::getSt() const
{
    return this->st.c_str();
}

void NeighborTable::setSt(const char * st)
{
    this->st = st;
}

class NeighborTableDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_neighbor,
        FIELD_st,
    };
  public:
    NeighborTableDescriptor();
    virtual ~NeighborTableDescriptor();

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

Register_ClassDescriptor(NeighborTableDescriptor)

NeighborTableDescriptor::NeighborTableDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(messages::NeighborTable)), "")
{
    propertyNames = nullptr;
}

NeighborTableDescriptor::~NeighborTableDescriptor()
{
    delete[] propertyNames;
}

bool NeighborTableDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NeighborTable *>(obj)!=nullptr;
}

const char **NeighborTableDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NeighborTableDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NeighborTableDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int NeighborTableDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_neighbor
        FD_ISEDITABLE,    // FIELD_st
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NeighborTableDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "neighbor",
        "st",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NeighborTableDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "neighbor") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "st") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *NeighborTableDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_neighbor
        "string",    // FIELD_st
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NeighborTableDescriptor::getFieldPropertyNames(int field) const
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

const char *NeighborTableDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int NeighborTableDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NeighborTableDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NeighborTable'", field);
    }
}

const char *NeighborTableDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NeighborTableDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: return long2string(pp->getNeighbor());
        case FIELD_st: return oppstring2string(pp->getSt());
        default: return "";
    }
}

void NeighborTableDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: pp->setNeighbor(string2long(value)); break;
        case FIELD_st: pp->setSt((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NeighborTable'", field);
    }
}

omnetpp::cValue NeighborTableDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: return pp->getNeighbor();
        case FIELD_st: return pp->getSt();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NeighborTable' as cValue -- field index out of range?", field);
    }
}

void NeighborTableDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor: pp->setNeighbor(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_st: pp->setSt(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NeighborTable'", field);
    }
}

const char *NeighborTableDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr NeighborTableDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NeighborTableDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NeighborTable *pp = omnetpp::fromAnyPtr<NeighborTable>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NeighborTable'", field);
    }
}

Register_Class(Header)

Header::Header(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

Header::Header(const Header& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

Header::~Header()
{
}

Header& Header::operator=(const Header& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void Header::copy(const Header& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->hopCount = other.hopCount;
}

void Header::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->hopCount);
}

void Header::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->hopCount);
}

int Header::getSrcAddr() const
{
    return this->srcAddr;
}

void Header::setSrcAddr(int srcAddr)
{
    this->srcAddr = srcAddr;
}

int Header::getDestAddr() const
{
    return this->destAddr;
}

void Header::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int Header::getHopCount() const
{
    return this->hopCount;
}

void Header::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

class HeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_hopCount,
    };
  public:
    HeaderDescriptor();
    virtual ~HeaderDescriptor();

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

Register_ClassDescriptor(HeaderDescriptor)

HeaderDescriptor::HeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(messages::Header)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

HeaderDescriptor::~HeaderDescriptor()
{
    delete[] propertyNames;
}

bool HeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Header *>(obj)!=nullptr;
}

const char **HeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int HeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcAddr
        FD_ISEDITABLE,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_hopCount
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *HeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "hopCount",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int HeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *HeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_srcAddr
        "int",    // FIELD_destAddr
        "int",    // FIELD_hopCount
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **HeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *HeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Header'", field);
    }
}

const char *HeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return long2string(pp->getSrcAddr());
        case FIELD_destAddr: return long2string(pp->getDestAddr());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        default: return "";
    }
}

void HeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(string2long(value)); break;
        case FIELD_destAddr: pp->setDestAddr(string2long(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Header'", field);
    }
}

omnetpp::cValue HeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr();
        case FIELD_destAddr: return pp->getDestAddr();
        case FIELD_hopCount: return pp->getHopCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Header' as cValue -- field index out of range?", field);
    }
}

void HeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        case FIELD_srcAddr: pp->setSrcAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destAddr: pp->setDestAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Header'", field);
    }
}

const char *HeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Header *pp = omnetpp::fromAnyPtr<Header>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Header'", field);
    }
}

Register_Class(OspfPacket)

OspfPacket::OspfPacket(const char *name, short kind) : ::messages::Header(name, kind)
{
}

OspfPacket::OspfPacket(const OspfPacket& other) : ::messages::Header(other)
{
    copy(other);
}

OspfPacket::~OspfPacket()
{
}

OspfPacket& OspfPacket::operator=(const OspfPacket& other)
{
    if (this == &other) return *this;
    ::messages::Header::operator=(other);
    copy(other);
    return *this;
}

void OspfPacket::copy(const OspfPacket& other)
{
    this->sending_gate_index = other.sending_gate_index;
}

void OspfPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::messages::Header::parsimPack(b);
    doParsimPacking(b,this->sending_gate_index);
}

void OspfPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::messages::Header::parsimUnpack(b);
    doParsimUnpacking(b,this->sending_gate_index);
}

int OspfPacket::getSendingGateIndex() const
{
    return this->sending_gate_index;
}

void OspfPacket::setSendingGateIndex(int sending_gate_index)
{
    this->sending_gate_index = sending_gate_index;
}

class OspfPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sending_gate_index,
    };
  public:
    OspfPacketDescriptor();
    virtual ~OspfPacketDescriptor();

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

Register_ClassDescriptor(OspfPacketDescriptor)

OspfPacketDescriptor::OspfPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(messages::OspfPacket)), "messages::Header")
{
    propertyNames = nullptr;
}

OspfPacketDescriptor::~OspfPacketDescriptor()
{
    delete[] propertyNames;
}

bool OspfPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OspfPacket *>(obj)!=nullptr;
}

const char **OspfPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *OspfPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int OspfPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int OspfPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sending_gate_index
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *OspfPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sending_gate_index",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int OspfPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sending_gate_index") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *OspfPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sending_gate_index
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **OspfPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sending_gate_index: {
            static const char *names[] = { "getter", "setter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *OspfPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sending_gate_index:
            if (!strcmp(propertyName, "getter")) return "getSendingGateIndex";
            if (!strcmp(propertyName, "setter")) return "setSendingGateIndex";
            return nullptr;
        default: return nullptr;
    }
}

int OspfPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void OspfPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'OspfPacket'", field);
    }
}

const char *OspfPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OspfPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sending_gate_index: return long2string(pp->getSendingGateIndex());
        default: return "";
    }
}

void OspfPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sending_gate_index: pp->setSendingGateIndex(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacket'", field);
    }
}

omnetpp::cValue OspfPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sending_gate_index: return pp->getSendingGateIndex();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'OspfPacket' as cValue -- field index out of range?", field);
    }
}

void OspfPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sending_gate_index: pp->setSendingGateIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacket'", field);
    }
}

const char *OspfPacketDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr OspfPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void OspfPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfPacket *pp = omnetpp::fromAnyPtr<OspfPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfPacket'", field);
    }
}

Register_Class(OspfHelloPacket)

OspfHelloPacket::OspfHelloPacket(const char *name, short kind) : ::messages::OspfPacket(name, kind)
{
}

OspfHelloPacket::OspfHelloPacket(const OspfHelloPacket& other) : ::messages::OspfPacket(other)
{
    copy(other);
}

OspfHelloPacket::~OspfHelloPacket()
{
}

OspfHelloPacket& OspfHelloPacket::operator=(const OspfHelloPacket& other)
{
    if (this == &other) return *this;
    ::messages::OspfPacket::operator=(other);
    copy(other);
    return *this;
}

void OspfHelloPacket::copy(const OspfHelloPacket& other)
{
    this->neighbor_table = other.neighbor_table;
}

void OspfHelloPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::messages::OspfPacket::parsimPack(b);
    doParsimPacking(b,this->neighbor_table);
}

void OspfHelloPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::messages::OspfPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->neighbor_table);
}

const NeighborTable& OspfHelloPacket::getNeighborTable() const
{
    return this->neighbor_table;
}

void OspfHelloPacket::setNeighborTable(const NeighborTable& neighbor_table)
{
    this->neighbor_table = neighbor_table;
}

class OspfHelloPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_neighbor_table,
    };
  public:
    OspfHelloPacketDescriptor();
    virtual ~OspfHelloPacketDescriptor();

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

Register_ClassDescriptor(OspfHelloPacketDescriptor)

OspfHelloPacketDescriptor::OspfHelloPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(messages::OspfHelloPacket)), "messages::OspfPacket")
{
    propertyNames = nullptr;
}

OspfHelloPacketDescriptor::~OspfHelloPacketDescriptor()
{
    delete[] propertyNames;
}

bool OspfHelloPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<OspfHelloPacket *>(obj)!=nullptr;
}

const char **OspfHelloPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *OspfHelloPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int OspfHelloPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int OspfHelloPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_neighbor_table
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *OspfHelloPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "neighbor_table",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int OspfHelloPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "neighbor_table") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *OspfHelloPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "messages::NeighborTable",    // FIELD_neighbor_table
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **OspfHelloPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_neighbor_table: {
            static const char *names[] = { "getter", "setter",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *OspfHelloPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_neighbor_table:
            if (!strcmp(propertyName, "getter")) return "getNeighborTable";
            if (!strcmp(propertyName, "setter")) return "setNeighborTable";
            return nullptr;
        default: return nullptr;
    }
}

int OspfHelloPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void OspfHelloPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'OspfHelloPacket'", field);
    }
}

const char *OspfHelloPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string OspfHelloPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor_table: return "";
        default: return "";
    }
}

void OspfHelloPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfHelloPacket'", field);
    }
}

omnetpp::cValue OspfHelloPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor_table: return omnetpp::toAnyPtr(&pp->getNeighborTable()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'OspfHelloPacket' as cValue -- field index out of range?", field);
    }
}

void OspfHelloPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfHelloPacket'", field);
    }
}

const char *OspfHelloPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_neighbor_table: return omnetpp::opp_typename(typeid(NeighborTable));
        default: return nullptr;
    };
}

omnetpp::any_ptr OspfHelloPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighbor_table: return omnetpp::toAnyPtr(&pp->getNeighborTable()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void OspfHelloPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    OspfHelloPacket *pp = omnetpp::fromAnyPtr<OspfHelloPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'OspfHelloPacket'", field);
    }
}

}  // namespace messages

namespace omnetpp {

}  // namespace omnetpp

