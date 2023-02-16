//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/queueing/common/LabelsTag.msg.
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
#include "LabelsTag_m.h"

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

Register_Class(LabelsTag)

LabelsTag::LabelsTag() : ::inet::TagBase()
{
}

LabelsTag::LabelsTag(const LabelsTag& other) : ::inet::TagBase(other)
{
    copy(other);
}

LabelsTag::~LabelsTag()
{
    delete [] this->labels;
}

LabelsTag& LabelsTag::operator=(const LabelsTag& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void LabelsTag::copy(const LabelsTag& other)
{
    delete [] this->labels;
    this->labels = (other.labels_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.labels_arraysize];
    labels_arraysize = other.labels_arraysize;
    for (size_t i = 0; i < labels_arraysize; i++) {
        this->labels[i] = other.labels[i];
    }
}

void LabelsTag::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    b->pack(labels_arraysize);
    doParsimArrayPacking(b,this->labels,labels_arraysize);
}

void LabelsTag::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    delete [] this->labels;
    b->unpack(labels_arraysize);
    if (labels_arraysize == 0) {
        this->labels = nullptr;
    } else {
        this->labels = new ::omnetpp::opp_string[labels_arraysize];
        doParsimArrayUnpacking(b,this->labels,labels_arraysize);
    }
}

size_t LabelsTag::getLabelsArraySize() const
{
    return labels_arraysize;
}

const char * LabelsTag::getLabels(size_t k) const
{
    if (k >= labels_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)labels_arraysize, (unsigned long)k);
    return this->labels[k].c_str();
}

void LabelsTag::setLabelsArraySize(size_t newSize)
{
    ::omnetpp::opp_string *labels2 = (newSize==0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t minSize = labels_arraysize < newSize ? labels_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        labels2[i] = this->labels[i];
    delete [] this->labels;
    this->labels = labels2;
    labels_arraysize = newSize;
}

void LabelsTag::setLabels(size_t k, const char * labels)
{
    if (k >= labels_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)labels_arraysize, (unsigned long)k);
    this->labels[k] = labels;
}

void LabelsTag::insertLabels(size_t k, const char * labels)
{
    if (k > labels_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)labels_arraysize, (unsigned long)k);
    size_t newSize = labels_arraysize + 1;
    ::omnetpp::opp_string *labels2 = new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        labels2[i] = this->labels[i];
    labels2[k] = labels;
    for (i = k + 1; i < newSize; i++)
        labels2[i] = this->labels[i-1];
    delete [] this->labels;
    this->labels = labels2;
    labels_arraysize = newSize;
}

void LabelsTag::appendLabels(const char * labels)
{
    insertLabels(labels_arraysize, labels);
}

void LabelsTag::eraseLabels(size_t k)
{
    if (k >= labels_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)labels_arraysize, (unsigned long)k);
    size_t newSize = labels_arraysize - 1;
    ::omnetpp::opp_string *labels2 = (newSize == 0) ? nullptr : new ::omnetpp::opp_string[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        labels2[i] = this->labels[i];
    for (i = k; i < newSize; i++)
        labels2[i] = this->labels[i+1];
    delete [] this->labels;
    this->labels = labels2;
    labels_arraysize = newSize;
}

class LabelsTagDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_labels,
    };
  public:
    LabelsTagDescriptor();
    virtual ~LabelsTagDescriptor();

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

Register_ClassDescriptor(LabelsTagDescriptor)

LabelsTagDescriptor::LabelsTagDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LabelsTag)), "inet::TagBase")
{
    propertyNames = nullptr;
}

LabelsTagDescriptor::~LabelsTagDescriptor()
{
    delete[] propertyNames;
}

bool LabelsTagDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LabelsTag *>(obj)!=nullptr;
}

const char **LabelsTagDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LabelsTagDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LabelsTagDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int LabelsTagDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_labels
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *LabelsTagDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "labels",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int LabelsTagDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "labels") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *LabelsTagDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_labels
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **LabelsTagDescriptor::getFieldPropertyNames(int field) const
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

const char *LabelsTagDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int LabelsTagDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: return pp->getLabelsArraySize();
        default: return 0;
    }
}

void LabelsTagDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: pp->setLabelsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LabelsTag'", field);
    }
}

const char *LabelsTagDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LabelsTagDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: return oppstring2string(pp->getLabels(i));
        default: return "";
    }
}

void LabelsTagDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: pp->setLabels(i,(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelsTag'", field);
    }
}

omnetpp::cValue LabelsTagDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: return pp->getLabels(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LabelsTag' as cValue -- field index out of range?", field);
    }
}

void LabelsTagDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        case FIELD_labels: pp->setLabels(i,value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelsTag'", field);
    }
}

const char *LabelsTagDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr LabelsTagDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LabelsTagDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LabelsTag *pp = omnetpp::fromAnyPtr<LabelsTag>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LabelsTag'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

