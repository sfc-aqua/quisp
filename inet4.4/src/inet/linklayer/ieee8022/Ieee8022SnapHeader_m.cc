//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee8022/Ieee8022SnapHeader.msg.
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
#include "Ieee8022SnapHeader_m.h"

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

Register_Class(Ieee8022SnapHeader)

Ieee8022SnapHeader::Ieee8022SnapHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(5));

}

Ieee8022SnapHeader::Ieee8022SnapHeader(const Ieee8022SnapHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Ieee8022SnapHeader::~Ieee8022SnapHeader()
{
}

Ieee8022SnapHeader& Ieee8022SnapHeader::operator=(const Ieee8022SnapHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Ieee8022SnapHeader::copy(const Ieee8022SnapHeader& other)
{
    this->oui = other.oui;
    this->protocolId = other.protocolId;
}

void Ieee8022SnapHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->oui);
    doParsimPacking(b,this->protocolId);
}

void Ieee8022SnapHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->oui);
    doParsimUnpacking(b,this->protocolId);
}

int Ieee8022SnapHeader::getOui() const
{
    return this->oui;
}

void Ieee8022SnapHeader::setOui(int oui)
{
    handleChange();
    this->oui = oui;
}

int Ieee8022SnapHeader::getProtocolId() const
{
    return this->protocolId;
}

void Ieee8022SnapHeader::setProtocolId(int protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

class Ieee8022SnapHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_oui,
        FIELD_protocolId,
    };
  public:
    Ieee8022SnapHeaderDescriptor();
    virtual ~Ieee8022SnapHeaderDescriptor();

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

Register_ClassDescriptor(Ieee8022SnapHeaderDescriptor)

Ieee8022SnapHeaderDescriptor::Ieee8022SnapHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee8022SnapHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

Ieee8022SnapHeaderDescriptor::~Ieee8022SnapHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee8022SnapHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee8022SnapHeader *>(obj)!=nullptr;
}

const char **Ieee8022SnapHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee8022SnapHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee8022SnapHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee8022SnapHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_oui
        FD_ISEDITABLE,    // FIELD_protocolId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee8022SnapHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "oui",
        "protocolId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee8022SnapHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "oui") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee8022SnapHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_oui
        "int",    // FIELD_protocolId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee8022SnapHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee8022SnapHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee8022SnapHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee8022SnapHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee8022SnapHeader'", field);
    }
}

const char *Ieee8022SnapHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee8022SnapHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: return long2string(pp->getOui());
        case FIELD_protocolId: return long2string(pp->getProtocolId());
        default: return "";
    }
}

void Ieee8022SnapHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: pp->setOui(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022SnapHeader'", field);
    }
}

omnetpp::cValue Ieee8022SnapHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: return pp->getOui();
        case FIELD_protocolId: return pp->getProtocolId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee8022SnapHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee8022SnapHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: pp->setOui(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022SnapHeader'", field);
    }
}

const char *Ieee8022SnapHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee8022SnapHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee8022SnapHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022SnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022SnapHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022SnapHeader'", field);
    }
}

Register_Class(Ieee8022LlcSnapHeader)

Ieee8022LlcSnapHeader::Ieee8022LlcSnapHeader() : ::inet::Ieee8022LlcHeader()
{
    this->setChunkLength(B(8));
    this->setDsap(0xAA);
    this->setSsap(0xAA);
    this->setControl(0x03);

}

Ieee8022LlcSnapHeader::Ieee8022LlcSnapHeader(const Ieee8022LlcSnapHeader& other) : ::inet::Ieee8022LlcHeader(other)
{
    copy(other);
}

Ieee8022LlcSnapHeader::~Ieee8022LlcSnapHeader()
{
}

Ieee8022LlcSnapHeader& Ieee8022LlcSnapHeader::operator=(const Ieee8022LlcSnapHeader& other)
{
    if (this == &other) return *this;
    ::inet::Ieee8022LlcHeader::operator=(other);
    copy(other);
    return *this;
}

void Ieee8022LlcSnapHeader::copy(const Ieee8022LlcSnapHeader& other)
{
    this->oui = other.oui;
    this->protocolId = other.protocolId;
}

void Ieee8022LlcSnapHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ieee8022LlcHeader::parsimPack(b);
    doParsimPacking(b,this->oui);
    doParsimPacking(b,this->protocolId);
}

void Ieee8022LlcSnapHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ieee8022LlcHeader::parsimUnpack(b);
    doParsimUnpacking(b,this->oui);
    doParsimUnpacking(b,this->protocolId);
}

int Ieee8022LlcSnapHeader::getOui() const
{
    return this->oui;
}

void Ieee8022LlcSnapHeader::setOui(int oui)
{
    handleChange();
    this->oui = oui;
}

int Ieee8022LlcSnapHeader::getProtocolId() const
{
    return this->protocolId;
}

void Ieee8022LlcSnapHeader::setProtocolId(int protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

class Ieee8022LlcSnapHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_oui,
        FIELD_protocolId,
    };
  public:
    Ieee8022LlcSnapHeaderDescriptor();
    virtual ~Ieee8022LlcSnapHeaderDescriptor();

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

Register_ClassDescriptor(Ieee8022LlcSnapHeaderDescriptor)

Ieee8022LlcSnapHeaderDescriptor::Ieee8022LlcSnapHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee8022LlcSnapHeader)), "inet::Ieee8022LlcHeader")
{
    propertyNames = nullptr;
}

Ieee8022LlcSnapHeaderDescriptor::~Ieee8022LlcSnapHeaderDescriptor()
{
    delete[] propertyNames;
}

bool Ieee8022LlcSnapHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee8022LlcSnapHeader *>(obj)!=nullptr;
}

const char **Ieee8022LlcSnapHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *Ieee8022LlcSnapHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int Ieee8022LlcSnapHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int Ieee8022LlcSnapHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_oui
        FD_ISEDITABLE,    // FIELD_protocolId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee8022LlcSnapHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "oui",
        "protocolId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee8022LlcSnapHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "oui") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *Ieee8022LlcSnapHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_oui
        "int",    // FIELD_protocolId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee8022LlcSnapHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee8022LlcSnapHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int Ieee8022LlcSnapHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void Ieee8022LlcSnapHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'Ieee8022LlcSnapHeader'", field);
    }
}

const char *Ieee8022LlcSnapHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee8022LlcSnapHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: return long2string(pp->getOui());
        case FIELD_protocolId: return long2string(pp->getProtocolId());
        default: return "";
    }
}

void Ieee8022LlcSnapHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: pp->setOui(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022LlcSnapHeader'", field);
    }
}

omnetpp::cValue Ieee8022LlcSnapHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: return pp->getOui();
        case FIELD_protocolId: return pp->getProtocolId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'Ieee8022LlcSnapHeader' as cValue -- field index out of range?", field);
    }
}

void Ieee8022LlcSnapHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        case FIELD_oui: pp->setOui(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022LlcSnapHeader'", field);
    }
}

const char *Ieee8022LlcSnapHeaderDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr Ieee8022LlcSnapHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void Ieee8022LlcSnapHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    Ieee8022LlcSnapHeader *pp = omnetpp::fromAnyPtr<Ieee8022LlcSnapHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'Ieee8022LlcSnapHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

