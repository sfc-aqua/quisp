//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/Ipv4OptionsTag.msg.
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
#include "Ipv4OptionsTag_m.h"

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

Register_Class(Ipv4OptionsTagBase)

Ipv4OptionsTagBase::Ipv4OptionsTagBase() : ::inet::TagBase()
{
}

Ipv4OptionsTagBase::Ipv4OptionsTagBase(const Ipv4OptionsTagBase& other) : ::inet::TagBase(other)
{
    copy(other);
}

Ipv4OptionsTagBase::~Ipv4OptionsTagBase()
{
    for (size_t i = 0; i < option_arraysize; i++)
        delete this->option[i];
    delete [] this->option;
}

Ipv4OptionsTagBase& Ipv4OptionsTagBase::operator=(const Ipv4OptionsTagBase& other)
{
    if (this == &other) return *this;
    ::inet::TagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionsTagBase::copy(const Ipv4OptionsTagBase& other)
{
    for (size_t i = 0; i < option_arraysize; i++)
        delete this->option[i];
    delete [] this->option;
    this->option = (other.option_arraysize==0) ? nullptr : new Ipv4Option *[other.option_arraysize];
    option_arraysize = other.option_arraysize;
    for (size_t i = 0; i < option_arraysize; i++) {
        this->option[i] = other.option[i];
        if (this->option[i] != nullptr) {
            this->option[i] = this->option[i]->dup();
        }
    }
}

void Ipv4OptionsTagBase::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TagBase::parsimPack(b);
    b->pack(option_arraysize);
    doParsimArrayPacking(b,this->option,option_arraysize);
}

void Ipv4OptionsTagBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TagBase::parsimUnpack(b);
    delete [] this->option;
    b->unpack(option_arraysize);
    if (option_arraysize == 0) {
        this->option = nullptr;
    } else {
        this->option = new Ipv4Option *[option_arraysize];
        doParsimArrayUnpacking(b,this->option,option_arraysize);
    }
}

size_t Ipv4OptionsTagBase::getOptionArraySize() const
{
    return option_arraysize;
}

const Ipv4Option * Ipv4OptionsTagBase::getOption(size_t k) const
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    return this->option[k];
}

void Ipv4OptionsTagBase::setOptionArraySize(size_t newSize)
{
    Ipv4Option * *option2 = (newSize==0) ? nullptr : new Ipv4Option *[newSize];
    size_t minSize = option_arraysize < newSize ? option_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        option2[i] = this->option[i];
    for (size_t i = minSize; i < newSize; i++)
        option2[i] = nullptr;
    for (size_t i = newSize; i < option_arraysize; i++)
        delete option[i];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

void Ipv4OptionsTagBase::setOption(size_t k, Ipv4Option * option)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    if (this->option[k] != nullptr) throw omnetpp::cRuntimeError("setOption(): a value is already set, remove it first with removeOption()");
    this->option[k] = option;
    if (this->option[k] != nullptr && this->option[k]->isOwnedObject()) take((cOwnedObject*)this->option[k]);
}

Ipv4Option * Ipv4OptionsTagBase::removeOption(size_t k)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    Ipv4Option * retval = this->option[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->option[k] = nullptr;
    return retval;
}

void Ipv4OptionsTagBase::insertOption(size_t k, Ipv4Option * option)
{
    if (k > option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    size_t newSize = option_arraysize + 1;
    Ipv4Option * *option2 = new Ipv4Option *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        option2[i] = this->option[i];
    option2[k] = option;
    if (option2[k] != nullptr && option2[k]->isOwnedObject()) take((cOwnedObject*)option2[k]);
    for (i = k + 1; i < newSize; i++)
        option2[i] = this->option[i-1];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

void Ipv4OptionsTagBase::appendOption(Ipv4Option * option)
{
    insertOption(option_arraysize, option);
}

void Ipv4OptionsTagBase::eraseOption(size_t k)
{
    if (k >= option_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)option_arraysize, (unsigned long)k);
    size_t newSize = option_arraysize - 1;
    Ipv4Option * *option2 = (newSize == 0) ? nullptr : new Ipv4Option *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        option2[i] = this->option[i];
    for (i = k; i < newSize; i++)
        option2[i] = this->option[i+1];
    if (this->option[k] != nullptr && this->option[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->option[k]); else delete this->option[k];
    delete [] this->option;
    this->option = option2;
    option_arraysize = newSize;
}

class Ipv4OptionsTagBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_option,
    };
  public:
    Ipv4OptionsTagBaseDescriptor();
    virtual ~Ipv4OptionsTagBaseDescriptor();

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

Register_ClassDescriptor(Ipv4OptionsTagBaseDescriptor)

Ipv4OptionsTagBaseDescriptor::Ipv4OptionsTagBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionsTagBase)), "inet::TagBase")
{
    propertyNames = nullptr;
}

Ipv4OptionsTagBaseDescriptor::~Ipv4OptionsTagBaseDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionsTagBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionsTagBase *>(obj)!=nullptr;
}

const char **Ipv4OptionsTagBaseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionsTagBaseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionsTagBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int Ipv4OptionsTagBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_option
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv4OptionsTagBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "option",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv4OptionsTagBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "option") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionsTagBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Option",    // FIELD_option
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv4OptionsTagBaseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *Ipv4OptionsTagBaseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int Ipv4OptionsTagBaseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: return pp->getOptionArraySize();
        default: return 0;
    }
}

void Ipv4OptionsTagBaseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOptionArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionsTagBase'", field);
    }
}

const char *Ipv4OptionsTagBaseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: { const Ipv4Option * value = pp->getOption(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string Ipv4OptionsTagBaseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: { auto obj = pp->getOption(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void Ipv4OptionsTagBaseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsTagBase'", field);
    }
}

omnetpp::cValue Ipv4OptionsTagBaseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: return omnetpp::toAnyPtr(pp->getOption(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionsTagBase' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionsTagBaseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOption(i,omnetpp::fromAnyPtr<Ipv4Option>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsTagBase'", field);
    }
}

const char *Ipv4OptionsTagBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_option: return omnetpp::opp_typename(typeid(Ipv4Option));
        default: return nullptr;
    };
}

omnetpp::any_ptr Ipv4OptionsTagBaseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: return omnetpp::toAnyPtr(pp->getOption(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionsTagBaseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsTagBase *pp = omnetpp::fromAnyPtr<Ipv4OptionsTagBase>(object); (void)pp;
    switch (field) {
        case FIELD_option: pp->setOption(i,omnetpp::fromAnyPtr<Ipv4Option>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsTagBase'", field);
    }
}

Register_Class(Ipv4OptionsReq)

Ipv4OptionsReq::Ipv4OptionsReq() : ::inet::Ipv4OptionsTagBase()
{
}

Ipv4OptionsReq::Ipv4OptionsReq(const Ipv4OptionsReq& other) : ::inet::Ipv4OptionsTagBase(other)
{
    copy(other);
}

Ipv4OptionsReq::~Ipv4OptionsReq()
{
}

Ipv4OptionsReq& Ipv4OptionsReq::operator=(const Ipv4OptionsReq& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4OptionsTagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionsReq::copy(const Ipv4OptionsReq& other)
{
}

void Ipv4OptionsReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4OptionsTagBase::parsimPack(b);
}

void Ipv4OptionsReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4OptionsTagBase::parsimUnpack(b);
}

class Ipv4OptionsReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv4OptionsReqDescriptor();
    virtual ~Ipv4OptionsReqDescriptor();

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

Register_ClassDescriptor(Ipv4OptionsReqDescriptor)

Ipv4OptionsReqDescriptor::Ipv4OptionsReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionsReq)), "inet::Ipv4OptionsTagBase")
{
    propertyNames = nullptr;
}

Ipv4OptionsReqDescriptor::~Ipv4OptionsReqDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionsReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionsReq *>(obj)!=nullptr;
}

const char **Ipv4OptionsReqDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionsReqDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionsReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv4OptionsReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv4OptionsReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv4OptionsReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionsReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv4OptionsReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionsReqDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionsReqDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionsReqDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionsReq'", field);
    }
}

const char *Ipv4OptionsReqDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionsReqDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv4OptionsReqDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsReq'", field);
    }
}

omnetpp::cValue Ipv4OptionsReqDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionsReq' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionsReqDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsReq'", field);
    }
}

const char *Ipv4OptionsReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv4OptionsReqDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionsReqDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsReq *pp = omnetpp::fromAnyPtr<Ipv4OptionsReq>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsReq'", field);
    }
}

Register_Class(Ipv4OptionsInd)

Ipv4OptionsInd::Ipv4OptionsInd() : ::inet::Ipv4OptionsTagBase()
{
}

Ipv4OptionsInd::Ipv4OptionsInd(const Ipv4OptionsInd& other) : ::inet::Ipv4OptionsTagBase(other)
{
    copy(other);
}

Ipv4OptionsInd::~Ipv4OptionsInd()
{
}

Ipv4OptionsInd& Ipv4OptionsInd::operator=(const Ipv4OptionsInd& other)
{
    if (this == &other) return *this;
    ::inet::Ipv4OptionsTagBase::operator=(other);
    copy(other);
    return *this;
}

void Ipv4OptionsInd::copy(const Ipv4OptionsInd& other)
{
}

void Ipv4OptionsInd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv4OptionsTagBase::parsimPack(b);
}

void Ipv4OptionsInd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv4OptionsTagBase::parsimUnpack(b);
}

class Ipv4OptionsIndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    Ipv4OptionsIndDescriptor();
    virtual ~Ipv4OptionsIndDescriptor();

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

Register_ClassDescriptor(Ipv4OptionsIndDescriptor)

Ipv4OptionsIndDescriptor::Ipv4OptionsIndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv4OptionsInd)), "inet::Ipv4OptionsTagBase")
{
    propertyNames = nullptr;
}

Ipv4OptionsIndDescriptor::~Ipv4OptionsIndDescriptor()
{
    delete[] propertyNames;
}

bool Ipv4OptionsIndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv4OptionsInd *>(obj)!=nullptr;
}

const char **Ipv4OptionsIndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ipv4OptionsIndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ipv4OptionsIndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int Ipv4OptionsIndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *Ipv4OptionsIndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int Ipv4OptionsIndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *Ipv4OptionsIndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **Ipv4OptionsIndDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv4OptionsIndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ipv4OptionsIndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ipv4OptionsIndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ipv4OptionsInd'", field);
    }
}

const char *Ipv4OptionsIndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv4OptionsIndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void Ipv4OptionsIndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsInd'", field);
    }
}

omnetpp::cValue Ipv4OptionsIndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ipv4OptionsInd' as cValue -- field index out of range?", field);
    }
}

void Ipv4OptionsIndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsInd'", field);
    }
}

const char *Ipv4OptionsIndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr Ipv4OptionsIndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ipv4OptionsIndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ipv4OptionsInd *pp = omnetpp::fromAnyPtr<Ipv4OptionsInd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ipv4OptionsInd'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

