//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp_common/TcpHeader.msg.
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
#include "TcpHeader_m.h"

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
namespace tcp {

Register_Enum(inet::tcp::TcpConstants, (inet::tcp::TcpConstants::TCP_MAX_SACK_ENTRIES));

Register_Enum(inet::tcp::TcpOptionNumbers, (inet::tcp::TcpOptionNumbers::TCPOPTION_END_OF_OPTION_LIST, inet::tcp::TcpOptionNumbers::TCPOPTION_NO_OPERATION, inet::tcp::TcpOptionNumbers::TCPOPTION_MAXIMUM_SEGMENT_SIZE, inet::tcp::TcpOptionNumbers::TCPOPTION_WINDOW_SCALE, inet::tcp::TcpOptionNumbers::TCPOPTION_SACK_PERMITTED, inet::tcp::TcpOptionNumbers::TCPOPTION_SACK, inet::tcp::TcpOptionNumbers::TCPOPTION_TIMESTAMP));

Register_Class(SackItem)

SackItem::SackItem() : ::omnetpp::cObject()
{
}

SackItem::SackItem(const SackItem& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

SackItem::~SackItem()
{
}

SackItem& SackItem::operator=(const SackItem& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void SackItem::copy(const SackItem& other)
{
    this->start = other.start;
    this->end = other.end;
}

void SackItem::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->start);
    doParsimPacking(b,this->end);
}

void SackItem::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->start);
    doParsimUnpacking(b,this->end);
}

unsigned int SackItem::getStart() const
{
    return this->start;
}

void SackItem::setStart(unsigned int start)
{
    this->start = start;
}

unsigned int SackItem::getEnd() const
{
    return this->end;
}

void SackItem::setEnd(unsigned int end)
{
    this->end = end;
}

class SackItemDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_start,
        FIELD_end,
    };
  public:
    SackItemDescriptor();
    virtual ~SackItemDescriptor();

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

Register_ClassDescriptor(SackItemDescriptor)

SackItemDescriptor::SackItemDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::SackItem)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

SackItemDescriptor::~SackItemDescriptor()
{
    delete[] propertyNames;
}

bool SackItemDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SackItem *>(obj)!=nullptr;
}

const char **SackItemDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SackItemDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SackItemDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int SackItemDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_start
        FD_ISEDITABLE,    // FIELD_end
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *SackItemDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "start",
        "end",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int SackItemDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "start") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "end") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *SackItemDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_start
        "unsigned int",    // FIELD_end
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **SackItemDescriptor::getFieldPropertyNames(int field) const
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

const char *SackItemDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SackItemDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SackItemDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SackItem'", field);
    }
}

const char *SackItemDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SackItemDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        case FIELD_start: return ulong2string(pp->getStart());
        case FIELD_end: return ulong2string(pp->getEnd());
        default: return "";
    }
}

void SackItemDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        case FIELD_start: pp->setStart(string2ulong(value)); break;
        case FIELD_end: pp->setEnd(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackItem'", field);
    }
}

omnetpp::cValue SackItemDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        case FIELD_start: return (omnetpp::intval_t)(pp->getStart());
        case FIELD_end: return (omnetpp::intval_t)(pp->getEnd());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SackItem' as cValue -- field index out of range?", field);
    }
}

void SackItemDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        case FIELD_start: pp->setStart(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_end: pp->setEnd(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackItem'", field);
    }
}

const char *SackItemDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr SackItemDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SackItemDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SackItem *pp = omnetpp::fromAnyPtr<SackItem>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SackItem'", field);
    }
}

Register_Class(Sack)

Sack::Sack() : ::inet::tcp::SackItem()
{
}

Sack::Sack(const Sack& other) : ::inet::tcp::SackItem(other)
{
    copy(other);
}

Sack::~Sack()
{
}

Sack& Sack::operator=(const Sack& other)
{
    if (this == &other) return *this;
    ::inet::tcp::SackItem::operator=(other);
    copy(other);
    return *this;
}

void Sack::copy(const Sack& other)
{
}

void Sack::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::SackItem::parsimPack(b);
}

void Sack::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::SackItem::parsimUnpack(b);
}

class SackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    SackDescriptor();
    virtual ~SackDescriptor();

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

Register_ClassDescriptor(SackDescriptor)

SackDescriptor::SackDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::Sack)), "inet::tcp::SackItem")
{
    propertyNames = nullptr;
}

SackDescriptor::~SackDescriptor()
{
    delete[] propertyNames;
}

bool SackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Sack *>(obj)!=nullptr;
}

const char **SackDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SackDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SackDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int SackDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *SackDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int SackDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *SackDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **SackDescriptor::getFieldPropertyNames(int field) const
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

const char *SackDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SackDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SackDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Sack'", field);
    }
}

const char *SackDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SackDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void SackDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Sack'", field);
    }
}

omnetpp::cValue SackDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Sack' as cValue -- field index out of range?", field);
    }
}

void SackDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Sack'", field);
    }
}

const char *SackDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr SackDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SackDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Sack *pp = omnetpp::fromAnyPtr<Sack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Sack'", field);
    }
}

Register_Class(TcpOption)

TcpOption::TcpOption() : ::omnetpp::cObject()
{
}

TcpOption::TcpOption(const TcpOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

TcpOption::~TcpOption()
{
}

TcpOption& TcpOption::operator=(const TcpOption& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void TcpOption::copy(const TcpOption& other)
{
    this->kind = other.kind;
    this->length = other.length;
}

void TcpOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->kind);
    doParsimPacking(b,this->length);
}

void TcpOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->kind);
    doParsimUnpacking(b,this->length);
}

TcpOptionNumbers TcpOption::getKind() const
{
    return this->kind;
}

void TcpOption::setKind(TcpOptionNumbers kind)
{
    this->kind = kind;
}

unsigned short TcpOption::getLength() const
{
    return this->length;
}

void TcpOption::setLength(unsigned short length)
{
    this->length = length;
}

class TcpOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_kind,
        FIELD_length,
    };
  public:
    TcpOptionDescriptor();
    virtual ~TcpOptionDescriptor();

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

Register_ClassDescriptor(TcpOptionDescriptor)

TcpOptionDescriptor::TcpOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOption)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpOptionDescriptor::~TcpOptionDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOption *>(obj)!=nullptr;
}

const char **TcpOptionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "packetData",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "packetData")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TcpOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_kind
        FD_ISEDITABLE,    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TcpOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "kind",
        "length",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TcpOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "kind") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "length") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::tcp::TcpOptionNumbers",    // FIELD_kind
        "unsigned short",    // FIELD_length
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOptionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_kind: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TcpOptionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_kind:
            if (!strcmp(propertyName, "enum")) return "inet::tcp::TcpOptionNumbers";
            return nullptr;
        default: return nullptr;
    }
}

int TcpOptionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOption'", field);
    }
}

const char *TcpOptionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        case FIELD_kind: return enum2string(pp->getKind(), "inet::tcp::TcpOptionNumbers");
        case FIELD_length: return ulong2string(pp->getLength());
        default: return "";
    }
}

void TcpOptionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOption'", field);
    }
}

omnetpp::cValue TcpOptionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        case FIELD_kind: return static_cast<int>(pp->getKind());
        case FIELD_length: return (omnetpp::intval_t)(pp->getLength());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOption' as cValue -- field index out of range?", field);
    }
}

void TcpOptionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOption'", field);
    }
}

const char *TcpOptionDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOptionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOption *pp = omnetpp::fromAnyPtr<TcpOption>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOption'", field);
    }
}

Register_Class(TcpOptionEnd)

TcpOptionEnd::TcpOptionEnd() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_END_OF_OPTION_LIST);
    this->setLength(1);
}

TcpOptionEnd::TcpOptionEnd(const TcpOptionEnd& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionEnd::~TcpOptionEnd()
{
}

TcpOptionEnd& TcpOptionEnd::operator=(const TcpOptionEnd& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionEnd::copy(const TcpOptionEnd& other)
{
}

void TcpOptionEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
}

void TcpOptionEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
}

class TcpOptionEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpOptionEndDescriptor();
    virtual ~TcpOptionEndDescriptor();

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

Register_ClassDescriptor(TcpOptionEndDescriptor)

TcpOptionEndDescriptor::TcpOptionEndDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionEnd)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionEndDescriptor::~TcpOptionEndDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionEnd *>(obj)!=nullptr;
}

const char **TcpOptionEndDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionEndDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpOptionEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpOptionEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpOptionEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpOptionEndDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionEndDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionEndDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionEndDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionEnd'", field);
    }
}

const char *TcpOptionEndDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionEndDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpOptionEndDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionEnd'", field);
    }
}

omnetpp::cValue TcpOptionEndDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionEnd' as cValue -- field index out of range?", field);
    }
}

void TcpOptionEndDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionEnd'", field);
    }
}

const char *TcpOptionEndDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpOptionEndDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionEndDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionEnd *pp = omnetpp::fromAnyPtr<TcpOptionEnd>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionEnd'", field);
    }
}

Register_Class(TcpOptionNop)

TcpOptionNop::TcpOptionNop() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_NO_OPERATION);
    this->setLength(1);
}

TcpOptionNop::TcpOptionNop(const TcpOptionNop& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionNop::~TcpOptionNop()
{
}

TcpOptionNop& TcpOptionNop::operator=(const TcpOptionNop& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionNop::copy(const TcpOptionNop& other)
{
}

void TcpOptionNop::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
}

void TcpOptionNop::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
}

class TcpOptionNopDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpOptionNopDescriptor();
    virtual ~TcpOptionNopDescriptor();

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

Register_ClassDescriptor(TcpOptionNopDescriptor)

TcpOptionNopDescriptor::TcpOptionNopDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionNop)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionNopDescriptor::~TcpOptionNopDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionNopDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionNop *>(obj)!=nullptr;
}

const char **TcpOptionNopDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionNopDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionNopDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpOptionNopDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpOptionNopDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpOptionNopDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionNopDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpOptionNopDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionNopDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionNopDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionNopDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionNop'", field);
    }
}

const char *TcpOptionNopDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionNopDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpOptionNopDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionNop'", field);
    }
}

omnetpp::cValue TcpOptionNopDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionNop' as cValue -- field index out of range?", field);
    }
}

void TcpOptionNopDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionNop'", field);
    }
}

const char *TcpOptionNopDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpOptionNopDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionNopDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionNop *pp = omnetpp::fromAnyPtr<TcpOptionNop>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionNop'", field);
    }
}

Register_Class(TcpOptionMaxSegmentSize)

TcpOptionMaxSegmentSize::TcpOptionMaxSegmentSize() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_MAXIMUM_SEGMENT_SIZE);
    this->setLength(4);

}

TcpOptionMaxSegmentSize::TcpOptionMaxSegmentSize(const TcpOptionMaxSegmentSize& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionMaxSegmentSize::~TcpOptionMaxSegmentSize()
{
}

TcpOptionMaxSegmentSize& TcpOptionMaxSegmentSize::operator=(const TcpOptionMaxSegmentSize& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionMaxSegmentSize::copy(const TcpOptionMaxSegmentSize& other)
{
    this->maxSegmentSize = other.maxSegmentSize;
}

void TcpOptionMaxSegmentSize::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
    doParsimPacking(b,this->maxSegmentSize);
}

void TcpOptionMaxSegmentSize::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->maxSegmentSize);
}

uint16_t TcpOptionMaxSegmentSize::getMaxSegmentSize() const
{
    return this->maxSegmentSize;
}

void TcpOptionMaxSegmentSize::setMaxSegmentSize(uint16_t maxSegmentSize)
{
    this->maxSegmentSize = maxSegmentSize;
}

class TcpOptionMaxSegmentSizeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_maxSegmentSize,
    };
  public:
    TcpOptionMaxSegmentSizeDescriptor();
    virtual ~TcpOptionMaxSegmentSizeDescriptor();

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

Register_ClassDescriptor(TcpOptionMaxSegmentSizeDescriptor)

TcpOptionMaxSegmentSizeDescriptor::TcpOptionMaxSegmentSizeDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionMaxSegmentSize)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionMaxSegmentSizeDescriptor::~TcpOptionMaxSegmentSizeDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionMaxSegmentSizeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionMaxSegmentSize *>(obj)!=nullptr;
}

const char **TcpOptionMaxSegmentSizeDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionMaxSegmentSizeDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionMaxSegmentSizeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpOptionMaxSegmentSizeDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_maxSegmentSize
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpOptionMaxSegmentSizeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "maxSegmentSize",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpOptionMaxSegmentSizeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "maxSegmentSize") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionMaxSegmentSizeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint16_t",    // FIELD_maxSegmentSize
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOptionMaxSegmentSizeDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionMaxSegmentSizeDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionMaxSegmentSizeDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionMaxSegmentSizeDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionMaxSegmentSize'", field);
    }
}

const char *TcpOptionMaxSegmentSizeDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionMaxSegmentSizeDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: return ulong2string(pp->getMaxSegmentSize());
        default: return "";
    }
}

void TcpOptionMaxSegmentSizeDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: pp->setMaxSegmentSize(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionMaxSegmentSize'", field);
    }
}

omnetpp::cValue TcpOptionMaxSegmentSizeDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: return (omnetpp::intval_t)(pp->getMaxSegmentSize());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionMaxSegmentSize' as cValue -- field index out of range?", field);
    }
}

void TcpOptionMaxSegmentSizeDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        case FIELD_maxSegmentSize: pp->setMaxSegmentSize(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionMaxSegmentSize'", field);
    }
}

const char *TcpOptionMaxSegmentSizeDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOptionMaxSegmentSizeDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionMaxSegmentSizeDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionMaxSegmentSize *pp = omnetpp::fromAnyPtr<TcpOptionMaxSegmentSize>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionMaxSegmentSize'", field);
    }
}

Register_Class(TcpOptionWindowScale)

TcpOptionWindowScale::TcpOptionWindowScale() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_WINDOW_SCALE);
    this->setLength(3);

}

TcpOptionWindowScale::TcpOptionWindowScale(const TcpOptionWindowScale& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionWindowScale::~TcpOptionWindowScale()
{
}

TcpOptionWindowScale& TcpOptionWindowScale::operator=(const TcpOptionWindowScale& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionWindowScale::copy(const TcpOptionWindowScale& other)
{
    this->windowScale = other.windowScale;
}

void TcpOptionWindowScale::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
    doParsimPacking(b,this->windowScale);
}

void TcpOptionWindowScale::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->windowScale);
}

unsigned short TcpOptionWindowScale::getWindowScale() const
{
    return this->windowScale;
}

void TcpOptionWindowScale::setWindowScale(unsigned short windowScale)
{
    this->windowScale = windowScale;
}

class TcpOptionWindowScaleDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_windowScale,
    };
  public:
    TcpOptionWindowScaleDescriptor();
    virtual ~TcpOptionWindowScaleDescriptor();

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

Register_ClassDescriptor(TcpOptionWindowScaleDescriptor)

TcpOptionWindowScaleDescriptor::TcpOptionWindowScaleDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionWindowScale)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionWindowScaleDescriptor::~TcpOptionWindowScaleDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionWindowScaleDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionWindowScale *>(obj)!=nullptr;
}

const char **TcpOptionWindowScaleDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionWindowScaleDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionWindowScaleDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpOptionWindowScaleDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_windowScale
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpOptionWindowScaleDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "windowScale",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpOptionWindowScaleDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "windowScale") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionWindowScaleDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_windowScale
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOptionWindowScaleDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionWindowScaleDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionWindowScaleDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionWindowScaleDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionWindowScale'", field);
    }
}

const char *TcpOptionWindowScaleDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionWindowScaleDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        case FIELD_windowScale: return ulong2string(pp->getWindowScale());
        default: return "";
    }
}

void TcpOptionWindowScaleDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        case FIELD_windowScale: pp->setWindowScale(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionWindowScale'", field);
    }
}

omnetpp::cValue TcpOptionWindowScaleDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        case FIELD_windowScale: return (omnetpp::intval_t)(pp->getWindowScale());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionWindowScale' as cValue -- field index out of range?", field);
    }
}

void TcpOptionWindowScaleDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        case FIELD_windowScale: pp->setWindowScale(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionWindowScale'", field);
    }
}

const char *TcpOptionWindowScaleDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOptionWindowScaleDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionWindowScaleDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionWindowScale *pp = omnetpp::fromAnyPtr<TcpOptionWindowScale>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionWindowScale'", field);
    }
}

Register_Class(TcpOptionSackPermitted)

TcpOptionSackPermitted::TcpOptionSackPermitted() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_SACK_PERMITTED);
    this->setLength(2);
}

TcpOptionSackPermitted::TcpOptionSackPermitted(const TcpOptionSackPermitted& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionSackPermitted::~TcpOptionSackPermitted()
{
}

TcpOptionSackPermitted& TcpOptionSackPermitted::operator=(const TcpOptionSackPermitted& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionSackPermitted::copy(const TcpOptionSackPermitted& other)
{
}

void TcpOptionSackPermitted::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
}

void TcpOptionSackPermitted::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
}

class TcpOptionSackPermittedDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpOptionSackPermittedDescriptor();
    virtual ~TcpOptionSackPermittedDescriptor();

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

Register_ClassDescriptor(TcpOptionSackPermittedDescriptor)

TcpOptionSackPermittedDescriptor::TcpOptionSackPermittedDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionSackPermitted)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionSackPermittedDescriptor::~TcpOptionSackPermittedDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionSackPermittedDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionSackPermitted *>(obj)!=nullptr;
}

const char **TcpOptionSackPermittedDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionSackPermittedDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionSackPermittedDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpOptionSackPermittedDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpOptionSackPermittedDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpOptionSackPermittedDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionSackPermittedDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpOptionSackPermittedDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionSackPermittedDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionSackPermittedDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionSackPermittedDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionSackPermitted'", field);
    }
}

const char *TcpOptionSackPermittedDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionSackPermittedDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpOptionSackPermittedDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSackPermitted'", field);
    }
}

omnetpp::cValue TcpOptionSackPermittedDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionSackPermitted' as cValue -- field index out of range?", field);
    }
}

void TcpOptionSackPermittedDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSackPermitted'", field);
    }
}

const char *TcpOptionSackPermittedDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpOptionSackPermittedDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionSackPermittedDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSackPermitted *pp = omnetpp::fromAnyPtr<TcpOptionSackPermitted>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSackPermitted'", field);
    }
}

Register_Class(TcpOptionSack)

TcpOptionSack::TcpOptionSack() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_SACK);
    this->setLength(2);

}

TcpOptionSack::TcpOptionSack(const TcpOptionSack& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionSack::~TcpOptionSack()
{
    delete [] this->sackItem;
}

TcpOptionSack& TcpOptionSack::operator=(const TcpOptionSack& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionSack::copy(const TcpOptionSack& other)
{
    delete [] this->sackItem;
    this->sackItem = (other.sackItem_arraysize==0) ? nullptr : new SackItem[other.sackItem_arraysize];
    sackItem_arraysize = other.sackItem_arraysize;
    for (size_t i = 0; i < sackItem_arraysize; i++) {
        this->sackItem[i] = other.sackItem[i];
    }
}

void TcpOptionSack::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
    b->pack(sackItem_arraysize);
    doParsimArrayPacking(b,this->sackItem,sackItem_arraysize);
}

void TcpOptionSack::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
    delete [] this->sackItem;
    b->unpack(sackItem_arraysize);
    if (sackItem_arraysize == 0) {
        this->sackItem = nullptr;
    } else {
        this->sackItem = new SackItem[sackItem_arraysize];
        doParsimArrayUnpacking(b,this->sackItem,sackItem_arraysize);
    }
}

size_t TcpOptionSack::getSackItemArraySize() const
{
    return sackItem_arraysize;
}

const SackItem& TcpOptionSack::getSackItem(size_t k) const
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sackItem_arraysize, (unsigned long)k);
    return this->sackItem[k];
}

void TcpOptionSack::setSackItemArraySize(size_t newSize)
{
    SackItem *sackItem2 = (newSize==0) ? nullptr : new SackItem[newSize];
    size_t minSize = sackItem_arraysize < newSize ? sackItem_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sackItem2[i] = this->sackItem[i];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

void TcpOptionSack::setSackItem(size_t k, const SackItem& sackItem)
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sackItem_arraysize, (unsigned long)k);
    this->sackItem[k] = sackItem;
}

void TcpOptionSack::insertSackItem(size_t k, const SackItem& sackItem)
{
    if (k > sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sackItem_arraysize, (unsigned long)k);
    size_t newSize = sackItem_arraysize + 1;
    SackItem *sackItem2 = new SackItem[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sackItem2[i] = this->sackItem[i];
    sackItem2[k] = sackItem;
    for (i = k + 1; i < newSize; i++)
        sackItem2[i] = this->sackItem[i-1];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

void TcpOptionSack::appendSackItem(const SackItem& sackItem)
{
    insertSackItem(sackItem_arraysize, sackItem);
}

void TcpOptionSack::eraseSackItem(size_t k)
{
    if (k >= sackItem_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sackItem_arraysize, (unsigned long)k);
    size_t newSize = sackItem_arraysize - 1;
    SackItem *sackItem2 = (newSize == 0) ? nullptr : new SackItem[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sackItem2[i] = this->sackItem[i];
    for (i = k; i < newSize; i++)
        sackItem2[i] = this->sackItem[i+1];
    delete [] this->sackItem;
    this->sackItem = sackItem2;
    sackItem_arraysize = newSize;
}

class TcpOptionSackDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sackItem,
    };
  public:
    TcpOptionSackDescriptor();
    virtual ~TcpOptionSackDescriptor();

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

Register_ClassDescriptor(TcpOptionSackDescriptor)

TcpOptionSackDescriptor::TcpOptionSackDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionSack)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionSackDescriptor::~TcpOptionSackDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionSackDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionSack *>(obj)!=nullptr;
}

const char **TcpOptionSackDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionSackDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionSackDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpOptionSackDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISRESIZABLE,    // FIELD_sackItem
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpOptionSackDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sackItem",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpOptionSackDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sackItem") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionSackDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::tcp::SackItem",    // FIELD_sackItem
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOptionSackDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionSackDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionSackDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        case FIELD_sackItem: return pp->getSackItemArraySize();
        default: return 0;
    }
}

void TcpOptionSackDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        case FIELD_sackItem: pp->setSackItemArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionSack'", field);
    }
}

const char *TcpOptionSackDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionSackDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        case FIELD_sackItem: return pp->getSackItem(i).str();
        default: return "";
    }
}

void TcpOptionSackDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSack'", field);
    }
}

omnetpp::cValue TcpOptionSackDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        case FIELD_sackItem: return omnetpp::toAnyPtr(&pp->getSackItem(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionSack' as cValue -- field index out of range?", field);
    }
}

void TcpOptionSackDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSack'", field);
    }
}

const char *TcpOptionSackDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_sackItem: return omnetpp::opp_typename(typeid(SackItem));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpOptionSackDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        case FIELD_sackItem: return omnetpp::toAnyPtr(&pp->getSackItem(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionSackDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionSack *pp = omnetpp::fromAnyPtr<TcpOptionSack>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionSack'", field);
    }
}

Register_Class(TcpOptionTimestamp)

TcpOptionTimestamp::TcpOptionTimestamp() : ::inet::tcp::TcpOption()
{
    this->setKind(TCPOPTION_TIMESTAMP);
    this->setLength(10);

}

TcpOptionTimestamp::TcpOptionTimestamp(const TcpOptionTimestamp& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionTimestamp::~TcpOptionTimestamp()
{
}

TcpOptionTimestamp& TcpOptionTimestamp::operator=(const TcpOptionTimestamp& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionTimestamp::copy(const TcpOptionTimestamp& other)
{
    this->senderTimestamp = other.senderTimestamp;
    this->echoedTimestamp = other.echoedTimestamp;
}

void TcpOptionTimestamp::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
    doParsimPacking(b,this->senderTimestamp);
    doParsimPacking(b,this->echoedTimestamp);
}

void TcpOptionTimestamp::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
    doParsimUnpacking(b,this->senderTimestamp);
    doParsimUnpacking(b,this->echoedTimestamp);
}

uint32_t TcpOptionTimestamp::getSenderTimestamp() const
{
    return this->senderTimestamp;
}

void TcpOptionTimestamp::setSenderTimestamp(uint32_t senderTimestamp)
{
    this->senderTimestamp = senderTimestamp;
}

uint32_t TcpOptionTimestamp::getEchoedTimestamp() const
{
    return this->echoedTimestamp;
}

void TcpOptionTimestamp::setEchoedTimestamp(uint32_t echoedTimestamp)
{
    this->echoedTimestamp = echoedTimestamp;
}

class TcpOptionTimestampDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderTimestamp,
        FIELD_echoedTimestamp,
    };
  public:
    TcpOptionTimestampDescriptor();
    virtual ~TcpOptionTimestampDescriptor();

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

Register_ClassDescriptor(TcpOptionTimestampDescriptor)

TcpOptionTimestampDescriptor::TcpOptionTimestampDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionTimestamp)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionTimestampDescriptor::~TcpOptionTimestampDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionTimestampDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionTimestamp *>(obj)!=nullptr;
}

const char **TcpOptionTimestampDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionTimestampDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionTimestampDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TcpOptionTimestampDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderTimestamp
        FD_ISEDITABLE,    // FIELD_echoedTimestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TcpOptionTimestampDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderTimestamp",
        "echoedTimestamp",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TcpOptionTimestampDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderTimestamp") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "echoedTimestamp") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionTimestampDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_senderTimestamp
        "uint32_t",    // FIELD_echoedTimestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpOptionTimestampDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionTimestampDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionTimestampDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpOptionTimestampDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionTimestamp'", field);
    }
}

const char *TcpOptionTimestampDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionTimestampDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: return ulong2string(pp->getSenderTimestamp());
        case FIELD_echoedTimestamp: return ulong2string(pp->getEchoedTimestamp());
        default: return "";
    }
}

void TcpOptionTimestampDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: pp->setSenderTimestamp(string2ulong(value)); break;
        case FIELD_echoedTimestamp: pp->setEchoedTimestamp(string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionTimestamp'", field);
    }
}

omnetpp::cValue TcpOptionTimestampDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: return (omnetpp::intval_t)(pp->getSenderTimestamp());
        case FIELD_echoedTimestamp: return (omnetpp::intval_t)(pp->getEchoedTimestamp());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionTimestamp' as cValue -- field index out of range?", field);
    }
}

void TcpOptionTimestampDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        case FIELD_senderTimestamp: pp->setSenderTimestamp(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_echoedTimestamp: pp->setEchoedTimestamp(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionTimestamp'", field);
    }
}

const char *TcpOptionTimestampDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOptionTimestampDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionTimestampDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionTimestamp *pp = omnetpp::fromAnyPtr<TcpOptionTimestamp>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionTimestamp'", field);
    }
}

Register_Class(TcpOptionUnknown)

TcpOptionUnknown::TcpOptionUnknown() : ::inet::tcp::TcpOption()
{
    this->setKind(static_cast<TcpOptionNumbers>(-1));

}

TcpOptionUnknown::TcpOptionUnknown(const TcpOptionUnknown& other) : ::inet::tcp::TcpOption(other)
{
    copy(other);
}

TcpOptionUnknown::~TcpOptionUnknown()
{
    delete [] this->bytes;
}

TcpOptionUnknown& TcpOptionUnknown::operator=(const TcpOptionUnknown& other)
{
    if (this == &other) return *this;
    ::inet::tcp::TcpOption::operator=(other);
    copy(other);
    return *this;
}

void TcpOptionUnknown::copy(const TcpOptionUnknown& other)
{
    delete [] this->bytes;
    this->bytes = (other.bytes_arraysize==0) ? nullptr : new uint8_t[other.bytes_arraysize];
    bytes_arraysize = other.bytes_arraysize;
    for (size_t i = 0; i < bytes_arraysize; i++) {
        this->bytes[i] = other.bytes[i];
    }
}

void TcpOptionUnknown::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::tcp::TcpOption::parsimPack(b);
    b->pack(bytes_arraysize);
    doParsimArrayPacking(b,this->bytes,bytes_arraysize);
}

void TcpOptionUnknown::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::tcp::TcpOption::parsimUnpack(b);
    delete [] this->bytes;
    b->unpack(bytes_arraysize);
    if (bytes_arraysize == 0) {
        this->bytes = nullptr;
    } else {
        this->bytes = new uint8_t[bytes_arraysize];
        doParsimArrayUnpacking(b,this->bytes,bytes_arraysize);
    }
}

size_t TcpOptionUnknown::getBytesArraySize() const
{
    return bytes_arraysize;
}

uint8_t TcpOptionUnknown::getBytes(size_t k) const
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    return this->bytes[k];
}

void TcpOptionUnknown::setBytesArraySize(size_t newSize)
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

void TcpOptionUnknown::setBytes(size_t k, uint8_t bytes)
{
    if (k >= bytes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)bytes_arraysize, (unsigned long)k);
    this->bytes[k] = bytes;
}

void TcpOptionUnknown::insertBytes(size_t k, uint8_t bytes)
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

void TcpOptionUnknown::appendBytes(uint8_t bytes)
{
    insertBytes(bytes_arraysize, bytes);
}

void TcpOptionUnknown::eraseBytes(size_t k)
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

class TcpOptionUnknownDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_bytes,
    };
  public:
    TcpOptionUnknownDescriptor();
    virtual ~TcpOptionUnknownDescriptor();

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

Register_ClassDescriptor(TcpOptionUnknownDescriptor)

TcpOptionUnknownDescriptor::TcpOptionUnknownDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpOptionUnknown)), "inet::tcp::TcpOption")
{
    propertyNames = nullptr;
}

TcpOptionUnknownDescriptor::~TcpOptionUnknownDescriptor()
{
    delete[] propertyNames;
}

bool TcpOptionUnknownDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpOptionUnknown *>(obj)!=nullptr;
}

const char **TcpOptionUnknownDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpOptionUnknownDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpOptionUnknownDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpOptionUnknownDescriptor::getFieldTypeFlags(int field) const
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

const char *TcpOptionUnknownDescriptor::getFieldName(int field) const
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

int TcpOptionUnknownDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "bytes") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpOptionUnknownDescriptor::getFieldTypeString(int field) const
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

const char **TcpOptionUnknownDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpOptionUnknownDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpOptionUnknownDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return pp->getBytesArraySize();
        default: return 0;
    }
}

void TcpOptionUnknownDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpOptionUnknown'", field);
    }
}

const char *TcpOptionUnknownDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpOptionUnknownDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return ulong2string(pp->getBytes(i));
        default: return "";
    }
}

void TcpOptionUnknownDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,string2ulong(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionUnknown'", field);
    }
}

omnetpp::cValue TcpOptionUnknownDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: return (omnetpp::intval_t)(pp->getBytes(i));
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpOptionUnknown' as cValue -- field index out of range?", field);
    }
}

void TcpOptionUnknownDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        case FIELD_bytes: pp->setBytes(i,omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionUnknown'", field);
    }
}

const char *TcpOptionUnknownDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpOptionUnknownDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpOptionUnknownDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpOptionUnknown *pp = omnetpp::fromAnyPtr<TcpOptionUnknown>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpOptionUnknown'", field);
    }
}

Register_Class(TcpHeader)

TcpHeader::TcpHeader() : ::inet::TransportHeaderBase()
{
    this->setChunkLength(TCP_MIN_HEADER_LENGTH);

}

TcpHeader::TcpHeader(const TcpHeader& other) : ::inet::TransportHeaderBase(other)
{
    copy(other);
}

TcpHeader::~TcpHeader()
{
    for (size_t i = 0; i < headerOption_arraysize; i++)
        delete this->headerOption[i];
    delete [] this->headerOption;
}

TcpHeader& TcpHeader::operator=(const TcpHeader& other)
{
    if (this == &other) return *this;
    ::inet::TransportHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void TcpHeader::copy(const TcpHeader& other)
{
    this->srcPort = other.srcPort;
    this->destPort = other.destPort;
    this->sequenceNo = other.sequenceNo;
    this->ackNo = other.ackNo;
    this->headerLength = other.headerLength;
    this->cwrBit = other.cwrBit;
    this->eceBit = other.eceBit;
    this->urgBit = other.urgBit;
    this->ackBit = other.ackBit;
    this->pshBit = other.pshBit;
    this->rstBit = other.rstBit;
    this->synBit = other.synBit;
    this->finBit = other.finBit;
    this->window = other.window;
    this->urgentPointer = other.urgentPointer;
    this->crc = other.crc;
    this->crcMode = other.crcMode;
    for (size_t i = 0; i < headerOption_arraysize; i++)
        delete this->headerOption[i];
    delete [] this->headerOption;
    this->headerOption = (other.headerOption_arraysize==0) ? nullptr : new TcpOption *[other.headerOption_arraysize];
    headerOption_arraysize = other.headerOption_arraysize;
    for (size_t i = 0; i < headerOption_arraysize; i++) {
        this->headerOption[i] = other.headerOption[i];
        if (this->headerOption[i] != nullptr) {
            this->headerOption[i] = this->headerOption[i]->dup();
        }
    }
}

void TcpHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::TransportHeaderBase::parsimPack(b);
    doParsimPacking(b,this->srcPort);
    doParsimPacking(b,this->destPort);
    doParsimPacking(b,this->sequenceNo);
    doParsimPacking(b,this->ackNo);
    doParsimPacking(b,this->headerLength);
    doParsimPacking(b,this->cwrBit);
    doParsimPacking(b,this->eceBit);
    doParsimPacking(b,this->urgBit);
    doParsimPacking(b,this->ackBit);
    doParsimPacking(b,this->pshBit);
    doParsimPacking(b,this->rstBit);
    doParsimPacking(b,this->synBit);
    doParsimPacking(b,this->finBit);
    doParsimPacking(b,this->window);
    doParsimPacking(b,this->urgentPointer);
    doParsimPacking(b,this->crc);
    doParsimPacking(b,this->crcMode);
    b->pack(headerOption_arraysize);
    doParsimArrayPacking(b,this->headerOption,headerOption_arraysize);
}

void TcpHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::TransportHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->srcPort);
    doParsimUnpacking(b,this->destPort);
    doParsimUnpacking(b,this->sequenceNo);
    doParsimUnpacking(b,this->ackNo);
    doParsimUnpacking(b,this->headerLength);
    doParsimUnpacking(b,this->cwrBit);
    doParsimUnpacking(b,this->eceBit);
    doParsimUnpacking(b,this->urgBit);
    doParsimUnpacking(b,this->ackBit);
    doParsimUnpacking(b,this->pshBit);
    doParsimUnpacking(b,this->rstBit);
    doParsimUnpacking(b,this->synBit);
    doParsimUnpacking(b,this->finBit);
    doParsimUnpacking(b,this->window);
    doParsimUnpacking(b,this->urgentPointer);
    doParsimUnpacking(b,this->crc);
    doParsimUnpacking(b,this->crcMode);
    delete [] this->headerOption;
    b->unpack(headerOption_arraysize);
    if (headerOption_arraysize == 0) {
        this->headerOption = nullptr;
    } else {
        this->headerOption = new TcpOption *[headerOption_arraysize];
        doParsimArrayUnpacking(b,this->headerOption,headerOption_arraysize);
    }
}

unsigned short TcpHeader::getSrcPort() const
{
    return this->srcPort;
}

void TcpHeader::setSrcPort(unsigned short srcPort)
{
    handleChange();
    this->srcPort = srcPort;
}

unsigned short TcpHeader::getDestPort() const
{
    return this->destPort;
}

void TcpHeader::setDestPort(unsigned short destPort)
{
    handleChange();
    this->destPort = destPort;
}

uint32_t TcpHeader::getSequenceNo() const
{
    return this->sequenceNo;
}

void TcpHeader::setSequenceNo(uint32_t sequenceNo)
{
    handleChange();
    this->sequenceNo = sequenceNo;
}

uint32_t TcpHeader::getAckNo() const
{
    return this->ackNo;
}

void TcpHeader::setAckNo(uint32_t ackNo)
{
    handleChange();
    this->ackNo = ackNo;
}

::inet::B TcpHeader::getHeaderLength() const
{
    return this->headerLength;
}

void TcpHeader::setHeaderLength(::inet::B headerLength)
{
    handleChange();
    this->headerLength = headerLength;
}

bool TcpHeader::getCwrBit() const
{
    return this->cwrBit;
}

void TcpHeader::setCwrBit(bool cwrBit)
{
    handleChange();
    this->cwrBit = cwrBit;
}

bool TcpHeader::getEceBit() const
{
    return this->eceBit;
}

void TcpHeader::setEceBit(bool eceBit)
{
    handleChange();
    this->eceBit = eceBit;
}

bool TcpHeader::getUrgBit() const
{
    return this->urgBit;
}

void TcpHeader::setUrgBit(bool urgBit)
{
    handleChange();
    this->urgBit = urgBit;
}

bool TcpHeader::getAckBit() const
{
    return this->ackBit;
}

void TcpHeader::setAckBit(bool ackBit)
{
    handleChange();
    this->ackBit = ackBit;
}

bool TcpHeader::getPshBit() const
{
    return this->pshBit;
}

void TcpHeader::setPshBit(bool pshBit)
{
    handleChange();
    this->pshBit = pshBit;
}

bool TcpHeader::getRstBit() const
{
    return this->rstBit;
}

void TcpHeader::setRstBit(bool rstBit)
{
    handleChange();
    this->rstBit = rstBit;
}

bool TcpHeader::getSynBit() const
{
    return this->synBit;
}

void TcpHeader::setSynBit(bool synBit)
{
    handleChange();
    this->synBit = synBit;
}

bool TcpHeader::getFinBit() const
{
    return this->finBit;
}

void TcpHeader::setFinBit(bool finBit)
{
    handleChange();
    this->finBit = finBit;
}

uint16_t TcpHeader::getWindow() const
{
    return this->window;
}

void TcpHeader::setWindow(uint16_t window)
{
    handleChange();
    this->window = window;
}

uint16_t TcpHeader::getUrgentPointer() const
{
    return this->urgentPointer;
}

void TcpHeader::setUrgentPointer(uint16_t urgentPointer)
{
    handleChange();
    this->urgentPointer = urgentPointer;
}

uint16_t TcpHeader::getCrc() const
{
    return this->crc;
}

void TcpHeader::setCrc(uint16_t crc)
{
    handleChange();
    this->crc = crc;
}

::inet::CrcMode TcpHeader::getCrcMode() const
{
    return this->crcMode;
}

void TcpHeader::setCrcMode(::inet::CrcMode crcMode)
{
    handleChange();
    this->crcMode = crcMode;
}

size_t TcpHeader::getHeaderOptionArraySize() const
{
    return headerOption_arraysize;
}

const TcpOption * TcpHeader::getHeaderOption(size_t k) const
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)headerOption_arraysize, (unsigned long)k);
    return this->headerOption[k];
}

void TcpHeader::setHeaderOptionArraySize(size_t newSize)
{
    handleChange();
    TcpOption * *headerOption2 = (newSize==0) ? nullptr : new TcpOption *[newSize];
    size_t minSize = headerOption_arraysize < newSize ? headerOption_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        headerOption2[i] = this->headerOption[i];
    for (size_t i = minSize; i < newSize; i++)
        headerOption2[i] = nullptr;
    for (size_t i = newSize; i < headerOption_arraysize; i++)
        delete headerOption[i];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

void TcpHeader::setHeaderOption(size_t k, TcpOption * headerOption)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)headerOption_arraysize, (unsigned long)k);
    handleChange();
    if (this->headerOption[k] != nullptr) throw omnetpp::cRuntimeError("setHeaderOption(): a value is already set, remove it first with removeHeaderOption()");
    this->headerOption[k] = headerOption;
    if (this->headerOption[k] != nullptr && this->headerOption[k]->isOwnedObject()) take((cOwnedObject*)this->headerOption[k]);
}

TcpOption * TcpHeader::removeHeaderOption(size_t k)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)headerOption_arraysize, (unsigned long)k);
    handleChange();
    TcpOption * retval = this->headerOption[k];
    if (retval != nullptr && retval->isOwnedObject()) drop((cOwnedObject*)retval);
    this->headerOption[k] = nullptr;
    return retval;
}

void TcpHeader::insertHeaderOption(size_t k, TcpOption * headerOption)
{
    if (k > headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)headerOption_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = headerOption_arraysize + 1;
    TcpOption * *headerOption2 = new TcpOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        headerOption2[i] = this->headerOption[i];
    headerOption2[k] = headerOption;
    if (headerOption2[k] != nullptr && headerOption2[k]->isOwnedObject()) take((cOwnedObject*)headerOption2[k]);
    for (i = k + 1; i < newSize; i++)
        headerOption2[i] = this->headerOption[i-1];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

void TcpHeader::appendHeaderOption(TcpOption * headerOption)
{
    insertHeaderOption(headerOption_arraysize, headerOption);
}

void TcpHeader::eraseHeaderOption(size_t k)
{
    if (k >= headerOption_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)headerOption_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = headerOption_arraysize - 1;
    TcpOption * *headerOption2 = (newSize == 0) ? nullptr : new TcpOption *[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        headerOption2[i] = this->headerOption[i];
    for (i = k; i < newSize; i++)
        headerOption2[i] = this->headerOption[i+1];
    if (this->headerOption[k] != nullptr && this->headerOption[k]->isOwnedObject()) dropAndDelete((cOwnedObject*)this->headerOption[k]); else delete this->headerOption[k];
    delete [] this->headerOption;
    this->headerOption = headerOption2;
    headerOption_arraysize = newSize;
}

class TcpHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_srcPort,
        FIELD_destPort,
        FIELD_sequenceNo,
        FIELD_ackNo,
        FIELD_headerLength,
        FIELD_cwrBit,
        FIELD_eceBit,
        FIELD_urgBit,
        FIELD_ackBit,
        FIELD_pshBit,
        FIELD_rstBit,
        FIELD_synBit,
        FIELD_finBit,
        FIELD_window,
        FIELD_urgentPointer,
        FIELD_crc,
        FIELD_crcMode,
        FIELD_headerOption,
    };
  public:
    TcpHeaderDescriptor();
    virtual ~TcpHeaderDescriptor();

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

Register_ClassDescriptor(TcpHeaderDescriptor)

TcpHeaderDescriptor::TcpHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpHeader)), "inet::TransportHeaderBase")
{
    propertyNames = nullptr;
}

TcpHeaderDescriptor::~TcpHeaderDescriptor()
{
    delete[] propertyNames;
}

bool TcpHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpHeader *>(obj)!=nullptr;
}

const char **TcpHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 18+base->getFieldCount() : 18;
}

unsigned int TcpHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_srcPort
        FD_ISEDITABLE,    // FIELD_destPort
        FD_ISEDITABLE,    // FIELD_sequenceNo
        FD_ISEDITABLE,    // FIELD_ackNo
        FD_ISEDITABLE,    // FIELD_headerLength
        FD_ISEDITABLE,    // FIELD_cwrBit
        FD_ISEDITABLE,    // FIELD_eceBit
        FD_ISEDITABLE,    // FIELD_urgBit
        FD_ISEDITABLE,    // FIELD_ackBit
        FD_ISEDITABLE,    // FIELD_pshBit
        FD_ISEDITABLE,    // FIELD_rstBit
        FD_ISEDITABLE,    // FIELD_synBit
        FD_ISEDITABLE,    // FIELD_finBit
        FD_ISEDITABLE,    // FIELD_window
        FD_ISEDITABLE,    // FIELD_urgentPointer
        FD_ISEDITABLE,    // FIELD_crc
        FD_ISEDITABLE,    // FIELD_crcMode
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISREPLACEABLE | FD_ISRESIZABLE,    // FIELD_headerOption
    };
    return (field >= 0 && field < 18) ? fieldTypeFlags[field] : 0;
}

const char *TcpHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcPort",
        "destPort",
        "sequenceNo",
        "ackNo",
        "headerLength",
        "cwrBit",
        "eceBit",
        "urgBit",
        "ackBit",
        "pshBit",
        "rstBit",
        "synBit",
        "finBit",
        "window",
        "urgentPointer",
        "crc",
        "crcMode",
        "headerOption",
    };
    return (field >= 0 && field < 18) ? fieldNames[field] : nullptr;
}

int TcpHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "srcPort") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destPort") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sequenceNo") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ackNo") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "headerLength") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "cwrBit") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "eceBit") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "urgBit") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "ackBit") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "pshBit") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "rstBit") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "synBit") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "finBit") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "window") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "urgentPointer") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "crc") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "crcMode") == 0) return baseIndex + 16;
    if (strcmp(fieldName, "headerOption") == 0) return baseIndex + 17;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_srcPort
        "unsigned short",    // FIELD_destPort
        "uint32_t",    // FIELD_sequenceNo
        "uint32_t",    // FIELD_ackNo
        "inet::B",    // FIELD_headerLength
        "bool",    // FIELD_cwrBit
        "bool",    // FIELD_eceBit
        "bool",    // FIELD_urgBit
        "bool",    // FIELD_ackBit
        "bool",    // FIELD_pshBit
        "bool",    // FIELD_rstBit
        "bool",    // FIELD_synBit
        "bool",    // FIELD_finBit
        "uint16_t",    // FIELD_window
        "uint16_t",    // FIELD_urgentPointer
        "uint16_t",    // FIELD_crc
        "inet::CrcMode",    // FIELD_crcMode
        "inet::tcp::TcpOption",    // FIELD_headerOption
    };
    return (field >= 0 && field < 18) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpHeaderDescriptor::getFieldPropertyNames(int field) const
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
        case FIELD_headerOption: {
            static const char *names[] = { "owned",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TcpHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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
        case FIELD_headerOption:
            if (!strcmp(propertyName, "owned")) return "";
            return nullptr;
        default: return nullptr;
    }
}

int TcpHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerOption: return pp->getHeaderOptionArraySize();
        default: return 0;
    }
}

void TcpHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerOption: pp->setHeaderOptionArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpHeader'", field);
    }
}

const char *TcpHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerOption: { const TcpOption * value = pp->getHeaderOption(i); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string TcpHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: return ulong2string(pp->getSrcPort());
        case FIELD_destPort: return ulong2string(pp->getDestPort());
        case FIELD_sequenceNo: return ulong2string(pp->getSequenceNo());
        case FIELD_ackNo: return ulong2string(pp->getAckNo());
        case FIELD_headerLength: return unit2string(pp->getHeaderLength());
        case FIELD_cwrBit: return bool2string(pp->getCwrBit());
        case FIELD_eceBit: return bool2string(pp->getEceBit());
        case FIELD_urgBit: return bool2string(pp->getUrgBit());
        case FIELD_ackBit: return bool2string(pp->getAckBit());
        case FIELD_pshBit: return bool2string(pp->getPshBit());
        case FIELD_rstBit: return bool2string(pp->getRstBit());
        case FIELD_synBit: return bool2string(pp->getSynBit());
        case FIELD_finBit: return bool2string(pp->getFinBit());
        case FIELD_window: return ulong2string(pp->getWindow());
        case FIELD_urgentPointer: return ulong2string(pp->getUrgentPointer());
        case FIELD_crc: return ulong2string(pp->getCrc());
        case FIELD_crcMode: return enum2string(pp->getCrcMode(), "inet::CrcMode");
        case FIELD_headerOption: { auto obj = pp->getHeaderOption(i); return obj == nullptr ? "" : obj->str(); }
        default: return "";
    }
}

void TcpHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(string2ulong(value)); break;
        case FIELD_destPort: pp->setDestPort(string2ulong(value)); break;
        case FIELD_sequenceNo: pp->setSequenceNo(string2ulong(value)); break;
        case FIELD_ackNo: pp->setAckNo(string2ulong(value)); break;
        case FIELD_headerLength: pp->setHeaderLength(B(string2long(value))); break;
        case FIELD_cwrBit: pp->setCwrBit(string2bool(value)); break;
        case FIELD_eceBit: pp->setEceBit(string2bool(value)); break;
        case FIELD_urgBit: pp->setUrgBit(string2bool(value)); break;
        case FIELD_ackBit: pp->setAckBit(string2bool(value)); break;
        case FIELD_pshBit: pp->setPshBit(string2bool(value)); break;
        case FIELD_rstBit: pp->setRstBit(string2bool(value)); break;
        case FIELD_synBit: pp->setSynBit(string2bool(value)); break;
        case FIELD_finBit: pp->setFinBit(string2bool(value)); break;
        case FIELD_window: pp->setWindow(string2ulong(value)); break;
        case FIELD_urgentPointer: pp->setUrgentPointer(string2ulong(value)); break;
        case FIELD_crc: pp->setCrc(string2ulong(value)); break;
        case FIELD_crcMode: pp->setCrcMode((inet::CrcMode)string2enum(value, "inet::CrcMode")); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpHeader'", field);
    }
}

omnetpp::cValue TcpHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: return (omnetpp::intval_t)(pp->getSrcPort());
        case FIELD_destPort: return (omnetpp::intval_t)(pp->getDestPort());
        case FIELD_sequenceNo: return (omnetpp::intval_t)(pp->getSequenceNo());
        case FIELD_ackNo: return (omnetpp::intval_t)(pp->getAckNo());
        case FIELD_headerLength: return cValue(pp->getHeaderLength().get(),"B");
        case FIELD_cwrBit: return pp->getCwrBit();
        case FIELD_eceBit: return pp->getEceBit();
        case FIELD_urgBit: return pp->getUrgBit();
        case FIELD_ackBit: return pp->getAckBit();
        case FIELD_pshBit: return pp->getPshBit();
        case FIELD_rstBit: return pp->getRstBit();
        case FIELD_synBit: return pp->getSynBit();
        case FIELD_finBit: return pp->getFinBit();
        case FIELD_window: return (omnetpp::intval_t)(pp->getWindow());
        case FIELD_urgentPointer: return (omnetpp::intval_t)(pp->getUrgentPointer());
        case FIELD_crc: return (omnetpp::intval_t)(pp->getCrc());
        case FIELD_crcMode: return static_cast<int>(pp->getCrcMode());
        case FIELD_headerOption: return omnetpp::toAnyPtr(pp->getHeaderOption(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpHeader' as cValue -- field index out of range?", field);
    }
}

void TcpHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_srcPort: pp->setSrcPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_destPort: pp->setDestPort(omnetpp::checked_int_cast<unsigned short>(value.intValue())); break;
        case FIELD_sequenceNo: pp->setSequenceNo(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_ackNo: pp->setAckNo(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_headerLength: pp->setHeaderLength(B(value.intValueInUnit("B"))); break;
        case FIELD_cwrBit: pp->setCwrBit(value.boolValue()); break;
        case FIELD_eceBit: pp->setEceBit(value.boolValue()); break;
        case FIELD_urgBit: pp->setUrgBit(value.boolValue()); break;
        case FIELD_ackBit: pp->setAckBit(value.boolValue()); break;
        case FIELD_pshBit: pp->setPshBit(value.boolValue()); break;
        case FIELD_rstBit: pp->setRstBit(value.boolValue()); break;
        case FIELD_synBit: pp->setSynBit(value.boolValue()); break;
        case FIELD_finBit: pp->setFinBit(value.boolValue()); break;
        case FIELD_window: pp->setWindow(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_urgentPointer: pp->setUrgentPointer(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crc: pp->setCrc(omnetpp::checked_int_cast<uint16_t>(value.intValue())); break;
        case FIELD_crcMode: pp->setCrcMode(static_cast<inet::CrcMode>(value.intValue())); break;
        case FIELD_headerOption: pp->setHeaderOption(i,omnetpp::fromAnyPtr<TcpOption>(value.pointerValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpHeader'", field);
    }
}

const char *TcpHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_headerOption: return omnetpp::opp_typename(typeid(TcpOption));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerOption: return omnetpp::toAnyPtr(pp->getHeaderOption(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpHeader *pp = omnetpp::fromAnyPtr<TcpHeader>(object); (void)pp;
    switch (field) {
        case FIELD_headerOption: pp->setHeaderOption(i,omnetpp::fromAnyPtr<TcpOption>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpHeader'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

